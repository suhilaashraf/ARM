#ifndef LCDCFG_H_
#define LCDCFG_H_

#include "std_types.h"

#define LCDPINS 11

typedef enum
{
	RS,
	RW,
	EN,
	DB0,
	DB1,
	DB2,
	DB3,
	DB4,
	DB5,
	DB6,
	DB7
}LCD_PINS;

typedef struct 
{
    void* Lcdport;
    uint8_t Lcdpin;
}LCDCFG_str;



#endif