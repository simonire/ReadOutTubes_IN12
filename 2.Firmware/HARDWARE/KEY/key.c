#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(KEY0_RCC,ENABLE);//ʹ��ʱ��

	GPIO_InitStructure.GPIO_Pin  = KEY0_PIN;//KEY0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(KEY0_GPIO, &GPIO_InitStructure);//��ʼ��GPIO

}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//ע��˺�������Ӧ���ȼ�,KEY0
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)
		key_up=1;  //֧������		  
	if(key_up&&(KEY0==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
	}else if(KEY0==1)key_up=1;	    
 	return 0;// �ް�������
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
