/*
 * File:   ocall018_kaypad_v001.c
 * Author: h-o-cally
 *
 * Created on October 4, 2018, 11:27 AM
 */


#include "xc.h"

void initKeyPad(void);
unsigned int readKeyPadRAW(void);

void initKeyPad(void) {
    AD1PCFG = 0x9fff; //all digital inputs and outputs
    TRISB |= 0b1111000000000000; //only set RB2-RB11 output. Leave the rest as they were
    TRISA &= 0b1111111111110000;
    LATA &=  0b0000000000001111; //turn off all displays
}

unsigned int readKeyPadRAW(void) {
    int i;
    int num;
    for(i = 0; i < 4; i++) {
	LATA |= 0b1111;
	LATA -= 1 << i;
	asm("nop");
	asm("nop");
	asm("nop");
	num = (!_RB15 << 3) | (!_RB14 << 2) | (!_RB13 << 1) | !_RB12;
	if(num > 0){
	    return 3;
	}
    }
    return 0;
}
