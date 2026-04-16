#include "soc_aon.h"
#include "soc_vbat.h"
#include "drv_mcupll.h"

/* for sys_busy_loop_us() function */
#include "sys_utils.h"

static void OSC_xtal_start(bool faststart, bool boost)
{
    if ((AONSEC->XO_REG1 & 1) == 1) return;

    /* Enable bandgap */
    AONALL->ANATOP_REG1 = 0x11;

    uint32_t xo_reg1_default = 0x11D08439;
    uint32_t val = xo_reg1_default;
    if (faststart)  val |= 1U << 1;
    if (boost)      val |= 1U << 6;

    /* Enable HFXO */
    AONSEC->XO_REG1 = val;
    sys_busy_loop_us(600);

    AONSEC->XO_REG1 = xo_reg1_default;
}

static void OSC_xtal_stop()
{
    AONSEC->XO_REG1 = 0;
    AONALL->ANATOP_REG1 = 0;
}

static void PLL_clkpll_start_e3(uint32_t xtal_freq, bool faststart)
{
    uint32_t reg1_val = 0;
    uint32_t reg2_val = 0xFC4A1FFE;

    switch(xtal_freq) {
    case 48000000:
        reg1_val |= 0x64 << 20;
        reg2_val |= 1U << 24;
        break;
    case 40000000:
        reg1_val |= 0x78 << 20;
        reg2_val |= 1U << 24;
        break;
    case 38400000:
        reg1_val |= 0x7D << 20;
        reg2_val |= 1U << 24;
        break;
    case 32000000:
        reg1_val |= 0x4B << 20;
        break;
    case 30000000:
        reg1_val |= 0x50 << 20;
        break;
    case 25000000:
        reg1_val |= 0x60 << 20;
        break;
    case 24000000:
        reg1_val |= 0x64 << 20;
        break;
    case 20000000:
        reg1_val |= 0x78 << 20;
        break;
    case 19200000:
        reg1_val |= 0x7D << 20;
        break;
    default:
        return;
    }

    /* set fast start bit if needed */
    if (faststart) reg1_val |= 1U << 30;

    /* apply initial config to PLL, optionally add faststart */
    AONSEC->MCUPLL_REG1 = reg1_val;
    AONSEC->MCUPLL_REG2 = reg2_val;
    AONSEC->MCUPLL_REG3 = 0x28018000;
    sys_busy_loop_us(15);

    /* release reset to PLL, wait to settle */
    reg1_val |=  (1U << 31);
    AONSEC->MCUPLL_REG1 = reg1_val;
    sys_busy_loop_us(45);

    /* clear fast start bit if needed */
    if (faststart) {
        reg1_val &= ~(1U << 30);
        AONSEC->MCUPLL_REG1 = reg1_val;
    }

    /* reset clock outputs */
    CGU->CLK_ENA |= (1U << 18);
    CGU->CLK_ENA &= ~(1U << 18);

    /* set PLL LOCK bit */
    CGU->PLL_LOCK_CTRL = 1;
}

static void PLL_clkpll_start_e1c(uint32_t xtal_freq, bool faststart)
{
    /* reg1_val = integer | (fractional) */
    uint32_t reg1_val = 0;
    uint32_t reg2_val = 0x84967BFE;

    switch(xtal_freq) {
    case 48000000:
        reg1_val |= 0x14 << 20;
        reg2_val |= 1U << 24;
        break;
    case 40000000:
        reg1_val |= 0x18 << 20;
        reg2_val |= 1U << 24;
        break;
    case 38400000:
        reg1_val |= 0x19 << 20;
        reg2_val |= 1U << 24;
        break;
    case 32000000:
        reg1_val |= 0x1E << 20;
        reg2_val |= 1U << 24;
        break;
    case 30000000:
        reg1_val |= 0x10 << 20;
        break;
    case 25000000:
        reg1_val |= 0x13 << 20 | 0x33333;
        break;
    case 24000000:
        reg1_val |= 0x14 << 20;
        break;
    case 20000000:
        reg1_val |= 0x18 << 20;
        break;
    case 19200000:
        reg1_val |= 0x19 << 20;
        break;
    default:
        return;
    }

    /* set fast start bit if needed */
    if (faststart) {
        reg1_val |= 1U << 30;
    }

    /* apply initial config to PLL, optionally add faststart */
    AONSEC->MCUPLL_REG1 = reg1_val;
    AONSEC->MCUPLL_REG2 = reg2_val;
    AONSEC->MCUPLL_REG3 = 0x08024000;
    sys_busy_loop_us(15);

    /* release reset to PLL, wait to settle */
    reg1_val |=  (1U << 31);
    AONSEC->MCUPLL_REG1 = reg1_val;
    sys_busy_loop_us(45);

    /* clear fast start bit if needed */
    if (faststart) {
        reg1_val &= ~(1U << 30);
        AONSEC->MCUPLL_REG1 = reg1_val;
    }

    /* set PLL LOCK bit */
    CGU->PLL_LOCK_CTRL = 1;
}

static void PLL_clkpll_start_e4(uint32_t xtal_freq, bool faststart)
{
    /* reg1_val = integer | (fractional) */
    uint32_t reg1_val = 0;
    uint32_t reg2_val = 0x2C8269FE;

    switch(xtal_freq) {
    case 48000000:
        reg1_val |= 0x21 << 20 | 0x55555;
        reg2_val |= 1U << 24;
        break;
    case 40000000:
        reg1_val |= 0x28 << 20;
        reg2_val |= 1U << 24;
        break;
    case 38400000:
        reg1_val |= 0x29 << 20 | 0xAAAAA;
        reg2_val |= 1U << 24;
        break;
    case 32000000:
        reg1_val |= 0x32 << 20;
        reg2_val |= 1U << 24;
        break;
    case 30000000:
        reg1_val |= 0x1A << 20 | 0xAAAAA;
        break;
    case 25000000:
        reg1_val |= 0x20 << 20;
        break;
    case 24000000:
        reg1_val |= 0x21 << 20 | 0x55555;
        break;
    case 20000000:
        reg1_val |= 0x28 << 20;
        break;
    case 19200000:
        reg1_val |= 0x29 << 20 | 0xAAAAA;
        break;
    default:
        return;
    }

    /* set fast start bit if needed */
    if (faststart) {
        reg1_val |= 1U << 30;
    }

    /* apply initial config to PLL, optionally add faststart */
    AONSEC->MCUPLL_REG1 = reg1_val;
    AONSEC->MCUPLL_REG2 = reg2_val;
    AONSEC->MCUPLL_REG3 = 0x08038000;
    sys_busy_loop_us(15);

    /* release reset to PLL, wait to settle */
    reg1_val |=  (1U << 31);
    AONSEC->MCUPLL_REG1 = reg1_val;
    sys_busy_loop_us(45);

    /* clear fast start bit if needed */
    if (faststart) {
        reg1_val &= ~(1U << 30);
        AONSEC->MCUPLL_REG1 = reg1_val;
    }

    /* reset clock outputs */
    CGU->CLK_ENA |= (1U << 18);
    CGU->CLK_ENA &= ~(1U << 18);

    /* set PLL LOCK bit */
    CGU->PLL_LOCK_CTRL = 1;
}

static void PLL_clkpll_start(uint32_t xtal_freq, bool faststart)
{
    /* check PLL LOCK bit */
    if ((CGU->PLL_LOCK_CTRL & 1) == 1) return;
    if ((AONSEC->XO_REG1 & 1) == 0) return;

#if defined(ENSEMBLE_SOC_GEN2)
    PLL_clkpll_start_e4(xtal_freq, faststart);
#elif defined(ENSEMBLE_SOC_E1C)
    PLL_clkpll_start_e1c(xtal_freq, faststart);
#else
    PLL_clkpll_start_e3(xtal_freq, faststart);
#endif
}

static void PLL_clkpll_stop()
{
    /* clear PLL LOCK bit */
    CGU->PLL_LOCK_CTRL = 0;

    AONSEC->MCUPLL_REG1 = 0;
    AONSEC->MCUPLL_REG2 = 0;
    AONSEC->MCUPLL_REG3 = 0;
}

bool OSC_enabled()
{
    return ((AONSEC->XO_REG1 & 1) == 1);
}

/* be sure to update the SystemREFClock variable */
void OSC_initialize()
{
    OSC_xtal_start(true, true);
}

void OSC_uninitialize()
{
    OSC_xtal_stop();
}

bool PLL_enabled()
{
    return ((CGU->PLL_LOCK_CTRL & 1) == 1);
}

/* be sure to update the SystemREFClock variable */
void PLL_initialize(uint32_t xtal_freq)
{
    OSC_xtal_start(true, true);
    PLL_clkpll_start(xtal_freq, true);
}

void PLL_uninitialize()
{
    PLL_clkpll_stop();
}
