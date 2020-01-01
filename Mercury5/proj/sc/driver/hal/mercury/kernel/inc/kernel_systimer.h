#ifndef __KERNEL_SYSTIMER_H__
#define __KERNEL_SYSTIMER_H__

/************************************************/
/* SYS TIMER registers definition               */
/************************************************/

typedef struct KeInfinteTimer_t
{
    /* [0x00] */
    u16 reg_timer_en                :1;
    u16 reg_timer_trig              :1;
    u16 rsvd1                       :6;
    u16 reg_timer_int_en            :1;
    u16 rsvd2                       :7;
    u16                             :16;
    /* [0x04] */
    u16 reg_timer_hit               :1;
    u16 rsvd3                       :15;
    u16                             :16;
    /* [0x08] */
    u16 reg_timer_max_low           :16;
    u16                             :16;
    /* [0x0C] */
    u16 reg_timer_max_high          :16;
    u16                             :16;
    /* [0x10] */
    u16 reg_timer_cap_low           :16;
    u16                             :16;
    /* [0x14] */
    u16 reg_timer_cap_high          :16;
    u16                             :16;
} KeInfinteTimer_t;

extern volatile KeInfinteTimer_t    * const g_ptKeInfinteTimer0;
extern volatile KeInfinteTimer_t    * const g_ptKeInfinteTimer1;
extern volatile KeInfinteTimer_t    * const g_ptKeInfinteTimer2;

typedef struct KeWdtTimer_t
{
    /* [0x00] */
    u16 reg_wdt_clr                 :1;
    u16 rsvd1                       :15;
    u16                             :16;
    /* [0x01] */
    u16                             :16;
    u16                             :16;
    /* [0x02] */
    u16 reg_wdt_rst_flag            :1;
    u16 rsvd2                       :7;
    u16 reg_wdt_rst_len             :8;
    u16                             :16;
    /* [0x03] */
    u16 reg_wdt_int                 :16;
    u16                             :16;
    /* [0x04] */
    u16 reg_wdt_max_low             :16;
    u16                             :16;
    /* [0x05] */
    u16 reg_wdt_max_high            :16;
    u16                             :16;
} KeWdtTimer_t;

extern volatile KeWdtTimer_t    * const g_ptKeWdtTimer;

#endif /*__KERNEL_SYSTIMER_H__*/

