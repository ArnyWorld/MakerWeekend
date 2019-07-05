#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#define DHTPIN D1 //pin donde conectamos el sensor
#define DHTTYPE DHT22 // iniciamos el dht11
DHT dht(DHTPIN, DHTTYPE);

const char auth[]="COPIAR TOKEN DEL EMAIL";
const char* ssid ="NOMBRE DE LA RED WIFI";//red WiFi
const char* pass="CONTRASEÑA DE LA RED WIFI";//contraseña de la red WiFi

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(auth,ssid,pass);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 // lectura del sensor de temperatura y humedad
 float t=dht.readTemperature();
 float h=dht.readHumidity();

 Blynk.virtualWrite(V1,t);
 Blynk.virtualWrite(V2,h);

 Serial.println("Temperatura : ");
 Serial.println(t);
  Serial.println("Humedad: ");
 Serial.println(h);

 
}



