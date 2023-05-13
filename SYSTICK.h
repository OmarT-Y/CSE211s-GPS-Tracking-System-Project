#ifndef SYSTICK__H_
#define SYSTICK__H_

#include "GPIO.h"
#include "Utilities.h"
#include "REGDEF.h"

void sysTick_Init(void);
void delay_us(uint32_t ustime);
void delay_ms(uint32_t mstime);

#endif
