/** @file   maingame.c
    @author K.N. Mugutso
    @date   08 Oct 2022
    @brief  Main game (just is won or draw or loss).
    @note   This will just see if the game has resulted in a win, loss or draw for the specific player.
*/

#include <stdbool.h>

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

bool isDraw(char player, char otherPlayer) 
{
    return (player == otherPlayer);
}
