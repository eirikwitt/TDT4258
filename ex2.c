#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "ex2.h"

/*
 * TODO calculate the appropriate sample period for the sound wave(s) you 
 * want to generate. The core clock (which the timer clock is derived
 * from) runs at 14 MHz by default. Also remember that the timer counter
 * registers are 16 bits. 
 */
/*
 * The period between sound samples, in clock cycles 
 */
#define   SAMPLE_PERIOD   1270

SOUND_DECLARE(ahem_x)
SOUND_DECLARE(nokia)
SOUND_DECLARE(call_to_arms)
SOUND_DECLARE(bloop_x)
SOUND_DECLARE(bad_disk_x)
SOUND_DECLARE(applause3)
SOUND_DECLARE(air_raid)
SOUND_DECLARE(bushj_liberty)
volatile Sound sounds[8] = {SOUND(ahem_x), SOUND(nokia), SOUND(call_to_arms),
	SOUND(bloop_x), SOUND(bad_disk_x), SOUND(applause3), SOUND(air_raid),
	SOUND(bushj_liberty)
};

/*
 * Your code will start executing here 
 */
int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */
	setup_gpio();
	setup_dac();
	setup_timer(SAMPLE_PERIOD);

	/*
	 * Enable interrupt handling 
	 */
	setup_nvic();

	*SCR = 2;
	while (1) __asm volatile ("wfi":::"memory");

	return 0;
}

void setup_nvic(void)
{
	*ISER0 = 1<<12 | 1<<11 | 1<<1;
}

/*
 * if other interrupt handlers are needed, use the following names:
 * NMI_Handler HardFault_Handler MemManage_Handler BusFault_Handler
 * UsageFault_Handler Reserved7_Handler Reserved8_Handler
 * Reserved9_Handler Reserved10_Handler SVC_Handler DebugMon_Handler
 * Reserved13_Handler PendSV_Handler SysTick_Handler DMA_IRQHandler
 * GPIO_EVEN_IRQHandler TIMER0_IRQHandler USART0_RX_IRQHandler
 * USART0_TX_IRQHandler USB_IRQHandler ACMP0_IRQHandler ADC0_IRQHandler
 * DAC0_IRQHandler I2C0_IRQHandler I2C1_IRQHandler GPIO_ODD_IRQHandler
 * TIMER1_IRQHandler TIMER2_IRQHandler TIMER3_IRQHandler
 * USART1_RX_IRQHandler USART1_TX_IRQHandler LESENSE_IRQHandler
 * USART2_RX_IRQHandler USART2_TX_IRQHandler UART0_RX_IRQHandler
 * UART0_TX_IRQHandler UART1_RX_IRQHandler UART1_TX_IRQHandler
 * LEUART0_IRQHandler LEUART1_IRQHandler LETIMER0_IRQHandler
 * PCNT0_IRQHandler PCNT1_IRQHandler PCNT2_IRQHandler RTC_IRQHandler
 * BURTC_IRQHandler CMU_IRQHandler VCMP_IRQHandler LCD_IRQHandler
 * MSC_IRQHandler AES_IRQHandler EBI_IRQHandler EMU_IRQHandler 
 */
