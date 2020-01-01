#ifndef AEON_R2_2DDMA_H
#define AEON_R2_2DDMA_H

//#define R2_BASE_ADDR 0x28000200 //FPGA
//#define R2_BASE_ADDR 0xA0000000
#define R2_BASE_ADDR 0xFFFF0000
#define R2_OFFSET 0x40
#define R2_SWITCH_BANK (R2_BASE_ADDR + ((R2_OFFSET+0x2C)<<2))
#define REG_VQM_BANK_SWITCH (1<<4)
#define REG_VQM_OWENER_SEL  (1<<3)

#define REG_VQMEM_EN        (R2_BASE_ADDR + ((R2_OFFSET+0x18)<<2))
#define REG_VQMEM_SPACE_EN  (1<<14)
#define REG_VQMEM_SPACE_DI  (0xBFFF)

#define REG_DQMEM_BASE_LOW  (R2_BASE_ADDR + ((R2_OFFSET+0x0D)<<2))
#define REG_DQMEM_BASE_HIGH (R2_BASE_ADDR + ((R2_OFFSET+0x0E)<<2))
#define REG_DQMEM_MASK_LOW  (R2_BASE_ADDR + ((R2_OFFSET+0x0F)<<2))
#define REG_DQMEM_MASK_HIGH (R2_BASE_ADDR + ((R2_OFFSET+0x10)<<2))

#define REG_VQMEM_BASE_LOW  (R2_BASE_ADDR + ((R2_OFFSET+0x27)<<2))
#define REG_VQMEM_BASE_HIGH (R2_BASE_ADDR + ((R2_OFFSET+0x28)<<2))
#define REG_VQMEM_MASK_LOW  (R2_BASE_ADDR + ((R2_OFFSET+0x29)<<2))
#define REG_VQMEM_MASK_HIGH (R2_BASE_ADDR + ((R2_OFFSET+0x2A)<<2))

//#define VQM_BASE_ADDR 0x28280000 //FPGA
#define DQM_BASE_ADDR 0xE1000000
#define VQM_BASE_ADDR (DQM_BASE_ADDR + 0x200000)
#define DQMEM_SIZE                   (8*1024)
#define VQMEM_SIZE                   (6*1024)
//#define R2_DQMEM_BASE           0xE1000000
//#define R2_VQMEM_BASE           (R2_DQMEM_BASE + 0x200000)

//#define QM_BASE_ADDR 0x28008000 //this should be DMA RIU bank base address
//#define QM_BASE_ADDR 0xA0008000 //this should be DMA RIU bank base address
#define QM_BASE_ADDR (R2_BASE_ADDR + 0x8000) //this should be DMA RIU bank base address
#define QM_SADR_ADDR (QM_BASE_ADDR + 0x0)
#define QM_DADR_ADDR (QM_BASE_ADDR + 0x4)
#define QM_CFG0_ADDR (QM_BASE_ADDR + 0x8)
#define QM_CTL0_ADDR (QM_BASE_ADDR + 0xC)

#define QM_CTL0_SW_RESET (1<<5)
//#define QM_CTL0_BANK_SWITCH #error 1
#define QM_CTL0_ENABLE   (1<<1)
#define QM_CTL0_DISABLE   (0xFFFD)
//#define QM_CTL0_SPECIAL  #error 2
#define QM_CTL0_CMD_STATS (0xF<<6)

#define R2_1D_DMA 0
#define R2_2D_DMA 1
#define QM_CFG0_OP_MODE R2_2D_DMA //18
#define QM_CFG0_CMD_REQ 1      //19

#define AHB  3 //0011, binary
#define QM32 4 //0100, binary
#define QM64 8 //1000, binary
//#define QM_CFG0_SRC_MAP      //23:20
//#define QM_CFG0_DST_MAP      //27:24
#define DQ_MEM 0
#define IQ_MEM 1
#define PQ_MEM 2
#define VQ_MEM 3
#define QM_CFG0_QM_SEL VQ_MEM  //31:28

#define QM_BANK_NUM  2
#define QM_BANK_SIZE (3*1024)
#define QM_CMD_QUEUE_SIZE 4 //must exponential of 2

#ifdef AEONDEV
//#define qm_dma_addr_cpu ((uint8*)0xC0000000)
//#define qm_dma_addr_cpu ((uint8*)0x28100000)
#define qm_dma_addr_cpu ((uint8*)VQM_BASE_ADDR)
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
extern int qm_cmd_queue[QM_CMD_QUEUE_SIZE];
extern int qm_ctl_code;
extern int qm_cmd_write;
extern int qm_cmd_read;
#endif
#endif

#define QM_READ 0
#define QM_WRITE 1

#define QM_MMIO_WRITE(addr, cmd) REG32(addr) = cmd
#define QM_MMIO_READ(addr, cmd)  cmd = REG32(addr)

#define QM_MMIO_WRITE_DBG(addr, cmd) { \
    uint32 val; \
    REG32(addr) = cmd; \
    val = REG32(addr); \
    DBG_PRINTF(("QM_MMIO_WRITE_DBG 0x%x 0x%x\n", cmd, val)); \
    swenc_assert(val == cmd); \
}
#if 0
#define QM_2DDMA_WAIT_DONE() { \
    uint32 ctl; \
    uint32 tmp_count =0; \
    do { \
        DBG_PRINTF(("QM_2DDMA_WAIT_DONE [0x%x] = (0x%x, 0x%x), [%s, %d]\n", QM_CTL0_ADDR, ctl, ctl&QM_CTL0_CMD_STATS, __FUNCTION__, __LINE__)); \
        QM_MMIO_READ(QM_CTL0_ADDR, ctl); \
        tmp_count++; \
    } while (ctl&QM_CTL0_CMD_STATS); \
    DrvUartDebugTrace("tmp_count = %d\n",tmp_count); \
}
#else
#define QM_2DDMA_WAIT_DONE() { \
    uint32 ctl; \
    do { \
        DBG_PRINTF(("QM_2DDMA_WAIT_DONE [0x%x] = (0x%x, 0x%x), [%s, %d]\n", QM_CTL0_ADDR, ctl, ctl&QM_CTL0_CMD_STATS, __FUNCTION__, __LINE__)); \
        QM_MMIO_READ(QM_CTL0_ADDR, ctl); \
    } while (ctl&QM_CTL0_CMD_STATS); \
}
#endif
#define DMA2D_ENABLE() { \
    uint32 regval, regval2; \
    regval = REG32(QM_CTL0_ADDR); \
    REG32(QM_CTL0_ADDR) = (regval | QM_CTL0_ENABLE); \
    regval2 = REG32(QM_CTL0_ADDR); \
    DBG_PRINTF(("DMA2D_ENABLE [0x%x] = (0x%x, 0x%x), [%s, %d]\n", QM_CTL0_ADDR, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}

#define DMA2D_DISABLE() { \
    uint32 regval, regval2; \
    regval = REG32(QM_CTL0_ADDR); \
    REG32(QM_CTL0_ADDR) = (regval & QM_CTL0_DISABLE); \
    regval2 = REG32(QM_CTL0_ADDR); \
    DBG_PRINTF(("DMA2D_DISABLE [0x%x] = (0x%x, 0x%x), [%s, %d]\n", QM_CTL0_ADDR, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}

#define QM_RESET() { \
    uint32 regval, regval2; \
    regval = REG32(QM_CTL0_ADDR); \
    REG32(QM_CTL0_ADDR) = (regval | QM_CTL0_SW_RESET); \
    regval2 = REG32(QM_CTL0_ADDR); \
    DBG_PRINTF(("1 QM_RESET [0x%x] = (0x%x, 0x%x), [%s, %d]\n", QM_CTL0_ADDR, regval, regval2, __FUNCTION__, __LINE__)); \
 \
    REG32(QM_CTL0_ADDR) = (regval2 & ~QM_CTL0_SW_RESET); \
    regval = REG32(QM_CTL0_ADDR); \
    DBG_PRINTF(("2 QM_RESET [0x%x] = (0x%x, 0x%x), [%s, %d]\n", QM_CTL0_ADDR, regval2, regval, __FUNCTION__, __LINE__)); \
 \
    /*regval = REG32(QM_CTL0_ADDR);*/ \
    /*regval &= ~QM_CTL0_BANK_SWITCH;*/ \
    /*REG32(QM_CTL0_ADDR) = regval;*/ \
 \
    /*regval = REG32(QM_CTL0_ADDR);*/ \
    /*regval |= QM_CTL0_SPECIAL;*/ \
    /*REG32(QM_CTL0_ADDR) = regval;*/ \
    /*regval = REG32(QM_CTL0_ADDR);*/ \
    /*DBG_PRINTF(("2DDMA special mode = 0x%X\n", regval&QM_CTL0_SPECIAL));*/ \
    asm("l.syncwritebuffer"); \
}

#define VQM_OWENER_SEL() { \
    uint32 regval, regval2; \
    regval = REG32(R2_SWITCH_BANK); \
    REG32(R2_SWITCH_BANK) = (regval | REG_VQM_OWENER_SEL); \
    regval2 = REG32(R2_SWITCH_BANK); \
    DBG_PRINTF(("VQM_OWENER_SEL [0x%x] = (0x%x, 0x%x), [%s, %d]\n", R2_SWITCH_BANK, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}

#define VQMEM_EN() { \
    uint32 regval, regval2; \
    regval = REG32(REG_VQMEM_EN); \
    DBG_PRINTF(("1 REG_VQMEM_EN [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_VQMEM_EN, regval, regval2, __FUNCTION__, __LINE__)); \
    REG32(REG_VQMEM_EN) = (regval | REG_VQMEM_SPACE_EN); \
    regval2 = REG32(REG_VQMEM_EN); \
    DBG_PRINTF(("2 REG_VQMEM_EN [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_VQMEM_EN, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}

#define VQMEM_DI() { \
    uint32 regval, regval2; \
    regval = REG32(REG_VQMEM_EN); \
    DBG_PRINTF(("1 REG_VQMEM_EN [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_VQMEM_EN, regval, regval2, __FUNCTION__, __LINE__)); \
    REG32(REG_VQMEM_EN) = (regval & REG_VQMEM_SPACE_DI); \
    regval2 = REG32(REG_VQMEM_EN); \
    DBG_PRINTF(("2 REG_VQMEM_EN [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_VQMEM_EN, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}

#define REG_DQMEM_BASE() { \
    uint32 regval, regval2; \
    regval = REG32(REG_DQMEM_BASE_HIGH); \
    REG32(REG_DQMEM_BASE_HIGH) = ((DQM_BASE_ADDR>>16)&0xffff); \
    regval2 = REG32(REG_DQMEM_BASE_HIGH); \
    DBG_PRINTF(("REG_DQMEM_BASE_HIGH [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_DQMEM_BASE_HIGH, regval, regval2, __FUNCTION__, __LINE__)); \
    regval = REG32(REG_DQMEM_BASE_LOW); \
    REG32(REG_DQMEM_BASE_LOW) = (DQM_BASE_ADDR&0xffff); \
    regval2 = REG32(REG_DQMEM_BASE_LOW); \
    DBG_PRINTF(("REG_DQMEM_BASE_LOW [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_DQMEM_BASE_LOW, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}

#define REG_DQMEM_MASK() { \
    uint32 regval, regval2; \
    regval = REG32(REG_DQMEM_MASK_HIGH); \
    REG32(REG_DQMEM_MASK_HIGH) = (((~(DQMEM_SIZE-1))>>16) & 0xFFFF); \
    regval2 = REG32(REG_DQMEM_MASK_HIGH); \
    DBG_PRINTF(("REG_DQMEM_MASK_HIGH [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_DQMEM_MASK_HIGH, regval, regval2, __FUNCTION__, __LINE__)); \
    regval = REG32(REG_DQMEM_MASK_LOW); \
    REG32(REG_DQMEM_MASK_LOW) = ((~(DQMEM_SIZE-1)) & 0xFFFF); \
    regval2 = REG32(REG_DQMEM_MASK_LOW); \
    DBG_PRINTF(("REG_DQMEM_MASK_LOW [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_DQMEM_MASK_LOW, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}


#define REG_VQMEM_BASE() { \
    uint32 regval, regval2; \
    regval = REG32(REG_VQMEM_BASE_HIGH); \
    REG32(REG_VQMEM_BASE_HIGH) = ((VQM_BASE_ADDR>>16)&0xffff); \
    regval2 = REG32(REG_VQMEM_BASE_HIGH); \
    DBG_PRINTF(("REG_VQMEM_BASE_HIGH [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_VQMEM_BASE_HIGH, regval, regval2, __FUNCTION__, __LINE__)); \
    regval = REG32(REG_VQMEM_BASE_LOW); \
    REG32(REG_VQMEM_BASE_LOW) = (VQM_BASE_ADDR&0xffff); \
    regval2 = REG32(REG_VQMEM_BASE_LOW); \
    DBG_PRINTF(("REG_VQMEM_BASE_LOW [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_VQMEM_BASE_LOW, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}

#define REG_VQMEM_MASK() { \
    uint32 regval, regval2; \
    regval = REG32(REG_VQMEM_MASK_HIGH); \
    REG32(REG_VQMEM_MASK_HIGH) = (((~(VQMEM_SIZE-1))>>16) & 0xFFFF); \
    regval2 = REG32(REG_VQMEM_MASK_HIGH); \
    DBG_PRINTF(("REG_VQMEM_MASK_HIGH [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_VQMEM_MASK_HIGH, regval, regval2, __FUNCTION__, __LINE__)); \
    regval = REG32(REG_VQMEM_MASK_LOW); \
    REG32(REG_VQMEM_MASK_LOW) = ((~(VQMEM_SIZE-1)) & 0xFFFF); \
    regval2 = REG32(REG_VQMEM_MASK_LOW); \
    DBG_PRINTF(("REG_VQMEM_MASK_LOW [0x%x] = (0x%x, 0x%x), [%s, %d]\n", REG_VQMEM_MASK_LOW, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}

#define QM_SWAP_BANK() { \
    uint32 regval, regval2; \
    QM_2DDMA_WAIT_DONE(); \
    asm("l.syncwritebuffer"); \
    regval = REG32(R2_SWITCH_BANK); \
    REG32(R2_SWITCH_BANK) = (regval ^ REG_VQM_BANK_SWITCH); \
    regval2 = REG32(R2_SWITCH_BANK); \
    DBG_PRINTF(("QM_SWAP_BANK [0x%x] = (0x%x, 0x%x), [%s, %d]\n", R2_SWITCH_BANK, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}

#define QM_SWAP_BANK_NOWAIT() { \
    uint32 regval, regval2; \
    asm("l.syncwritebuffer"); \
    regval = REG32(R2_SWITCH_BANK); \
    REG32(R2_SWITCH_BANK) = (regval ^ REG_VQM_BANK_SWITCH); \
    regval2 = REG32(R2_SWITCH_BANK); \
    DBG_PRINTF(("QM_SWAP_BANK [0x%x] = (0x%x, 0x%x), [%s, %d]\n", R2_SWITCH_BANK, regval, regval2, __FUNCTION__, __LINE__)); \
    asm("l.syncwritebuffer"); \
}

#define QM_GET_ACTIVE_BANK_INDEX() ( \
}

void hal_dcache_invalidate(unsigned int base, unsigned int size);
void hal_whole_dcache_flush();
void hal_whole_dcache_invalidate();

#define QM_PUT_CMD(dstart, qoffset, N, stride, H, WE, line_gap) \
{ \
    uint32 sadr, dadr, cfg, ctl; \
    uint32 src_map, dst_map; \
 \
    DBG_PRINTF(("QM_PUT_CMD: dstart = 0x%x qoffset = 0x%x N = %d, stride = %d, H = %d, WE = %d, line_gap = %d, [%s, %d]\n", dstart, qoffset, N, stride, H, WE, line_gap, __FUNCTION__, __LINE__)); \
    DBG_PRINTF(("QM_SADR_ADDR: 0x%x\n", QM_SADR_ADDR)); \
    DBG_PRINTF(("QM_DADR_ADDR: 0x%x\n", QM_DADR_ADDR)); \
    DBG_PRINTF(("QM_CFG0_ADDR: 0x%x\n", QM_CFG0_ADDR)); \
    DBG_PRINTF(("QM_CTL0_ADDR: 0x%x\n", QM_CTL0_ADDR)); \
 \
    asm("l.syncwritebuffer"); \
    DBG_PRINTF(("9\n")); \
    if (WE==QM_READ) { \
        /*read from dram*/ \
        sadr = (uint32)(dstart); \
        dadr = (uint32)(qoffset&0xffff); \
        src_map = AHB; \
        dst_map = QM64; \
    } else { \
        /*write to dram*/ \
        sadr = (uint32)(qoffset&0xffff); \
        dadr = (uint32)(dstart); \
        src_map = QM64; \
        dst_map = AHB; \
    } \
 \
    cfg = (QM_CFG0_QM_SEL<<28) | \
          (dst_map<<24) | \
          (src_map<<20) | \
          (QM_CFG0_CMD_REQ<<19) | \
          (QM_CFG0_OP_MODE<<18) | \
          ((line_gap)<<16) | ((H)<<11) | ((stride)<<2) | (N); \
 \
    DBG_PRINTF(("10\n")); \
     QM_2DDMA_WAIT_DONE(); \
    DBG_PRINTF(("11\n")); \
    do { \
        QM_MMIO_READ(QM_CTL0_ADDR, ctl); \
    } while ((int32)ctl<0); \
    DBG_PRINTF(("12\n")); \
    \
    QM_MMIO_WRITE(QM_SADR_ADDR, sadr); \
    QM_MMIO_WRITE(QM_DADR_ADDR, dadr); \
    QM_MMIO_WRITE(QM_CFG0_ADDR, cfg); \
    DBG_PRINTF(("QM 0x%x 0x%x 0x%x\n", sadr, dadr, cfg)); \
    asm("l.syncwritebuffer"); \
}

#if 0
#define QM_PUT_CMD_NOWAIT QM_PUT_CMD
#else
#define QM_PUT_CMD_NOWAIT(dstart, qoffset, N, stride, H, WE, line_gap) \
{ \
    uint32 sadr, dadr, cfg; \
    uint32 src_map, dst_map; \
    asm("l.syncwritebuffer"); \
    if (WE==QM_READ) { \
        /*read from dram*/ \
        sadr = (uint32)(dstart); \
        dadr = (uint32)((qoffset)&(0xffff)); \
        src_map = AHB; \
        dst_map = QM64; \
    } else { \
        /*write to dram*/ \
        sadr = (uint32)((qoffset)&(0xffff)); \
        dadr = (uint32)(dstart); \
        src_map = QM64; \
        dst_map = AHB; \
    } \
 \
    cfg = (QM_CFG0_QM_SEL<<28) | \
          (dst_map<<24) | \
          (src_map<<20) | \
          (QM_CFG0_CMD_REQ<<19) | \
          (QM_CFG0_OP_MODE<<18) | \
          ((line_gap)<<16) | ((H)<<11) | ((stride)<<2) | (N); \
    QM_MMIO_WRITE(QM_SADR_ADDR, sadr); \
    QM_MMIO_WRITE(QM_DADR_ADDR, dadr); \
    QM_MMIO_WRITE(QM_CFG0_ADDR, cfg); \
    DBG_PRINTF(("QM 0x%x 0x%x 0x%x\n", sadr, dadr, cfg)); \
    asm("l.syncwritebuffer"); \
}

#endif
#define QM_MEM ((uint8 *) qm_dma_addr_cpu)

#define QM_DEST_OFFSET 768
#define QM_PRED_OFFSET 1024
#define QM_ITRAN_ADDR (QM_MEM + 0)              //< inverse transformation input, size: 384 * 2
#define QM_DEST_ADDR  (QM_MEM + QM_DEST_OFFSET) //< destination for itrans and mocomp, size: 256
#define QM_PRED_ADDR  (QM_MEM + QM_PRED_OFFSET) //< reference pixel of mocomp, size: T.B.D.

#endif
