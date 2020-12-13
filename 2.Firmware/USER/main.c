#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"
#include "led.h"
#include "pwm.h"

#include "iic.h"
#include "ds3231.h"

#include "74HC595.h"


 
/************************************************
        TX     RX
串口1   PA9   PA10
串口2   PA2   PA3      
串口3   PB10  PB11

************************************************/
extern Calendar_OBJ calendar; 		//日历结构体	
int flag=0;
void BSP_Init(void)
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	TIM3_Int_Init(500-1,7200-1);//500ms
//	KEY_Init();
	DS3231_Init();
	HC595_Init();
		
}
int main(void)
{
	u8 str[8];

	BSP_Init();
//	Set_DS3231_Time(20,8,22,21,21,50,6);
	while(1)
	{		

		Get_DS3231_Time();
//		HC595_ShowNum(10048596);
//		HC595_printf(" 5201314");
		if(flag==1)
			sprintf((char *)str,"%02d %02d-%02d",calendar.hour,calendar.min,calendar.sec);
		if(flag==3)
			sprintf((char *)str,"%02d-%02d %02d",calendar.hour,calendar.min,calendar.sec);
		
		HC595_printf(str);
	}
	
	//HC595_Wheel();

}	

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{

		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update );  //清除TIMx的中断待处理位:TIM 中断源 

		flag++;			
		if(flag==4)
		{	
			flag=0;	
		}
	}
}



