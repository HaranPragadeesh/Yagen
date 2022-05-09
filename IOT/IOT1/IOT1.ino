#include <ESP8266WiFi.h>

//DECLARATIONS

//WIFI
const char* ssid ="Satz";
const char* pass ="12345678";

//RELAYS
int R1 = 12;
int R2 = 14;

//Web Server
WiFiServer server(80); //Communicating via PORT 80

void setup() {
  
  Serial.begin(115200);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);

  //CONNECTING TO WiFi
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");

  //ESTABLISHING SERVER
  server.begin();
  Serial.println("Server established !");

  //Getting the IP details and Web Server link
  Serial.println("Current IP Address: ");
  Serial.print(WiFi.localIP());
  Serial.println("Enter the following address in your browser: ");
  Serial.print("https://");
  Serial.print(WiFi.localIP());
  Serial.print("/");
}

void loop() {
  WiFiClient client = server.available();
  if(!client){
    return;
  }
  Serial.println("Waiting for new client");

  while(!client.available()){
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int val1;
  int val2;
  if (request.indexOf("/RELAY1=ON") != -1){
    digitalWrite(R1, HIGH);
    val1 = HIGH;
  } else if(request.indexOf("/RELAY2=ON") != -1){
    digitalWrite(R2, HIGH);
    val2 = HIGH;
  }else if(request.indexOf("/RELAY1=OFF") != -1){
    digitalWrite(R1, LOW);
    val1 = LOW;
  }else if(request.indexOf("/RELAY2=OFF") != -1){
    digitalWrite(R2, LOW);
    val2 = LOW;
  }

  //-------------------HTML PAGE CODE------------------------//

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("RELAY 1 State: ");
  if (val1 == HIGH){
    client.print("ON");
  }else{
    client.print("OFF");
  }
  client.println("<br>");
  client.println("RELAY 2 State: ");
  if (val2 == HIGH){
    client.print("ON");
  }else{
    client.print("OFF");
  }
  client.println("<br><br>");
  client.println("<a href =\"/RELAY1=ON\"\"><button>ON</button></a>");
  client.println("<a href =\"/RELAY1=OFF\"\"><button>OFF</button></a><br/>");
  client.println("<br><br>");
  client.println("<a href =\"/RELAY2=ON\"\"><button>ON</button></a>");
  client.println("<a href =\"/RELAY2=OFF\"\"><button>OFF</button></a><br/>");
  client.println("</html>");
} 
