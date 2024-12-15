/*
 * File:   main.c
 * Author: No_One
 *
 * Created on November 22, 2024, 10:29 AM
 */


#include <xc.h>
#include <stdint.h>
#include "confic.h"

#define _XTAL_FREQ 4000000

void PWM1_SET_DUTY(uint16_t);


void main(void) {
    // TO RUN IN PWM
    CCP1M2 = 1;
    CCP1M3 = 1; 
    
    // RC2 MUST BE OUTPUT PIN
    TRISC2 = 0;
    PR2 = 124;          // to generate a 2khz pwm signal
    
    T2CKPS0 = 1;
    T2CKPS1 = 0;    // SET TIMER 2 Prescaler to match the 1:4 ratio
    
    TMR2ON   = 1;               // TURN ON THE TIMER
    
    uint16_t DC = 0;
    while(1){
        DC= 0;
        
        // gradually increase the LED brightness    
        while(DC < 500){
          PWM1_SET_DUTY(DC);
          DC++;
          __delay_ms(2);
          
        }
        __delay_ms(100);
        
        // gradually decrease the LED brightness
        while(DC > 0){
            PWM1_SET_DUTY(DC);
            DC --;
            __delay_ms(2);
            
        }
        __delay_ms(100);
    }
    
    return;
}


void PWM1_SET_DUTY(uint16_t DC){
    // we want to generate a 70% duty cycle of 2khz
    // so we need to put 350
    //CCP1CONbits.CCP1Y = (350) & 1;  // extract the first bit
//    CCP1CONbits.CCP1X = (350) & 2;  // EXTRACT THE SECOND BIT
//    CCPR1L = (350) >> 2;            // Move the 8 bits to the right.
    
    
    // general code
    // check if the value of DC is within 10-bit range
    if(DC < 1024){
        CCP1CONbits.CCP1Y = DC & 1;
        CCP1CONbits.CCP1X = DC & 2;
        CCPR1L = DC >> 2;
    }
}