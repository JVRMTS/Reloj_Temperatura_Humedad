/*
 * Funciones para mostrar en el LCD los datos de reloj y sensor DHT
 * 27/12/2023
 */

#include <Time.h>

// Confinguramos el servidor NTP
const char* ntpServer = "pool.ntp.org"; // Servidor NTP para sincronizar el reloj
const long gmtOffset_sec = 3600;        // Selección de la zona horaria GMT+1
const int daylightOffset_sec = 0;       // Configuración para el horario de verano

// Declaramos las variables que mostraremos en pantalla para que estén disponibles
int8_t hor;
int8_t minu;
String diaS;
int8_t dia;
String mes;
int16_t ano;
char horMin[7];

// Función fecha para mostrarla en el LCD
void fecha(){
   configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
   struct tm timeinfo;
   if (!getLocalTime(&timeinfo))
   {
      Serial.println("Fallo al obtener fecha y hora");
      return;
   }
   // Conseguir el día de la semana corto en castellano
   char *diaSemana[] = {"Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"};
   diaS = diaSemana[timeinfo.tm_wday];
   // Conseguir el mes en castellano
   String meses[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
   // Asignar valor a las variables que mostraremos en pantalla
   mes = meses[timeinfo.tm_mon];
   ano = timeinfo.tm_year + 1900;
   dia = timeinfo.tm_mday;
   sprintf(horMin, "%02d:%02d",timeinfo.tm_hour, timeinfo.tm_min ); // Damos formato a horas y minutos para mostrorlos en la tft
 }
