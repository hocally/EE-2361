/*
   File:   ocall018_kaypad_v001.c
   Author: h-o-cally

   Created on October 4, 2018, 11:27 AM
*/


#include "xc.h"

void initKeyPad(void);
unsigned int readKeyPadRAW(void);

void initKeyPad(void) {
  AD1PCFG = 0x9fff; //all digital inputs and outputs
  TRISB |= 0b1111000000000000; //only set RB2-RB11 output. Leave the rest as they were
  TRISA &= 0b1111111111110000;
  LATA &=  0b0000000000001111; //turn off all displays
}

/*
  1  2      3      4      5       6       7       8
  RA0    RA1    RA2    RA3    RB15    RB14    RB13    RB12
*/

unsigned int readKeyPadRAW(void) {
  static unsigned short int pressed = 0;
  static unsigned int key = 0;
  int i;
  int num;
  for (i = 0; i < 4; i++) {
    LATA |= 0b1111; //Changed this around, I think we had the logic flipped
    LATA -= 0b1000 >> i;

    asm("nop");
    asm("nop");
    asm("nop");

    num = (!_RB15 << 3) | (!_RB14 << 2) | (!_RB13 << 1) | !_RB12;

    if (num > 0) {
      if (!pressed) {
        if (i == 0) {
          switch (num) {
            //1
            case 0b1000:
              key = 0x10; //Change this
              break;
            case 0b0100:
              key = 7;
              break;
            case 0b0010:
              key = 4;
              break;
            case 0b0001:
              key = 1;
              break;
          }
        } else if (i == 1) {
          //2
          switch (num) {
            case 0b1000:
              key = 0;
              break;
            case 0b0100:
              key = 8;
              break;
            case 0b0010:
              key = 5;
              break;
            case 0b0001:
              key = 2;
              break;
          }
        } else if (i == 2) {
          //3
          switch (num) {
            case 0b1000:
              key = 0x10; //Change this
              break;
            case 0b0100:
              key = 9;
              break;
            case 0b0010:
              key = 6;
              break;
            case 0b0001:
              key = 3;
              break;
          }
        } else if (i == 3) {
          //A
          switch (num) {
            case 0b1000:
              key = 0xd;
              break;
            case 0b0100:
              key = 0xc;
              break;
            case 0b0010:
              key = 0xb;
              break;
            case 0b0001:
              key = 0xa;
              break;
          }
        }
        pressed = 1;
      }
    } else {
      pressed = 0;
    }
  }
  return key;
}
