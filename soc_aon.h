#include <stdint.h>

/* PD2 AON Register Base Addresses */
#define AONALL_BASE     0x1A604000
#define AONSEC_BASE     0x1A605000
#define SE_EWIC_BASE    0x1A607000

typedef struct
{
    volatile uint32_t RTSS_HP_CTRL;     /* 0x00 */
    volatile uint32_t RTSS_HP_RESET;    /* 0x04 */
    volatile const uint32_t RESERVED1[2];
    volatile uint32_t RTSS_HE_CTRL;     /* 0x10 */
    volatile uint32_t RTSS_HE_RESET;    /* 0x14 */
    volatile const uint32_t RESERVED2;
    volatile uint32_t LPPERIPH_CLK_EN;  /* 0x1C */
    volatile uint32_t SYSTOP_CLK_DIV;   /* 0x20 */
    volatile const uint32_t RESERVED3[3];
    volatile uint32_t MISC_REG1;        /* 0x30 */
    volatile uint32_t ANATOP_REG1;      /* 0x34 */
    volatile const uint32_t RESERVED4[3];
    volatile uint32_t OSPI_BYPASS_EN;   /* 0x44 */
} AONALL_Type;

typedef struct
{
    volatile const uint32_t RESERVED1[4];
    volatile uint32_t CM55_HP_NS_VTOR;  /* 0x10 */
    volatile uint32_t CM55_HP_SE_VTOR;  /* 0x14 */
    volatile const uint32_t RESERVED2[2];
    volatile uint32_t XO_REG1;          /* 0x20 */
    volatile uint32_t MCUPLL_REG1;      /* 0x24 */
    volatile uint32_t MCUPLL_REG2;      /* 0x28 */
    volatile uint32_t MCUPLL_REG3;      /* 0x2C */
#if defined(ENSEMBLE_SOC_GEN2) || defined(ENSEMBLE_SOC_E1C)
    volatile uint32_t AUDIO_PLL_REG1;   /* 0x30 */
    volatile uint32_t AUDIO_PLL_REG2;   /* 0x34 */
    volatile uint32_t AUDIO_PLL_REG3;   /* 0x38 */
#if defined(ENSEMBLE_SOC_GEN2)
    volatile uint32_t SHARED_MEM_CTRL;  /* 0x3C */
#endif
#else
    volatile const uint32_t RESERVED3[4];
    volatile uint32_t PD4_CLK_SEL;      /* 0x40 */
    volatile const uint32_t RESERVED4;
    volatile uint32_t PD4_PWR_CTRL;     /* 0x48 */
    volatile uint32_t PD4_CLK_PLL;      /* 0x4C */
    volatile const uint32_t RESERVED5[2];
    volatile uint32_t PD4_PWR_STAT;     /* 0x58 */
#endif
} AONSEC_Type;

typedef struct
{
    volatile uint32_t EWIC_STAT;        /* 0x00 */
    volatile uint32_t EWIC_ENABLE;      /* 0x04 */
    volatile uint32_t EWIC_CLEAR;       /* 0x08 */
    volatile uint32_t EWIC_SET;         /* 0x0C */
} SE_EWIC_Type;

#define AONALL ((AONALL_Type *) AONALL_BASE)
#define AONSEC ((AONSEC_Type *) AONSEC_BASE)
#define SE_EWIC ((SE_EWIC_Type *) SE_EWIC_BASE)