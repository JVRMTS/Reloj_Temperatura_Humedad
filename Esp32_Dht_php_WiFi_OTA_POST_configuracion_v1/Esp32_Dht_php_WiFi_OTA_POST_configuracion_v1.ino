/*
 * @JMTS
 * ESP32 DEVKIT
 * Reloj con fecha y hora más sensor de temperatura y humedad en pantalla LCD I2C 2004
 * Sensor de Temperatura-Humedad DHT22.
 * Hora a traves de servidor NTP basado en el ejemplo SimpleTime de la libreria del ESP32
 * Conexión a base de datos Mysql mediante php con el método POST para realizar un registro
 * La retroiluminación del LCD se gradua mediante LDR
 * Actualización del frimware via OTA con contraseña basado en el ejemplo ArduinoOTA
 * 16/10/2021
 */
#include "configuracion.h"
#include "reloj.h"
#include "conexionWiFi.h"
#include "baseDatos.h"
#include "ota.h"
#include "ldr.h"


// Iniciamos los contadores para insertar en la base de datos y actualizar el reloj
unsigned long previosMillis_0;
unsigned long previosMillis_1;
unsigned long intervalo_0 = 60000;
unsigned long intervalo_1 = 1000;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Turn onboard LED OFF
  Serial.begin(115200); // Se inicia el puerto serie y la velocidad
  lcd.init();           // Se inicia el lcd
  lcd.backlight();      // Se enciende la retroiluminación del lcd
  lcd.clear();          // Se borra la pantalla del lcd
  dht.begin();          // Se inicia la lectura del dht

  // Conexion a la wifi y sincronización del reloj NTP
  conectarWiFi();

  // Configuramos la actualización via OTA
  actualizacionOTA();
}
  void loop()
  {
    //Si se ha perdido la conexión wifi llamamos a la función para conectar de nuevo y configuramos fecha y hora
    if (WiFi.isConnected() == false){
      conectarWiFi();
      }

    // Llamamos a la función para imprimir los datos en el LCD cada segundo
    unsigned long currentMillis = millis();
    
    // Llamamos, cada minuto, a la función para insertar los datos en la base de datos
    if ((unsigned long) (currentMillis - previosMillis_0) >= intervalo_0){
        enviarBD();
        previosMillis_0 = millis();
      }
    if ((unsigned long) (currentMillis - previosMillis_1) >= intervalo_1){
        mostrarPantalla();
        previosMillis_1 = millis();
      }
    
    // Llamamos a la función iluminacion que controla la retroiluminación de la pantalla
    iluminacion();
     
    ArduinoOTA.handle(); //Llamamos a la actualización via OTA

  }
