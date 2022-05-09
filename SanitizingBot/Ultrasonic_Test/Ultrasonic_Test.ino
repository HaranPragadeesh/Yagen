// * Hardware Connection Arduino Uno and Ultrasonic 1 and 2:
// *   GND ------------- GND
// *   5v -------------- 5v
// *   12 -------------- Trig1
// *   11 -------------- Echo1 (PWM)
// *   8 --------------- Trig2
// *   9 --------------- Echo2 (PWM)

#include <Ultrasonic.h>

//Ultrasonic Variables
Ultrasonic ultrasonic1(12, 11);
Ultrasonic ultrasonic2(8, 9);
int obs1 = 0;
int obs2 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  obs1 = ultrasonic1.read();
  //Serial.println(obs1);
  obs2 = ultrasonic2.read();
  //Serial.println(obs2);
  if (obs1 > 10 && obs2 > 10){
     Serial.println("Following line");
  }
  else{
    //Serial.println("Stopped following line");

    if (obs1 > 10 ){
        Serial.println("Obstacle detected by Sensor 2 at a Distance: ");
        Serial.print(obs2);
    } 
    else if (obs2 > 10){
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
}
