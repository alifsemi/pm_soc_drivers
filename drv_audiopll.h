#include <stdint.h>
#include <stdbool.h>

/**
  @fn       bool AUDIOPLL_enabled(void)
  @brief    Check whether the audio PLL is currently out of reset and
            running, by inspecting the PLL reset-release bit.
            Refer to "AUDIO_PLL_REG1 Register" in HWRM for more details.
  @return   true if the audio PLL is enabled, false otherwise
*/
bool AUDIOPLL_enabled();

/**
  @fn       void AUDIOPLL_initialize(uint32_t xtal_freq)
  @brief    Initialize and start the audio PLL from the HFXO crystal.
            Selects the integer and fractional divider values appropriate
            for the supplied crystal frequency, releases the PLL reset,
            waits for it to settle, and routes the audio PLL output to the
            audio clock mux. To actually consume the audio PLL clock, the
            clk_sel bit in I2Sx_CTRL or the pdm_cksel bit in EXPSLV0_CTRL
            must also be set.
            Refer to "AUDIO_PLL_REG1 Register", "AUDIO_PLL_REG2 Register",
            "AUDIO_PLL_REG3 Register" and "SEL_AUDIO_PLL Register" in HWRM
            for more details.
  @note     Only applicable on ENSEMBLE_SOC_GEN2 and ENSEMBLE_SOC_E1C.
  @note     The HFXO crystal oscillator must already be running before
            this function is called.
  @param    xtal_freq   HFXO crystal frequency in Hz. Supported values are
                        19200000, 20000000, 24000000, 25000000, 30000000,
                        32000000, 38400000, 40000000 and 48000000.
                        Unsupported values cause the function to hang.
  @return   None
*/
void AUDIOPLL_initialize(uint32_t xtal_freq);

/**
  @fn       void AUDIOPLL_uninitialize(void)
  @brief    Deselect the audio PLL from the audio clock mux, put the PLL
            back into reset, and clear its configuration registers.
            Refer to "AUDIO_PLL_REG1 Register", "AUDIO_PLL_REG2 Register",
            "AUDIO_PLL_REG3 Register" and "SEL_AUDIO_PLL Register" in HWRM
            for more details.
  @note     Only applicable on ENSEMBLE_SOC_GEN2 and ENSEMBLE_SOC_E1C.
  @return   None
*/
void AUDIOPLL_uninitialize();
