#include "soc_aon.h"
#include "soc_vbat.h"
#include "drv_counter.h"
#include "drv_mcupll.h"

#define SE_CGU_OSC_CTRL     0x1A602000
#define SE_CGU_PLL_LOCK     0x1A602004
#define SE_CGU_PLL_SEL      0x1A602008
#define SE_CGU_ESCLK_SEL    0x1A602010
#define SE_ANATOP_REG1      0x1A604034
#define SE_XO_REG1          0x1A605020
#define SE_MCU_CLKPLL_REG1  0x1A605024
#define SE_MCU_CLKPLL_REG2  0x1A605028
#define SE_MCU_CLKPLL_REG3  0x1A60502C

static void OSC_xtal_start(bool faststart, bool boost)
{
    /* Enable bandgap */
    AONALL->ANATOP_REG1 = 0x11;

    uint32_t xo_reg1_default = 0x11D08439;
    uint32_t val = xo_reg1_default;
    if (faststart)  val |= 1U << 1;
    if (boost)      val |= 1U << 6;

    /* Enable HFXO */
    AONSEC->XO_REG1 = val;
    delay_us_refclk(600);

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
        while(1);
        break;
    }

    /* set fast start bit if needed */
    if (faststart) reg1_val |= 1U << 30;

    /* apply initial config to PLL, optionally add faststart */
    AONSEC->MCUPLL_REG1 = reg1_val;
    AONSEC->MCUPLL_REG2 = reg2_val;
    delay_us_refclk(15);

    /* release reset to PLL, wait to settle */
    reg1_val |=  (1U << 31);
    AONSEC->MCUPLL_REG1 = reg1_val;
    delay_us_refclk(45);

    /* clear fast start bit if needed */
    if (faststart) {
        reg1_val &= ~(1U << 30);
        AONSEC->MCUPLL_REG1 = reg1_val;
    }

    /* reset clock outputs */
    *(volatile uint32_t *)0x1A602014 |= (1U << 18);
    *(volatile uint32_t *)0x1A602014 &= ~(1U << 18);
}

static void PLL_clkpll_start_e1c(bool faststart)
{
    /* reg1_val = integer | (fractional) */
    uint32_t reg1_val = 0x19 << 20;
    uint32_t reg2_val = 0x84967BFE | (1U << 24);

    /* set fast start bit if needed */
    if (faststart) {
        reg1_val |= 1U << 30;
    }

    /* apply initial config to PLL, optionally add faststart */
    AONSEC->MCUPLL_REG1 = reg1_val;
    AONSEC->MCUPLL_REG2 = reg2_val;
    delay_us_refclk(15);

    /* release reset to PLL, wait to settle */
    reg1_val |=  (1U << 31);
    AONSEC->MCUPLL_REG1 = reg1_val;
    delay_us_refclk(45);

    /* clear fast start bit if needed */
    if (faststart) {
        reg1_val &= ~(1U << 30);
        AONSEC->MCUPLL_REG1 = reg1_val;
    }
}

static void PLL_clkpll_start_e4(uint32_t xtal_freq, bool faststart)
{
    /* reg1_val = integer | (fractional) */
    uint32_t reg1_val = 0;
    uint32_t reg2_val = 0x2C8269FE;

    switch(xtal_freq) {
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
        while(1);
        break;
    }

    /* set fast start bit if needed */
    if (faststart) {
        reg1_val |= 1U << 30;
    }

    /* apply initial config to PLL, optionally add faststart */
    AONSEC->MCUPLL_REG1 = reg1_val;
    AONSEC->MCUPLL_REG2 = reg2_val;
    delay_us_refclk(15);

    /* release reset to PLL, wait to settle */
    reg1_val |=  (1U << 31);
    AONSEC->MCUPLL_REG1 = reg1_val;
    delay_us_refclk(45);

    /* clear fast start bit if needed */
    if (faststart) {
        reg1_val &= ~(1U << 30);
        AONSEC->MCUPLL_REG1 = reg1_val;
    }

    /* reset clock outputs */
    CGU->CLK_ENA |= (1U << 18);
    CGU->CLK_ENA &= ~(1U << 18);
}

void PLL_clkpll_start(uint32_t xtal_freq, bool faststart)
{
    /* check PLL LOCK bit */
    if ((CGU->PLL_LOCK_CTRL & 1) == 1) return;
    if ((AONSEC->XO_REG1 & 1) == 0) return;

#if defined(ENSEMBLE_SOC_GEN2)
    PLL_clkpll_start_e4(xtal_freq, faststart);
#elif defined(ENSEMBLE_SOC_E1C)
    PLL_clkpll_start_e1c(faststart);
#else
    PLL_clkpll_start_e3(xtal_freq, faststart);
#endif

    /* set PLL LOCK bit */
    CGU->PLL_LOCK_CTRL = 1;
}

void PLL_clkpll_stop()
{
    /* clear PLL LOCK bit */
    CGU->PLL_LOCK_CTRL = 0;

    AONSEC->MCUPLL_REG1 = 0;
    AONSEC->MCUPLL_REG2 = 0;
    AONSEC->MCUPLL_REG3 = 0;
}

void OSC_initialize()
{
    OSC_xtal_start(true, true);
}

void OSC_uninitialize()
{
    OSC_xtal_stop();
}

void PLL_initialize(uint32_t xtal_freq)
{
    OSC_xtal_start(true, true);
    PLL_clkpll_start(xtal_freq, true);
}

void PLL_uninitialize()
{
    PLL_clkpll_stop();
}
