#ifndef __UTIL_H_
#define __UTIL_H_

#include <Arduino.h>


#ifdef __cplusplus
extern "C"
{
#endif

    //macros para facilitar manejo de bits
    #define bit_set(SFR,BIT) SFR|=(1<<BIT)
    #define bit_clear(SFR,BIT) SFR&=~(1<<BIT)




    /**
     * @brief configura pines de entrada/salida
     *
     */
    void config_io(void);



    /* esta funcion configura el timer0 para que de una irq cada 1mSeg*/
    /**
     * @brief configura el timer0 para generar interrupciones cada 1mSeg
     *
     */
    void config_timer0(void);






#ifdef __cplusplus
}
#endif

#endif //__UTIL_H_