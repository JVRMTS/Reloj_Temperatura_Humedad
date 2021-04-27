/*
 * Conexión con la base de datos y envío de la información
 * 24/03/2021
 */
#include "incluir.h"
HTTPClient http; // Se crea el objeto http para el envío de datos

void enviarBD()
{
  // Leemos las variables de temperatura, humedad y el cálculo de la senación térmica
  double h = dht.readHumidity();                  //Leemos la humedad del sensor
  String Hum = String(h, 2);                      // La convertimos a un String
  double t = dht.readTemperature();               // Leemos la temperatura del sensor
  String Temp = String(t, 2);                     // La convertimos a un String
  double hic = dht.computeHeatIndex(t, h, false); // Calculamos la sensación térmica
  String TeR = String(hic, 2);                    // La convertimos a un String
  String datos = ("t=" + Temp + "&h=" + Hum + "&st=" + TeR + "&ub=" + ub);

  http.begin(url);                                                     // Iniciamos la conexión http con la dirección web donde esta la páguina que nos inserta los datos
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // tipo de datos que enviamos
  String httpRequestData = datos;                                      // enviamos los datos por POST
  int httpResponseCode = http.POST(httpRequestData);                   // leemos la respuesta del servidor
  http.end();                                                          // cerramos la conexión http
}
