#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "efm32gg.h"
#include "ex2.h"

/* TIMER1 interrupt handler */
void __attribute__((interrupt)) TIMER1_IRQHandler(void)
{
	int16_t sum = 0;
	uint16_t usum;
	unsigned i;

	*TIMER1_IFC = *TIMER1_IF; /* clears pending interrupt*/
	*SCR |= 4; /* enable deep sleep, is disabled again if a sound is still playing */
	for (i = 0; i < 8; i++) {
		if (!sounds[i].pos) continue; /* sound is not playing */
		if (sounds[i].pos >= sounds[i].end) {
			sounds[i].pos = NULL; /* end of sound */
		} else {
			/* Adds value of sound to sum */
			/* Sound is shifted to increase volume, as it is an 8 bit value in a 12 bit dac */
			sum += *(sounds[i].pos++) << 2;
			*SCR &= ~4; /* disable deep sleep */
		}
	}
	usum = (uint32_t)sum + 0x7FF; /* Converts sum to unsigned by adding 0x7FF */
	write_dac(usum << 16 | usum); /* Writes the sound to both channels */
}

/* Common handler for all GPIO interrupts */
void handle_gpio(void)
{
	uint32_t btn = *GPIO_IF;
	unsigned i;

	*GPIO_IFC = btn; /* Clears active GPIO interrupt flags */
	for (i = 0; i < 8; ++i) {
		if (btn & 1 << i) {
			*SCR &= ~4; /* disable deep sleep */
			sounds[i].pos = sounds[i].start; /* start playing sound */
		}
	}
}

/* GPIO even pin interrupt handler */
void __attribute__((interrupt)) GPIO_EVEN_IRQHandler(void)
{
	handle_gpio();
}

/* GPIO odd pin interrupt handler */
void __attribute__((interrupt)) GPIO_ODD_IRQHandler(void)
{
	handle_gpio();
}
