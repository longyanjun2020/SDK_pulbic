#ifndef __R2_SYSTEM_H__
#define __R2_SYSTEM_H__

#include <r2_spr_defs.h>
#include <cpu_mem_map_g1.h>

/* R2_Core_register access base*/
//#define AHB32_IO_BASE 0xe488 /* fix me */


#define CFG_MALLOC_SIZE		(4*1024*1024)

#define CFG_PRINT_BUFFER_SIZE	1024

#define readb(addr)		(*(volatile unsigned char *) (addr))
#define readw(addr)		(*(volatile unsigned short *) (addr))
#define readl(addr)		(*(volatile unsigned int *) (addr))

#define writeb(b,addr)		((*(volatile unsigned char *) (addr)) = (b))
#define writew(b,addr)		((*(volatile unsigned short *) (addr)) = (b))
#define writel(b,addr)		((*(volatile unsigned int *) (addr)) = (b))

/* Memory bariers */
#define barrier()		__asm__ __volatile__("": : :"memory")
#define mb()			barrier()
#define rmb()			mb()
#define wmb()			mb()
#define read_barrier_depends()	do { } while(0)
#define set_mb(var, value)	do { var = value; mb(); } while (0)
#define set_wmb(var, value)	do { var = value; wmb(); } while (0)

#define nop()			__asm__ __volatile__ ("l.nop"::)

static inline unsigned long get_return_address(void)
{
	unsigned long ret;
	asm volatile("l.addi	%0, r9, 0" : "=r" (ret));
	return ret;
}

static inline void local_irq_disable(void)
{
	unsigned long sr;
	asm volatile("l.mfspr	%0,r0,%1" : "=r"(sr) : "i"(SPR_SR));
	sr &= ~(SPR_SR_TEE | SPR_SR_IEE);
	asm volatile("l.mtspr	r0,%0,%1" :: "r"(sr), "i"(SPR_SR));
}

static inline void local_irq_enable(void)
{
	unsigned long sr;
	asm volatile("l.mfspr	%0,r0,%1" : "=r"(sr) : "i"(SPR_SR));
	sr |= (SPR_SR_TEE | SPR_SR_IEE);
	asm volatile("l.mtspr	r0,%0,%1" :: "r"(sr), "i"(SPR_SR));
}

static inline void local_irq_restore(unsigned long flags)
{
	asm volatile("l.mtspr	r0,%0,%1" :: "r"(flags), "i"(SPR_SR));
}

#define local_irq_save(flags)		\
 do { \
	unsigned long sr; \
	asm volatile("l.mfspr	%0,r0,%1" : "=r"(flags) : "i"(SPR_SR)); \
	sr = flags & ~(SPR_SR_TEE | SPR_SR_IEE); \
	asm volatile("l.mtspr	r0,%0,%1" :: "r"(sr), "i"(SPR_SR)); \
 } while(0)

#define local_save_flags(flags)		\
	asm volatile("l.mfspr	%0,r0,%1" : "=r"(flags) : "i"(SPR_SR))

struct __xchg_dummy { unsigned long a[100]; };
#define __xg(x)			((volatile struct __xchg_dummy *)(x))
#define xchg(ptr,x)		((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
#define tas(ptr)		(xchg((ptr),1))

static inline unsigned long __xchg(unsigned long x, volatile void * ptr, int size)
{
	unsigned long tmp, flags;

	local_irq_save(flags);
	switch (size) {
	case 1:
		__asm__ __volatile__
		("l.lbz %0,%2\n\t"
		 "l.sb %2,%1"
		 : "=&r" (tmp) : "r" (x), "m" (*__xg(ptr)) : "memory");
		break;
	case 2:
		__asm__ __volatile__
		("l.lhz %0,%2\n\t"
		 "l.sh %2,%1"
		 : "=&r" (tmp) : "r" (x), "m" (*__xg(ptr)) : "memory");
		break;
	case 4:
		__asm__ __volatile__
		("l.lwz %0,%2\n\t"
		 "l.sw %2,%1"
		 : "=&r" (tmp) : "r" (x), "m" (*__xg(ptr)) : "memory");
		break;
	}
	local_irq_restore(flags);
	return tmp;
}

static inline void *xchg_ptr(void * m, void * val)
{
	return (void *) __xchg((unsigned long)m, val, sizeof(unsigned long));
}

static inline void mtspr(unsigned long add, unsigned long val)
{
#if 1
	asm volatile ("l.mtspr %0,%1,0" :: "r" (add), "r" (val));
#else
	if (__builtin_constant_p(add) && (add <= 65535))
		asm volatile ("l.mtspr r0,%1,%0" :: "i" (add), "r" (val));
	else
		asm volatile ("l.mtspr %0,%1,0" :: "r" (add), "r" (val));
#endif
}

static inline unsigned long mfspr(unsigned long add)
{
	unsigned long ret;
#if 1
	asm volatile ("l.mfspr %0,%1,0" : "=r" (ret) : "r" (add));
#else
	if (__builtin_constant_p(add) && ((add) <= 65535))
		asm volatile ("l.mfspr %0,r0,%1" : "=r" (ret) : "i" (add));
	else
		asm volatile ("l.mfspr %0,%1,0" : "=r" (ret) : "r" (add));
#endif
	return ret;
}


static inline unsigned short r2core_reg_read(unsigned short reg)
{
  unsigned long addr = MMP_R2_CORE_BASE_ADD + ((reg+0x40) << 2);
  return *((volatile unsigned short*) addr);
}

static void inline r2core_reg_write(unsigned short reg, unsigned short val)
{
  unsigned long addr = MMP_R2_CORE_BASE_ADD + ((reg+0x40) << 2);
  *((volatile unsigned short*) addr) = val;
}

static inline unsigned short r2cpu_reg_read(unsigned short reg)
{
  unsigned long addr = MMP_R2_CORE_BASE_ADD  + (reg << 2);
  return *((volatile unsigned short*) addr);
}

static void inline r2cpu_reg_write(unsigned short reg, unsigned short val)
{
  unsigned long addr = MMP_R2_CORE_BASE_ADD + (reg << 2);
  *((volatile unsigned short*) addr) = val;
}

static void inline r2_enter_wfi(void)
{
  
  unsigned long int tmp;

#if defined(SIMULATION_DSP_BUILD) || defined(SIMULATION_MCU_BUILD)  
  tmp = *((volatile unsigned long int *)(0x50001c0c));
  tmp |= (0x01 << 10);
  *((volatile unsigned long int *)(0x50001c0c)) = tmp;
#endif
  
  asm volatile ("bg.syncwritebuffer");
  
  while((r2cpu_reg_read(0x16) & 0x02) == 0);

  tmp = r2core_reg_read(0x2B);
  tmp |= (0x01 << 10);
  r2core_reg_write(0x2B, tmp);

  tmp = mfspr(SPR_PMR);
  tmp |= (0x01 << 6);
  mtspr(SPR_PMR, tmp); 
  tmp &= ~(0x01 << 6);
  mtspr(SPR_PMR, tmp); 

}




#define irqs_disabled() ((mfspr(SPR_SR) & (SPR_SR_IEE | SPR_SR_TEE)) == 0)

extern const unsigned long _malloc_start;
extern const unsigned long _malloc_end;
extern const unsigned long _stack_top;
extern const unsigned long sys_malloc_start;
extern const unsigned long sys_stack_top;

void    HalUtilIMIParking2MMP(void);
#define drvUtilHaveIMIParking   HalUtilIMIParking2MMP

#define BUG() \
do { \
	printf("BUG: failure at %s:%d/%s()!\n", __FILE__, __LINE__, __FUNCTION__); \
	panic("BUG!"); \
} while (0)

#define BUG_ON(condition) \
do { if (unlikely((condition)!=0)) BUG(); } while(0)

extern void panic(const char *fmt, ...);
extern void hang(void) __attribute__ ((noreturn));

extern void uart_putc(const char c);
extern void uart_puthex(const unsigned long v);
extern void uart_puts(const char *s);

#endif // __R2_SYSTEM_H__
