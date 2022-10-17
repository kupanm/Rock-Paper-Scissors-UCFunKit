/** @file   ledModule.c
    @author David Liang and K.N. Mugutso
    @date   17/10/2022
    @brief  Controls LED tasks.
*/

#include "ledModule.h"
#include "led.h"

/**
 * @brief Initialises the LED.
 * 
 */
void ledInit(void)
{
    led_init();

    // Start with LED off.
    led_set(LED1, false);

}

/**
 * @brief Turns on the LED.
 * 
 */
void ledOn(void)
{
    led_set(LED1, true);
}

/**
 * @brief Turns off the LED.
 * 
 */
void ledOff(void)
{
    led_set(LED1, false);
}