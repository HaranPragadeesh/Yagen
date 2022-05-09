#include <SPI.h>
#include <nRF24L01.h>
#include<RF24.h>
#include<Wire.h>

//Declarations

//RIGHT BUTTONS
#define B7 A4  // Button R-UP
#define B3 8   // Button R-DOWN
#define B6 9   // Button R-LEFT
#define B2 10  // Button R-RIGHT
//LEFT BUTTONS
#define B8 2   // Button L-UP
#define B1 7   // Button L-DOWN
#define B4 3   // Button L-LEFT
#define B5 4   // Button L-RIGHT

RF24 radio(5, 6);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001"; // Address

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  byte button1;
  byte button2;
  byte button3;
  byte button4;
  byte button5;
  byte button6;
  byte button7;
  byte button8;
};
Data_Package data;

void setup() {
  Serial.begin(9600);

  pinMode(B1,INPUT_PULLUP);
  pinMode(B2,INPUT_PULLUP);
  pinMode(B3,INPUT_PULLUP);
  pinMode(B4,INPUT_PULLUP);
  pinMode(B5,INPUT_PULLUP);
  pinMode(B6,INPUT_PULLUP);
  pinMode(B7,INPUT_PULLUP);
  pinMode(B8,INPUT_PULLUP);

  data.button1 = 1;
  data.button2 = 1;
  data.button3 = 1;
  data.button4 = 1;
  data.button5 = 1;
  data.button6 = 1;
  data.button7 = 1;
  data.button8 = 1;
}

void loop() {

  data.button1 = digitalRead(B1);
  data.button2 = digitalRead(B2);
  data.button3 = digitalRead(B3);
  data.button4 = digitalRead(B4);
  data.button5 = digitalRead(B5);
  data.button6 = digitalRead(B6);
  data.button7 = digitalRead(B7);
  data.button8 = digitalRead(B8);

  radio.write(&data, sizeof(Data_Package));
}
