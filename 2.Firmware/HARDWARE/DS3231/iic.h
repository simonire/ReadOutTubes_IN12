#ifndef __IIC_H
#define __IIC_H
#include "sys.h"

#define SCL_PIN GPIO_Pin_6//板上第8针
#define SDA_PIN GPIO_Pin_7//板上第9针

#define SCL_PORT GPIOB
#define SDA_PORT GPIOB

#define SCL_RCC_CLOCK RCC_APB2Periph_GPIOB
#define SDA_RCC_CLOCK RCC_APB2Periph_GPIOB

#define SCL_H  SCL_PORT->BSRR = SCL_PIN
#define SCL_L  SCL_PORT->BRR = SCL_PIN
 
#define SDA_H  SDA_PORT->BSRR = SDA_PIN
#define SDA_L  SDA_PORT->BRR = SDA_PIN

#define SCL_read SCL_PORT->IDR& SCL_PIN
#define SDA_read SDA_PORT->IDR& SDA_PIN

//#define I2C_PageSize??8??//24C02每页8字节??

void I2C_GPIO_Config(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
u8 I2C_WaitAck(void);
void I2C_SendByte(u8 SendByte);
u8 I2C_ReceiveByte(void);

//bool I2C_WriteByte(u8 SendByte, u16 WriteAddress, u8 DeviceAddress);
//bool I2C_BufferWrite(u8* pBuffer, u8 length, u16 WriteAddress, u8 DeviceAddress);
//void I2C_PageWrite(u8* pBuffer, u8 length, u16 WriteAddress, u8 DeviceAddress);
//bool I2C_ReadByte(u8* pBuffer, u8 length, u16 ReadAddress, u8 DeviceAddress);
//void I2C_Test(void);

#endif



