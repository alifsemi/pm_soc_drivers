#include "drv_cgu.h"
#include "soc_aon.h"
#include "soc_vbat.h"
#include "soc_hostbase.h"
#include "pm_soc_pwr.h"

/* for sys_busy_loop_us() function */
#include "sys_utils.h"

/* for CGU_Type */
#include "soc.h"

#define PD6_ENABLE_SRAM_DELAY_TIME_US 60

static uint32_t dcdc_default_trim = 0;

void pm_soc_set_dcdc_pfm(void) {
#if defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for this family */
#else
    VBATSEC->DCDC_REG2 |= (VBATSEC_DCDC_REG2_DCDC_PFM_EN_Msk);
#endif
}

void pm_soc_set_dcdc_pwm(void) {
#if defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for this family */
#else
    VBATSEC->DCDC_REG2 &= ~(VBATSEC_DCDC_REG2_DCDC_PFM_EN_Msk);
#endif
}

/* Alif SoCs typically default to 825mV on the DCDC converter output.
 * Before calling pm_soc_set_dcdc_voltage(), use pm_soc_set_dcdc_default_trim() to set 
 * the default trim value which corresponds to 825mV on the DCDC converter.
 * This is required to ensure that the DCDC converter operates correctly within the specified voltage range.
 */
void pm_soc_set_dcdc_default_trim(uint32_t trim_val) {
    dcdc_default_trim = trim_val;
}

void pm_soc_set_dcdc_voltage(uint32_t millivolts) {
    if ((millivolts < 700) || (millivolts > 850)) {
        return; /* out of range */
    }
    if (dcdc_default_trim == 0) {
        return; /* default trim value not set */
    }
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    int32_t trim_val = millivolts;
    trim_val -= 825;
    trim_val /= 8;
    trim_val += dcdc_default_trim;

    if ((trim_val < 0) || (trim_val > 63)) {
        return; /* calculated trim value is out of range */
    }

    uint32_t dcdc_reg1_val = VBATSEC->DCDC_REG1;
    dcdc_reg1_val &= ~(VBATSEC_DCDC_REG1_DCDC_TRIM_VOUT_Msk);
    dcdc_reg1_val |= trim_val << VBATSEC_DCDC_REG1_DCDC_TRIM_VOUT_Pos;
    VBATSEC->DCDC_REG1 = dcdc_reg1_val;
#endif
}

void pm_soc_enable_syst_sram(uint32_t sram_select)
{
#if defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for this family */
#else
    uint32_t mask, reg_data;
    reg_data = CGU->CLK_ENA;

    /* SRAM0 clock enable */
    if (sram_select & PD6_ENABLE_SRAM0) {
        reg_data |= (CGU_CLK_ENA_SRAM0);
    } else {
        reg_data &= ~(CGU_CLK_ENA_SRAM0);
    }

    /* SRAM1 clock enable */
    if (sram_select & PD6_ENABLE_SRAM1) {
        reg_data |= (CGU_CLK_ENA_SRAM1);
    } else {
        reg_data &= ~(CGU_CLK_ENA_SRAM1);
    }

    CGU->CLK_ENA = reg_data;

    reg_data = VBATSEC->PWR_CTRL;

    /* SRAM0 power mask */
    mask = VBATSEC_PWR_CTRL_SRAM0_ISO_Msk | VBATSEC_PWR_CTRL_SRAM0_PWR_MASK_Msk;
    if (sram_select & PD6_ENABLE_SRAM0) {
        reg_data &= ~(mask);
    } else {
        reg_data |= (mask);
    }

    /* SRAM1 power mask */
    mask = VBATSEC_PWR_CTRL_SRAM1_ISO_Msk | VBATSEC_PWR_CTRL_SRAM1_PWR_MASK_Msk;
    if (sram_select & PD6_ENABLE_SRAM1) {
        reg_data &= ~(mask);
    } else {
        reg_data |= (mask);
    }

    VBATSEC->PWR_CTRL = reg_data;

    /* TBD - replace with "BISR Done" Status */
    if (sram_select) {
        sys_busy_loop_us(PD6_ENABLE_SRAM_DELAY_TIME_US);
    }
#endif
}

void pm_soc_retain_rtss_he_tcm(uint32_t retention_select)
{
#if defined(ENSEMBLE_SOC_E1C)
    uint32_t mask, reg_data;
    mask = VBATALL_RET_CTRL_HETCM_RET1_EN_Msk | VBATALL_RET_CTRL_HETCM_RET2_EN_Msk | \
           VBATALL_RET_CTRL_HETCM_RET3_EN_Msk | VBATALL_RET_CTRL_HETCM_RET4_EN_Msk | \
           VBATALL_RET_CTRL_HETCM_RET5_EN_Msk | VBATALL_RET_CTRL_HETCM_RET6_EN_Msk;
    reg_data = VBATALL->RET_CTRL;

    /* HW polarity: 1=retain (matches the macro bits directly) */
    reg_data &= ~(mask); /* clear retention bits 1..6 (no retention by default) */
    reg_data |= (retention_select & mask); /* set bits for TCM blocks to retain */
    VBATALL->RET_CTRL = reg_data;
#else
    uint32_t mask, reg_data;
    mask = VBATALL_RET_CTRL_HETCM_RET1_MASK_Msk | VBATALL_RET_CTRL_HETCM_RET1_FORCE_Msk | \
           VBATALL_RET_CTRL_HETCM_RET2_MASK_Msk | VBATALL_RET_CTRL_HETCM_RET2_FORCE_Msk;
    reg_data = VBATALL->RET_CTRL;

    /* HW polarity: 0=retain (function inverts the caller's mask) */
    reg_data |= mask; /* set retention bits 4..7 (no retention by default) */
    reg_data &= ~(retention_select & mask); /* clear bits for TCM blocks to retain */
    VBATALL->RET_CTRL = reg_data;
#endif
}

void pm_soc_retain_syst_sram(uint32_t retention_select)
{
#if defined(ENSEMBLE_SOC_GEN2)
    uint32_t mask, reg_data;
    mask = VBATALL_RET_CTRL_SRAM0_RET1_MASK_Msk | VBATALL_RET_CTRL_SRAM0_RET1_FORCE_Msk | \
           VBATALL_RET_CTRL_SRAM0_RET2_MASK_Msk | VBATALL_RET_CTRL_SRAM0_RET2_FORCE_Msk | \
           VBATALL_RET_CTRL_SRAM0_RET3_MASK_Msk | VBATALL_RET_CTRL_SRAM0_RET3_FORCE_Msk | \
           VBATALL_RET_CTRL_SRAM0_RET4_MASK_Msk | VBATALL_RET_CTRL_SRAM0_RET4_FORCE_Msk | \
           VBATALL_RET_CTRL_SRAM1_RET_MASK_Msk | VBATALL_RET_CTRL_SRAM1_RET_FORCE_Msk;
    reg_data = VBATALL->RET_CTRL;

    /* HW polarity: 0=retain (function inverts the caller's mask) */
    reg_data |= mask; /* set retention bits 8..17 (no retention by default) */
    reg_data &= ~(retention_select & mask); /* clear bits for SRAM blocks to retain */
    VBATALL->RET_CTRL = reg_data;
#else
    return; /* only applicable for Ensemble E4/E6/E8 */
#endif
}

void pm_soc_enable_pd_syst()
{
    uint32_t mask = HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_FUNC_RET;
    HOSTBASE->BSYS_PWR_REQ |=  (mask);
}

void pm_soc_disable_pd_syst()
{
    uint32_t mask = HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_FUNC_RET |
                    HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_ON;
    HOSTBASE->BSYS_PWR_REQ &= ~(mask);
}

void pm_soc_enable_pd_debug()
{
    uint32_t mask = HOSTBASE_BSYS_PWR_REQ_DBGTOP_PWR_REQ_Msk;
    HOSTBASE->BSYS_PWR_REQ |=  (mask);
}

void pm_soc_disable_pd_debug()
{
    uint32_t mask = HOSTBASE_BSYS_PWR_REQ_DBGTOP_PWR_REQ_Msk;
    HOSTBASE->BSYS_PWR_REQ &= ~(mask);
}

void pm_soc_enable_pd_sram_aon(uint32_t retention_select)
{
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for these families */
#else
    /* Enable PD1 via VBATSEC PWR_CTRL regiser */
    VBATSEC->PWR_CTRL |= (VBATSEC_PWR_CTRL_PD1_PWR_CTRL_Msk);

    /* Enable Main SRAM Retention LDO
     * Note: shared between SE, HE, PD4 SRAMs */
    VBATSEC->VBAT_ANA_REG1 |= (VBATSEC_VBAT_ANA_REG1_RET_LDO_MAIN_EN_Msk);

    /* Enable PD4 SRAM Retention (optional) */
    uint32_t mask = VBATPD4_RET_CTRL_SRAM_RET1_FORCE_Msk | VBATPD4_RET_CTRL_SRAM_RET1_MASK_Msk | \
                    VBATPD4_RET_CTRL_SRAM_RET2_FORCE_Msk | VBATPD4_RET_CTRL_SRAM_RET2_MASK_Msk | \
                    VBATPD4_RET_CTRL_SRAM_RET3_FORCE_Msk | VBATPD4_RET_CTRL_SRAM_RET3_MASK_Msk | \
                    VBATPD4_RET_CTRL_SRAM_RSVD_FORCE_Msk | VBATPD4_RET_CTRL_SRAM_RSVD_MASK_Msk;
    retention_select = ~retention_select;
    VBATPD4->RET_CTRL = retention_select & mask;

    /* Disconnect PPU from M55-M[4] and M55-G[8]
     * Allows PD4 to turn on and off via functions:
     * pm_soc_enable_pd4_sram() / pm_soc_disable_pd4_sram() */
    VBATPD4->PWR_CTRL = VBATPD4_PWR_CTRL_PPU_BYPASS_Msk;

    /* PD4 PWR STAT Value */
    while((AONSEC->PD4_PWR_STAT & AONSEC_PD4_PWR_STAT_Msk) == AONSEC_PD4_PWR_STAT_PWR_OFF);
#endif
}

void pm_soc_disable_pd_sram_aon()
{
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for these families */
#else
    /* Disable PD1 via VBATSEC PWR_CTRL regiser */
    VBATSEC->PWR_CTRL &= ~(VBATSEC_PWR_CTRL_PD1_PWR_CTRL_Msk);

    /* Disable PD4 SRAM Retention */
    uint32_t mask = VBATPD4_RET_CTRL_SRAM_RET1_FORCE_Msk | VBATPD4_RET_CTRL_SRAM_RET1_MASK_Msk | \
                    VBATPD4_RET_CTRL_SRAM_RET2_FORCE_Msk | VBATPD4_RET_CTRL_SRAM_RET2_MASK_Msk | \
                    VBATPD4_RET_CTRL_SRAM_RET3_FORCE_Msk | VBATPD4_RET_CTRL_SRAM_RET3_MASK_Msk | \
                    VBATPD4_RET_CTRL_SRAM_RSVD_FORCE_Msk | VBATPD4_RET_CTRL_SRAM_RSVD_MASK_Msk;
    VBATPD4->RET_CTRL = mask;

    /* PD4 PWR STAT Value */
    while((AONSEC->PD4_PWR_STAT & AONSEC_PD4_PWR_STAT_Msk) != AONSEC_PD4_PWR_STAT_PWR_OFF);
#endif
}

void pm_soc_enable_pd4_sram(uint32_t clk_sel)
{
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for these families */
#else
    /* Switch PD4 between HFXO and PLL-160M clock */
    AONSEC->PD4_CLK_SEL = clk_sel ? AONSEC_PD4_CLK_SEL_Msk : 0;
    AONSEC->PD4_CLK_PLL = clk_sel ? AONSEC_PD4_CLK_PLL_Msk : 0;

    /* Enable PD4 */
    AONSEC->PD4_PWR_CTRL |= (AONSEC_PD4_PWR_CTRL_Msk);

    /* PD4 PWR STAT Value */
    while((AONSEC->PD4_PWR_STAT & AONSEC_PD4_PWR_STAT_Msk) != AONSEC_PD4_PWR_STAT_PWR_ON);
#endif
}

void pm_soc_disable_pd4_sram()
{
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    return; /* not applicable for these families */
#else
    /* Disable PD4 */
    AONSEC->PD4_PWR_CTRL &= ~(AONSEC_PD4_PWR_CTRL_Msk);

    /* PD4 PWR STAT Value */
    while((AONSEC->PD4_PWR_STAT & AONSEC_PD4_PWR_STAT_Msk) == AONSEC_PD4_PWR_STAT_PWR_ON);
#endif
}
