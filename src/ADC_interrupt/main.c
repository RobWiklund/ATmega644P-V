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
#include"LCD.h"

void ADCInit(); 

int main (void) 
{ 
	LCD_init(); 
	ADCInit(); 
	ADCSRA |= (1 << ADSC); // ADSC ändrar endast, skriver ej över något annat värde 

/*
	ADSC:	Function:
	1		ADC Start Conversion
*/

	while(1) {}
		
return(0); 		
} 

ISR(ADC_vect) {

		unsigned inADC;
		unsigned inADCH;
			
		float kvant8_10;
		float kvant8_8;
			
		int kvant8deci_10;
		int kvant8deci_8;


		inADC = (ADCL>>6) + (ADCH<<2); // Både minsta och största signifikanta bitarna till inAD
		inADCH = ADCH;
		
		LCD_goto(ROW1); LCD_puts("Voltage:");
		
		kvant8_10 = (inADC) / 1023.0 * 5; // 10 bitar, värden mellan 0 ... 5V
		kvant8deci_10 = ((int) 100 * kvant8_10);

		LCD_goto(ROW2+14); LCD_puts(" volt ");
		LCD_goto(ROW2+9); LCD_puti((kvant8deci_10));
		LCD_goto(ROW2+11); LCD_putc(',');
		LCD_goto(ROW2+6); LCD_puti(kvant8_10);
		LCD_goto(ROW2);
		
		LCD_puts("10 bit");

		
		// ------- 8 bit --------- //
		
		kvant8_8 = (inADCH) / 255.0 * 5; // 8 bitar, värden mellan 0 ... 5V
		kvant8deci_8 = ((int) 100 * kvant8_8);
		LCD_goto(ROW3+14); LCD_puts(" volt ");
		LCD_goto(ROW3+9); LCD_puti((kvant8deci_8));
		LCD_goto(ROW3+11); LCD_putc(',');
		LCD_goto(ROW3+6); LCD_puti(kvant8_8);
		LCD_goto(ROW3);
		
		LCD_puts("8 bit");
		LCD_goto(ROW4);
		_delay_ms(100);
	
	
	ADCSRA |= (1 << ADSC);// ADSC ändrar endast, skriver ej över något annat värde 

/*
	ADSC:	Function:
	1		ADC Start Conversion
*/
}


void ADCInit() 
{                            
	ADMUX = (1 << REFS0)|(1 << MUX0)| ((1 << ADLAR));
	
/*
	REFS1: 	REFS0:	Voltage Reference Selection:
	0		0 		AREF, Internal Vref turned off
->	0		1 		AVCC with external capacitor at AREF pin	-> Ställer in referensspänningen för att stabilisera spänningen och reducera störningar
	1		0 		Internal 1.1V Voltage Reference with external capacitor at AREF pin
	1		1 		Internal 2.56V Voltage Reference with external capacitor at AREF pin

	MUX2:	MUX:1	MUX0:	Single Ended Input:
	0		0		0		ADC0
->	0		0		1	 	ADC1	-> Ingångskälla port och pinne: PA1
	0		1		0	 	ADC2
	0		1		1	 	ADC3
	1		0		0 		ADC4
	1		0		1	 	ADC5
	1		1		0		ADC6
	1		1		1	 	ADC7

	ADLAR: 	ADC Adjust Result
	0		The result is right adjusted.
->	1		The result is left adjusted.
*/


	ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN) | (1 << ADIE);  // Ställer ner hastigheten på ad konvertern med 128 och interrupt
	
/*
	ADCSRA
	----------------------------------------		

	ADPS2:	ADPS1:	ADPS0:	Division Factor:
	0		0		0		2
	0		0		1		2
	0		1		0	 	4
	0		1		1 		8
	1		0		0	 	16
	1		0		1	 	32
	1		1		0 		64
->	1		1		1 		128 	-> Ställer ner hastigheten på ad konvertern med 128 


	ADEN:	Function:
	1		ADC Enable

	ADIE:	Function
	1		ADC Interrupt Enable

*/
	
	ADCSRB = (0 << ADTS0) | (0 << ADTS1) | (0 << ADTS2); // Trigger source -> Free running mode = 000. (default)

/*

	ADCSRB
	----------------------------------------	
	ADTS2	ADTS1	ADTS0	Trigger Source
	0		0		0 		Free Running mode
	0		0		1		Analog Comparator
	0		1		0 		External Interrupt Request 0
	0		1		1	 	Timer/Counter0 Compare Match A
	1		0		0		Timer/Counter0 Overflow
	1		0		1 		Timer/Counter1 Compare Match B
	1		1		0		Timer/Counter1 Overflow
	1		1		1	 	Timer/Counter1 Capture Event

*/

	sei(); // Set global interrupts
}