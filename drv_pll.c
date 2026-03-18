#include <stdint.h>
#include "drv_counter.h"
#include "drv_pll.h"

#ifndef HW_REG32
#define HW_REG32(u,v) (*((volatile uint32_t *)(u + v)))
#endif

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
    HW_REG32(SE_ANATOP_REG1, 0) = 0x11;

    uint32_t xo_reg1_default = 0x11D08439;
    uint32_t val = xo_reg1_default;
    if (faststart)  val |= 1U << 1;
    if (boost)      val |= 1U << 6;

    /* Enable HFXO */
    HW_REG32(SE_XO_REG1, 0) = val;
    delay_us_refclk(600);

    HW_REG32(SE_XO_REG1, 0) = xo_reg1_default;
}

static void OSC_xtal_stop()
{
    HW_REG32(SE_XO_REG1, 0) = 0;
    HW_REG32(SE_ANATOP_REG1, 0) = 0;
}

static void PLL_clkpll_start_bolt(uint32_t xtal_freq, bool faststart)
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
    HW_REG32(SE_MCU_CLKPLL_REG1, 0) = reg1_val;
    HW_REG32(SE_MCU_CLKPLL_REG2, 0) = reg2_val;
    delay_us_refclk(15);

    /* release reset to PLL, wait to settle */
    reg1_val |=  (1U << 31);
    HW_REG32(SE_MCU_CLKPLL_REG1, 0) = reg1_val;
    delay_us_refclk(45);

    /* clear fast start bit if needed */
    if (faststart) {
        reg1_val &= ~(1U << 30);
        HW_REG32(SE_MCU_CLKPLL_REG1, 0) = reg1_val;
    }

    /* reset clock outputs */
    *(volatile uint32_t *)0x1A602014 |= (1U << 18);
    *(volatile uint32_t *)0x1A602014 &= ~(1U << 18);
}

static void PLL_clkpll_start_spark(bool faststart)
{
    uint32_t reg1_val = 0x19 << 20;
    uint32_t reg2_val = 0x84967BFE | (1U << 24);

    /* set fast start bit if needed */
    if (faststart) {
        reg1_val |= 1U << 30;
    }

    /* apply initial config to PLL, optionally add faststart */
    HW_REG32(SE_MCU_CLKPLL_REG1, 0) = reg1_val;
    HW_REG32(SE_MCU_CLKPLL_REG2, 0) = reg2_val;
    delay_us_refclk(15);

    /* release reset to PLL, wait to settle */
    reg1_val |=  (1U << 31);
    HW_REG32(SE_MCU_CLKPLL_REG1, 0) = reg1_val;
    delay_us_refclk(45);

    /* clear fast start bit if needed */
    if (faststart) {
        reg1_val &= ~(1U << 30);
        HW_REG32(SE_MCU_CLKPLL_REG1, 0) = reg1_val;
    }
}

static void PLL_clkpll_start_eagle(bool faststart)
{
    /* reg1_val = integer | (fractional) */
    uint32_t reg1_val = 0x29 << 20 | (0xAAAAA);
    uint32_t reg2_val = 0x2C8269FE | (1U << 24);

    /* set fast start bit if needed */
    if (faststart) {
        reg1_val |= 1U << 30;
    }

    /* apply initial config to PLL, optionally add faststart */
    HW_REG32(SE_MCU_CLKPLL_REG1, 0) = reg1_val;
    HW_REG32(SE_MCU_CLKPLL_REG2, 0) = reg2_val;
    delay_us_refclk(15);

    /* release reset to PLL, wait to settle */
    reg1_val |=  (1U << 31);
    HW_REG32(SE_MCU_CLKPLL_REG1, 0) = reg1_val;
    delay_us_refclk(45);

    /* clear fast start bit if needed */
    if (faststart) {
        reg1_val &= ~(1U << 30);
        HW_REG32(SE_MCU_CLKPLL_REG1, 0) = reg1_val;
    }

    /* reset clock outputs */
    *(volatile uint32_t *)0x1A602014 |= (1U << 18);
    *(volatile uint32_t *)0x1A602014 &= ~(1U << 18);
}

void PLL_clkpll_start(uint32_t xtal_freq, bool faststart)
{
    /* check PLL LOCK bit */
    if ((HW_REG32(SE_CGU_PLL_LOCK, 0) & 1) == 1) return;
    if ((HW_REG32(SE_XO_REG1, 0) & 1) == 0) return;

#if defined(ENSEMBLE_SOC_GEN2)
        PLL_clkpll_start_eagle(faststart);
#elif defined(ENSEMBLE_SOC_E1C)
        PLL_clkpll_start_spark(faststart);
#else
        PLL_clkpll_start_bolt(xtal_freq, faststart);
#endif

    /* set PLL LOCK bit */
    HW_REG32(SE_CGU_PLL_LOCK, 0) = 1;
}

void PLL_clkpll_stop()
{
    /* clear PLL LOCK bit */
    HW_REG32(SE_CGU_PLL_LOCK, 0) = 0;

    HW_REG32(SE_MCU_CLKPLL_REG1, 0) = 0;
    HW_REG32(SE_MCU_CLKPLL_REG2, 0) = 0;
    HW_REG32(SE_MCU_CLKPLL_REG3, 0) = 0;
}

void OSC_rc_to_xtal()
{
    /* CGU Registers */
    /* OSC Control Register (0x00)
     * sys_xtal_sel[0] 0: 76.8M HFRC/X, 1: 38.4M HFXO/Z (bolt)
     * sys_xtal_sel[0] 0: 76.8M HFRC/X, 1: 76.8M HFXOx2 (eagle/spark)
     * SYS_REFCLK, SYSPLL, CPUPLL
     *
     * periph_xtal_sel[4] 0: 38.4M HFRC/X/2, 1: 38.4M HFXO/Z
     * SYS_UART, MRAM_EFUSE, I2S, CAN_FD, MIPI
     *
     * clkmon_ena[16] 0: disable 1: enable HFXO clock monitor
     * xtal_dead[20] read-only status of HFXO clock monitor
     */
    HW_REG32(SE_CGU_OSC_CTRL, 0) |= 0x11;

    /* ESCLK Select Register (0x10)
     * es0_pll_sel[1:0]     0: 100M PLL, 1: 200M PLL, 2: reserved, 3: 400M PLL
     * es1_pll_sel[5:4]     0: reserved, 1:  80M PLL, 2: reserved, 3: 160M PLL
     * es0_osc_sel[9:8]     0: 76.8M HFRC, 1: 38.4M HFRC, 2: 76.8M HFXO, 3: 38.4M HFXO
     * es1_osc_sel[13:12]   0: 76.8M HFRC, 1: 38.4M HFRC, 2: 76.8M HFXO, 3: 38.4M HFXO
     */
    HW_REG32(SE_CGU_ESCLK_SEL, 0) = 0x2233;
}

void OSC_xtal_to_rc()
{
    /* Switch to HFRC from HFXO */
    HW_REG32(SE_CGU_OSC_CTRL, 0) = 0;
    HW_REG32(SE_CGU_ESCLK_SEL, 0) = 0;
}

static void PLL_clock_mux_select(uint32_t mux_select)
{
    /* Switch from non-PLL to PLL clock
     *  osc_mix_clk is result of sys_xtal_sel bit
     *  osc_9p6M_clk is result of periph_xtal_sel bit
     *  ESx OSC clk is result of esX_osc_sel bits
     *  ESx PLL clk is result of esX_pll_sel bits
     *
     *  REFCLK[0] - osc_mix_clk  or PLL_100M
     *  SYS[4]    - osc_mix_clk  or PLL_400M (AXI)
     *  ES0[16]   - HFRC/HFXO or PLL
     *  ES1[20]   - HFRC/HFXO or PLL
     */
    if (mux_select) {
        HW_REG32(SE_CGU_PLL_SEL, 0) = 0x110011;
    }
    else {
        HW_REG32(SE_CGU_PLL_SEL, 0) = 0;
    }
}

void OSC_initialize()
{
    OSC_xtal_start(true, true);
    OSC_rc_to_xtal();
}

void OSC_uninitialize()
{
    OSC_xtal_to_rc();
    OSC_xtal_stop();
}

void PLL_initialize(uint32_t xtal_freq)
{
    OSC_xtal_start(true, true);
    PLL_clkpll_start(xtal_freq, true);

    OSC_rc_to_xtal();
    PLL_clock_mux_select(1);
}

void PLL_uninitialize()
{
    PLL_clock_mux_select(0);
    PLL_clkpll_stop();
}
