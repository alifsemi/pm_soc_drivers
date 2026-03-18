#include <stdint.h>
#include <stdbool.h>

void OSC_rc_to_xtal();
void OSC_initialize();

void OSC_xtal_to_rc();
void OSC_uninitialize();

void PLL_clkpll_start(uint32_t xtal_freq, bool faststart);
void PLL_clkpll_stop();
void PLL_initialize(uint32_t xtal_freq);
void PLL_uninitialize();
