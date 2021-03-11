/*
 * @JMTS
 * Arduino nano
 * AZDelivery Ethernet Shield para Nano V3 que utiliza la libreria UIPEthernet
 * Sensor de Temperatura-Humedad DHT22.
 * Conexión a base de datos Mysql.
 * 01/01/2021
 */
 
//#include <wiring.h>
#include <TimeLib.h>
#include <UIPEthernet.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTTYPE DHT22   // Se define el tipo de DHT: DHT 22
#define DHTPIN 5 // Se define el puerto al que conectamos el Sensor: pin digital 5.


LiquidCrystal_I2C lcd (0x27,20,4); // 0x27 Se ha definido la dirección del bus de la pantalla LCD y el tamaño de esta.
DHT dht(DHTPIN, DHTTYPE); // Se define el objeto dht

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // Dirección MAC asignada a la shield ethernet
Ethernet.begin(mac);
IPAddress ip(192, 168, 1, 22); // Dirección IP asignada a la shield ethernet
//IPAddress gatewaw(192, 168 , 1, 1); 
//IPAddress subnt(255, 255, 255, 0);
//IPAddress DNS(8,8,8,8);
byte server[] = { 192,168,1,4 }; // Direccion IP del servidor
EthernetClient client; // Iniciamos el cliente ethernet
EthernetUDP Udp;
unsigned int localPort = 8888;
const char* ntpServer = "pool.ntp.org";// Servidor NTP para sincronizar el reloj
const long  gmtOffset_sec = 3600; // Selección de la zona horaria GMT+1
const int   daylightOffset_sec = 3600; // Configuración para el horario de verano

/// Iniciamos los contadores para insertar en la base de datos
long previosMillis = 0;
long intervalo_0= 60000;
long intervalo_1 = 1000;

void fecha(){
  struct tm timeinfo;
  
  if(!getLocalTime(&timeinfo)){
    Serial.println("Fallo al obtener fecha y hora");
    return;
    }
 // Conseguir el día de la semana corto en castellano 
    String diaSemana[] = {"Dom","Lun","Mar","Mie","Jue","Vie","Sab"};
    String diaS = diaSemana[timeinfo.tm_wday];
    
    lcd.print(diaS);
    lcd.print(&timeinfo, " %d/%m/%Y %H:%M");
}

// Mostrar el reloj en la pantalla del LCD
void mostrarReloj(){

  double h=dht.readHumidity(); //Leemos la humedad del sensor
  String Hum= String(h,2); // La convertimos a un String
  double t=dht.readTemperature(); // Leemos la temperatura del sensor
  String Temp = String(t,2);// La convertimos a un String
  char g=(char)223; // Generamos el simbolo de grados centigrados para mostrar por LCD
  char p='%'; // Simbolo de % para mostrar por el LCD
  double hic=dht.computeHeatIndex(t,h,false); // Calculamos la sensación térmica
  String TeR= String(hic,2); // La convertimos a un String
  String t1("Temperatura: "+Temp+g+"C"); // Se crea la cadena de la temperatura
  String t2("Humedad: "+Hum+" "+p); // Se crea la cadena de la humedad
  String t3("Sen.Termic.: "+TeR+g+"C"); // Se crea la cadena de la sensacion termica
  
  lcd.setCursor(0,0); // Situamos el cursor en la primera linea del LCD
  fecha(); // Se imprime el día de la semana, fecha y hora en el LCD
  lcd.setCursor(0,1); // Se situa el cursor en la segunda linea del LCD
  lcd.print(t1); // Se imprime la temperatura en el LCD
  lcd.setCursor(4,2); // Se situa el cursor en la tercera linea en la posición 4 para que cuadre
  lcd.print(t2); // Se imprime la humedad en el LCD
  lcd.setCursor(0,3); // Se situa el cursor en la cuarta linea
  lcd.print(t3); // Se imprime la sensacion termica en el LCD
}

void setup() {
  Serial.begin(9600); // inicamos el puerto serie
  Ethernet.begin(mac, ip); // iniciamos el shield ethernet con su MAC y su IP
  dht.begin(); // se inicia la lectura del dht
  enviarBD(); // al arrancar enviamos los primeros datos
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
