#ifndef __ARM_GIC__
#define __ARM_GIC__

#include "cpu_mem_map.hc"


/* CPU interface register map */
#define GICC_CTLR			0x00
#define GICC_PMR			0x04
#define GICC_BPR    		0x08
#define GICC_IAR			0x0c
#define GICC_EOIR			0x10
#define GICC_RPR    		0x14
#define GICC_HPPIR			0x18
#define GICC_ABPR			0x1c
#define GICC_APR			0xd0
#define GICC_IIDR			0xfc

/* CPU interface register settings */
#define GICC_ENABLE			0x1
#define GICC_INT_PRI_THRESHOLD		0xf0
#define GICC_IAR_INT_ID_MASK		0x3ff
#define GICC_INT_SPURIOUS		1023
#define GICC_DIS_BYPASS_MASK		0x1e0

/* Distributor register map */
#define GICD_CTLR				0x000
#define GICD_TYPER				0x004
#define GICD_IGROUPR			0x080
#define GICD_ISENABLER			0x100
#define GICD_ICENABLER			0x180
#define GICD_ISPENDR			0x200
#define GICD_ICPENDR			0x280
#define GICD_ISACTIVER			0x300
#define GICD_ICACTIVER			0x380
#define GICD_IPRORITYR			0x400
#define GICD_ITARGETSR			0x800
#define GICD_ICFGR				0xc00
#define GICD_SGIR				0xf00
#define GICD_CPENDSGIR			0xf10
#define GICD_SPENDSGIR			0xf20

/* Distributor register settings */
#define GICD_ENABLE			0x1
#define GICD_DISABLE			0x0
#define GICD_INT_ACTLOW_LVLTRIG		0x0
#define GICD_INT_EN_CLR_X32		0xffffffff
#define GICD_INT_EN_SET_SGI		0x0000ffff
#define GICD_INT_EN_CLR_PPI		0xffff0000
#define GICD_INT_DEF_PRI		0xa0
#define GICD_INT_DEF_PRI_X4		((GICD_INT_DEF_PRI << 24) |\
    (GICD_INT_DEF_PRI << 16) |\
    (GICD_INT_DEF_PRI << 8) |\
    GICD_INT_DEF_PRI)

#define armINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS 		( MS_BASE_INTERRUPT_CONTROLLER_PA + MS_INTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET )

#define GICD_READB(a)  (*(volatile unsigned char *)(u32)(MS_BASE_INTERRUPT_CONTROLLER_PA+a))
#define GICD_READL(a)  (*(volatile unsigned int *)(u32)(MS_BASE_INTERRUPT_CONTROLLER_PA+a))
#define GICD_WRITEB(a,v)  (*(volatile unsigned char *)(u32)(MS_BASE_INTERRUPT_CONTROLLER_PA+a) = (v))
#define GICD_WRITEL(a,v)  (*(volatile unsigned int *)(u32)(MS_BASE_INTERRUPT_CONTROLLER_PA+a) = (v))

#define GICC_READB(a)  (*(volatile unsigned char *)(u32)(armINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS+a))
#define GICC_READL(a)  (*(volatile unsigned int *)(u32)(armINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS+a))
#define GICC_WRITEB(a,v)  (*(volatile unsigned char *)(u32)(armINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS+a) = (v))
#define GICC_WRITEL(a,v)  (*(volatile unsigned int *)(u32)(armINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS+a) =(v))

#endif

