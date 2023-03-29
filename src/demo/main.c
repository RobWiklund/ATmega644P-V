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
#include "lcd.h"

void IOInit(void);		
void LeftShiftPins(void);				

int main (void)
{
	IOInit();		

    	LCD_init();			// Initialize the LCD
   	
    	LCD_goto(ROW1);		// Move cursor to row 1 on LCD
    	LCD_puts("ERROR");	// Print a string on the LCD
   	
    	LCD_goto(ROW1+6);	// Move cursor to given position
		LCD_putc('-');		// Print a char on the LCD
		
    	LCD_goto(ROW1+7);	// Move cursor to given position
    	LCD_puti(4545);		// Print an integer on the LCD

		while(1)
		{
			LeftShiftPins(); // Kör loop
		}
		return 0;

}

void IOInit(void)
{
	DDRD = 0xFF; 			// Set pin PD0...PD7 to output
	PORTD = 0x00; 			// Set pin PD0...PD7 low
}

void LeftShiftPins(void)
{	
	// Blinkar PortD, på och av

	int DelayTime = 2000;	// 200 ms

	PORTD = 0xF0;			// Set all pins on port D to high
	_delay_ms(DelayTime);	// Wait time
	PORTD = 0x00;			// Set all pins on port D to low
	_delay_ms(DelayTime);	// Wait time

}
