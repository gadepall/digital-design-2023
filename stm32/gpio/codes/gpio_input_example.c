/*
GVV Sharma, August 20, 2018
Code released under GNU GPL
*/

/*
 * Turn LED ON/OFF
 */
#include "stm32f103xb.h"	

#define B7             0x0080                     // PB7 

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
	 * Enable the PB4 as a digital output and PB7 as input
	 */
	GPIOB->CRL = 0x80030000;	

	/*
	 * Infinite loop
	 */
	while(1)
	{
		if (((GPIOB->IDR & B7) == 0 ))  
			GPIOB->BRR = (1<<4); //PB4 = 0 (Led ON)		
		else
			GPIOB->BSRR = (1<<4); //PB4 = 1 (Led OFF)					

	}
}
