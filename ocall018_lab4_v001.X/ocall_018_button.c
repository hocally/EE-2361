/*
 * File:   ocall_018_button.c
 * Author: h-o-cally
 *
 * Created on October 16, 2018, 8:44 AM
 */


#include "xc.h"
#include "ocall018_button.h"

void initPushButton();

void initPushButton() {
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR7bits.IC1R = 9;
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    T2CON = 0x0010;
    TMR2 = 0;
    PR2 = 60000;
    T2CONbits.TON = 1;
    IC1CON = 0; // Turn off and reset internal state of IC1
    IC1CONbits.ICTMR = 1; // Use Timer 2 for capture source
    IC1CONbits.ICM = 0b011; // Turn on and capture every rising edge
}

volatile long int curPeriod=0;

IC1Interrupt() {
    static unsigned int prevEdge=0;
    int curEdge;
    _IC1IF = 0;
    curEdge = IC1BUF;
    curPeriod = curEdge - prevEdge;
    prevEdge = curEdge;
}