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
#include <Ultrasonic.h>

//MotorDriver
#define IN1 4
#define AN1 5
#define AN2 6
#define IN2 7
Cytron_SmartDriveDuo MDriver(PWM_INDEPENDENT, IN1, IN2, AN1, AN2);

//Other Variables
char val;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0){
      val = Serial.read();
      Drive(val,30);
  }
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
       MDriver.control(spd/2, spd);
       break;
    case 'L':
       MDriver.control(spd, spd/2);
       break;
    default:
       Brake();
       break;
  }
}

void Brake(){
  MDriver.control(0,0);
}
