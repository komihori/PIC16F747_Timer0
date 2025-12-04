/*
 * File:   main.c
 * Author: komihori
 *
 * Created on 2025/12/02, 17:56
 */


// PIC16F747 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTRC oscillator; CLKO function on OSC2/CLKO/RA6 and port I/O function on OSC1/CLKI/RA7)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF       // MCLR/VPP/RE3 Pin Function Select bit (MCLR/VPP/RE3 pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (Enabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)
#pragma config CCP2MX = RC1     // CCP2 Multiplex bit (CCP2 is on RC1)
#pragma config CP = OFF         // Flash Program Memory Code Protection bits (Code protection off)

// CONFIG2
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)
#pragma config BORSEN = ON      // Brown-out Reset Software Enable bit (Enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 8000000

int count = 0;
int LEDflg = 0;

void __interrupt(__flags(TMR0IF)) InterruptManager(){
    TMR0IF = 0;
    count++;
    if(count > 25){
        count = 0;
        if(LEDflg == 0)
            LEDflg = 1;
        else
            LEDflg = 0;
    }
    return;
}

void main(void) {
    PORTA   = 0x00;
    TRISA = 0x00;
    OSCCON = 0b01111110;
    OSCTUNE = 0x00;
    OPTION_REG = 0b10000000;
    GIE    = 1;
    PEIE = 1;
    TMR0IE = 1;
    TMR0 = 0;
    
    while(1){        
        if(LEDflg == 1)
            RA1   = 0x01;
        else
            RA1   = 0x00;
    }
    return;
}
