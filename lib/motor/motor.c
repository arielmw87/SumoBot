#include <motor.h>

void go(uint8_t direction, uint8_t speed)
{

    set_speed(0);

    switch (direction)
    {
    //---------------------
    case FORWARD:
        break;
    //---------------------
    case BACKWARD:
        break;
    //---------------------
    case LEFT:
        break;
    //---------------------
    case RIGHT:
        break;
        //---------------------

    default:
        speed=0;
        break;
    }

    set_speed(speed);
}

void set_speed(uint8_t speed)
{

    //setear PWM

}
