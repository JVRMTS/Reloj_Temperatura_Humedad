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
#include "incluir.h"
#include "configuracion.h"
#include "reloj.h"
#include "conexionWiFi.h"
#include "baseDatos.h"
#include "ota.h"

// Iniciamos los contadores para insertar en la base de datos y actualizar el reloj
unsigned long previosMillis_0;
unsigned long previosMillis_1;
unsigned long intervalo_0 = 59000;
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
    if (WiFi.isConnected() == false)
    {
      conectarWiFi();
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    }

    // Llamamos a la función para imprimir los datos en el LCD cada segundo
    unsigned long currentMillis = millis();
    
    // Llamamos, cada minuto, a la función para insertar los datos en la base de datos
    if ((unsigned long) (currentMillis - previosMillis_0) >= intervalo_0)
    {
      enviarBD();
      previosMillis_0 = millis();
    }
    if ((unsigned long) (currentMillis - previosMillis_1) >= intervalo_1)
    {
      mostrarTemperatura();
      previosMillis_1 = millis();
    }

     // Comprobamos la intensidad de la luz
    valorLDR = analogRead(pinLDR); // Leemos la variable del LDR
    unsigned int x = valorLDR / 8;
    if(x <6)
    {
      valorLCD = 5; // esto es para que nunca se apaque del todo el LCD
    }else{
      valorLCD = x; // Asignamos el valor de iluminación del LCD en base al valor del LDR
    }
    pwm.analogWrite(pinLCD, valorLCD); // Escribimos en el pinLCD el valor de la retroiluminación
    
    ArduinoOTA.handle(); //Llamamos a la actualización via OTA

  }