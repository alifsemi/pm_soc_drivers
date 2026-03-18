#include "hostbase.h"
#include "soc_clk.h"

#include "sys_clocks.h"
#include "alif.h"

/*----------------------------------------------------------------------------
  Core identification function (0 = RTSS_HP, 1 = RTSS_HE)
 *----------------------------------------------------------------------------*/
uint32_t CoreID()
{
    uint32_t coreID = *((volatile uint32_t *)0xE00FEFE0UL);
    return coreID & 1;
}

/*----------------------------------------------------------------------------
  SoC Top Clock get divider functions
 *----------------------------------------------------------------------------*/
static uint32_t GetDividerActiveHFRC() {
    uint32_t shift_val = (ANA->VBAT_ANA_REG2 >> 11) & 7U;
    return shift_val;
}

static uint32_t GetDividerStandbyHFRC() {
    uint32_t shift_val = (ANA->VBAT_ANA_REG2 >> 19) & 7U;
    if (shift_val > 7) {
        shift_val -= 8;
        if (shift_val > 6) shift_val += 3;          // 2^(7   + 3) = 1024 (75k)
        else if (shift_val > 3) shift_val += 2;     // 2^(4-6 + 2) = 64-256 (1.2M-300k)
        else if (shift_val > 2) shift_val += 1;     // 2^(3   + 1) = 16 (4.8M)
                                                    // 2^(0-2 + 0) = 1-4 (76.8M-19.2M)
    }
    return shift_val;
}

static uint32_t GetDividerActiveHFXO() {
    uint32_t shift_val;
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    shift_val = ((AON->MISC_REG1 >> 17) & 15U);
#else
    shift_val = ((AON->MISC_REG1 >> 13) & 15U);
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
  SoC Top Clock update functions
 *----------------------------------------------------------------------------*/

uint32_t SocTopClockHFRC()
{
    return 76800000 >> GetDividerActiveHFRC();
}

uint32_t SocTopClockHFXO()
{
    return 38400000 >> GetDividerActiveHFXO();
}

uint32_t SocTopClockHFOSC()
{
    if (CGU->OSC_CTRL & (1 << 4)) {
        SystemHFOSCClock = SocTopClockHFXO();
    }
    else {
        SystemHFOSCClock = SocTopClockHFRC() >> 1;
    }

    return SystemHFOSCClock;
}

/*----------------------------------------------------------------------------
  SYST_REFCLK update function
 *----------------------------------------------------------------------------*/
uint32_t SystRefclkUpdate()
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
            SystemREFClock = SocTopClockHFXO();
#endif
        }
        else {
            SystemREFClock = SocTopClockHFRC();
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
            return SocTopClockHFXO();
#endif
        }
        else {
            return SocTopClockHFRC();
        }
    }
}

/*----------------------------------------------------------------------------
  SYST_ACLK / SYST_HCLK / SYST_PCLK bus clock update function
 *----------------------------------------------------------------------------*/
uint32_t SystBusClkUpdate()
{
    uint32_t aclk_status = (HOSTBASE->ACLK_CTRL >> 8) & 0xFF;
    uint32_t syst_clkdiv = AON->SYSTOP_CLK_DIV & 0x303;
    uint8_t hclk_div = (syst_clkdiv >> 8) & 3;
    uint8_t pclk_div = syst_clkdiv & 3;

    hclk_div = hclk_div > 2 ? 2 : hclk_div;
    pclk_div = pclk_div > 2 ? 2 : pclk_div;

    if (aclk_status == 1) {
        SystemAXIClock = SystRefclkUpdate();
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
  Core clock update function for RTSS-M55 subsystems
 *----------------------------------------------------------------------------*/
uint32_t CoreClockUpdate()
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
  Core clock config function
 *----------------------------------------------------------------------------*/
int32_t CoreClockConfig(uint32_t esclk_osc_sel, uint32_t esclk_pll_sel)
{
    /* Configured divider values should be 0 to 3
     */
    if ((esclk_osc_sel > 3) || (esclk_pll_sel > 3)) return -1;

    /* get the number of bits to shift in the register depending on CoreID */
    uint32_t shift_val = CoreID() ? 4 : 0;

    /* refer to CoreClockUpdate() function for how to set esclk_sel value */
    uint32_t reg_data = CGU->ESCLK_SEL;

    /* RTSS clock will be pll_rtss_he/hp_clocks[esclk_sel] */
    reg_data &= ~(3U << shift_val);
    reg_data |= (esclk_pll_sel << shift_val);

    /* RTSS clock will be osc_rtss_clocks[esclk_sel] */
    shift_val += 8;
    reg_data &= ~(3U << shift_val);
    reg_data |= (esclk_osc_sel << shift_val);

    CGU->ESCLK_SEL = reg_data;

    return 0;
}

/*----------------------------------------------------------------------------
  Top level clock divider config function, refer to "OSC_76M_DIV_CTRL" Registers in HWRM
 *----------------------------------------------------------------------------*/
int32_t DivClockConfig(uint32_t div_active, uint32_t div_standby, uint32_t div_xtal)
{
    /* Configured divider values should be 0 to 7
     */
    if ((div_active > 7) || (div_standby > 7) || (div_xtal > 7)) return -1;

    /* VBAT_ANA_REG2 Register (0x1A60A03C)
     *
     * OSC_76M_DIV_CTRL_ACTIVE[13:11]
     *      in "active" mode, HFRC is divided by 2^x, where x = 0 to 7
     *
     * OSC_76M_DIV_CTRL_STBY[21:19]
     *      in "standby" mode, HFRC is divided
     *          by 2^x, where x = 0 to 2    (divide by 1 to 4)
     *          by 2^(x+1), where x = 3     (divide by 16)
     *          by 2^(x+2), where x = 4 to 6(divide by 64 to 256)
     *          by 2^(x+3), where x = 7     (divide by 1024)
     */

    uint32_t reg_data = ANA->VBAT_ANA_REG2;
    reg_data &= ~((7U << 11) | (7U << 19));
    reg_data |= (div_active << 11) | (div_standby << 19);
    ANA->VBAT_ANA_REG2 = reg_data;

    reg_data = *((volatile uint32_t *)0x1A604030);
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
    *((volatile uint32_t *)0x1A604030) = reg_data;

    return 0;
}

/*----------------------------------------------------------------------------
  Oscillator clock select function, refer to "OSC_CTRL Register" in HWRM
 *----------------------------------------------------------------------------*/
void OscClockConfig(uint32_t xtal_sel)
{
    /* OSC Control Register (0x00)
     *
     * sys_xtal_sel[0] 0: 76.8M HFRC, 1: 38.4M HFXO (bolt)
     * sys_xtal_sel[0] 0: 76.8M HFRC, 1: 76.8M HFXOx2 (eagle/spark)
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
void PllClockConfig(uint32_t pll_sel)
{
    /* Switch from non-PLL to PLL clock
     *  osc_mix_clk is result of sys_xtal_sel bit
     *  osc_9p6M_clk is result of periph_xtal_sel bit
     *  ESx HFRC/HFXO clk is result of ESCLK_SEL bits
     *
     *  SYST_REFCLK[0]  - osc_mix_clk  or PLL-100M
     *  SYST_ACLK[4]    - osc_mix_clk  or PLL-400M
     *  ES0[16]         - HFRC/HFXO or PLL, refer to ESCLK_SEL
     *  ES1[20]         - HFRC/HFXO or PLL, refer to ESCLK_SEL
     */
    uint32_t reg_data = CGU->PLL_CLK_SEL;
    reg_data &= ~(0x110111);
    reg_data |=  (0x110011 & pll_sel);
    CGU->PLL_CLK_SEL = reg_data;
}

/*----------------------------------------------------------------------------
  Bus clock select function, refer to "CLKCTL_SYS Registers" and "SYSTOP_CLK_DIV Register" in HWRM
 *----------------------------------------------------------------------------*/
int32_t BusClockConfig(uint32_t aclk_ctrl, uint32_t aclk_div, uint32_t hclk_div, uint32_t pclk_div)
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
    *((volatile uint32_t *)0x1A010820) = aclk_ctrl;
    *((volatile uint32_t *)0x1A010824) = aclk_div;

    /* Refer to "SYSTOP_CLK_DIV Register" in the HWRM */
    uint32_t reg_data = AON->SYSTOP_CLK_DIV;
    reg_data &= ~(0x303);
    reg_data |=  (0x303 & (hclk_div << 8 | pclk_div));
    AON->SYSTOP_CLK_DIV = reg_data;

    return 0;
}
