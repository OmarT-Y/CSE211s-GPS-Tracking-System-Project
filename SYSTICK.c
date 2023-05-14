#include "SYSTICK.h"

void sysTick_Init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R=0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0 ;
	NVIC_ST_CTRL_R = 0x00000005;
}
void SysTick_delay_1us(void){
	NVIC_ST_RELOAD_R=15;
	NVIC_ST_CURRENT_R=0;
	while((NVIC_ST_CTRL_R&0x00010000)==0){}
}
void delay_us(uint32_t ustime){
	uint32_t i;
	for(i=0;i<ustime;i++){
			SysTick_delay_1us();
	}
}
void delay_ms(uint32_t mstime){
	uint32_t ii;
	for(ii=0;ii<mstime;ii++)
			delay_us(1000);
}
