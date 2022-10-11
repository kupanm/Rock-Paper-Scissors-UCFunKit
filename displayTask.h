/** @file   displayTask.h
    @author David Liang
    @date   09/10/2022
    @brief  Controls navswitch task and update.
*/

#ifndef DISPLAYTASK_H
#define DISPLAYTASK_H

#include "pacer.h"

#define displayRATE 250

/**
 * Initialises the display.
 */
void displayTaskInit(pacer_rate_t pacerRate, uint16_t messageRate);

/** 
 * Increments display tick and checks if it is the appropriate 
 * time to execute the display task.
*/
void displayTaskCheck(pacer_rate_t pacerRate);

#endif