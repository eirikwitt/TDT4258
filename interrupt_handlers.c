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
	uint16_t sum;
	unsigned i;

	*GPIO_PA_DOUT = (*GPIO_PA_DOUT + 0x1) & 0xFFFF;
	*TIMER1_IFC = 0xFFFFFFFFUL;
	for (i = 0; i < 8; i++) {
		if (!sounds[i].pos) continue;
		if (sounds[i].pos >= sounds[i].end) {
			sounds[i].pos = NULL;
		} else {
			sum += *(sounds[i].pos++);
		}
	}
	write_dac((uint32_t)sum << 12 | sum >> 4);
}

/*
 * GPIO even pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
}

/*
 * GPIO odd pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
}
