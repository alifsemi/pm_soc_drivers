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

/**
  @fn       void CGU_clock_enable_syspll(bool enable)
  @brief    Enable or disable the SYSPLL clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_syspll(bool enable);

/**
  @fn       void CGU_clock_enable_cpupll(bool enable)
  @brief    Enable or disable the CPUPLL clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_cpupll(bool enable);

/**
  @fn       void CGU_clock_enable_clk25M(bool enable)
  @brief    Enable or disable the 25MHz clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk25M(bool enable);

/**
  @fn       void CGU_clock_enable_clk50M(bool enable)
  @brief    Enable or disable the 50MHz clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk50M(bool enable);

/**
  @fn       void CGU_clock_enable_clk100M(bool enable)
  @brief    Enable or disable the 100MHz clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk100M(bool enable);

/**
  @fn       void CGU_clock_enable_clk10M(bool enable)
  @brief    Enable or disable the 10MHz clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk10M(bool enable);

/**
  @fn       void CGU_clock_enable_clk80M(bool enable)
  @brief    Enable or disable the 80MHz clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk80M(bool enable);

/**
  @fn       void CGU_clock_enable_mram(bool enable)
  @brief    Enable or disable the MRAM clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_mram(bool enable);

/**
  @fn       void CGU_clock_enable_clk200M(bool enable)
  @brief    Enable or disable the 200MHz clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk200M(bool enable);

/**
  @fn       void CGU_clock_enable_clk400M(bool enable)
  @brief    Enable or disable the 400MHz clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk400M(bool enable);

/**
  @fn       void CGU_clock_enable_trace(bool enable)
  @brief    Enable or disable the debug trace clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_trace(bool enable);

/**
  @fn       void CGU_clock_enable_hfxo(bool enable)
  @brief    Enable or disable the HFXO clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_hfxo(bool enable);

/**
  @fn       void CGU_clock_enable_clk160M(bool enable)
  @brief    Enable or disable the 160MHz clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk160M(bool enable);

/**
  @fn       void CGU_clock_enable_clk266M(bool enable)
  @brief    Enable or disable the 266MHz clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk266M(bool enable);

/**
  @fn       void CGU_clock_enable_clk20M(bool enable)
  @brief    Enable or disable the 20MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk20M(bool enable);

/**
  @fn       void CGU_clock_enable_clk38p4M(bool enable)
  @brief    Enable or disable the 38.4MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk38p4M(bool enable);

/**
  @fn       void CGU_clock_enable_clk76p8M(bool enable)
  @brief    Enable or disable the 76.8MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk76p8M(bool enable);

/**
  @fn       void CGU_clock_enable_pclk(bool enable)
  @brief    Enable or disable the APB PCLK output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_pclk(bool enable);

/**
  @fn       void CGU_clock_enable_hclk(bool enable)
  @brief    Enable or disable the AHB HCLK output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_hclk(bool enable);

/**
  @fn       void CGU_clock_enable_sram0(bool enable)
  @brief    Enable or disable the SRAM0 clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_sram0(bool enable);

/**
  @fn       void CGU_clock_enable_sram1(bool enable)
  @brief    Enable or disable the SRAM1 clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_sram1(bool enable);

/**
  @fn       void CGU_clock_enable_isp(bool enable)
  @brief    Enable or disable the ISP clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_isp(bool enable);

/**
  @fn       void CGU_clock_enable_jpeg(bool enable)
  @brief    Enable or disable the JPEG clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_jpeg(bool enable);

/**
  @fn       void CGU_clock_enable_ethos_u85(bool enable)
  @brief    Enable or disable the Ethos-U85 NPU clock output from the
            CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_ethos_u85(bool enable);

/**
  @fn       void CGU_clock_select_ospi_clk(uint32_t clk_sel)
  @brief    Select the clock source feeding the OSPI (HEXSPI) block.
            0 selects the ACLK-derived path (up to 400MHz), 1 selects a
            fixed 266MHz source from the PLL.
            Refer to "MISC_CLK_CTRL Register" in HWRM for more details.
  @param    clk_sel OSPI clock source select (0 = ACLK path,
                    1 = 266MHz PLL)
  @return   None
*/
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

/**
  @fn       void CGU_clock_enable_syspll(bool enable)
  @brief    Enable or disable the SYSPLL clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_syspll(bool enable);

/**
  @fn       void CGU_clock_enable_cpupll(bool enable)
  @brief    Enable or disable the CPUPLL clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_cpupll(bool enable);

/**
  @fn       void CGU_clock_enable_trace(bool enable)
  @brief    Enable or disable the debug trace clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_trace(bool enable);

/**
  @fn       void CGU_clock_enable_hfxo(bool enable)
  @brief    Enable or disable the HFXO clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_hfxo(bool enable);

/**
  @fn       void CGU_clock_enable_clk160M(bool enable)
  @brief    Enable or disable the 160MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk160M(bool enable);

/**
  @fn       void CGU_clock_enable_clk100M(bool enable)
  @brief    Enable or disable the 100MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk100M(bool enable);

/**
  @fn       void CGU_clock_enable_clk20M(bool enable)
  @brief    Enable or disable the 20MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk20M(bool enable);

/**
  @fn       void CGU_clock_enable_clk38p4M(bool enable)
  @brief    Enable or disable the 38.4MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk38p4M(bool enable);

/**
  @fn       void CGU_clock_enable_sram0(bool enable)
  @brief    Enable or disable the SRAM0 clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_sram0(bool enable);

/**
  @fn       void CGU_clock_enable_sram1(bool enable)
  @brief    Enable or disable the SRAM1 clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
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

/**
  @fn       void CGU_clock_enable_syspll(bool enable)
  @brief    Enable or disable the SYSPLL clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_syspll(bool enable);

/**
  @fn       void CGU_clock_enable_cpupll(bool enable)
  @brief    Enable or disable the CPUPLL clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_cpupll(bool enable);

/**
  @fn       void CGU_clock_enable_trace(bool enable)
  @brief    Enable or disable the debug trace clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_trace(bool enable);

/**
  @fn       void CGU_clock_enable_clk160M(bool enable)
  @brief    Enable or disable the 160MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk160M(bool enable);

/**
  @fn       void CGU_clock_enable_clk100M(bool enable)
  @brief    Enable or disable the 100MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk100M(bool enable);

/**
  @fn       void CGU_clock_enable_clk20M(bool enable)
  @brief    Enable or disable the 20MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk20M(bool enable);

/**
  @fn       void CGU_clock_enable_clk38p4M(bool enable)
  @brief    Enable or disable the 38.4MHz clock output from the CGU.
            Reset default: disabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_clk38p4M(bool enable);

/**
  @fn       void CGU_clock_enable_sram0(bool enable)
  @brief    Enable or disable the SRAM0 clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_sram0(bool enable);

/**
  @fn       void CGU_clock_enable_sram1(bool enable)
  @brief    Enable or disable the SRAM1 clock output from the CGU.
            Reset default: enabled.
            Refer to "CLK_ENA Register" in HWRM for more details.
  @param    enable  true to enable the clock, false to disable it
  @return   None
*/
void CGU_clock_enable_sram1(bool enable);

#endif

#endif /* DRV_CGU_H */
