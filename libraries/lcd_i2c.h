#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "lcd_i2c.c"

void PCF8574_write(unsigned char x);
void twi_lcd_4bit_send(unsigned char x);
void twi_lcd_cmd(const unsigned char x);
void twi_lcd_dwr(unsigned char x);
void twi_lcd_msg(const char *c);
void twi_lcd_clear();
void twi_lcd_init();

#endif