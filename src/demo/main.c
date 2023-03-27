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
			LeftShiftPins();
		}
		return 0;

}

void IOInit(void)
{
	//*****************************************************************************
	//
	//	Set data direction (DDRx) of I/O pins, 1 = output, 0 = input
	//	Set data register value (PORTx), 1 = high, 0 = low 
	//	Activate pull-up resitors if pin is input (PORTx), 1 = activate, 0 = deactivate
	// 
	//*****************************************************************************

//	DDRA = 0xFF; 			// Set pin PA0...PA7 to output
//	PORTA = 0x00; 			// Set pin PA0...PA7 low

//	DDRB = 0xFF; 			// Set pin PB0...PB7 to output
//	PORTB = 0x00; 			// Set pin PB0...PB7 low

//	DDRB = DDRB & ~0x07;	// Set pin PB0...PB2 to input
//	PORTB = PORTB | 0x01;	// Set pin PB0 high, enable pull-up resistor

//	DDRC = 0xFF; 			// Set pin PC0...PC7 to output
//	PORTC = 0x00; 			// Set pin PC0...PC7 low

	DDRD = 0xFF; 			// Set pin PD0...PD7 to output
	PORTD = 0x00; 			// Set pin PD0...PD7 low
}

void LeftShiftPins(void)
{	
	// *****************************************************************************
	//
	//	Left shifts register value with a frequency specified by DelayTime
	//	The amount of times the value is shifted is specified by the for-loop parameters
	//
	// *****************************************************************************
	
	int DelayTime = 2000;	// 200 ms
	short StepValue;
	
//	for(StepValue = 0; StepValue <= 7; StepValue++)
//	{	
//		PORTA = 1 << StepValue;
//		_delay_ms(DelayTime); 
//		PORTA = 0;
//	}
	
//	for(StepValue = 0; StepValue <= 7; StepValue++)
//	{	
//		PORTB = 1 << StepValue;
//		_delay_ms(DelayTime); 
//		PORTB = 0;
//	}
	
//	for(StepValue = 0; StepValue <= 7; StepValue++)
//	{	
//		PORTC = 1 << StepValue;
//		_delay_ms(DelayTime);
//		PORTC = 0; 
//	}
//
//	for(StepValue = 4; StepValue <= 7; StepValue++)
//	{	
//		PORTD = 1 << StepValue;
//		_delay_ms(DelayTime); 
//		PORTD = 0;
//	}

	PORTD = 0xF0;			// Set all pins on port D to high
	_delay_ms(DelayTime);	// Wait time
	PORTD = 0x00;			// Set all pins on port D to low
	_delay_ms(DelayTime);	// Wait time

}
