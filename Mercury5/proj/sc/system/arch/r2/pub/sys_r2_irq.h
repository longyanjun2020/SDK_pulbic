#ifndef __SYS_R2_LIB_H__
#define __SYS_R2_LIB_H__


#define INTERRUPT_STACK_SIZE 4096
#define NR_IRQS 20

#define IRQ_FLAGS_VALID		0x00000001 // bit 0
#define IRQ_FLAGS_ENABLE	0x00000002 // bit 1

#define PRIORITY_X_BIGGER_THAN_Y(x,y) (x<y) //higher priority is with smaller value

typedef void (*PfnR2PicISR)(void);

struct irq_handler_t
{
    unsigned int flags;
    unsigned int irq;
    unsigned int priority_highest;
    unsigned int priority_lowest;
    PfnR2PicISR  handler;
//    void (*handler)(void);
    unsigned char wakeup;
    void *arg;
};

typedef enum {
    R2PIC_PRIORITY_0 = 0,
    R2PIC_PRIORITY_1,
    R2PIC_PRIORITY_2,
    R2PIC_PRIORITY_3,
    R2PIC_PRIORITY_4,
    R2PIC_PRIORITY_5,
    R2PIC_PRIORITY_6,
    R2PIC_PRIORITY_7,
    R2PIC_PRIORITY_8,
    R2PIC_PRIORITY_9,
    R2PIC_PRIORITY_10,
    R2PIC_PRIORITY_11,
    R2PIC_PRIORITY_12,
    R2PIC_PRIORITY_13,
    R2PIC_PRIORITY_14,
    R2PIC_PRIORITY_15,
    R2PIC_PRIORITY_MAX = R2PIC_PRIORITY_15,
    R2PIC_PRIORITY_INVALID
} R2PicPriority_e;



typedef struct
{
    R2PicPriority_e    ePriority_highest;
    R2PicPriority_e    ePriority_lowest;
    unsigned char      bWakeUp;
    PfnR2PicISR        pfnIsr;
} R2PicParam_t;

enum {

    R2_PIC_NMI_0 = 0,
    R2_PIC_NMI_1,
    R2_PIC_FIQ,
    R2_PIC_BT_TIMER_0,
    R2_PIC_BT_TIMER_1,
    R2_PIC_IRQ,
    R2_PIC_MCU2MMP,
    R2_PIC_DSP2MMP,
    R2_PIC_ETMI_0_A,
    R2_PIC_ETMI_0_B,
    R2_PIC_ETMI_1_A,
    R2_PIC_ETMI_1_B,
    R2_PIC_R2DMA_INT = 16,
    R2_PIC_INTER_UART = 19,  
    R2_PIC_MAX  

};

extern void R2PicInitController();
extern void R2PicInitialize(R2PicParam_t *ptR2PicParam, unsigned long int nR2PicNumber);
extern void R2PicMask(unsigned long int R2PicNumber);
extern void R2PicUnmask(unsigned long int R2PicNumber);
extern void R2PicAck(unsigned long int R2PicNumber);
extern void R2PicClear(unsigned long int R2PicNumber);
extern void pic_priority_check (unsigned int R2PicPriority_e, unsigned int pic_num);
extern void R2PicConfigDefaultHandlers(void);

#endif /* __SYS_R2_LIB_H__ */
