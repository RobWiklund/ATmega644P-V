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
	
	unsigned inADC; 
	unsigned inADCH; 
	
	float kvant8_10; 
	float kvant8_8;
	
	int kvant8deci_10;
	int kvant8deci_8;
	
	while(1) {   
				
		inADC = (ADCL>>6) + (ADCH<<2); // inADC läser värden med 10 bitar, värden mellan 0-1023.
		inADCH = ADCH;	// inADCH läser värden med 8 bitar (1111 1111), värden mellan 0-255. 
		
		// inADC och inADCH -> används i denna kod för att jämföra noggrannheten mellan 8 och 10 bitar 
		
		
		LCD_goto(ROW1); LCD_puts("Voltage:"); 
		
		// ------- 10 bitar --------- //

		kvant8_10 = (inADC) / 1023.0 * 5; // Divideras med 1023 -> Största talet -> Omvandlar avlästa värden 0-1023 till 0-5 V. Då maxvärdet är 1023 blir det 1023/1023 * 5 = 5 
		kvant8deci_10 = ((int) 100 * kvant8_10); // Tar omvandligen och lägger till 100, (4.17 -> 417)	
		
		LCD_goto(ROW2+14); LCD_puts(" volt "); 
		LCD_goto(ROW2+9); LCD_puti((kvant8deci_10)); // Skriver ut decimaltalet utan första karaktären. (417 -> 17)
		LCD_goto(ROW2+11); LCD_putc(','); // Comma mellan talen (4,)
		LCD_goto(ROW2+6); LCD_puti(kvant8_10); // Skriver ut talet före comma (4)
		LCD_goto(ROW2);                                  
		
		LCD_puts("10 bit"); 

		
		// ------- 8 bitar --------- //
		
		kvant8_8 = (inADCH) / 255.0 * 5; // Omvandlar avlästa värden 0-255 till 0-5 V. Då maxvärdet är 255 blir det 255/255 * 5 = 5 
		kvant8deci_8 = ((int) 100 * kvant8_8); // Tar omvandligen och lägger till 100, (4.17 -> 417)
		
		LCD_goto(ROW3+14); LCD_puts(" volt ");
		LCD_goto(ROW3+9); LCD_puti((kvant8deci_8)); // Skriver ut decimaltalet utan första karaktären. (417 -> 17)
		LCD_goto(ROW3+11); LCD_putc(','); // Comma mellan talen (4,)
		LCD_goto(ROW3+6); LCD_puti(kvant8_8); // Skriver ut talet före comma (4)
		LCD_goto(ROW3);
		
		LCD_puts("8 bit");
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
