#include <display.h>


#include <stdio.h>
#include <stdint.h>

/*
 Segment layout:
      A
     ---
  F |   | B
     -G-
  E |   | C
     ---
      D

*/

// Using uint8_t to ensure we have exactly 8 bits
const uint8_t SEVEN_SEG_DIGITS[] = {

    // CDEGFAB

    // CDEGFAB
    0b01110111,  // 0: ABCDEF
    0b01000001,  // 1: BC
    0b00111011,  // 2: ABGED
    0b01101011,  // 3: ABGCD
    0b01001101,  // 4: FGBC
    0b01101110,  // 5: AFGCD
    0b01111110,  // 6: AFGEDC
    0b01000011,  // 7: ABC
    0b01111111,  // 8: ABCDEFG
    0b01101111,   // 9: ABFGCD
    0b01011111,  // A: ABCEFG
    0b01111100,  // b: CDEFG
    0b00110110,  // C: ADEF
    0b01111001,  // d: BCDEG
    0b00111110,  // E: ADEFG
    0b00011110   // F: AEFG
};


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void generate_clock(void)
{
    asm("NOP");
    clk_line_set;
    asm("NOP");
    clk_line_clear;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void latch_data(void)
{

    asm("NOP");
    latch_line_set;
    asm("NOP");
    latch_line_clear;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void send_byte(uint8_t data)
{

    for (uint8_t i = 0; i < 8; i++)
    {
        if ((data & 0x01) != 0)
        {
            data_line_set;
        }
        else
        {
            data_line_clear;
        }
        data>>=1;

        generate_clock();
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void send_buff(uint8_t *buff, uint8_t qty)
{

    for (uint8_t i = 0; i < qty; i++)
    {
        send_byte(buff[i]);
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void refresh_disp(uint16_t *data, uint8_t format)
{
    static uint8_t mux = 0;
    uint8_t outbuff[5];

    switch (mux)
    {
    //================================
    case col1:
        for(uint8_t i=0;i<5;i++){
            if(format == DECIMAL){outbuff[i] = SEVEN_SEG_DIGITS[data[i] / 1000 % 10];}
            if(format == HEXADECIMAL){outbuff[i] = SEVEN_SEG_DIGITS[data[i] / 4096 % 16];}
        }
        col4_off;
        send_buff(&outbuff[0],5);
        latch_data();
        col1_on;
        mux= col2;
        break;
    //================================
    case col2:
        for(uint8_t i=0;i<5;i++){
            if(format == DECIMAL){outbuff[i] = SEVEN_SEG_DIGITS[data[i] / 100 % 10];}
            if(format == HEXADECIMAL){outbuff[i] = SEVEN_SEG_DIGITS[data[i] / 256 % 16];}
        }
        col1_off;
        send_buff(&outbuff[0],5);
        latch_data();
        col2_on;
        mux=col3;
        break;
    //================================
    case col3:
        for(uint8_t i=0;i<5;i++){
            if(format == DECIMAL){outbuff[i] = SEVEN_SEG_DIGITS[data[i] / 10 % 10];}
            if(format == HEXADECIMAL){outbuff[i] = SEVEN_SEG_DIGITS[data[i] / 16 % 16];}
        }
        col2_off;
        send_buff(&outbuff[0],5);
        latch_data();
        col3_on;
        mux=col4;
        break;
    //================================
    case col4:
        for(uint8_t i=0;i<5;i++){
            if(format == DECIMAL){outbuff[i] = SEVEN_SEG_DIGITS[data[i] % 10];}
            if(format == HEXADECIMAL){outbuff[i] = SEVEN_SEG_DIGITS[data[i] % 16];}
        }
        col3_off;
        send_buff(&outbuff[0],5);
        latch_data();
        col4_on;
        mux = col1;
        break;
    //================================

    default:
        break;
    }




}