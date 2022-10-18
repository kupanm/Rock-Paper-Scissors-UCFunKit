/** @file   irModule.c
    @author David Liang and K.N. Mugutso
    @date   09/10/2022
    @brief  Controls IR communication task and updates.
*/

#include "irModule.h"
#include "pacer.h"
#include "ir_uart.h"

#include <ctype.h>

static uint8_t irPutTick;
static uint8_t irGetTick;

/**
 * @brief Initialises IR communication and their tickers.
 * 
 */
void irInit(void)
{
    ir_uart_init();
    irPutTick = 0;
    irGetTick = 0;
}

/**
 * @brief Sends a character to another UCFK4.
 * 
 * @param sendChar The character to send.
 */
static void irPutTask(char sendChar)
{
    ir_uart_putc(sendChar);
}

/**
 * @brief Increments IR put tick and checks if it is the appropriate 
 *        time to execute the IR put task.
 * 
 * @param pacerRate The system pacer rate.
 * @param sendChar The character to send.
 */
void irPutTaskCheck(pacer_rate_t pacerRate, char sendChar)
{
    irPutTick++;
    if (irPutTick >= pacerRate/IRPUTRATE) {
        irPutTask(sendChar);
        // Reset ticker.
        irPutTick = 0;
    }
}

/**
 * @brief Receives a character if there is one available. 
 * Otherwise, returns dummy character Y.
 * 
 * @return char The character received or Y.
 */
static char irGetTask(void)
{
    char receiveChar = 'Y';
    if (ir_uart_read_ready_p()) {
        // Error checking with isprint to account for IR interference
        char ch = ir_uart_getc();
        if (isprint(ch)) {
            receiveChar = ch;
        }
    }
    return receiveChar;
}

/**
 * @brief Increments IR get tick and checks if it is the appropriate 
 *        time to execute the IR get task.
 * 
 * @param pacerRate The system pacer rate.
 * @return char The character received or Y.
 */
char irGetTaskCheck(pacer_rate_t pacerRate)
{
    irGetTick++;
    char receiveChar = 'Y';
    if (irGetTick >= pacerRate/IRGETRATE) {
        receiveChar = irGetTask();
        // Reset ticker.
        irGetTick = 0;
    }
    return receiveChar;
}