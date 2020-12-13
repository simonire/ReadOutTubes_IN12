#include "74HC595.h"
#include "delay.h"
#include "pwm.h"
/*
【HC595_CLK】-->【SHCP_OUT】
【HC595_SCK】-->【STCP_OUT】
【HC595_DAT】-->【DS_OUT】
*/
u32 HC595_HEX[]={
0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x0100, 0x0200,/*0-9*/ 
};
int numdisplay[]={
27504983,75049838,50498389,4983894,49838940,98389405,83894057,38940572,89405726,94057261
};
NixieModStructure MOD[ModeBlock];	//全局结构体变量
/*==================================
* 函数名 ：HC595_Init()
* 调  用 ：void
* 参  数 ：void
* 返回值 ：void
* 结  果 ：初始化74HC595
* 备  注 ：
===================================*/
void HC595_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_HC595_PORT, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(HC595_PORT, &GPIO_InitStructure);

	GPIO_SetBits(HC595_PORT,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);
}


/*==================================
* 函数名 ：HC595_Send1Data(u8 data)
* 调  用 ：u8 data
* 参  数 ：u8 data
* 返回值 ：void
* 结  果 ：74HC595发送1B数据
* 备  注 ：
===================================*/
void HC595_Send1Data(u8 data)
{
	u8 j;
	for (j = 8; j > 0; j--)
	{
		if(data & 0x80)
			HC595_DAT=1;
		else
			HC595_DAT=0;
		
		HC595_CLK=0;delay_us(1);      //上升沿发生移位
		
		data <<= 1;
		
		HC595_CLK=1;delay_us(1);
	}
	//HC595Load();
}

/*==================================
* 函数名 ：HC595_Load(void)
* 调  用 ：void
* 参  数 ：void
* 返回值 ：void
* 结  果 ：74HC595启动传输
* 备  注 ：
===================================*/
void HC595_Load(void)
{
	HC595_SCK=0;
	HC595_SCK=1;
}
/*==================================
* 函数名 ：HC595_RowOut(u32 Data)
* 调  用 ：u32 Data
* 参  数 ：u32 Data
* 返回值 ：void
* 结  果 ：74HC595发送1帧数据
* 备  注 ：
===================================*/
void HC595_RowOut(u32 Data)//40808080
{
	HC595_Send1Data(Data >> 24);//0x40
	HC595_Send1Data(Data >> 16);//0x08
	HC595_Send1Data(Data >> 8);//0x0840
	HC595_Send1Data(Data >> 0);//0x084020
//	HC595_Load();
}


/*********************function**********************/
/*==================================
* 函数名 ：HC595_ShowNum(u32 number)
* 调  用 ：u32 number
* 参  数 ：u32 number
* 返回值 ：void
* 结  果 ：74HC595显示一个int型数字
* 备  注 ：
===================================*/
void HC595_ShowNum(u32 number)//e.g. : 68 or 54 //12345678
{
	u32 NumVal=0;
	u32 NumValFront,NumValBehind;//1234,5678
	u16 a,b,c,d,e,f,g,h;
	
	NumValFront = number / 10000;//1234	
	NumValBehind= number % 10000;//5678
	
	a=HC595_HEX[NumValFront/1000];
	b=HC595_HEX[NumValFront%1000/100];
	c=HC595_HEX[NumValFront%1000%100/10];
	d=HC595_HEX[NumValFront%10];
	e=HC595_HEX[NumValBehind/1000];
	f=HC595_HEX[NumValBehind%1000/100];
	g=HC595_HEX[NumValBehind%1000%100/10];
	h=HC595_HEX[NumValBehind%10];
	
	//0xABabABab	
	HC595_Send1Data(0x00);
	HC595_Send1Data(a >> 2 );
	NumVal = a<<30 | b<<20 | c<<10 | d;
	HC595_RowOut(NumVal);

	HC595_Send1Data(e >> 2 );
	NumVal = e<<30 | f<<20 | g<<10 | h;
	HC595_RowOut(NumVal);
	HC595_Load();
//	
	
}
/*==================================
* 函数名 ：HC595_Wheel(void)
* 调  用 ：void
* 参  数 ：void
* 返回值 ：
* 结  果 ：显示波浪效果
* 备  注 ：
===================================*/
void HC595_Wheel(void)
{
	u8 t=0;
	while(1)
	{
		for (t=0;t<=10;t++)
		{
			HC595_ShowNum(numdisplay[10-t]);
			delay_ms(8);
		}
	}
}
/*==================================
* 函数名 ：HC595_SetNum(u8 *p) && HC595_Update(void)
* 调  用 ：void
* 参  数 ：void
* 返回值 ：void
* 结  果 ：74HC595更新模块内数据
* 备  注 ：
===================================*/
void HC595_SetNum(u8 *p)//"010101."
{
	;
}
void HC595_Update(u16 Dots,u16 a,u16 b,u16 c,u16 d,u16 e,u16 f,u16 g,u16 h)
{
	;
}
/*==================================
* 函数名 ：HC595_printf(u8 *str)
* 调  用 ：*p
* 参  数 ：*p
* 返回值 ：void
* 结  果 ：74HC595显示字符带小数点
* 备  注 ：
===================================*/
void HC595_printf(u8 *str)//【56】//"1.048596"
{
	u8 j=0;
	u16 disp[9]={0x00};//012345678
	u32 NumVal=0;
////记录数组位数	
//	while (str[j]!='\0')		
//	{j++;cnt++;	}
//	cnt--;j=0;
//遍历数组
	for(j=0;j<8;j++)
	{
		if(str[j]>='0' && str[j]<='9')
		{
			disp[j+1] = HC595_HEX[str[j]-'0'];
		}

		if( str[j]==' ' )
			disp[j+1]= 0x00;
		
		if( str[j]=='-')
			disp[0] |= HC595_HEX[7-j];
	}	
	
	
	//0xABabABab	
	HC595_Send1Data(disp[0]);
	HC595_Send1Data(disp[1] >> 2 );
	NumVal = disp[1]<<30 | disp[2]<<20 | disp[3]<<10 | disp[4];
	HC595_RowOut(NumVal);

	HC595_Send1Data(disp[5] >> 2 );
	NumVal = disp[5]<<30 | disp[6]<<20 | disp[7]<<10 | disp[8];
	HC595_RowOut(NumVal);
	HC595_Load();
			
	
}



