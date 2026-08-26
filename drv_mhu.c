#include "drv_mhu.h"

/* Set bits in the sending channel to generate an interrupt */
void MHU_SENDER_Set(uint32_t target, uint32_t channel, uint32_t value)
{
    MHU_SENDER_regs *MHU = (MHU_SENDER_regs *) target;
    if (value == 0) return;
    if (channel < (MHU->MHU_CFG & 0x7FU)) {
        MHU->ACCESS_REQUEST = 1;
        while(MHU->ACCESS_READY == 0);
        MHU->SEND_CHANNELS[channel].CH_SET = value;
        MHU->ACCESS_REQUEST = 0;
    }
}

/* Check if bits in the sending channel were cleared by the receiver */
void MHU_SENDER_Check(uint32_t target, uint32_t channel, uint32_t *value)
{
    MHU_SENDER_regs *MHU = (MHU_SENDER_regs *) target;
    if (channel < (MHU->MHU_CFG & 0x7FU)) {
        *value = MHU->SEND_CHANNELS[channel].CH_ST;
    }
}

/* Read bits in the receiving channel */
void MHU_RECEIVER_Read(uint32_t source, uint32_t channel, uint32_t *value)
{
    MHU_RECEIVER_regs *MHU = (MHU_RECEIVER_regs *) source;
    if (channel < (MHU->MHU_CFG & 0x7FU)) {
        *value = MHU->RECV_CHANNELS[channel].CH_ST;
    }
}

/* Clear bits in the receiving channel */
void MHU_RECEIVER_Clear(uint32_t source, uint32_t channel, uint32_t value)
{
    MHU_RECEIVER_regs *MHU = (MHU_RECEIVER_regs *) source;
    if (value == 0) return;
    if (channel < (MHU->MHU_CFG & 0x7FU)) {
        MHU->RECV_CHANNELS[channel].CH_CLR = value;
    }
}
