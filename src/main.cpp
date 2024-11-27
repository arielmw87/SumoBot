#include <Arduino.h>
#include <util/delay.h> //para usar _delay_ms()
#include <util.h>
#include <display.h>
#include <sensores.h>

void setup(){

  config_io();     // configuro las entradas y salidas
  config_ultrasonic_measure();
  sei();
  Serial.begin(9600);
  
}


void loop(){
  Serial.println(get_s1_centimeters());
  Serial.println(get_s2_centimeters());
  Serial.println(get_s3_centimeters());
  Serial.println("--------------------");
  delay(300);


}
