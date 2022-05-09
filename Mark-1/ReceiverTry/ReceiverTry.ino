#include <SPI.h>
#include <nRF24L01.h>
#include<RF24.h>

RF24 radio(10,9);
const byte address[6] = "00001";

unsigned long lastReceivedTime = 0;
unsigned long currentTime = 0;

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
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  resetData();
}

void loop() {

  if(radio.available()){
    radio.read(&data, sizeof(Data_Package));
    lastReceiveTime = millis();
  }
  currentTime = millis();

  if(currentTime - lastReceivedTime > 1000){resetData();}
 
}

void resetData(){

  data.button1 = 1;
  data.button2 = 1;
  data.button3 = 1;
  data.button4 = 1;
  data.button5 = 1;
  data.button6 = 1;
  data.button7 = 1;
  data.button8 = 1;
  
}
