#include "system.h"
#include "navswitch.h"
#include "button.h"
#include "ir_serial.h"
#include "handSelect.h"

int main (void)
{
    system_init ();
    navswitch_init();
    button_init();
    ir_serial_init();

    char playerHand;
    char opponentHand;

    while (1) {
        while (!button_release_event_p(BUTTONS_NUM))   {
            playerHand = seectHand();
        }
        ir_serial_transmit(playerHand);


    }
}
