#ifndef DISPLAY_H
#define DISPLAY_H

#include "display.c"

void LCD_Init(void);
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char data);
void LCD_String(const char *str);
void LCD_PulseEnable(void);
void LCD_SendNibble(unsigned char nibble);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Clear();
void display_mode();
void display_riego();
void display_valve();
void display_humedad();
void trigger_lcd();

#endif