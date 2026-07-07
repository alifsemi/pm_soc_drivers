#include "soc_hostbase.h"
#include "drv_counter.h"
#include "pm_soc_clk.h"

void refclk_cntr_init() {
    HOSTBASE->BSYS_PWR_REQ |= HOSTBASE_BSYS_PWR_REQ_REFCLK_REQ_Msk;
    *((volatile uint32_t *)0x1A200000) = 1;
    *((volatile uint32_t *)0x1A220000) = pm_soc_clk_get_refclk();
}

void refclk_cntr_update() {
    *((volatile uint32_t *)0x1A220000) = pm_soc_clk_get_refclk();
}

uint32_t refclk_cntr_freq() {
    return *((volatile uint32_t *)0x1A220000);
}

uint32_t refclk_cntr_val() {
    return *((volatile uint32_t *)0x1A210000);
}

uint64_t refclk_cntr_val64() {
    return *((volatile uint64_t *)0x1A210000);
}

void s32k_cntr_init() {
    *((volatile uint32_t *)0x1A400000) = 1;
    *((volatile uint32_t *)0x1A420000) = 32768;
}

uint32_t s32k_cntr_val() {
    return *((volatile uint32_t *)0x1A410000);
}

uint64_t s32k_cntr_val64() {
    return *((volatile uint64_t *)0x1A410000);
}

void delay_ms_s32k(uint32_t nticks) {
    uint64_t cntr_value = s32k_cntr_val64();
    cntr_value += ((uint64_t)nticks * 32768 + 500) / 1000;
    while (s32k_cntr_val64() < cntr_value);
}

void delay_us_s32k(uint32_t nticks) {
    uint64_t cntr_value = s32k_cntr_val64();
    cntr_value += ((uint64_t)nticks * 32768 + 500000) / 1000000;
    while (s32k_cntr_val64() < cntr_value);
}

void delay_us_refclk(uint32_t nticks) {
    uint64_t cntr_value = refclk_cntr_val64();
    uint64_t nticks64 = refclk_cntr_freq() * (uint64_t)nticks;
    cntr_value += (nticks64 + 500000) / 1000000;
    while (refclk_cntr_val64() < cntr_value);
}

void refclk_cntr_enable_cntbase(uint32_t cntbase) {
    if (cntbase > 3) return;
    *((volatile uint32_t *)(0x1A220040 + (0x4 * cntbase))) = 0x25;
    *((volatile uint32_t *)(0x1A23002C + (0x10000 * cntbase))) = 0;
}

void refclk_cntr_disable_cntbase(uint32_t cntbase) {
    if (cntbase > 3) return;
    *((volatile uint32_t *)(0x1A23002C + (0x10000 * cntbase))) = 0;
    *((volatile uint32_t *)(0x1A220040 + (0x4 * cntbase))) = 0;
}

void refclk_cntr_enable_cntbase_intr(uint32_t cntbase, uint64_t compare_val) {
    if (cntbase > 3) return;
    *((volatile uint64_t *)(0x1A230020 + (0x10000 * cntbase))) = compare_val;
    *((volatile uint32_t *)(0x1A23002C + (0x10000 * cntbase))) = 1;
}

void refclk_cntr_disable_cntbase_intr(uint32_t cntbase) {
    if (cntbase > 3) return;
    *((volatile uint32_t *)(0x1A23002C + (0x10000 * cntbase))) = 0;
}

void s32k_cntr_enable_cntbase(uint32_t cntbase) {
    if (cntbase > 1) return;
    *((volatile uint32_t *)(0x1A420040 + (0x4 * cntbase))) = 0x25;
    *((volatile uint32_t *)(0x1A43002C + (0x10000 * cntbase))) = 0;
}

void s32k_cntr_disable_cntbase(uint32_t cntbase) {
    if (cntbase > 1) return;
    *((volatile uint32_t *)(0x1A43002C + (0x10000 * cntbase))) = 0;
    *((volatile uint32_t *)(0x1A420040 + (0x4 * cntbase))) = 0;
}

void s32k_cntr_enable_cntbase_intr(uint32_t cntbase, uint64_t compare_val) {
    if (cntbase > 1) return;
    *((volatile uint64_t *)(0x1A430020 + (0x10000 * cntbase))) = compare_val;
    *((volatile uint32_t *)(0x1A43002C + (0x10000 * cntbase))) = 1;
}

void s32k_cntr_disable_cntbase_intr(uint32_t cntbase) {
    if (cntbase > 1) return;
    *((volatile uint32_t *)(0x1A43002C + (0x10000 * cntbase))) = 0;
    while (*((volatile uint32_t *)(0x1A43002C + (0x10000 * cntbase))) != 0);
}
