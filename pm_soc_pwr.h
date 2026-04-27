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

/**
  @fn       void pm_soc_set_dcdc_pfm(void)
  @brief    Put the internal DCDC converter into PFM (pulse frequency
            modulation) mode, which favors efficiency at light loads.
            Refer to "DCDC_REG2 Register" in HWRM for more details.
  @note     Not applicable on ENSEMBLE_SOC_E1C; the call is a no-op.
  @return   None
*/
void pm_soc_set_dcdc_pfm(void);

/**
  @fn       void pm_soc_set_dcdc_pwm(void)
  @brief    Put the internal DCDC converter into PWM (pulse width
            modulation) mode, which favors regulation quality at higher
            loads.
            Refer to "DCDC_REG2 Register" in HWRM for more details.
  @note     Not applicable on ENSEMBLE_SOC_E1C; the call is a no-op.
  @return   None
*/
void pm_soc_set_dcdc_pwm(void);

/**
  @fn       void pm_soc_set_dcdc_default_trim(uint32_t trim_val)
  @brief    Record the DCDC trim value that corresponds to the factory
            default output voltage (typically 825mV). This must be called
            before pm_soc_set_dcdc_voltage(), which uses it as the reference
            point for relative trim adjustment.
  @param    trim_val    Trim code corresponding to the default 825mV output
  @return   None
*/
void pm_soc_set_dcdc_default_trim(uint32_t trim_val);

/**
  @fn       void pm_soc_set_dcdc_voltage(uint32_t millivolts)
  @brief    Adjust the internal DCDC converter output voltage by computing
            a new trim code relative to the stored default trim. The call
            is silently ignored if the target voltage is out of range, if
            the default trim has not been set, or if the computed trim is
            out of range.
            Refer to "DCDC_REG1 Register" in HWRM for more details.
  @note     Only applicable on ENSEMBLE_SOC_GEN2 and ENSEMBLE_SOC_E1C.
  @param    millivolts  Target output voltage in millivolts (valid range
                        700 to 850)
  @return   None
*/
void pm_soc_set_dcdc_voltage(uint32_t millivolts);

/* Power & Retention Controls for PD6 SRAMs (retention is optional) */

/**
  @fn       void pm_soc_enable_syst_sram(uint32_t sram_select)
  @brief    Enable power and clock to the selected PD6 SYST SRAM banks.
            Banks not selected have their clocks gated and their power
            masked off. Includes a short busy wait for BISR to complete.
            Refer to "CLK_ENA Register" and "PWR_CTRL Register" in HWRM
            for more details.
  @note     Not applicable on ENSEMBLE_SOC_E1C; the call is a no-op.
  @param    sram_select Bitmask of banks to enable: SYST_SRAM0_EN and/or
                        SYST_SRAM1_EN
  @return   None
*/
void pm_soc_enable_syst_sram(uint32_t sram_select);

/**
  @fn       void pm_soc_retain_syst_sram(uint32_t retention_select)
  @brief    Configure retention power for the PD6 SYST SRAM banks so that
            their contents survive while PD6 is powered off. Any banks not
            listed in retention_select are left without retention.
            Refer to "RET_CTRL Register" in HWRM for more details.
  @note     Only applicable on ENSEMBLE_SOC_GEN2 (Ensemble E4/E6/E8);
            the call is a no-op on other families.
  @param    retention_select    Bitmask of banks to retain (see macros for
                                PD6_RETAIN_SRAM0_* and PD6_RETAIN_SRAM1_* )
  @return   None
*/
void pm_soc_retain_syst_sram(uint32_t retention_select);

/* Power Domain Controls for PD6 SYST and PD8 DBSS */

/**
  @fn       void pm_soc_enable_pd_syst(void)
  @brief    Request that the PD6 SYST power domain be powered on.
            Refer to "BSYS_PWR_REQ Register" in HWRM for more details.
  @return   None
*/
void pm_soc_enable_pd_syst();

/**
  @fn       void pm_soc_disable_pd_syst(void)
  @brief    Release the request to keep the PD6 SYST power domain powered
            on, allowing it to turn off when no other consumer holds it up.
            Refer to "BSYS_PWR_REQ Register" in HWRM for more details.
  @return   None
*/
void pm_soc_disable_pd_syst();

/**
  @fn       void pm_soc_enable_pd_debug(void)
  @brief    Request that the PD8 DBSS debug subsystem power domain be
            powered on.
            Refer to "BSYS_PWR_REQ Register" in HWRM for more details.
  @return   None
*/
void pm_soc_enable_pd_debug();

/**
  @fn       void pm_soc_disable_pd_debug(void)
  @brief    Release the request to keep the PD8 DBSS debug subsystem power
            domain powered on, allowing it to turn off.
            Refer to "BSYS_PWR_REQ Register" in HWRM for more details.
  @return   None
*/
void pm_soc_disable_pd_debug();

/* Power Domain Controls for PD1 SRAM_AON and PD4 SRAM (retention is optional) */

/**
  @fn       void pm_soc_enable_pd_sram_aon(uint32_t retention_select)
  @brief    Enable PD1 SRAM_AON, bring up the main SRAM retention LDO,
            configure optional PD4 SRAM retention, and disconnect PD4 from
            the PPU so that pm_soc_enable_pd4_sram() /
            pm_soc_disable_pd4_sram() can manage it manually. Waits for
            PD4 to report a valid power status.
            Refer to "PWR_CTRL Register", "VBAT_ANA_REG1 Register" and
            "PD4_PWR_STAT Register" in HWRM for more details.
  @note     Only applicable on ENSEMBLE_SOC_GEN1; the call is a no-op on
            other families.
  @param    retention_select    Bitmask of PD4 SRAM blocks to retain (see
                                PD4_RETAIN_* macros)
  @return   None
*/
void pm_soc_enable_pd_sram_aon(uint32_t retention_select);

/**
  @fn       void pm_soc_disable_pd_sram_aon(void)
  @brief    Disable PD1 SRAM_AON, clear PD4 SRAM retention, and wait for
            PD4 to report powered off.
            Refer to "PWR_CTRL Register" and "PD4_PWR_STAT Register" in
            HWRM for more details.
  @note     Only applicable on ENSEMBLE_SOC_GEN1; the call is a no-op on
            other families.
  @return   None
*/
void pm_soc_disable_pd_sram_aon();

/**
  @fn       void pm_soc_enable_pd4_sram(uint32_t clk_sel)
  @brief    Power on the PD4 SRAM domain, using the selected clock source,
            and wait for PD4 to report powered on.
            Refer to "PD4_CLK_SEL Register", "PD4_CLK_PLL Register",
            "PD4_PWR_CTRL Register" and "PD4_PWR_STAT Register" in HWRM
            for more details.
  @note     Only applicable on ENSEMBLE_SOC_GEN1; the call is a no-op on
            other families.
  @param    clk_sel     Clock source: PD4_CLK_HFXO (0) selects HFXO,
                        PD4_CLK_PLL160M (1) selects the 160MHz PLL output
  @return   None
*/
void pm_soc_enable_pd4_sram(uint32_t clk_sel);

/**
  @fn       void pm_soc_disable_pd4_sram(void)
  @brief    Power off the PD4 SRAM domain and wait for it to report
            powered off.
            Refer to "PD4_PWR_CTRL Register" and "PD4_PWR_STAT Register"
            in HWRM for more details.
  @note     Only applicable on ENSEMBLE_SOC_GEN1; the call is a no-op on
            other families.
  @return   None
*/
void pm_soc_disable_pd4_sram();
