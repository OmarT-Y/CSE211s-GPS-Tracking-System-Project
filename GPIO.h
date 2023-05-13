#ifndef GPIO_H__
#define GPIO_H__
#include <stdio.h>
#include <stdint.h>
#include "REGDEF.h"
#include "Utilities.h"

void initDig_Port(uint8_t PORT);
void set_PortDir(uint8_t PORT,uint8_t direction);
void set_PinDir(uint8_t PORT,uint8_t pin,uint8_t i_o);
void write_Port(uint8_t PORT,uint8_t data);
void write_Pin(uint8_t PORT,uint8_t pin,uint8_t h_l);
uint8_t read_Port(uint8_t PORT);
uint8_t read_Pin(uint8_t PORT,uint8_t pin );
void set_LED(uint8_t R,uint8_t G,uint8_t B);

#define Led_Red 1
#define Led_Blue 2 
#define Led_Green 3
#endif
