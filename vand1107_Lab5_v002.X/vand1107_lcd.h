/* 
 * File:   vand1107.h
 * Author: Kevin
 *
 * Created on November 1, 2018, 12:03 PM
 */

#ifndef VAND1107_H
#define	VAND1107_H

#ifdef	__cplusplus
extern "C" {
#endif

    void lcd_cmd(char command);
    void lcd_init();
    void lcd_setCursor(char x, char y);
    void lcd_printChar();
    void lcd_printStr(const char *s);
    void rightShift();
    void leftShift();


#ifdef	__cplusplus
}
#endif

#endif	/* VAND1107_H */

