/*
 * File:   main.c
 * Author: user
 *
 * Created on July 5, 2016, 8:01 PM
 */


#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define _XTAL_FREQ 8000000
#pragma config WDT = OFF
#pragma config FOSC = INTOSC_EC

void delaySeconds(unsigned seconds) {
    int a;
    for (a = 0; a < (seconds * 100); a++) {
        __delay_ms(10);
    }
}

void analogRead()
{
    unsigned int res;

    OSCCON = 0xF2;
    TRISA = 0b00000001;
    
    ADCON2=0b10001010;
    
    ADCON0 = 0b00000000;
    ADON = 1;
    GODONE = 1;

    while (GODONE);
    ADON = 0;
    res = (ADRESH<<8)|ADRESL;
}

void main(void) {
    TRISCbits.RC2 = 0;
    PORTCbits.RC2 = 0;
    
    PR2 = 0b00110001 ;
    T2CON = 0b00000101 ;
    CCPR1L = 0b00100101 ;
    CCP1CON = 0b00011100 ;
    
    while(1)
    {
        
    }

    return;
}
