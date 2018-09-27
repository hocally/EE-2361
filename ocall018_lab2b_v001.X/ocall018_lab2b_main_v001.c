/*
 * File:   ocall018_lab2b_main_v001.c
 * Author: h-o-cally
 *
 * Created on September 25, 2018, 3:55 PM
 */


#include "xc.h"
#include "stdint.h"
#include "ocall018_lab2b_asmLib_v001.h"

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

#define PERIOD 5

void writeColor(int r, int g, int b);
void drawFrame(unsigned char frame);
void delay(int delay_in_ms);
uint32_t packColor(unsigned char Red, unsigned char Blu, unsigned char Grn);
unsigned char getR(uint32_t RGBval);
unsigned char getG(uint32_t RGBval);
unsigned char getB(uint32_t RGBval);
void writePacCol(uint32_t packedColor);
uint32_t wheel(unsigned char WheelPos);

void setup() {
    AD1PCFG = 0x9fff;
    TRISA = 0b1111111111111110;
    LATA = 0x0000;
}

int main(void) {
    setup();
    unsigned char num;
    while(1) {
	/*
	for(num = 0; num <= 255; num++) {
	     writePacCol(wheel(num));
	     delay(PERIOD);
	}
	*/
    }
    return 0;
}

void writeColor(int r, int g, int b) {
    //LOL
}

void drawFrame(unsigned char frame) {
    writeColor(frame, 0, 255 - frame);
    delay(PERIOD);
}

void delay(int delay_in_ms) {
    int loops;
    for(loops = delay_in_ms; loops > 0; loops--) {
	hoc_delay_1ms();
    }
}

uint32_t packColor(unsigned char r, unsigned char g, unsigned char b) {
    return ((long) r << 16) | ((long) g << 8) | ((long) b);
}

unsigned char getR(uint32_t RGBval) {
    return (unsigned char) (RGBval >> 16);
}

unsigned char getG(uint32_t RGBval) {
    return (unsigned char) (RGBval >> 8);
}

unsigned char getB(uint32_t RGBval) {
    return (unsigned char) RGBval;
}

void writePacCol(uint32_t packedColor) {
    writeColor(getR(packedColor), getG(packedColor), getB(packedColor));
}

uint32_t wheel(unsigned char wheelPos) {
    wheelPos = 255 - wheelPos;
    if(wheelPos < 85) {
	return packColor(255 - wheelPos * 3, 0, wheelPos * 3);
    }
    if(wheelPos < 170) {
	return packColor(0, wheelPos * 3, 255 - wheelPos * 3);
    }
    wheelPos -= 170;
    return packColor(wheelPos * 3, 255 - wheelPos * 3, 0);
}