#include "../assert.h"
#include "../gpio.h"
#include "../timer.h"

void test_gpio_set_get_function(void) {
    gpio_init();

    // Test get pin function (pin2 defaults to input)
    assert( gpio_get_function(GPIO_PIN2) == GPIO_FUNC_INPUT );

    // Test set pin to output
    gpio_set_output(GPIO_PIN2);

    // Test get pin function after setting
    assert( gpio_get_function(GPIO_PIN2) == GPIO_FUNC_OUTPUT );

    // Test pins in other registers
    for (int i = 0; i < GPIO_PIN_LAST; i++) {
        gpio_set_output(i);
        assert( gpio_get_function(i) == GPIO_FUNC_OUTPUT );
    }

    // test ALT functions
    for (int i=0; i < 7; i++) {
        gpio_set_function(GPIO_PIN12, i);
        assert( gpio_get_function(GPIO_PIN12) == i );
    }

    // test setting two pins in same register
    gpio_set_function(GPIO_PIN12, GPIO_FUNC_ALT0);
    assert( gpio_get_function(GPIO_PIN12) ==  GPIO_FUNC_ALT0 );
    gpio_set_function(GPIO_PIN13, GPIO_FUNC_ALT3);
    assert( gpio_get_function(GPIO_PIN13) ==  GPIO_FUNC_ALT3 );
    assert( gpio_get_function(GPIO_PIN12) == GPIO_FUNC_ALT0 );

    // test setting invalid function
    gpio_set_function(GPIO_PIN3, 8);

    // test setting invalid pin 
    gpio_set_function(54, GPIO_FUNC_OUTPUT);

    // test getting invalid pin
    assert( gpio_get_function(54) == GPIO_INVALID_REQUEST );

}

void test_gpio_read_write(void) {
    gpio_init();
    gpio_set_function(GPIO_PIN20, GPIO_FUNC_OUTPUT);

    // Test gpio_write low, then gpio_read
    gpio_write(GPIO_PIN20, 0);
    assert( gpio_read(GPIO_PIN20) ==  0 );

   // Test gpio_write high, then gpio_read
    gpio_write(GPIO_PIN20, 1);
    assert( gpio_read(GPIO_PIN20) ==  1 );

    // test pins in second register
    gpio_write(GPIO_PIN33, 0);
    assert( gpio_read(GPIO_PIN33) ==  0 );
    gpio_write(GPIO_PIN33, 1);
    assert( gpio_read(GPIO_PIN33) ==  1 );

    // test write/read multiple pins in same register
    gpio_write(GPIO_PIN20, 1);
    assert( gpio_read(GPIO_PIN20) == 1 );
    gpio_write(GPIO_PIN21, 1);
    assert( gpio_read(GPIO_PIN21) == 1 );
    assert( gpio_read(GPIO_PIN20) == 1 );

    gpio_write(GPIO_PIN20, 0);
    assert( gpio_read(GPIO_PIN21) == 1 );
    assert( gpio_read(GPIO_PIN20) == 0 );

    gpio_write(GPIO_PIN21, 0);
    assert( gpio_read(GPIO_PIN21) == 0 );
    assert( gpio_read(GPIO_PIN20) == 0 );

    // test invalid pin write/read
    gpio_write(54, 0);
    assert( gpio_read(54) == -1 );

    // test write output level other than 0 or 1
    gpio_write(GPIO_PIN22, 3);
    assert( gpio_read(GPIO_PIN22) == 1 );
}

void test_timer(void) {
    timer_init();

    // Test timer tick count incrementing
    volatile unsigned int start = timer_get_ticks();
    for( int i=0; i<10; i++ ) { /* Spin */ }
    unsigned int finish = timer_get_ticks();
    assert( finish > start );

    // Test timer delay
    unsigned int secs = 5;
    start = timer_get_ticks();
    timer_delay(secs);
    finish = timer_get_ticks();
    assert( finish >= start + secs*1000000 );
}

// Uncomment each call below when you have implemented the functions
// and are ready to test them

void main(void) {
    test_gpio_set_get_function();
    test_gpio_read_write();
    test_timer();
}
