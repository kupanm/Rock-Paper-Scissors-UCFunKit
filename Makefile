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
game.o: game.c ../../drivers/avr/system.h ../../drivers/avr/navswitch.h ../../drivers/avr/button.h ../../drivers/avr/ir_serial.h ../../drivers/avr/led.h ../../drivers/avr/handSelect.h ../../drivers/avr/gameLogic.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: button.c ../../drivers/avr/pio.h ../../drivers/avr/system.h button.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_serial.o: ir_serial.c ../../ence260-ucfk4/drivers/ir_serial.h ../../drivers/avr/delay.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

handSelect.o: handSelect.c ../../assignment/group_226/handSelect.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

gameLogic.o: gameLogic.c ../../assignment/group_226/gameLogic.h
	$(CC) -c $(CFLAGS) $< -o $@



# Link: create ELF output file from object files.
game.out: game.o navswitch.o button.o ir_serial.o led.o pio.o system.o handSelect.o gameLogic.o
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
