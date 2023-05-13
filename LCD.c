#include "LCD.h"

void LCD_Pset(void){
	initDig_Port(LCD_DATA_PORT);
	set_PortDir(LCD_DATA_PORT,0xFF);
	initDig_Port(LCD_CTRL_PORT);
	set_PinDir(LCD_CTRL_PORT,LCD_EN_PIN,1);
	set_PinDir(LCD_CTRL_PORT,LCD_RW_PIN,1);
	set_PinDir(LCD_CTRL_PORT,LCD_RS_PIN,1);
}
void LCD_CMD(uint8_t command){
	write_Port(LCD_DATA_PORT,command);
	write_Pin(LCD_CTRL_PORT,LCD_RS_PIN,0);
	write_Pin(LCD_CTRL_PORT,LCD_RW_PIN,0);
	write_Pin(LCD_CTRL_PORT,LCD_EN_PIN,1);
	delay_ms(1);
	write_Pin(LCD_CTRL_PORT,LCD_EN_PIN,0);
	delay_ms(1);
}


void LCD_setup(void){
	LCD_Pset();
	LCD_CMD (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_CMD (0x0C);		/* Display ON Cursor OFF */
	LCD_CMD (0x06);		/* Auto Increment cursor */
	LCD_CMD (0x01);		/* Clear display */
	LCD_CMD (0x80);		/* Cursor at home position */
}
void LCD_WRITE_CHAR(uint8_t c){
	write_Port(LCD_DATA_PORT,c);
	write_Pin(LCD_CTRL_PORT,LCD_RS_PIN,1);
	write_Pin(LCD_CTRL_PORT,LCD_RW_PIN,0);
	write_Pin(LCD_CTRL_PORT,LCD_EN_PIN,1);
	delay_ms(1);
	write_Pin(LCD_CTRL_PORT,LCD_EN_PIN,0);
	delay_us(50);
}
void LCD_WRITE_STR(uint8_t *ss){
	uint8_t i;
	for(i = 0;ss[i]!=0;i++)
		LCD_WRITE_CHAR(ss[i]);
}

void LCD_CLEAR_SCND(void)
{
	LCD_CMD(0xC0);
	uint8_t x;
	for(x=0;x<16;x++)
		LCD_WRITE_CHAR(' ');
	LCD_CMD(0xC0);
}
void LCD_CLEAR_FRST(void)
{
	LCD_CMD(0x80);
	uint8_t x;
	for(x=0;x<16;x++)
		LCD_WRITE_CHAR(' ');
	LCD_CMD(0x80);
}
void LCD_CLEAR()
{
	LCD_CMD(1);
	LCD_CMD(0x80);
	delay_ms(50);
}

void LCD_SETcursor(uint8_t row,uint8_t col){
	uint8_t pos;
	if(!row)
		pos = 0x80;
	else
		pos = 0xC0;
	pos+=col;
	LCD_CMD(pos);
}

void LCD_WRITE_FLOAT(float num){
	if(num<0.001)
		num=0;
	char sss[8];
	uint8_t i;
	sprintf(sss,"%f",num);
	for(i=0;i<7;i++){
		if(sss[i]==0)
			break;
		if(sss[i]==0x88)
			LCD_WRITE_CHAR('.');
		else
			LCD_WRITE_CHAR(sss[i]);
	}
}