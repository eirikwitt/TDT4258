#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "ex2.h"

/* function to set up GPIO mode and interrupts */
void setup_gpio(void)
{
	/* Example of HW access from C code: turn on joystick LEDs D4-D8 check
	 * efm32gg.h for other useful register definitions
	 */
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; /* enable GPIO clock */
	*GPIO_PA_CTRL = 2; /* set high drive strength */
	*GPIO_PA_MODEH = 0x55555555; /* set pins A8-15 as output */
	*GPIO_PA_DOUT = 0x0700;	/* turn on LEDs D4-D8 (LEDs are active low) */

	*GPIO_PC_MODEL = 0x33333333; /* sets pinmode to input */
	*GPIO_PC_DOUT = 0xFF; /* enables pulldown */

	/* enables gpio fall interrupts on pin 0-7 on port C */
	*GPIO_EXTIPSELL = 0x22222222;
	*GPIO_EXTIFALL = 0xFF;
	*GPIO_IFC = 0xFF;
	*GPIO_IEN = 0xFF;
}

uint8_t read_buttons(void)
{
	return *GPIO_PC_DIN & 0xFF;
}
