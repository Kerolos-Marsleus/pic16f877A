/*
 * File:   mainSlave.c
 * Author: No_One
 *
 * Created on December 7, 2024, 9:11 AM
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>

#define _XTAL_FREQ 4000000

void SPI_Slave_Init();
uint8_t SPI_Read();
void SPI_Read_String(uint8_t *, uint16_t);
uint8_t Data;
void main(void) {
    SPI_Slave_Init();
    TRISB = 0;
    while(1){
        PORTB = SPI_Read();
    }
    ?
    return;
}
    uint8_t Data;
void SPI_Slave_Init(){
    // SET SPI to Slave mode ++ SS enable
    SSPM0 = 0;
    SSPM1 = 0;
    SSPM2 = 1;
    SSPM3 = 0;
    
    // Enable the synchrounous Serial Port
    SSPEN = 1;
    
    // Config the clock polarity and phase  (SPI Mode Number 1)
    CKP = 0;
    CKE = 0;
    
    // Clear the SMP Bit
    SMP = 0;
    
    // configure the IO pins for SPI Master mode
    TRISC5 = 0;     // SDO -> Output
    TRISC4 = 1;     // SDI _> input
    TRISC3 = 1;     // SCK -> Input
    
    // set SS (RA5 / AN4) to be Digital IO
    PCFG3 = 0;
    PCFG2 = 1;
    PCFG1 = 0;
    PCFG0 = 0;
    TRISA5 = 1;  // ss-> input
    
    // Enable interrupts 
    SSPIE = 1;
    PEIE = 1;
    GIE = 1;
    
}

uint8_t SPI_Read(){

    if(BF){ // Read the buffer
        Data = SSPBUF;
        BF = 0; // Clear the buffer field indicator
        SSPOV = 0;          // Clear the overflow indicator bit
        return Data;
    }
}
void SPI_Read_String(uint8_t *Output, uint16_t length){
    uint16_t i;
    for(int i = 0; i < length; i++)
        Output[i] = SPI_Read();
}

void __interrupt() ISR (){
    if(SSPIF){
        Data = SSPBUF;
        SSPIE = 0;
    }
}

