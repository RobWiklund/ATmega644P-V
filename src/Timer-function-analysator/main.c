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
#include <avr/interrupt.h>
#include <stdlib.h>
#include "LCD.h"


void LCD_init();
void Timer_init();

unsigned int counter = 59286;
float freq;


int main (void)
{
	LCD_init();
	Timer_init();

	sei();

	while(1);

	return(0);
}

void Timer_init()
{
	TCCR0A = 0x02;	// WGM2/WGM1/WGM0 = 010 (mode 2 -CTC)
	TCCR0B = 0x07;	// External source T0 pin. Rising edge
	OCR0A = 0;		// R�kna till
	TIMSK0 = 0x02;	// Output compare A match IE
	
	TCCR1A = 0x00;	// WGM1/WGM0 = 00 (mode 4 - CTC)
	TCCR1B= 0x08;	// WGM3/WGM2 = 01 (mode 4 - CTC)
	TCCR1B |= 0x05;	// Prescale = 1024
	OCR1A = 19530;	// R�kna till 19530 = Trigga en g�ng per sek = 2 Hz
	TIMSK1 = 0x02;	// Output compare A Match IE
}

ISR(TIMER0_COMPA_vect)
{
	counter++;
}

ISR(TIMER1_COMPA_vect)
{
	freq = counter;
	counter = 0;
	
	
	// RAD 1

	LCD_goto(ROW1+6);
	LCD_puts("FREKVENS");

	// RAD 3
	
	LCD_goto(ROW3+11);
	LCD_puts(" Hz");
	

	LCD_goto(ROW3+6);
	LCD_puti(freq);


	// RAD 4

	LCD_goto(ROW4+1);
}

