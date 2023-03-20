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
		inADC = (ADCL>>6) + (ADCH<<2); // B�de minst och st�rst signifikanta bitarna till inADC
		
		kvant8 = (inADC) / 51.15 * 5;
		kvant8deci = ((int) 100 * kvant8); 
		
		float kvant; // F�r kalk av "minustal"
		
		
		
		LCD_goto(ROW2+14); LCD_puts(" *C "); 
		LCD_goto(ROW2+9); LCD_puti((kvant8deci)); 
		LCD_goto(ROW2+11); LCD_putc(','); 
		LCD_goto(ROW2+6); LCD_puti(kvant); 
		LCD_goto(ROW1); LCD_puts("Temperatur:"); 
		 
		
			if (kvant8 > 50){
				kvant = kvant8 -50;
				LCD_goto(ROW2+8); LCD_putc(' ');
			}
			else
			{
				kvant =  kvant8;
				kvant = 50 - kvant; 
				
				LCD_goto(ROW2+8); LCD_putc('-'); // Minustecken skriver �ver osynliga bitar i uint
			}
		
		LCD_goto(ROW4); // Mark�ren till sista raden
		_delay_ms(100); 
		ADCStart();
		}
		
return(0); 		
} 
	

void ADCInit() 
{                            
ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN); // St�ller ner hastigheten p� ad konvertern med 128 
ADMUX = (1 << REFS0)|(1 << MUX0)| ((1 << ADLAR)); // ADLAR shiftad till v�nster | MUX0 = ing�ng 0 | REFS0 = reference voltage source
}


void ADCStart()
{
	ADCSRA |= (1 << ADSC); // ADSC = Set ADC to start conversion 
}
