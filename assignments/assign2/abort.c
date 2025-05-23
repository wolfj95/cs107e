#define GPIO_FSEL2  ((unsigned int *)0x3f200008)
#define GPIO_SET0   ((unsigned int *)0x3f20001C)
#define GPIO_CLR0   ((unsigned int *)0x3f200028)

// Green ACT  LED (on Pi board) is GPIO 29.
#define ABORT_OUTPUT (1 << (3*9))
#define ABORT_BIT    (1 << (29))

#define DELAY1 0x100000

// abort goes into an infinite loop that flashes the green ACT led.
// since you can't control the PWR led, abort flashed ACT led in 4 beat/pause sequence.
void abort(void) {
    // First, configure GPIO 29 function to be output.
    // This assignment wipes functions for other pins in this register
    // (GPIO 20-29), but that's okay, because this is a dead-end routine.
    *GPIO_FSEL2 = ABORT_OUTPUT;
    while (1) {
        for (int i = 0; i < 4; i++) {
            *GPIO_SET0 = ABORT_BIT;
             // These delay loops have volatile counters to prevent being
             // optimized out.
             for (volatile int i = 0; i < DELAY1; i++) ;
            *GPIO_CLR0 = ABORT_BIT;
             for (volatile int i = 0; i < DELAY1; i++) ;
        } 
        for (volatile int i = 0; i < DELAY1*2; i++) ;
    }
}
