/*
 * Funciones para mostrar en el LCD los datos de reloj y sensor DHT
 * 24/03/2021
 */
#include "incluir.h"

time_t local, utc;
LiquidCrystal_I2C lcd(dir, col, fil); // Creamos el objeto LCD y lo configuramos con su direccion I2C y el tipo de pantalla (en este caso 2004)
DHT dht(DHTPIN, DHTTYPE);             // Creamos el objeto DHT y lo configuramos cno su pin y el tipo

// Función fecha para mostrarla en el LCD
void fecha()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Fallo al obtener fecha y hora");
    return;
  }
  // Conseguir el día de la semana corto en castellano
  String diaSemana[] = {"Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"};
  String diaS = diaSemana[timeinfo.tm_wday];
  // Conseguir el mes en castellano
  String meses[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
  String mes = meses[timeinfo.tm_mon];
  // Mostrar la fecha y hora en el LCD
  lcd.setCursor(7, 0);
  lcd.print(&timeinfo, "%H:%M");
  lcd.setCursor(2, 1); // Situamos el cursor en la primera linea del LCD
  lcd.print(diaS);
  lcd.setCursor(5, 1);
  lcd.print(&timeinfo, " %d ");
  lcd.print(mes);
  lcd.print(&timeinfo, " %Y");
}

// Función mostrarTemperatura para imprimirlaen el LCD
void mostrarTemperatura()
{
  double h = dht.readHumidity();                  //Leemos la humedad del sensor
  String Hum = String(h, 1);                      // La convertimos a un String
  double t = dht.readTemperature();               // Leemos la temperatura del sensor
  String Temp = String(t, 2);                     // La convertimos a un String
  char g = (char)223;                             // Generamos el simbolo de grados centigrados para mostrar por LCD
  char p = '%';                                   // Simbolo de % para mostrar por el LCD
  double hic = dht.computeHeatIndex(t, h, false); // Calculamos la sensación térmica
  String TeR = String(hic, 2);                    // La convertimos a un String
  String t1("Tem:" + Temp + g);                   // Se crea la cadena de la temperatura
  String t2("Hum:" + Hum + p);                    // Se crea la cadena de la humedad
  String t3("Sen.Ter.: " + TeR + g);              // Se crea la cadena de la sensacion termica

  fecha();              // Se imprime el día de la semana, fecha y hora en el LCD
  lcd.setCursor(0, 2);  // Se situa el cursor en la segunda linea del LCD
  lcd.print(t1);        // Se imprime la temperatura en el LCD
  lcd.setCursor(11, 2); // Se situa el cursor en la tercera linea en la posición 4 para que cuadre
  lcd.print(t2);        // Se imprime la humedad en el LCD
  lcd.setCursor(2, 3);  // Se situa el cursor en la cuarta linea
  lcd.print(t3);        // Se imprime la sensacion termica en el LCD
}
