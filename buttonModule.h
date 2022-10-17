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
 * @brief Initialises the button and its ticker
 * 
 */
void buttonInit(void);

/**
 * @brief Increments button tick and checks if it is the appropriate 
 *        time to execute the button task.
 * 
 * @param pacerRate The pacer rate of the system.
 * @return true if the button has been pushed.
 * @return false otherwise.
 */
bool buttonTaskCheck(pacer_rate_t pacerRate);

#endif