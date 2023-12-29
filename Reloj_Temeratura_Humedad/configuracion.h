
/* Fichero de configuración para el reloj con envío de datos por POST y actualización via OTA
 * Creado el 27/12/2021
 * por @JMTS
*/

// Configuración de la Ubicación
// tambien da nombre al puerto de actualizacion via OTA

byte ub = 2;// Ubicación (1-despacho) (2-salon) (3-pruebas)

char* ubicacion(){
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
const char *ssid = "JMTS";
const char *password = "JAVIER276MTS";

//Password para la actualización via OTA
char *passwordOTA = "JavierMt5*/";

//Configuración del Servidor Web
String dominio = "sensores.jmts.es";
String url = "http://" + dominio + "/config/insertar_post.php"; //Dirección web del servidor
