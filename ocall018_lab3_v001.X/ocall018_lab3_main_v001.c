/*
 * File:   ocall018_lab3_main_v001.c
 * Author: h-o-cally
 *
 * Created on October 3, 2018, 4:49 PM
 */


#include "xc.h"
#include "stdint.h"
#include "ocall018_display_v001.h"
#include "ocall018_keypad_v001.h"

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

void setup(void) {
    CLKDIVbits.RCDIV = 0;
    init7seg();
    initKeyPad();
}

int main(void) {
    setup();
    //int i;
    //long int j;

    unsigned short key;
    unsigned short lastKey = -1;
    unsigned short left = 16;
    unsigned short right = 16;
    while (1) {
        key = readKeyPadRAW();
        if (key == -1) {
            lastKey = key;
        } else if (lastKey == -1) {
            left = right;
            right = key;
            lastKey = key;
        }
        showChar7seg(left, msb);
        int a;
        for (a = 0; a < 159; a++) {
            asm("nop");
        }
        showChar7seg(right, lsb);
        for (a = 0; a < 159; a++) {
            asm("nop");
        }

        /*
        for(i = 0x0; i < 0x10; i++) {
            showChar7seg(i, msb);
            for(j = 0; j < 400000; j++) {
            asm("nop");
            }
        }
         */
    }
    return 0;
}