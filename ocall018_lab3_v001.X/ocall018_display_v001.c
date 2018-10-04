/*
 * File:   ocall018_display_v001.c
 * Author: h-o-cally
 *
 * Created on October 4, 2018, 11:28 AM
 */


#include "xc.h"
#include "ocall018_display_v001.h"


void init7seg(void);
void showChar7seg(char myChar, enum DIGIT myDigit);

const unsigned int patterns[] = {
    0b0000000000001100,   // '0'
    0b0000001001111100,   // '1'
    0b0000000010010100,   // '2'
    0b0000000000110100,   // '3'
    0b0000001001100100,   // '4'
    0b0000000100100100,   // '5'
    0b0000000100000100,   // '6'
    0b0000000001111100,   // '7'
    0b0000000000000100,   // '8'
    0b0000000000100100,   // '9'
    0b0000000001000100,   // 'A'
    0b0000001100000100,   // 'b'
    0b0000000110001100,   // 'C'
    0b0000001000010100,   // 'd'
    0b0000000110000100,   // 'E'
    0b0000000111000100,   // 'F'
    0b0000001111111100    // all off
};

void init7seg(void) {
    AD1PCFG = 0x9fff; //all digital inputs and outputs
    TRISB &= 0b1111000000000011; //only set RB2-RB11 output. Leave the rest as they were
    LATB |=  0b0000111111111100; //turn all 7-seg LEDs off
    LATB &=  0b1100111111111111; //turn off all displays
}

void showChar7seg(char myChar, enum DIGIT myDigit) {
    LATB &= CLEAR_ALL_DIG_AND_SEGS_BITS_MASK;
    LATB |= myDigit | patterns[myChar];    
}