#include <stdint.h>

/* PD2 AON Register Base Addresses */
#define HOSTBASE_BASE   0x1A604000

typedef struct
{
	volatile uint32_t CLUSTER_CONFIG;
	volatile const uint32_t reserved1[3];
	volatile uint32_t PE0_CONFIG;
	volatile uint32_t PE0_RVBARADDR_LW;
	volatile const uint32_t PE0_RVBARADDR_UP;
	volatile const uint32_t reserved_PE0;
	volatile uint32_t PE1_CONFIG;
	volatile uint32_t PE1_RVBARADDR_LW;
	volatile const uint32_t PE1_RVBARADDR_UP;
	volatile const uint32_t reserved_PE1;
	volatile uint32_t PE2_CONFIG;
	volatile uint32_t PE2_RVBARADDR_LW;
	volatile const uint32_t PE2_RVBARADDR_UP;
	volatile const uint32_t reserved_PE2;
	volatile uint32_t PE3_CONFIG;
	volatile uint32_t PE3_RVBARADDR_LW;
	volatile const uint32_t PE3_RVBARADDR_UP;
	volatile const uint32_t reserved_PE3;
	volatile const uint32_t reserved2[108];
	volatile const uint32_t HOST_RST_SYN;
	volatile const uint32_t reserved3[63];
	volatile uint32_t HOST_CPU_BOOT_MSK;
	volatile uint32_t HOST_CPU_CLUS_PWR_REQ;
	volatile uint32_t HOST_CPU_WAKEUP;
	volatile const uint32_t reserved4;
	volatile uint32_t EXT_SYS0_RST_CTRL;
	volatile const uint32_t EXT_SYS0_RST_ST;
	volatile uint32_t EXT_SYS1_RST_CTRL;
	volatile const uint32_t EXT_SYS1_RST_ST;
	volatile const uint32_t reserved5[56];
	volatile uint32_t BSYS_PWR_REQ;
	volatile const uint32_t BSYS_PWR_ST;
	volatile const uint32_t reserved6[62];
	volatile const uint32_t HOST_SYS_LCTRL_ST;
	volatile uint32_t HOST_SYS_LCTRL_SET;
	volatile uint32_t HOST_SYS_LCTRL_CLR;
	volatile const uint32_t reserved7[189];
	volatile uint32_t HOSTCPUCLK_CTRL;
	volatile uint32_t HOSTCPUCLK_DIV0;
	volatile uint32_t HOSTCPUCLK_DIV1;
	volatile const uint32_t reserved8;
	volatile uint32_t GICCLK_CTRL;
	volatile uint32_t GICCLK_DIV0;
	volatile const uint32_t reserved9[2];
	volatile uint32_t ACLK_CTRL;
	volatile uint32_t ACLK_DIV0;
	volatile const uint32_t reserved10[2];
	volatile uint32_t CTRLCLK_CTRL;
	volatile uint32_t CTRLCLK_DIV0;
	volatile const uint32_t reserved11[2];
	volatile uint32_t DBGCLK_CTRL;
	volatile uint32_t DBGCLK_DIV0;
	volatile const uint32_t reserved12[2];
	volatile uint32_t HOSTUARTCLK_CTRL;
	volatile uint32_t HOSTUARTCLK_DIV0;
	volatile const uint32_t reserved13[2];
	volatile uint32_t REFCLK_CTRL;
	volatile const uint32_t reserved14[103];
	volatile const uint32_t CLKFORCE_ST;
	volatile uint32_t CLKFORCE_SET;
	volatile uint32_t CLKFORCE_CLR;
	volatile const uint32_t reserved15;
	volatile const uint32_t PLL_ST;
	volatile const uint32_t reserved16[59];
	volatile const uint32_t HOST_PPU_INT_ST;
	volatile const uint32_t reserved17[307];
	volatile const uint32_t PERIPHERAL_ID[12];
} HOSTBASE_Type;

#define HOSTBASE ((HOSTBASE_Type *) HOSTBASE_BASE)