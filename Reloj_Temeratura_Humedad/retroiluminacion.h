/* 
 * Control de la retroiluminación de la pantalla, mediante la lectura de una LDR
 * Con la version 3.0.0 de Esp32 podemos utilizar analogWrite en con el Esp32, se a configurar la resolución y la frecuencia de la función analogWrite,
 * si no se configura la pantalla parpadeará dependiendo de la iluminación.
 * @JMTS - www.jmts.es
 * Creado el 02/07/2024
 */

// Asignamos los pines de la iluminación del LCD y del LDR y declaramos sus variables
#define PINLCD 18
#define PINLDR 32
// Definimos el minimo de retroiluminación
#define MINIMO 12
unsigned int valorLDR;
unsigned int valorLCD;

// Configuración canal analógico
void configLedc(){
  analogWriteResolution(PINLCD, 8);   // Configuramos la resoloción de escritura en el pin seleccionado a una resolución de 8 bits
  analogWriteFrequency(PINLCD,5000);  // Configuramos la frecuencia de escritura en el pin seleccionado
}

void iluminacion(){
  valorLDR = analogRead(PINLDR)/16;   // Leemos la variable del LDR y lo convertimos a 8 bits
  // Comprobamos la intenisad lumínica mínima para que no se apague nunca el LCD
  if(valorLDR <= MINIMO){
    valorLCD = MINIMO;                // Ajustamos un mínimo de iluminación
  }else{
    valorLCD = valorLDR;              // Asignamos el valor de iluminación del LCD en base al valor del LDR
  }
  analogWrite(PINLCD, valorLCD);      // Escribimos en el pinLCD el valor de la retroiluminación
}