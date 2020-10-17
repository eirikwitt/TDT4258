#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "efm32gg.h"
#include "ex2.h"

/*
 * TIMER1 interrupt handler 
 */
void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	/*
	 * TODO feed new samples to the DAC remember to clear the pending
	 * interrupt by writing 1 to TIMER1_IFC 
	 */
	int16_t sum = 0;
	uint16_t usum;
	unsigned i;

	*TIMER1_IFC = 0xFFFFFFFFul;
	for (i = 0; i < 8; i++) {
		if (!sounds[i].pos) continue;
		if (sounds[i].pos >= sounds[i].end) {
			sounds[i].pos = NULL;
		} else {
			sum += *(sounds[i].pos++) << 2;
		}
	}
	usum = (uint32_t)sum + 0x7FF;
	write_dac(usum << 16 | usum);
}

void handle_gpio()
{
	uint8_t btn = GPIO_IF;
	unsigned i;

	*GPIO_IFC = btn;
	for (i = 0; i < 8; ++i)
		if (btn & 1<<i)
			sounds[i].pos = sounds[i].start;

}

/*
 * GPIO even pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	handle_gpio();
}

/*
 * GPIO odd pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	handle_gpio();
}
