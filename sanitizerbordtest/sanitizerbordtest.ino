/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. 18 is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 18 as an output.
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(19, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(18, HIGH);
  digitalWrite(23, LOW);
    digitalWrite(26, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(27, HIGH);
  digitalWrite(25, LOW);
  digitalWrite(2, LOW);
  digitalWrite(13, HIGH);
  delay(1000);                       // wait for a second
  digitalWrite(19, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(23, HIGH);
  digitalWrite(18, LOW);
    digitalWrite(26, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(25, HIGH);
  digitalWrite(27, LOW);
    digitalWrite(13, LOW);
  digitalWrite(2 , HIGH);
  
  
  delay(1000);                       // wait for a second
}
