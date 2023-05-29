/* GVV Sharma 
 * September 5, 2018
 * 
 * Blink a LED using Timer1 as master and Timer2 as slave
 */
#include "stm32f103xb.h"


int main()
{
	/*
	 * Enable all Ports and Alternate Function clocks
	 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |
	    RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN;

	/* enable the timer peripherals: */	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  // enable Timer1
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  // enable Timer2	

	/*
	 * Disable JTAG and SWO (Free PB3, PB4 and PA15)
	 */
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
	
	/* Master - TIM1  */
	TIM1->SMCR  = 0;	//Internal clock, 8MHz	
	TIM1->PSC	= 0;	//Prescalar
	TIM1->ARR 	= 999;	//Load Count
	TIM1->RCR 	= 0;	//Load Repetition Count	
	TIM1->CR2	= 0x0020;//MMS = 010

	/* Slave - TIM2  */
	TIM2->PSC	= 0;	//Prescalar
	TIM2->SMCR	= 0x0007;//TS = 000, SMS = 111	
	TIM2->ARR 	= 999;	//Load Count
		
	TIM2->CR1 	= 0x0001;	//enable Timer2	
	TIM1->CR1 	= 0x0001;	//enable Timer1

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
		if(TIM2->SR & 0x0001)//check if TIM2 ARR count complete
		{
			TIM2->SR &= ~0x0001;//clear TIM2 status register SR
			GPIOA->ODR ^= (1 << 1);//blink LED through PA1
		}
	}
}
