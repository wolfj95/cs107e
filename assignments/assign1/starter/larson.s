/*
 * LARSON SCANNER
 *
 * Currently this code is the blink code copied from lab 1.
 *
 * Modify the code to implement the larson scanner for assignment 1.
 *
 * Make sure to use GPIO pins 20-23 (or 20-27) for your scanner.
 */

.equ DELAY, 0x3F000
.equ FSELSPACE, 0x3
.equ NUMLED, 0x5

// configure GPIO in FSEL2 for output
ldr r0, FSEL2

// looping from 1 to NUMLEDS - 1 to set a bit every FSELSPACE bits 
mov r5, #NUMLED
sub r5, r5, #1  // r5 holds counter from NUMLEDS - 1 to 0
mov r1, #1 // r1 hold bits for GPIO config
mov r6, #FSELSPACE
loop1:
    mul r3, r5, r6
    mov r8, #1
    lsl r2, r8, r3
    orr r1, r2
    subs r5, r5, #1
    bne loop1

// setting GPIO pins based on bits in r1
str r1, [r0]

ldr r0, CLR0
ldr r1, SET0

loopforever:

mov r5, #NUMLED  //r5 holds current led num
sub r5, r5, #1

// [light last led] set bit 20 + NUMLED - 1 (stored in r2)
add r2, r5, #20
mov r3, #1
lsl r2, r3, r2
str r2, [r1]

// [delay]
mov  r4, #DELAY
wait0:
    subs r4, #1
    bne wait0

// [turn off last led]
str r2, [r0]

// [decrement currled counter]
sub r5, r5, #1

loopledsdown:

//mov r6, #NUMLED  //throwaway ops to make timing equal
//sub r6, r6, #1   //throwaway ops to make timing equal

// [turn on currled] set bit 20 + currled (r5) (stored in r2)
add r2, r5, #20
mov r3, #1
lsl r2, r3, r2
str r2, [r1]

// [delay]
mov r4, #DELAY
wait1:
    subs r4, #1
    bne wait1

// [turn off currled]
str r2, [r0]

add r6, r6, #1 //throwaway op to make time equal between going up and going down

// [decrement currled counter]
subs r5, r5, #1

// loop if currled not 0
bne  loopledsdown


//mov r6, #NUMLED  //throwaway ops to make timing equal
//sub r6, r6, #1   //throwaway ops to make timing equal

// [turn on first led] set bit 20 (stored in r2)
mov r2, #(1 << 20)
str r2, [r1]

// [delay]
mov  r4, #DELAY
wait2:
    subs r4, #1
    bne wait2

// [turn off first led]
str r2, [r0]

// [increment currled counter]
add r5, r5, #1

loopledsup:

//mov r6, #NUMLED  //throwaway ops to make timing equal
//sub r6, r6, #1   //throwaway ops to make timing equal

// [turn on currled] set bit 20 + currled (r5) (stored in r2)
add r2, r5, #20
mov r3, #1
lsl r2, r3, r2
str r2, [r1]

// [delay]
mov r4, #DELAY
wait3:
    subs r4, #1
    bne wait3

// [turn off currled]
str r2, [r0]

// [increment currled counter]
add r5, r5, #1

// loop if currled not NUMLED - 1
sub r3, r5, #NUMLED
adds r3, r3, #1
bne  loopledsup

b loopforever

FSEL0: .word 0x3F200000
FSEL1: .word 0x3F200004
FSEL2: .word 0x3F200008
SET0:  .word 0x3F20001C
SET1:  .word 0x3F200020
CLR0:  .word 0x3F200028
CLR1:  .word 0x3F20002C

