#include <Arduino.h>
//estas dos de abajo ya estan incluidas en Arduino.h
//#include <stdint.h>  //para usar uint8_t etc...
#include <util/delay.h> //para usar _delay_ms()
#include <util.h>
#include <display.h>


//uso arduino porque el pro micro usa las funciones internas de arduino para el manejo del USB
setup(){

  config_io();  //configuro las entradas y salidas
//  config_timer0();//configuro el Timer0


}


loop(){



//}
//int main(void){


  uint16_t disp_data[5];
  disp_data[0]=1234;
  disp_data[1]=5678;
  disp_data[2]=9012;
  disp_data[3]=3456;
  disp_data[4]=7890;
//  sei();//habilita las interrupciones

  //delay(1);

  refresh_disp(&disp_data[0]);


}



