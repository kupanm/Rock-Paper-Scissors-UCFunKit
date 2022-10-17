/** @file   irModule.h
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls IR communication task and updates.
*/

#ifndef IRMODULE_H
#define IRMODULE_H

#include "pacer.h"

#define IRPUTRATE 500
#define IRGETRATE 100

/**
 * @brief Initialises IR communication and their tickers.
 * 
 */
void irInit(void);

/**
 * @brief Increments IR put tick and checks if it is the appropriate 
 *        time to execute the IR put task.
 * 
 * @param pacerRate The system pacer rate.
 * @param sendChar The character to send.
 */
void irPutTaskCheck(pacer_rate_t pacerRate, char sendChar);

/**
 * @brief Increments IR get tick and checks if it is the appropriate 
 *        time to execute the IR get task.
 * 
 * @param pacerRate The system pacer rate.
 * @return char The character received or Y.
 */
char irGetTaskCheck(pacer_rate_t pacerRate);

#endif