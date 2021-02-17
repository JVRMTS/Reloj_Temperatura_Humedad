/*
 * @JMTS
 * Arduino nano
 * Reloj con fecha y hora más sensor de temperatura y humedad en pantalla lcd I2C 2004
 * Sensor de Temperatura-Humedad DHT22.
 * DS3231 y libreria RTClib.h
 * Pantalla LCD 2040 I2C.
 * 01/01/2021
 */
 
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include "DHT.h"
#define DHTTYPE DHT22   // Se define el tipo de DHT: DHT 22
#define DHTPIN 5 // Se define el puerto al que conectamos el Sensor: pin digital 5.
RTC_DS3231 RTC ;
LiquidCrystal_I2C lcd (0x27,20,4); // 0x27 Se ha definido la dirección del bus de la pantalla LCD y el tamaño de esta.
DHT dht(DHTPIN, DHTTYPE); // Se define el objeto dht

void setup() {
  Serial.begin(115200);
  RTC.begin(); // Inicia la comunicaci¢n con el RTC

   // Comentar una vez establecida la hora
  //RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora
  //el anterior se usa solo en la configuracion inicial

  lcd.init(); // Se inicia el lcd
  lcd.backlight(); // Se enciende la retroiluminación del lcd
  lcd.clear(); // Se borra la pantalla del lcd
  dht.begin(); // se inicia la lectura del dht
}

void loop() {
  mostrarReloj();// Llamamos a la función para mostrar los datos en el LCD
  delay(1000);// Esperamos un segundo para actualizar la información
}
// Función para poner en castellano el día de la semana en el calendario
char* dSem(){
DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC  
byte diaSemana = now.dayOfTheWeek();
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
  return  diaS;
}
// Función para mostrar los datos del calendario, temperatura, humedad y sensación térmica en la pantalla LCD2004
void mostrarReloj(){

  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
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
  lcd.print(dSem());
  sprintf(buffer, " %02d/%02d/%2d %02d:%02d", now.day(), now.month(), now.year(), now.hour(), now.minute()); // Se crea la primera linea desde el buffer y se le da formato
  lcd.print(buffer);
  lcd.setCursor(0,1); // Se situa el cursor en la segunda linea del lcd
  lcd.print(t1); // Se imprime por lcd la temperatura
  lcd.setCursor(4,2); // Se situa el cursor en la tercera linea en la posición 4 para que cuadre
  lcd.print(t2); // Se imprime la humedad
  lcd.setCursor(0,3); // Se situa el cursor en la cuarta linea
  lcd.print(t3); // Se imprime la sensacion termica
}
