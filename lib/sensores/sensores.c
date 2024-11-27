#include <sensores.h>
/*

la cosa es asi:

pongo timer 1 a andar a 250Khz, cada 100mSeg genera una interrupcion.

cada irq por timer mira los timestaps de flancos de sensores y actualiza la medicion. Luego genera el disparo para la proxima medicion.

se configura IRQ por cambio de nivel en pines de entrada de pulsos.

en la IRQ de cambio de nivel, se detecta el flanco, y se guarda un timestamp para luego relizar el calculo de distancias.
*/

// variables de estado de entradas para deteccion de flanco:
uint8_t last_state;
// variables para timestamp de flancos
uint16_t rise_time, fall_time;
// variables de salida de medicion:
uint16_t s1_distance;
uint16_t s2_distance;
uint16_t s3_distance;

uint8_t channel = 1;
uint8_t measure_mode=0, measure_state=NONE;
//---------------------------------------
// measuring result getters
//---------------------------------------
uint16_t get_s1_centimeters(void)
{
  return s1_distance;//
}
//---------------------------------------
uint16_t get_s2_centimeters(void)
{
  return s2_distance;
}
//---------------------------------------
uint16_t get_s3_centimeters(void){
  return s3_distance;
}
//---------------------------------------
//---------------------------------------
void config_ultrasonic_measure(uint8_t mode)
{
  measure_mode = mode;
  config_timer1();
  config_IO_change_interrupt(1);

}
//---------------------------------------
//---------------------------------------


uint8_t get_floor_value( void ){

  if( bit_is_set(PINC,PC5) ){
    return 1;
  }
  return 0;

}
//---------------------------------------
//---------------------------------------
uint8_t get_audio_value( void ){

  if( bit_is_set(PINB,PB1) ){
    return 1;
  }
  return 0;

}

//---------------------------------------
//---------------------------------------
void config_timer1(void)
{

  TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (0 << WGM11) | (0 << WGM10);         // CTC
  TCCR1B = (0 << ICNC1) | (0 << ICES1) | (0 << WGM13) | (1 << WGM12) | (0 << CS12) | (1 << CS11) | (1 << CS10); // clk/64
  TCCR1C = (0 << FOC1A) | (0 << FOC1B);
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
void config_IO_change_interrupt(uint8_t channel)
{

  PCICR |= (1 << PCIE1);
  if (channel == 1)
  {
    PCMSK1 = (1 << PCINT9);
  } // Pin Change Mask Register
  if (channel == 2)
  {
    PCMSK1 = (1 << PCINT10);
  } // Pin Change Mask Register
  if (channel == 3)
  {
    PCMSK1 = (1 << PCINT11);
  } // Pin Change Mask Register

  asm("NOP");
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void distance_read(uint8_t readchannel){


  TCNT1=0; //reinicio TIMER 1

  measure_state = MEASURING;

  channel = readchannel; 
  last_state = 0;
  config_IO_change_interrupt(readchannel);

  // trigger next ultrasonic measure
  bit_set(PORTC, 0);
  _delay_us(15);
  bit_clear(PORTC, 0);

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
uint8_t distance_read_done(){
  return measure_state;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)
{
  // esto se da cada 100mSeg

  // calculo distancias a partir de las ultimas mediciones:
  if (channel == 1){ s1_distance = (fall_time - rise_time); } else
  if (channel == 2){ s2_distance = (fall_time - rise_time); } else
  if (channel == 3){ s3_distance = (fall_time - rise_time); }
  measure_state = DONE;
  
  if(measure_mode == DISTANCE_MODE_CONTINUOUS){
    //defino proxima medicion:    
    channel++;
    if( channel > 3 ){ channel = 1; }
    
    last_state = 0;

    config_IO_change_interrupt(channel);
    
    // trigger next ultrasonic measure
    bit_set(PORTC, 0);
    _delay_us(15);
    bit_clear(PORTC, 0);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

ISR(PCINT1_vect)
{
  uint16_t time = TCNT1;
  uint8_t state;

  //------------------------------------------
  // capturo valor de entradas
  //if (channel == 1){ state = bit_is_set(PINC, PC1) ? 1 : 0; }else
  //if (channel == 2){ state = bit_is_set(PINC, PC2) ? 1 : 0; }else
  //if (channel == 3){ state = bit_is_set(PINC, PC3) ? 1 : 0; }
  //------------------------------------------
  state = bit_is_set(PINC, channel) ? 1 : 0;

  // flanco ascendente sensor
  if (state == 1 && last_state == 0)
  {
    rise_time = time;
  }

  // flnco descendente sensor
  if (state == 0 && last_state == 1)
  {
    fall_time = time;
  }
  last_state = state;



}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
