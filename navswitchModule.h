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
 * Initialises the navswitch and its ticker.
 */
void navInit(void);

/** 
 * Increments navswitch tick and checks if it is the appropriate 
 * time to execute the navswitch task.
*/
void navTaskCheck(pacer_rate_t pacerRate);

#endif