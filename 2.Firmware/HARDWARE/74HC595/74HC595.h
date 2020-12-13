#ifndef __74HC595_H
#define __74HC595_H
#include "sys.h"



#define RCC_HC595_PORT 	RCC_APB2Periph_GPIOA
#define HC595_PORT		GPIOA

#define HC595_CLK  PAout(5)//S_CLK_Pin12_SHCP_OUT 	
#define HC595_SCK  PAout(6)//R_CLK_Pin13_STCP_OUT	 
#define HC595_DAT  PAout(4)//MOSIO_Pin14_DS_OUT
#define HC595_OE   PAout(7)

typedef struct 
{
 	u32 Ones_CLO;		//ð��״̬
 	u32 Ones_NUM;		//��ʾ��λ����
	u32 Tens_NUM;
	u32 Tens_CLO;
}NixieModStructure;

#define ModeBlock 1

#define	NUM_OFF			0x000000		//��������ʾ

#define	Tens_NUM_0		(0x000001<<10)	//��ʾ����0
#define	Tens_NUM_1		(0x000002<<10)	//��ʾ����1
#define	Tens_NUM_2		(0x000004<<10)	//��ʾ����2
#define	Tens_NUM_3		(0x000008<<10)	//��ʾ����3
#define	Tens_NUM_4		(0x000010<<10)	//��ʾ����4
#define	Tens_NUM_5		(0x000020<<10)	//��ʾ����5
#define	Tens_NUM_6		(0x000040<<10)	//��ʾ����6
#define	Tens_NUM_7		(0x000080<<10)	//��ʾ����7
#define	Tens_NUM_8		(0x000100<<10)	//��ʾ����8
#define	Tens_NUM_9		(0x000200<<10)	//��ʾ����9

#define	Ones_NUM_0		0x000001		//��ʾ����0
#define	Ones_NUM_1		0x000002		//��ʾ����1
#define	Ones_NUM_2		0x000004		//��ʾ����2
#define	Ones_NUM_3		0x000008		//��ʾ����3
#define	Ones_NUM_4		0x000010		//��ʾ����4
#define	Ones_NUM_5		0x000020		//��ʾ����5
#define	Ones_NUM_6		0x000040		//��ʾ����6
#define	Ones_NUM_7		0x000080		//��ʾ����7
#define	Ones_NUM_8		0x000100		//��ʾ����8
#define	Ones_NUM_9		0x000200		//��ʾ����9

#define Ones_Ldp 		0x100000
#define Ones_Rdp		0x200000
#define Tens_Ldp		0x400000
#define Tens_Rdp		0x800000





void HC595_Init(void);
void HC595_Send1Data(u8 data);
void HC595_Load(void);
void HC595_RowOut(u32 Data);

void HC595_ShowNum(u32 number);
void HC595_Wheel(void);
//void HC595_SetNum(u8 *p);
//void HC595_Update(u8 mode);
void HC595_printf(u8 *str);

//void SaduduShow(u8 *p)
//{
//	u32 i;
//	for(i=0;i<2*ModeBlock;i++)
//	{
//		if(p[i]>='0' && p[i]<='9')
//		{
//			
//		}
//	}
//}

#endif

