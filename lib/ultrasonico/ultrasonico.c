#include <ultrasonico.h>
/*

la cosa es asi:

pongo timer 1 a andar a 250Khz, cada 100mSeg genera una interrupcion.

cada irq por timer mira los timestaps de flancos de sensores y actualiza la medicion. Luego genera el disparo para la proxima medicion.

se configura IRQ por cambio de nivel en pines de entrada de pulsos.

en la IRQ de cambio de nivel, se detecta el flanco, y se guarda un timestamp para luego relizar el calculo de distancias.




*/
// variables de estado de entradas para deteccion de flanco:
uint8_t last_s1_state, last_s2_state, last_s3_state;
uint8_t s1_state, s2_state, s3_state;
// variables para timestamp de flancos
uint16_t s1_rise_time, s1_fall_time;
uint16_t s2_rise_time, s2_fall_time;
uint16_t s3_rise_time, s3_fall_time;
// variables de salida de medicion:
uint8_t s1_distance;
uint8_t s2_distance;
uint8_t s3_distance;




//---------------------------------------
// measuring result getters
//---------------------------------------
uint8_t get_s1_centimeters(void){
  return s1_distance;
}
//---------------------------------------
uint8_t get_s2_centimeters(void){
  return s2_distance;
}
//---------------------------------------
uint8_t get_s3_centimeters(void){
  return s2_distance;
}
//---------------------------------------
//---------------------------------------
void config_ultrasonic_measure(void){

  config_timer1();
  config_IO_change_interrupt();
}
//---------------------------------------
//---------------------------------------
//---------------------------------------
//---------------------------------------
void config_timer1(void){


  TCCR1A = ( 0 << COM1A1 ) | ( 0 << COM1A0 ) | ( 0 << COM1B1 ) | ( 0 << COM1B0 ) | ( 0 << WGM11 ) | ( 0 << WGM10 ); //CTC
  TCCR1B = (0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10); //clk/64
  TCCR1C = (0<<FOC1A) | (0 << FOC1B);
  OCR1A = 24999; // irq cada 100mSeg
  TIMSK1 = (1 << OCIE0A);
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
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void config_IO_change_interrupt(void){


    PCICR |= (1<<PCIE1);
    PCMSK1 =  ( 1 << PCINT11 ) | ( 1 << PCINT10 ) | ( 1 << PCINT9  );//Pin Change Mask Register


}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect){
//esto se da cada 100mSeg

  //cambio de estado el led del arduino para que titile al compas de la medicion.
  
  bit_clear(PORTB, PB5);//prendo led

  //calculo distancias a partir de las ultimas mediciones:

  s1_distance = (uint16_t)(s1_fall_time - s1_rise_time) / (58/4);// 58 es la constante uS a CM, 4 es la base de tiempo en uS del timer
  s2_distance = (uint16_t)(s2_fall_time - s2_rise_time) / (58/4);// 58 es la constante uS a CM, 4 es la base de tiempo en uS del timer
  s3_distance = (uint16_t)(s3_fall_time - s3_rise_time) / (58/4);// 58 es la constante uS a CM, 4 es la base de tiempo en uS del timer


  //trigger next ultrasonic measure
  bit_set(PORTC,0);
  _delay_us(15);
  bit_clear(PORTC,0);

  bit_set(PORTB, PB5);//apago led

}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

ISR(PCINT1_vect){

//capturo valor de entradas
s1_state = bit_is_set(PINC,PC1) ? 1 : 0;
s2_state = bit_is_set(PINC,PC2) ? 1 : 0;
s3_state = bit_is_set(PINC,PC3) ? 1 : 0;

//detecto flancos:
//ascendente sensor 1
if( s1_state == 1 && last_s1_state == 0){s1_rise_time = TCNT1; }
//ascendente sensor 2
if( s2_state == 1 && last_s2_state == 0){s2_rise_time = TCNT1; }
//ascendente sensor 3
if( s3_state == 1 && last_s3_state == 0){s3_rise_time = TCNT1; }

//descendente sensor 1
if( s1_state == 0 && last_s1_state == 1){s1_fall_time = TCNT1; }
//descendente sensor 2
if( s2_state == 0 && last_s2_state == 1){s2_fall_time = TCNT1; }
//descendente sensor 3
if( s3_state == 0 && last_s3_state == 1){s3_fall_time = TCNT1; }



//guardo valores para la proxima:
last_s1_state = s1_state;
last_s2_state = s2_state;
last_s3_state = s1_state;

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
