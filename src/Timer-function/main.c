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

unsigned int count = 59286;
int presc[] = {1,8,64,256,1024};
int i=1, n=12, steg=10000;

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


ISR(TIMER1_OVF_vect) // Overflow interrupt f�r 16 bitars timer (normal mode)
{
	PORTA ^= 0x80; // 0b1000 0000 // Invers p� signalen
	TCNT1 = count;
}


ISR(INT0_vect) // External vrider vridknappen interrupt
{
	cli();
	
	if (bit_is_set(PINB, 3))
	{
		count += steg;
	}
	else if (bit_is_clear(PINB, 3))
	{
		count -= steg;
	}
	
	_delay_ms(100);

	FREQ_count();
}

ISR(INT1_vect) // External trycker vridknappen interrupt
{
	cli();

	n++;
	
	if (n == 17) n = 12;
	
	LCD_goto(ROW4+1);

	if (n == 12) steg = 10000;
	else if (n == 13) steg = 1000;
	else if (n == 14) steg = 100;
	else if (n == 15) steg = 10;
	else steg = 1;

	sei();
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

	_delay_ms(100);

	FREQ_count();
}

void PORT_init(void)
{
	DDRA = 0x80; // 0b1000 0000
	DDRB = 0x00;
}

void INT_init(void)
{
	EICRA  = 0x0A; // 0b0000 1010
	EIMSK  = 0x03; // 0b0000 0011

	TCCR1B = (i+1); // i = 0..4
	TCNT1 = count;
	TIMSK1 = 0x01;

	PCICR = 0x02; // 0b0000 0010
	PCMSK1 = 0x07; // 0b0000 0111

	sei();
}

void FREQ_count()
{
	cli();

	freq = (float) 20000000 / 2 / presc[i] / (1 + 65535 - count);
	freq_helt = freq;
	freq_deci = (freq * 100.0) - (freq_helt * 100);

	// RAD 1

	LCD_goto(ROW1+17);
	LCD_puts(" Hz");
	
	LCD_goto(ROW1+12);
	LCD_puti(freq_deci);

	LCD_goto(ROW1+14);
	LCD_putc(',');

	LCD_goto(ROW1+9);
	LCD_puti(freq_helt);

	if (freq_deci < 10)
	{
		LCD_goto(ROW1+15);
		LCD_putc('0');
	}

	LCD_goto(ROW1);
	LCD_puts("Freq.:");

	// RAD 2

	LCD_goto(ROW2+12);
	LCD_puti(presc[i]);

	LCD_goto(ROW2);
	LCD_puts("Prescaler:");

	// RAD 3

	LCD_goto(ROW3+12);
	LCD_puti(count);

	LCD_goto(ROW3);
	LCD_puts("Count:");

	// RAD 4

	LCD_goto(ROW4+1);

	INT_init();
}
