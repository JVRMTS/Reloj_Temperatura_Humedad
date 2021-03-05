/*
 * @JMTS
 * ESP32 DEVKIT
 * Reloj con fecha y hora más sensor de temperatura y humedad en pantalla LCD I2C 2004
 * Sensor de Temperatura-Humedad DHT22.
 * Hora a traves de servidor NTP basado en el ejemplo SimpleTime de la libreria del ESP32
 * Conexión a base de datos Mysql mediante php por GET para realizar un registro
 * La retroiluminación del LCD se gradua mediante LDR
 * 20/02/2021
 */

#include <WiFi.h>
#include <Time.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Wire.h>
#include <analogWrite.h>
#define DHTTYPE DHT22   // Se define el tipo de DHT: DHT 22
#define DHTPIN 27 // Se define el puerto al que conectamos el Sensor DHT: pin digital 27

// Conectamos con la WiFi y sincronizamos el reloj con el servidor NTP
const char* ssid       = "****";
const char* password   = "****";
const char* ntpServer = "pool.ntp.org";// Servidor NTP para sincronizar el reloj
const long  gmtOffset_sec = 3600; // Selección de la zona horaria GMT+1
const int   daylightOffset_sec = 3600; // Configuración para el horario de verano

// Configuramos la direccion de la base de datos
byte server[] = { 192,168,1,4 }; // Direccion IP del servidor 
WiFiClient client; // Activamos el cliente web

// Iniciamos los contadores para insertar en la base de datos
long previosMillis = 0;
long intervalo_0= 60000;
long intervalo_1 = 1000;

const int pinLCD = 18;
const int pinLDR = 32;
unsigned int valorLDR;
unsigned int valorLCD;

LiquidCrystal_I2C lcd (0x27,20,4);
DHT dht(DHTPIN, DHTTYPE);

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

// Enviar los datos de temperatura, humedad y sensación termica a la base de datos mediate GET en php.
void enviarBD(){
  // Leemos las variables de temperatura, humedad y el cálculo de la senación térmica
  double tp=dht.readTemperature();
  double h=dht.readHumidity();
  double hic=dht.computeHeatIndex(tp,h,false);
  int ub = 1; // Ubicación (1-despacho) (2-salon) (3-pruebas)
  // Nos conectamos a la base de datos y enviamos las medidas del sensor
  Serial.println("Conectando...");
  if  (client.connect(server, 80)>0) {  // Conexion con el servidor
  // Introducimos las variables por GET 
    client.print F(("GET /sensores/insertar.php?t=")); // Enviamos los datos por GET
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
  } else {
    Serial.println("Fallo en la conexion");
  }
  if (!client.connected()) {
    Serial.println("Desconectado");
  }
  // Paramos y limpiamos el cliente
  client.stop();
  client.flush();
  Serial.println("Desconectado");
}

void conectarWiFi(){
  Serial.println("Arrancando");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Conexion fallida! Reseteando...");
    delay(5000);
    ESP.restart();
  }
  //Iniciamos y configuramos el reloj
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void setup(){
  
  Serial.begin(115200);
  lcd.init(); // Se inicia el lcd
  lcd.backlight(); // Se enciende la retroiluminación del lcd
  lcd.clear(); // Se borra la pantalla del lcd
  dht.begin(); // Se inicia la lectura del dht
  pinMode(pinLCD,OUTPUT);
   //Llamamos a la función para conectar a la wifi
  conectarWiFi();
}

void loop(){
  //Si se ha perdido la conexión wifi llamamos a la función para conectar de nuevo y configuramos fecha y hora
  if (WiFi.isConnected() == false){
    conectarWiFi();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    }
    
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
  valorLDR = analogRead(pinLDR); // Leemos la variable del LDR
  if (valorLDR > 10){
    valorLCD = valorLDR/8;// Le damos el valor a la salida del LCD
    }else{
    valorLCD = 10; // esto es para que nunca se apaque del todo el LCD
    }
  analogWrite(pinLCD,valorLCD); // Escribimos en el pinLCD el valor
  }
