#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
							  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ�������.��ʹ��ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(LED0_RCC, ENABLE);	 //ʹ�ܶ˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = LED0_PIN;				 //LED0 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(   LED0_GPIO	, 	&GPIO_InitStructure);					 //�����趨������ʼ��GPIO
	 GPIO_SetBits(LED0_GPIO	,	LED0_PIN);						 //�����


}
 
