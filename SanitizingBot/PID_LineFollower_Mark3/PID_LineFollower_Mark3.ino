// * Hardware Connection Arduino Uno and MDDS30:
// *   GND ---------- GND
// *   4 ------------ IN1
// *   5 ------------ AN1 (PWM)
// *   6 ------------ AN2 (PWM)
// *   7 ------------ IN2

// * Hardware Connection Arduino Uno and Line Array:
// *   GND ----------- GND
// *   5v ------------ 5v
// *   A0 ------------ S1 (A0)
// *   A1 ------------ S2 (A1) 
// *   A2 ------------ S3 (A2)
// *   A3 ------------ S4 (A3)
// *   A4 ------------ S5 (A4)
// *   A5 ------------ S6 (A5)

// * Hardware Connection Arduino Uno and Ultrasonic 1 and 2:
// *   GND ------------- GND
// *   5v -------------- 5v
// *   12 -------------- Trig1
// *   11 -------------- Echo1 (PWM)
// *   8 --------------- Trig2
// *   9 --------------- Echo2 (PWM)

// * Hardware Connection Arduino Uno and Bluetooth:
// *   GND ------------- GND
// *   5v -------------- 5v
// *   TX -------------- RX
// *   RX -------------- TX

// * Hardware Connection Arduino Uno and Relay:
// *   G ------------- GND
// *   V ------------- 5v
// *   S ------------- 10 (PWM)


#include <Cytron_SmartDriveDuo.h>
#include <QTRSensors.h>
#include <Ultrasonic.h>

//Line Sensor Array
QTRSensors line;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

//MotorDriver
#define IN1 4
#define AN1 5
#define AN2 6
#define IN2 7
Cytron_SmartDriveDuo MDriver(PWM_INDEPENDENT, IN1, IN2, AN1, AN2);

//Ultrasonic
Ultrasonic ultrasonic1(12, 11);
Ultrasonic ultrasonic2(8, 9);
int obs1 = 0;
int obs2 = 0;

//Relay
int relay = 10;

//Other Variables
int BaseMotorSpeed = 15;
int MaxSpeed = 20;
int Lspeed, Rspeed = 0;
int BasePos = 2500;
bool calib = true;
float Pos = 0;
float P , I , D, PIDVal, lastP = 0;
float Kp = 0.008;
float Kd = 0.01;
float Ki = 0.0001;
char val;
int mode;

void setup() {

  line.setTypeAnalog();
  line.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, SensorCount);
  line.setEmitterPin(2);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relay, OUTPUT);
  
  Serial.begin(9600);
  
  Serial.println("Calibrating Line Sensor...");
  digitalWrite(LED_BUILTIN, HIGH);
  calibSensor();
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
 
  Serial.println("INITIATING THE BOT...");
  Serial.println("SELECT A MODE: 0-Line Follow ; 1-Manual Control; e-To Exit a mode" );
//  Serial.println ("P     I     D     PIDVal");
//  Serial.println ("------------------------");
  Brake();
}

void loop() {
  
  if (Serial.available() > 0){
    mode = Serial.parseInt();
    Serial.println ("Mode: ");
    //Serial.print (mode);
      while (mode == 1){
        obs1 = ultrasonic1.read();
        obs2 = ultrasonic2.read();
        if (obs1 > 30 && obs2 > 30){
          while (Serial.available() == 0){}
            val = Serial.read();
            //Serial.print(val);
            Drive(val,30);
            delay(100);
            Brake();
            if (val == 'e' || val == 'E'){
              mode = 0;
              val = 'k';
              Serial.println ("Mode: ");
              Serial.print (mode);
              break;
            }else if (val == 'h' || val == 'H'){
              analogWrite(relay,255);
            }
            else if (val == 't' || val == 'T'){
              analogWrite(relay,0);
            }
        }
        else {
          Brake();
          analogWrite(relay,0);
          if (obs1 > 10 ){
//            Serial.println("Obstacle detected by Sensor 2 at a Distance: ");
//            Serial.print(obs2);
          } else if (obs2 > 10){
//            Serial.println("Obstacle detected by Sensor 1 at a Distance: ");
//            Serial.print(obs1);
          }
          else {
//            Serial.println("Obstacle detected by Sensors 1 & 2 at a Distances: ");
//            Serial.println(obs1);
//            Serial.println("  ");
//            Serial.println(obs2);
//            Serial.println(" respectively.");
          }
        }
      }
      while (mode == 0){
        obs1 = ultrasonic1.read();
        obs2 = ultrasonic2.read();
        if (obs1 > 30 && obs2 > 30){
          uint16_t position = line.readLineBlack(sensorValues);
          Serial.println((int)position);
          Serial.println();
          if (0 > (int)position > 5000){
            Serial.println("Distance: ");
            Serial.print(obs1);
            Serial.print(" ");
            Serial.print(obs2);
            analogWrite(relay,255);
            }
            PIDVal = PIDv((int)position,Kp,Ki,Kd);
            Lspeed = constrain(BaseMotorSpeed + PIDVal, -MaxSpeed, MaxSpeed);
            Rspeed = constrain(BaseMotorSpeed - PIDVal, -MaxSpeed, MaxSpeed);
            Move(Lspeed, Rspeed);
            Serial.print("LeftSpeed: ");
            Serial.println(Lspeed);
            Serial.print("RightSpeed: ");
            Serial.println(Rspeed);
        }
        else {
          Brake();
          analogWrite(relay,0);
          if (obs1 > 10 ){
            Serial.println("Obstacle detected by Sensor 2 at a Distance: ");
            Serial.print(obs2);
          } else if (obs2 > 10){
            Serial.println("Obstacle detected by Sensor 1 at a Distance: ");
            Serial.print(obs1);
          }
          else {
            Serial.println("Obstacle detected by Sensors 1 & 2 at a Distances: ");
            Serial.println(obs1);
            Serial.println("  ");
            Serial.println(obs2);
            Serial.println(" respectively.");
          }
        }
        val = Serial.read();
        if (val == 'e' || val == 'E' ){
          mode = 1;
          Serial.println ("Mode: ");
          Serial.print (mode);
          break;
          Serial.println (mode);
        }         
     }
  }
  delay(500);
}

float PIDv (int pos, float kp, float ki, float kd){
  P = pos - BasePos;
  I = I + P;
  D = P - lastP;

  lastP = P;

  float PIDv = P*kp + I*ki + D*kd;

  Serial.println("");
  Serial.print(P);
  Serial.print ("     ");
  Serial.print(I);
  Serial.print ("     ");
  Serial.print(D);
  Serial.print ("     ");
  Serial.print(PIDv);
  
  return PIDv;
}

void calibSensor (){
  
   for (uint16_t i = 0; i < 200; i++)
  {
    line.calibrate();
  }
  delay(500);

  //MINIMUM Value in the sensors
  Serial.println("Minimum Value in the sensors");
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(line.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  //MAXIMUM Value in the sensors
  Serial.println("Maximum Value in the sensors");
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(line.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
}

void Move(int spdL, int spdR){
  MDriver.control(spdL, spdR);
}

void Drive(char dir, int spd){
  switch(dir){
    case 'F'|'f':
       MDriver.control(spd, spd);
       break;
    case 'B'|'b':
       MDriver.control(-spd, -spd);
       break;
    case 'R'|'r':
       MDriver.control(spd, spd/2);
       break;
    case 'L'|'l':
       MDriver.control(spd/2, spd);
       break;
    default:
       Brake();
       break;
  }
}

void Brake(){
  MDriver.control(0,0);
}
