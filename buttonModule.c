/** @file   buttonModule.c
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls button task.
*/

#include "buttonModule.h"
#include "button.h"
#include "pacer.h"
#include <stdbool.h>

static uint8_t buttonTick;

/**
 * Initialises the button.
 */
void buttonTaskInit(void)
{
    button_init();
    buttonTick = 0;
}

/**
 * Updates the button state.
 * @returns bool in regards to if the button has been pushed.
 */
static bool buttonTask(void)
{
    bool buttonPushed = false;
    button_update();
    if (button_push_event_p(BUTTON1)) {
        buttonPushed = true;
    }
    return buttonPushed;
}

/** 
 * Increments navswitch tick and checks if it is the appropriate 
 * time to execute the navswitch task.
 * @returns bool in regards to if the button has been pushed.
*/
bool buttonTaskCheck(pacer_rate_t pacerRate)
{
    buttonTick++;
    bool buttonPushed = false;
    if (buttonTick >= pacerRate/BUTTONRATE) {
        buttonPushed = buttonTask();
        buttonTick = 0;
    }
    return buttonPushed;
}