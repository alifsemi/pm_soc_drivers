#include <stdint.h>

#define APSS_RX_MHU0_BASE 0x40000000
#define APSS_TX_MHU0_BASE 0x40010000
#define APSS_RX_MHU1_BASE 0x40020000
#define APSS_TX_MHU1_BASE 0x40030000

#define SESS_RX_MHU0_BASE 0x40040000
#define SESS_TX_MHU0_BASE 0x40050000
#define SESS_RX_MHU1_BASE 0x40060000
#define SESS_TX_MHU1_BASE 0x40070000

#define RTSS_RX_MHU0_BASE 0x40080000
#define RTSS_TX_MHU0_BASE 0x40090000
#define RTSS_RX_MHU1_BASE 0x400A0000
#define RTSS_TX_MHU1_BASE 0x400B0000

#define MHU_MAX_CHANNELS    124

typedef struct {
    volatile const uint32_t CH_ST;      // RO
    volatile const uint32_t reserved1;
    volatile const uint32_t reserved2;
    volatile uint32_t CH_SET;           // WO
    volatile const uint32_t CH_INT_ST;  // RO
    volatile uint32_t CH_INT_CL;        // WO
    volatile uint32_t CH_INT_EN;        // RW
    volatile const uint32_t reserved3;
} MHU_SENDER_CHANNEL_type;

typedef struct {
    volatile const uint32_t CH_ST;      // RO
    volatile const uint32_t CH_ST_MSK;  // RO
    volatile uint32_t CH_CLR;           // WO
    volatile const uint32_t reserved1;
    volatile const uint32_t CH_MSK_ST;  // RO
    volatile uint32_t CH_MSK_SET;       // WO
    volatile uint32_t CH_MSK_CLR;       // WO
    volatile const uint32_t reserved2;
} MHU_RECEIVER_CHANNEL_type;

typedef struct {
    MHU_SENDER_CHANNEL_type SEND_CHANNELS[MHU_MAX_CHANNELS];
    volatile const uint32_t MHU_CFG;
    volatile const uint32_t RESP_CFG;
    volatile uint32_t ACCESS_REQUEST;
    volatile const uint32_t ACCESS_READY;
    volatile const uint32_t INT_ST;
    volatile uint32_t INT_CLR;
    volatile uint32_t INT_EN;
    volatile const uint32_t reserved1;
    volatile const uint32_t CHCOMB_INT_ST[4];
    volatile const uint32_t reserved2[6];
    volatile const uint32_t IIDR;
    volatile const uint32_t AIDR;
    volatile const uint32_t PID2[4];
    volatile const uint32_t PID[4];
    volatile const uint32_t CID[4];
} MHU_SENDER_regs;

typedef struct {
    MHU_RECEIVER_CHANNEL_type RECV_CHANNELS[MHU_MAX_CHANNELS];
    volatile const uint32_t MHU_CFG;
    volatile const uint32_t reserved1[3];
    volatile const uint32_t INT_ST;
    volatile uint32_t INT_CLR;
    volatile uint32_t INT_EN;
    volatile const uint32_t reserved2;
    volatile const uint32_t CHCOMB_INT_ST[4];
    volatile const uint32_t reserved3[6];
    volatile const uint32_t IIDR;
    volatile const uint32_t AIDR;
    volatile const uint32_t PID2[4];
    volatile const uint32_t PID[4];
    volatile const uint32_t CID[4];
} MHU_RECEIVER_regs;

void MHU_SENDER_Set(uint32_t target, uint32_t channel, uint32_t value);
void MHU_SENDER_Check(uint32_t target, uint32_t channel, uint32_t *value);

void MHU_RECEIVER_Read(uint32_t source, uint32_t channel, uint32_t *value);
void MHU_RECEIVER_Clear(uint32_t source, uint32_t channel, uint32_t value);
