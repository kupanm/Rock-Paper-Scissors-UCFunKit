/** @file   game.c
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Primary game controller for a UCFK4 rock paper scissors game.
*/

#include "system.h"
#include "gameLogic.h"
#include "buttonModule.h"
#include "displayModule.h"
#include "irModule.h"
#include "navswitchModule.h"
#include "ledModule.h"

#include <avr/io.h>
#include <stdbool.h>

#define PACERRATE 500
#define MESSAGERATE 50

/**
 * @brief Initialises everything required for the game.
 * 
 */
static void gameInit(void)
{
    system_init ();
    displayInit(PACERRATE, MESSAGERATE);
    irInit();
    navInit();
    buttonInit();
    ledInit();
    pacer_init(PACERRATE);

}

/**
 * @brief Main game loop.
 * 
 * @return int The program exit state.
 */
int main(void)
{
    gameInit();

    char player = 'X';
    char otherPlayer = 'Y';
    char displayChar = player;
    bool handSent = false;
    bool gameFinished = false;
    bool shouldDisplayHand = true;
    result_t gameResult = ONGOING;

    while(1) {
        pacer_wait();
        displayTaskCheck(PACERRATE);
        navTaskCheck(PACERRATE);

        player = selectHand(player);
        
        if (buttonTaskCheck(PACERRATE) && player != 'X') {
            irPutTaskCheck(PACERRATE, player);
            ledOn();
            handSent = true;
        }

        if (otherPlayer == 'Y') {
            otherPlayer = irGetTaskCheck(PACERRATE);
        }

        if (!gameFinished && handSent) {
            gameResult = checkGameResult(player, otherPlayer);
            gameFinished = (gameResult == ONGOING) ? false : true;
            updateState(gameResult);
        }
        if (toggleDisplayHand()) {
            shouldDisplayHand = !shouldDisplayHand;
        }

        /* Choose character to be displayed on the screen.
           Either the player's hand, or blank to hide it. */
        displayChar = (shouldDisplayHand) ? player : ' ';
        if (!gameFinished) {
            displayHand(displayChar);
        }
    }   
}
