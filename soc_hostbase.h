#include <stdint.h>

/* PD2 AON Register Base Addresses */
#define HOSTBASE_BASE 0x1A010000

typedef struct
{
    volatile uint32_t CLUSTER_CONFIG;          /* 0x000 */
    volatile const uint32_t reserved1[3];      /* 0x004-0x00C */
    volatile uint32_t PE0_CONFIG;              /* 0x010 */
    volatile uint32_t PE0_RVBARADDR_LW;        /* 0x014 */
    volatile const uint32_t PE0_RVBARADDR_UP;  /* 0x018 */
    volatile const uint32_t reserved_PE0;      /* 0x01C */
    volatile uint32_t PE1_CONFIG;              /* 0x020 */
    volatile uint32_t PE1_RVBARADDR_LW;        /* 0x024 */
    volatile const uint32_t PE1_RVBARADDR_UP;  /* 0x028 */
    volatile const uint32_t reserved_PE1;      /* 0x02C */
    volatile uint32_t PE2_CONFIG;              /* 0x030 */
    volatile uint32_t PE2_RVBARADDR_LW;        /* 0x034 */
    volatile const uint32_t PE2_RVBARADDR_UP;  /* 0x038 */
    volatile const uint32_t reserved_PE2;      /* 0x03C */
    volatile uint32_t PE3_CONFIG;              /* 0x040 */
    volatile uint32_t PE3_RVBARADDR_LW;        /* 0x044 */
    volatile const uint32_t PE3_RVBARADDR_UP;  /* 0x048 */
    volatile const uint32_t reserved_PE3;      /* 0x04C */
    volatile const uint32_t reserved2[108];    /* 0x050-0x1FC */
    volatile const uint32_t HOST_RST_SYN;      /* 0x200 */
    volatile const uint32_t reserved3[63];     /* 0x204-0x2FC */
    volatile uint32_t HOST_CPU_BOOT_MSK;       /* 0x300 */
    volatile uint32_t HOST_CPU_CLUS_PWR_REQ;   /* 0x304 */
    volatile uint32_t HOST_CPU_WAKEUP;         /* 0x308 */
    volatile const uint32_t reserved4;         /* 0x30C */
    volatile uint32_t EXT_SYS0_RST_CTRL;       /* 0x310 */
    volatile const uint32_t EXT_SYS0_RST_ST;   /* 0x314 */
    volatile uint32_t EXT_SYS1_RST_CTRL;       /* 0x318 */
    volatile const uint32_t EXT_SYS1_RST_ST;   /* 0x31C */
    volatile const uint32_t reserved5[56];     /* 0x320-0x3FC */
    volatile uint32_t BSYS_PWR_REQ;            /* 0x400 */
    volatile const uint32_t BSYS_PWR_ST;       /* 0x404 */
    volatile const uint32_t reserved6[62];     /* 0x408-0x4FC */
    volatile const uint32_t HOST_SYS_LCTRL_ST; /* 0x500 */
    volatile uint32_t HOST_SYS_LCTRL_SET;      /* 0x504 */
    volatile uint32_t HOST_SYS_LCTRL_CLR;      /* 0x508 */
    volatile const uint32_t reserved7[189];    /* 0x50C-0x7FC */
    volatile uint32_t HOSTCPUCLK_CTRL;         /* 0x800 */
    volatile uint32_t HOSTCPUCLK_DIV0;         /* 0x804 */
    volatile uint32_t HOSTCPUCLK_DIV1;         /* 0x808 */
    volatile const uint32_t reserved8;         /* 0x80C */
    volatile uint32_t GICCLK_CTRL;             /* 0x810 */
    volatile uint32_t GICCLK_DIV0;             /* 0x814 */
    volatile const uint32_t reserved9[2];      /* 0x818-0x81C */
    volatile uint32_t ACLK_CTRL;               /* 0x820 */
    volatile uint32_t ACLK_DIV0;               /* 0x824 */
    volatile const uint32_t reserved10[2];     /* 0x828-0x82C */
    volatile uint32_t CTRLCLK_CTRL;            /* 0x830 */
    volatile uint32_t CTRLCLK_DIV0;            /* 0x834 */
    volatile const uint32_t reserved11[2];     /* 0x838-0x83C */
    volatile uint32_t DBGCLK_CTRL;             /* 0x840 */
    volatile uint32_t DBGCLK_DIV0;             /* 0x844 */
    volatile const uint32_t reserved12[2];     /* 0x848-0x84C */
    volatile uint32_t HOSTUARTCLK_CTRL;        /* 0x850 */
    volatile uint32_t HOSTUARTCLK_DIV0;        /* 0x854 */
    volatile const uint32_t reserved13[2];     /* 0x858-0x85C */
    volatile uint32_t REFCLK_CTRL;             /* 0x860 */
    volatile const uint32_t reserved14[103];   /* 0x864-0x9FC */
    volatile const uint32_t CLKFORCE_ST;       /* 0xA00 */
    volatile uint32_t CLKFORCE_SET;            /* 0xA04 */
    volatile uint32_t CLKFORCE_CLR;            /* 0xA08 */
    volatile const uint32_t reserved15;        /* 0xA0C */
    volatile const uint32_t PLL_ST;            /* 0xA10 */
    volatile const uint32_t reserved16[59];    /* 0xA14-0xAFC */
    volatile const uint32_t HOST_PPU_INT_ST;   /* 0xB00 */
    volatile const uint32_t reserved17[307];   /* 0xB04-0xFCC */
    volatile const uint32_t PERIPHERAL_ID[12]; /* 0xFD0-0xFFC */
} HOSTBASE_Type;

/* HOST_CPU_CLUS_PWR_REQ register bit fields */
#define HOSTBASE_HOST_CPU_CLUS_PWR_REQ_PWR_REQ_Pos     (0U)
#define HOSTBASE_HOST_CPU_CLUS_PWR_REQ_PWR_REQ_Msk     (1U << HOSTBASE_HOST_CPU_CLUS_PWR_REQ_PWR_REQ_Pos)
#define HOSTBASE_HOST_CPU_CLUS_PWR_REQ_MEM_RET_REQ_Pos (1U)
#define HOSTBASE_HOST_CPU_CLUS_PWR_REQ_MEM_RET_REQ_Msk (1U << HOSTBASE_HOST_CPU_CLUS_PWR_REQ_MEM_RET_REQ_Pos)

/* HOST_CPU_WAKEUP register bit fields */
#define HOSTBASE_HOST_CPU_WAKEUP_CORE0_WAKEUP_Pos (0U)
#define HOSTBASE_HOST_CPU_WAKEUP_CORE0_WAKEUP_Msk (1U << HOSTBASE_HOST_CPU_WAKEUP_CORE0_WAKEUP_Pos)
#define HOSTBASE_HOST_CPU_WAKEUP_CORE1_WAKEUP_Pos (1U)
#define HOSTBASE_HOST_CPU_WAKEUP_CORE1_WAKEUP_Msk (1U << HOSTBASE_HOST_CPU_WAKEUP_CORE1_WAKEUP_Pos)
#define HOSTBASE_HOST_CPU_WAKEUP_CORE2_WAKEUP_Pos (2U)
#define HOSTBASE_HOST_CPU_WAKEUP_CORE2_WAKEUP_Msk (1U << HOSTBASE_HOST_CPU_WAKEUP_CORE2_WAKEUP_Pos)
#define HOSTBASE_HOST_CPU_WAKEUP_CORE3_WAKEUP_Pos (3U)
#define HOSTBASE_HOST_CPU_WAKEUP_CORE3_WAKEUP_Msk (1U << HOSTBASE_HOST_CPU_WAKEUP_CORE3_WAKEUP_Pos)

/* EXT_SYS{0-1}_RST_CTRL register bit fields */
#define HOSTBASE_EXT_SYS_RST_CTRL_CPUWAIT_Pos (0U)
#define HOSTBASE_EXT_SYS_RST_CTRL_CPUWAIT_Msk (1U << HOSTBASE_EXT_SYS_RST_CTRL_CPUWAIT_Pos)
#define HOSTBASE_EXT_SYS_RST_CTRL_RST_REQ_Pos (1U)
#define HOSTBASE_EXT_SYS_RST_CTRL_RST_REQ_Msk (1U << HOSTBASE_EXT_SYS_RST_CTRL_RST_REQ_Pos)

/* EXT_SYS{0-1}_RST_ST register bit fields */
#define HOSTBASE_EXT_SYS_RST_ST_RST_ACK_Pos      (1U)
#define HOSTBASE_EXT_SYS_RST_ST_RST_ACK_Msk      (3U << HOSTBASE_EXT_SYS_RST_ST_RST_ACK_Pos)
#define HOSTBASE_EXT_SYS_RST_ST_RST_ACK_NONE     (0U << HOSTBASE_EXT_SYS_RST_ST_RST_ACK_Pos)
#define HOSTBASE_EXT_SYS_RST_ST_RST_ACK_UNABLE   (1U << HOSTBASE_EXT_SYS_RST_ST_RST_ACK_Pos)
#define HOSTBASE_EXT_SYS_RST_ST_RST_ACK_COMPLETE (2U << HOSTBASE_EXT_SYS_RST_ST_RST_ACK_Pos)

/* BSYS_PWR_REQ register bit fields */
#define HOSTBASE_BSYS_PWR_REQ_WAKEUP_EN_Pos           (0U)
#define HOSTBASE_BSYS_PWR_REQ_WAKEUP_EN_Msk           (1U << HOSTBASE_BSYS_PWR_REQ_WAKEUP_EN_Pos)
#define HOSTBASE_BSYS_PWR_REQ_REFCLK_REQ_Pos          (1U)
#define HOSTBASE_BSYS_PWR_REQ_REFCLK_REQ_Msk          (1U << HOSTBASE_BSYS_PWR_REQ_REFCLK_REQ_Pos)
#define HOSTBASE_BSYS_PWR_REQ_DBGTOP_PWR_REQ_Pos      (2U)
#define HOSTBASE_BSYS_PWR_REQ_DBGTOP_PWR_REQ_Msk      (1U << HOSTBASE_BSYS_PWR_REQ_DBGTOP_PWR_REQ_Pos)
#define HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_Pos      (3U)
#define HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_Msk      (7U << HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_Pos)
#define HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_OFF      (0U << HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_Pos)
#define HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_MEM_RET  (1U << HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_Pos)
#define HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_FUNC_RET (2U << HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_Pos)
#define HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_ON       (4U << HOSTBASE_BSYS_PWR_REQ_SYSTOP_PWR_REQ_Pos)

/* BSYS_PWR_ST register bit fields */
#define HOSTBASE_BSYS_PWR_ST_DBGTOP_PWR_ST_Pos      (2U)
#define HOSTBASE_BSYS_PWR_ST_DBGTOP_PWR_ST_Msk      (1U << HOSTBASE_BSYS_PWR_ST_DBGTOP_PWR_ST_Pos)
#define HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_Pos      (3U)
#define HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_Msk      (7U << HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_Pos)
#define HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_OFF      (0U << HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_Pos)
#define HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_MEM_RET  (1U << HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_Pos)
#define HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_FUNC_RET (2U << HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_Pos)
#define HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_ON       (4U << HOSTBASE_BSYS_PWR_ST_SYSTOP_PWR_ST_Pos)

/* CLKFORCE_ST register bit fields */
#define HOSTBASE_CLKFORCE_ST_GICCLK_FORCE_ST_Pos  (1U)
#define HOSTBASE_CLKFORCE_ST_GICCLK_FORCE_ST_Msk  (1U << HOSTBASE_CLKFORCE_ST_GICCLK_FORCE_ST_Pos)
#define HOSTBASE_CLKFORCE_ST_ACLK_FORCE_ST_Pos    (2U)
#define HOSTBASE_CLKFORCE_ST_ACLK_FORCE_ST_Msk    (1U << HOSTBASE_CLKFORCE_ST_ACLK_FORCE_ST_Pos)
#define HOSTBASE_CLKFORCE_ST_CTRLCLK_FORCE_ST_Pos (3U)
#define HOSTBASE_CLKFORCE_ST_CTRLCLK_FORCE_ST_Msk (1U << HOSTBASE_CLKFORCE_ST_CTRLCLK_FORCE_ST_Pos)
#define HOSTBASE_CLKFORCE_ST_DBGCLK_FORCE_ST_Pos  (4U)
#define HOSTBASE_CLKFORCE_ST_DBGCLK_FORCE_ST_Msk  (1U << HOSTBASE_CLKFORCE_ST_DBGCLK_FORCE_ST_Pos)
#define HOSTBASE_CLKFORCE_ST_REFCLK_FORCE_ST_Pos  (6U)
#define HOSTBASE_CLKFORCE_ST_REFCLK_FORCE_ST_Msk  (1U << HOSTBASE_CLKFORCE_ST_REFCLK_FORCE_ST_Pos)

/* CLKFORCE_SET register bit fields */
#define HOSTBASE_CLKFORCE_SET_GICCLK_FORCE_SET_Pos  (1U)
#define HOSTBASE_CLKFORCE_SET_GICCLK_FORCE_SET_Msk  (1U << HOSTBASE_CLKFORCE_SET_GICCLK_FORCE_SET_Pos)
#define HOSTBASE_CLKFORCE_SET_ACLK_FORCE_SET_Pos    (2U)
#define HOSTBASE_CLKFORCE_SET_ACLK_FORCE_SET_Msk    (1U << HOSTBASE_CLKFORCE_SET_ACLK_FORCE_SET_Pos)
#define HOSTBASE_CLKFORCE_SET_CTRLCLK_FORCE_SET_Pos (3U)
#define HOSTBASE_CLKFORCE_SET_CTRLCLK_FORCE_SET_Msk (1U << HOSTBASE_CLKFORCE_SET_CTRLCLK_FORCE_SET_Pos)
#define HOSTBASE_CLKFORCE_SET_DBGCLK_FORCE_SET_Pos  (4U)
#define HOSTBASE_CLKFORCE_SET_DBGCLK_FORCE_SET_Msk  (1U << HOSTBASE_CLKFORCE_SET_DBGCLK_FORCE_SET_Pos)
#define HOSTBASE_CLKFORCE_SET_REFCLK_FORCE_SET_Pos  (6U)
#define HOSTBASE_CLKFORCE_SET_REFCLK_FORCE_SET_Msk  (1U << HOSTBASE_CLKFORCE_SET_REFCLK_FORCE_SET_Pos)

/* CLKFORCE_CLR register bit fields */
#define HOSTBASE_CLKFORCE_CLR_GICCLK_FORCE_CLR_Pos  (1U)
#define HOSTBASE_CLKFORCE_CLR_GICCLK_FORCE_CLR_Msk  (1U << HOSTBASE_CLKFORCE_CLR_GICCLK_FORCE_CLR_Pos)
#define HOSTBASE_CLKFORCE_CLR_ACLK_FORCE_CLR_Pos    (2U)
#define HOSTBASE_CLKFORCE_CLR_ACLK_FORCE_CLR_Msk    (1U << HOSTBASE_CLKFORCE_CLR_ACLK_FORCE_CLR_Pos)
#define HOSTBASE_CLKFORCE_CLR_CTRLCLK_FORCE_CLR_Pos (3U)
#define HOSTBASE_CLKFORCE_CLR_CTRLCLK_FORCE_CLR_Msk (1U << HOSTBASE_CLKFORCE_CLR_CTRLCLK_FORCE_CLR_Pos)
#define HOSTBASE_CLKFORCE_CLR_DBGCLK_FORCE_CLR_Pos  (4U)
#define HOSTBASE_CLKFORCE_CLR_DBGCLK_FORCE_CLR_Msk  (1U << HOSTBASE_CLKFORCE_CLR_DBGCLK_FORCE_CLR_Pos)
#define HOSTBASE_CLKFORCE_CLR_REFCLK_FORCE_CLR_Pos  (6U)
#define HOSTBASE_CLKFORCE_CLR_REFCLK_FORCE_CLR_Msk  (1U << HOSTBASE_CLKFORCE_CLR_REFCLK_FORCE_CLR_Pos)

#define HOSTBASE ((HOSTBASE_Type *)HOSTBASE_BASE)