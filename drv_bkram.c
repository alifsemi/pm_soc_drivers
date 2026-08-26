#include "drv_bkram.h"

#if BKRAM_IN_TCM && defined(M55_HE)
static volatile uint32_t bk_ram_data[BKRAM_IDX_MAX]
__attribute__((section (".bss.noinit.bk_ram")));
#else
static volatile uint32_t *bk_ram_data = (uint32_t *)0x4902C000;
#endif

int32_t bk_ram_rd(uint32_t *data, uint32_t offset)
{
    if (offset < BKRAM_IDX_MAX) {
        *data = bk_ram_data[offset];
        return 0;
    }
    return -1;
}

int32_t bk_ram_wr(uint32_t *data, uint32_t offset)
{
    if (offset < BKRAM_IDX_MAX) {
        bk_ram_data[offset] = *data;
        return 0;
    }
    return -1;
}