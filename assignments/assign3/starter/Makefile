APPLICATION = apps/print_pinout
MY_MODULES = strings.o printf.o
# Add gpio.o and timer.o to list of MY_MODULES to use your own code

# MY_MODULES is a list of those library modules (such as gpio.o)
# for which you intend to use your own code. The reference implementation
# from our libraries will be used for any module you do not name in this list.
# Editing this list allows you to control whether the application being
# built is using your code or the reference implementation for each module
# on a per-module basis. Great for testing!
# NOTE: when you name a module in this list, it must provide definitions
# for all of the symbols in the entire module. For example, if you list
# gpio.o as one of your modules, your gpio.o must define gpio_set_function,
# gpio_get_function, ... and so on for all functions declared in the gpio.h
# header file. If your module forgets to implement any of the needed
# functions, the linker will bring in gpio.o from reference libpi to
# resolve the missing definition. But you can't have both gpio.o modules!
# The linker will report multiple definition errors for every function
# that occurs in both your gpio.o and the reference gpio.o. No bueno!

CFLAGS = -I$(CS107E)/include -g -Wall -Og -std=c99 -ffreestanding
CFLAGS += -mapcs-frame -fno-omit-frame-pointer -Wpointer-arith
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lpi -lgcc

all : $(APPLICATION).bin $(MY_MODULES)

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(MY_MODULES) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.list: %.o
	arm-none-eabi-objdump --no-show-raw-insn -d $< > $@

disassemble: disassemble.elf disassemble.bin
	arm-none-eabi-objdump -d disassemble.elf > disassemble.bin.list
	rpi-install.py -p disassemble.bin

install: $(APPLICATION).bin
	rpi-install.py -p $<

test: tests/test_strings_printf.bin
	rpi-install.py -p $<

clean:
	rm -f *.o *.bin *.elf *.list *~
	rm -f apps/*.o apps/*.bin apps/*.elf apps/*.list apps/*~
	rm -f tests/*.o tests/*.bin tests/*.elf tests/*.list tests/*~

.PHONY: all clean install test
.PRECIOUS: %.elf %.o

# empty recipe used to disable built-in rules for native build
%:%.c
%:%.o

define CS107E_ERROR_MESSAGE
ERROR - CS107E environment variable is not set.

Review instructions for properly configuring your shell.
https://cs107e.github.io/guides/install/userconfig#env

endef

ifndef CS107E
$(error $(CS107E_ERROR_MESSAGE))
endif
