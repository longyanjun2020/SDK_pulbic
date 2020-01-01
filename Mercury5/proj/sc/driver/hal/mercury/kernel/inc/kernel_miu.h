#ifndef __KERNEL_MIU_H__
#define __KERNEL_MIU_H__

/************************************************/
/* GARB: Group aribiter                         */
/************************************************/

typedef struct KeMiuGarb_s {
    /* [0x00] */
    u32 reg_marb_status            :16 ; /// Current imi status
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_marb_status_ctrl        :8 ; /// Control status:  0: arb_token
    u32 reg_marb_no_resp            :4 ; ///	No response limit (4bit, 0 = Off)
    u32 :3 ;
	u32 reg_marb_reset             :1;  ///Reset
	u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_marb_ignore_last    :12; /// Ignore last signal from client
    u32 :20; /// [0x02]
    /* [0x03] */
	u32 reg_marb_ignore_pr      :12; ///Ignore pr signal from client
	u32 :20; ///[0x03]
    /* [0x04] */
	u32 reg_marb_force_pr        :12; ///Force high priority for client
	u32 :20; ///[0x04]
    /* [0x05] */
	u32 reg_marb_burst_read_size  :8; ///Max burst read size (7bit, n + 1, [7] = enable)
	u32 reg_marb_burst_write_size :8; ///Max burst write size (7bit, n + 1,  [7] = enable)
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_rq_mask                   :16; /// request mask
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_marb_last_rdy_off              :1 ; /// Trun off rdy for IP after last
    u32 reg_marb_type_mode              :1 ; /// Trun on type mode
    u32 reg_marb_mask_force              :1 ; /// Mask force mode
    u32 :1;
    u32 reg_marb_spare              :12 ; /// Spare
    u32 :16; /// [0x07]

} KeMiuGarb_t;

extern volatile KeMiuGarb_t * const g_ptKeMiuGarb0;
extern volatile KeMiuGarb_t * const g_ptKeMiuGarb1;
//extern volatile KeMiuGarb_t * const g_ptKeMiuGarb2;
//extern volatile KeMiuGarb_t * const g_ptKeMiuGarb3;
extern volatile KeMiuGarb_t * const g_ptKeMiuGarbImi2;
//extern volatile KeMiuGarb_t * const g_ptKeMiuGarbImi3;

#endif /*__KERNEL_MIU_H__*/
