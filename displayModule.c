/** @file   displayModule.c
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls display task and updates.
*/

#include "displayModule.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


static uint8_t displayTick;

/**
 * Initialises the display.
 */
void displayTaskInit(pacer_rate_t pacerRate, uint16_t messageRate)
{
    tinygl_init (pacerRate);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (messageRate);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    displayTick = 0;

}

/**
 * Updates the display state.
 * 
 */
static void displayTask(void)
{
    tinygl_update();
}

/** 
 * Increments display tick and checks if it is the appropriate 
 * time to execute the display task.
*/
void displayTaskCheck(pacer_rate_t pacerRate)
{
    displayTick++;
    if (displayTick >= pacerRate/displayRATE) {
        displayTask();
        displayTick = 0;
    }
}