/* Control de la retroiluminación de la pantalla, mediante la lectura de una LDR
 * y escribiendo con la libreria PWMOutESP32.h en el pin de la retroiluminación
 * Creado el 26/12/2023
*/
void iluminacion(){

// Comprobamos la intensidad de la luz
    valorLDR = analogRead(pinLDR); // Leemos la variable del LDR
    unsigned int x = valorLDR / 8;
    if(x < 6){
      valorLCD = 5; // esto es para que nunca se apaque del todo el LCD
    }else{
      valorLCD = x; // Asignamos el valor de iluminación del LCD en base al valor del LDR
    }
    pwm.analogWrite(pinLCD, valorLCD); // Escribimos en el pinLCD el valor de la retroiluminación

}