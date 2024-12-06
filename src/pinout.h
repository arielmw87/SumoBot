
#ifndef __PINOUT_H_
#define __PINOUT_H_

#include <Arduino.h>
#include <util.h>


/*--------------------------------------------------------------*/
/*                                                              */
/* Pines del sumobot                                            */
/*                                                              */
/*--------------------------------------------------------------*/

//#define col1_on             bit_set(PORTD, PD5)//bit_set(PORTF, PF7)
//#define col1_off            bit_clear(PORTD, PD5)//bit_clear(PORTF, PF7)
/*

//ultrasonicos:

trigger: PC0
Echo 1: PC1
Echo 2: PC2
Echo 3: PC3
//se usa TIMER 1 para base de tiempo e interrupciones por cambio en los pines para la medicion.


IR: PC5
AUDIO: PB1


//seria muy bueno cambiar los enable a PD5 y PD6, de esa manera ambos PWM se generarian con el TIMER 0
Motor R:
    Enable: PD3 (PWM) -> PD6
    In 1:   PD2
    In 2:   PD4

Motor L:
    Enable: PD5 (PWM)
    In 3:   PD7
    In 4:   PD6 -> PD3

*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif






#ifdef __cplusplus
}
#endif

#endif //__PINOUT_H_