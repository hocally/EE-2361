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
    TRISB &= 1111111111011111;
    OC1CON = 0;
    OC1R = 0;
    OC1RS = 0;
    //OC1CONbits.OCTSEL = 0b1;
    //OC1CONbits.OCM = 0b110;
    OC1CON = 1;

    PR3 = 1249;
    T3CONbits.TCKPS = 0b11;
    T3CONbits.TCS = 0b0;
    T3CONbits.TGATE = 0b0;
    T3CONbits.TON = 1;


    //PWM period (sec) = (PRy + 1) * 62.5ns * TMRx PreScaler
    //DutyCycle (sec) = OCxR * 62.5ns * TMRx PreScaler
    
    
    
    OC1CONbits.OCM = 0b110;
    OC1CONbits.OCTSEL = 0b1;


}

void setServo(int val) {
    OC1RS = val;
}