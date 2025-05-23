.equ DELAY, 0x3F0000

// configure GPIO 29 (ACT LED) for output
ldr r0, FSEL2
mov r1, #(1<<27)
str r1, [r0]

// set bit 29
mov r1, #(1<<29)

loop: 

// set GPIO 29 high
ldr r0, SET0
str r1, [r0] 

// delay
mov r2, #DELAY
wait1:
    subs r2, #1
    bne wait1

// set GPIO 29 low
ldr r0, CLR0
str r1, [r0] 

// delay
mov r2, #DELAY
wait2:
    subs r2, #1
    bne wait2

b loop

FSEL2: .word 0x3f200008
SET0:  .word 0x3f20001C
CLR0:  .word 0x3f200028
