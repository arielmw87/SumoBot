#include <motor.h>


void go(uint8_t direction, uint8_t speed)
{
    set_speed(0,0);

    switch (direction)
    {
    //---------------------
    case FORWARD:
        //MOTOR R
        bit_set(PORTD,PD2);
        bit_clear(PORTD,PD4);
        //MOTOR L
        bit_set(PORTD,PD2);
        bit_clear(PORTD,PD4);

        set_speed(speed,speed);
        break;
    //---------------------
    case BACKWARD:
        //MOTOR R
        bit_clear(PORTD,PD2);
        bit_set(PORTD,PD4);
        //MOTOR L
        bit_clear(PORTD,PD2);
        bit_set(PORTD,PD4);

        set_speed(speed,speed);
        break;
    //---------------------
    case LEFT:
        //MOTOR R
        bit_clear(PORTD,PD2);
        bit_set(PORTD,PD4);
        //MOTOR L
        bit_set(PORTD,PD2);
        bit_clear(PORTD,PD4);
        set_speed(speed,speed);
        break;
    //---------------------
    case RIGHT:
        //MOTOR R
        bit_set(PORTD,PD2);
        bit_clear(PORTD,PD4);

        //MOTOR L
        bit_clear(PORTD,PD2);
        bit_set(PORTD,PD4);

        set_speed(speed,speed);
        break;
    //---------------------
    case FRONT_LEFT:
        //MOTOR R
        bit_set(PORTD,PD2);
        bit_clear(PORTD,PD4);
        //MOTOR L
        bit_set(PORTD,PD2);
        bit_clear(PORTD,PD4);

        set_speed(speed/2,speed);
        break;
    //---------------------
    case FRONT_RIGHT:
        //MOTOR R
        bit_set(PORTD,PD2);
        bit_clear(PORTD,PD4);
        //MOTOR L
        bit_set(PORTD,PD2);
        bit_clear(PORTD,PD4);

        set_speed(speed,speed/2);
        break;
    //---------------------

    default:
        break;
    }

}

void set_speed(uint8_t speed_L, uint8_t speed_R)
{
    OCR0A = speed_R;  // 0-255 -> 0-100% de duty cycle para PD6
    OCR0B = speed_L;  // 0-255 -> 0-100% de duty cycle para PD5
}



void motor_init(){
    // Configurar los pines PD5 y PD6 como salidas
    DDRD |= (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7);
    PORTD &= ~( (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7) );
    
    // Configurar Timer 0 en modo Fast PWM
    TCCR0A |= (1 << WGM00) | (1 << WGM01);  // Modo Fast PWM
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);  // Comparar salida en modo no inverso para OC0A y OC0B
    TCCR0B |= (1 << CS01) | (1 << CS00);  // Prescaler de 64
    //frec = 16Mz / ( prescaler * 256 )
    //frec = 16Mz / (64*256) = 976.56Hz

    // Establecer el duty cycle inicial (50% por ejemplo)
    OCR0A = 0;  // 0% de duty cycle para PD6
    OCR0B = 0;  // 0% de duty cycle para PD5
}





