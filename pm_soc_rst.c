#include "soc.h"
#include "app_mem_regions.h"

#include "aon.h"
#include "hostbase.h"
#include "soc_rst.h"

void pm_soc_reset_rtss_hp(uint32_t vtor_address)
{
#if !defined(ENSEMBLE_SOC_E1C)
    AONALL->RTSS_HP_RESET = 0;
    AONSEC->CM55_HP_SE_VTOR = vtor_address;

    /* apply reset & M55 CPUWAIT */
    HOSTBASE->EXT_SYS0_RST_CTRL = 3;

    /* wait for reset acknowledge */
    uint32_t timeout = 1000;
    while ((HOSTBASE->EXT_SYS0_RST_ST != 4) && (timeout-- > 0));

    /* release reset, but keep M55 CPUWAIT */
    HOSTBASE->EXT_SYS0_RST_CTRL = 1;
#endif
}

void pm_soc_reset_rtss_he(uint32_t vtor_address)
{
    AONALL->RTSS_HE_RESET = 0;
    VBATSEC->CM55_HE_SE_VTOR = vtor_address;

    /* apply reset & M55 CPUWAIT */
    HOSTBASE->EXT_SYS1_RST_CTRL = 3;

    /* wait for reset acknowledge */
    uint32_t timeout = 1000;
    while ((HOSTBASE->EXT_SYS1_RST_ST != 4) && (timeout-- > 0));

    /* release reset, but keep M55 CPUWAIT */
    HOSTBASE->EXT_SYS1_RST_CTRL = 1;
}

void pm_soc_boot_rtss_hp()
{
#if !defined(ENSEMBLE_SOC_E1C)
    /* release M55 CPUWAIT */
    HOSTBASE->EXT_SYS0_RST_CTRL = 0;

    /* dummy read from RTSS-HP TCM to force clocks to start */
    (void) *((volatile uint32_t *) 0x50000000);
#endif
}

void pm_soc_boot_rtss_he()
{
    /* release M55 CPUWAIT */
    HOSTBASE->EXT_SYS1_RST_CTRL = 0;

    /* dummy read from RTSS-HE TCM to force clocks to start */
    (void) *((volatile uint32_t *) 0x58000000);
}
