#include <stdint.h>
#include <stdbool.h>

bool AUDIOPLL_enabled();
void AUDIOPLL_initialize(uint32_t xtal_freq);
void AUDIOPLL_uninitialize();
