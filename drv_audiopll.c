#include "soc_aon.h"
#include "soc_vbat.h"
#include "drv_mcupll.h"
#include "drv_audiopll.h"

/* for sys_busy_loop_us() function */
#include "sys_utils.h"

bool AUDIOPLL_enabled()
{
    /* check if the PLL reset is released */
    return ((AONSEC->AUDIOPLL_REG1 >> 31) & 1);
}

static void AUDIOPLL_clkpll_start(uint32_t xtal_freq, bool faststart)
{
    /* check PLL LOCK bit */
    if (AUDIOPLL_enabled()) return;
    if ((AONSEC->XO_REG1 & 1) == 0) return;

    /* reg1_val = integer | (fractional) */
    uint32_t reg1_val = 0;
    uint32_t reg2_val = 0x54A615FE;

    switch(xtal_freq) {
    case 48000000:
        reg1_val |= 0x6 << 20 | 0x66666;
        break;
    case 40000000:
        reg1_val |= 0x7 << 20 | 0xAE147;
        break;
    case 38400000:
        reg1_val |= 0x8 << 20;
        break;
    case 32000000:
        reg1_val |= 0x9 << 20 | 0x99999;
        break;
    case 30000000:
        reg1_val |= 0xA << 20 | 0x3D70A;
        break;
    case 25000000:
        reg1_val |= 0xC << 20 | 0x80000;
        break;
    case 24000000:
        reg1_val |= 0xC << 20 | 0xCCCCC;
        break;
    case 20000000:
        reg1_val |= 0xF << 20 | 0x5C28F;
        break;
    case 19200000:
        reg1_val |= 0x10 << 20;
        break;
    default:
        return;
    }

    /* set fast start bit if needed */
    if (faststart) {
        reg1_val |= 1U << 30;
    }

    /* apply initial config to PLL, optionally add faststart */
    AONSEC->AUDIOPLL_REG1 = reg1_val;
    AONSEC->AUDIOPLL_REG2 = reg2_val;
    AONSEC->AUDIOPLL_REG3 = 0x08024000;
    sys_busy_loop_us(15);

    /* release reset to PLL, wait to settle */
    reg1_val |=  (1U << 31);
    AONSEC->AUDIOPLL_REG1 = reg1_val;
    sys_busy_loop_us(45);

    /* clear fast start bit if needed */
    if (faststart) {
        reg1_val &= ~(1U << 30);
        AONSEC->AUDIOPLL_REG1 = reg1_val;
    }
}

static void AUDIOPLL_clkpll_stop()
{
    AONSEC->AUDIOPLL_REG1 = 0;
    AONSEC->AUDIOPLL_REG2 = 0;
    AONSEC->AUDIOPLL_REG3 = 0;
}

/* be sure to update the SystemREFClock variable,
 * to use this AUDIOPLL clock you must set the 
 * clk_sel bit in I2Sx_CTRL to 1, or set the
 * pdm_cksel bit in EXPSLV0_CTRL to 1 */
void AUDIOPLL_initialize(uint32_t xtal_freq)
{
    AUDIOPLL_clkpll_start(xtal_freq, true);
    VBATSEC2->SEL_AUDIO_PLL = 1;
}

void AUDIOPLL_uninitialize()
{
    VBATSEC2->SEL_AUDIO_PLL = 0;
    AUDIOPLL_clkpll_stop();
}
