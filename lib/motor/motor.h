
#ifndef __MOTOR_H_
#define __MOTOR_H_

#include <Arduino.h>
#include <util.h>

#define     FORWARD     1
#define     BACKWARD    2
#define     LEFT        3
#define     RIGHT       4

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * direction = FORWARD, BACKWARD, LEFT, RIGTH
 * speed = 0 to 255
*/
void go(uint8_t direction, uint8_t speed);

void set_speed(uint8_t speed);

#ifdef __cplusplus
}
#endif

#endif //__MOTOR_H_