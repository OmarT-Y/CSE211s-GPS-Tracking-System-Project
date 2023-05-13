#include "UART.h"

void intUART5(void){
		SETBit(SYSCTL_RCGCUART_R,5);  //activate UART5
		SETBit(SYSCTL_RCGCGPIO_R,4);  // activate PORTE
		while (ReadBit(SYSCTL_PRGPIO_R ,5)==0){};  //delay until PORTE is activated
		//SET(UART5_CTL_R ,(UART5_CTL_R & 0xFFFFFF00)+0x00000011);  //disable the UART and enable TX&RX
		UART5_IBRD_R = 1000000 / 9600;   // assuming MC 16 MHZ & baud rate 9600 
		UART5_FBRD_R = 1000000 % 9600 / 9600.0 * 64 + 0.5;;
		UART5_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN) & ~UART_LCRH_PEN; // 8 bit, no parity, 1 stop, FIFOs
		UART5_CTL_R = UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;		// Enable UART5, Rx, Tx
		SETBit(GPIO_PORTE_AMSEL_R,4);  // disable  analog mode for pins 4&5
		SETBit(GPIO_PORTE_AMSEL_R,5);
		SETBit(GPIO_PORTE_AFSEL_R ,4);  //enable alternate fun. for pins 4&5
		SETBit(GPIO_PORTE_AFSEL_R ,5);
		GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) | 0x00110000;
		SETBit(GPIO_PORTE_DEN_R,4);  //enable digital ll pins 4&5
		SETBit(GPIO_PORTE_DEN_R,5);
		SET(GPIO_PORTE_PUR_R,0x11);
}
 char UART_Read(void){
	 while((UART5_FR_R & (1 << 4)) != 0);
		 return (unsigned char)UART5_DR_R;	 
 }