#ifndef UART_H_
#define UART_H_
#include <stdbool.h>  //as there is no boolean type in C
#include "REGDEF.h"
#include "Utilities.h"

// intialization of UART5(PORTE)
void intUART5(void);
//return data written in UART Data R(1byte=8 bits)
char UART_Read(void);
 
 #endif