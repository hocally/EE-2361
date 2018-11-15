/*
 * File:   vand1107_lcd.c
 * Author: Kevin
 *
 * Created on November 1, 2018, 12:02 PM
 */

#include "string.h"
#include "xc.h"
#include "vand1107_lcd.h"

#define CONTRAST 0b100000

void lcd_cmd(char command)
{
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF=0;
    I2C2TRN= 0b01111100;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    I2C2TRN = 0b00000000;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    I2C2TRN = command;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
    
}

void lcd_init()
{

    //TRISBbits.TRISB2 = 0;
    //TRISBbits.TRISB3 = 0; 
   /* _CN6PUE=1;
    _CN7PUE=1;
    LATB |= 0b1100;*/
    long int i;
    for(i=0;i<816000;i++)
    {
        asm("nop");
    }
     lcd_cmd(0b00111000); // function set, normal instruction mode    
     lcd_cmd(0b00111001); // function set, extended instruction mode
     lcd_cmd(0b00010100); // interval osc
     lcd_cmd(0x70 | (CONTRAST & 0xf)); // contrast C3-C0     
     lcd_cmd(0x54 | ((CONTRAST >> 4) & 3)); // Ion, Bon, C5-C4     
     lcd_cmd(0b01101100); // follower control 
     for(i=0;i<6400000;i++)
    {
        asm("nop");
    }
      lcd_cmd(0b00111000); // function set, normal instruction mode     
      lcd_cmd(0b00001100); // Display On     
      lcd_cmd(0b00000001); // Clear Display 
      
      for(i=0;i<32000;i++)
    {
        asm("nop");
    }
}

void lcd_setCursor(char x, char y) {
    char address = x + 0x40 * y;
    char packet = (1 << 7) + address;
    lcd_cmd(packet);
}

void lcd_printChar() {
    I2C2CONbits.SEN = 1;    //Initiate Start condition
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF=0;
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    I2C2TRN = 0b01000000; // 8-bits consisting of control byte /w RS=1
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    I2C2TRN = 0b10000100; // 8-bits consisting of the data byte
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
}

void lcd_printStr(const char *s) {
    int len = strlen(s);
    int i;
    I2C2CONbits.SEN = 1; //Initiate Start condition
    while (I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while (!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    for (i = 0; i < len - 1; i++) {
	I2C2TRN = 0b11000000; // 8-bits consisting of control byte /w RS=1
	while (!IFS3bits.MI2C2IF);
	IFS3bits.MI2C2IF = 0;
	I2C2TRN = s[i]; // 8-bits consisting of the data byte
	while (!IFS3bits.MI2C2IF);
	IFS3bits.MI2C2IF = 0;
    }
    I2C2TRN = 0b01000000; // 8-bits consisting of control byte /w RS=1
    while (!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = s[len-1]; // 8-bits consisting of the data byte
    while (!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN);

}

void rightShift() {
    lcd_cmd(0b00011100);
}

void leftShift() {
    lcd_cmd(0b00011000);
}