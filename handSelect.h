/** @file   handSelect.h
    @author David Liang
    @date   08/10/2022
    @brief  Hand selection in rock paper scissors game using navstick.
*/

#ifndef HANDSELECT_H
#define HANDSELECT_H

#include "system.h"
#include "navswitch.h"


#define ROCK navswitch_push_event_p(NAVSWITCH_SOUTH)
#define PAPER navswitch_push_event_p(NAVSWITCH_NORTH)
#define SCISSORS navswitch_push_event_p(NAVSWITCH_EAST)

/* Selects hand based on last navstick press */
char selectHand(void);

#endif