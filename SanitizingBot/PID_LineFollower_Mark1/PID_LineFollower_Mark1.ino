// * Hardware Connection Arduino Uno and MDDS30:
// *   GND ---------- GND
// *   4 ------------ IN1
// *   5 ------------ AN1 (PWM)
// *   6 ------------ AN2 (PWM)
// *   7 ------------ IN2

// * Hardware Connection Arduino Uno and Line Array:
// *   GND ----------- GND
// *   5v ------------ 5v
// *   A0 ------------ S1
// *   A1 ------------ S2
// *   A2 ------------ S3
// *   A3 ------------ S4
// *   A4 ------------ S5
// *   A5 ------------ S6

// * Hardware Connection Arduino Uno and Ultrasonic 1 and 2:
// *   GND ------------- GND
// *   5v -------------- 5v
// *   12 -------------- Trig1
// *   11 -------------- Echo1 (PWM)
// *   8 --------------- Trig2
// *   9 --------------- Echo2 (PWM)

// * Hardware Connection Arduino Uno and Relay:
// *   G ------------- GND
// *   V ------------- 5v
// *   S ------------- 10 (PWM)

#include <Cytron_SmartDriveDuo.h>
#include <Ultrasonic.h>

//Line Sensor Array
int S1 = A0; //Right 
int S2 = A1;
int S3 = A2;
int S4 = A3;
int S5 = A4;
int S6 = A5; //Left
int SensorVals[6] = {0, 0, 0, 0, 0, 0};

//MotorDriver
#define IN1 4
#define AN1 5
#define AN2 6
#define IN2 7
Cytron_SmartDriveDuo MDriver(PWM_INDEPENDENT, IN1, IN2, AN1, AN2);

//Ultrasonic
Ultrasonic ultrasonic1(12, 11);
Ultrasonic ultrasonic2(8, 9);
int obs = 0;

//Relay
int relay = 9;

//Other Variables
int BaseMotorSpeed = 15;
int MaxSpeed = 20;
int Lspeed, Rspeed = 0;
int BasePos = 2500;
float Pos = 0;
float P , I , D, PIDVal, lastP = 0;
float Kp = 0.008;
float Ki = 0.00008;
float Kd = 0.01;

void setup() {
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);
  pinMode(S6,INPUT);
  
  Serial.begin(9600);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  Serial.println("INITIATING THE BOT...");
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println ("S0     S1     S2     S3     S4     S5     Current Position");
  Serial.println ("----------------------------------------------------------");
// Serial.println ("P     I     D     PIDVal");
// Serial.println ("------------------------");
  Brake();
}

void loop() {

//  obs1 = ultrasonic1.read();
//  obs2 = ultrasonic2.read();
//  if (obs1 > 10 && obs2 > 10){
//    uint16_t position = line.readLineBlack(sensorValues);
//    if (0 > (int)position > 5000){
//      Serial.println("Distance: ");
//      Serial.print(obs);
//      analogWrite(relay,255);
//    }

Pos = AreadSensorVal();
//  PIDVal = PIDv(Pos,Kp,Ki,Kd);
//  Lspeed = constrain(BaseMotorSpeed + PIDVal, -MaxSpeed, MaxSpeed);
//  Rspeed = constrain(BaseMotorSpeed - PIDVal, -MaxSpeed, MaxSpeed);
//  Move(Lspeed, Rspeed);
//  Serial.print("LeftSpeed: ");
//  Serial.println(Lspeed);
//  Serial.print("RightSpeed: ");
//  Serial.println(Rspeed);

//  }
// else {
//  Brake();
//  analogWrite(relay,0);
//  if (obs1 > 10 ){
//    Serial.println("Obstacle detected by Sensor 2 at a Distance: ");
//    Serial.print(obs2);
//  } else if (obs2 > 10){
//    Serial.println("Obstacle detected by Sensor 1 at a Distance: ");
//    Serial.print(obs1);
//  }
//  else {
//    Serial.println("Obstacle detected by Sensors 1 & 2 at a Distances: ");
//    Serial.println(obs1);
//    Serial.println("  ");
//    Serial.println(obs2);
//    Serial.println(" respectively.");
//  }
// }
  delay(500);
}

float PIDv (float pos, float kp, float ki, float kd){
  P = (pos - BasePos);
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

float AreadSensorVal(){
  //This function gets Analog Read values from the sensors
  //The GreyRobotics Line Array Sensor gives values in a range of 0 -1024
  //The following map function maps the value of tne sensor to a range of 0 - 255
  
  SensorVals[0] = map(analogRead(S1),0,1024,0,1000);
  SensorVals[1] = map(analogRead(S2),0,1024,0,1000);
  SensorVals[2] = map(analogRead(S3),0,1024,0,1000);
  SensorVals[3] = map(analogRead(S4),0,1024,0,1000);
  SensorVals[4] = map(analogRead(S5),0,1024,0,1000);
  SensorVals[5] = map(analogRead(S6),0,1024,0,1000);

   float currPos;
   currPos = (SensorVals[0]*0 + SensorVals[1]*1 + SensorVals[2]*2 + 
                SensorVals[4]*3 + SensorVals[5]*4 + SensorVals[6]*5)
                /(SensorVals[0]+SensorVals[1]+SensorVals[2]+SensorVals[3]+SensorVals[4]+SensorVals[5]);

//   Serial.println("");
//   Serial.print (SensorVals[0]);
//   Serial.print("     ");
//   Serial.print (SensorVals[1]);
//   Serial.print("     ");
//   Serial.print (SensorVals[2]);
//   Serial.print("     ");
//   Serial.print (SensorVals[3]);
//   Serial.print("     ");
//   Serial.print (SensorVals[4]);
//   Serial.print("     ");
//   Serial.print (SensorVals[5]);
//   Serial.print("     ");
//   Serial.print (currPos);

   return currPos;
}

float DreadSensorVal(){
  //This function gets Digital Read Values from the sensors
  
  SensorVals[0] = digitalRead(S1);
  SensorVals[1] = digitalRead(S2);
  SensorVals[2] = digitalRead(S3);
  SensorVals[3] = digitalRead(S4);
  SensorVals[4] = digitalRead(S5);
  SensorVals[5] = digitalRead(S6);

  float currPos;
  currPos = (SensorVals[0]*0 + SensorVals[1]*1 + SensorVals[2]*2 + 
                SensorVals[4]*3 + SensorVals[5]*4 + SensorVals[6]*5)
                /(SensorVals[0]+SensorVals[1]+SensorVals[2]+SensorVals[3]+SensorVals[4]+SensorVals[5]);
//   Serial.println("");
//   Serial.print (SensorVals[0]);
//   Serial.print("     ");
//   Serial.print (SensorVals[1]);
//   Serial.print("     ");
//   Serial.print (SensorVals[2]);
//   Serial.print("     ");
//   Serial.print (SensorVals[3]);
//   Serial.print("     ");
//   Serial.print (SensorVals[4]);
//   Serial.print("     ");
//   Serial.print (SensorVals[5]);
//   Serial.print("     ");
//   Serial.print (currPos);

   return currPos;
}

void Move(int spdL, int spdR){
  MDriver.control(spdL, spdR);
}

void Drive(char dir, int spd){
  switch(dir){
    case 'F':
       MDriver.control(spd, spd);
       break;
    case 'B':
       MDriver.control(-spd, -spd);
       break;
    case 'R':
       MDriver.control(spd, spd-50);
       break;
    case 'L':
       MDriver.control(spd-50, spd);
       break;
    default:
       Brake();
       break;
  }
}

void Brake(){
  MDriver.control(0,0);
}
