#include <stdint.h>

#define SOUND_DECLARE(name) \
extern int8_t _binary_##name##_raw_start[]; \
extern int8_t _binary_##name##_raw_end[];
#define SOUND(name) {_binary_##name##_raw_start, _binary_##name##_raw_end}
typedef struct {
	const int8_t *const start;
	const int8_t *const end;
	const volatile int8_t * pos;
} Sound;
extern volatile Sound sounds[8];

/*
 * Declaration of peripheral setup functions
 */
void setup_timer(uint16_t period);
void setup_dac(void);
void setup_gpio(void);
void setup_nvic(void);
uint8_t read_buttons(void);
void write_dac(uint32_t data);
