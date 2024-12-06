
#ifndef __MOTOR_H_
#define __MOTOR_H_

#include <Arduino.h>
#include <util.h>

//#define     PUSH        1
#define     FORWARD     2
#define     BACKWARD    3
#define     LEFT        4
#define     RIGHT       5
#define     FRONT_LEFT  6
#define     FRONT_RIGHT 7

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * direction = FORWARD, BACKWARD, LEFT, RIGHT, FRONT_LEFT, FRONT_RIGHT
 * speed = 0 to 255
*/
void go(uint8_t direction, uint8_t speed);

/**
 * Speed 0 - 255
 */
void set_speed(uint8_t speed_L,uint8_t speed_R);


/**
 * initialize PWM on pins PD5 and PD6
 */
void motor_init();

#ifdef __cplusplus
}
#endif

#endif //__MOTOR_H_