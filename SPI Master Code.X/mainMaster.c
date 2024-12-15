/*
 * File:   mainMaster.c
 * Author: No_One
 *
 * Created on December 6, 2024, 7:08 PM
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>

#define  _XTAL_FREQ 4000000

#define UP RB0
#define Down RB1
#define Send RB2

void SPI_Master_Init();
void SPI_Write(uint8_t);



void main(void) {
    SPI_Master_Init();
    uint8_t  Data = 0;
    TRISB = 0x07;   // RB0, RB1, RB2 Are input pins (Bush buttons)
    TRISD = 0x00;   // Output port
    PORTD = 0x00;   // OFF
   
    while(1){
        if(UP){
            Data++;
            __delay_ms(250);
          
        }
         if(Down){
            Data--;
            __delay_ms(250);
          
        }
        if(Send){
            SPI_Write(Data);
            __delay_ms(250);
          
        }
        PORTD = Data;
       
    }
    
    
    return;
}

void SPI_Master_Init(){
    // set SPI mode to master + Set SCK Rate to Fosc/4
    SSPM0 = 0;
    SSPM1 = 0;
    SSPM2 = 0;
    SSPM3 = 0;
    
    // Enable the Synchounous Port
    SSPEN = 1;
    
    // configure the clock polarity & phase (SPI mode num 1)
    CKP = 0;
    CKE = 0;
    
    // configure the sampling time (Lets make it at the middle)
    SMP = 0;
    // configure the IO pins for SPI Master Mode
    
    TRISC5 = 0;  // SD0 -> OUTPUT
    TRISC4 = 1;  // SDI -> INPUT
    TRISC3 = 0;  // SCK -> OUTPUT
    // If Interrupts Are Needed, Un-comment The Line Below
  // SSPIE = 1; PEIE = 1; GIE = 1;
}

void SPI_Write(uint8_t Data){
    SSPBUF  = Data;// transfer the data to the buffer register 
     while(!SSPSTATbits.BF); // Un-comment it if you're Not Using Interrupts!
  // The Above While Loop Protects Against Writing To The Buffer
  // Before The Previous Transmission Ends
}