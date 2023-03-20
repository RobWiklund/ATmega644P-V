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
	DDRA = 0x20;
	
	INT_init();
	while(1)
	{
		sleep_mode();
	}
	
	return(0);
}

ISR(TIMER2_COMPA_vect)
{
	PORTA ^= 0x20; // 0b1000 0000 // Invers p� signalen
}


void INT_init(void)
{
	TCCR2A = (1<<WGM21);
	TCCR2B = (1<<CS20);
	OCR2A = 39;
	TIMSK2 = (1<<OCIE2A);
	
	// Sleep mode - IDLE 
	//SMCR = (0<<SM2) | (0<<SM1) | (0<<SM0) | (1<<SE); // SE = Sleep enable

	// Sleep mode - Power-save
	//SMCR = (0<<SM2) | (1<<SM1) | (1<<SM0) | (1<<SE); // SE = Sleep enable

	// Sleep mode - Extended standby
	SMCR = (1<<SM2) | (1<<SM1) | (1<<SM0) | (1<<SE); // SE = Sleep enable

	PRR0 = 0b10111111; // Power reduction, "0" = activated

	sei();
}


// 38hz //
/*
TCCR2A = (1<<WGM21);
TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);
OCR2A = 255;
TIMSK2 = (1<<OCIE2A);
*/

// 2500hz //
/*
TCCR2A = (1<<WGM21);
TCCR2B = (1<<CS21) | (1<<CS20);
OCR2A = 124;
TIMSK2 = (1<<OCIE2A);
*/

// 250 000hz //
/*
TCCR2A = (1<<WGM21);
TCCR2B = (1<<CS20);
OCR2A = 39;
TIMSK2 = (1<<OCIE2A);
*/