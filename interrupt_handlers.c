#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "efm32gg.h"
#include "ex2.h"

/* TIMER1 interrupt handler */
void __attribute__((interrupt)) TIMER1_IRQHandler() {
	int16_t sum = 0;
	uint16_t usum;
	unsigned i;

	*TIMER1_IFC = 1; /* clears pending interrupt*/
	for (i = 0; i < 8; i++) {
		/* If pos == NULL, then the sound is not included in the sum */
		if (!sounds[i].pos) continue;
		/* Sets pos = NULL if the sound is finished */
		if (sounds[i].pos >= sounds[i].end) {
			sounds[i].pos = NULL;
		} else {
			/* Adds value of sound to sum */
			/* Sound is shifted to increase volume, as it is an 8 bit value in a 12 bit dac */
			sum += *(sounds[i].pos++) << 2;
		}
	}
	usum = (uint32_t)sum + 0x7FF; /* Converts sum to unsigned by adding 0x7FF */
	write_dac(usum << 16 | usum); /* Writes the sound to both channels */
}

/* Common handler for all GPIO interrupts */
void handle_gpio()
{
	uint8_t btn = GPIO_IF;
	unsigned i;

	*GPIO_IFC = btn; /* Clears active GPIO interrupt flags */
	for (i = 0; i < 8; ++i)
		if (btn & 1 << i)
			/* Starts sounds by setting pos to start*/
			sounds[i].pos = sounds[i].start;
}

/* GPIO even pin interrupt handler */
void __attribute__((interrupt)) GPIO_EVEN_IRQHandler()
{
	handle_gpio();
}

/* GPIO odd pin interrupt handler */
void __attribute__((interrupt)) GPIO_ODD_IRQHandler()
{
	handle_gpio();
}
