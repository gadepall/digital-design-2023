/* GVV Sharma 
 * September 24, 2018
 * Adapted from LCD code for AVR-GCC
 * Augusto Fraga Giachero, 2015
 * Display string on 16x2 HD44780-controlled LCD
 * 
 * Released under GNU GPL
 */

#include "stm32f103xb.h"

// TYPEDEFS
typedef uint8_t byte; // changed the name


// ------------------
//LCD DRIVER ROUTINES
//
// Routines:
// LCD_Init initializes the LCD controller
// LCD_Cmd sends LCD controller command
// LCD_Char sends single ascii character to display
// LCD_Clear clears the LCD display & homes cursor
// LCD_Message displays a string
// GPIOA is used for data communications with the HD44780-controlled LCD.
//// The following defines are controller commands
#define CLEARDISPLAY 0x01

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

void PulseEnableLine ()
{
GPIOA->BSRR = 2; // take LCD enable line high
 delay_us(40); // wait 40 microseconds
GPIOA->BRR = 2; // take LCD enable line low
}
void SendNibble(byte data)
{
GPIOA->BRR = ~(data << 2) & 0b00111100;
GPIOA->BSRR = (data << 2) & 0b00111100;
 
 PulseEnableLine(); // clock 4 bits into controller
}
void SendByte (byte data)
{

 SendNibble(data >> 4); // send upper 4 bits
 SendNibble(data); // send lower 4 bits
}
void LCD_Cmd (byte cmd)
{
 GPIOA->BRR = 1; // R/S line 0 = command data
 SendByte(cmd); // send it
}
void LCD_Char (byte ch)
{
GPIOA->BSRR = 1;// R/S line 1 = character data
 SendByte(ch); // send it
}
void LCD_Init()
{
	
 LCD_Cmd(0x33); // initialize controller
 LCD_Cmd(0x32); // set to 4-bit input mode
 LCD_Cmd(0x28); // 2 line, 5x7 matrix
 LCD_Cmd(0x0C); // turn cursor off (0x0E to enable)
 LCD_Cmd(0x06); // cursor direction = right
 LCD_Cmd(0x01); // start with clear display
 delay_us(3000); // wait for LCD to initialize

}
void LCD_Clear() // clear the LCD display
{
 LCD_Cmd(CLEARDISPLAY);
 delay_us(3000); // wait for LCD to process command

}

void LCD_Message(const char *text) // display string on LCD
{
 while (*text) // do until /0 character
 LCD_Char(*text++); // send char & update char pointer
}


// MAIN PROGRAM
int main(void)
{

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


	/*
	 * 100ms delay to ensure that the
	 * LCD display is properly powered on 
	 */
	delay_us(100000);


GPIOA->CRL = (GPIOA->CRL & 0xFF000000) | 0x00333333;//set A0-A5 as outputs

 LCD_Init(); // initialize LCD controller

 while(1)
 {
LCD_Clear();
LCD_Message("Jai Hind"); 

delay_us(600000);     // set animation speed 600 ms
}
}
