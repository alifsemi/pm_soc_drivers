#include <stdint.h>

#define SYST_SRAM0_EN 1
#define SYST_SRAM1_EN 2

/* ENSEMBLE_SOC_GEN1 only */
#define PD4_CLK_HFXO        0
#define PD4_CLK_PLL160M     1
#define PD4_RETAIN_1024KB   (3U << 4)
#define PD4_RETAIN_1280KB   ((3U << 8) | PD4_RETAIN_1024KB)
#define PD4_RETAIN_1536KB   ((3U << 12)| PD4_RETAIN_1280KB)

/* ENSEMBLE_SOC_GEN2 only */
#define PD6_RETAIN_SRAM0_512KB      (3U << 8)
#define PD6_RETAIN_SRAM0_1024KB     ((3U << 10) | PD6_RETAIN_SRAM0_512KB)
#define PD6_RETAIN_SRAM0_2048KB     ((3U << 12) | PD6_RETAIN_SRAM0_1024KB)
#define PD6_RETAIN_SRAM0_4096KB     ((3U << 14) | PD6_RETAIN_SRAM0_2048KB)
#define PD6_RETAIN_SRAM1_4096KB     (3U << 16)

/* Power Management Functions */

/* Adjustments for the internal DCDC converter */
void pm_soc_set_dcdc_pfm(void);
void pm_soc_set_dcdc_pwm(void);
void pm_soc_set_dcdc_default_trim(uint32_t trim_val);
void pm_soc_set_dcdc_voltage(uint32_t millivolts);

/* Power & Retention Controls for PD6 SRAMs (retention is optional) */

/* sram_select controls power and clock to the SRAMs when PD6 SYST is ON */
void pm_soc_enable_syst_sram(uint32_t sram_select);
/* retention_select controls retention power to the SRAMs when PD6 SYST is OFF */
void pm_soc_retain_syst_sram(uint32_t retention_select);

/* Power Domain Controls for PD6 SYST and PD8 DBSS */

void pm_soc_enable_pd_syst();
void pm_soc_disable_pd_syst();
void pm_soc_enable_pd_debug();
void pm_soc_disable_pd_debug();

/* Power Domain Controls for PD1 SRAM_AON and PD4 SRAM (retention is optional) */

/* retention_select controls retention power to the PD4 SRAMs when PD4 is OFF */
void pm_soc_enable_pd_sram_aon(uint32_t retention_select);
void pm_soc_disable_pd_sram_aon();
/* clk_sel controls the clock selection for PD4 SRAM */
void pm_soc_enable_pd4_sram(uint32_t clk_sel);
void pm_soc_disable_pd4_sram();
