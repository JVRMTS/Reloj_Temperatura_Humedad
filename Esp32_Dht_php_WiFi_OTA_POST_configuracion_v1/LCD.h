/*
 * La función de este archivo es mostrar en la pantalla LCD los datos que queremos ver.
 * Probado con un LCD 2004.
 * JMTS
 * 29/12/24
*/

#include <LiquidCrystal_I2C.h>

// Tipo de LCD y Dirección I2C LCD
int col = 20;    //Columnas del LCD
int fil = 4;     //Filas del LCD
byte dir = 0x27; //Dirección I2C del LCD

LiquidCrystal_I2C lcd(dir, col, fil); // Creamos el objeto LCD y lo configuramos con su direccion I2C y el tipo de pantalla (en este caso 2004)

// Función mostrarTemperatura para imprimirlaen el LCD
void mostrarPantalla(){
   temperatura();
   fecha();             
   // Se imprime el día de la semana, fecha y hora en el LCD
   lcd.setCursor(7, 0);
   lcd.print(horMin);
   lcd.setCursor(2, 1); // Situamos el cursor en la primera linea del LCD
   lcd.print(diaS);
   lcd.setCursor(5, 1);
   lcd.print(diaS + " " + dia + " " + mes + " " + ano);// Imprimimos la fecha
   lcd.setCursor(0, 2);  // Se situa el cursor en la segunda linea del LCD
   lcd.print(t1);        // Se imprime la temperatura en el LCD
   lcd.setCursor(11, 2); // Se situa el cursor en la tercera linea en la posición 4 para que cuadre
   lcd.print(t2);        // Se imprime la humedad en el LCD
   lcd.setCursor(2, 3);  // Se situa el cursor en la cuarta linea
   lcd.print(t3);        // Se imprime la sensacion termica en el LCD
}
