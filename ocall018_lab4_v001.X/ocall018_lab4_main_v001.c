/*
 * File:   ocall018_lab4_main_v001.c
 * Author: h-o-cally
 *
 * Created on October 15, 2018, 3:39 PM
 */


#include "xc.h"
#include "stdint.h"
#include "ocall018_servo.h"
#include "ocall018_button.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1 // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME // Clock Switching and Monitor (Clock switching is enabled,
                                // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void setup() {
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR7bits.IC1R = 8;
    RPOR3bits.RP6R = 18; // Use Pin RP6 for Output Compare 1 = "18" (Table 10-3)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff; //all digital inputs and outputs
    _CN22PUE = 1;
    TRISB |= 100000000;
    initServo();
    initPushButton();
}

int main(void) {
    setup();
    while (1) {
	setServo(94);
    }
    return 0;
}