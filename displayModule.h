/** @file   displayModule.h
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls display tasks, actions, and updates.
*/

#ifndef DISPLAYMODULE_H
#define DISPLAYMODULE_H

#include "pacer.h"

#define displayRATE 250

/**
 * @brief Sets text font and rotation to vertical on ledmat.
 * 
 */
void setVerticalText(void);

/**
 * @brief Changes text font and rotation to horizontal on ledmat on game end.
 * 
 */
void setHorizontalText(void);

/**
 * @brief Initialises the display and its ticker
 * 
 * @param pacerRate The rate of the system pacer.
 * @param messageRate The scrolling rate of the message.
 */
void displayInit(pacer_rate_t pacerRate, uint16_t messageRate);

/**
 * @brief Increments display tick and checks if it is the appropriate 
 *        time to execute the display task.
 * 
 * @param pacerRate The rate of the system pacer.
 */
void displayTaskCheck(pacer_rate_t pacerRate);

/**
 * @brief Displays the player's hand on the LedMat.
 * 
 * @param hand The player's hand to display.
 */
void displayHand(char hand);

/**
 * @brief Displays a scrolling message on the LedMat.
 * 
 * @param text The message to display.
 */
void setText(char* text);

#endif