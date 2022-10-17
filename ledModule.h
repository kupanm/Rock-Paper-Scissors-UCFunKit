/** @file   ledModule.h
    @author David Liang and K.N. Mugutso
    @date   17/10/2022
    @brief  Controls LED tasks.
*/

#ifndef LEDMODULE_H
#define LEDMODULE_H

/**
 * @brief Initialises the LED.
 * 
 */
void ledInit(void);

/**
 * @brief Turns on the LED.
 * 
 */
void ledOn(void);

/**
 * @brief Turns off the LED.
 * 
 */
void ledOff(void);

#endif