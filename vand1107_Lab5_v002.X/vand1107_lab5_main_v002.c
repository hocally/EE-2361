/*
 * File:   vand1107_lab5_main_v002.c
 * Author: Kevin
 *
 * Created on November 1, 2018, 12:31 PM
 */


#include "xc.h"
#include "stdint.h"
#include "vand1107_lcd.h"

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

void setup()
{
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff; //all digital inputs and outputs
    I2C2BRG = 0x9D;
    I2C2CONbits.I2CEN = 1;
    _I2CSIDL = 0;
    IFS3bits.MI2C2IF=0;
   
    lcd_init();

    
    
    
}

const char data2[2] = { 0b01101111,
			0b01110010};

int main(void) {
    setup();
    //int side = 0;
    //int i = 0;
    lcd_setCursor(0, 0);
    lcd_printStr("Hello World!");
    unsigned long i;
    while (1) {
	for (i = 0; i < 800000; i++) {
	    asm("nop");
	}
	
	leftShift();
    }
    return 0;
}
//Got an NACK and a Stop bit