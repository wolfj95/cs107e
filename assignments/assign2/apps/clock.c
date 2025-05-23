#include "../gpio.h"
#include "../timer.h"

char HEX_SEGS[] = { 0b00111111,  //0
                    0b00000110,  //1
                    0b01011011,  //2
                    0b01001111,  //3
                    0b01100110,  //4
                    0b01101101,  //5
                    0b01111101,  //6
                    0b00000111,  //7
                    0b01111111,  //8
                    0b01100111,  //9
                    0b01011111,  //a
                    0b01111100,  //b
                    0b01011000,  //c
                    0b01011110,  //d
                    0b01111011,  //e
                    0b01110001,  //f
                    0b10000000,  //.
                    0b01000000   //-
                  };

char HEX_SEGS_W_DECIMAL[] =
                  { 0b10111111,  //0.
                    0b10000110,  //1.
                    0b11011011,  //2.
                    0b11001111,  //3.
                    0b11100110,  //4.
                    0b11101101,  //5.
                    0b11111101,  //6.
                    0b10000111,  //7.
                    0b11111111,  //8.
                    0b11100111,  //9.
                    0b11011111,  //a.
                    0b11111100,  //b.
                    0b11011000,  //c.
                    0b11011110,  //d.
                    0b11111011,  //e.
                    0b11110001   //f.
                  };
void config_clock_pin_functions() {
    // set pins 10-13 to output for digits
    for (int i = 0; i < 4; i++) {
        gpio_set_output(GPIO_PIN10 + i);
    }
    //set pins 20-27 to output for segments
    for (int i = 0; i < 8; i++) {
        gpio_set_output(GPIO_PIN20 + i);
    }
    // set pin 19 to input for button
    gpio_set_input(GPIO_PIN19);
}

void all_digits_off() {
    for (int i = 0; i < 4; i++) {
        gpio_write(GPIO_PIN10 + i, 0);
    }
}

void gpio_display_digit_at_display_num(int digit, int display_num) {
    all_digits_off();
    gpio_write(GPIO_PIN10 + display_num, 1);
    unsigned int seg_bin = HEX_SEGS[digit];
    // use digits with decimal if digit in ones place
    if (display_num == 1) {
        seg_bin = HEX_SEGS_W_DECIMAL[digit];
    }
    for (int i = 0; i < 8; i++) {
        char zero_bit = seg_bin & (1);
        gpio_write(20+i, zero_bit);
        seg_bin = seg_bin >> 1;
    }
}

void display_before_start() {
    for (int i = 0; i < 4; i++) {
        gpio_write(GPIO_PIN10 + i, 1);
    }
    gpio_write(GPIO_PIN26, 1);
}

void display_refresh_loop(int digits[4]) {
    for (int i = 0; i < 4; i++) {
        gpio_display_digit_at_display_num(digits[i], i);
        timer_delay_us(2500);
    }
}

void ticks_to_display_digits(int ticks_since_start, int display_digits[]) {
    int seconds_since_start = ticks_since_start / 1000000;
    int minutes_since_start = seconds_since_start / 60;
    int seconds_remaining = seconds_since_start % 60;
    display_digits[0] = (minutes_since_start % 100) / 10;
    display_digits[1] = minutes_since_start % 10;
    display_digits[2] = seconds_remaining / 10;
    display_digits[3] = seconds_remaining % 10;
}

void run_clock() {
    while (1) {
        int ticks_at_start = timer_get_ticks();
        int display_digits[4] = {0,0,0,0};
        // run timer until button press
        while(1) {
            display_refresh_loop(display_digits);
            int ticks_since_start = timer_get_ticks() - ticks_at_start;
            ticks_to_display_digits(ticks_since_start, display_digits);
            if (gpio_read(GPIO_PIN19) == 1 && ticks_since_start > 1*1000000) {break;}
        }
        // maintain time on display until button press
        ticks_at_start = timer_get_ticks();
        while(1) {
            display_refresh_loop(display_digits);
            int ticks_since_start = timer_get_ticks() - ticks_at_start;
            if (gpio_read(GPIO_PIN19) == 1 && ticks_since_start > 1*1000000) {break;}
        }
    }
}

void main(void)
{
    config_clock_pin_functions();
    display_before_start();

    // wait for button press
    while (1) { if ( gpio_read(GPIO_PIN19) == 1  ) { break; } }

    run_clock();
}
