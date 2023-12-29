/*
 * Conexión con la base de datos y envío de la información
 * 29/12/2023
 */
#include <HTTPClient.h>
HTTPClient http; // Se crea el objeto http para el envío de datos

void enviarBD(){
  
  // Llamamos a la funcion temperatura para leer las variables de temperatura, humedad y el cálculo de la senación térmica
  temperatura();  
  String datos = ("t=" + Temp + "&h=" + Hum + "&st=" + TeR + "&ub=" + ub);
  http.begin(url);                                                     // Iniciamos la conexión http con la dirección web donde esta la páguina que nos inserta los datos
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // tipo de datos que enviamos
  String httpRequestData = datos;                                      // enviamos los datos por POST
  int httpResponseCode = http.POST(httpRequestData);                   // leemos la respuesta del servidor
  http.end();                                                          // cerramos la conexión http
}
