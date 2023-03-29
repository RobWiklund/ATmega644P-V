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
		inADC = (ADCL>>6) + (ADCH<<2); 	// inADC läser värden med 10 bitar, värden mellan 0-1023.
		
		kvant8 = (inADC) / 1023.0 * 5;	// Divideras med 1023 -> Största talet -> Omvandlar avlästa värden 0-1023 till 0-5 V. Då maxvärdet är 1023 blir det 1023/1023 * 5 = 5 
		kvant8deci = ((int) 100 * kvant8); // Tar omvandligen och lägger till 100, (4.17 -> 417)
		LCD_goto(ROW2+14); LCD_puts(" volt "); 
		LCD_goto(ROW2+9); LCD_puti((kvant8deci)); // Skriver ut decimaltalet utan första karaktären. (417 -> 17)
		LCD_goto(ROW2+11); LCD_putc(','); 
		LCD_goto(ROW2+6); LCD_puti(kvant8); // Skriver ut talet före comma (4)
		LCD_goto(ROW2);                                  
		
		LCD_puts("Voltage"); 
		LCD_goto(ROW4);  
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

}


void ADCStart()
{
	ADCSRA |= (1 << ADSC); // ADSC ändrar endast, skriver ej över något annat värde 

/*
	ADSC:	Function:
	1		ADC Start Conversion
*/
}
