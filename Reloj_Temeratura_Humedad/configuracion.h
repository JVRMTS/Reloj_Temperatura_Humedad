
/* Fichero de configuración para el reloj con envío de datos por POST y actualización via OTA
 * Creado el 27/12/2021
 * por @JMTS
*/

// Configuración de la Ubicación
// tambien da nombre al puerto de actualizacion via OTA

byte ub = 1;// Ubicación (1-despacho) (2-salon) (3-dormitorio) (4-resumen) (5-pruebas)

char * ubicacion(){
  char * ubic;
  switch (ub) {
    case 1:
      ubic = "DESPACHO";
    break;
    case 2:
      ubic = "SALON";
    break;
    case 3:
      ubic = "DORMITORIO";
    break;
    case 4:
      ubic = "RESUMEN";
    break;
    case 5:
      ubic = "PRUEBAS";
    break;
  }
  return ubic;
}

//Configuración de la WiFi
char * ssid = "*****";
char * password = "*****";

//Password para la actualización via OTA
char * passwordOTA = "*****";

//Configuración del Servidor Web
String dominio = "tu_dominio.com"; // El dominio en el que lo quieras publicar
String url = "http://" + dominio + "/config/insertar_post.php"; //Dirección web del servidor
