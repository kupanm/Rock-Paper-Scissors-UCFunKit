/** @file   displayModule.h
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls display task and updates.
*/

#ifndef DISPLAYMODULE_H
#define DISPLAYMODULE_H

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