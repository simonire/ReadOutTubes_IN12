#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
								  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0_RCC 	RCC_APB2Periph_GPIOA
#define LED0_GPIO 		GPIOA
#define LED0_PIN 	GPIO_Pin_4
#define LED0 			PAout(4)// PB12

void LED_Init(void);//��ʼ��

		 				    
#endif