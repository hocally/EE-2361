/*
 * File:   vandh1107_bufferLibrary.c
 * Author: Kevin
 *
 * Created on November 15, 2018, 11:38 AM
 */

#include "xc.h"
#include "vand1107_lcd.h"

#define BUF_SIZE 1024
unsigned long avg = 0;
long buffer[BUF_SIZE];
long myIndex = 0;

void putVal(int newValue) { // add a new value to the buffer
    buffer[myIndex++] = newValue;
    if(myIndex >= BUF_SIZE) {
        myIndex = 0;
    }
}    
int getAvg() {
    long sum = 0;
    long i;
    for(i = 0; i < BUF_SIZE; i++) {
        sum += buffer[i];
    }
    avg = sum / BUF_SIZE;
    return avg;
} // average all buffer vals
void initBuffer() {
    long i;
    for(i = 0; i < BUF_SIZE; i++) {
        buffer[i] = 0;
    }
}
