/** @file   buttonModule.h
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls button task.
*/

#ifndef BUTTONMODULE_H
#define BUTTONMODULE_H

#include "pacer.h"

#define BUTTONRATE 20

/**
 * Initialises the button.
 */
void buttonInit(void);

/** 
 * Increments button tick and checks if it is the appropriate 
 * time to execute the button task.
 * @returns bool in regards to if the button has been pushed.
*/
bool buttonTaskCheck(pacer_rate_t pacerRate);

#endif