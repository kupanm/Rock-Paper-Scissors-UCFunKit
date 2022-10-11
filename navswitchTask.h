/** @file   navswitchTask.h
    @author David Liang
    @date   09/10/2022
    @brief  Controls navswitch task and update.
*/

#ifndef NAVSWITCHTASK_H
#define NAVSWITCHTASK_H

#include "pacer.h"

#define NAVRATE 20

/**
 * Initialises the navswitch.
 */
void navTaskInit(void);

/** 
 * Increments navswitch tick and checks if it is the appropriate 
 * time to execute the navswitch task.
*/
void navTaskCheck(pacer_rate_t pacerRate);

#endif