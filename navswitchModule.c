/** @file   navswitchModule.c
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls navswitch task and updates.
*/

#include "navswitchModule.h"
#include "navswitch.h"
#include "pacer.h"

#include <stdbool.h>

static uint8_t navTick;

/**
 * @brief Initialises the navswitch and its ticker.
 * 
 */
void navInit(void)
{
    navswitch_init();
    navTick = 0;
}

/**
 * @brief Updates the navswitch state.
 * 
 */
static void navTask(void)
{
    navswitch_update();
}

/**
 * @brief Increments navswitch tick and checks if it is the appropriate 
 *        time to execute the navswitch task.
 * 
 * @param pacerRate The system pacer rate.
 */
void navTaskCheck(pacer_rate_t pacerRate)
{
    navTick++;
    if (navTick >= pacerRate/NAVRATE) {
        navTask();
        // Reset ticker.
        navTick = 0;
    }
}

/**
 * @brief Checks if rock input has been pushed (South)
 * 
 * @return true if the navswitch has been pushed south.
 * @return false outherwise.
 */
bool isRock(void)
{
    return navswitch_push_event_p(NAVSWITCH_SOUTH);
}

/**
 * @brief Checks if scissors input has been pushed (East)
 * 
 * @return true if the navswitch has been pushed East.
 * @return false outherwise.
 */
bool isScissors(void)
{
    return navswitch_push_event_p(NAVSWITCH_EAST);
}

/**
 * @brief Checks if paper input has been pushed (North)
 * 
 * @return true if the navswitch has been pushed North.
 * @return false outherwise.
 */
bool isPaper(void)
{
    return navswitch_push_event_p(NAVSWITCH_NORTH);
}

/**
 * @brief Checks if display hand has been toggled (inward push)
 * 
 * @return true if the navswitch has been pushed inwards.
 * @return false otherwise.
 */
bool toggleDisplayHand(void)
{
    return navswitch_push_event_p(NAVSWITCH_PUSH);
}