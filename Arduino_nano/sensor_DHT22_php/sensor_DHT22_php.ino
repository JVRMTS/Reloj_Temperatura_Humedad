/*
 * @JMTS
 * Arduino nano
 * AZDelivery Ethernet Shield para Nano V3 que utiliza la libreria UIPEthernet
 * Sensor de Temperatura-Humedad DHT22.
 * Conexión a base de datos Mysql.
 * 03/03/2021
 */
 
#include <Wire.h>
#include <UIPEthernet.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

#define DHTTYPE DHT22   // Se define el tipo de DHT: DHT 22
#define DHTPIN 5 // Se define el puerto al que conectamos el Sensor: pin digital 5.

RTC_DS3231 RTC ;
LiquidCrystal_I2C lcd (0x27,20,4); // 0x27 Se ha definido la dirección del bus de la pantalla LCD y el tamaño de esta.
DHT dht(DHTPIN, DHTTYPE); // Se define el objeto dht
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // Dirección MAC asignada a la shield ethernet
IPAddress ip(192, 168, 1, 22); // Dirección IP asignada a la shield ethernet
//IPAddress gatewaw(192, 168 , 1, 1); 
//IPAddress subnet(255, 255, 255, 0);
byte server[] = { 192,168,1,4 }; // Direccion IP del servidor
EthernetClient client; // Iniciamos el cliente ethernet
// Preparamos el contador para actualizar la base de datos se hara cada minuto
long previosMillis = 0;
long intervalo_0= 59999;
long intervalo_1 = 999;

void setup() {
  Serial.begin(115200); // inicamos el puerto serie
  Ethernet.begin(mac, ip); // iniciamos el shield ethernet con su MAC y su IP
  dht.begin(); // se inicia la lectura del dht
  //enviarBD(); // al arrancar enviamos los primeros datos
  RTC.begin(); // Inicia la comunicaci¢n con el RTC

   // Comentar una vez establecida la hora
  //RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora
  //el anterior se usa solo en la configuracion inicial

  lcd.init(); // Se inicia el lcd
  lcd.backlight(); // Se enciende la retroiluminación del lcd
  lcd.clear(); // Se borra la pantalla del lcd
}

void loop() {
  // Llamamos a la función para imprimir los datos en el LCD cada segundo
  unsigned long currentMillis = millis();
  if (currentMillis - previosMillis > intervalo_1){
    mostrarReloj();
  }
  // Llamamos cada minuto a la función para enviar los datos a la base de datos cada minuto
  if (currentMillis - previosMillis > intervalo_0){
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
   int ub = 3; // Ubicación (1-despacho) (2-salón)
  
   Serial.println("Connecting...");
  if  (client.connect(server, 80)>0) {  // Conexion con el servidor
    client.print (F("GET /sensores/iot.php?t=")); // Enviamos los datos por GET
    client.print(tp);
    client.print (F("&h="));
    client.print(h);
    client.print (F("&st="));
    client.print(hic);
    client.print (F("&ub="));
    client.print(ub);
    client.println (F(" HTTP/1.0"));
    client.println (F("User-Agent: Arduino 1.0"));
    client.println();
    Serial.println (F("Conectado"));
    } else {
    Serial.println (F("Fallo en la conexion"));
  }
  if (!client.connected()) {
    Serial.println (F("Disconnected!"));
  }
  client.stop();
  client.flush();
}
void mostrarReloj(){

  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC  
// Conseguir el día de la semana corto en castellano 
  String diaSemana[] = {"Dom","Lun","Mar","Mie","Jue","Vie","Sab"};
  String dSem = diaSemana[now.dayOfTheWeek()];
  char buffer[18]; // Se crea el buffer y se define su longitud
  double h=dht.readHumidity();
  String Hum= String(h,2);
  double tp=dht.readTemperature();
  String Temp = String(tp,2);
  char g=(char)223;
  char p='%';
  double hic=dht.computeHeatIndex(tp,h,false);
  String TeR= String(hic,2);
  String t1("Temperatura: "+Temp+g+"C"); // Se crea la cadena de la temperatura
  String t2("Humedad: "+Hum+" "+p); // Se crea la cadena de la humedad
  String t3("Sen.Termic.: "+TeR+g+"C"); // Se crea la cadena de la sensacion termica

  lcd.setCursor(0,0); // Se situa el cursor en la primera linea del lcd
  lcd.print(dSem);
  sprintf(buffer, " %02d/%02d/%2d %02d:%02d", now.day(), now.month(), now.year(), now.hour(), now.minute()); // Se crea la primera linea desde el buffer y se le da formato
  lcd.print(buffer);
  lcd.setCursor(0,1); // Se situa el cursor en la segunda linea del lcd
  lcd.print(t1); // Se imprime por lcd la temperatura
  lcd.setCursor(4,2); // Se situa el cursor en la tercera linea en la posición 4 para que cuadre
  lcd.print(t2); // Se imprime la humedad
  lcd.setCursor(0,3); // Se situa el cursor en la cuarta linea
  lcd.print(t3); // Se imprime la sensacion termica
}
