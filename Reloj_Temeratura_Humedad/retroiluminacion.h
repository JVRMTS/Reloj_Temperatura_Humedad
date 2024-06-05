/* 
 * Control de la retroiluminación de la pantalla, mediante la lectura de una LDR
 * Con la version 3.0.0 de Esp32 podemos utilizar analogWrite en con el Esp32, se a configurar ledcAttach,
 * si no se configura la pantalla parpadeará dependiendo de la iluminación.
 * @JMTS - www.jmts.es
 * Creado el 05/06/2024
 */

// Asignamos los pines de la iluminación del LCD y del LDR y declaramos sus variables
#define PINLCD 18
#define PINLDR 32
// Definimos el minimo de retroiluminación
#define MINIMO 16
unsigned int valorLDR;
unsigned int valorLCD;

// Configuración canal analógico
void configLedc(){
  ledcAttach(PINLCD, 5000, 12);
}

void iluminacion(){
// Comprobamos la intensidad de la luz
  valorLDR = analogRead(PINLDR)/4; // Leemos la variable del LDR
// Comprobamos una intenisad lumínica mínima para que no se apague nunca el LCD
  if(valorLDR <= MINIMO){
    valorLCD = MINIMO;        // Ajustamos un mínimo de iluminación
  }else{
    valorLCD = valorLDR;  // Asignamos el valor de iluminación del LCD en base al valor del LDR
  }
  analogWrite(PINLCD, valorLCD); // Escribimos en el pinLCD el valor de la retroiluminación
}