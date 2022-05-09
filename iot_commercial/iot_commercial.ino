/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. 33 is set to
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
  // initialize digital pin 33 as an output.
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(33, HIGH);
//  digitalWrite(25, HIGH);
//  digitalWrite(26, HIGH);
//  digitalWrite(27, HIGH);
//  digitalWrite(13, HIGH);
  delay(1000);                       // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
//  digitalWrite(33, LOW);
//  digitalWrite(25, LOW);
//  digitalWrite(26, LOW);
//  digitalWrite(27, LOW);
//  digitalWrite(13, LOW);
  delay(1000);                       // wait for a second
}
