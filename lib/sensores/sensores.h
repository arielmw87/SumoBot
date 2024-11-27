#ifndef __SENSORES_H_
#define __SENSORES_H_

#include <Arduino.h>
#include <util.h>
#include <util/delay.h> //para usar _delay_ms()

//#define SAMPLES 1

#ifdef __cplusplus
extern "C"
{
#endif

//funciones para obtener valores de sensores:

uint8_t get_floor_value( void );
uint8_t get_audio_value( void );



//funciones para obtener las mediciones
uint16_t get_s2_centimeters(void);
uint16_t get_s3_centimeters(void);
uint16_t get_s1_centimeters(void);


void config_ultrasonic_measure(void);

void config_timer1(void);
void config_IO_change_interrupt(uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif //__SENSORES_H_