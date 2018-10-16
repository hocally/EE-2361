/* 
 * File:   ocall018_display_001.h
 * Author: h-o-cally
 *
 * Created on October 4, 2018, 11:28 AM
 */

#ifndef OCALL018_DISPLAY_001_H
#define	OCALL018_DISPLAY_001_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CLEAR_ALL_DIG_AND_SEGS_BITS_MASK    0b1100000000000011   // to be ANDED

enum DIGIT {
    msb = 0b0000010000000000, 
    lsb = 0b0000100000000000
};

void init7seg(void);
void showChar7seg(char myChar, enum DIGIT myDigit);


#ifdef	__cplusplus
}
#endif

#endif	/* OCALL018_DISPLAY_001_H */

