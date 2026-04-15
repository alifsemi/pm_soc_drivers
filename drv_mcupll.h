#include <stdint.h>
#include <stdbool.h>

/**
  @fn       bool OSC_enabled(void)
  @brief    Check whether the HFXO crystal oscillator is currently
            enabled.
            Refer to "XO_REG1 Register" in HWRM for more details.
  @return   true if the HFXO oscillator is enabled, false otherwise
*/
bool OSC_enabled();

/**
  @fn       void OSC_initialize(void)
  @brief    Enable the on-chip bandgap, power up the HFXO crystal
            oscillator with the fast-start and boost options active for
            faster lock, wait for the oscillator to stabilize, and then
            drop back to the normal (non-boost) running configuration.
            Refer to "ANATOP_REG1 Register" and "XO_REG1 Register" in
            HWRM for more details.
  @note     The caller should update the SystemREFClock variable before
            enabling HFXO.
  @return   None
*/
void OSC_initialize();

/**
  @fn       void OSC_uninitialize(void)
  @brief    Disable the HFXO crystal oscillator and turn off the
            associated bandgap.
            Refer to "ANATOP_REG1 Register" and "XO_REG1 Register" in
            HWRM for more details.
  @return   None
*/
void OSC_uninitialize();

/**
  @fn       bool PLL_enabled(void)
  @brief    Check whether the MCU PLL is currently enabled, by reading
            the PLL_LOCK bit.
            Refer to "PLL_LOCK_CTRL Register" in HWRM for more details.
  @return   true if the MCU PLL is enabled, false otherwise
*/
bool PLL_enabled();

/**
  @fn       void PLL_initialize(uint32_t xtal_freq)
  @brief    Start the HFXO crystal oscillator (if not already running),
            then configure and release the MCU PLL using integer and
            fractional divider values appropriate for the supplied
            crystal frequency, wait for lock, and set the PLL_LOCK bit.
            The exact PLL configuration used depends on the SoC family.
            Refer to "XO_REG1 Register", "MCUPLL_REG1 Register",
            "MCUPLL_REG2 Register", "MCUPLL_REG3 Register",
            "CLK_ENA Register" and "PLL_LOCK_CTRL Register" in HWRM for
            more details.
  @note     The caller should update the SystemREFClock variable before
            enabling the MCU PLL.
  @param    xtal_freq   HFXO crystal frequency in Hz. Supported values
                        are 19200000, 20000000, 24000000, 25000000,
                        30000000, 32000000, 38400000, 40000000 and
                        48000000. Unsupported values cause the function
                        to hang.
  @return   None
*/
void PLL_initialize(uint32_t xtal_freq);

/**
  @fn       void PLL_uninitialize(void)
  @brief    Clear the PLL_LOCK bit, place the MCU PLL back into reset,
            and clear its configuration registers. The HFXO crystal
            oscillator is left running.
            Refer to "PLL_LOCK_CTRL Register", "MCUPLL_REG1 Register",
            "MCUPLL_REG2 Register" and "MCUPLL_REG3 Register" in HWRM
            for more details.
  @return   None
*/
void PLL_uninitialize();
