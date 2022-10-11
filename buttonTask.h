/** @file   buttonTask.h
    @author David Liang
    @date   09/10/2022
    @brief  Controls button task.
*/

#ifndef BUTTONTASK_H
#define BUTTONTASK_H

#include "pacer.h"

#define BUTTONRATE 20

/**
 * Initialises the button.
 */
void buttonTaskInit(void);

/** 
 * Increments navswitch tick and checks if it is the appropriate 
 * time to execute the navswitch task.
 * @returns bool in regards to if the button has been pushed.
*/
bool buttonTaskCheck(pacer_rate_t pacerRate);

#endif