
#include "SysTick.h"

#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Counter load value

// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void)
{
	NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
	NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value
	NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}

// Time delay using busy wait.
// The delay parameter is in units of the core clock.
//units of 50 nsec for 20 MHz clock
void SysTick_Wait(uint32_t delay)
{
	volatile uint32_t elapsedTime;
	uint32_t startTime = NVIC_ST_CURRENT_R;
	do
	{
		elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
	}while(elapsedTime <= delay);
}

// Time delay using busy wait.
// This assumes 20 MHz system clock.
void SysTick_Wait10ms(uint32_t delay)
{
	uint32_t i;
	for(i=0; i<delay; i++)
	{
		SysTick_Wait(200000);  // wait 10ms
	}
}
