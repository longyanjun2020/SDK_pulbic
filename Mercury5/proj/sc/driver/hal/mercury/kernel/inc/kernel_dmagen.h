/***************************************************************************
 *  kernel_dmagen.h
 *--------------------------------------------------------------------------
 *  Scope: General DMA related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_DMAGEN_H__
#define __KERNEL_DMAGEN_H__

#include "cpu_mem_map.hc"

/****************************************************************************/
/*        General DMA registers                                                     */
/****************************************************************************/

typedef struct KeDmaGen_s
{
    // 0x00
    u32 reg_dma_move_en                 :2;
    u32                                 :30;
    // 0x01
    u32 reg_move0_offset_en             :1;
    u32 reg_move1_offset_en             :1;
    u32                                 :30;
    // 0x02
    u32 reg_dma_move0_en_status         :1;     // [RO]
    u32 reg_dma_move1_en_status         :1;     // [RO]
    u32                                 :30;
    // 0x03
    u32 reg_move0_src_start_addr_l      :16;
    u32                                 :16;
    // 0x04
    u32 reg_move0_src_start_addr_h      :16;
    u32                                 :16;
    // 0x05
    u32 reg_move0_dest_start_addr_l     :16;
    u32                                 :16;
    // 0x06
    u32 reg_move0_dest_start_addr_h     :16;
    u32                                 :16;
    // 0x07
    u32 reg_move0_total_byte_cnt_l      :16;
    u32                                 :16;
    // 0x08
    u32 reg_move0_total_byte_cnt_h      :12;
    u32                                 :20;
    // 0x09
    u32 reg_move0_offset_src_width_l    :16;
    u32                                 :16;
    // 0x0A
    u32 reg_move0_offset_src_width_h    :12;
    u32                                 :20;
    // 0x0B
    u32 reg_move0_offset_src_offset_l   :16;
    u32                                 :16;
    // 0x0C
    u32 reg_move0_offset_src_offset_h   :12;
    u32                                 :20;
    // 0x0D
    u32 reg_move0_offset_dest_width_l   :16;
    u32                                 :16;
    // 0x0E
    u32 reg_move0_offset_dest_width_h   :12;
    u32                                 :20;
    // 0x0F
    u32 reg_move0_offset_dest_offset_l  :16;
    u32                                 :16;
    // 0x10
    u32 reg_move0_offset_dest_offset_h  :12;
    u32                                 :20;
    // 0x11
    u32 reg_dma_move0_left_byte_l       :16;    // [RO]
    u32                                 :16;
    // 0x12
    u32 reg_dma_move0_left_byte_h       :13;    // [RO]
    u32                                 :19;
    // 0x13
    u32 reg_move1_src_start_addr_l      :16;
    u32                                 :16;
    // 0x14
    u32 reg_move1_src_start_addr_h      :16;
    u32                                 :16;
    // 0x15
    u32 reg_move1_dest_start_addr_l     :16;
    u32                                 :16;
    // 0x16
    u32 reg_move1_dest_start_addr_h     :16;
    u32                                 :16;
    // 0x17
    u32 reg_move1_total_byte_cnt_l      :16;
    u32                                 :16;
    // 0x18
    u32 reg_move1_total_byte_cnt_h      :12;
    u32                                 :20;
    // 0x19
    u32 reg_move1_offset_src_width_l    :16;
    u32                                 :16;
    // 0x1A
    u32 reg_move1_offset_src_width_h    :12;
    u32                                 :20;
    // 0x1B
    u32 reg_move1_offset_src_offset_l   :16;
    u32                                 :16;
    // 0x1C
    u32 reg_move1_offset_src_offset_h   :12;
    u32                                 :20;
    // 0x1D
    u32 reg_move1_offset_dest_width_l   :16;
    u32                                 :16;
    // 0x1E
    u32 reg_move1_offset_dest_width_h   :12;
    u32                                 :20;
    // 0x1F
    u32 reg_move1_offset_dest_offset_l  :16;
    u32                                 :16;
    // 0x20
    u32 reg_move1_offset_dest_offset_h  :12;
    u32                                 :20;
    // 0x21
    u32 reg_dma_move1_left_byte_l       :16;
    u32                                 :16;
    // 0x22
    u32 reg_dma_move1_left_byte_h       :13;
    u32                                 :19;
    // 0x23
    u32 reg_dummy                       :16;
    u32                                 :16;
    // 0x24
    u32 reg_dma_mov_sw_rst              :2;     // [WO]
    u32                                 :30;
    // 0x25
    u32 reg_dma02mi_priority_mask       :1;
    u32 reg_dma12mi_priority_mask       :1;
    u32                                 :30;
    // 0x26
    u32 reg_dma_irq_mask                :2;
    u32                                 :30;
    // 0x27
    u32 reg_dma_irq_force               :2;
    u32                                 :30;
    // 0x28
    u32 reg_dma_irq_clr                 :2;
    u32                                 :30;
    // 0x29
    u32 reg_dma_irq_select              :1;
    u32                                 :31;
    // 0x2A
    u32 reg_dma_irq_final_status        :2;     // [RO]
    u32                                 :30;
    // 0x2B
    u32 reg_dma_irq_raw_status          :2;     // [RO]
    u32                                 :30;
        #define DMAGEN_INT_MOVE0_DONE   (0x01)
        #define DMAGEN_INT_MOVE1_DONE   (0x02)
    // 0x2C
    u32 reg_dma_probe_sel               :8;
    u32                                 :24;
    // 0x2D
    u32 reg_dma_probe_l                 :16;    // [RO]
    u32                                 :16;
    // 0x2E
    u32 reg_dma_probe_h                 :8;     // [RO]
    u32                                 :24;
    // 0x2F
    u32 reg_dma_bist_fail_rd            :2;     // [RO]
    u32                                 :30;
} KeDmaGen_t;

extern volatile KeDmaGen_t* const g_ptKeDmaGen;

#endif // __KERNEL_DMAGEN_H__

