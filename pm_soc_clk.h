#include <stdint.h>

uint32_t CoreID();
uint32_t SocTopClockHFRC();
uint32_t SocTopClockHFXO();
uint32_t SocTopClockHFOSC();
uint32_t SystRefclkUpdate();
uint32_t SystBusClkUpdate();
uint32_t CoreClockUpdate();
int32_t  CoreClockConfig(uint32_t esclk_osc_sel, uint32_t esclk_pll_sel);
int32_t  DivClockConfig (uint32_t div_active, uint32_t div_standby, uint32_t div_xtal);
void     OscClockConfig (uint32_t xtal_sel);
void     PllClockConfig (uint32_t pll_sel);
int32_t  BusClockConfig (uint32_t aclk_ctrl, uint32_t aclk_div, uint32_t hclk_div, uint32_t pclk_div);
