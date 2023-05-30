/* GVV Sharma 
 * September 6, 2018
 * 
 * Decade Counter using  Timer1 as master and Timer2 as slave
 */
#include "stm32f103xb.h"

void sysinit(void);
void master(uint16_t psc, uint16_t arr, uint8_t rcr);
void slave(uint16_t psc, uint16_t arr);
void sevenseg(uint8_t dec);

int main()
{
	sysinit();
	//Clock frequency
	master(1,249,1);//8M/(2x250x2) = 8K
	slave(8999,9);//8K/(90000) = 8/90
	/*
	 * Infinite loop
	 */
	while(1)
	{
			sevenseg(TIM2->CNT);	//Extract values from CNT register

		//half second on, half second off
		if(TIM2->SR & 0x0001)//check if TIM2 ARR count complete
		{
			TIM2->SR &= ~0x0001;//clear TIM2 status register SR
			GPIOA->ODR ^= (1 << 1);//blink LED through PA1
		}
	}
}
void sysinit(void)
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
	/*
	 * Enable the PA1 as a digital output
	 */
	GPIOA->CRL = 0x00000030;
	/*
	 * Enable the PB3-PB9 as a digital output
	 */
	GPIOB->CRL = 0x33333000;
	GPIOB->CRH = 0x00000033;		
	
	
}
	/* Master - TIM1  */
void master(uint16_t psc, uint16_t arr, uint8_t rcr)
{
	TIM1->SMCR  = 0;	//Internal clock, 8MHz	
	TIM1->PSC	= psc;	//Prescalar
	TIM1->ARR 	= arr;	//Load Count
	TIM1->RCR 	= rcr;	//Load Repetition Count	
	TIM1->CR2	= 0x0020;//MMS = 010
	TIM1->CR1 	= 0x0001;	//enable Timer1	
}
	/* Slave - TIM2  */
void slave(uint16_t psc, uint16_t arr)
{

	TIM2->PSC	= psc;	//Prescalar
	TIM2->SMCR	= 0x0007;//TS = 000, SMS = 111	
	TIM2->ARR 	= arr;	//Load Count
	TIM2->CR1 	= 0x0001;	//enable Timer2	
	
}
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
