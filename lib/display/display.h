#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include <Arduino.h>
#include <util.h>

#define ON 1
#define OFF 0

#define col1 0
#define col2 1
#define col3 2
#define col4 3

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
     * @brief Prende/Apaga columna de displays
     *
     * @param column numero de columna
     * @param on prender o apagar
     */
    void set_column(uint8_t column, uint8_t on);


    /**
     * @brief refresca datos en los displays
     *
     * @param data buffer de datos que se muestra en los displays
     */
    void refresh_disp(uint16_t * data);




#ifdef __cplusplus
}
#endif

#endif //__DISPLAY_H_