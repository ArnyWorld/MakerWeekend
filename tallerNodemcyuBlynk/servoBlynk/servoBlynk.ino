#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;

const char auth[]="COPIAR TOKEN EMAIL";
const char* ssid ="NOMBRE RED WIFI";//red WiFi
const char* pass="CONTRASEÑA RED WIFI";//contraseña de la red WiFi

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass);
  servo.attach(D2);
  
}
void loop() {
 Blynk.run();
}

BLYNK_WRITE(V3){
  servo.write(param.asInt());
}







