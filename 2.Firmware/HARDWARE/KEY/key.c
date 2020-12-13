#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(KEY0_RCC,ENABLE);//使能时钟

	GPIO_InitStructure.GPIO_Pin  = KEY0_PIN;//KEY0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(KEY0_GPIO, &GPIO_InitStructure);//初始化GPIO

}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//注意此函数有响应优先级,KEY0
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)
		key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
	}else if(KEY0==1)key_up=1;	    
 	return 0;// 无按键按下
}


//		key = KEY_Scan(0);
//		if(key){	
//			switch(key){
//				case KEY0_PRES:	{
//					LED0 = !LED0;
//					break;}
//			}
//		}
//		else delay_ms(10);
