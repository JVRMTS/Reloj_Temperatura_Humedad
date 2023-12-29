
ACTUALIZACIÓN DEL 29/12/23

Se ha actualizado el nombre y la carpeta del archivo .ino, se han creado nuevos archivos para que alberguen las distintas funciones
y así poder reutilizarlas en distintos proyectos, ahora la definición de pines y librerias de cada biblioteca estan en cada fichero.

Es importante mantener el orden de los includes en el script principal, si no lo haces te dará fallo en la compilación.
Ahora en el archivo configuracion.h solo se define la ubicación, la WiFi, la contraseña WiFi, la contraseña OTA y el dominio web para actualizar la base de datos si lo utilizas.

ACTUALIZACIÓN DEL 26/10/2023

Se cambia la libreria AnalogWrite por PWMOutESP32 que realiza la misma función, al impedirme la primera compilar. 
Tambien me ha dado problemas la actualización vía OTA, se soluciono conectando el módulo via USB y ya aparecio como puerto ota.

RELOJ CON TEMPERATURA, HUMEDAD Y SENSACIÓN TÉRMICA CON ESP32 Y ENVIO A BASE DE DATOS Y PUBLICACION DE WEB CON ESTOS DATOS.
Este proyecto comenzó con el confinamiento, no soy experto, simplemente tenia que matar el tiempo de alguna forma y me decidí por comenzar a conocer Arduino, aquí se puede ver la evolución que ha tenido.
El código es mejorable, pues como ya he comentado solo soy un aficionado, aunque ante varias consulta que he visto en grupos de facebook me decidí a subirlo por si a alguna persona le puede interesar.

Despues de varias pruebas se realiza con el envío de los valores a la base de datos mediante el protocolo POST ( la versión anterior lo realizaba con GET ) y se implementa la actualización via OTA para no tener que estar moviendo los relojes de lugar.

Se adjuntan archivos de publicación en la web.

Sientete libre de utilizar todo el contenido que está en el repositorio y si crees que lo puedes mejorar no dudes en hacerlo y compartirlo.

La web esta activa y funcionando en https://pruebas.jmts.es puedes pasar a verla.

El archivo STL de la caja esta publicado en https://www.thingiverse.com/thing:4808951
