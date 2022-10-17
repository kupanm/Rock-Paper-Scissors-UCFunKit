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
 * @brief Initialises the button and its ticker
 * 
 */
void buttonInit(void)
{
    button_init();
    buttonTick = 0;
}

/**
 * @brief Updates the button state and checks if it's been pushed.
 * 
 * @return true if the button has been pushed.
 * @return false otherwise.
 */
static bool buttonTask(void)
{
    bool buttonPushed = false;
    button_update();
    if (button_push_event_p(BUTTON1)) {
        // Button has been pushed.
        buttonPushed = true;
    }
    return buttonPushed;
}

/**
 * @brief Increments button tick and checks if it is the appropriate 
 *        time to execute the button task.
 * 
 * @param pacerRate The pacer rate of the system.
 * @return true if the button has been pushed.
 * @return false otherwise.
 */
bool buttonTaskCheck(pacer_rate_t pacerRate)
{
    buttonTick++;
    bool buttonPushed = false;
    if (buttonTick >= pacerRate/BUTTONRATE) {
        buttonPushed = buttonTask();
        // Reset ticker.
        buttonTick = 0;
    }
    return buttonPushed;
}