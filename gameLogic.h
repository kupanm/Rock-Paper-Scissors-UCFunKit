/** @file   gameLogic.h
    @author David Liang and K.N. Mugutso
    @date   08/10/2022
    @brief  Contains all game logic.
*/

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdbool.h>
/* Selects hand based on last navstick press */
char selectHand(char player);

/*Will return true if the player has won based on whether
  they chose rock ('R'), paper ('P') or scissors ('S') */
bool isWon(char player, char otherPlayer);

/*Will return true if the player has lost*/
bool isLoss(char player, char otherPlayer);

/*Will return true if the player has drawn with the other player*/
bool isDraw(char player, char otherPlayer);

#endif
