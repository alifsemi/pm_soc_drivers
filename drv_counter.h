#include <stdint.h>

/**
  @fn       void refclk_cntr_init(void)
  @brief    Initialize and enable the REFCLK system counter and program its
            frequency register with the current REFCLK frequency so that the
            counter value can be converted to time.
  @return   None
*/
void refclk_cntr_init();

/**
  @fn       void refclk_cntr_update(void)
  @brief    Re-program the REFCLK counter frequency register with the current
            REFCLK frequency. Call this after a clock change so that delays
            and time conversions based on the counter stay accurate.
  @return   None
*/
void refclk_cntr_update();

/**
  @fn       uint32_t refclk_cntr_freq(void)
  @brief    Read back the REFCLK counter frequency register, i.e. the number
            of counter ticks per second.
  @return   REFCLK counter frequency in Hz
*/
uint32_t refclk_cntr_freq();

/**
  @fn       uint32_t refclk_cntr_val(void)
  @brief    Read the lower 32 bits of the current REFCLK counter value.
  @return   Lower 32 bits of the REFCLK counter
*/
uint32_t refclk_cntr_val();

/**
  @fn       uint64_t refclk_cntr_val64(void)
  @brief    Read the full 64-bit current REFCLK counter value.
  @return   64-bit REFCLK counter value
*/
uint64_t refclk_cntr_val64();

/**
  @fn       void s32k_cntr_init(void)
  @brief    Initialize and enable the 32.768 kHz (S32K) system counter and
            program its frequency register with 32768, so that the counter
            value can be converted to time.
  @return   None
*/
void s32k_cntr_init();

/**
  @fn       uint32_t s32k_cntr_val(void)
  @brief    Read the lower 32 bits of the current S32K counter value.
  @return   Lower 32 bits of the S32K counter
*/
uint32_t s32k_cntr_val();

/**
  @fn       uint64_t s32k_cntr_val64(void)
  @brief    Read the full 64-bit current S32K counter value.
  @return   64-bit S32K counter value
*/
uint64_t s32k_cntr_val64();

/**
  @fn       void delay_ms_s32k(uint32_t nticks)
  @brief    Busy-wait for the requested number of milliseconds using the
            S32K (32.768 kHz) counter as the time base.
  @note     s32k_cntr_init() must have been called beforehand.
  @param    nticks  delay duration in milliseconds
  @return   None
*/
void delay_ms_s32k(uint32_t nticks);

/**
  @fn       void delay_us_s32k(uint32_t nticks)
  @brief    Busy-wait for the requested number of microseconds using the
            S32K (32.768 kHz) counter as the time base. Resolution is
            limited by the 32.768 kHz tick (~30.5 us).
  @note     s32k_cntr_init() must have been called beforehand.
  @param    nticks  delay duration in microseconds
  @return   None
*/
void delay_us_s32k(uint32_t nticks);

/**
  @fn       void delay_us_refclk(uint32_t nticks)
  @brief    Busy-wait for the requested number of microseconds using the
            REFCLK counter as the time base, deriving the tick count from
            the programmed REFCLK frequency.
  @note     refclk_cntr_init() must have been called beforehand.
  @param    nticks  delay duration in microseconds
  @return   None
*/
void delay_us_refclk(uint32_t nticks);

/**
  @fn       void refclk_cntr_enable_cntbase(uint32_t cntbase)
  @brief    Enable a REFCLK compare counter base (channel) and clear its
            interrupt enable.
  @param    cntbase  compare counter base index, valid range 0..3
  @return   None
*/
void refclk_cntr_enable_cntbase(uint32_t cntbase);

/**
  @fn       void refclk_cntr_disable_cntbase(uint32_t cntbase)
  @brief    Disable a REFCLK compare counter base (channel) and its
            interrupt enable.
  @param    cntbase  compare counter base index, valid range 0..3
  @return   None
*/
void refclk_cntr_disable_cntbase(uint32_t cntbase);

/**
  @fn       void refclk_cntr_enable_cntbase_intr(uint32_t cntbase, uint64_t compare_val)
  @brief    Program the compare value for a REFCLK counter base and enable
            its interrupt, which fires when the counter reaches compare_val.
  @param    cntbase      compare counter base index, valid range 0..3
  @param    compare_val  64-bit counter value at which the interrupt fires
  @return   None
*/
void refclk_cntr_enable_cntbase_intr(uint32_t cntbase, uint64_t compare_val);

/**
  @fn       void refclk_cntr_disable_cntbase_intr(uint32_t cntbase)
  @brief    Disable the compare interrupt for a REFCLK counter base.
  @param    cntbase  compare counter base index, valid range 0..3
  @return   None
*/
void refclk_cntr_disable_cntbase_intr(uint32_t cntbase);

/**
  @fn       void s32k_cntr_enable_cntbase(uint32_t cntbase)
  @brief    Enable an S32K compare counter base (channel) and clear its
            interrupt enable.
  @param    cntbase  compare counter base index, valid range 0..1
  @return   None
*/
void s32k_cntr_enable_cntbase(uint32_t cntbase);

/**
  @fn       void s32k_cntr_disable_cntbase(uint32_t cntbase)
  @brief    Disable an S32K compare counter base (channel) and its
            interrupt enable.
  @param    cntbase  compare counter base index, valid range 0..1
  @return   None
*/
void s32k_cntr_disable_cntbase(uint32_t cntbase);

/**
  @fn       void s32k_cntr_enable_cntbase_intr(uint32_t cntbase, uint64_t compare_val)
  @brief    Program the compare value for an S32K counter base and enable
            its interrupt, which fires when the counter reaches compare_val.
  @param    cntbase      compare counter base index, valid range 0..1
  @param    compare_val  64-bit counter value at which the interrupt fires
  @return   None
*/
void s32k_cntr_enable_cntbase_intr(uint32_t cntbase, uint64_t compare_val);

/**
  @fn       void s32k_cntr_disable_cntbase_intr(uint32_t cntbase)
  @brief    Disable the compare interrupt for an S32K counter base and wait
            until the interrupt enable is observed as cleared.
  @param    cntbase  compare counter base index, valid range 0..1
  @return   None
*/
void s32k_cntr_disable_cntbase_intr(uint32_t cntbase);
