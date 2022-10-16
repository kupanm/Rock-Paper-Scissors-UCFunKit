# File:   Makefile
# Author: K.N. Mugutso and David Liang
# Date:   08 Oct 2022
# Descr:  Makefile for game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files. !!!*ATTENTION*!!!: may have to add the modules that the drivers also include such as system, pio, delay etc.
game.o: game.c ../../drivers/avr/system.h ../../drivers/navswitch.h ../../drivers/button.h ../../drivers/avr/ir_uart.h ../../drivers/led.h gameLogic.h ../../utils/tinygl.h ../../fonts/font5x7_1.h buttonModule.h displayModule.h irModule.h navswitchModule.h
	$(CC) -c $(CFLAGS) $< -o $@

buttonModule.o: buttonModule.c buttonModule.h ../../drivers/avr/system.h ../../utils/pacer.h ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

displayModule.o: displayModule.c displayModule.h ../../drivers/avr/system.h ../../utils/pacer.h ../../utils/tinygl.h ../../fonts/font5x7_1.h ../../fonts/font3x5_1.h
	$(CC) -c $(CFLAGS) $< -o $@

irModule.o: irModule.c irModule.h ../../drivers/avr/system.h ../../utils/pacer.h ../../drivers/avr/ir_uart.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitchModule.o: navswitchModule.c navswitchModule.h ../../drivers/avr/system.h ../../utils/pacer.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/avr/system.h ../../drivers/button.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

gameLogic.o: gameLogic.c gameLogic.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@



# Link: create ELF output file from object files.
game.out: game.o navswitch.o button.o ir_uart.o led.o pio.o system.o gameLogic.o font.o pacer.o tinygl.o timer.o timer0.o usart1.o display.o ledmat.o prescale.o buttonModule.o displayModule.o irModule.o navswitchModule.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start
