/*
 * 16/06/2021
*/
#include <ArduinoOTA.h>
void actualizacionOTA(){

// ACTUALIZACIONES VIA OTA
// Establecemos el nombre del dispositivo por la ubicación
ArduinoOTA.setHostname(ubicacion());
// Establecemos una contraseña para autentificar la actualización
ArduinoOTA.setPassword(passwordOTA);

ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTA: si actualiza SPIFFS, este sería el lugar para desmontar SPIFFS usando SPIFFS.end ()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR)
        Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR)
        Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR)
        Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR)
        Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR)
        Serial.println("End Failed");
    });

ArduinoOTA.begin();

Serial.println("Ready");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
}
