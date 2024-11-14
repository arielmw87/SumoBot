#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include <Arduino.h>
#include <util.h>

#define ON 1
#define OFF 0

#define HEXADECIMAL 1
#define DECIMAL 0

#define col1 0
#define col2 1
#define col3 2
#define col4 3


/*--------------------------------------------------------------*/
/* aca defino el manejo de pines para el display, si se cambia, */
/* acordarse de configurar los pines                            */
/*--------------------------------------------------------------*/

#define col1_on             bit_set(PORTD, PD5)//bit_set(PORTF, PF7)
#define col1_off            bit_clear(PORTD, PD5)//bit_clear(PORTF, PF7)
#define col2_on             bit_set(PORTD, PD4)//bit_set(PORTF, PF6)
#define col2_off            bit_clear(PORTD, PD4)//bit_clear(PORTF, PF6)
#define col3_on             bit_set(PORTD, PD3)//bit_set(PORTF, PF5)
#define col3_off            bit_clear(PORTD, PD3)//bit_clear(PORTF, PF5)
#define col4_on             bit_set(PORTD, PD2)//bit_set(PORTF, PF4)
#define col4_off            bit_clear(PORTD, PD2)//bit_clear(PORTF, PF4)

#define data_line_set       bit_set(PORTD, PD6)//bit_set(PORTB, PB1)
#define data_line_clear     bit_clear(PORTD, PD6)//bit_clear(PORTB, PB1)
#define clk_line_set        bit_set(PORTB, PB0)//bit_set(PORTB, PB2)
#define clk_line_clear      bit_clear(PORTB, PB0)//bit_clear(PORTB, PB2)
#define latch_line_set      bit_set(PORTD, PD7)//bit_set(PORTB, PB3)
#define latch_line_clear    bit_clear(PORTD, PD7)//bit_clear(PORTB, PB3)

/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief genera pulso de clock para registro de desplazamiento
     *
     */
    void generate_clock(void);
    /**
     * @brief envia pulso para latchear data del registro de desplazamiento
     *
     */
    void latch_data(void);

    /**
     * @brief envia un byte al registro de deplazamiento
     *
     * @param data byte a enviar
     */
    void send_byte(uint8_t data);

    /**
     * @brief envia una serie de bytes a los registros de desplazamiento en daisy chain
     *
     * @param buff puntero al vector de datos a enviar
     * @param qty cantidad de datos a enviar.
     */
    void send_buff(uint8_t * buff, uint8_t qty);


    /**
     * @brief refresca datos en los displays
     *
     * @param data buffer de datos que se muestra en los displays
     * @param format DECIMAL / HEXADECIMAL
     */
    void refresh_disp(uint16_t * data, uint8_t format);




#ifdef __cplusplus
}
#endif

#endif //__DISPLAY_H_