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
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // Dirección MAC asignada a la shield ethernet
IPAddress ip(192, 168, 1, 22); // Dirección IP asignada a la shield ethernet
//IPAddress gatewaw(192, 168 , 1, 1); 
//IPAddress subnet(255, 255, 255, 0);
byte server[] = { 192,168,1,4 }; // Direccion IP del servidor
EthernetClient client; // Iniciamos el cliente ethernet
// Preparamos el contador para actualizar la base de datos se hara cada minuto
long previosMillis = 0;
long intervalo = 59999;

void setup() {
  Serial.begin(115200); // inicamos el puerto serie
  Ethernet.begin(mac, ip); // iniciamos el shield ethernet con su MAC y su IP
  dht.begin(); // se inicia la lectura del dht
  enviarBD(); // al arrancar enviamos los primeros datos
}

void loop() {
  // usamos el contador para enviar los datos a la base de datos
  unsigned long currentMillis = millis();
  if (currentMillis - previosMillis > intervalo){
    previosMillis = currentMillis;
    enviarBD();
  }
  delay(1);
}
// Función para enviar por Get los datos del sensor a la base de datos
void enviarBD(){

   double tp=dht.readTemperature();
   double h=dht.readHumidity();
   double hic=dht.computeHeatIndex(tp,h,false);
   int ub = 1; // Ubicación (1-despacho) (2-salón)
  
   Serial.println("Connecting...");
  if  (client.connect(server, 80)>0) {  // Conexion con el servidor
    client.print (F("GET /sensores/insertar.php?t=")); // Enviamos los datos por GET
    client.print(tp);
    client.print (F("&h="));
    client.print(h);
    client.print (F("&st="));
    client.print(hic);
    client.print (F("&ub="));
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
