//--------------------------------------------------------------------------------
//
// Titel				: Digital IO demo program
// MCU					: Atmel ATMEGA164P/324P/644P
// Author				: Atmel
// Modifyer				: Robin Wiklund
// Description			: 
//
//--------------------------------------------------------------------------------

#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void INT_init();

int main (void)
{
	DDRD = (1 << PD7); //PORTD = 0x40; // 0b0000 0111 
	
	INT_init();
	while(1)
	{
		sleep_mode();
	}
	return(0);
}


void INT_init(void)
{
	
	TCCR2A = (1<<COM2A0) | (0<<COM2A1) | (1<<WGM21);
	TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);
	OCR2A = 255;
		
	
	// Sleep mode - IDLE 
	SMCR = (0<<SM2) | (0<<SM1) | (0<<SM0) | (1<<SE); // SE = Sleep enable

	// Sleep mode - Power-save
	//SMCR = (0<<SM2) | (1<<SM1) | (1<<SM0) | (1<<SE); // SE = Sleep enable

	// Sleep mode - Extended standby
	//SMCR = (1<<SM2) | (1<<SM1) | (1<<SM0) | (1<<SE); // SE = Sleep enable

	PRR0 = 0b10111111; // Power reduction, "0" = activated
	
}


// 38hz //
/*
TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);
OCR2A = 255;
*/

// 2500hz //
/*
TCCR2B = (1<<CS21) | (1<<CS20);
OCR2A = 124;
*/

// 250 000hz //
/*
TCCR2B = (1<<CS20);
OCR2A = 39;
*/