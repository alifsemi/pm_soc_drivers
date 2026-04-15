#include "soc_aon.h"
#include "soc_vbat.h"
#include "soc_hostbase.h"
#include "pm_soc_clk.h"

/* definitions for SystemAXIClock, SystemAHBClock, SystemAPBClock */
#include "sys_clocks.h"

/* definition for SystemCoreClock */
#include "system.h"

/*----------------------------------------------------------------------------
  Core identification function (0 = RTSS_HP, 1 = RTSS_HE)
 *----------------------------------------------------------------------------*/
uint32_t CoreID()
{
    uint32_t coreID = *((volatile uint32_t *)0xE00FEFE0UL);
    return coreID & 1;
}

/*----------------------------------------------------------------------------
  SoC Clock divider functions
 *----------------------------------------------------------------------------*/
static uint32_t GetDividerActiveHFRC() {
    uint32_t shift_val = (VBATSEC->VBAT_ANA_REG2 >> 11) & 7U;
    return shift_val;
}

static uint32_t GetDividerStandbyHFRC() {
    uint32_t shift_val = (VBATSEC->VBAT_ANA_REG2 >> 19) & 7U;

    if (shift_val > 6) shift_val += 3;          // 2^(7   + 3) = 1024 (75k)
    else if (shift_val > 3) shift_val += 2;     // 2^(4-6 + 2) = 64-256 (1.2M-300k)
    else if (shift_val > 2) shift_val += 1;     // 2^(3   + 1) = 16 (4.8M)
                                                // 2^(0-2 + 0) = 1-4 (76.8M-19.2M)
    return shift_val;
}

static uint32_t GetDividerActiveHFXO() {
    uint32_t shift_val;
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    shift_val = ((AONALL->MISC_REG1 >> 17) & 15U);
#else
    shift_val = ((AONALL->MISC_REG1 >> 13) & 15U);
#endif

    if (shift_val > 7) {
        shift_val -= 8;
        if (shift_val > 6) shift_val += 3;          // 2^(7   + 3) = 1024 (37.5k)
        else if (shift_val > 3) shift_val += 2;     // 2^(4-6 + 2) = 64-256 (600k-150k)
        else if (shift_val > 2) shift_val += 1;     // 2^(3   + 1) = 16 (2.4M)
                                                    // 2^(0-2 + 0) = 1-4 (38.4M-9.6M)
    }
    return shift_val;
}

/*----------------------------------------------------------------------------
  SoC Clock update functions
 *----------------------------------------------------------------------------*/

uint32_t pm_soc_clk_get_hfrc()
{
    return 76800000 >> GetDividerActiveHFRC();
}

uint32_t pm_soc_clk_get_hfxo()
{
    return 38400000 >> GetDividerActiveHFXO();
}

uint32_t pm_soc_clk_get_hfosc()
{
    if (CGU->OSC_CTRL & (1 << 4)) {
        SystemHFOSCClock = pm_soc_clk_get_hfxo();
    }
    else {
        SystemHFOSCClock = pm_soc_clk_get_hfrc() >> 1;
    }

    return SystemHFOSCClock;
}

/*----------------------------------------------------------------------------
  SYST_REFCLK update function
 *----------------------------------------------------------------------------*/
uint32_t pm_soc_clk_get_refclk()
{
    if (CGU->PLL_CLK_SEL & 1) {
#if defined(ENSEMBLE_SOC_E1C)
        SystemREFClock = 80000000;
#else
        SystemREFClock = 100000000;
#endif
    }
    else {
        if (CGU->OSC_CTRL & 1U) {
#if defined(ENSEMBLE_SOC_E1C) || defined(ENSEMBLE_SOC_GEN2)
            SystemREFClock = 76800000;
#else
            SystemREFClock = pm_soc_clk_get_hfxo();
#endif
        }
        else {
            SystemREFClock = pm_soc_clk_get_hfrc();
        }
    }

    return SystemREFClock;
}

/*----------------------------------------------------------------------------
  SYSPLL update function
 *----------------------------------------------------------------------------*/
static uint32_t GetSyspllPLL() {
#if defined(ENSEMBLE_SOC_E1C)
    return 160000000;
#else
    return 400000000;
#endif
}

static uint32_t SystSyspllUpdate()
{
    if (CGU->PLL_CLK_SEL & (1 << 4)) {
        return GetSyspllPLL();
    }
    else {
        if (CGU->OSC_CTRL & 1) {
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
            return 76800000;
#else
            return pm_soc_clk_get_hfxo();
#endif
        }
        else {
            return pm_soc_clk_get_hfrc();
        }
    }
}

static uint32_t SystCpupllUpdate()
{
#if defined(ENSEMBLE_SOC_E1C)
    return 0;
#else
    if (CGU->PLL_CLK_SEL & (1 << 4)) {
        return 800000000;
    }
    else {
        if (CGU->OSC_CTRL & 1) {
#if defined(ENSEMBLE_SOC_GEN2)
            return 76800000;
#else
            return pm_soc_clk_get_hfxo();
#endif
        }
        else {
            return pm_soc_clk_get_hfrc();
        }
    }
#endif
}

/*----------------------------------------------------------------------------
  SYST_ACLK update function
 *----------------------------------------------------------------------------*/
uint32_t pm_soc_clk_get_axiclk()
{
    uint32_t aclk_status = (HOSTBASE->ACLK_CTRL >> 8) & 0xFF;

    if (aclk_status == 1) {
        SystemAXIClock = pm_soc_clk_get_refclk();
    }
    else if (aclk_status == 2) {
        SystemAXIClock = SystSyspllUpdate() / ((HOSTBASE->ACLK_DIV0 >> 16) + 1);
    }

    return SystemAXIClock;
}

/*----------------------------------------------------------------------------
  SYST_HCLK update function
 *----------------------------------------------------------------------------*/
uint32_t pm_soc_clk_get_ahbclk()
{
    uint32_t syst_clkdiv = AONALL->SYSTOP_CLK_DIV & 0x303;
    uint8_t hclk_div = (syst_clkdiv >> 8) & 3;
    hclk_div = hclk_div > 2 ? 2 : hclk_div;

#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    uint32_t syspll_clk = SystSyspllUpdate();
    SystemAHBClock = syspll_clk >> hclk_div;
#else
    uint32_t systaxi_clk = pm_soc_clk_get_axiclk();
    SystemAHBClock = SystemAXIClock >> hclk_div;
#endif

    return SystemAHBClock;
}

/*----------------------------------------------------------------------------
  SYST_PCLK update function
 *----------------------------------------------------------------------------*/
uint32_t pm_soc_clk_get_apbclk()
{
    uint32_t syst_clkdiv = AONALL->SYSTOP_CLK_DIV & 0x303;
    uint8_t pclk_div = syst_clkdiv & 3;
    pclk_div = pclk_div > 2 ? 2 : pclk_div;

#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    uint32_t syspll_clk = SystSyspllUpdate();
    SystemAPBClock = syspll_clk >> pclk_div;
#else
    uint32_t systaxi_clk = pm_soc_clk_get_axiclk();
    SystemAPBClock = SystemAXIClock >> pclk_div;
#endif

    return SystemAPBClock;
}

/*----------------------------------------------------------------------------
  SYST_ACLK / SYST_HCLK / SYST_PCLK combined update function
 *----------------------------------------------------------------------------*/
uint32_t pm_soc_clk_get_busclk()
{
    uint32_t aclk_status = (HOSTBASE->ACLK_CTRL >> 8) & 0xFF;
    uint32_t syst_clkdiv = AONALL->SYSTOP_CLK_DIV & 0x303;
    uint8_t hclk_div = (syst_clkdiv >> 8) & 3;
    uint8_t pclk_div = syst_clkdiv & 3;

    hclk_div = hclk_div > 2 ? 2 : hclk_div;
    pclk_div = pclk_div > 2 ? 2 : pclk_div;

    if (aclk_status == 1) {
        SystemAXIClock = pm_soc_clk_get_refclk();
    }
    else if (aclk_status == 2) {
        SystemAXIClock = SystSyspllUpdate() / ((HOSTBASE->ACLK_DIV0 >> 16) + 1);
    }

#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    uint32_t syspll_clk = SystSyspllUpdate();
    SystemAHBClock = syspll_clk >> hclk_div;
    SystemAPBClock = syspll_clk >> pclk_div;
#else
    SystemAHBClock = SystemAXIClock >> hclk_div;
    SystemAPBClock = SystemAXIClock >> pclk_div;
#endif

    return SystemAXIClock;
}

/*----------------------------------------------------------------------------
  Top level clock divider config function, refer to "OSC_76M_DIV_CTRL" Registers in HWRM
 *----------------------------------------------------------------------------*/
int32_t pm_soc_clk_set_hfrc_div(uint32_t div_active, uint32_t div_standby)
{
    /* Configured divider value should be 0 to 7 */
    if ((div_active > 7) || (div_standby > 7)) return -1;

    /* VBAT_ANA_REG2 Register (0x1A60A03C)
     *
     * OSC_76M_DIV_CTRL_ACTIVE[13:11]
     *      in SoC "active" mode, HFRC is divided by 2^x, where x = 0 to 7
     *
     * OSC_76M_DIV_CTRL_STBY[21:19]
     *      in SoC "standby" mode, HFRC is divided
     *          by 2^x, where x = 0 to 2    (divide by 1 to 4)
     *          by 2^(x+1), where x = 3     (divide by 16)
     *          by 2^(x+2), where x = 4 to 6(divide by 64 to 256)
     *          by 2^(x+3), where x = 7     (divide by 1024)
     * 
     * Note: SoC "standby" mode is only when all PDs > 2 are off
     */

    uint32_t reg_data = VBATSEC->VBAT_ANA_REG2;
    reg_data &= ~((7U << 11) | (7U << 19));
    reg_data |= (div_active << 11) | (div_standby << 19);
    VBATSEC->VBAT_ANA_REG2 = reg_data;

    return 0;
}

int32_t pm_soc_clk_set_hfxo_div(uint32_t div_xtal)
{
    /* Configured divider value should be 0 to 7 */
    if (div_xtal > 7) return -1;

    uint32_t reg_data = AONALL->MISC_REG1;
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    /* MISC_REG1 Register (0x1A604030)
     *
     * cont_clkDiv[19:17]
     *      HF XTAL is divided by 2^x, where x = 0 to 7
     * sel_clkDivHi[20]
     *      simply should be set to 0
     */
    reg_data &= ~(15 << 17);
    reg_data |= (div_xtal << 17);
#else
    /* MISC_REG1 Register (0x1A604030)
     *
     * cont_clkDiv[15:13]
     *      HF XTAL is divided by 2^x, where x = 0 to 7
     * sel_clkDivHi[16]
     *      simply should be set to 0
     */
    reg_data &= ~(15 << 13);
    reg_data |= (div_xtal << 13);
#endif
    AONALL->MISC_REG1 = reg_data;

    return 0;
}

/*----------------------------------------------------------------------------
  Oscillator clock select function, refer to "OSC_CTRL Register" in HWRM
 *----------------------------------------------------------------------------*/
void pm_soc_clk_set_osc_sel(uint32_t xtal_sel)
{
    /* OSC Control Register (0x00)
     *
     * sys_xtal_sel[0] 0: 76.8M HFRC, 1: 38.4M HFXO (E1/E3/E5/E7)
     * sys_xtal_sel[0] 0: 76.8M HFRC, 1: 76.8M HFXOx2 (B1/E1C/E4/E6/E8)
     *      used by SYST_REFCLK, SYSPLL_CLK, CPUPLL_CLK
     *
     * periph_xtal_sel[4] 0: 38.4M HFRC, 1: 38.4M HFXO
     *      used by peripherals as HFOSC_CLK
     */
    uint32_t reg_data = CGU->OSC_CTRL;
    reg_data &= ~(0x11);
    reg_data |=  (0x11 & xtal_sel);
    CGU->OSC_CTRL = reg_data;
}

/*----------------------------------------------------------------------------
  PLL clock select function, refer to "PLL_CLK_SEL Register" in HWRM
 *----------------------------------------------------------------------------*/
void pm_soc_clk_set_pll_sel(uint32_t pll_sel)
{
    /* Switch from non-PLL to PLL clock
     *  osc_mix_clk is result of sys_xtal_sel bit in OSC_CTRL register
     *
     *  SYSREF[0] 0: osc_mix_clk, 1: PLL-100M (E1-E8) or PLL-80M (B1/E1C)
     *      select the source for SYST_REFCLK
     *  SYS[4] 0: osc_mix_clk, 1: PLL-400M (E1-E8) or PLL-160M (B1/E1C)
     *      select the source for SYSPLL_CLK and CPUPLL_CLK (E5-E8)
     *  ES0[16]         - HFRC/HFXO or PLL, refer to ESCLK_SEL
     *      select the source for RTSS_HP_CLK
     *  ES1[20]         - HFRC/HFXO or PLL, refer to ESCLK_SEL
     *      select the source for RTSS_HE_CLK
     */
    uint32_t reg_data = CGU->PLL_CLK_SEL;
    reg_data &= ~(0x110011);
    reg_data |=  (0x110011 & pll_sel);
    CGU->PLL_CLK_SEL = reg_data;
}

/*----------------------------------------------------------------------------
  Bus clock select function, refer to "CLKCTL_SYS Registers" and "SYSTOP_CLK_DIV Register" in HWRM
 *----------------------------------------------------------------------------*/
int32_t pm_soc_clk_set_busclk(uint32_t aclk_ctrl, uint32_t aclk_div, uint32_t hclk_div, uint32_t pclk_div)
{
    /* ACLK select should be 1 (SYST_REFCLK) or 2 (SYSPLL_CLK)
     * Note: ACLK divider is n + 1, where n is up to 31
     * Note: divider is only valid on 2 (SYSPLL_CLK)
     */
    if ((aclk_ctrl != 1) && (aclk_ctrl != 2)) return -1;
    if ((aclk_ctrl == 1) && (aclk_div != 0)) return -1;

    /* ACLK is further divided to create HCLK and PCLK
     * HCLK and PCLK divider should be 0 to 2
     * Note: divider is 2^n
     */
    if ((hclk_div > 2) || (pclk_div > 2)) return - 1;

    /* Refer to "ACLK_CTRL" and "ACLK_DIV0" Registers in the HWRM */
    HOSTBASE->ACLK_CTRL = aclk_ctrl;
    HOSTBASE->ACLK_DIV0 = aclk_div;

    /* Refer to "SYSTOP_CLK_DIV Register" in the HWRM */
    uint32_t reg_data = AONALL->SYSTOP_CLK_DIV;
    reg_data &= ~(0x303);
    reg_data |=  (0x303 & (hclk_div << 8 | pclk_div));
    AONALL->SYSTOP_CLK_DIV = reg_data;

    return 0;
}

#if (defined(M55_HE) || defined(M55_HP))
/*----------------------------------------------------------------------------
  Core clock update function for RTSS (Cortex-M55 subsystems)
 *----------------------------------------------------------------------------*/
uint32_t pm_core_clk_update()
{
    uint32_t coreID = CoreID();
    uint32_t PLL_CLK_SEL = CGU->PLL_CLK_SEL;
    uint32_t ESCLK_SEL = CGU->ESCLK_SEL;

#if defined(ENSEMBLE_SOC_GEN2)
    uint32_t const pll_rtss_hp_clocks[4] = {100000000UL, 200000000UL, 400000000UL, 400000000UL};
    uint32_t const pll_rtss_he_clocks[4] = {80000000UL, 80000000UL, 160000000UL, 160000000UL};
    uint32_t const osc_rtss_clocks[4] = {76800000UL, 38400000UL, 76800000UL, 38400000UL};
#else
    uint32_t const pll_rtss_hp_clocks[4] = {100000000UL, 200000000UL, 300000000UL, 400000000UL};
    uint32_t const pll_rtss_he_clocks[4] = {60000000UL, 80000000UL, 120000000UL, 160000000UL};
    uint32_t const osc_rtss_clocks[4] = {76800000UL, 38400000UL, 76800000UL, 38400000UL};
#endif

    if (coreID == 0) {
        if ((PLL_CLK_SEL >> 16) & 1) {
            ESCLK_SEL = ESCLK_SEL & 3;
            SystemCoreClock = pll_rtss_hp_clocks[ESCLK_SEL];

            return SystemCoreClock;
        }
        else {
            ESCLK_SEL = (ESCLK_SEL >> 8) & 3;
        }
    }
    else {
        if ((PLL_CLK_SEL >> 20) & 1) {
            ESCLK_SEL = (ESCLK_SEL >> 4) & 3;
            SystemCoreClock = pll_rtss_he_clocks[ESCLK_SEL];

            return SystemCoreClock;
        }
        else {
            ESCLK_SEL = (ESCLK_SEL >> 12) & 3;
        }
    }

    uint32_t shift_val = 0;

    /* ESCLK = 0, using 76.8M HFRC/X. ESCLK = 1, using 76.8M HFRC/2/X. */
    /* HFRC can be further divided by X=(2^n) divider */
    if (ESCLK_SEL < 2) {
        shift_val = GetDividerActiveHFRC();
    }

    /* ESCLK == 2, using 76.8M HFXOx2. ESCLK == 3, using 38.4M HFXO/Z
     * Only 38.4M HFXO option can be further divided by Z=(2^n) divider */
    else if (ESCLK_SEL == 3) {
        shift_val = GetDividerActiveHFXO();
    }

    SystemCoreClock = osc_rtss_clocks[ESCLK_SEL];
    SystemCoreClock >>= shift_val;
    return SystemCoreClock;
}

/*----------------------------------------------------------------------------
  Core clock config function for RTSS (Cortex-M55 subsystems)
 *----------------------------------------------------------------------------*/
int32_t pm_core_clk_set(uint32_t osc_sel, uint32_t pll_sel)
{
    /* mux select values should be 0 to 3 */
    if ((osc_sel > 3) || (pll_sel > 3)) return -1;

    /* get the number of bits to shift in the register depending on CoreID */
    uint32_t shift_val = CoreID() ? 4 : 0;

    /* refer to CoreClockUpdate() function for how to set esclk_sel value */
    uint32_t reg_data = CGU->ESCLK_SEL;

    /* RTSS clock will be pll_rtss_he/hp_clocks[esclk_sel] */
    reg_data &= ~(3U << shift_val);
    reg_data |= (pll_sel << shift_val);

    /* RTSS clock will be osc_rtss_clocks[esclk_sel] */
    shift_val += 8;
    reg_data &= ~(3U << shift_val);
    reg_data |= (osc_sel << shift_val);

    CGU->ESCLK_SEL = reg_data;

    return 0;
}
#else
/*----------------------------------------------------------------------------
  Core clock update function for APSS (Cortex-A subsystem)
 *----------------------------------------------------------------------------*/
uint32_t pm_core_clk_update()
{
    uint32_t apss_clk_status = (HOSTBASE->HOSTCPUCLK_CTRL >> 8) & 0xFF;
    if (apss_clk_status == 0)
    {
        SystemCoreClock = 0;
    }
    else if (apss_clk_status == 1) {
        SystemCoreClock = pm_soc_clk_get_refclk();
    }
    else if (apss_clk_status == 2) {
        SystemCoreClock = SystSyspllUpdate() / ((HOSTBASE->HOSTCPUCLK_DIV1 >> 16) + 1);
    }
    else if (apss_clk_status == 4) {
        SystemCoreClock = SystCpupllUpdate() / ((HOSTBASE->HOSTCPUCLK_DIV0 >> 16) + 1);
    }

    return SystemCoreClock;
}

/*----------------------------------------------------------------------------
  Core clock config function for APSS (Cortex-A subsystem)
 *----------------------------------------------------------------------------*/
int32_t pm_core_clk_set(uint32_t clk_src, uint32_t clk_div)
{
    if ((clk_src != 1) && (clk_src != 2) && (clk_src != 4)) return -1;
    if ((clk_src == 1) && (clk_div != 0)) return -1;
    if ((clk_src == 2) && (clk_div > 31)) return -1;
    if ((clk_src == 4) && (clk_div > 31)) return -1;

    /* pre-set the divider before setting the clock source */
    if (clk_src == 2) {
        HOSTBASE->HOSTCPUCLK_DIV1 = clk_div;
    }
    else if (clk_src == 4) {
        HOSTBASE->HOSTCPUCLK_DIV0 = clk_div;
    }
    HOSTBASE->HOSTCPUCLK_CTRL = clk_src;

    return 0;
}
#endif
