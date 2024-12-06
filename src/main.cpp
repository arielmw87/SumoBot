#include <Arduino.h>
#include <util/delay.h> //para usar _delay_ms()
#include <util.h>
#include <sensores.h>
#include <motor.h>

void setup(){

  config_io();     // configuro las entradas y salidas
  motor_init();
  config_ultrasonic_measure(DISTANCE_MODE_CONTINUOUS);
  sei();
  Serial.begin(9600);
  
}


void loop(){


  Serial.println(get_s1_centimeters());
  Serial.println(get_s2_centimeters());
  Serial.println(get_s3_centimeters());
  Serial.println("--------------------");
  
  go(FORWARD,102);
  delay(150);
  
  go(BACKWARD,102);
  delay(150);


}
