/** @file   gameLogic.c
    @author David Liang and K.N. Mugutso
    @date   08/10/2022
    @brief  Contains all game logic.
*/

#include "system.h"
#include "gameLogic.h"
#include "navswitchModule.h"
#include "displayModule.h"
#include "ledModule.h"

#include <stdbool.h>

/**
 * @brief Checks if the player has won the game.
 * @param player The player's hand.
 * @param otherPlayer The opponent's hand.
 * @return true if the player wins the matchup.
 * @return false otherwise.
 */
bool isWon(char player, char otherPlayer)
{
    bool won = false;
    if (player == 'R' && otherPlayer == 'S') {
        won = true;
    }
    if (player == 'S' && otherPlayer == 'P') {
        won = true;    
    }
    if (player == 'P' && otherPlayer == 'R') {
        won = true;    
    }
    return won;
}

/**
 * @brief Checks if the player has lost the game.
 * @param player The player's hand.
 * @param otherPlayer The opponent's hand.
 * @return true if the player loses the matchup.
 * @return false otherwise.
 */
bool isLoss(char player, char otherPlayer)
{
    bool loss = false;
    if (player == 'R' && otherPlayer == 'P') {
        loss = true;    
    }
    if (player == 'S' && otherPlayer == 'R') {
        loss = true;    
    }
    if (player == 'P' && otherPlayer == 'S') {
        loss = true;    
    }
    return loss;
}   

/**
 * @brief Checks if the game has drawn.
 * @param player The player's hand.
 * @param otherPlayer The opponent's hand.
 * @return true if the player 's hand is the same as the opponent's.
 * @return false otherwise.
 */
bool isDraw(char player, char otherPlayer) 
{
    // X check to make sure game doesn't prematurely end.
    return (player == otherPlayer && player != 'X');
}

/**
 * @brief Selects hand based on last navstick press
 * 
 * @param player The player's original hand.
 * @return char The selected hand if a stick has been pressed.
 *              The player's original hand otherwise.
 */
char selectHand(char player)
{
    char handCharacter = player;
    if (isRock()) {
        handCharacter = 'R';
    }
    if (isPaper()) {
        handCharacter = 'P';
    }
    if (isScissors()) {
        handCharacter = 'S';
    }
    return handCharacter;
}

/**
 * @brief Checks the result of the game.
 * 
 * @param player The player's hand.
 * @param otherPlayer The opponent's hand.
 * @return result_t The result of the game. ONGOING if it hasn't changed.
 */
result_t checkGameResult(char player, char otherPlayer)
{
    result_t gameResult = ONGOING;
    if (isWon(player, otherPlayer)) {
        gameResult = WIN;
    }
    if (isLoss(player, otherPlayer)) {
        gameResult = LOSE;
    }
    if (isDraw(player, otherPlayer)) {
        gameResult = DRAW;
    }
    return gameResult;
}

/**
 * @brief Updates the game state if a result has been reached. 
 *        Does nothing if game is still ongoing.
 * 
 * @param gameResult The result of the current game.
 */
void updateState(result_t gameResult)
{
    if (gameResult != ONGOING) {
        // Prepare ledmat text for game end.
        setHorizontalText();
            ledOff();
    }
    switch (gameResult) {
        case WIN:
            setText("  YOU WIN! \0");
            ledOn();
            break;
        case LOSE:
            setText("  YOU LOSE! \0"); 
            break;
        case DRAW:
            setText("  DRAW! \0");
            break;
        default:
            break;
    }
}