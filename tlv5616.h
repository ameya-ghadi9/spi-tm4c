/*
Author: Ameya Ghadi
*/
#ifndef _TLV_5616_H
#define _TLV_5616_H

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../driverlib/ssi.h"

#define Pin_PD1 (*(volatile uint32_t*)(0x40007000+0x08))
#define PIN_PA1 (*(volatile uint32_t*)(0x40004020))
	
void SSI3_Init_Master(void);
void SSI3_Transmit_Data(uint16_t DAC_Output);

#endif
