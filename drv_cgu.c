#include "drv_cgu.h"
#include "soc.h" /* for CGU */

static inline void cgu_set_clk(uint32_t mask)
{
    CGU->CLK_ENA |= mask;
}

static inline void cgu_clear_clk(uint32_t mask)
{
    CGU->CLK_ENA &= ~mask;
}

#if defined(ENSEMBLE_SOC_GEN2)

void CGU_clock_enable_syspll(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_SYSPLL); else cgu_clear_clk(CGU_CLK_ENA_SYSPLL); }
void CGU_clock_enable_cpupll(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_CPUPLL); else cgu_clear_clk(CGU_CLK_ENA_CPUPLL); }
void CGU_clock_enable_clk25M(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK25M); else cgu_clear_clk(CGU_CLK_ENA_CLK25M); }
void CGU_clock_enable_clk50M(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK50M); else cgu_clear_clk(CGU_CLK_ENA_CLK50M); }
void CGU_clock_enable_clk100M(bool enable)  { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK100M); else cgu_clear_clk(CGU_CLK_ENA_CLK100M); }
void CGU_clock_enable_clk10M(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK10M); else cgu_clear_clk(CGU_CLK_ENA_CLK10M); }
void CGU_clock_enable_clk80M(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK80M); else cgu_clear_clk(CGU_CLK_ENA_CLK80M); }
void CGU_clock_enable_mram(bool enable)     { if (enable) cgu_set_clk(CGU_CLK_ENA_MRAM); else cgu_clear_clk(CGU_CLK_ENA_MRAM); }
void CGU_clock_enable_rtsshp(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_RTSSHP); else cgu_clear_clk(CGU_CLK_ENA_RTSSHP); }
void CGU_clock_enable_rtsshe(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_RTSSHE); else cgu_clear_clk(CGU_CLK_ENA_RTSSHE); }
void CGU_clock_enable_clk200M(bool enable)  { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK200M); else cgu_clear_clk(CGU_CLK_ENA_CLK200M); }
void CGU_clock_enable_clk400M(bool enable)  { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK400M); else cgu_clear_clk(CGU_CLK_ENA_CLK400M); }
void CGU_clock_enable_trace(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_TRACE); else cgu_clear_clk(CGU_CLK_ENA_TRACE); }
void CGU_clock_enable_hfxo(bool enable)     { if (enable) cgu_set_clk(CGU_CLK_ENA_HFXO); else cgu_clear_clk(CGU_CLK_ENA_HFXO); }
void CGU_clock_enable_clk160M(bool enable)  { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK160M); else cgu_clear_clk(CGU_CLK_ENA_CLK160M); }
void CGU_clock_enable_clk266M(bool enable)  { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK266M); else cgu_clear_clk(CGU_CLK_ENA_CLK266M); }
void CGU_clock_enable_clk20M(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK20M); else cgu_clear_clk(CGU_CLK_ENA_CLK20M); }
void CGU_clock_enable_clk38p4M(bool enable) { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK38P4M); else cgu_clear_clk(CGU_CLK_ENA_CLK38P4M); }
void CGU_clock_enable_clk76p8M(bool enable) { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK76P8M); else cgu_clear_clk(CGU_CLK_ENA_CLK76P8M); }
void CGU_clock_enable_pclk(bool enable)     { if (enable) cgu_set_clk(CGU_CLK_ENA_PCLK); else cgu_clear_clk(CGU_CLK_ENA_PCLK); }
void CGU_clock_enable_hclk(bool enable)     { if (enable) cgu_set_clk(CGU_CLK_ENA_HCLK); else cgu_clear_clk(CGU_CLK_ENA_HCLK); }
void CGU_clock_enable_sram0(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_SRAM0); else cgu_clear_clk(CGU_CLK_ENA_SRAM0); }
void CGU_clock_enable_sram1(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_SRAM1); else cgu_clear_clk(CGU_CLK_ENA_SRAM1); }
void CGU_clock_enable_isp(bool enable)      { if (enable) cgu_set_clk(CGU_CLK_ENA_ISP); else cgu_clear_clk(CGU_CLK_ENA_ISP); }
void CGU_clock_enable_jpeg(bool enable)     { if (enable) cgu_set_clk(CGU_CLK_ENA_JPEG); else cgu_clear_clk(CGU_CLK_ENA_JPEG); }
void CGU_clock_enable_ethos_u85(bool enable) { if (enable) cgu_set_clk(CGU_CLK_ENA_ETHOS_U85); else cgu_clear_clk(CGU_CLK_ENA_ETHOS_U85); }

#elif defined(ENSEMBLE_SOC_E1C)

void CGU_clock_enable_syspll(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_SYSPLL); else cgu_clear_clk(CGU_CLK_ENA_SYSPLL); }
void CGU_clock_enable_cpupll(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_CPUPLL); else cgu_clear_clk(CGU_CLK_ENA_CPUPLL); }
void CGU_clock_enable_hfxo(bool enable)     { if (enable) cgu_set_clk(CGU_CLK_ENA_HFXO); else cgu_clear_clk(CGU_CLK_ENA_HFXO); }
void CGU_clock_enable_trace(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_TRACE); else cgu_clear_clk(CGU_CLK_ENA_TRACE); }
void CGU_clock_enable_clk160M(bool enable)  { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK160M); else cgu_clear_clk(CGU_CLK_ENA_CLK160M); }
void CGU_clock_enable_clk100M(bool enable)  { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK100M); else cgu_clear_clk(CGU_CLK_ENA_CLK100M); }
void CGU_clock_enable_clk20M(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK20M); else cgu_clear_clk(CGU_CLK_ENA_CLK20M); }
void CGU_clock_enable_clk38p4M(bool enable) { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK38P4M); else cgu_clear_clk(CGU_CLK_ENA_CLK38P4M); }
void CGU_clock_enable_sram0(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_SRAM0); else cgu_clear_clk(CGU_CLK_ENA_SRAM0); }
void CGU_clock_enable_sram1(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_SRAM1); else cgu_clear_clk(CGU_CLK_ENA_SRAM1); }

#else

void CGU_clock_enable_syspll(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_SYSPLL); else cgu_clear_clk(CGU_CLK_ENA_SYSPLL); }
void CGU_clock_enable_cpupll(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_CPUPLL); else cgu_clear_clk(CGU_CLK_ENA_CPUPLL); }
void CGU_clock_enable_trace(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_TRACE); else cgu_clear_clk(CGU_CLK_ENA_TRACE); }
void CGU_clock_enable_clk160M(bool enable)  { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK160M); else cgu_clear_clk(CGU_CLK_ENA_CLK160M); }
void CGU_clock_enable_clk100M(bool enable)  { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK100M); else cgu_clear_clk(CGU_CLK_ENA_CLK100M); }
void CGU_clock_enable_clk20M(bool enable)   { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK20M); else cgu_clear_clk(CGU_CLK_ENA_CLK20M); }
void CGU_clock_enable_clk38p4M(bool enable) { if (enable) cgu_set_clk(CGU_CLK_ENA_CLK38P4M); else cgu_clear_clk(CGU_CLK_ENA_CLK38P4M); }
void CGU_clock_enable_sram0(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_SRAM0); else cgu_clear_clk(CGU_CLK_ENA_SRAM0); }
void CGU_clock_enable_sram1(bool enable)    { if (enable) cgu_set_clk(CGU_CLK_ENA_SRAM1); else cgu_clear_clk(CGU_CLK_ENA_SRAM1); }

#endif
