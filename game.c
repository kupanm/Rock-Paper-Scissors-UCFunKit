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
#define MESSAGERATE 60

/**
 * @brief Initialises everything required for the game.
 * 
 */
static void gameInit(void)
{
    system_init();
    displayInit(PACERRATE, MESSAGERATE);
    irInit();
    navInit();
    buttonInit();
    ledInit();
    pacer_init(PACERRATE);
}

/**
 * @brief Plays one iteration of the main game loop.
 * 
 */
static void mainGame(void)
{
    char player = 'X';
    char otherPlayer = 'Y';
    char displayChar = player;
    bool handSent = false;
    bool gameFinished = false;
    bool shouldDisplayHand = true;
    bool endLoop = false;
    result_t gameResult = ONGOING;

    while(!endLoop) {
        pacer_wait();
        displayTaskCheck(PACERRATE);
        navTaskCheck(PACERRATE);

        if (!gameFinished) {

            player = selectHand(player);

            // Chooses to either display or hide the player's hand.
            displayChar = (shouldDisplayHand) ? player : ' ';
            displayHand(displayChar);

            // Gets opponent hand from IR if possible and haven't already gotten one.
            if (otherPlayer == 'Y') {
                otherPlayer = irGetTaskCheck(PACERRATE);
            }

            // Toggles displaying/hiding hand on the screen.
            if (toggleDisplayHand()) {
                shouldDisplayHand = !shouldDisplayHand;
            }

            // Sends hand through IR if button has been pressed.
            if (buttonTaskCheck(PACERRATE) && player != 'X') {
                irPutTaskCheck(PACERRATE, player);
                ledOn();
                handSent = true;
            }

            // Checks and updates the game state after sending player hand.
            if (handSent) {
                gameResult = checkGameResult(player, otherPlayer);
                gameFinished = (gameResult == ONGOING) ? false : true;
                updateState(gameResult);
            }

        } else if (buttonTaskCheck(PACERRATE)) {
            // Game has reached it's end state, button has been pushed to reset..
            setVerticalText();
            ledOff();
            endLoop = true;
        }
    }
}

/**
 * @brief Main game loop.
 * 
 * @return int The program exit state.
 */
int main(void)
{
    gameInit();
    while(1) {
        mainGame();
    }
}
