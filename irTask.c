/** @file   irTask.c
    @author David Liang
    @date   09/10/2022
    @brief  Controls IR communication task and updates.
*/

#include "ir_uart.h"
#include "pacer.h"
#define IRRATE 250

static uint8_t irPutTick;
static uint8_t irGetTick;

/**
 * Initialises IR communication.
 * 
 */
void irTaskInit(void)
{
    ir_uart_init();
    irPutTick = 0;
    irGetTick = 0;
}

/**
 * Sends a character. 
 */
static void irPutTask(char sendChar)
{
    ir_uart_putc(sendChar);
}

/** 
 * Increments IR put tick and checks if it is the appropriate 
 * time to execute the IR put task.
*/
void irPutTaskCheck(pacer_rate_t pacerRate, char sendChar)
{
    irPutTick++;
    if (irPutTick >= pacerRate/IRRATE) {
        irPutTask(sendChar);
        irPutTick = 0;
    }
}

/**
 * Receives a character if there is one available. 
 * Otherwise, returns dummy character X.
 */
static char irGetTask(void)
{
    char receiveChar = 'X';
    if (ir_uart_read_ready_p()) {
        receiveChar = ir_uart_getc();
    }
    return receiveChar;
}

/** 
 * Increments IR get tick and checks if it is the appropriate 
 * time to execute the IR get task.
*/
char irGetTaskCheck(pacer_rate_t pacerRate)
{
    irTick++;
    char receiveChar = 'X';
    if (navTick >= pacerRate/IRRATE) {
        receiveChar = irGetTask();
        navTick = 0;
    }
    return receiveChar;
}