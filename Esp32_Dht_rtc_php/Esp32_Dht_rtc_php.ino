/*
 * @JMTS
 * ESP32 DEVKIT
 * Reloj con fecha y hora más sensor de temperatura y humedad en pantalla LCD I2C 2004
 * Sensor de Temperatura-Humedad DHT22.
 * Hora a traves de servidor NTP basado en el ejemplo SimpleTime de la libreria del ESP32
 * Conexión a base de datos Mysql mediante php por GET para realizar un registro
 * La retroiluminación del LCD se gradua mediante un potenciometro
 * 01/01/2021
 */

#include <WiFi.h>
#include <Time.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
//#include <analogWrite.h>
#include <Wire.h>
#define DHTTYPE DHT22   // Se define el tipo de DHT: DHT 22
#define DHTPIN 27 // Se define el puerto al que conectamos el Sensor DHT: pin digital 27

// Conectamos con la WiFi y sincronizamos el reloj con el servidor NTP
const char* ssid       = "tu WiFi";
const char* password   = "la contraseña de tu WiFi";
const char* ntpServer = "pool.ntp.org";// Servidor NTP para sincronizar el reloj
const long  gmtOffset_sec = 3600; // Selección de la zona horaria GMT+1
const int   daylightOffset_sec = 3600; // Configuración para el horario de verano

// Configuramos la direccion de la base de datos
byte server[] = { 192,168,1,4 }; // Direccion IP del servidor 
WiFiClient client; // Activamos el cliente web

// Iniciamos los contadores para insertar en la base de datos
long previosMillis = 0;
long intervalo = 59000;

LiquidCrystal_I2C lcd (0x27,20,4);
DHT dht(DHTPIN, DHTTYPE);

void fecha(){
  struct tm timeinfo;
  
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
    }
 // Conseguir el día de la semana corto en castellano 
  byte diaSemana = timeinfo.tm_wday;
  char* diaS;
  if (diaSemana ==0){
    diaS="Dom";
    }
  else if (diaSemana ==1){
    diaS="Lun";
    }
  else if (diaSemana ==2){
    diaS="Mar";
    }
  else if (diaSemana ==3){
    diaS="Mie";
    }
  else if (diaSemana ==4){
    diaS="Jue";
    }
  else if (diaSemana ==5){
    diaS="Vie";
    }
  else{
    diaS="Sab";
    }
    
    //Serial.print(diaS);
    //Serial.println(&timeinfo, " %d/%m/%Y %H:%M");
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
  
  delay(1000); // La informaci¢n en el LCD se actualiza cada 1 seg.
}
// Enviar los datos de temperatura, humedad y sensación termica a la base de datos mediate GET en php.
void enviarBD(){
  // Leemos las variables de temperatura, humedad y el cálculo de la senación térmica
  double tp=dht.readTemperature();
  double h=dht.readHumidity();
  double hic=dht.computeHeatIndex(tp,h,false);
  int ub = 2; // Ubicación (1-despacho) (2-salon)
  // Nos conectamos a la base de datos y enviamos las medidas del sensor
  Serial.println("Connecting...");
  if  (client.connect(server, 80)>0) {  // Conexion con el servidor
  // Introducimos las variables por GET 
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
    //Serial.println("Conectado");
  } else {
    Serial.println("Fallo en la conexion");
  }
  if (!client.connected()) {
    Serial.println("Disconnected!");
  }
  // Paramos y limpiamos el cliente
  client.stop();
  client.flush();
  
}

void setup(){
  
  Serial.begin(115200);
  lcd.init(); // Se inicia el lcd
  lcd.backlight(); // Se enciende la retroiluminación del lcd
  lcd.clear(); // Se borra la pantalla del lcd
  dht.begin(); // Se inicia la lectura del dht
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  Serial.println(WiFi.localIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
  //Iniciamos y configuramos el reloj
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  //fecha();
  //disconnect WiFi as it's no longer needed
  //WiFi.disconnect(true);
  //WiFi.mode(WIFI_OFF);
  
}

void loop(){
  // Llamamos a la función para imprimir los datos en el LCD
  mostrarReloj();
  // Llamamos cada minuto a la función para enviar los datos a la base de datos
  unsigned long currentMillis = millis();
  if (currentMillis - previosMillis > intervalo){
    previosMillis = currentMillis;
    enviarBD();
  }
  // Actualizamos el reloj cada segundo
  delay(1000);
  
}
