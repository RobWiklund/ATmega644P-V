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
void LCD_Hello_World(void);			
void InterruptInit(void);	

int main (void)
{
		short i = 0;
		int DelayTime = 1000;		// 1 s
	
     LCD_init();			// Initialize the LCD
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


void InterruptInit(void)
{
	//*****************************************************************************
	//
	//	External Interrupt setup
	//
	//*****************************************************************************
	
	cli();							// Disable global interrupts
	EICRA  = EICRA | 0b000001000;	// Enable falling edge to generate an interrupt request, s.60
	EIMSK  = EIMSK | 0b000000010;	// Enable external INT1 interrupt, s.61 typ - Calle
	sei(); 							// Enable global interrupts
}

ISR(INT1_vect)
{
	LCD_Hello_World(); // Or cut code here...
} 


void LCD_Hello_World(void)
{
	int start = 31;
	short i;
	int DelayTime = 200;	// 200 ms

	char outputText[] = "                    Hello World                    ";


	while (start != -1)
	{

		for (i=0; i<20; i++)
		{
			LCD_putc(outputText[start+i]);	// Print a string on the LCD
		}

		_delay_ms(DelayTime);
		LCD_goto(ROW4);
		start--;
	}
}