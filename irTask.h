/** @file   irTask.h
    @author David Liang
    @date   09/10/2022
    @brief  Controls IR tasks.
*/

#ifndef IRTASK_H
#define IRTASK_H

#include "pacer.h"

/**
 * Initialises IR communication.
 * 
 */
void irTaskInit(void);

/**
 * Sends a character. 
 */
static void irPutTask(char sendChar);

/** 
 * Increments IR put tick and checks if it is the appropriate 
 * time to execute the IR put task.
*/
void irPutTaskCheck(pacer_rate_t pacerRate, char sendChar);

/**
 * Receives a character if there is one available. 
 * Otherwise, returns dummy character X.
 * @return the character received or X.
 */
static char irGetTask(void);

/** 
 * Increments IR get tick and checks if it is the appropriate 
 * time to execute the IR get task.
 * @return the character received or X.
*/
char irGetTaskCheck(pacer_rate_t pacerRate);

#endif