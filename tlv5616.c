/*
Author: Ameya Ghadi
*/

#include "tlv5616.h"

void SSI3_Init_Master()
{
	SYSCTL_RCGCSSI_R |= (1<<3);       // activate clock to SSI3
	SYSCTL_RCGCGPIO_R |= (1<<3);			//activate clock to Port D
	while((SYSCTL_PRGPIO_R&(1<<3)) == 0){};// ready?
	
	GPIO_PORTD_DIR_R |= (1<<1);
	GPIO_PORTD_PUR_R |= (1<<1);		
	GPIO_PORTD_DEN_R |= ((1<<0)|(1<<1)|(1<<3));	//Enable Digital Functions on PD0,PD1,PD3
	//Pin_PD1 = 2;        // Make PD1 FSS high
		
	GPIO_PORTD_AFSEL_R |= ((1<<0)|(1<<3));	//PD0,PD3 as SSICLK, SSIMOSI
	GPIO_PORTD_PCTL_R	|= ((1<<12)|(1<<8)|(1<<4)|(1<<0));
	GPIO_PORTD_AMSEL_R = 0;	//Disable analog functions on Port D
			
	SSI3_CR1_R = 0x00000000;
	SSI3_CPSR_R |= 0x01;
	SSI3_CR0_R |= (3<<8);	//SCR = 3
	SSI3_CR0_R &= ~(1<<6);		//SPO = 0; SPH = 1
	SSI3_CR0_R |= (1<<7);
	SSI3_CR0_R &= ~(3<<4);	//Freescale SPI mode
	SSI3_CR0_R |= 0x0F;			//16-bit data
	SSI3_CR1_R |= (1<<1);	//Enable SSI
	
}

void SSI3_Transmit_Data(uint16_t DAC_Output)
{

	Pin_PD1 = 0;        // Make PD1 FSS low
	while((SSI3_SR_R &(1<<1)) == 0)	//Poll TNF bit
	{
		//Wait until transmit FIFO is full(TNF bit == 0)
	}
	
	SSI3_DR_R = DAC_Output;
	Pin_PD1 = 2;        // Make PD1 FSS high

}
