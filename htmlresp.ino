#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "God";
const char* password = "byrf5189";
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
int LEDPin = D0;

// PWM 
int IN1 = D0; //0;
int IN2 = D1; //2;

int IN3 = D2; //0;
int IN4 = D3; //2;

void setup(void){
  // set all the motor control pins to outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
    
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1><p><a href=\"Go\"><button>Go</button></a>&nbsp;<a href=\"LEFT\"><button>Left</button></a><a href=\"RIGHT\"><button>Right</button></a>&nbsp;<a href=\"Break\"><button>Break</button></a>&nbsp;</p>";
  //make the LED pin output and initially turned off
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/Go", [](){
    server.send(200, "text/html", page);
    go();
    delay(1000);
  });
  server.on("/LEFT", [](){
    server.send(200, "text/html", page);
    left();
    delay(1000); 
  });
  server.on("/RIGHT", [](){
    server.send(200, "text/html", page);
    right();
    delay(1000); 
  });
  server.on("/Break", [](){
    server.send(200, "text/html", page);
    breaks();
    delay(1000); 
  });
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}

/* Function Control */
void go(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
 }

 void breaks(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
 }
 
  void left(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
  breaks();
 }

 void right(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(500);
  breaks();
 }
