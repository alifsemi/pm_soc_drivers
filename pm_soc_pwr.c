#include "soc_aon.h"
#include "soc_vbat.h"
#include "soc_hostbase.h"
#include "pm_soc_pwr.h"

/* for sys_busy_loop_us() function */
#include "sys_utils.h"

/* for CGU_Type */
#include "soc.h"

void pm_soc_set_dcdc_pfm(void) {
#if defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for this family */
#else
    VBATSEC->DCDC_REG2 |= (1U << 23);
#endif
}

void pm_soc_set_dcdc_pwm(void) {
#if defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for this family */
#else
    VBATSEC->DCDC_REG2 &= ~(1U << 23);
#endif
}

void pm_soc_set_dcdc_voltage(uint32_t millivolts) {
    if ((millivolts < 700) || (millivolts > 850)) {
        return; /* out of range */
    }
#if defined(ENSEMBLE_SOC_GEN2)

#elif defined(ENSEMBLE_SOC_E1C)

#endif
}

void pm_soc_enable_syst_sram(uint32_t sram_select)
{
#if defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for this family */
#else
    uint32_t reg_data;
    reg_data = CGU->CLK_ENA;

#if defined(ENSEMBLE_SOC_GEN2)
    /* SRAM0 clock enable is bit 27 */
    if (sram_select & SYST_SRAM0_EN) {
        reg_data |= (1UL << 27);
    } else {
        reg_data &= ~(1UL << 27);
    }
#else
    /* SRAM0 clock enable is bit 24 */
    if (sram_select & SYST_SRAM0_EN) {
        reg_data |= (1UL << 24);
    } else {
        reg_data &= ~(1UL << 24);
    }
#endif

    /* SRAM1 clock enable is bit 28 */
    if (sram_select & SYST_SRAM1_EN) {
        reg_data |= (1UL << 28);
    } else {
        reg_data &= ~(1UL << 28);
    }

    CGU->CLK_ENA = reg_data;

    reg_data = VBATSEC->PWR_CTRL;

    /* SRAM0 power mask is bit 8 */
    if (sram_select & SYST_SRAM0_EN) {
        reg_data &= ~(3UL << 8);
    } else {
        reg_data |= (3UL << 8);
    }

    /* SRAM1 power mask is bit 12 */
    if (sram_select & SYST_SRAM1_EN) {
        reg_data &= ~(3UL << 12);
    } else {
        reg_data |= (3UL << 12);
    }

    VBATSEC->PWR_CTRL = reg_data;

    /* TBD - replace with "BISR Done" Status */
    if (sram_select) {
        sys_busy_loop_us(60);
    }
#endif
}

void pm_soc_retain_syst_sram(uint32_t retention_select)
{
#if !defined(ENSEMBLE_SOC_GEN2)
    return; /* only applicable for Ensemble E4/E6/E8 */
#else
    uint32_t reg_data;
    reg_data = VBATALL->RET_CTRL;

    /* do not touch bits 0-7 */
    reg_data |= 0x3FF00; /* set all retention bits to 1 (no retention) */
    reg_data &= ~(retention_select); /* clear bits for SRAM blocks that should be retained */
    VBATALL->RET_CTRL = reg_data;
#endif
}

void pm_soc_enable_pd_syst()
{
    HOSTBASE->BSYS_PWR_REQ |= 1U << 4;
}

void pm_soc_disable_pd_syst()
{
    HOSTBASE->BSYS_PWR_REQ &= ~(1U << 4);
}

void pm_soc_enable_pd_debug()
{
    HOSTBASE->BSYS_PWR_REQ |= 1U << 2;
}

void pm_soc_disable_pd_debug()
{
    HOSTBASE->BSYS_PWR_REQ &= ~(1U << 2);
}

void pm_soc_enable_pd_sram_aon(uint32_t retention_select)
{
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for these families */
#else
    /* Enable PD1 via VBATSEC PWR_CTRL regiser */
    VBATSEC->PWR_CTRL |= 1U;

    /* Enable Main SRAM Retention LDO
     * Note: shared between SE, HE, PD4 SRAMs */
    VBATSEC->VBAT_ANA_REG1 |= (1U << 10);

    /* Enable PD4 SRAM Retention (optional) */
    retention_select = ~retention_select;
    VBATPD4->RET_CTRL = retention_select & 0x3333U;

    /* Disconnect PPU from M55-M[4] and M55-G[8]
     * Allows PD4 to turn on and off via functions:
     * pm_soc_enable_pd4_sram() / pm_soc_disable_pd4_sram() */
    VBATPD4->PWR_CTRL  = 0x110U;

    /* PD4 PWR STAT Value */
    while((AONSEC->PD4_PWR_STAT & 0x7FFUL) == 0);
#endif
}

void pm_soc_disable_pd_sram_aon()
{
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for these families */
#else
    /* Disable PD1 via VBATSEC PWR_CTRL regiser */
    VBATSEC->PWR_CTRL &= ~1U;

    /* Disable PD4 SRAM Retention */
    VBATPD4->RET_CTRL  = 0x3333U;

    /* PD4 PWR STAT Value */
    while((AONSEC->PD4_PWR_STAT & 0x7FFUL) != 0);
#endif
}

void pm_soc_enable_pd4_sram(uint32_t clk_sel)
{
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for these families */
#else
    /* Switch PD4 between HFXO and PLL-160M clock */
    AONSEC->PD4_CLK_SEL = clk_sel ? 3 : 0;
    AONSEC->PD4_CLK_PLL = clk_sel ? 1 : 0;

    /* Enable PD4 */
    AONSEC->PD4_PWR_CTRL |= (1U << 12);

    /* PD4 PWR STAT Value */
    while((AONSEC->PD4_PWR_STAT & 0x7FFUL) != 0x100);
#endif
}

void pm_soc_disable_pd4_sram()
{
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for these families */
#else
    /* Disable PD4 */
    AONSEC->PD4_PWR_CTRL &= ~(1U << 12);

    /* PD4 PWR STAT Value */
    while((AONSEC->PD4_PWR_STAT & 0x7FFUL) == 0x100);
#endif
}
