#include <stdint.h>
#include <stdbool.h>

bool OSC_enabled();
void OSC_initialize();
void OSC_uninitialize();

bool PLL_enabled();
void PLL_initialize(uint32_t xtal_freq);
void PLL_uninitialize();
