#include <stdint.h>

/**
  @fn       uint32_t pm_soc_clk_get_hfrc(void)
  @brief    Get the current HFRC oscillator frequency in Hz, taking the
            active-mode HFRC divider into account.
            Refer to "VBAT_ANA_REG2 Register" in HWRM for more details.
  @return   HFRC clock frequency in Hz
*/
uint32_t pm_soc_clk_get_hfrc();

/**
  @fn       uint32_t pm_soc_clk_get_hfxo(void)
  @brief    Get the current HFXO crystal oscillator frequency in Hz, taking
            the active-mode HFXO divider into account.
            Refer to "MISC_REG1 Register" in HWRM for more details.
  @return   HFXO clock frequency in Hz
*/
uint32_t pm_soc_clk_get_hfxo();

/**
  @fn       uint32_t pm_soc_clk_get_hfosc(void)
  @brief    Get the current HFOSC_CLK frequency in Hz, as used by peripherals
            such as UART and CAN. The source is selected between HFRC and
            HFXO via the periph_xtal_sel field.
            Refer to "OSC_CTRL Register" in HWRM for more details.
  @return   HFOSC clock frequency in Hz
*/
uint32_t pm_soc_clk_get_hfosc();    /* used by some peripherals like UART and CAN */

/**
  @fn       uint32_t pm_soc_clk_get_refclk(void)
  @brief    Get the current SYST_REFCLK frequency in Hz. The source is
            either PLL or the oscillator mix clock, depending on the
            PLL_CLK_SEL[SYSREF] select bit.
            Refer to "OSC_CTRL Register" and "PLL_CLK_SEL Register" in HWRM
            for more details.
  @return   SYST_REFCLK frequency in Hz
*/
uint32_t pm_soc_clk_get_refclk();   /* returns REFCLK */

/**
  @fn       uint32_t pm_soc_clk_get_axiclk(void)
  @brief    Get the current SYST_ACLK (AXI) frequency in Hz. The source is
            selected by the ACLK control field, and may optionally be
            divided down from SYSPLL.
            Refer to "ACLK_CTRL Register" and "ACLK_DIV0 Register" in HWRM
            for more details.
  @return   SYST_ACLK frequency in Hz
*/
uint32_t pm_soc_clk_get_axiclk();   /* returns SYST_ACLK (AXI) */

/**
  @fn       uint32_t pm_soc_clk_get_ahbclk(void)
  @brief    Get the current SYST_HCLK (AHB) frequency in Hz. SYST_HCLK is
            derived from SYST_ACLK (or SYSPLL on newer families) using the
            HCLK divider field.
            Refer to "SYSTOP_CLK_DIV Register" in HWRM for more details.
  @return   SYST_HCLK frequency in Hz
*/
uint32_t pm_soc_clk_get_ahbclk();   /* returns SYST_HCLK (AHB) */

/**
  @fn       uint32_t pm_soc_clk_get_apbclk(void)
  @brief    Get the current SYST_PCLK (APB) frequency in Hz. SYST_PCLK is
            derived from SYST_ACLK (or SYSPLL on newer families) using the
            PCLK divider field.
            Refer to "SYSTOP_CLK_DIV Register" in HWRM for more details.
  @return   SYST_PCLK frequency in Hz
*/
uint32_t pm_soc_clk_get_apbclk();   /* returns SYST_PCLK (APB) */

/**
  @fn       uint32_t pm_soc_clk_get_busclk(void)
  @brief    Update SYST_REFCLK, SYST_ACLK, SYST_HCLK and SYST_PCLK all at
            once, and return the AXI bus clock frequency.
            Refer to "ACLK_CTRL Register", "ACLK_DIV0 Register" and
            "SYSTOP_CLK_DIV Register" in HWRM for more details.
  @return   SYST_ACLK frequency in Hz
*/
uint32_t pm_soc_clk_get_busclk();   /* updates REFCLK, AXI, AHB, APB all at once, returns SYST_ACLK */

/**
  @fn       int32_t pm_soc_clk_set_hfrc_div(uint32_t div_active,
                                            uint32_t div_standby)
  @brief    Configure the HFRC clock dividers used in SoC active and standby
            modes. Each divider is a 3-bit field; the resulting divide ratio
            is 2^x in active mode, and a family-specific mapping in standby.
            Refer to "VBAT_ANA_REG2 Register" (OSC_76M_DIV_CTRL fields) in
            HWRM for more details.
  @param    div_active  HFRC divider for SoC active mode (valid range 0-7)
  @param    div_standby HFRC divider for SoC standby mode (valid range 0-7)
  @return   0 on success, -1 if any argument is out of range
*/
int32_t  pm_soc_clk_set_hfrc_div(uint32_t div_active, uint32_t div_standby);

/**
  @fn       int32_t pm_soc_clk_set_hfxo_div(uint32_t div_xtal)
  @brief    Configure the HFXO crystal oscillator divider. The HFXO clock is
            divided by 2^div_xtal.
            Refer to "MISC_REG1 Register" (CLKDIV field) in HWRM for
            more details.
  @param    div_xtal    HFXO divider value (valid range 0-7)
  @return   0 on success, -1 if div_xtal is out of range
*/
int32_t  pm_soc_clk_set_hfxo_div(uint32_t div_xtal);

/**
  @fn       void pm_soc_clk_set_osc_sel(uint32_t xtal_sel)
  @brief    Select the oscillator source (HFRC or HFXO) used for both the
            system reference clock (sys_xtal_sel bit) and the peripheral
            clock (periph_xtal_sel bit).
            Refer to "OSC_CTRL Register" in HWRM for more details.
  @param    xtal_sel    Bitmask: bit 0 selects sys_xtal_sel, bit 4 selects
                        periph_xtal_sel. 0 selects HFRC, 1 selects HFXO.
  @return   None
*/
void     pm_soc_clk_set_osc_sel(uint32_t xtal_sel);

/**
  @fn       void pm_soc_clk_set_pll_sel(uint32_t pll_sel)
  @brief    Select whether SYST_REFCLK, SYST_ACLK, RTSS_HP_CLK, and
            RTSS_HE_CLK are sourced from the oscillator or from the PLL.
            Refer to "PLL_CLK_SEL Register" in HWRM for more details.
  @param    pll_sel     Bitmask selecting PLL vs. oscillator for each
                        consumer (bit 0 SYST_REFCLK, bit 4 SYST_ACLK,
                        bit 16 RTSS_HP_CLK, bit 20 RTSS_HE_CLK).
  @return   None
*/
void     pm_soc_clk_set_pll_sel(uint32_t pll_sel);

/**
  @fn       int32_t pm_soc_clk_set_busclk(uint32_t aclk_ctrl,
                                          uint32_t aclk_div,
                                          uint32_t hclk_div,
                                          uint32_t pclk_div)
  @brief    Configure the ACLK source, ACLK divider, and the HCLK/PCLK
            dividers derived from ACLK.
            Refer to "ACLK_CTRL Register", "ACLK_DIV0 Register" and
            "SYSTOP_CLK_DIV Register" in HWRM for more details.
  @param    aclk_ctrl   ACLK source select: 1 = SYST_REFCLK, 2 = SYSPLL_CLK
  @param    aclk_div    ACLK divider value (n, actual divide is n+1, up to
                        31; only valid when aclk_ctrl is 2)
  @param    hclk_div    HCLK divider exponent (0-2, actual divide is 2^n)
  @param    pclk_div    PCLK divider exponent (0-2, actual divide is 2^n)
  @return   0 on success, -1 if any argument is out of range
*/
int32_t  pm_soc_clk_set_busclk(uint32_t aclk_ctrl, uint32_t aclk_div, uint32_t hclk_div, uint32_t pclk_div);

#if (defined(M55_HE) || defined(M55_HP))
/* for Cortex-M cores in RTSS */

/**
  @fn       uint32_t pm_core_clk_update(void)
  @brief    Update and return the current RTSS Cortex-M55 core clock in Hz.
            The source and divider are determined by the PLL select bit for
            this core and the ESCLK_SEL field.
            Refer to "PLL_CLK_SEL Register" and "ESCLK_SEL Register" in
            HWRM for more details.
  @return   RTSS_HE_CLOCK or RTSS_HP_CLOCK in Hz (also written to
            SystemCoreClock)
*/
uint32_t pm_core_clk_update();      /* returns RTSS_HE_CLOCK or RTSS_HP_CLOCK */

/**
  @fn       int32_t pm_core_clk_set(uint32_t osc_sel, uint32_t pll_sel)
  @brief    Configure the RTSS Cortex-M55 core clock source selection. The
            oscillator and PLL mux selects map into the ESCLK_SEL field for
            the calling core.
            Refer to "ESCLK_SEL Register" in HWRM for more details.
  @param    osc_sel     Oscillator mux select (valid range 0-3)
  @param    pll_sel     PLL mux select (valid range 0-3)
  @return   0 on success, -1 if any argument is out of range
*/
int32_t  pm_core_clk_set(uint32_t osc_sel, uint32_t pll_sel);
#else
/* for Cortex-A cores in APSS (TBD) */

/**
  @fn       uint32_t pm_core_clk_update(void)
  @brief    Update and return the current APSS Cortex-A core clock in Hz.
            The source is either SYST_REFCLK, SYSPLL, or CPUPLL, each with
            an independent divider.
            Refer to "HOSTCPUCLK_CTRL Register", "HOSTCPUCLK_DIV0 Register"
            and "HOSTCPUCLK_DIV1 Register" in HWRM for more details.
  @return   APSS_CPU_CLOCK in Hz (also written to SystemCoreClock)
*/
uint32_t pm_core_clk_update();      /* returns APSS_CPU_CLOCK */

/**
  @fn       int32_t pm_core_clk_set(uint32_t clk_src, uint32_t clk_div)
  @brief    Configure the APSS Cortex-A core clock source and divider.
            Refer to "HOSTCPUCLK_CTRL Register", "HOSTCPUCLK_DIV0 Register"
            and "HOSTCPUCLK_DIV1 Register" in HWRM for more details.
  @param    clk_src     Clock source: 1 = SYST_REFCLK, 2 = SYSPLL_CLK,
                        4 = CPUPLL_CLK
  @param    clk_div     Divider value (n, actual divide is n+1, up to 31;
                        must be 0 when clk_src is 1)
  @return   0 on success, -1 if any argument is out of range
*/
int32_t  pm_core_clk_set(uint32_t clk_src, uint32_t clk_div);
#endif
