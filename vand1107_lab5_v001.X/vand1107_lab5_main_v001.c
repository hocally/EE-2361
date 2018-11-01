/*
 * File:   vand1107_lab5_main_v001.c
 * Author: Kevin
 *
 * Created on November 1, 2018, 11:06 AM
 */


#include "xc.h"

int main(void) {
    return 0;
}
void lcd_cmd(char command)
{
    I2C2CONbits.SEN = 1;
    while(!IFS3bits.MI2C2IF)
    IFS3bits.MI2C2IF=0;
    
    
}