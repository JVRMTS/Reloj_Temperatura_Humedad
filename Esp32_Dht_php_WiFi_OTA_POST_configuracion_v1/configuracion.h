/* Fichero de configuración para el reloj con envío de datos por POST y actualización via OTA
 * Creado el 24/03/2021
 * por @JMTS
*/

#define DHTTYPE DHT22 // Se define el tipo de DHT: DHT 22
#define DHTPIN 27     // Se define el puerto al que conectamos el Sensor DHT: pin digital 27

// Configuración de la Ubicación
// tambien da nombre al puerto de actualizacion via OTA
byte ub = 1; // Ubicación (1-despacho) (2-salon) (3-pruebas)

char *ubicacion()
{
  char *ubic;
  if (ub == 1)
  {
    ubic = "Despacho";
  }
  else if (ub == 2)
  {
    ubic = "Salon";
  }
  else if (ub == 3)
  {
    ubic = "Pruebas";
  }
  return ubic;
}

//Configuración de la WiFi
const char *ssid = "****";
const char *password = "****";

//Password para la actualización via OTA
char *passwordOTA = "*****";

//Configuración del Servidor Web
String dominio = "pruebas.jmts.es";
String url = "https://" + dominio + "/config/insertar_post.php"; //Dirección web del servidor

// Tipo de LCD y Dirección I2C LCD
int col = 20;    //Columnas del LCD
int fil = 4;     //Filas del LCD
byte dir = 0x27; //Dirección I2C del LCD

// Asignamos los pines de la iluminación del LCD y del LDR y declaramos sus variables
const int pinLCD = 18;
const int pinLDR = 32;
unsigned int valorLDR;
unsigned int valorLCD;
