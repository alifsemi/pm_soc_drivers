#include <stdint.h>

/* PD0 Wakeup events */
#define WE_SERTC    (1 << 4)     // bit4
#define WE_LPRTC    (1 << 5)     // bit5
#define WE_LPCMP    (1 << 6)     // bit6
#define WE_BOD      (1 << 7)     // bit7
#define WE_LPTIMER0 (1 << 8)     // bit8
#define WE_LPTIMER1 (1 << 9)     // bit9
#define WE_LPTIMER2 (1 << 10)    // bit10
#define WE_LPTIMER3 (1 << 11)    // bit11
#define WE_LPGPIO0  (1 << 16)    // bit16
#define WE_LPGPIO1  (1 << 17)    // bit17
#define WE_LPGPIO2  (1 << 18)    // bit18
#define WE_LPGPIO3  (1 << 19)    // bit19
#define WE_LPGPIO4  (1 << 20)    // bit20
#define WE_LPGPIO5  (1 << 21)    // bit21
#define WE_LPGPIO6  (1 << 22)    // bit22
#define WE_LPGPIO7  (1 << 23)    // bit23

#define WE_LPTIMER  0xF00     // bit11:8
#define WE_LPGPIO   0xFF0000  // bit23:16

/**
  @fn       void pm_soc_reset_soc(void)
  @brief    Reset the entire SoC. TBD - there is currently no way to
            perform a full SoC reset from RTSS, so this function is a
            placeholder. Use SERVICES_boot_reset_soc() instead.
  @return   None
*/
void pm_soc_reset_soc();

/**
  @fn       void pm_soc_reset_apss(void)
  @brief    Reset the APSS (Cortex-A) subsystem. TBD - there is currently
            no way to perform an APSS reset from RTSS, so this function is
            a placeholder. Use SERVICES_boot_reset_soc() instead. Do not
            use SERVICES_boot_reset_cpu() to reset the APSS because this
            will also reset the RTSS and make the SoC unresponsive.
  @return   None
*/
void pm_soc_reset_apss();

/**
  @fn       int32_t pm_soc_reset_rtss_hp(uint32_t vtor_address)
  @brief    Reset the RTSS-HP (Cortex-M55 High Performance) subsystem.
            Programs the boot vector table address, asserts reset with
            CPUWAIT held, waits for the reset acknowledge, then releases
            reset while keeping CPUWAIT asserted. After this call, RTSS-HP
            is left in the OFF state; use pm_soc_boot_rtss_hp() to actually
            start the core.
            Refer to "RTSS_HP_CTRL Register", "CM55_HP_SE_VTOR Register",
            "EXT_SYS0_RST_CTRL Register" and "EXT_SYS0_RST_ST Register" in
            HWRM for more details.
  @note     Not applicable on ENSEMBLE_SOC_E1C; the call is a no-op.
  @param    vtor_address    Address where the RTSS-HP CPU will start
                            execution when booted
  @return   0 on success, -1 on reset timeout or if not applicable
*/
int32_t pm_soc_reset_rtss_hp(uint32_t vtor_address);

/**
  @fn       int32_t pm_soc_reset_rtss_he(uint32_t vtor_address)
  @brief    Reset the RTSS-HE (Cortex-M55 High Efficiency) subsystem.
            Programs the boot vector table address, asserts reset with
            CPUWAIT held, waits for the reset acknowledge, then releases
            reset while keeping CPUWAIT asserted. After this call, RTSS-HE
            is left in the OFF state; use pm_soc_boot_rtss_he() to actually
            start the core.
            Refer to "RTSS_HE_CTRL Register", "CM55_HE_SE_VTOR Register",
            "EXT_SYS1_RST_CTRL Register" and "EXT_SYS1_RST_ST Register" in
            HWRM for more details.
  @param    vtor_address    Address where the RTSS-HE CPU will start
                            execution when booted
  @return   0 on success, -1 on reset timeout
*/
int32_t pm_soc_reset_rtss_he(uint32_t vtor_address);

/**
  @fn       int32_t pm_soc_boot_rtss_hp(void)
  @brief    Boot the RTSS-HP (Cortex-M55 High Performance) subsystem by
            releasing CPUWAIT, then performing a dummy read of the RTSS-HP
            TCM to force clocks to start. Has no effect if RTSS-HP was
            booted already.
            Refer to "EXT_SYS0_RST_CTRL Register" in HWRM for more details.
  @note     Not applicable on ENSEMBLE_SOC_E1C; the call is a no-op.
  @return   0 on success or if core was already booted, -1 if not applicable
*/
int32_t pm_soc_boot_rtss_hp(void);

/**
  @fn       int32_t pm_soc_boot_rtss_he(void)
  @brief    Boot the RTSS-HE (Cortex-M55 High Efficiency) subsystem by
            releasing CPUWAIT, then performing a dummy read of the RTSS-HE
            TCM to force clocks to start. Has no effect if RTSS-HE was
            booted already.
            Refer to "EXT_SYS1_RST_CTRL Register" in HWRM for more details.
  @return   0 on success or if core was already booted
*/
int32_t pm_soc_boot_rtss_he(void);

/* TBD - implement functions for STOP Mode and Getting Wake-up Status */

/**
  @fn       void pm_soc_enter_stop_mode(void)
  @brief    Enter SoC STOP mode. TBD - not yet implemented; this is a
            placeholder for a future entry sequence.
  @return   None
*/
void pm_soc_enter_stop_mode();

/**
  @fn       void pm_soc_enable_stop_mode_wake_sources(void)
  @brief    Enable the wake sources that can bring the SoC out of STOP
            mode. TBD - not yet implemented; will program the VBATSEC
            WAKEUP_CTRL register.
  @return   None
*/
void pm_soc_enable_stop_mode_wake_sources();    // VBATSEC WAKEUP_CTRL register

/**
  @fn       void pm_soc_get_stop_mode_wake_pending(void)
  @brief    Get the set of wake sources that are currently pending for
            STOP mode exit. TBD - not yet implemented; will read the
            SE_EWIC EWIC_STAT register.
  @return   None
*/
void pm_soc_get_stop_mode_wake_pending();       // SE_EWIC EWIC_STAT register
