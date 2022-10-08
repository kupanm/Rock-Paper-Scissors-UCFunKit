#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "ir_uart.h"
#include "led.h"
#include "handSelect.h"
#include "gameLogic.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"

#include <stdbool.h>

#define PACER_RATE 500
#define MESSAGE_RATE 10
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


int main (void)
{
    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    navswitch_init();
    button_init();
    ir_uart_init();
    led_init();
    pacer_init(PACER_RATE);

    char playerHand = 'A';
    char opponentHand;

    while (1) {

        led_set(LED1, false);
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        display_character(playerHand);

        while (!button_release_event_p(BUTTON1) && playerHand == 0) {
            playerHand = selectHand();
            tinygl_update();
            display_character(playerHand);
            button_update();
        }

        ir_uart_putc(playerHand);
        while (!ir_uart_read_ready_p()) {
            continue;
        }
        opponentHand = ir_uart_getc();

        if (isWon(playerHand, opponentHand)) {
            led_set(LED1, true);
        }
        
        while (!button_release_event_p(BUTTON1)) {
            button_update();
        }
    }
}
