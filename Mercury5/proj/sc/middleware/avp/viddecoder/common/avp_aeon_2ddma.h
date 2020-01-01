#ifndef AEON_2DDMA_H
#define AEON_2DDMA_H

#include "avp_mvc_types.h"
//#define DBG_ON

#ifdef DBG_ON
#define DBG_PRINTF(x) printf x
#else
#define DBG_PRINTF(x) // nothing
#endif

#ifndef REG32
#define REG32(add) *((volatile unsigned long *)(add))
#endif

#ifdef _R2_DMA_
#include "avp_aeon_r2_2ddma.h"
#else

#define CONFIG_R2_2DDMA
#define QM_BASE_ADDR 0xB0000000
#define QM_CMD0_ADDR (QM_BASE_ADDR + 0)
#define QM_CMD1_ADDR (QM_BASE_ADDR + 4)
#define QM_CTL0_ADDR (QM_BASE_ADDR + 8)
#define QM_CMD2_ADDR (QM_BASE_ADDR + 12) //QM_CTL1_ADDR (QM_BASE_ADDR + 12)

#define QM_CTL0_SW_RESET (1<<5)
#define QM_CTL0_BANK_SWITCH (1)
#define QM_CTL0_ENABLE   (1<<1)
#define QM_CTL0_SPECIAL  (1<<30)
#define QM_CTL0_CMD_STATS (0xF<<6)

#define QM_BANK_NUM  3
#ifdef CONFIG_R2_2DDMA
#define QM_BANK_SIZE 3*1024
#else
#define QM_BANK_SIZE 2048
#endif
#define QM_CMD_QUEUE_SIZE 4 //must exponential of 2

#ifdef AEONDEV
#define qm_dma_addr_cpu ((uint8*)0xC0000000)
#else
#ifdef INT_AEON_2DDMA
uint8 qm_mem[QM_BANK_SIZE*QM_BANK_NUM];
int qm_active_bank = 0;
uint64 *qm_dma_addr_dma;
uint64 *qm_dma_addr_cpu;
int qm_cmd_queue[QM_CMD_QUEUE_SIZE];
int qm_ctl_code = 0;
int qm_cmd_write = 0;
int qm_cmd_read = 0;
#else
extern uint8 qm_mem[QM_BANK_SIZE*QM_BANK_NUM];
extern int qm_active_bank;
extern uint64 *qm_dma_addr_dma;
extern uint64 *qm_dma_addr_cpu;
extern uint64 *qm_dma_addr_tmp;
extern int qm_cmd_queue[QM_CMD_QUEUE_SIZE];
extern int qm_ctl_code;
extern int qm_cmd_write;
extern int qm_cmd_read;
#endif
#endif


#define QM_READ 0
#define QM_WRITE 1

#ifdef AEONDEV

#define QM_MMIO_WRITE(addr, cmd) REG32(addr) = cmd
#define QM_MMIO_READ(addr, cmd)  cmd = REG32(addr)

#define QM_MMIO_WRITE_DBG(addr, cmd) { \
    uint32 val; \
    REG32(addr) = cmd; \
    val = REG32(addr); \
    DBG_PRINTF(("QM_MMIO_WRITE_DBG 0x%x 0x%x\n", cmd, val)); \
    assert(val == cmd); \
}

#define QM_2DDMA_WAIT_DONE() { \
    uint32 ctl; \
    do { \
        QM_MMIO_READ(QM_CTL0_ADDR, ctl); \
        DBG_PRINTF(("QM_CTL0_ADDR = 0x%x\n", ctl)); \
    } while (ctl&QM_CTL0_CMD_STATS); \
}

#define DMA2D_ENABLE() { \
    uint32 regval; \
    regval = REG32(QM_CTL0_ADDR); \
    regval |= QM_CTL0_ENABLE; \
    REG32(QM_CTL0_ADDR) = regval; \
    regval = REG32(QM_CTL0_ADDR); \
    DBG_PRINTF(("2DDMA enable = %d\n", regval&QM_CTL0_ENABLE)); \
}

#define QM_RESET() { \
    uint32 regval; \
    regval = REG32(QM_CTL0_ADDR); \
    regval |= QM_CTL0_SW_RESET; \
    REG32(QM_CTL0_ADDR) = regval; \
    printf("2DDMA sw reset = %d\n", regval&QM_CTL0_SW_RESET); \
    regval &= ~QM_CTL0_SW_RESET; \
    REG32(QM_CTL0_ADDR) = regval; \
    regval = REG32(QM_CTL0_ADDR); \
    regval &= ~QM_CTL0_BANK_SWITCH; \
    REG32(QM_CTL0_ADDR) = regval; \
    regval = REG32(QM_CTL0_ADDR); \
    regval |= QM_CTL0_SPECIAL; \
    REG32(QM_CTL0_ADDR) = regval; \
    regval = REG32(QM_CTL0_ADDR); \
    DBG_PRINTF(("2DDMA special mode = 0x%X\n", regval&QM_CTL0_SPECIAL)); \
}

#define QM_SWAP_BANK() { \
    uint32 regval, regval2; \
    QM_2DDMA_WAIT_DONE(); \
    regval = REG32(QM_CTL0_ADDR); \
    regval ^= QM_CTL0_BANK_SWITCH; \
    REG32(QM_CTL0_ADDR) = regval; \
    regval2 = REG32(QM_CTL0_ADDR); \
    DBG_PRINTF(("swap bank, regval 0x%x => 0x%x\n", regval, regval2)); \
}

#define QM_GET_ACTIVE_BANK_INDEX() ( \
    uint32 regval; \
    regval = REG32(QM_CTL0_ADDR) & QM_CTL0_BANK_SWITCH \
}

void hal_dcache_invalidate(unsigned int base, unsigned int size);
void hal_whole_dcache_flush();
void hal_whole_dcache_invalidate();

#else

#include <string.h>

#define QM_MMIO_WRITE(addr, cmd) \
    if (addr == QM_CMD0_ADDR) { \
        qm_cmd_queue[0] = cmd; \
    } else if (addr == QM_CMD1_ADDR) { \
        qm_cmd_queue[1] = cmd; \
    } else if (addr == QM_CMD2_ADDR) { \
        qm_cmd_queue[2] = cmd; \
        QM_2DDMA_WAIT_DONE(); \
    } else if (addr == QM_CTL0_ADDR) \
        qm_ctl_code = cmd;

#define QM_MMIO_READ(addr, cmd) \
    if (addr == QM_CMD0_ADDR) \
        cmd = qm_cmd_queue[0]; \
    else if (addr == QM_CMD1_ADDR) \
        cmd = qm_cmd_queue[1]; \
    else if (addr == QM_CMD2_ADDR) \
        cmd = qm_cmd_queue[2]; \
    else if (addr == QM_CTL0_ADDR) \
        cmd = qm_ctl_code;

#define QM_2DDMA_WAIT_DONE() \
{ \
    uint8 *dstart; \
    int qoffset, N, stride, H, WE; \
    uint64* dmem_addr; \
    uint64* qmem_addr; \
    uint32 stride_q; \
    uint32 w, h8; \
    uint32 i; \
 \
    dstart = (uint8*)((qm_cmd_queue[0]&0xffffff)<<3); \
    /*qoffset = (qm_cmd_queue[0]&0xfff00000) >> 20; */\
    qoffset = (qm_cmd_queue[1]&0xfff); \
    N = (qm_cmd_queue[2]&0xf); \
    stride = (qm_cmd_queue[2]&0x3f0)>>1; \
    H = (qm_cmd_queue[2]&0x7c00)>>10; \
    WE = (qm_cmd_queue[2]&0x8000)>>15; \
    DBG_PRINTF(("dstart = 0x%x, qoffset = %d, N = %d, stride = %d, H = %d, WE = %d\n", dstart, qoffset, N, stride, H, WE)); \
 \
    dmem_addr = (uint64*)dstart; \
    qmem_addr = (uint64*)((uint8*)qm_dma_addr_dma + qoffset); \
 \
    stride_q = stride >> 3; \
 \
    w = N; \
    h8 = H; \
    if (WE) { \
        while (h8!=0) { \
            for (i=0; i<w; i++) { \
                dmem_addr[i] = qmem_addr[0]; \
                qmem_addr++; \
            } \
            dmem_addr += stride_q; \
            h8--; \
        } \
    } else { \
        while (h8!=0) { \
            for (i=0; i<w; i++) { \
                qmem_addr[0] = dmem_addr[i]; \
                qmem_addr++; \
            } \
            dmem_addr += stride_q; \
            h8--; \
        } \
    } \
}

#define DMA2D_ENABLE()
#define QM_RESET() { \
    qm_active_bank = 0; \
    qm_dma_addr_cpu = (uint64*) &qm_mem[0*QM_BANK_SIZE]; \
    qm_dma_addr_dma = (uint64*) &qm_mem[1*QM_BANK_SIZE]; \
    qm_dma_addr_tmp = (uint64*) &qm_mem[2*QM_BANK_SIZE]; \
}

#define QM_SWAP_BANK() { \
    memcpy(qm_dma_addr_tmp, qm_dma_addr_cpu, sizeof(uint8)*QM_BANK_SIZE);\
    memcpy(qm_dma_addr_cpu, qm_dma_addr_dma, sizeof(uint8)*QM_BANK_SIZE);\
    memcpy(qm_dma_addr_dma, qm_dma_addr_tmp, sizeof(uint8)*QM_BANK_SIZE);\
}

#define QM_GET_ACTIVE_BANK_INDEX() qm_active_bank

#define hal_dcache_invalidate(base, size) // nothing
#define hal_whole_dcache_flush()          // nothing
#define hal_whole_dcache_invalidate()     // nothing

#endif

#define QM_PUT_CMD(dstart, qoffset, N, stride, H, WE, line_gap) \
{ \
    uint32 cmd0, cmd1, cmd2, ctl; \
 \
    DBG_PRINTF(("QM_PUT_CMD: dstart = 0x%x qoffset = 0x%x N = %d, stride = %d, H = %d, WE = %d, line_gap = %d\n", dstart, qoffset, N, stride, H, WE, line_gap)); \
    assert((((int)(dstart))&7) == 0); \
    assert(((qoffset)&7) == 0); \
    assert(((stride)&7) == 0); \
    assert((N)>0 && (N)<16); \
    assert((H)>0 && (H)<32); \
    assert((WE==0) || (WE==1)); \
    assert((line_gap==0) || (line_gap==1) || (line_gap==2) || (line_gap==3)); \
    assert((((uint32)(dstart))&0xf8000000)==0); \
 \
    cmd0 = ((uint32)(dstart)>>3); \
    cmd1 = (uint32)qoffset; \
    cmd2 = ((line_gap)<<16) | ((WE)<<15) | ((H)<<10) | ((stride)<<1) | (N); \
    do { \
        QM_MMIO_READ(QM_CTL0_ADDR, ctl); \
    } while ((int32)ctl<0); \
    QM_MMIO_WRITE(QM_CMD0_ADDR, cmd0); \
    /*QM_MMIO_WRITE_DBG(QM_CMD0_ADDR, cmd0);*/ \
    QM_MMIO_WRITE(QM_CMD1_ADDR, cmd1); \
    QM_MMIO_WRITE(QM_CMD2_ADDR, cmd2); \
    DBG_PRINTF(("QM 0x%x 0x%x\n", cmd0, cmd1)); \
    /*QM_2DDMA_WAIT_DONE();*/ \
}

#define QM_MEM ((uint8 *) qm_dma_addr_cpu)

#define QM_DEST_OFFSET 768
#define QM_DEST_OFFSET2 2368//2624
#define QM_PRED_OFFSET 1024
#define QM_PRED_OFFSET2 (1024+672)      //21*32
#define QM_ITRAN_ADDR (QM_MEM + 0)              //< inverse transformation input, size: 384 * 2
#define QM_DEST_ADDR  (QM_MEM + QM_DEST_OFFSET) //< destination for itrans and mocomp, size: 256
#define QM_DEST_ADDR2 (QM_MEM + QM_DEST_OFFSET2) //< destination for itrans and mocomp, size: 256, bak frame MC
#define QM_PRED_ADDR  (QM_MEM + QM_PRED_OFFSET) //< reference pixel of mocomp, size: T.B.D.
#define QM_PRED_ADDR2  (QM_MEM + QM_PRED_OFFSET2) //< reference pixel for backward
#define QM_RVC_MCTEMP (QM_MEM + 0)
#define ITRANS_2DDMA_LUMA_PITCH     32
#define ITRANS_2DDMA_CHROMA_PITCH   24
#endif

#endif
