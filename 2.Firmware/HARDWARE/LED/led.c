#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
							  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化输出口.并使能时钟		    
//LED IO初始化
void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(LED0_RCC, ENABLE);	 //使能端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = LED0_PIN;				 //LED0 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(   LED0_GPIO	, 	&GPIO_InitStructure);					 //根据设定参数初始化GPIO
	 GPIO_SetBits(LED0_GPIO	,	LED0_PIN);						 //输出高


}
 
