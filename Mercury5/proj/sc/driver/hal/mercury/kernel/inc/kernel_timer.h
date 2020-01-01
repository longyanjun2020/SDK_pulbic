#ifndef __KERNEL_TIMER_H__
#define __KERNEL_TIMER_H__

/************************************************/
/* Timer registers definition                   */
/************************************************/

typedef struct KeTimer_s
{
	u32	u32_TimerControl;        // 0x0
	u32 u32_TimerStartCnt0;      // 0x4
	u32 u32_TimerPrecision0;     // 0x8
	u32 u32_TimerStartCnt1;      // 0xC
	u32 u32_TimerPrecision1;     // 0x10
	u32 u32_TimerCnt0;           // 0x14
	u32 u32_TimerPcnt0;          // 0x18
	u32 u32_TimerCnt1;           // 0x1C
	u32 u32_TimerPcnt1;          // 0x20
	u32 u32_TimerIrqMask;        // 0x24
	u32 u32_TimerIrqForce;       // 0x28
	u32 u32_TimerIrqClr;         // 0x2C
	u32 u32_TimerIrqRawStatus;   // 0x30
	u32 u32_TimerIrqFinalStatus; // 0x34
	u32 u32_TimerSwRstn;         // 0x38
} KeTimer_t;


// Timer Control
#define TIMER0_ENABLE           0x0001
#define TIMER0_RELOAD           0x0002
#define TIMER1_ENABLE           ((u32)0x01 << 0x08)
#define TIMER1_RELOAD           ((u32)0x02 << 0x08)

// Timer Start Counter
#define TIMER_START_CNT_POS		  0
#define TIMER_START_CNT_MASK    ((u32)0xFFFF << TIMER_START_CNT_POS)

// Timer Precision
#define TIMER_PRECISIO_CNT_POS  0
#define TIMER_PRECISIO_CNT_MASK ((u32)0xFFFF << TIMER_PRECISIO_CNT_POS)

// Timer Counter Reading
#define TIMER_COUNTER_POS       0
#define TIMER_COUNTER_MASK      ((u32)0xFFFF << TIMER_COUNTER_POS)

// Timer Irq Mask (0: Unmak, 1: Mask)
#define TIMER0_IRQ_MASK         0x0001
#define TIMER1_IRQ_MASK         ((u32)0x01 << 0x01)

// Timer Irq Force
#define TIMER0_IRQ_FORCE        0x0001
#define TIMER1_IRQ_FORCE        ((u32)0x01 << 0x01)

// Timer Irq Clear
#define TIMER0_IRQ_CLEAR        0x0001
#define TIMER1_IRQ_CLEAR        ((u32)0x01 << 0x01)

// Timer Raw Status Reading (Raw status just toggled
#define TIMER0_IRQ_RAW_STATUS   0x0001
#define TIMER1_IRQ_RAW_STATUS   ((u32)0x01 << 0x01)

// Timer Final Status Reading (
#define TIMER0_IRQ_FINAL_STATUS 0x0001
#define TIMER1_IRQ_FINAL_STATUS ((u32)0x01 << 0x01)

extern volatile KeTimer_t* const g_ptKeTimer;

#endif /*__KERNEL_TIMER_H__*/

