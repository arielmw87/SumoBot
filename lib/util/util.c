#include <util.h>

//---------------------------------------
//---------------------------------------
void config_timer0(void)
{

  TCCR0A = 0b00000010; // CTC
  TCCR0B = 0b00000011; // clk/64
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

//---------------------------------------
//---------------------------------------
ISR(TIMER0_COMPA_vect)
{

  static uint16_t cnt = 0;
  cnt++;
  if (cnt >= 500)
  {

    // PINB |= (1<<PB5);//cambio estado de salida
    PINB |= (1 << PB1); // cambio estado de salida
    cnt = 0;
  }
}

//---------------------------------------
//---------------------------------------
void config_io(void)
{

  DDRB = (0 << PB1);                                                                  // AUDIO
  DDRC = (1 << PC0) | (0 << PC1) | (0 << PC2) | (0 << PC3) | (0 << PC5);              // ultrasonicos: trigger, Echoes, IR
  DDRD = (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7); // Motores
}