/** @file   game.c
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Primary game controller for a UCFK4 rock paper scissors game.
*/

#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "ir_uart.h"
#include "led.h"
#include "gameLogic.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"
#include <avr/io.h>
#include <stdbool.h>

#include "buttonModule.h"
#include "displayModule.h"
#include "irModule.h"
#include "navswitchModule.h"

#define PACER_RATE 500
#define MESSAGE_RATE 50
#define ROCK navswitch_push_event_p(NAVSWITCH_SOUTH)
#define PAPER navswitch_push_event_p(NAVSWITCH_NORTH)
#define SCISSORS navswitch_push_event_p(NAVSWITCH_EAST)

/* Initialises everything required for the game.*/
void gameInit(void)
{
    system_init ();
    displayInit(PACER_RATE, MESSAGE_RATE);
    irInit();
    navInit();
    buttonInit();
    pacer_init(PACER_RATE);

    led_init();
    led_set(LED1, false);
}

/*Updates the game state if a result has been reached. Does nothing if game is still ongoing.*/
void updateState(result_t gameResult)
{
    if (gameResult != ONGOING) {
        gameFinishedText();
    }
    switch (gameResult) {
        case WIN:
            led_set(LED1, true);
            setText("  YOU WIN! \0");
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

int main(void)
{
    gameInit();

    char player = 'X';
    char otherPlayer = 'Y';
    bool gameFinished = false;
    bool shouldDisplayHand = true;
    result_t gameResult = ONGOING;

    while(1) {
        pacer_wait();
        displayTaskCheck(PACER_RATE);
        navTaskCheck(PACER_RATE);

        player = selectHand(player);
        
        if (buttonTaskCheck(PACER_RATE)) {
            irPutTaskCheck(PACER_RATE, player);
        }

        otherPlayer = irGetTaskCheck(PACER_RATE);
        
        if (!gameFinished) {
            gameResult = checkGameResult(player, otherPlayer);
            gameFinished = (gameResult == ONGOING) ? false : true;
            updateState(gameResult);
        }

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            shouldDisplayHand = !shouldDisplayHand;
        }

        if (!gameFinished && shouldDisplayHand) {
            displayHand(player);
        } else if (!gameFinished && !shouldDisplayHand) {
            /* Hiding the player hand. */
            displayHand(' ');
        }
    }   
}
