/* 
 * Control de la retroiluminación de la pantalla, mediante la lectura de una LDR
 * Escribimos en PWM con la libreria PWMOutESP32
 * @JMTS - www.jmts.es
 * Creado el 28/04/2024
 */

// Asignamos los pines de la iluminación del LCD y del LDR y declaramos sus variables
#define PINLCD 18
#define PINLDR 32

// Definimos el minimo de retroiluminación
#define MINIMO 50

unsigned int valorLDR;
unsigned int valorLCD;


#include <PWMOutESP32.h>
PWMOutESP32 pwm(12,5000); // Ajustamos la resolución de 12 bits y una frecuencia de 5000Hz

void iluminacion(){
// Comprobamos la intensidad de la luz
  valorLDR = analogRead(PINLDR); // Leemos la variable del LDR
// Comprobamos una intenisad lumínica mínima para que no se apague nunca el LCD
  if(valorLDR <= MINIMO){
    valorLCD = MINIMO;        // Ajustamos un mínimo de iluminación
  }else{
    valorLCD = valorLDR;  // Asignamos el valor de iluminación del LCD en base al valor del LDR
  }
  pwm.analogWrite(PINLCD, valorLCD); // Escribimos en el pinLCD el valor de la retroiluminación
}