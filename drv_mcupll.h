#include <stdint.h>
#include <stdbool.h>

void OSC_initialize();
void OSC_uninitialize();

void PLL_initialize(uint32_t xtal_freq);
void PLL_uninitialize();
