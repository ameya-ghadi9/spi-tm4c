#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../driverlib/sysctl.h"
#include "../driverlib/gpio.h"
#include "../driverlib/ssi.h"
#include "../inc/hw_memmap.h"

#include "PLL.h"
#include "UART.h"
#include "SysTick.h"
#include "tlv5616.h"


int main(void)
{

	PLL_Init(Bus20MHz);
	SysTick_Init();
	SSI3_Init_Master();

	while(1)
	{
		SSI3_Transmit_Data(0X4FFF);
		SysTick_Wait10ms(10);
		SSI3_Transmit_Data(0X4CFF);
		SysTick_Wait10ms(10);
		SSI3_Transmit_Data(0X47FF);
		SysTick_Wait10ms(10);
		SSI3_Transmit_Data(0X43FF);
		SysTick_Wait10ms(10);
		SSI3_Transmit_Data(0X40FF);
		SysTick_Wait10ms(10);
	}
}

