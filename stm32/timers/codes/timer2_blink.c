/* GVV Sharma 
 * August 31, 2018
 * 
 * Blink a LED using HSI clock and Timer1
 */
#include "stm32f103xb.h"

int main()
{
	/*
	 * Enable all Ports and Alternate Function clocks
	 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |
	    RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  // enable Timer2
	
	/*
	 * Disable JTAG and SWO (Free PB3, PB4 and PA15)
	 */
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

	TIM2->SMCR  = 0;	//Internal clock, 8MHz	
	TIM2->PSC	= 3999;	//Prescalar, dividing clock by 4000
	TIM2->CR1 	= 0x0001;	//enable Timer2
	TIM2->ARR 	= 999;	//Load Count


	/*
	 * Enable the PA1 as a digital output
	 */
	GPIOA->CRL = 0x00000030;

	/*
	 * Infinite loop
	 */
	while(1)
	{
		//half second on, half second off
		if(TIM2->SR & 0x0001)//check if ARR count complete
		{
			TIM2->SR &= ~0x0001;//clear status register SR
			GPIOA->ODR ^= (1 << 1);//blink LED through PA1
		}
	}
}

