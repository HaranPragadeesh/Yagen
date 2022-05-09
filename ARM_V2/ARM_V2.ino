

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver Arm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#define Base 0 // CHANNEL 1 - Base
#define Shoulder 1 // CHANNEL 2 - Shoulder
#define Elbow 2 // CHANNEL 3 - Elbow
#define Wrist 3 // CHANNEL 4 - Wrist
#define Palm 4 // CHANNEL 5 - Palm
#define Clamp 5 // CHANNEL 6 - Clamp

#define Little 8 // CHANNEL 9 - Base
#define Ring 9 // CHANNEL 10 - Shoulder
#define Middle 10 // CHANNEL 11 - Elbow
#define Index 11 // CHANNEL 12 - Wrist
#define Wris 12 // CHANNEL 13 - Palm

int ShoulderB;
void setup() {
  Serial.begin(9600);
  Arm.begin();
  Arm.setOscillatorFrequency(27000000);
  Arm.setPWMFreq(SERVO_FREQ);
  delay(10);

  yield();
}

// the code inside loop() has been updated by Robojax
void loop() {
  Arm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  ArmControl(0,75,45,65,15);
  ArmControl(40,75,45,65,75);
  ClampO(60);
  delay(250);
  ArmControl(40,0,40,65,15);
  delay(250);
  ClampC(20);
  ArmControl(40,75,60,65,15);
  ArmControl(90,75,60,65,15);
  ShoulderB = map(50, 0, 180, SERVOMIN, SERVOMAX);
  Arm.setPWM(Shoulder, 0, ShoulderB);
  delay(1000);
  ClampO(60);
  delay(250);
  ClampC(20);
  delay(60000);
  
//  delay(5000);
//  Bionic(0,135,0,135,0);
//  delay(2000);
//  Bionic(135,0,135,0,60);

}
void ArmControl(int baseA, int ShoulderA, int ElbowA, int WristA, int PalmA){

  baseA = map(baseA, 0, 180, SERVOMIN, SERVOMAX);
  ShoulderA = map(ShoulderA, 0, 180, SERVOMIN, SERVOMAX);
  ElbowA = map(ElbowA, 0, 180, SERVOMIN, SERVOMAX);
  WristA = map(WristA, 0, 180, SERVOMIN, SERVOMAX);
  PalmA = map(PalmA, 0, 180, SERVOMIN, SERVOMAX);
  

  // Serial.println(baseA);
  // Serial.println(ShoulderA);
  // Serial.println(ElbowA);
  // Serial.println(WristA);
  // Serial.println(PalmA);
  // Serial.println(ClampA);

  Arm.setPWM(Base, 0, baseA);
  delay(800);
  Arm.setPWM(Shoulder, 0, ShoulderA);
  delay(800);
  Arm.setPWM(Elbow, 0, ElbowA);
  delay(800);
  Arm.setPWM(Wrist, 0, WristA);
  delay(800);
  Arm.setPWM(Palm, 0, PalmA);
  delay(800);
  

}
void Bionic(int LittleA, int RingA, int MiddleA, int IndexA, int WrisA){

  LittleA = map(LittleA, 0, 180, SERVOMIN, SERVOMAX);
  RingA = map(RingA, 0, 180, SERVOMIN, SERVOMAX);
  MiddleA = map(MiddleA, 0, 180, SERVOMIN, SERVOMAX);
  IndexA = map(IndexA, 0, 180, SERVOMIN, SERVOMAX);
  WrisA = map(WrisA, 0, 180, SERVOMIN, SERVOMAX);
  

  // Serial.println(baseA);
  // Serial.println(ShoulderA);
  // Serial.println(ElbowA);
  // Serial.println(WristA);
  // Serial.println(PalmA);
  // Serial.println(ClampA);
  
  Arm.setPWM(Little, 0,LittleA);
  delay(200);
  Arm.setPWM(Ring, 0, RingA);
  delay(200);
  Arm.setPWM(Middle, 0, MiddleA);
  delay(200);
  Arm.setPWM(Index, 0, IndexA);
  delay(200);
  Arm.setPWM(Wris, 0, WrisA);
  delay(500);
 
  

}
void ClampO(int ClampA){
  ClampA = map(ClampA, 0, 180, SERVOMIN, SERVOMAX);
  Arm.setPWM(Clamp,0,ClampA);
  delay(1000);
  
  }
void ClampC(int ClampA){
  ClampA = map(ClampA, 0, 180, SERVOMIN, SERVOMAX);
  Arm.setPWM(Clamp,0,ClampA);
  delay(1000);
  
  }
// void ArmControlAdv(int baseA, int shoulderA, int elbowA, int wristA, int palmA, int clampA){

//   for (int bai = 0; baseA > bai ; bai++){
//     base.write(bai);
//   }
//   delay(20);
//   for (int shi = 0;shoulderA > shi; shi++){
//     shoulder.write(shi);
//   }
//   delay(20);
//   for (int eli = 0; elbowA > eli ; eli++){
//     elbow.write(eli);
//   }
//   delay(20);
//   for (int wri = 0; wri < wristA+1; wri++){
//     wrist.write(wri);
//   }
//   delay(20);
//   for (int pai = 0; pai < palmA+1; pai++){
//     palm.write(pai);
//   }
//   delay(20);
//   for (int cli = 0; cli < clampA+1; cli++){
//     clamp.write(cli);
//   }
//   delay(20);

// }
