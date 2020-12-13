#include "iic.h"
void I2C_GPIO_Config(void)  
{  
    GPIO_InitTypeDef  GPIO_InitStructure;  
          
    RCC_APB2PeriphClockCmd(SCL_RCC_CLOCK | SDA_RCC_CLOCK ,ENABLE);  
          
    //初始化SCL管脚  
    GPIO_InitStructure.GPIO_Pin =  SCL_PIN;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;    
    GPIO_Init(SCL_PORT, &GPIO_InitStructure);  
          
    //初始化SDA管脚  
    GPIO_InitStructure.GPIO_Pin =  SDA_PIN;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
    GPIO_Init(SDA_PORT, &GPIO_InitStructure);  
}
/**************************************************************************  
* 函数名: void I2C_delay(void)
* 描述  : 短暂延时
* 输入  : 无
* 输出  : 无
* 说明  : 内部定义的i可以优化速度，经测试最低到5还能写入
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
* 函数名: void I2C_Start(void)
* 描述  : 起始信号
* 输入  : 无
* 输出  : 无
* 说明  :  
***************************************************************************/
void I2C_Start(void)
{
    SCL_H;    I2C_delay();
    SDA_H;    I2C_delay();
    SDA_L;    I2C_delay();
    SCL_L;    I2C_delay();
}
/**************************************************************************
* 函数名: I2C_Stop(void)
* 描述  : 终止信号
* 输入  : 无
* 输出  : 无
* 说明  :  
***************************************************************************/
void I2C_Stop(void)
{
    SDA_L;    I2C_delay();
    SCL_H;    I2C_delay();
    SDA_H;    I2C_delay();
}
/**************************************************************************
* 函数名: void I2C_Ack(void)
* 描述  : 应答信号
* 输入  : 无
* 输出  : 无
* 说明  :  
***************************************************************************/
void I2C_Ack(void)  
{    
    SCL_L;  I2C_delay();  
    SDA_L;  I2C_delay();  
    SCL_H;  I2C_delay();  
    SCL_L;  I2C_delay();  
}
/**************************************************************************
* 函数名: void I2C_NoAck(void)
* 描述  : 无应答信号
* 输入  : 无
* 输出  : 无
* 说明  :  
***************************************************************************/
void I2C_NoAck(void)  
{    
    SCL_L;  I2C_delay();  
    SDA_H;  I2C_delay();  
    SCL_H;  I2C_delay();  
    SCL_L;  I2C_delay();  
}  
/**************************************************************************
* 函数名: u8 I2C_WaitAck(void)
* 描述  : 等待应答信号
* 输入  : 无
* 输出  : TRUE : 有应答
           FALSE : 无应答
* 说明  :  
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
* 函数名: void I2C_SendByte(u8 SendByte)  
* 描述  : 发送一个字节
* 输入  : SendByte : 字节数据
* 输出  : 无
* 说明  : 数据从高位到低位
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
* 函数名: u8 I2C_ReceiveByte(void)  
* 描述  : 读取一个字节
* 输入  : 无  
* 输出  : 字节数据
* 说明  : ReceiveByte : 数据从高位到低位
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

