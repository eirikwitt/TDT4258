#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "ex2.h"

void setup_dac(void)
{
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_DAC0; // Enable the DAC clock by setting bit 17 in CMU_HFPERCLKEN0
	*DAC0_CAL = *(volatile uint32_t *)0x0FE081C8;
	*DAC0_CTRL = 0x50010; //Prescale DAC clock by writing 0x50010 to DAC0_CTRL 3
	*DAC0_CH0CTRL = 1; //Enable left audio channel
	*DAC0_CH1CTRL = 1; //Enable right audio channel
}

void write_dac(uint32_t data)
{
	*DAC0_COMBDATA = data & 0x0FFF0FFF; //Write data of samples to the DAC data registers
}
