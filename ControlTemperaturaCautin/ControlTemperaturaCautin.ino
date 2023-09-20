/**
   GeekFactory - "INNOVATING TOGETHER"
   Distribucion de materiales para el desarrollo e innovacion tecnologica
   www.geekfactory.mx

   SKETCH PARA MEDIR TEMPERATURA CON TERMOPAR Y MAX6675. MUESTRA EL RESULTADO
   DE LA MEDICION EN EL MONITOR //Serial DE ARDUINO. ESTE EJEMPLO USA LA LIBRERIA
   PARA EL MAX6675 DE ADAFRUIT.
*/
#include "max6675.h"
//incluyo la libreria para el LCD
#include <LiquidCrystal.h>
//Crear el objeto LCD con los números correspondientes (rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(8, 3, 4, 2, 1, 0);


const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)



// CONFIGURACION DE LOS PINES UTILIZADOS PARA LA COMUNICACIÓN CON EL MAX6675
#define CONFIG_TCGND_PIN      8
#define CONFIG_TCVCC_PIN      9
#define CONFIG_TCSCK_PIN      10
#define CONFIG_TCCS_PIN       11
#define CONFIG_TCDO_PIN       12

// OBJETO UTILIZADO PARA LA COMUNICACION CON EL MAX6675
MAX6675 thermocouple(CONFIG_TCSCK_PIN, CONFIG_TCCS_PIN, CONFIG_TCDO_PIN);

void setup() {
  // PREPARAR LA INTERFAZ //Serial
  //Serial.begin(9600);

  // USAR PINES DE ARDUINO PARA ALIMENTAR EL MODULO MAX6675
  pinMode(CONFIG_TCVCC_PIN, OUTPUT); 
  digitalWrite(CONFIG_TCVCC_PIN, HIGH);
  pinMode(CONFIG_TCGND_PIN, OUTPUT); 
  digitalWrite(CONFIG_TCGND_PIN, LOW);

  // IMPRIMR MENSAJE INICIAL A LA TERMINAL
  //Serial.println(F("----------------------------------------------------"));
  //Serial.println(F("      TUTORIAL TERMOPAR CON ARDUINO Y MAX6675       "));
  //Serial.println(F("            http://www.geekfactory.mx               "));
  //Serial.println(F("----------------------------------------------------"));

  // Inicializar el LCD con el número de  columnas y filas del LCD
  lcd.begin(16, 2);
  // Escribimos el Mensaje en el LCD.
  lcd.print("Hola Mundo");

  // ESPERAR A QUE SE ESTABILICE LA ENERGIA
  delay(500);
}

void loop() {
  // IMPRIMIR LA TEMPERATURA EN LA TERMINAL //Serial
  long   temperatura=thermocouple.readCelsius()*.59;
  //ahora leo la temperatura del potenciometro
  sensorValue =map(analogRead(analogInPin), 0, 1023, 200, 450);
  //mando la informacion alpuerto //Serial
  //Serial.print("temperatura= ");
  //Serial.print(temperatura);
  //Serial.print("\tpotenciometro= ");
  //Serial.println(sensorValue );  
  //mando la informacion al LCD
  // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 0);
  lcd.print("Tem. Meta:");
  lcd.print(sensorValue );

  lcd.setCursor(0, 1);
  lcd.print("Tem. Actual:");
  lcd.print(temperatura );
  //comaro las temperaturas
  if(temperatura<sensorValue)
  {
    //hay que activar el cautin para que se caliente
    analogWrite(analogOutPin, 0xf0);
  }
  else
  {
    //apago el cautin para poder leer la teperartura
    analogWrite(analogOutPin, 0x00);
  }
  //me espero un rato
  delay(500)  ;
}
