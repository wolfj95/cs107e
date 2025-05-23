APPLICATION = apps/interrupts_console_shell.bin
TEST = tests/test_keyboard_interrupts.bin


# This is the list of your modules that will be used when 
# buliding the console application and libmypi.a library
# To be considered for system bonus, MY_MODULES must name all of your modules
# If you have unresolved issues with a module, you can remove it and the
# reference module will be used instead (no system bonus, though)
#
# *** Before you submit, be sure MY_MODULES is set correctly for the 
#     configuration you want to use when grading your work!!!

MY_MODULES = timer.o gpio.o strings.o printf.o backtrace.o malloc.o keyboard.o shell.o fb.o gl.o console.o

CFLAGS = -I$(CS107E)/include -g -Wall -Og -std=c99 -ffreestanding 
CFLAGS += -mapcs-frame -fno-omit-frame-pointer -mpoke-function-name -Wpointer-arith
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lpi -lgcc

all : $(MY_MODULES) $(APPLICATION) $(TEST)

lib: libmypi.a

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o $(MY_MODULES) start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

libmypi.a: $(MY_MODULES) Makefile
	rm -f $@
	arm-none-eabi-ar cDr $@ $(filter %.o,$^)

%.list: %.o
	arm-none-eabi-objdump --no-show-raw-insn -d $< > $@

install: $(APPLICATION)
	rpi-install.py -p $<

test: $(TEST)
	rpi-install.py -p $<

clean:
	rm -f *.o *.bin *.elf *.list *~ libmypi.a
	rm -f apps/*.o apps/*.bin apps/*.elf apps/*.list apps/*~
	rm -f tests/*.o tests/*.bin tests/*.elf tests/*.list tests/*~

.PHONY: all clean install test
.PRECIOUS: %.elf %.o %.a

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

