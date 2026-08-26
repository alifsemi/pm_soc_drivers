#include <stdint.h>

/* BKRAM_IN_TCM
    0: HE and HP cores share the 4kB Backup SRAM
    1: HE uses its TCM and HP core uses 4kB Backup SRAM region */
#define BKRAM_IN_TCM            0
#define BKRAM_IDX_MAX           1000

#define BKRAM_INDEX_LPT0_COUNT  0
#define BKRAM_INDEX_LPT1_COUNT  1
#define BKRAM_INDEX_HP_RX_CNT   2
#define BKRAM_INDEX_HE_RX_CNT   3
#define BKRAM_INDEX_WHILE1      4
#define BKRAM_INDEX_HP_CYCLES   5
#define BKRAM_INDEX_HE_CYCLES   6
#define BKRAM_INDEX_FIRSTBOOT   7

int32_t bk_ram_rd(uint32_t *data, uint32_t offset);
int32_t bk_ram_wr(uint32_t *data, uint32_t offset);
