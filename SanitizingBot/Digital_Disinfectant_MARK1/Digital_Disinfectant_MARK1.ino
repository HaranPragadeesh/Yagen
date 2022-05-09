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
int obs1 = 0;
int obs2 = 0;

//Relay
int relay = 9;

//Other Variables
int MotorSpeed = 15;
float Pos = 0;
char val;
int mode;
bool RelayState;

void setup() {

  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  pinMode(S4,INPUT);
  pinMode(S5,INPUT);
  pinMode(S6,INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relay, OUTPUT);
  
  Serial.begin(9600);

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("INITIATING THE BOT...");
  RelayState = false;
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
 
  Serial.println ("SELECT A MODE: 0-Line Follow ; 1-Manual Control; e-To Exit a mode");

  Brake();
}

void loop() {
  
  if (Serial.available() > 0){
    mode = Serial.parseInt();
    Serial.println ("Mode: ");
    Serial.print (mode);
      while (mode == 1){
        while (Serial.available() == 0){}
          val = Serial.read();
          Serial.print(val);
          Drive(val,30);
          delay(100);
          Brake();
          if (val == 'e'){
            mode = 0;
            val = 'k';
            Serial.println ("Mode: ");
            Serial.print (mode);
            break;
          }
        }
      while (mode == 0){
//        obs1 = ultrasonic1.read();
//        obs2 = ultrasonic2.read();
//        if (obs1 > 10 && obs2 > 10){
          float pos = DreadSensorVal();
//          Serial.println(pos);
//          Serial.println();
          if (-2.0 <= pos <= 2.0){
//            Serial.println("Distance: ");
//            Serial.print(obs1);
//            Serial.print(" ");
//            Serial.print(obs2);
            RelayState = true;
            
             //MIDS
            if (pos == 0.0 || pos == 0.5){
              Drive('F', MotorSpeed);
            }
            
            //EXTREMES & LATER EXTREMES
            else if(pos == -2.0){
              Drive('L',MotorSpeed+5);
            } else if (pos == 2.0){
              Drive('R',MotorSpeed+5);
            }else if (pos == -1.5){
              Drive('L', MotorSpeed);
            }else if (pos == 1.5){
              Drive('R',MotorSpeed);
            }
            else{
              Brake();
              }
            }
            if (RelayState == true){
              digitalWrite(relay,HIGH);
            }else{
              digitalWrite(relay,LOW);
            }
//        }
//        else {
//          Brake();
//          RelayState = false;
//          digitalWrite(relay,LOW);
//          if (obs1 > 10 ){
//            Serial.println("Obstacle detected by Sensor 2 at a Distance: ");
//            Serial.print(obs2);
//          } else if (obs2 > 10){
//            Serial.println("Obstacle detected by Sensor 1 at a Distance: ");
//            Serial.print(obs1);
//          }
//          else {
//            Serial.println("Obstacle detected by Sensors 1 & 2 at a Distances: ");
//            Serial.println(obs1);
//            Serial.println("  ");
//            Serial.println(obs2);
//            Serial.println(" respectively.");
//          }
//        }
        val = Serial.read();
        if (val == 'e'){
          mode = 1;
          Serial.println ("Mode: ");
          Serial.print (mode);
          //break;
          Serial.println (mode);
        }         
     }
  }
  delay(500);
}

float DreadSensorVal(){
  //This function gets Analog Read values from the sensors
  //The GreyRobotics Line Array Sensor gives values in a range of 0 -1024
  //The following map function maps the value of tne sensor to a range of 0 - 255
  
  SensorVals[0] = digitalRead(S1);
  SensorVals[1] = digitalRead(S2);
  SensorVals[2] = digitalRead(S3);
  SensorVals[3] = digitalRead(S4);
  SensorVals[4] = digitalRead(S5);
  SensorVals[5] = digitalRead(S6);

  float currpos = 0;
  
  //EXTREMES
  if(SensorVals[0]== HIGH){
    currpos = -2.0; //ASSUMED RIGHT EXTREME
  } else if (SensorVals[5] == HIGH){
    currpos = 2.0; //ASSUMED LEFT EXTREME
  } else if (SensorVals[0]== HIGH && SensorVals[1] == HIGH){
    currpos = -1.5;
  }else if(SensorVals[4] == HIGH && SensorVals[5] == HIGH){
    currpos = 1.5;
  }
  //AFTER EXTREMES
  else if (SensorVals[1]== HIGH){
    currpos = -1.0;
  }else if(SensorVals[4] == HIGH){
    currpos = 1.0;
  }
  //MIDS
  else if (SensorVals[2]== HIGH){
    currpos = 0.0;
  }else if(SensorVals[3] == HIGH){
    currpos = 0.5;
  }
  else{
    currpos = 6.0;
  }
  
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
//   Serial.print (currpos);

   return currpos;
}


void Move(int spdL, int spdR){
  MDriver.control(spdL, spdR);
}

void Drive(char dir, int spd){
  switch(dir){
    case 'F':
       Move(spd, spd);
       Serial.println('F');
       break;
    case 'B':
       Move(-spd, -spd);
       Serial.println('B');
       break;
    case 'R':
       Move(spd, spd/2);
       Serial.println('R');
       break;
    case 'L':
       Move(spd/2, spd);
       Serial.println('L');
       break;
    default:
       Brake();
       break;
  }
}

void Brake(){
  Move(0,0);
}
