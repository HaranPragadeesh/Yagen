int pressure = A0;
float sens;
void setup(){
  pinMode(pressure,INPUT);
  Serial.begin(9600);
  }
void loop(){
  sens = (analogRead(pressure)*3.3)/1024;
  Serial.println(sens);
  }
