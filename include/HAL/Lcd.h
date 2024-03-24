#ifndef LCD_H
#define LCD_H

#include "Error.h"
#include "std_types.h"

#define FIRSTROW 0x80
#define SECONDROW 0xC0

void Lcdinit_Asyn(void);
Error_enumStatus_t LcdWriteString_Asyn(const char * msg , uint8_t length);
Error_enumStatus_t Lcd_ClearScreen_Asyn(void);
//Error_enumStatus_t Lcd_GetStatus();
Error_enumStatus_t Lcd_SetCursorPosAsyn(uint8_t row , uint8_t col);

#endif
