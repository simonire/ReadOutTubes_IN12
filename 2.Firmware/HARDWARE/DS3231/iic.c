#include "iic.h"
void I2C_GPIO_Config(void)  
{  
    GPIO_InitTypeDef  GPIO_InitStructure;  
          
    RCC_APB2PeriphClockCmd(SCL_RCC_CLOCK | SDA_RCC_CLOCK ,ENABLE);  
          
    //��ʼ��SCL�ܽ�  
    GPIO_InitStructure.GPIO_Pin =  SCL_PIN;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;    
    GPIO_Init(SCL_PORT, &GPIO_InitStructure);  
          
    //��ʼ��SDA�ܽ�  
    GPIO_InitStructure.GPIO_Pin =  SDA_PIN;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
    GPIO_Init(SDA_PORT, &GPIO_InitStructure);  
}
/**************************************************************************  
* ������: void I2C_delay(void)
* ����  : ������ʱ
* ����  : ��
* ���  : ��
* ˵��  : �ڲ������i�����Ż��ٶȣ���������͵�5����д��
***************************************************************************/  
static void I2C_delay(void)  
{    
    u8 i=5;  
    while(i)  
    {  
        i--;  
    }  
}
/**************************************************************************
* ������: void I2C_Start(void)
* ����  : ��ʼ�ź�
* ����  : ��
* ���  : ��
* ˵��  :  
***************************************************************************/
void I2C_Start(void)
{
    SCL_H;    I2C_delay();
    SDA_H;    I2C_delay();
    SDA_L;    I2C_delay();
    SCL_L;    I2C_delay();
}
/**************************************************************************
* ������: I2C_Stop(void)
* ����  : ��ֹ�ź�
* ����  : ��
* ���  : ��
* ˵��  :  
***************************************************************************/
void I2C_Stop(void)
{
    SDA_L;    I2C_delay();
    SCL_H;    I2C_delay();
    SDA_H;    I2C_delay();
}
/**************************************************************************
* ������: void I2C_Ack(void)
* ����  : Ӧ���ź�
* ����  : ��
* ���  : ��
* ˵��  :  
***************************************************************************/
void I2C_Ack(void)  
{    
    SCL_L;  I2C_delay();  
    SDA_L;  I2C_delay();  
    SCL_H;  I2C_delay();  
    SCL_L;  I2C_delay();  
}
/**************************************************************************
* ������: void I2C_NoAck(void)
* ����  : ��Ӧ���ź�
* ����  : ��
* ���  : ��
* ˵��  :  
***************************************************************************/
void I2C_NoAck(void)  
{    
    SCL_L;  I2C_delay();  
    SDA_H;  I2C_delay();  
    SCL_H;  I2C_delay();  
    SCL_L;  I2C_delay();  
}  
/**************************************************************************
* ������: u8 I2C_WaitAck(void)
* ����  : �ȴ�Ӧ���ź�
* ����  : ��
* ���  : TRUE : ��Ӧ��
           FALSE : ��Ӧ��
* ˵��  :  
***************************************************************************/
u8 I2C_WaitAck(void)    
{  
    u8 ucErrTime=0;
    SCL_L;  I2C_delay();  
    SDA_H;  I2C_delay();  
    SCL_H;  I2C_delay();  
    while(SDA_read)  
    {  
        ucErrTime++;
        if(ucErrTime>250)
        {
            I2C_Stop();
            return 0;
        }
    }  
    SCL_L;  
    return 1;  
}  
/**************************************************************************  
* ������: void I2C_SendByte(u8 SendByte)  
* ����  : ����һ���ֽ�
* ����  : SendByte : �ֽ�����
* ���  : ��
* ˵��  : ���ݴӸ�λ����λ
***************************************************************************/
void I2C_SendByte(u8 SendByte)  
{  
    u8 i=8;  
    while(i--)  
    {  
        SCL_L;  
        I2C_delay();
        
        if(SendByte & 0x80)  
            SDA_H;    
        else  
            SDA_L;    
        SendByte<<=1;  
        I2C_delay();
        
        SCL_H;  
        I2C_delay();  
    }  
    SCL_L;  
}
/**************************************************************************
* ������: u8 I2C_ReceiveByte(void)  
* ����  : ��ȡһ���ֽ�
* ����  : ��  
* ���  : �ֽ�����
* ˵��  : ReceiveByte : ���ݴӸ�λ����λ
***************************************************************************/
u8 I2C_ReceiveByte(void)    
{  
    u8 i=8;  
    u8 ReceiveByte=0;  
          
    SDA_H;                
    while(i--)  
    {  
        ReceiveByte<<=1;        
        SCL_L;  
        I2C_delay();  
        SCL_H;
        I2C_delay();      
        if(SDA_read)  
        {  
            ReceiveByte|=0x01;  
        }  
    }  
    SCL_L;  
    return ReceiveByte;  
}

