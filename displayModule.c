/** @file   displayModule.c
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls display tasks, actions, and updates.
*/

#include "displayModule.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "../fonts/font3x5_1.h"


static uint8_t displayTick;

/**
 * @brief Sets text font and rotation to vertical on ledmat.
 * 
 */
void setVerticalText(void)
{
    tinygl_font_set (&font5x7_1);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_NORMAL);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
}

/**
 * @brief Changes text font and rotation to horizontal on ledmat on game end.
 * 
 */
void setHorizontalText(void)
{
    tinygl_font_set (&font3x5_1);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

/**
 * @brief Initialises the display and its ticker
 * 
 * @param pacerRate The rate of the system pacer.
 * @param messageRate The scrolling rate of the message.
 */
void displayInit(pacer_rate_t pacerRate, uint16_t messageRate)
{
    tinygl_init (pacerRate);
    tinygl_text_speed_set (messageRate);
    setVerticalText();
    displayTick = 0;

}

/**
 * @brief Updates the display state.
 * 
 */
static void displayTask(void)
{
    tinygl_update();
}

/**
 * @brief Increments display tick and checks if it is the appropriate 
 *        time to execute the display task.
 * 
 * @param pacerRate The rate of the system pacer.
 */
void displayTaskCheck(pacer_rate_t pacerRate)
{
    displayTick++;
    if (displayTick >= pacerRate/displayRATE) {
        displayTask();
        // Reset ticker.
        displayTick = 0;
    }
}

/**
 * @brief Displays the player's hand on the LedMat.
 * 
 * @param hand The player's hand to display.
 */
void displayHand(char hand)
{
    // Convert char to string so it can be displayed.
    char handString[2] = {hand, '\0'};
    tinygl_text (handString);
}

/**
 * @brief Displays a scrolling message on the LedMat.
 * 
 * @param text The message to display.
 */
void setText(char* text)
{
    tinygl_text(text);
}
