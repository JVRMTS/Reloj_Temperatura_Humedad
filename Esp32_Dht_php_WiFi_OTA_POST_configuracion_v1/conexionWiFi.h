/*
 * Conexión WiFi
 * 24/03/2021
 */
#include "incluir.h"
// Conexión a la WiFi y configuración de fecha y hora
void conectarWiFi()
{
  Serial.println("Arrancando");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Conexion fallida! Reseteando...");
    delay(5000);
    ESP.restart();
  }
  //Iniciamos y configuramos el reloj
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}
