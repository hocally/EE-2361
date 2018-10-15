/*
 * File:   ocall018_servo.c
 * Author: h-o-cally
 *
 * Created on October 15, 2018, 4:09 PM
 */


#include "xc.h"
#include "ocall018_servo.h"

void initServo();
void setServo(int val);

void initServo() {
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR3bits.RP6R = 18; // Use Pin RP6 for Output Compare 1 = "18" (Table 10-3)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    OC1CONbits.OCM = 0b110;
    OC1CONbits.OCTSEL = 0b1;
    
    T3CONbits.TON = 1;
    T3CONbits.TCKPS = 0b00;
    T3CONbits.TCS = 0b0;
    T3CONbits.TGATE = 0b0;
    
    
}

void setServo(int val) {
    
}