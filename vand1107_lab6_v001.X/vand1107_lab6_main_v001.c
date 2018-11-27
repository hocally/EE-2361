/*
 * File:   vand1107_lab6_main_v001.c
 * Author: Kevin
 *
 * Created on November 15, 2018, 11:37 AM
 */


#include "xc.h"
#include "vand1107_lcd.h"
#include "vandh1107_bufferLibrary.h"
#include "stdint.h"
#include "stdio.h"

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

unsigned char displayFlag = 0;

void setup() {
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9ffe; //all digital inputs and outputs
    TRISA |= 1;
    
    I2C2BRG = 0x9D;
    I2C2CONbits.I2CEN = 1;
    _I2CSIDL = 0;
    IFS3bits.MI2C2IF=0;
    
    initBuffer();
    lcd_init();
    lcd_setCursor(0, 0);
    
    AD1CON1 = 0;    // use default settings, AND turn off A/D for now
    AD1CON1bits.SSRC = 0b010;  // timer 3 rollover stops sampling, starts conversion
    AD1CON1bits.ASAM = 1; // auto-sample
    AD1CON1bits.FORM = 0b00;
    AD1CON2 = 0;
    AD1CON2bits.CSCNA = 0; // turn off scan
    AD1CON2bits.SMPI = 0b1111; // interrupt after every 16th conversion
    AD1CON2bits.BUFM = 0;  // two 8-word buffers
    AD1CON3bits.ADCS = 1;
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.SAMC = 1;
    AD1CON1bits.ADON = 1; // turn on module
    AD1CHS = 0;
    AD1CHSbits.CH0NB = 0;
    AD1CHSbits.CH0SB = 0;
    AD1CHSbits.CH0NA = 0;
    AD1CHSbits.CH0SA = 0;
    
    
    T3CON = 0;
    TMR3 = 0;
    T3CONbits.TCKPS = 0b10;
    PR3 = 15625;
    T3CONbits.TON = 1;

    T2CON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0b10;
    PR2 = 25000;
    T2CONbits.TON = 1;

    IEC0bits.AD1IE = 1; // enable interrupt on ADC completion
    IFS0bits.AD1IF = 0;
    
    //IEC0bits.T3IE = 1; // enable interrupt on T3 completion
    //IFS0bits.T3IF = 0;
    
    IEC0bits.T2IE = 1; // enable interrupt on T2 completion
    IFS0bits.T2IF = 0;
}

void __attribute__((__interrupt__, __auto_psv__)) _ADC1Interrupt(void) {
    IFS0bits.AD1IF = 0;
    putVal(ADC1BUF0);
    putVal(ADC1BUF1);
    putVal(ADC1BUF2);
    putVal(ADC1BUF3);
    putVal(ADC1BUF4);
    putVal(ADC1BUF5);
    putVal(ADC1BUF6);
    putVal(ADC1BUF7);
    putVal(ADC1BUF8);
    putVal(ADC1BUF9);
    putVal(ADC1BUFA);
    putVal(ADC1BUFB);
    putVal(ADC1BUFC);
    putVal(ADC1BUFD);
    putVal(ADC1BUFE);
    putVal(ADC1BUFF);
}

void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void) {
    _T2IF = 0;
    displayFlag = 1;
}

int main(void) {
    setup();
    unsigned long data;
    char dataStr[20];
    while(1) {
        if(displayFlag) {
	    displayFlag = 0;
	    lcd_setCursor(0, 0);
	    data = getAvg();
	    data = (3.3/1024) * data;
	    sprintf(dataStr, "%6.4f V", (3.3/1024)*data);
	    lcd_printStr(dataStr);
	}
    }
}
