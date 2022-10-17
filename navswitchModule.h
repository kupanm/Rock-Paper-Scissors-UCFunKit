/** @file   navswitchModule.h
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls navswitch task and updates.
*/

#ifndef NAVSWITCHMODULE_H
#define NAVSWITCHMODULE_H

#include "pacer.h"

#define NAVRATE 20

/**
 * @brief Initialises the navswitch and its ticker.
 * 
 */
void navInit(void);

/**
 * @brief Increments navswitch tick and checks if it is the appropriate 
 *        time to execute the navswitch task.
 * 
 * @param pacerRate The system pacer rate.
 */

void navTaskCheck(pacer_rate_t pacerRate);

/**
 * @brief Checks if rock input has been pushed (South)
 * 
 * @return true if the navswitch has been pushed south.
 * @return false outherwise.
 */
bool isRock(void);

/**
 * @brief Checks if scissors input has been pushed (East)
 * 
 * @return true if the navswitch has been pushed East.
 * @return false outherwise.
 */
bool isScissors(void);

/**
 * @brief Checks if paper input has been pushed (North)
 * 
 * @return true if the navswitch has been pushed North.
 * @return false outherwise.
 */
bool isPaper(void);

/**
 * @brief Checks if display hand has been toggled (inward push)
 * 
 * @return true if the navswitch has been pushed inwards.
 * @return false otherwise.
 */
bool toggleDisplayHand(void);

#endif