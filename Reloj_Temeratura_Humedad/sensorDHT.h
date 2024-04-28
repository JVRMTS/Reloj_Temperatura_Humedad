/*
 / Configuración y función para la toma de datos de un sensor DHT, esta probado con DHT11 y DHT22 en Esp32 Dev Module
 / creado por JMTS
 / EL 27/12/2023
*/

#include <DHT.h>

#define DHTTYPE DHT22
#define DHTPIN 27     // Se define el puerto al que conectamos el Sensor DHT: pin digital 27

DHT dht(DHTPIN, DHTTYPE); // Objeto DHT

double h;
String Hum;
double t;
String Temp;
char g;
char p;
double hic;
String TeR;
String t1;
String t2;
String t3;

void temperatura(){
   h = dht.readHumidity();                  //Leemos la humedad del sensor
   Hum = String(h, 1);                      // La convertimos a un String
   t = dht.readTemperature();               // Leemos la temperatura del sensor
   Temp = String(t, 2);                     // La convertimos a un String
   g = (char)223;                          // Generamos el simbolo de grados centigrados para mostrar en la TFT
   p = '%';                                 // Simbolo de % para mostrar por el LCD
   hic = dht.computeHeatIndex(t, h, false); // Calculamos la sensación térmica
   TeR = String(hic, 2);                    // La convertimos a un String
   t1=("Tem:" + Temp + g);                  // Se crea la cadena de la temperatura
   t2=("Hum:" + Hum + p);                   // Se crea la cadena de la humedad
   t3=("Sen.Ter.:" + TeR + g);             // Se crea la cadena de la sensacion termica
}  
