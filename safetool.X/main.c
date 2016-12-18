/*
 * File:   main.c
 * Author: User
 *
 * Created on July 2, 2016, 12:26 PM
 */

#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 8000000
#pragma config WDT = OFF
#pragma config FOSC = INTOSC_EC

void delaySeconds(unsigned seconds) {
    int a;
    for (a = 0; a < (seconds * 100); a++) {
        __delay_ms(10);
    }
}

int main() {
    int state;
    unsigned long tUnlocked, tRemaining, tSecondsPerHour;
    double tHours, tLocked;
    OSCCON = 0xF2;
    TRISAbits.TRISA0 = 0; //YELLOW LED
    TRISAbits.TRISA1 = 0; //RED LED
    TRISAbits.TRISA2 = 0; //GREEN LED
    TRISAbits.TRISA3 = 0; //SOLENOID
    TRISAbits.TRISA4 = 1; //SWITCH
    
    state = 1;
    tHours = 22;
    tSecondsPerHour = 3600;
    tLocked = tHours * tSecondsPerHour;
    tUnlocked = 10;
    tRemaining = tLocked;
    
    LATAbits.LATA3 = 0;
    LATAbits.LATA0 = 1;
    LATAbits.LATA2 = 0;
    delaySeconds(1);
    while (1) {
        switch (state) {
            case 0: // unlocked
                LATAbits.LATA2 = 1;
                LATAbits.LATA1 = 0;
                LATAbits.LATA0 = 0;
                while (1) {
                    if (PORTAbits.RA4 == 0) {
                        LATAbits.LATA2 = 0;
                        LATAbits.LATA0 = 1;
                        LATAbits.LATA3 = 1;
                        delaySeconds(tUnlocked);
                        LATAbits.LATA0 = 0;
                        state = 1;
                        break;
                    }
                }
                state = 1;
                break;
            case 1: // locked
                LATAbits.LATA0 = 0;
                LATAbits.LATA1 = 1;
                LATAbits.LATA2 = 0;
                LATAbits.LATA3 = 0;
                tRemaining = tLocked;
                while (tRemaining > 0) {
                    delaySeconds(1);
                    tRemaining--;
                }
                state = 0;
                break;
        }
    }
    return 0;
}
