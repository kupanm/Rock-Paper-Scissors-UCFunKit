# File:   Makefile
# Author: K.N. Mugutso
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
game.o: game.c
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/test/ir_uart.c
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c
	$(CC) -c $(CFLAGS) $< -o $@

handSelect.o: handSelect.c
	$(CC) -c $(CFLAGS) $< -o $@

gameLogic.o: gameLogic.c
	$(CC) -c $(CFLAGS) $< -o $@



# Link: create ELF output file from object files.
game.out: game.o navswitch.o button.o ir_uart.o led.o pio.o system.o handSelect.o gameLogic.o
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
