#include <stdint.h>

uint32_t pm_soc_clk_get_hfrc();
uint32_t pm_soc_clk_get_hfxo();
uint32_t pm_soc_clk_get_hfosc();    /* used by some peripherals like UART and CAN */
uint32_t pm_soc_clk_get_refclk();   /* returns REFCLK */
uint32_t pm_soc_clk_get_axiclk();   /* returns SYST_ACLK (AXI) */
uint32_t pm_soc_clk_get_ahbclk();   /* returns SYST_HCLK (AHB) */
uint32_t pm_soc_clk_get_apbclk();   /* returns SYST_PCLK (APB) */
uint32_t pm_soc_clk_get_busclk();   /* updates REFCLK, AXI, AHB, APB all at once, returns SYST_ACLK */

int32_t  pm_soc_clk_set_hfrc_div(uint32_t div_active, uint32_t div_standby);
int32_t  pm_soc_clk_set_hfxo_div(uint32_t div_xtal);
void     pm_soc_clk_set_osc_sel(uint32_t xtal_sel);
void     pm_soc_clk_set_pll_sel(uint32_t pll_sel);
int32_t  pm_soc_clk_set_busclk(uint32_t aclk_ctrl, uint32_t aclk_div, uint32_t hclk_div, uint32_t pclk_div);

#if (defined(M55_HE) || defined(M55_HP))
/* for Cortex-M cores in RTSS */
uint32_t pm_core_clk_update();      /* returns RTSS_HE_CLOCK or RTSS_HP_CLOCK */
int32_t  pm_core_clk_set(uint32_t osc_sel, uint32_t pll_sel);
#else
/* for Cortex-A cores in APSS (TBD) */
uint32_t pm_core_clk_update();      /* returns APSS_CPU_CLOCK */
int32_t  pm_core_clk_set(uint32_t clk_src, uint32_t clk_div);
#endif