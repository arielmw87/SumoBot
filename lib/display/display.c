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
    bit_set(PORTB, PB2);
    asm("NOP");
    bit_clear(PORTB, PB2);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void latch_data(void)
{

    asm("NOP");
    bit_set(PORTB, PB3);
    asm("NOP");
    bit_clear(PORTB, PB3);
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
            bit_set(PORTB, PB1);
        }
        else
        {
            bit_clear(PORTB, PB1);
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
void set_column(uint8_t column, uint8_t on)
{

    switch (column)
    {
    //================================
    case col1:
        if (on==ON)
        {
            bit_set(PORTF, PF7);
        }
        else
        {
            bit_clear(PORTF, PF7);
        }
        break;
    //================================
    case col2:
        if (on==ON)
        {
            bit_set(PORTF, PF6);
        }
        else
        {
            bit_clear(PORTF, PF6);
        }
        break;
    //================================
    case col3:
        if (on==ON)
        {
            bit_set(PORTF, PF5);
        }
        else
        {
            bit_clear(PORTF, PF5);
        }
        break;
    //================================
    case col4:
        if (on==ON)
        {
            bit_set(PORTF, PF4);
        }
        else
        {
            bit_clear(PORTF, PF4);
        }
        break;
        //================================

    default:
        break;
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void refresh_disp(uint16_t *data)
{
    static uint8_t mux = 0;
    uint8_t outbuff[5];

    switch (mux)
    {
    //================================
    case col1:
        for(uint8_t i=0;i<5;i++){
            outbuff[i] = SEVEN_SEG_DIGITS[data[i] / 1000 % 10];
        }
        set_column(col4, OFF);
        send_buff(&outbuff[0],5);
        latch_data();
        set_column(col1, ON);
        mux= col2;
        break;
    //================================
    case col2:
        for(uint8_t i=0;i<5;i++){
            outbuff[i]=SEVEN_SEG_DIGITS[data[i]/100%10];
        }
        set_column(col1, OFF);
        send_buff(&outbuff[0],5);
        latch_data();
        set_column(col2, ON);
        mux=col3;
        break;
    //================================
    case col3:
        for(uint8_t i=0;i<5;i++){
            outbuff[i]=SEVEN_SEG_DIGITS[data[i]/10%10];
        }
        set_column(col2, OFF);
        send_buff(&outbuff[0],5);
        latch_data();
        set_column(col3, ON);
        mux=col4;
        break;
    //================================
    case col4:
        for(uint8_t i=0;i<5;i++){
            outbuff[i]=SEVEN_SEG_DIGITS[data[i]%10];
        }
        set_column(col3, OFF);
        send_buff(&outbuff[0],5);
        latch_data();
        set_column(col4, ON);
        mux = col1;
        break;
    //================================

    default:
        break;
    }




}