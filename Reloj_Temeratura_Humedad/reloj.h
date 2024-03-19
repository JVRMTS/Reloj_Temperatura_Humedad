/*
 * Funciones para mostrar en el LCD los datos de reloj y sensor DHT
 * 17/03/2024
 * @JMTS - www.jmts.es
 */

#include <Time.h>

void setTimezone(String timezone){
  //Serial.printf("Setting Timezone to %s\n",timezone.c_str());
  setenv("TZ",timezone.c_str(),1);
  tzset();
}

void configReloj(){
  // Confinguramos el servidor NTP
  const char* ntpServer = "pool.ntp.org";                // Servidor NTP para sincronizar el reloj
  const long gmtOffset_sec = 3600;                       // Selección de la zona horaria GMT+1
  const int daylightOffset_sec = 3600;                   // Configuración para el horario de verano
  String timezone = "CET-1CEST,M3.5.0,M10.5.0/3";        // TimeZone regla para Europa/Roma incluyendo el horario de verano
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  setTimezone(timezone);
}

// Declaramos las variables que mostraremos en pantalla para que estén disponibles
String diaS;
int dia;
String mes;
int ano;
char horMin[6];

void fecha(){
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)){
    //Serial.println("Fallo al obtener fecha y hora");
    return;
  }
  // Conseguir el día de la semana corto en castellano
  char *diaSemana[]= {"Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"};
  diaS = diaSemana[timeinfo.tm_wday];
  // Conseguir el mes en castellano
  char *meses[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
  // Asignar valor a las variables que mostraremos en pantalla
  mes = meses[timeinfo.tm_mon];
  ano = timeinfo.tm_year + 1900;
  dia = timeinfo.tm_mday;
  // Damos formato a horas y minutos para mostrorlos en el LCD   
  sprintf(horMin, "%02d:%02d",timeinfo.tm_hour, timeinfo.tm_min ); // Damos formato a horas y minutos
  String asString(horMin);                                         // Convertimos las horas y minutos en un String para poder mostrarlas en pantalla
}
