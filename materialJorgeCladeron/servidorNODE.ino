#include <ESP8266WiFi.h>

#define led 16 // definimos el pin para el led
const char* ssid = "JcR";//nombre de red wifi
const char* password= "70536951calderon";//contraseña de red WiFi

WiFiServer server(80);//puerto por el que se conecta al servidor del nodemcu
int selector;


void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200); //velocidad de comunicacion optima para el node mcu
  Serial.println();
  Serial.println("conectando a...");
  Serial.println(ssid);
  WiFi.begin(ssid,password); //inicia la conexion a la red WiFi
  //verificacion de que se conecto a la red WiFi
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("");
  Serial.println("WiFi conectado");
  Serial.println("Direccion ip: ");
  Serial.println(WiFi.localIP());// direccion IP del node mcu
  //inicializamos el servidor
  server.begin();
  Serial.println("servidor iniciado");
}

void loop() {   
 
  //comprobamos si hay un cliente disponible
  //NOTA: si existe un cliente se realiza una operacion caso contrario no
  WiFiClient cliente= server.available();
  if(!cliente){
    return;
  }
  //nueva peticion del cliente
 Serial.println("nuevo cliente");
 while(!cliente.available()){
  delay(1);
 }
 
   // Leo la primera linea de la petición del cliente
  String request = cliente.readStringUntil('\r'); // Leo hasta retorno de carro
  Serial.println(request); //Imprimo la petición
  cliente.flush(); //Limpio el buffer
 
  // Interpreta lo que ha recibido
  if (request.indexOf("/LED=ON") != -1)  {
     digitalWrite(led, HIGH);
     }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(led, LOW);
  }
 
   // Devuelvo la respuesta al cliente -> Todo ha ido bien, el mensaje ha sido interpretado correctamente
  cliente.println("HTTP/1.1 200 OK");
  cliente.println("Content-Type: text/html");
  cliente.println(""); //  do not forget this one
  
  // A partir de aquí se crea la página HTML, el cliente.println es el formato que maneja el node mcu para interpretar el codigo html
  cliente.println("<!DOCTYPE HTML>"); 
  cliente.println("<html>");
   cliente.println("<center>");
 
  // Los botones con enlace
  cliente.println("<br><br>");
  cliente.println("LED  ");
  cliente.println("<a href=\"/LED=ON\"\"><button>Encender </button></a>"); 
  cliente.println("<a href=\"/LED=OFF\"\"><button>Apagar </button></a><br />");
  cliente.println("<br><br>");
  cliente.println("</center>");   
  cliente.println("</html>");
 
  delay(1);
  Serial.println("Cliente desconectado"); // Nos desconectamos del cliente
  Serial.println("");
}


 
 


