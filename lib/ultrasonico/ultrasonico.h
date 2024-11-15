#ifndef _ULTRASONICO_H_
#define _ULTRASONICO_H_

#include <Arduino.h>
#include <util.h>
#include <util/delay.h> //para usar _delay_ms()


#ifdef __cplusplus
extern "C"
{
#endif


//funciones para obtener las mediciones
uint8_t get_s1_centimeters(void);
uint8_t get_s2_centimeters(void);
uint8_t get_s3_centimeters(void);


void config_ultrasonic_measure(void);

void config_timer1(void);
void config_IO_change_interrupt(void);

#ifdef __cplusplus
}
#endif

#endif //_ULTRASONICO_H_