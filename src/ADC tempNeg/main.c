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
		inADC = (ADCL>>6) + (ADCH<<2); // Både minsta och största signifikanta bitarna till inADC
		
		kvant8 = (inADC) / 51.15 * 5; // 1023 / 51.15 * 5 = 100, som är max
		kvant8deci = ((int) 100 * kvant8); // Tar omvandligen och lägger till 100, (4.17 -> 417)
		
		float kvant; // För kalk av "minustal"
		
		
		
		LCD_goto(ROW2+14); LCD_puts(" *C "); 
		LCD_goto(ROW2+9); LCD_puti((kvant8deci)); // Skriver ut decimaltalet utan första karaktären. (417 -> 17)
		LCD_goto(ROW2+11); LCD_putc(','); 	// Comma mellan talen (4,)
		LCD_goto(ROW2+6); LCD_puti(kvant); 	// Skriver ut talet före comma (4)
		LCD_goto(ROW1); LCD_puts("Temperatur:"); 
		 
				// Positiva tal
			if (kvant8 > 50){
				kvant = kvant8 -50; // till exmepel 100-50 = 50 som är max
				LCD_goto(ROW2+8); LCD_putc(' '); // inget minustecken / tar bort minustecken
			}
			else
			{	// Negativa tal
				kvant = kvant8; // vid kvant8 <= 50
				kvant = 50 - kvant; // 50 - 50 = 0, eller 0 - 50 = -50 men utan minustecken
				
				LCD_goto(ROW2+8); LCD_putc('-'); // Minustecken skriver över osynliga bitar i uint
			}
		
		LCD_goto(ROW4); // Markören till sista raden
		_delay_ms(100); 
		ADCStart();
		}
		
return(0); 		
} 
	

void ADCInit() 
{                            
ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN); // Ställer ner hastigheten på ad konvertern med 128 

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

*/


ADMUX = (1 << REFS0)|(1 << MUX0)| ((1 << ADLAR)); // ADLAR shiftad till vänster | MUX0 = ingång 0 | REFS0 = reference voltage source

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

}


void ADCStart()
{
	ADCSRA |= (1 << ADSC); // ADSC ändrar endast, skriver ej över något annat värde 

/*
	ADSC:	Function:
	1		ADC Start Conversion
*/

}
