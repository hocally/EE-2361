/*
 * File:   ocall_018_button.c
 * Author: h-o-cally
 *
 * Created on October 16, 2018, 8:44 AM
 */


#include "xc.h"
#include "ocall018_button.h"
#include "ocall018_servo.h"

void initPushButton();

void initPushButton() {
    //Configure Timer 2 (500ns/count, 25ms max).
    // note that resolution = 500ns = 8 x 62.5ns, max period = 25ms = Tcy*8*50,000
    T2CON = 0x0110; //Stop Timer, Tcy clk source, PRE 1:8
    TMR2 = 0;
    // Initialize to zero (also best practice)
    PR2 = 0xffff; // Set period to be larger than max external sig duration
    T2CONbits.TON = 1; // Restart 16-bit Timer2
    
    // Initialize the Input Capture Module
    IC1CONbits.ICM = 0b00; // Disable Input Capture 1 module
    IC1CONbits.ICTMR = 1; // Select Timer2 as the IC1 Time base
    IC1CONbits.ICI = 0b01; // Interrupt on every second capture event
    IC1CONbits.ICM = 0b011; // Generate capture event on every Rising edge
    // Enable Capture Interrupt And Timer2
    IPC0bits.IC1IP = 1; // Setup IC1 interrupt priority level
    IFS0bits.IC1IF = 0; // Clear IC1 Interrupt Status Flag
    IEC0bits.IC1IE = 1; // Enable IC1 interrupt
}

volatile long int curPeriod=0;

void __attribute__((__interrupt__)) _IC1Interrupt(void) {
    static unsigned int prevEdge = 0;
    int curEdge;
    _IC1IF = 0;
    curEdge = IC1BUF;
    curPeriod = curEdge - prevEdge;
    prevEdge = curEdge;
    setServo(curEdge);
    T2CONbits.TON = 0; //Stops 16-bit Timer y
    PR2 = 0xffff;
    TMR2 = 0;
    T2CONbits.TON = 1;
}