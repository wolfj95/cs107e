.equ DELAY, 0x3F0000

// configure GPIO 35 (PWR LED) for output
ldr r0, FSEL3
mov r1, #(1<<15)
str r1, [r0]

// set bit 3
mov r1, #(1<<3)

loop: 

// set GPIO 35 high
ldr r0, SET1
str r1, [r0] 

// delay
mov r2, #DELAY
wait1:
    subs r2, #1
    bne wait1

// set GPIO 35 low
ldr r0, CLR1
str r1, [r0] 

// delay
mov r2, #DELAY
wait2:
    subs r2, #1
    bne wait2

b loop

FSEL3: .word 0x3f20001C
SET1:  .word 0x3f200020
CLR1:  .word 0x3f20002C
