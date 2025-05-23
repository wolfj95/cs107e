#include "gpio.h"

#define GPIO_FSEL0  ((unsigned int *)0x3f200000)
#define GPIO_SET0   ((unsigned int *)0x3f20001C)
#define GPIO_CLR0   ((unsigned int *)0x3f200028)
#define GPIO_LEV0   ((unsigned int *)0x3f200034)

void gpio_init(void) {
}

void gpio_set_function(unsigned int pin, unsigned int function) {
    if (pin >= GPIO_PIN_FIRST  && pin <= GPIO_PIN_LAST && function >= 0 && function <= 7) {
        unsigned int *FSEL_ADDRESS = GPIO_FSEL0 + (pin/10);
        *FSEL_ADDRESS = (*FSEL_ADDRESS & ~(7 << 3*(pin%10))) | (function << 3*(pin%10)); 
    }
}

unsigned int gpio_get_function(unsigned int pin) {
    if (pin >= GPIO_PIN_FIRST  && pin <= GPIO_PIN_LAST) {
        unsigned int *FSEL_ADDRESS = GPIO_FSEL0 + (pin/10);
        int function = (*FSEL_ADDRESS & (7 << 3*(pin%10))) >> 3*(pin%10);
        return function;
    }
    return GPIO_INVALID_REQUEST;
}

void gpio_set_input(unsigned int pin) {
    gpio_set_function(pin, GPIO_FUNC_INPUT);
}

void gpio_set_output(unsigned int pin) {
    gpio_set_function(pin, GPIO_FUNC_OUTPUT);
}

void gpio_write(unsigned int pin, unsigned int value) {
    if (pin >= GPIO_PIN_FIRST && pin <= GPIO_PIN_LAST) {
        if (value == 0) { 
            unsigned int *GPIO_CLR = GPIO_CLR0 + (pin/32);
            *GPIO_CLR = (1 << (pin%32)); 
        } else {
            unsigned int *GPIO_SET = GPIO_SET0 + (pin/32);
            *GPIO_SET = (1 << (pin%32)); 
        }
    }
}

unsigned int gpio_read(unsigned int pin) {
    if (pin >= GPIO_PIN_FIRST && pin <= GPIO_PIN_LAST) {
        volatile unsigned int *GPIO_LEV = GPIO_LEV0 + (pin/32);
        int level = (*GPIO_LEV & (1 << (pin%32))) >> (pin%32);
        return level;
    }
    return GPIO_INVALID_REQUEST;
}
