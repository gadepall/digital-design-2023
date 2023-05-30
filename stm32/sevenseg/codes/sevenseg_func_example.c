/*
GVV Sharma, August 19, 2018
Code released under GNU GPL
*/

/*
 * Control Seven Segment Display through a function
 */
#include "stm32f103xb.h"	

void sevenseg(uint8_t dec)
{
	switch(dec)
	{
	case 0:
			GPIOB->BRR = (1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9); // (Led ON)		
			GPIOB->BSRR = (1<<3); // (Led OFF)					
			break;

	case 1:
			GPIOB->BRR = (1<<7)|(1<<8); // (Led ON)		
			GPIOB->BSRR = (1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<9); // (Led OFF)					
			break;

	case 2:
			GPIOB->BRR = (1<<3)|(1<<5)|(1<<6)|(1<<8)|(1<<9); // (Led ON)		
			GPIOB->BSRR = (1<<4)|(1<<7); // (Led OFF)					
			break;

	case 3:
			GPIOB->BRR = (1<<3)|(1<<6)|(1<<7)|(1<<8)|(1<<9); // (Led ON)		
			GPIOB->BSRR = (1<<4)|(1<<5); // (Led OFF)					
			break;

	case 4:
			GPIOB->BRR = (1<<3)|(1<<4)|(1<<7)|(1<<8); // (Led ON)		
			GPIOB->BSRR = (1<<5)|(1<<6)|(1<<9); // (Led OFF)					
			break;

	case 5:
			GPIOB->BRR = (1<<3)|(1<<4)|(1<<6)|(1<<7)|(1<<9); // (Led ON)		
			GPIOB->BSRR = (1<<5)|(1<<8); // (Led OFF)					
			break;

	case 6:
			GPIOB->BRR = (1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<9); // (Led ON)		
			GPIOB->BSRR = (1<<8); // (Led OFF)					
			break;

	case 7:
			GPIOB->BRR = (1<<7)|(1<<8)|(1<<9); // (Led ON)		
			GPIOB->BSRR = (1<<3)|(1<<4)|(1<<5)|(1<<6); // (Led OFF)					
			break;

	case 8:
			GPIOB->BRR = (1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9); // (Led ON)		
			break;

	case 9:
			GPIOB->BRR = (1<<3)|(1<<4)|(1<<6)|(1<<7)|(1<<8)|(1<<9); // (Led ON)		
			GPIOB->BSRR = (1<<5); // (Led OFF)					
			break;
	default:
			GPIOB->BRR = (1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<9); // (Led ON)		
			GPIOB->BSRR = (1<<7)|(1<<8); // (Led OFF)					
	
			break;


	}
}

int main()
{
	/*
	 * Enable all Ports and Alternate Function clocks
	 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |
	    RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN;
	
	/*
	 * Disable JTAG and SWO (Free PB3, PB4 and PA15)
	 */
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

	/*
	 * Enable the PB3-PB9 as a digital output
	 */
	GPIOB->CRL = 0x33333000;
	GPIOB->CRH = 0x00000033;		

	/*
	 * Infinite loop
	 */
	while(1)
	{
		sevenseg(10);

	}
}
