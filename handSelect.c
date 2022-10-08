/** @file   handSelect.c
    @author David Liang
    @date   08/10/2022
    @brief  Hand selection in rock paper scissors game using navstick.
*/

#include "system.h"


/* Selects hand based on last navstick press */
char selectHand(void)
{
    char handCharacter;
    navswitch_update();
    if (ROCK) {
        handCharacter = 'R';
    }
    if (PAPER) {
        handCharacter = 'P';
    }
    if (SCISSORS) {
        handCharacter = 'S';
    }
    return handCharacter;
}