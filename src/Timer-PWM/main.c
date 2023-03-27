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

void PORT_init();
void LCD_init();
void INT_init();
void FREQ_count();

float count = 0, bit10 = 1023.5;

unsigned duty_cycle = 0;
int presc[] = {1,8,64,256,1024};
int i=1;

float freq;
long freq_helt;
int freq_deci;

int main (void)
{
	PORT_init();
	LCD_init();
	INT_init();
	FREQ_count();

	while(1);
	
	return(0);
}


ISR(INT0_vect) // External vrider vridknappen interrupt
{
	cli();
	
	if (bit_is_set(PINB, 3))
	{
		count += (bit10*0.05);
	}
	else if (bit_is_clear(PINB, 3))
	{
		count -= (bit10*0.05);
	}
	
	
	if (count > bit10) {
		count = bit10;
	}
	else if (count < 0) {
		count = 0;
	}
	
	duty_cycle = (count/bit10)*100;
		
	_delay_ms(20);

	FREQ_count();
}


ISR(PCINT1_vect) // Pin change interrupt (tryckknapparna)
{
	if (bit_is_clear(PINB, 2))
	i++;
	else if (bit_is_clear(PINB, 1))
	i = 2;
	else if (bit_is_clear(PINB, 0))
	i--;

	if (i < 0) i = 0;
	else if (i > 4) i = 4;

	_delay_ms(20);

	FREQ_count();
}

void PORT_init(void)
{
	DDRA = 0x80; // 0b1000 0000
	DDRB = 0x00;
	DDRD = 0xF0;
}

void INT_init(void)
{
	EICRA  = 0x0A; // 0b0000 1010
	EIMSK  = 0x03; // 0b0000 0011

	PCICR = 0x02; // 0b0000 0010
	PCMSK1 = 0x07; // 0b0000 0111
	
	TCCR1A = 0b10000011;
	
	TCCR1B = (i+1); // i = 0..4
	TCCR1B |= (0<<WGM13) | (1<<WGM12);

	OCR1A = count;

	sei();
}

void FREQ_count()
{
	cli();

	// RAD 1

	LCD_goto(ROW1+2);
	LCD_puts(" Duty-Cycle:");
	
	// RAD 2

	LCD_goto(ROW2+2);
	LCD_puti(duty_cycle);
	
	LCD_goto(ROW2+8);
	LCD_putc('%');


	// RAD 3

	LCD_goto(ROW3+2);
	
	if (count == 1024){
		LCD_puti(count-1.0);
	}
	else {
		LCD_puti(count);
	}


	LCD_goto(ROW3+8);
	LCD_puts("(0-1023)");

	// RAD 4

	LCD_goto(ROW4+2);
	LCD_puti(presc[i]);

	LCD_goto(ROW4+8);
	LCD_puts("(Prescaler)");


	LCD_goto(ROW4+1);

	INT_init();
}
