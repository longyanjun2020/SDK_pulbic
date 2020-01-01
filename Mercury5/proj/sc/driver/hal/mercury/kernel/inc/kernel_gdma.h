/***************************************************************************
 *  kernel_gdma.h
 *--------------------------------------------------------------------------
 *  Scope: GDMA SPI related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_GDMA_H__
#define __KERNEL_GDMA_H__

#include "stdcomp.h"
#include "cpu_mem_map.hc"

/****************************************************************************/
/*        GDMA registers                           */
/****************************************************************************/
typedef struct KeGdma_s
{
    //0x0[rw]
    u32 reg_gdma_ctrl_enable        :1;
    u32 reg_gdma_ctrl_reset         :1;
    u32 reg_gdma_ctrl_interrupt     :1;
    u32                             :1;
    u32 reg_gdma_ctrl_dst_addr_mode :2;
    u32 reg_gdma_ctrl_src_addr_mode :2;
    u32 reg_gdma_path_sel           :2;
    u32 reg_gdma_piu_src            :3;
    u32 reg_gdma_piu_dst            :3;
    u32                             :16;
    //0x1[rw]
    u32 reg_gdma_miu_src_addrL      :16;
    u32                             :16;
    //0x2[rw]
    u32 reg_gdma_miu_src_addrH      :16;
    u32                             :16;
    //0x3[rw]
    u32 reg_gdma_miu_dst_addrL      :16;
    u32                             :16;
    //0x4[rw]
    u32 reg_gdma_miu_dst_addrH      :16;
    u32                             :16;
    //0x5[rw]
    u32 reg_gdma_tx_countL          :16;
    u32                             :16;
    //0x6[rw]
    u32 reg_gdma_tx_countH          :8;
    u32                             :24;
    //0x7[w]
    u32 reg_gdma_trigger            :1;
    u32                             :31;
    //0x8[r]
    u32 reg_gdma_done_flag          :1;     //0:Busy 1:Done
    u32                             :31;
    //0x9[w]
    u32 reg_gdma_clear              :1;
    u32                             :31;
} KeGdma_t;

extern volatile KeGdma_t* const g_ptKeGdma;

#endif // __KERNEL_GDMA_H__
                                                 
