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
void ADCStart(); 

int main (void) 
{ 
	LCD_init(); 
	ADCInit(); 
	ADCStart(); 
	
	//unsigned inADCL; 
	unsigned inADC; 
	float kvant8; 
	int kvant8deci; 
	
	while(1) {      
		inADC = (ADCL>>6) + (ADCH<<2);
		
		kvant8 = (inADC) / 1023.0 * 5;
		kvant8deci = ((int) 100 * kvant8); 
		LCD_goto(ROW2+14); LCD_puts(" volt "); 
		LCD_goto(ROW2+9); LCD_puti((kvant8deci)); 
		LCD_goto(ROW2+11); LCD_putc(','); 
		LCD_goto(ROW2+6); LCD_puti(kvant8); 
		LCD_goto(ROW2);                                  
		
		LCD_puts("Sp�nning"); 
		LCD_goto(ROW4);  
		_delay_ms(100); 
		ADCStart();
		}
		
return(0); 		
} 
	

void ADCInit() 
{                            
ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN); // St�ller ner hastigheten p� ad konvertern med 128 
ADMUX = (1 << REFS0)|(1 << MUX0)| ((1 << ADLAR));
}


void ADCStart()
{
	ADCSRA |= (1 << ADSC);
}
