#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "ir_uart.h"
#include "led.h"
#include "handSelect.h"
#include "gameLogic.h"

#include <stdbool.h>

int main (void)
{
    system_init ();
    navswitch_init();
    button_init();
    ir_uart_init();
    led_init();

    char playerHand = 0;
    char opponentHand;

    while (1) {

        led_set(LED1, false);

        while (!button_release_event_p(BUTTON1) && playerHand == 0) {
            playerHand = selectHand();
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
