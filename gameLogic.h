/** @file   gameLogic.h
    @author David Liang and K.N. Mugutso
    @date   08/10/2022
    @brief  Contains all game logic.
*/

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <stdbool.h>

/**
 * @brief Enum for the result of the game. 
 *        Ongoing if it hasn't finished yet.
 * 
 */
typedef enum  {
    ONGOING,
    WIN,
    LOSE,
    DRAW
} result_t;

/**
 * @brief Checks if the player has win the game.
 * @param player The player's hand.
 * @param otherPlayer The opponent's hand.
 * @return true if the player wins the matchup.
 * @return false otherwise.
 */
bool isWon(char player, char otherPlayer);

/**
 * @brief Checks if the player has lost the game.
 * @param player The player's hand.
 * @param otherPlayer The opponent's hand.
 * @return true if the player loses the matchup.
 * @return false otherwise.
 */
bool isLoss(char player, char otherPlayer);

/**
 * @brief Checks if the game has drawn.
 * @param player The player's hand.
 * @param otherPlayer The opponent's hand.
 * @return true if the player 's hand is the same as the opponent's.
 * @return false otherwise.
 */
bool isDraw(char player, char otherPlayer);

/**
 * @brief Selects hand based on last navstick press
 * 
 * @param player The player's original hand.
 * @return char The selected hand if a stick has been pressed.
 *              The player's original hand otherwise.
 */
char selectHand(char player);

/**
 * @brief Checks the result of the game.
 * 
 * @param player The player's hand.
 * @param otherPlayer The opponent's hand.
 * @return result_t The result of the game. ONGOING if it hasn't changed.
 */
result_t checkGameResult(char player, char otherPlayer);

/**
 * @brief Updates the game state if a result has been reached. 
 *        Does nothing if game is still ongoing.
 * 
 * @param gameResult The result of the current game.
 */
void updateState(result_t gameResult);

#endif
