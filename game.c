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
#include "../fonts/font3x5_1.h"
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

/*Enum for the result of the game. Ongoing if it hasn't finished yet.*/
typedef enum  {
    ONGOING,
    WIN,
    LOSE,
    DRAW
} result_t;

/*Will display the operator that the player has chosen*/
void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/* Initialises everything required for the game.*/
void gameInit(void)
{
    system_init ();
    displayTaskInit(PACER_RATE, MESSAGE_RATE);
    irTaskInit();
    navTaskInit();
    buttonTaskInit();
    pacer_init(PACER_RATE);

    led_init();
    led_set(LED1, false);
}

/* Changes text font and rotation on game end.*/
void gameFinishedText(void)
{
    tinygl_font_set (&font3x5_1);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

/* Checks the result of the game.*/
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

/*Updates the game state if a result has been reached. Does nothing if game is still ongoing.*/
void updateState(result_t gameResult)
{
    if (gameResult != ONGOING) {
        gameFinishedText();
    }
    switch (gameResult) {
        case WIN:
            led_set(LED1, true);
            tinygl_text("  YOU WIN! \0");
            break;
        case LOSE:
            tinygl_text("  YOU LOSE! \0"); 
            break;
        case DRAW:
            tinygl_text("  DRAW! \0");
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
    bool displayHand = true;
    result_t gameResult = ONGOING;

    while(1) {
        pacer_wait();
        displayTaskCheck(PACER_RATE);
        navTaskCheck(PACER_RATE);

        player = selectHand(player);
        
        if (buttonTaskCheck(PACER_RATE)) {
            irPutTaskCheck(PACER_RATE, player);
            otherPlayer = 'S';
        }

        otherPlayer = irGetTaskCheck(PACER_RATE);
        
        if (!gameFinished) {
            gameResult = checkGameResult(player, otherPlayer);
            gameFinished = (gameResult == ONGOING) ? false : true;
            updateState(gameResult);
        }

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            displayHand = !displayHand;
        }

        if (!gameFinished && displayHand) {
            display_character(player);
        } else if (!gameFinished && !displayHand) {
            display_character(' ');
        }
    }   
}
