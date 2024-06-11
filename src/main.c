#include <Arduino.h>
//estas dos de abajo ya estan incluidas en Arduino.h
#include <stdint.h>  //para usar uint8_t etc...
#include <util/delay.h> //para usar _delay_ms()


void config_IO(void);
void config_TIMER0(void);
void config_TIMER1(void);

main(){

  config_IO();  //configuro las entradas y salidas
  config_TIMER0();//configuro el Timer0
  config_TIMER1();//configuro el Timer1
  sei();//habilita las interrupciones

  while(1){

    _delay_ms(500);


  }

}



//---------------------------------------
ISR(TIMER0_COMPA_vect){
  static uint16_t cnt=0;
  cnt++;
  if(cnt>=100){
    PINB |= (1<<PB5);//cambio estado de salida
  cnt=0;
  }

}
//---------------------------------------
void config_TIMER0(void){

  TCCR0A = 0b00000010; //CTC
  TCCR0B = 0b00000011; //clk/64
  OCR0A = 249;
  TIMSK0 = (1 << OCIE0A);
/*
16 Mhz
16 Mhz / 8 = 2Mhz(500nS)  desborda max cada = 128useg
16 Mhz / 64 = 250Khz  desborda max cada = 1.024mseg
16 Mhz / 256 = 62500hz  desborda max cada = 4.096mseg
16 Mhz / 1024 = 15625hz  desborda max cada = 16.384mseg

250Khz(4useg)
1mseg/4uSeg = 250cuentas
*/

}

ISR(TIMER1_COMPA_vect){
  static uint16_t cnt=0;
  cnt++;
  if(cnt>=500){

    //PINB |= (1<<PB5);//cambio estado de salida
    PINB |= (1<<PB1);//cambio estado de salida
  cnt=0;
  }
}

void config_TIMER1(void)
{
  //TCCR0A = 0xFF;
  TCCR1A = 0b00000000; //CTC
  TCCR1B = 0b00001011; //clk/64
  TCCR1C = 0;
  OCR1A = 249;
  TIMSK1 = (1 << OCIE1A);
/*
16 Mhz
16 Mhz / 8 = 2Mhz(500nS)  desborda max cada = 128useg
16 Mhz / 64 = 250Khz  desborda max cada = 1.024mseg
16 Mhz / 256 = 62500hz  desborda max cada = 4.096mseg
16 Mhz / 1024 = 15625hz  desborda max cada = 16.384mseg

250Khz(4useg)
1mseg/4uSeg = 250cuentas
*/


//  TCCR0A = (1 << WGM01);              //Activa el bit CTC (clear timer on compare match)                                      //del TCCR0A (timer counter/control register)
//  OCR0A = 5;                        //valor de comparacion de int cada 0.4ms  2520hz
//  TCCR0B = (1 << CS00) | (1 << CS02); //preescaler dividiendo 1024
//  TIMSK0 = (1 << OCIE0A);             //Habilita las interrupciones entimer compare
}

void config_IO(void){

  DDRB |= (1<<PB5);//salida
  DDRB |= (1<<PB1);//salida
}