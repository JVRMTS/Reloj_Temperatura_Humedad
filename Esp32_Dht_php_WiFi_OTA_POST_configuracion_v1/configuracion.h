/* Fichero de configuración para el reloj con envío de datos por POST y actualización via OTA
 * Creado el 24/3/2021
 * por @JMTS
*/ 

                    // Configuración de la Ubicación
                    // Ubicación (1-despacho) (2-salon) (3-pruebas)
                    // tambien da nombre al puerto de actualizacion via OTA
byte ub = 1;

char* ubicacion(){
char* ubic;
  if (ub == 1){
    ubic = "Despacho";
  }else if (ub == 2){
    ubic = "Salon";
  }else if (ub == 3){
    ubic = "Pruebas";  
  }
  return ubic;
}

                    //Configuración de la WiFi
const char* ssid = "****"; // el nombre de tu wifi
const char* password = "****"; // pon la contraseña de tu wifi 

                    //Password para la ota
char* passwordOTA = "****"; //pon la contraseña que desees para la actualización via OTA

                    //Configuración del Servidor Web
String dominio = "192.168.1.4"; // Pon el dominio o dirección IP del servidor
String url = "http://" + dominio + "/config/insertar_post.php"; //Dirección web del servidor

                    // Tipo de LCD y Dirección I2C LCD
int col= 20;
int fil= 4;
byte dir = 0x27;

                    // Asignamos los pines de la iluminación del LCD y del LDR y declaramos sus variables
const int pinLCD = 18;
const int pinLDR = 32;
unsigned int valorLDR;
unsigned int valorLCD;
