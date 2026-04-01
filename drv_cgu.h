#ifndef DRV_CGU_H
#define DRV_CGU_H

#include <stdint.h>
#include <stdbool.h>

#if defined(ENSEMBLE_SOC_GEN2)

/* CGU CLK_ENA bit masks for ENSEMBLE_SOC_GEN2 */
#define CGU_CLK_ENA_SYSPLL         (1U << 0)
#define CGU_CLK_ENA_CPUPLL         (1U << 4)
#define CGU_CLK_ENA_CLK25M         (1U << 5)
#define CGU_CLK_ENA_CLK50M         (1U << 6)
#define CGU_CLK_ENA_CLK100M        (1U << 7)
#define CGU_CLK_ENA_CLK10M         (1U << 9)
#define CGU_CLK_ENA_CLK80M         (1U << 10)
#define CGU_CLK_ENA_MRAM           (1U << 11)
#define CGU_CLK_ENA_CLK200M        (1U << 14)
#define CGU_CLK_ENA_CLK400M        (1U << 15)
#define CGU_CLK_ENA_TRACE          (1U << 16)
#define CGU_CLK_ENA_HFXO           (1U << 19)
#define CGU_CLK_ENA_CLK160M        (1U << 20)
#define CGU_CLK_ENA_CLK266M        (1U << 21)
#define CGU_CLK_ENA_CLK20M         (1U << 22)
#define CGU_CLK_ENA_CLK38P4M       (1U << 23)
#define CGU_CLK_ENA_CLK76P8M       (1U << 24)
#define CGU_CLK_ENA_PCLK           (1U << 25)
#define CGU_CLK_ENA_HCLK           (1U << 26)
#define CGU_CLK_ENA_SRAM0          (1U << 27)
#define CGU_CLK_ENA_SRAM1          (1U << 28)
#define CGU_CLK_ENA_ISP            (1U << 29)
#define CGU_CLK_ENA_JPEG           (1U << 30)
#define CGU_CLK_ENA_ETHOS_U85      (1U << 31)

/* Per-clock enable/disable helper prototypes */
void CGU_clock_enable_syspll(bool enable);
void CGU_clock_enable_cpupll(bool enable);
void CGU_clock_enable_clk25M(bool enable);
void CGU_clock_enable_clk50M(bool enable);
void CGU_clock_enable_clk100M(bool enable);
void CGU_clock_enable_clk10M(bool enable);
void CGU_clock_enable_clk80M(bool enable);
void CGU_clock_enable_mram(bool enable);
void CGU_clock_enable_clk200M(bool enable);
void CGU_clock_enable_clk400M(bool enable);
void CGU_clock_enable_trace(bool enable);
void CGU_clock_enable_hfxo(bool enable);
void CGU_clock_enable_clk160M(bool enable);
void CGU_clock_enable_clk266M(bool enable);
void CGU_clock_enable_clk20M(bool enable);
void CGU_clock_enable_clk38p4M(bool enable);
void CGU_clock_enable_clk76p8M(bool enable);
void CGU_clock_enable_pclk(bool enable);
void CGU_clock_enable_hclk(bool enable);
void CGU_clock_enable_sram0(bool enable);
void CGU_clock_enable_sram1(bool enable);
void CGU_clock_enable_isp(bool enable);
void CGU_clock_enable_jpeg(bool enable);
void CGU_clock_enable_ethos_u85(bool enable);

void CGU_clock_select_ospi_clk(uint32_t clk_sel);

#elif defined(ENSEMBLE_SOC_E1C)

/* CGU CLK_ENA bit masks for ENSEMBLE_SOC_E1C */
#define CGU_CLK_ENA_SYSPLL         (1U << 0)
#define CGU_CLK_ENA_CPUPLL         (1U << 4)
#define CGU_CLK_ENA_TRACE          (1U << 16)
#define CGU_CLK_ENA_HFXO           (1U << 18)
#define CGU_CLK_ENA_CLK160M        (1U << 20)
#define CGU_CLK_ENA_CLK100M        (1U << 21)
#define CGU_CLK_ENA_CLK20M         (1U << 22)
#define CGU_CLK_ENA_CLK38P4M       (1U << 23)
#define CGU_CLK_ENA_SRAM0          (1U << 24)
#define CGU_CLK_ENA_SRAM1          (1U << 28)

/* Per-clock enable/disable helper prototypes */
void CGU_clock_enable_syspll(bool enable);
void CGU_clock_enable_cpupll(bool enable);
void CGU_clock_enable_trace(bool enable);
void CGU_clock_enable_hfxo(bool enable);
void CGU_clock_enable_clk160M(bool enable);
void CGU_clock_enable_clk100M(bool enable);
void CGU_clock_enable_clk20M(bool enable);
void CGU_clock_enable_clk38p4M(bool enable);
void CGU_clock_enable_sram0(bool enable);
void CGU_clock_enable_sram1(bool enable);

#else

/* CGU CLK_ENA bit masks for ENSEMBLE_SOC_GEN1 */
#define CGU_CLK_ENA_SYSPLL         (1U << 0)
#define CGU_CLK_ENA_CPUPLL         (1U << 4)
#define CGU_CLK_ENA_TRACE          (1U << 16)
#define CGU_CLK_ENA_CLK160M        (1U << 20)
#define CGU_CLK_ENA_CLK100M        (1U << 21)
#define CGU_CLK_ENA_CLK20M         (1U << 22)
#define CGU_CLK_ENA_CLK38P4M       (1U << 23)
#define CGU_CLK_ENA_SRAM0          (1U << 24)
#define CGU_CLK_ENA_SRAM1          (1U << 28)

/* Per-clock enable/disable helper prototypes */
void CGU_clock_enable_syspll(bool enable);
void CGU_clock_enable_cpupll(bool enable);
void CGU_clock_enable_trace(bool enable);
void CGU_clock_enable_clk160M(bool enable);
void CGU_clock_enable_clk100M(bool enable);
void CGU_clock_enable_clk20M(bool enable);
void CGU_clock_enable_clk38p4M(bool enable);
void CGU_clock_enable_sram0(bool enable);
void CGU_clock_enable_sram1(bool enable);

#endif

#endif /* DRV_CGU_H */
