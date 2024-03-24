#include "Lcd.h"

#define FIRSTROW 0x80
#define SECONDROW 0xC0

void LCD_TEST (void)
{
    static uint8_t time;

    if (time == 1)
    {
        LcdWriteString_Asyn("Amina", 5);
    }
    if (time == 3)
    {
       Lcd_SetCursorPosAsyn( SECONDROW , 0 );    
    }
    if (time == 4)
    {
        LcdWriteString_Asyn("Suhila Ashraf", 13);
    }
    time ++;

} 
