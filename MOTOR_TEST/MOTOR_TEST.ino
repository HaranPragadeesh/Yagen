#define RM1 3 
#define RM2 4
#define LM1 7
#define LM2 8

void setup() {
  // put your setup code here, to run once:
  pinMode(RM1,OUTPUT);
  pinMode(RM2,OUTPUT);
  pinMode(LM1,OUTPUT);
  pinMode(LM2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RM2,LOW);
  digitalWrite(RM1,HIGH);

}
