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
#include <ctype.h>

#define PACER_RATE 500
#define MESSAGE_RATE 10
#define ROCK navswitch_push_event_p(NAVSWITCH_SOUTH)
#define PAPER navswitch_push_event_p(NAVSWITCH_NORTH)
#define SCISSORS navswitch_push_event_p(NAVSWITCH_EAST)

/*will display the operator that the player has chosen*/
void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

int main(void)
{
    system_init ();

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    led_init();
    led_set(LED1, false);
    ir_uart_init();
    navswitch_init();
    pacer_init (PACER_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    char player;
    char otherPlayer;
    button_init();
    bool gameFinished = false;
    while(1) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update();
        button_update();
        if (ROCK) {
        	player = 'R';
		}
		if (PAPER) {
		    player = 'P';
		}
		if (SCISSORS) {
		    player = 'S';
		}
        // display_character(player);
        if (button_push_event_p(BUTTON1)) {
            ir_uart_putc(player);  
            led_set(LED1, true);     
        }
        if (ir_uart_read_ready_p())
        {
            char ch = ir_uart_getc();
            if (isprint(ch)) {
                otherPlayer = ch;
            }
        }
        if (isWon(player, otherPlayer) && !gameFinished) {
            led_set(LED1, true);
            tinygl_text("You Win!\0");
            gameFinished = true;
        }
        if (isLoss(player, otherPlayer) && !gameFinished) {
            tinygl_text("You Lose!\0"); 
            gameFinished = true;
        }
        if (isDraw(player, otherPlayer) && !gameFinished) {
        	tinygl_text("Draw!\0");
            gameFinished = true;
        }
    }   
}
