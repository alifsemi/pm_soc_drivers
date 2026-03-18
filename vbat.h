#include <stdint.h>

/* PD0 VBAT Register Base Addresses */
#define VBATALL_BASE    0x1A609000
#define VBATSEC_BASE    0x1A60A000
#define VBATSEC2_BASE   0x1A60C000

typedef struct
{
    volatile uint32_t GPIO_CTRL;        /* 0x00 */
    volatile uint32_t TIMER_CLKSEL;     /* 0x04 */
    volatile uint32_t PWR_CTRL;         /* 0x08 */
    volatile uint32_t RET_CTRL;         /* 0x0C */
    volatile uint32_t RTC_CLK_EN;       /* 0x10 */
#if defined(ENSEMBLE_SOC_E1C)
    volatile uint32_t RTCB_CLK_EN;      /* 0x14 */
#endif
} VBATALL_Type;

typedef struct
{
    volatile uint32_t MISC_CTRL;        /* 0x00 */
    volatile uint32_t PWR_CTRL;         /* 0x04 */
    volatile uint32_t WKUP_CTRL;        /* 0x08 */
    volatile const uint32_t RESERVED1;  /* 0x0C */
    volatile const uint32_t RESERVED2;  /* 0x10 */
    volatile const uint32_t RESERVED3;  /* 0x14 */
    volatile uint32_t RET_CTRL;         /* 0x18 */
    volatile const uint32_t RESERVED4;  /* 0x1C */
    volatile uint32_t CM55_HE_NS_VTOR;  /* 0x20 */
    volatile uint32_t CM55_HE_SE_VTOR;  /* 0x24 */
    volatile const uint32_t RESERVED5;  /* 0x28 */
    volatile const uint32_t RESERVED6;  /* 0x2C */
    volatile uint32_t DCDC_REG1;        /* 0x30 */
    volatile uint32_t DCDC_REG2;        /* 0x34 */
    volatile uint32_t VBAT_ANA_REG1;    /* 0x38 */
    volatile uint32_t VBAT_ANA_REG2;    /* 0x3C */
    volatile uint32_t VBAT_ANA_REG3;    /* 0x40 */
} VBATSEC_Type;

typedef struct
{
    volatile uint32_t GPIO_POR_CTRL;    /* 0x00 */
    volatile uint32_t SEL_AUDIO_PLL;    /* 0x04 */
    volatile uint32_t ANA_REG_SEL;      /* 0x08 */
    volatile const uint32_t RESERVED1;  /* 0x0C */
    volatile uint32_t CLEAR_ON_NSRST;   /* 0x10 */
    volatile uint32_t SEL_FAST_APB;     /* 0x14 */
    volatile uint32_t VBAT_RST_SYN;     /* 0x18 */
} VBATSEC2_Type;

#define VBATALL ((VBATALL_Type *) VBATALL_BASE)
#define VBATSEC ((VBATSEC_Type *) VBATSEC_BASE)
#define VBATSEC2 ((VBATSEC2_Type *) VBATSEC2_BASE)