#include "REGDEF.h"
#include "GPIO.h"
#include "LCD.h"
#include "Utilities.h"
#include "gps.h"
#include "UART.h"
#include "SYSTICK.h"
#include "stdio.h"

float currentLat, currentLong;
float oldLat, oldLong;
float dist2arrival=0.0;
float moved=0;
float flag = 0;
 int main(void){
	initDig_Port('F');
	moved=0;
	set_PinDir('F',Led_Blue,1);
	set_PinDir('F',Led_Red,1);
	set_PinDir('F',Led_Green,1);
	intUART5();
	sysTick_Init();
	initDig_Port('B');
	set_PortDir('B',0xFF);
	initDig_Port('A');
	set_PinDir('A',5,1);
	set_PinDir('A',6,1);
	set_PinDir('A',7,1);
	LCD_setup();
	LCD_WRITE_STR("Starting ....");
	set_LED(1,0,0);
	GPSread();
	oldLat=currentLat;
	oldLong=currentLong;
	set_LED(1,0,1);
	dist2arrival = Finaldist();
	set_LED(1,1,1);
	delay_ms(3000);
	moved = 0;
	while(1)
	{
		GPSread();
		flag = dist();
		if(flag>0){
			moved+=flag;
			dist2arrival = Finaldist();
		}
		else
			continue;
		if(dist2arrival<2){
			set_LED(0,1,0);
		}
		else if(dist2arrival<5){
			set_LED(1,1,0);
		}
		else{
			set_LED(1,0,0);
		}
		LCD_CLEAR_FRST();
		LCD_WRITE_STR("Moved:");
		LCD_WRITE_FLOAT(moved);
		LCD_CLEAR_SCND();
		LCD_WRITE_STR("Arrival:");
		LCD_WRITE_FLOAT(dist2arrival);
		oldLat=currentLat;
		oldLong=currentLong;
		delay_ms(250);
	}
}
