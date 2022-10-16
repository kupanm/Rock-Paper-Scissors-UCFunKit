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
 * Initialises the display and its ticker.
 */
void displayInit(pacer_rate_t pacerRate, uint16_t messageRate);

/** 
 * Increments display tick and checks if it is the appropriate 
 * time to execute the display task.
*/
void displayTaskCheck(pacer_rate_t pacerRate);

/* Displays the player's hand on the LedMat.*/
void displayHand(char hand);

/* Displays a scrolling message on the LedMat. */
void setText(char* text);

/* Changes text font and rotation on LedMat on game end.*/
void gameFinishedText(void);

#endif