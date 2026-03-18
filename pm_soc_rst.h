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

#define WE_LPTIMER  0XF00     // bit11:8
#define WE_LPGPIO   0XFF0000  // bit23:16

/* TBD - there is no way to do this via RTSS */
void pm_soc_reset_soc();

/* TBD - there is no way to do this via RTSS */
void pm_soc_reset_apss();

/* resetting the RTSS will leave it in the OFF state
 * vtor_address is where the CPU will start execution when booted */
void pm_soc_reset_rtss_hp(uint32_t vtor_address);
void pm_soc_reset_rtss_he(uint32_t vtor_address);

/* booting the RTSS will bring it out of the OFF state,
 * there is no effect if the RTSS was booted already */
void pm_soc_boot_rtss_hp();
void pm_soc_boot_rtss_he();

/* TBD - implement functions for STOP Mode and Getting Wake-up Status */
void pm_soc_enter_stop_mode();
void pm_soc_enable_stop_mode_wake_sources();    // VBATSEC WAKEUP_CTRL register
void pm_soc_get_stop_mode_wake_pending();       // SE_EWIC EWIC_STAT register