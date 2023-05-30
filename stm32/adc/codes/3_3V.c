/* GVV Sharma 
 * October 8, 2018
 * Adapted from https://electronics.stackexchange.com/questions/347170/stm32f103-temperature-sensor-calibration-addresses
 * 3.3V as input to STM32 ADC1 and Display output on 16x2 HD44780-controlled LCD
 * Released under GNU GPL
 */

#include "stm32f103xb.h"
#include "lcd.h"
#include "stdlib.h"

/*
 * Delay function:
 * Uses the SysTick timer to wait for
 * an abitrary time in microseconds.
 *
 * The clock source is assumed to be
 * the internal 8MHz RC oscilator
 */
void delay_us(unsigned int time)
{
	/*
	 * (source is 1MHz and the time is specified in us)
	 */
	SysTick->LOAD = time;

	/*
	 * Clears the current value and the count flag
	 */
	SysTick->VAL = 0;

	/*
	 * Waits until the count ends
	 */
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}


// MAIN PROGRAM
int main(void)
{
char adstr[6];
	/*
	 * Enable all ports and Alternate Function clocks
	 */
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |
	    RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_AFIOEN;
	
	/*
	 * Disable JTAG and SWO (Free PB3, PB4 and PA15)
	 */
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;


	/*
	 * Enable the SysTick Timer
	 */
	SysTick->CTRL = 0x00000001;// 1 MHz Clock

// Select a clock source for ADC


RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;     // Enable ADC1 to use APB2 BUS
RCC->CR |= RCC_CR_HSION;  // set the internal clock on (8MHz)
while((RCC->CR & RCC_CR_HSIRDY) == 0){}     // wait until HSI is ready

RCC->CFGR &= ~(RCC_CFGR_HPRE);  // set AHB prescaler to 1
RCC->CFGR &= ~(RCC_CFGR_PPRE2); // set APB2 prescaler to 1 (PCLK2)
RCC->CFGR |= RCC_CFGR_ADCPRE;   // use ADC prescaler

// Select a Sampling rate
//ADC1->SMPR1 |= ADC_SMPR1_SMP16;
//ADC1->SQR3 |= ADC_SQR3_SQ1_4; //set to convert the channel 16 fitst

ADC1->SMPR1 |= ADC_SMPR2_SMP9;
ADC1->SQR3 |=  0x000000120; //set to convert the channel 9 second

// enable temperature sensor
ADC1->CR2 |= ADC_CR2_TSVREFE;

// ADC Calibration
// Power up the ADC and then Calibrate it
ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CAL | ADC_CR2_CONT;
// wait until the calibration is completed and reseted
while((ADC1->CR2 & ADC_CR2_CAL) == 1){}


	/*
	 * 100ms delay to ensure that the
	 * LCD display is properly powered on 
	 */
	delay_us(100000);

GPIOA->CRL = (GPIOA->CRL & 0xFF000000) | 0x00333333;//set A0-A5 as outputs
GPIOB->CRL = 0x00000080;	//set B1 as input




 LCD_Init(); // initialize LCD controller

 while(1)
 {

   ADC1->CR2 |= ADC_CR2_ADON;
    while((ADC1->SR & ADC_SR_EOC) == 0){} // wait for end of conversion
itoa(ADC1->DR, adstr, 10);    
LCD_Clear();
//LCD_Message("Jai Hind"); 
LCD_Message(adstr); 

delay_us(600000);     // set animation speed 600 ms
}
}
