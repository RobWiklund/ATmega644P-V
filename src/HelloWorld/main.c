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

    	LCD_init();			// Initialize the LCD
   	
		int DelayTime = 500;	// 500 ms
		int start = 31;
		short i;

		char outputText[] = "                    Hello World                    ";


		while (1) {

			for (i=0; i<20; i++){
				LCD_putc(outputText[start+i]);	// Print a string on the LCD
			}

			_delay_ms(DelayTime);
			LCD_goto(0);
			start--;
			
			if (start == 0)
			start = 31;
	}
	return 0;
}
