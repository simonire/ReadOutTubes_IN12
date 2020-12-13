#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

/* LED亮度等级 PWM表,指数曲线 ，此表使用工程目录下的python脚本index_wave.py生成*/


void TIM3_Int_Init(u16 arr,u16 psc);
#endif


