/* 
 * File:   ocall018_button.h
 * Author: h-o-cally
 *
 * Created on October 16, 2018, 8:43 AM
 */

#ifndef OCALL018_BUTTON_H
#define	OCALL018_BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif

void initPushButton();
void __attribute__((__interrupt__, __auto_psv__))_IC1Interrupt(void);


#ifdef	__cplusplus
}
#endif

#endif	/* OCALL018_BUTTON_H */

