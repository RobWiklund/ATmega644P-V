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
#include <avr/io.h>			// See HELP / avr-libc Reference Manual for detailed information
#include <util/delay.h>		// See HELP / avr-libc Reference Manual for detailed information
#include <avr/interrupt.h>	// See HELP / avr-libc Reference Manual for detailed information
#include "lcd.h"

void IOInit(void);		
void LCD_Hello_World(int);	
void InterruptInit(void);	

int main (void)
{
		short i = 0;
		int DelayTime = 1000;		// 1s delay time
	
     LCD_init();				// Initialize the LCD
     InterruptInit();		// Initialize interrupt
	 
	 while(1){
		LCD_goto(ROW1);
		LCD_puts("Running time:");		
		LCD_goto(ROW1 + 14);
		LCD_puti(i);				// Counting main program
		_delay_ms(DelayTime);
		i++;
	}
	 
     return 0;
}


void InterruptInit(void)		// Setup interrupt
{
	cli();					// Disable global interrupts
	PCICR |= (1 << PCIE1);	// Any change on any enabled PCINT15..8 pin will cause an interrupt.
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10); // Now we enable exactly the pin PCINT10 (above we enabled interrupts for 8-15)
	EICRA  = EICRA | 0b000001000;	// Enable falling edge to generate an interrupt request, s.60
	EIMSK  = EIMSK | 0b000000010;	// Enable external INT1 interrupt, s.61 typ - Calle
	sei(); 					// Enable global interrupts
}

ISR(INT1_vect) // Turnbutton press external interrupt
{
	LCD_Hello_World(ROW4);
}

ISR(PCINT1_vect) // 3 pressbuttons pin interrupts
{
	if (bit_is_clear(PINB, 2)) // leftmost button
	{
		LCD_Hello_World(ROW1);
	}
	
	else if (bit_is_clear(PINB, 1)) // middle button
	{
		LCD_Hello_World(ROW2);
	}
	
	else if (bit_is_set(PINB, 0)) // rightmost button
	{
		LCD_Hello_World(ROW3);
	}
	else{}
		
	PCIFR = 1<<PCIF1; // Flaggregister
} 


void LCD_Hello_World(int row) // Row as parameter
{
	int start = 31;
	short i;
	int DelayTime = 200;	// 200 ms delay time for LCD-scroll

	char outputText[] = "                    Hello World                    ";


	while (start != -1)
	{

		for (i=0; i<20; i++)
		{
			LCD_putc(outputText[start+i]);	// Print a string on the LCD
		}

		_delay_ms(DelayTime);
		LCD_goto(row); // Parameter
		start--;
	}
}