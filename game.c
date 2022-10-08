#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "ir_serial.h"
#include "led.h"
#include "handSelect.h"
#include "main"

#include <stdbool.h>

int main (void)
{
    system_init ();
    navswitch_init();
    button_init();
    ir_serial_init();
    led_init();

    char playerHand;
    char opponentHand;
    ir_serial_ret receiveErrorCode;

    while (1) {

        while (!button_release_event_p(BUTTONS_NUM))   {
            playerHand = selectHand();
            button_update();
        }

        ir_serial_transmit(playerHand);
        receiveErrorCode = ir_serial_receive(&opponentHand);

        if (receiveErrorCode == IR_SERIAL_OK) {
            if (isWon(playerHand, opponentHand)) {
                led_set(LED1, true);
            }
        }
    }
}
