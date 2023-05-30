//Driving a seven segment display
//GVV Sharma
//July 30, 2018
#include "stm32f10x_lib.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//Setup GPIO pins
void Init_GPIO(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Initialize LED which connected to PC13 */
  // Enable PORTB Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}//end GPIO pin setup

int main(void)
{
  

Init_GPIO(); //configure gpio pins

//begin loop
  while (1) {


	 GPIOB->ODR = 0x03FF;//0
//	 GPIOB->ODR = 0x9FFF;//1

  }//end loop
  
}//end main
