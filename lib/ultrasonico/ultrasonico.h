#ifndef _ULTRASONICO_H_
#define _ULTRASONICO_H_

#include <Arduino.h>
#include <util.h>
#include <util/delay.h> //para usar _delay_ms()

//#define SAMPLES 1

#define     DISTANCE_MODE_TRIGGERED     1
#define     DISTANCE_MODE_CONTINUOUS    0

#define  NONE 0
#define  MEASURING 1
#define  DONE 2

#ifdef __cplusplus
extern "C"
{
#endif


//funciones para obtener las mediciones
uint16_t get_s2_centimeters(void);
uint16_t get_s3_centimeters(void);
uint16_t get_s1_centimeters(void);

/**
 * modo = DISTANCE_MODE_CONTINUOUS, mide automaticamente y podes obtener la ultima medidion con los getters 
 * modo = DISTANCE_MODE_TRIGGERED, use distance_read() to measure, can be blocking or polled
 */
void config_ultrasonic_measure(uint8_t mode);

/**
 * Preguntar si termino con distance_read_done() y leer con getters
 */
void distance_read(uint8_t readchannel);

/**
 * devuelve si la medicion de distancia termino o no
 */
uint8_t distance_read_done();



void config_timer1(void);
void config_IO_change_interrupt(uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif //_ULTRASONICO_H_