/*
 * @JMTS
 * ESP32 DEVKIT
 * Reloj con fecha y hora más sensor de temperatura y humedad en pantalla LCD I2C 2004
 * Sensor de Temperatura-Humedad DHT22.
 * Hora a traves de servidor NTP basado en el ejemplo SimpleTime de la libreria del ESP32
 * Conexión a base de datos Mysql mediante php con el método POST para realizar un registro
 * La retroiluminación del LCD se gradua mediante LDR
 * Actualización del frimware via OTA con contraseña basado en el ejemplo ArduinoOTA
 * 24/03/2021
 */
#include "incluir.h"
#include "configuracion.h"
#include "reloj.h"
#include "conexionWiFi.h"
#include "baseDatos.h"

// Iniciamos los contadores para insertar en la base de datos y actualizar el reloj
long previosMillis = 0;
long intervalo_0 = 59999;
long intervalo_1 = 1000;

void setup()
{
  Serial.begin(115200); // Se inicia el puerto serie y la velocidad
  lcd.init();           // Se inicia el lcd
  lcd.backlight();      // Se enciende la retroiluminación del lcd
  lcd.clear();          // Se borra la pantalla del lcd
  dht.begin();          // Se inicia la lectura del dht

  // Conexion a la wifi y sincronización del reloj NTP
  conectarWiFi();
  Serial.println("Arrancando");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Conexion fallida! Reseteando...");
    delay(5000);
    ESP.restart();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    // Establecemos el nombre del dispositivo
  }

// incluimos la actualización via OTA
#include "ota.h"

  void loop()
  {
    ArduinoOTA.handle(); //Llamamos a la actualización via OTA

    // Comprobamos la intensidad de la luz
    valorLDR = analogRead(pinLDR); // Leemos la variable del LDR
    if (valorLDR >= 5)
    {
      valorLCD = valorLDR / 8; // Le damos el valor a la salida del LCD
    }
    else
    {
      valorLCD = 5; // esto es para que nunca se apaque del todo el LCD
    }
    analogWrite(pinLCD, valorLCD); // Escribimos en el pinLCD el valor

    //Si se ha perdido la conexión wifi llamamos a la función para conectar de nuevo y configuramos fecha y hora
    if (WiFi.isConnected() == false)
    {
      conectarWiFi();
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    }

    // Llamamos a la función para imprimir los datos en el LCD cada segundo
    unsigned long currentMillis = millis();
    if (currentMillis - previosMillis > intervalo_1)
    {
      mostrarTemperatura();
    }

    // Llamamos cada minuto a la función para insertar los datos en la base de datos
    if (currentMillis - previosMillis > intervalo_0)
    {
      previosMillis = currentMillis;
      enviarBD();
    }
  }
