/** @file   buttonTask.c
    @author David Liang
    @date   09/10/2022
    @brief  Controls button task.
*/

#include "button.h"
#include "pacer.h"
#include <stdbool.h>
#define NAVRATE 20

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
    if (button_push_event()) {
        buttonPushed = true;
    }
    return buttonPushed;
}

/** 
 * Increments navswitch tick and checks if it is the appropriate 
 * time to execute the navswitch task.
 * @returns bool in regards to if the button has been pushed.
*/
bool navTaskCheck(pacer_rate_t pacerRate)
{
    buttonTick++;
    bool buttonPushed = false;
    if (buttonTick >= pacerRate/NAVRATE) {
        buttonPushed = buttonTask();
        buttonTick = 0;
    }
    return buttonPushed;
}