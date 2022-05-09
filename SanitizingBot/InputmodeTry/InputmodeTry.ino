char val;
int mode;

void setup() {

  Serial.begin(9600);
  Serial.println("INITIATING..."); 
  
}

void loop() {
  while (Serial.available() == 0){}
   mode = Serial.parseInt();
    while (mode == 1){
      Serial.println ("Mode: ");
      Serial.print (mode);
      while (Serial.available() ==0){}
      val = Serial.read(); 
        Serial.print ("Val: ");
        Serial.println (val);
        if (val == 'e'){
            mode = 0;
            val = 'k';
            Serial.println ("Mode: ");
            Serial.print (mode);
            break;
            Serial.println(mode);
        }
     }
     while (mode == 0){
      Serial. println("Following the line");
        val = Serial.read();
        if (val == 'e'){
          mode = 1;
          Serial.println ("Mode: ");
          Serial.print (mode);
          break;
          Serial.println (mode);
        }         
     }
  delay(1000);
}
