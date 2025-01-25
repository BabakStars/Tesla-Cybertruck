#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
ESP8266WebServer server (80);
IPAddress local_IP(192,168,1,150);
IPAddress subnet(255,255,255,0);
String A;

void setup() {
  WiFi.disconnect();

  pinMode(D4,OUTPUT);
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D5,OUTPUT);
  digitalWrite(D4,1);   //LEDs
  digitalWrite(D0,0);   //MOTOR1
  digitalWrite(D1,0);   //MOTOR1
  digitalWrite(D2,0);   //MOTOR2
  digitalWrite(D3,0);   //MOTOR2
  analogWrite(D5,0);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP,local_IP,subnet);
  WiFi.softAP("Babak Stars","12345678");
  server.on("/light",handleLight);
  server.on("/move",moved);
  server.begin();
  
  
}

void loop() {
  server.handleClient();
}

void handleLight(){
  String L = server.arg("Li");
  if(L == "1")
  {
    digitalWrite(D4,0);
    
  }
  else
  {
    digitalWrite(D4,1);
  }
  server.send(204,"");
}
void moved(){
  int PWM = server.arg("pwm").toInt();
  String H = server.arg("head");
  analogWrite(D5,PWM);
  if(H == "f")
  {
    digitalWrite(D0,1);
    digitalWrite(D1,0);
    digitalWrite(D2,1);
    digitalWrite(D3,0);
  }
  else if(H == "b")
  {
    digitalWrite(D0,0);
    digitalWrite(D1,1);
    digitalWrite(D2,0);
    digitalWrite(D3,1);
  }
  else if(H == "r")
  {
    digitalWrite(D0,0);
    digitalWrite(D1,1);
    digitalWrite(D2,1);
    digitalWrite(D3,0);
  }
  else if(H == "l")
  {
    digitalWrite(D0,1);
    digitalWrite(D1,0);
    digitalWrite(D2,0);
    digitalWrite(D3,1);
  }
  else
  {
    digitalWrite(D0,0);
    digitalWrite(D1,0);
    digitalWrite(D2,0);
    digitalWrite(D3,0);
  }
  server.send(204,"");
}
