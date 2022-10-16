/** @file   navswitchModule.c
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls navswitch task and updates.
*/

#include "navswitchModule.h"
#include "navswitch.h"
#include "pacer.h"

static uint8_t navTick;

/**
 * Initialises the navswitch and its ticker.
 */
void navInit(void)
{
    navswitch_init();
    navTick = 0;

}

/**
 * Updates the navswitch state.
 * 
 */
static void navTask(void)
{
    navswitch_update();
}

/** 
 * Increments navswitch tick and checks if it is the appropriate 
 * time to execute the navswitch task.
*/
void navTaskCheck(pacer_rate_t pacerRate)
{
    navTick++;
    if (navTick >= pacerRate/NAVRATE) {
        navTask();
        navTick = 0;
    }
}