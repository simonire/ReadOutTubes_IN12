#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
									  
//////////////////////////////////////////////////////////////////////////////////   	 
#define KEY0_RCC 	RCC_APB2Periph_GPIOA
#define KEY0_GPIO	GPIOA
#define KEY0_PIN 	GPIO_Pin_5
#define KEY0 		PAin(5)   	

//#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0


#define KEY0_PRES 	1	//KEY0按下

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
