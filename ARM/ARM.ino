

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

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


void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();

  yield();
}

// the code inside loop() has been updated by Robojax
void loop() {
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  pwm.setPWM(0, 0, 125 );
  delay(500);
  pwm.setPWM(1, 0, 425 );
  delay(500);
  pwm.setPWM(2, 0, 350);
  delay(500);
  pwm.setPWM(3, 0, 350 );
  delay(500);
  pwm.setPWM(4, 0, 200);
  delay(2000);

 
  pwm.setPWM(0, 0, 275 );
  delay(1000);
  pwm.setPWM(4, 0, 350);
  delay(1000);
  pwm.setPWM(1, 0, 125);
  delay(500);
  pwm.setPWM(2, 0, 275);
  delay(1000);
  pwm.setPWM(3, 0, 350 );
  delay(1000);
  
  // 3rd Position
  pwm.setPWM(4, 0, 200);
  delay(500);
  pwm.setPWM(5, 0, 600);
  delay(1000);
  pwm.setPWM(5, 0, 300);
  delay(1000);

  //4th Position
  pwm.setPWM(0, 0, 275 );
  delay(500);
  pwm.setPWM(1, 0, 425 );
  delay(500);
  pwm.setPWM(2, 0, 350);
  delay(500);
  pwm.setPWM(3, 0, 350 );
  delay(500);
  pwm.setPWM(4, 0, 200);
  delay(2000);

  // 5th Position
  pwm.setPWM(0, 0, 400 );
  delay(500);
  pwm.setPWM(4, 0, 350);
  delay(500);
  pwm.setPWM(1, 0, 125);
  delay(500);
  pwm.setPWM(2, 0, 275);
  delay(500);
  pwm.setPWM(3, 0, 350 );
  delay(2500);

  //6th position
  pwm.setPWM(1, 0, 425 );
  delay(500);
  pwm.setPWM(2, 0, 350);
  delay(500);
  pwm.setPWM(0, 0, 125 );
  delay(500);
  pwm.setPWM(3, 0, 350 );
  delay(500);
  pwm.setPWM(4, 0, 200);
  delay(1000);
  
  
}
