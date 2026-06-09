#include "soc_aon.h"
#include "soc_vbat.h"
#include "soc_hostbase.h"
#include "pm_soc_rst.h"

/* for SOC_FEAT_HP_ITCM_BASE and SOC_FEAT_HE_ITCM_BASE */
#include "soc_features.h"

int32_t pm_soc_reset_rtss_hp(uint32_t vtor_address)
{
#if !defined(ENSEMBLE_SOC_E1C)
    AONALL->RTSS_HP_CTRL = 0;
    AONSEC->CM55_HP_SE_VTOR = vtor_address;

    /* apply reset & M55 CPUWAIT */
    HOSTBASE->EXT_SYS0_RST_CTRL = 3;

    /* wait for reset acknowledge */
    uint32_t timeout = 1000;
    while ((HOSTBASE->EXT_SYS0_RST_ST != 4) && (timeout-- > 0));

    /* release reset, but keep M55 CPUWAIT */
    HOSTBASE->EXT_SYS0_RST_CTRL = 1;

    return timeout == 0 ? -1 : 0;
#else
    (void) vtor_address;
    return -1;
#endif
}

int32_t pm_soc_reset_rtss_he(uint32_t vtor_address)
{
    AONALL->RTSS_HE_CTRL = 0;
    VBATSEC->CM55_HE_SE_VTOR = vtor_address;

    /* apply reset & M55 CPUWAIT */
    HOSTBASE->EXT_SYS1_RST_CTRL = 3;

    /* wait for reset acknowledge */
    uint32_t timeout = 1000;
    while ((HOSTBASE->EXT_SYS1_RST_ST != 4) && (timeout-- > 0));

    /* release reset, but keep M55 CPUWAIT */
    HOSTBASE->EXT_SYS1_RST_CTRL = 1;

    return timeout == 0 ? -1 : 0;
}

int32_t pm_soc_boot_rtss_hp(void)
{
#if !defined(ENSEMBLE_SOC_E1C)
    if (HOSTBASE->EXT_SYS0_RST_CTRL == 0) {
        /* RTSS-HP is booted */
        return 0;
    }

    /* release M55 CPUWAIT */
    HOSTBASE->EXT_SYS0_RST_CTRL = 0;

    /* dummy read from RTSS-HP TCM to force clocks to start */
    (void) *((volatile uint32_t *) SOC_FEAT_HP_ITCM_BASE);

    return 0;
#else
    return -1;
#endif
}

int32_t pm_soc_boot_rtss_he(void)
{
    if (HOSTBASE->EXT_SYS1_RST_CTRL == 0) {
        /* RTSS-HE is booted */
        return 0;
    }

    /* release M55 CPUWAIT */
    HOSTBASE->EXT_SYS1_RST_CTRL = 0;

    /* dummy read from RTSS-HE TCM to force clocks to start */
    (void) *((volatile uint32_t *) SOC_FEAT_HE_ITCM_BASE);

    return 0;
}
