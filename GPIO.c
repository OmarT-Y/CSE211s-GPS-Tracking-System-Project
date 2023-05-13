#include "GPIO.h"

void initDig_Port(uint8_t PORT){
    switch(PORT){
        case 'A':
        SETBit(SYSCTL_RCGCGPIO_R,0); // set port A
		    while (ReadBit(SYSCTL_PRGPIO_R,0) == 0){} // check the delay
        	GPIO_PORTA_LOCK_R = 0x4C4F434B;
        	GPIO_PORTA_CR_R |= 0xFC;
						GPIO_PORTA_AMSEL_R &= ~0xFC; // disable analog mode select
         	GPIO_PORTA_AFSEL_R &= ~0xFC; // no alternative fn
        	GPIO_PORTA_DEN_R |= 0xFC;
        break;

        case 'B':
            SETBit(SYSCTL_RCGCGPIO_R,1); // set port B
		    while (ReadBit(SYSCTL_PRGPIO_R,1) == 0){} // check the delay
            GPIO_PORTB_LOCK_R = 0x4C4F434B;
            GPIO_PORTB_CR_R = 0xFF;
            GPIO_PORTB_AMSEL_R = 0; // disable analog mode select
         	GPIO_PORTB_AFSEL_R = 0; // no alternative fn
        	GPIO_PORTB_DEN_R = 0xFF;
        break;
            
        case 'C':
            SETBit(SYSCTL_RCGCGPIO_R,2); // set port C
		    while (ReadBit(SYSCTL_PRGPIO_R,2) == 0){} // check the delay
        	GPIO_PORTC_LOCK_R = 0x4C4F434B;
        	GPIO_PORTC_CR_R |= 0xF0;
     	    GPIO_PORTC_AMSEL_R &= ~0xF0; // disable analog mode select
     	    GPIO_PORTC_AFSEL_R &= ~0xF0; // no alternative fn
        	GPIO_PORTC_DEN_R |= 0xF0;
        break;

        case 'D':
            SETBit(SYSCTL_RCGCGPIO_R,3); // set port D
		    while (ReadBit(SYSCTL_PRGPIO_R,3) == 0){} // check the delay
        	GPIO_PORTD_LOCK_R = 0x4C4F434B;
        	GPIO_PORTD_CR_R |= 0x0C;
     	    GPIO_PORTD_AMSEL_R &= ~0x0C; // disable analog mode select
     	    GPIO_PORTD_AFSEL_R &= ~0x0C; // no alternative fn
        	GPIO_PORTD_DEN_R |= 0x0C;
        break;

        case 'E':
            SETBit(SYSCTL_RCGCGPIO_R,4); // set port E
		    while (ReadBit(SYSCTL_PRGPIO_R,4) == 0){} // check the delay
        	GPIO_PORTE_LOCK_R = 0x4C4F434B;
        	GPIO_PORTE_CR_R |= 0x3F;
     	    GPIO_PORTE_AMSEL_R &= ~0x3F; // disable analog mode select
     	    GPIO_PORTE_AFSEL_R &= ~0x3F; // no alternative fn
        	GPIO_PORTE_DEN_R |= 0x3F;
        break;

        case 'F':
          SETBit(SYSCTL_RCGCGPIO_R,5); // set port F
					while (ReadBit(SYSCTL_PRGPIO_R,5) == 0){} // check the delay
        	GPIO_PORTF_LOCK_R = 0x4C4F434B;
        	GPIO_PORTF_CR_R = 0x1F;
     	    GPIO_PORTF_AMSEL_R = 0; // disable analog mode select
     	    GPIO_PORTF_AFSEL_R = 0; // no alternative fn
        	GPIO_PORTF_DEN_R = 0x1F;
        break;
    }
}
void set_PortDir(uint8_t PORT,uint8_t direction){
    switch(PORT){
        case 'A':
            GPIO_PORTA_DIR_R |= (direction&0xFC);
        break;

        case 'B':
            GPIO_PORTB_DIR_R = direction;
        break;

        case 'C':
            GPIO_PORTC_DIR_R |= (direction&0xF0);
        break;

        case 'D':
            GPIO_PORTD_DIR_R |= (direction&0x0C);
        break;

        case 'E':
            GPIO_PORTE_DIR_R |= (direction&0x3F);
        break;

        case 'F':
            GPIO_PORTF_DIR_R = direction;
        break;
    }
}
void set_PinDir(uint8_t PORT,uint8_t pin,uint8_t i_o){
    switch(PORT){
        case 'A':
            if(i_o)
                SETBit(GPIO_PORTA_DIR_R,pin);
            else
                CLRBit(GPIO_PORTA_DIR_R,pin);
        break;

        case 'B':
            if(i_o)
                SETBit(GPIO_PORTB_DIR_R,pin);
            else
                CLRBit(GPIO_PORTB_DIR_R,pin);
        break;

        case 'C':
            if(i_o)
                SETBit(GPIO_PORTC_DIR_R,pin);
            else
                CLRBit(GPIO_PORTC_DIR_R,pin);
        break;

        case 'D':
            if(i_o)
                SETBit(GPIO_PORTD_DIR_R,pin);
            else
                CLRBit(GPIO_PORTD_DIR_R,pin);
        break;

        case 'E':
            if(i_o)
                SETBit(GPIO_PORTE_DIR_R,pin);
            else
                CLRBit(GPIO_PORTE_DIR_R,pin);
        break;

        case 'F':
            if(i_o)
                SETBit(GPIO_PORTF_DIR_R,pin);
            else
                CLRBit(GPIO_PORTF_DIR_R,pin);
        break;
    }
}
void write_Port(uint8_t PORT,uint8_t data){
    switch(PORT){
        case 'A':
           GPIO_PORTA_DATA_R |= (data&0xFC);
        break;

        case 'B':
            GPIO_PORTB_DATA_R = data;
        break;

        case 'C':
            GPIO_PORTC_DATA_R |= (data&0xF0);
        break;

        case 'D':
            GPIO_PORTD_DATA_R |= (data&0x0C);
        break;

        case 'E':
            GPIO_PORTE_DATA_R |= (data&0x3F);
        break;

        case 'F':
            GPIO_PORTF_DATA_R = data;
        break;
    }
}
void write_Pin(uint8_t PORT,uint8_t pin,uint8_t h_l){
    switch(PORT){
        case 'A':
            if(h_l)
                SETBit(GPIO_PORTA_DATA_R,pin);
            else
                CLRBit(GPIO_PORTA_DATA_R,pin);
        break;

        case 'B':
            if(h_l)
                SETBit(GPIO_PORTB_DATA_R,pin);
            else
                CLRBit(GPIO_PORTB_DATA_R,pin);
        break;

        case 'C':
            if(h_l)
                SETBit(GPIO_PORTC_DATA_R,pin);
            else
                CLRBit(GPIO_PORTC_DATA_R,pin);
        break;

        case 'D':
            if(h_l)
                SETBit(GPIO_PORTD_DATA_R,pin);
            else
                CLRBit(GPIO_PORTD_DATA_R,pin);
        break;

        case 'E':
            if(h_l)
                SETBit(GPIO_PORTE_DATA_R,pin);
            else
                CLRBit(GPIO_PORTE_DATA_R,pin);
        break;

        case 'F':
            if(h_l)
                SETBit(GPIO_PORTF_DATA_R,pin);
            else
                CLRBit(GPIO_PORTF_DATA_R,pin);
        break;
    }
}
uint8_t read_Port(uint8_t PORT) {
    switch(PORT){
        case 'A':
            return GPIO_PORTA_DATA_R & 0xFF;
        break;

        case 'B':
            return GPIO_PORTB_DATA_R  & 0xFF;
        break;

        case 'C':
            return GPIO_PORTC_DATA_R  & 0xFF;
        break;

        case 'D':
            return GPIO_PORTD_DATA_R  & 0xFF;
        break;

        case 'E':
            return GPIO_PORTE_DATA_R  & 0xFF;
        break;

        case 'F':
            return GPIO_PORTF_DATA_R & 0xFF;
        break;
    }
}

uint8_t read_Pin(uint8_t PORT,uint8_t pin ) {
    switch(PORT){
        case 'A':
            return ReadBit(GPIO_PORTA_DATA_R,pin);
        break;

        case 'B':
            return ReadBit(GPIO_PORTB_DATA_R,pin);
        break;

        case 'C':
            return ReadBit(GPIO_PORTC_DATA_R,pin);
        break;

        case 'D':
            return ReadBit(GPIO_PORTD_DATA_R,pin);
        break;

        case 'E':
            return ReadBit(GPIO_PORTE_DATA_R,pin);
        break;

        case 'F':
            return ReadBit(GPIO_PORTF_DATA_R,pin);
        break;
    }
}
void set_LED(uint8_t R,uint8_t G,uint8_t B){
	write_Pin('F',Led_Blue,B);
	write_Pin('F',Led_Green,G);
	write_Pin('F',Led_Red,R);
}
