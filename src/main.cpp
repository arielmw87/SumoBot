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

uint16_t front_dist=0;

front_dist =get_s1_centimeters();
  Serial.println( front_dist);
  Serial.println(get_s2_centimeters());
  Serial.println(get_s3_centimeters());
  Serial.println("--------------------");
  

  if(front_dist < 200){
    go(BACKWARD,72);
  }else if(front_dist > 600){
    go(FORWARD,72);
  }



}
