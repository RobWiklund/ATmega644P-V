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
	ADCSRA |= (1 << ADSC); 


	while(1) {   
			
	}
		
return(0); 		
} 


ISR(ADC_vect) {

		unsigned inADC;
		unsigned inADCH;
			
		float kvant8_10;
		float kvant8_8;
			
		int kvant8deci_10;
		int kvant8deci_8;


		inADC = (ADCL>>6) + (ADCH<<2);
		inADCH = ADCH;
		
		LCD_goto(ROW1); LCD_puts("Voltage:");
		kvant8_10 = (inADC) / 1023.0 * 5;
		kvant8deci_10 = ((int) 100 * kvant8_10);
		LCD_goto(ROW2+14); LCD_puts(" volt ");
		LCD_goto(ROW2+9); LCD_puti((kvant8deci_10));
		LCD_goto(ROW2+11); LCD_putc(',');
		LCD_goto(ROW2+6); LCD_puti(kvant8_10);
		LCD_goto(ROW2);
		
		LCD_puts("10 bit");

		
		// ------- 8 bit --------- //
		
		kvant8_8 = (inADCH) / 255.0 * 5;
		kvant8deci_8 = ((int) 100 * kvant8_8);
		LCD_goto(ROW3+14); LCD_puts(" volt ");
		LCD_goto(ROW3+9); LCD_puti((kvant8deci_8));
		LCD_goto(ROW3+11); LCD_putc(',');
		LCD_goto(ROW3+6); LCD_puti(kvant8_8);
		LCD_goto(ROW3);
		
		LCD_puts("8 bit");
		LCD_goto(ROW4);
		_delay_ms(100);
	
	
	ADCSRA |= (1 << ADSC);
}


void ADCInit() 
{                            
	ADMUX = (1 << REFS0)|(1 << MUX0)| ((1 << ADLAR));
	
	ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN) | (1 << ADIE);  // St�ller ner hastigheten p� ad konvertern med 128 och interrupt
	ADCSRB = (0 << ADTS0) | (0 << ADTS1) | (0 << ADTS2); // Trigger source -> Free running mode = 000. (default)

	sei(); // Set global interrupts
}