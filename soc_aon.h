#include <stdint.h>

/* PD2 AON Register Base Addresses */
#define AONALL_BASE  0x1A604000
#define AONSEC_BASE  0x1A605000
#define SE_EWIC_BASE 0x1A607000

typedef struct
{
    volatile uint32_t RTSS_HP_CTRL;       /* 0x00 */
    volatile uint32_t RTSS_HP_RESET;      /* 0x04 */
    volatile const uint32_t RESERVED1[2]; /* 0x08-0x0C */
    volatile uint32_t RTSS_HE_CTRL;       /* 0x10 */
    volatile uint32_t RTSS_HE_RESET;      /* 0x14 */
    volatile const uint32_t RESERVED2;    /* 0x18 */
    volatile uint32_t LPPERIPH_CLK_EN;    /* 0x1C */
    volatile uint32_t SYSTOP_CLK_DIV;     /* 0x20 */
    volatile const uint32_t RESERVED3[3]; /* 0x24-0x2C */
    volatile uint32_t MISC_REG1;          /* 0x30 */
    volatile uint32_t ANATOP_REG1;        /* 0x34 */
    volatile const uint32_t RESERVED4[3]; /* 0x38-0x40 */
#if defined(ENSEMBLE_SOC_GEN2)
    volatile uint32_t OSPI_BYPASS_EN;     /* 0x44 */
#endif
} AONALL_Type;

#define AONALL_RTSS_HP_CTRL_COLD_WAKEUP_Pos    (0U)
#define AONALL_RTSS_HP_CTRL_COLD_WAKEUP_Msk    (1U << AONALL_RTSS_HP_CTRL_COLD_WAKEUP_Pos)
#define AONALL_RTSS_HE_CTRL_COLD_WAKEUP_Pos    (0U)
#define AONALL_RTSS_HE_CTRL_COLD_WAKEUP_Msk    (1U << AONALL_RTSS_HE_CTRL_COLD_WAKEUP_Pos)
#define AONALL_LPPERIPH_CLK_EN_UART_CKEN_Pos   (0U)
#define AONALL_LPPERIPH_CLK_EN_UART_CKEN_Msk   (1U << AONALL_LPPERIPH_CLK_EN_UART_CKEN_Pos)
#define AONALL_SYSTOP_CLK_DIV_PCLK_DIVISOR_Pos (0U)
#define AONALL_SYSTOP_CLK_DIV_PCLK_DIVISOR_Msk (3U << AONALL_SYSTOP_CLK_DIV_PCLK_DIVISOR_Pos)
#define AONALL_SYSTOP_CLK_DIV_HCLK_DIVISOR_Pos (8U)
#define AONALL_SYSTOP_CLK_DIV_HCLK_DIVISOR_Msk (3U << AONALL_SYSTOP_CLK_DIV_HCLK_DIVISOR_Pos)
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
#define AONALL_MISC_REG1_HFXTAL_DIVISOR_Pos (17U)
#define AONALL_MISC_REG1_HFXTAL_DIVISOR_Msk (15U << AONALL_MISC_REG1_HFXTAL_DIVISOR_Pos)
#else
#define AONALL_MISC_REG1_HFXTAL_DIVISOR_Pos (13U)
#define AONALL_MISC_REG1_HFXTAL_DIVISOR_Msk (15U << AONALL_MISC_REG1_HFXTAL_DIVISOR_Pos)
#endif
#define AONALL_ANATOP_REG1_HFXTAL_BG_ENA_Pos        (0U)
#define AONALL_ANATOP_REG1_HFXTAL_BG_ENA_Msk        (1U << AONALL_ANATOP_REG1_HFXTAL_BG_ENA_Pos)
#define AONALL_ANATOP_REG1_HFXTAL_VRET_CTRL_Pos     (1U)
#define AONALL_ANATOP_REG1_HFXTAL_VREF_CTRL_Msk     (15U << AONALL_ANATOP_REG1_HFXTAL_VRET_CTRL_Pos)
#define AONALL_ANATOP_REG1_HFXTAL_VREF_CTRL_DEFAULT (8U << AONALL_ANATOP_REG1_HFXTAL_VRET_CTRL_Pos)

typedef struct
{
    volatile const uint32_t RESERVED1[4]; /* 0x00-0x0C */
    volatile uint32_t CM55_HP_NS_VTOR;    /* 0x10 */
    volatile uint32_t CM55_HP_SE_VTOR;    /* 0x14 */
    volatile const uint32_t RESERVED2[2]; /* 0x18-0x1C */
    volatile uint32_t XO_REG1;            /* 0x20 */
    volatile uint32_t MCUPLL_REG1;        /* 0x24 */
    volatile uint32_t MCUPLL_REG2;        /* 0x28 */
    volatile uint32_t MCUPLL_REG3;        /* 0x2C */
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    volatile uint32_t AUDIOPLL_REG1;      /* 0x30 */
    volatile uint32_t AUDIOPLL_REG2;      /* 0x34 */
    volatile uint32_t AUDIOPLL_REG3;      /* 0x38 */
#if defined(ENSEMBLE_SOC_GEN2)
    volatile uint32_t SHARED_MEM_CTRL;    /* 0x3C */
#endif
#else
    volatile const uint32_t RESERVED3[4]; /* 0x30-0x3C */
    volatile uint32_t PD4_CLK_SEL;        /* 0x40 */
    volatile const uint32_t RESERVED4;    /* 0x44 */
    volatile uint32_t PD4_PWR_CTRL;       /* 0x48 */
    volatile uint32_t PD4_CLK_PLL;        /* 0x4C */
    volatile const uint32_t RESERVED5[2]; /* 0x50-0x54 */
    volatile uint32_t PD4_PWR_STAT;       /* 0x58 */
#endif
} AONSEC_Type;

#define AONSEC_XO_REG1_EN_XTAL_Pos       (0U)
#define AONSEC_XO_REG1_EN_XTAL_Msk       (1U << AONSEC_XO_REG1_EN_XTAL_Pos)
#define AONSEC_XO_REG1_FASTSTART_Pos     (1U)
#define AONSEC_XO_REG1_FASTSTART_Msk     (1U << AONSEC_XO_REG1_FASTSTART_Pos)
#define AONSEC_XO_REG1_BOOST_Pos         (6U)
#define AONSEC_XO_REG1_BOOST_Msk         (1U << AONSEC_XO_REG1_FASTSTART_Pos)
#define AONSEC_XO_REG1_XTAL_CAP_CTRL_Pos (7U)
#define AONSEC_XO_REG1_XTAL_CAP_CTRL_Msk (15U << AONSEC_XO_REG1_XTAL_CAP_CTRL_Pos)
#define AONSEC_PD4_CLK_SEL_Pos           (0U)
#define AONSEC_PD4_CLK_SEL_Msk           (3U << AONSEC_PD4_CLK_SEL_Pos)
#define AONSEC_PD4_PWR_CTRL_Pos          (12U)
#define AONSEC_PD4_PWR_CTRL_Msk          (1U << AONSEC_PD4_PWR_CTRL_Pos)
#define AONSEC_PD4_CLK_PLL_Pos           (0U)
#define AONSEC_PD4_CLK_PLL_Msk           (1U << AONSEC_PD4_CLK_PLL_Pos)
#define AONSEC_PD4_PWR_STAT_Pos          (0U)
#define AONSEC_PD4_PWR_STAT_Msk          (0x7FFUL << AONSEC_PD4_PWR_STAT_Pos)
#define AONSEC_PD4_PWR_STAT_PWR_OFF      (0U << AONSEC_PD4_PWR_STAT_Pos)
#define AONSEC_PD4_PWR_STAT_PWR_ON       (0x100UL << AONSEC_PD4_PWR_STAT_Pos)

typedef struct
{
    volatile uint32_t EWIC_STAT;   /* 0x00 */
    volatile uint32_t EWIC_ENABLE; /* 0x04 */
    volatile uint32_t EWIC_CLEAR;  /* 0x08 */
    volatile uint32_t EWIC_SET;    /* 0x0C */
} SE_EWIC_Type;

#define AONALL  ((AONALL_Type *)AONALL_BASE)
#define AONSEC  ((AONSEC_Type *)AONSEC_BASE)
#define SE_EWIC ((SE_EWIC_Type *)SE_EWIC_BASE)