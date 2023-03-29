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



/*	
	VARIABELN start

	Räknare:			Textsträngens position:						Output:
	start= 31			outputText[] = "    Hello World[ ]  ";		[ ]
	start= 30			outputText[] = "    Hello Worl[d]   ";		[d]
	start= 29			outputText[] = "    Hello Wor[l]d   ";		[ld]
	start= 28			outputText[] = "    Hello Wo[r]ld   ";		[rld]
	start= 27			outputText[] = "    Hello W[o]rld   ";		[orld]
	etc...

	until:
	start= 0			outputText[] = "[ ]     Hello World";		[         Hello World]	

		
	VARIABELN i

	Används endast för att skriva ut 20 karaktär från startposition mot höger, loopar då igenom 20 tecken för varje steg variabeln "start" minskar med 1.

	Exempel:			Textsträngens position:						Output:
	start= 27			outputText[] = "    Hello W[o]rld   ";		[orld]

	De 20 tecken som finns är då:
	rld                    "


	Då används i såhär:

	i[0]	i[1]	i[2]	i[3]	i[4]	i[5]   ->	i[19]
	'r'		'l'		'd'		' '		' '		' '			' '
*/