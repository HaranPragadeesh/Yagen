
#include <QTRSensors.h>

//Line Sensor Array
QTRSensors line;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

void setup() {
  // put your setup code here, to run once:
  line.setTypeAnalog();
  line.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, SensorCount);
  line.setEmitterPin(2);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  line.read(sensorValues);
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  delay(250);
  
}
