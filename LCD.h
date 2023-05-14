#ifndef _LCD_H__
#define _LCD_H__

#include "REGDEF.h"
#include "GPIO.h"
#include "SYSTICK.h"
#include <stdio.h>

#define LCD_DATA_PORT 'B'
#define LCD_CTRL_PORT 'A'
#define LCD_EN_PIN 7
#define LCD_RW_PIN 6
#define LCD_RS_PIN 5

void LCD_setup(void);
void LCD_CMD(uint8_t command);

void LCD_WRITE_CHAR(uint8_t c);
void LCD_WRITE_STR(uint8_t *ss);
void LCD_WRITE_FLOAT(float num);
void LCD_SETcursor(uint8_t row,uint8_t col);

void LCD_CLEAR(void);
void LCD_CLEAR_FRST(void);
void LCD_CLEAR_SCND(void);

#endif
