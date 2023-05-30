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
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  // enable Timer1
	
	/*
	 * Disable JTAG and SWO (Free PB3, PB4 and PA15)
	 */
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

	TIM1->SMCR  = 0;	//Internal clock, 8MHz	
	TIM1->PSC	= 999;	//Prescalar, dividing clock by 1000
	TIM1->CR1 	= 0x0001;	//enable Timer1
	TIM1->ARR 	= 999;	//Load Count
	TIM1->RCR 	= 3;	//Load Repetition Count	


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
		if(TIM1->SR & 0x0001)//check if ARR count complete
		{
			TIM1->SR &= ~0x0001;//clear status register SR
			GPIOA->ODR ^= (1 << 1);//blink LED through PA1
		}
	}
}
