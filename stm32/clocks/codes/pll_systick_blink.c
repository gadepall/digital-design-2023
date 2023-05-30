/* GVV Sharma 
 * September 9 , 2018
 * 
 * Blink a LED using HSE clock
 * and SysTick timer
 */
#include "stm32f103xb.h"

void delay_us(uint32_t time)
{
	/*
	 * Load the delay period in microseconds
	 */
	SysTick->LOAD = time;
	/*
	 * Clears the current value and the count flag
	 */
	SysTick->VAL = 0;
	
	/*
	 * Waits until the count ends
	 */
//	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	while(!(SysTick->CTRL & 0x00010000));
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

	//PLL Configuration
	
	RCC->CFGR =0x00010002;		//SYSCLOCK= PLL = 2 x HSE, 
	RCC->CR =RCC->CR =0x01010000;//HSE ON, PLL ON


	/*
	 * Enable the SysTick Timer with
	 * the CPU clock
	 */
//	SysTick->CTRL = 0x00000001; //SYSCLOCK/8
	SysTick->CTRL = 0x00000005;	//SYSCLOCK

	/*
	 * Enable the PA1 as a digital output
	 */
	GPIOA->CRL = 0x00000030;

	/*
	 * Infinite loop
	 */
	while(1)
	{
		GPIOA->BSRR = (1 << 1); //PA1 = 1 (Led OFF)
		delay_us(4000000); //500ms delay
		GPIOA->BRR = (1 << 1);	//PA1 = 0 (Led ON)
		delay_us(4000000); //500ms delay
	}
}
