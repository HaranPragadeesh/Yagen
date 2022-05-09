#include <dummy.h>


#include "BluetoothSerial.h" // https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run
`make menuconfig` to and enable it
#endif

#define pwm1 19
#define pwm2 26
#define IN1A 18
#define IN2A 27
#define IN1B 23
#define IN2B 25

char t;
int vspeed = 0;

BluetoothSerial SerialBT;
 
void setup() {
  
  SerialBT.begin("ROVER"); //Bluetooth device name
  ledcAttachPin(pwm1, 1);
  ledcAttachPin(pwm2, 2);
  pinMode(IN1A, OUTPUT);
  pinMode(IN2A, OUTPUT);
  pinMode(IN1B, OUTPUT);
  pinMode(IN2B, OUTPUT);
  Serial.begin(115200);
  ledcSetup(1, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 12000, 8);
  

 
}
 
void loop() {
  if(SerialBT.available()){
    t = SerialBT.read();
    Serial.println(t);
    }
    if (t == '0'){
      vspeed=10;
      }
    else if (t == '1'){
      vspeed=25;
      }
    else if (t == '2'){
      vspeed=50;
      }
    else if (t == '3'){
      vspeed=75;
      }
    else if (t == '4'){
      vspeed=100;
      }  
    else if (t == '5'){
      vspeed=125;
      }  
    else if (t == '6'){
      vspeed=150;
      }  
    else if (t == '7'){
      vspeed=175;
      }  
    else if (t == '8'){
      vspeed=200;
     }  
    else if (t == '9'){
      vspeed=225;
     }  
    else if (t == 'q'){
      vspeed=255;
      }
      
    if(t == 'F'){            //move forward(all motors rotate in forward direction)
      ledcWrite(1 , vspeed);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(IN1A, HIGH);
      digitalWrite(IN1B, LOW);
      ledcWrite(2, vspeed); // RIGHT
      digitalWrite(IN2A, HIGH);
      digitalWrite(IN2B, LOW);
    }
     
    else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
      ledcWrite(1 , vspeed);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(IN1A, LOW);
      digitalWrite(IN1B, HIGH);
      ledcWrite(2, vspeed);  //RIGHT
      digitalWrite(IN2A, LOW);
      digitalWrite(IN2B, HIGH);
    }
    else if(t == 'L'){      //move reverse (all motors rotate in reverse direction)
      ledcWrite(1 , vspeed);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(IN1A, LOW);
      digitalWrite(IN1B, HIGH);
      ledcWrite(2, vspeed);  //RIGHT
      digitalWrite(IN2A, HIGH);
      digitalWrite(IN2B, LOW);
    }
    else if(t == 'R'){            //move forward(all motors rotate in forward direction)
      ledcWrite(1 , vspeed);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(IN1A, HIGH);
      digitalWrite(IN1B, LOW);
      ledcWrite(2, vspeed);  //RIGHT
      digitalWrite(IN2A, LOW);
      digitalWrite(IN2B, HIGH);
    }
    else if(t == 'G'){      //move reverse (all motors rotate in reverse direction)
      
      ledcWrite(2, vspeed);  //RIGHT
      digitalWrite(IN2A, HIGH);
      digitalWrite(IN2B, LOW);
    }
    else if(t == 'I'){            //move forward(all motors rotate in forward direction)
      ledcWrite(1 , vspeed);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(IN1A, HIGH);
      digitalWrite(IN1B, LOW);
    }
    else if(t == 'H'){      //move reverse (all motors rotate in reverse direction)
  
      ledcWrite(2, vspeed);  //RIGHT
      digitalWrite(IN2A, LOW);
      digitalWrite(IN2B, HIGH);
    }
    else if(t == 'J'){      //move reverse (all motors rotate in reverse direction)
      
    
      ledcWrite(1 , vspeed);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(IN1A, LOW);
      digitalWrite(IN1B, HIGH);
      
    }
    
    
    else if(t == 'S'){      //move reverse (all motors rotate in reverse direction)
      digitalWrite(19, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(18, LOW);
      digitalWrite(23, LOW);
      digitalWrite(26, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(27, LOW);
      digitalWrite(25, LOW);
    }
    
    if(t=='W'){
      digitalWrite(2,HIGH);
      }
    else if(t=='w'){
      digitalWrite(2,LOW);
      }
 
}
