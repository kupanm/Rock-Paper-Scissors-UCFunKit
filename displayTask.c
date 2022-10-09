/** @file   displayTask.c
    @author David Liang
    @date   09/10/2022
    @brief  Controls display task rate and updates.
*/

#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#define displayRATE 250

static uint8_t displayTick;

/**
 * Initialises the display.
 */
void displayTaskInit(void)
{
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
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