/** @file   irTask.h
    @author David Liang
    @date   09/10/2022
    @brief  Controls IR tasks.
*/

#ifndef IRTASK_H
#define IRTASK_H

#include "pacer.h"

#define IRPUTRATE 500
#define IRGETRATE 100

/**
 * Initialises IR communication.
 * 
 */
void irTaskInit(void);

/** 
 * Increments IR put tick and checks if it is the appropriate 
 * time to execute the IR put task.
*/
void irPutTaskCheck(pacer_rate_t pacerRate, char sendChar);

/** 
 * Increments IR get tick and checks if it is the appropriate 
 * time to execute the IR get task.
 * @return the character received or Y.
*/
char irGetTaskCheck(pacer_rate_t pacerRate);

#endif