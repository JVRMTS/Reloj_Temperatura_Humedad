/*
 * @JMTS
 * Arduino nano
 * AZDelivery Ethernet Shield para Nano V3 que utiliza la libreria UIPEthernet
 * Sensor de Temperatura-Humedad DHT22.
 * Conexión a base de datos Mysql.
 * 01/01/2021
 */
 
#include <Wire.h>
#include <UIPEthernet.h>
#include "DHT.h"

#define DHTTYPE DHT22   // Se define el tipo de DHT: DHT 22
#define DHTPIN 5 // Se define el puerto al que conectamos el Sensor: pin digital 5.


DHT dht(DHTPIN, DHTTYPE); // Se define el objeto dht
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 22);
//IPAddress gatewaw(192, 168 , 1, 1);
//IPAddress subnet(255, 255, 255, 0);
byte server[] = { 192,168,1,4 }; // Direccion IP del servidor
EthernetClient client; 
long previosMillis = 0;
long intervalo = 59999;

void setup() {
  Serial.begin(115200);
  Ethernet.begin(mac, ip);
  dht.begin(); // se inicia la lectura del dht
  enviarBD();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previosMillis > intervalo){
    previosMillis = currentMillis;
    enviarBD();
  }
  delay(1);
}

void enviarBD(){

   double tp=dht.readTemperature();
   double h=dht.readHumidity();
   double hic=dht.computeHeatIndex(tp,h,false);
   int ub = 1; // Ubicación (1-despacho) (2-salÓn)
  
   Serial.println("Connecting...");
  if  (client.connect(server, 80)>0) {  // Conexion con el servidor
    client.print F(("GET /sensores/iot.php?t=")); // Enviamos los datos por GET
    client.print(tp);
    client.print F(("&h="));
    client.print(h);
    client.print F(("&st="));
    client.print(hic);
    client.print F(("&ub="));
    client.print(ub);
    client.println(F(" HTTP/1.0"));
    client.println(F("User-Agent: Arduino 1.0"));
    client.println();
    Serial.println("Conectado");
    } else {
    Serial.println("Fallo en la conexion");
  }
  if (!client.connected()) {
    Serial.println("Disconnected!");
  }
  client.stop();
  client.flush();
}
