/** @file   gameLogic.c
    @author K.N. Mugutso
    @date   08 Oct 2022
    @brief  Main game (just is won or draw or loss).
    @note   This will just see if the game has resulted in a win, loss or draw for the specific player.
*/

#include <stdbool.h>
#include "system.h"
#include "navswitch.h"
#include "gameLogic.h"

#define ROCK navswitch_push_event_p(NAVSWITCH_SOUTH)
#define PAPER navswitch_push_event_p(NAVSWITCH_NORTH)
#define SCISSORS navswitch_push_event_p(NAVSWITCH_EAST)


/* Selects hand based on last navstick press */
//char selectHand(void)
//{
//    char handCharacter;
//    navswitch_update();
//    if (ROCK) {
//        handCharacter = 'R';
//    }
//    if (PAPER) {
//        handCharacter = 'P';
//    }
//    if (SCISSORS) {
//        handCharacter = 'S';
//    }
//    return handCharacter;
//}

/*Will return true if the player has won based on whether
  they chose rock ('R'), paper ('P') or scissors ('S') */
bool isWon(char player, char otherPlayer)
{
    bool won = false;
    if (player == 'R' && otherPlayer == 'S') {
        won = true;
    } else if (player == 'S' && otherPlayer == 'P') {
        won = true;    
    } else if (player == 'P' && otherPlayer == 'R') {
        won = true;    
    }
    return won;
}

/*Will return true if the player has lost*/
bool isLoss(char player, char otherPlayer)
{
    bool loss = false;
    if (player == 'R' && otherPlayer == 'P') {
        loss = true;    
    } else if (player == 'S' && otherPlayer == 'R') {
        loss = true;    
    } else if (player == 'P' && otherPlayer == 'S') {
        loss = true;    
    }
    return loss;
}   

/*Will return true if the player has drawn with the other player*/
bool isDraw(char player, char otherPlayer) 
{
    return (player == otherPlayer);
}
