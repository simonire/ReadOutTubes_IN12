#ifndef __DS3231_H__
#define __DS3231_H__
#include "sys.h"


typedef struct
{
    u8   hour;
    u8   min;
    u8   sec;            
    u32  w_year;
    u8   w_month;
    u8   w_date;
    u8   week;        
    u8   temper_H;
    u8   temper_L;
}Calendar_OBJ;
extern Calendar_OBJ calendar;    //日历结构体
extern u8 const mon_table[12];    //月份日期数据表
void DS3231_Init(void);
void Get_DS3231_Time(void);      
//u8 RTC_Get_Week(u16 year,u8 month,u8 day);
void Set_DS3231_Time(u8 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec,u8 week);//设置时间 
int day_diff(int year_start, int month_start, int day_start, int year_end, int month_end, int day_end);
#endif

