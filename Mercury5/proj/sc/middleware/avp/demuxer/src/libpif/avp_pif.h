/* Hercules+++ */
#ifndef __PIF_H__
#define __PIF_H__

#include "avp_pif_reg.h"

#ifdef ECO_CONFIG
  #include "avp_pif_driver.h"
#endif



/***************************************************************
*
*	type
*
***************************************************************/

typedef unsigned long pif_reg_t;
typedef unsigned char pif_sid_t;
typedef unsigned long pif_addr_t;
typedef unsigned char pif_err_t; /* PIF_E_XXX */
typedef unsigned short pif_flags_t;

#include "avp_pif_os.h"

/***************************************************************
*
*	flags
*
***************************************************************/

#define PIF_F_READY	(1 << 0)
#define PIF_F_LOCK	(1 << 1)
#define PIF_F_DAR		(1 << 2)
#define PIF_F_DOUBLE_WORD	(1 << 3)
#define PIF_F_STREAM_MODE	(1 << 4)
#define PIF_F_USE_B_BANK	(1 << 5)
#define PIF_F_BLOCKING      (1 << 7)
#define PIF_F_WAIT_FOR_COMPLETE      (1 << 8)
#define PIF_F_HOLD_FIRE (1 << 9)

/***************************************************************
*
*	error
*
***************************************************************/

#define PIF_E_NONE	0
#define PIF_E_HW_ERROR	1
#define PIF_E_BUSY	2
#define PIF_E_REMOTE_BUSY	3
#define PIF_E_NOT_READY	4
#define PIF_E_HW_TIMEOUT	5
#define PIF_E_PARAM	6
#define PIF_E_INTERNAL	7
#define PIF_E_NOT_SUPPORT	8


/***************************************************************
*
*	error
*
***************************************************************/

typedef enum {
	PIF_ACCESS_TYPE_NORMAL = 0,
	PIF_ACCESS_TYPE_BLOCK,
	PIF_ACCESS_TYPE_SLAVE
} pif_access_type_t;


/***************************************************************
*
*	common macro
*
***************************************************************/

#if (PIF_4A_SUPPORT && !PIF_3A3B_SUPPORT)
#define PIF_STREAM_ACCESS   1
#elif (!PIF_4A_SUPPORT && PIF_3A3B_SUPPORT)
#define PIF_STREAM_ACCESS   0
#else
#define PIF_STREAM_ACCESS	(pif_cb.flags & PIF_F_STREAM_MODE)
#endif


/*
 * dma
 */
typedef unsigned long pif_dma_addr_t;
typedef unsigned short pif_dma_len_t;
#if PIF_STREAM_ACCESS
typedef unsigned short pif_dma_len_t2;
#else
typedef unsigned long pif_dma_len_t2;
#endif

/***************************************************************
*
*	marco for master
*
***************************************************************/

/*
 * register address convert
 */
#if PIF_B_BANK_SUPPORT
#define MPIF_R_ADDR_CONVERT(addr)       pif_reg_m_addr_convert(addr)
#else
#define MPIF_R_ADDR_CONVERT(addr)       (addr)
#endif

/*
 * register read / write
 */
#define MPIF_R_MASK(reg)	((pif_reg_t)(((1 << MPIF_R_ ## reg ## _LEN) - 1) << (MPIF_R_ ## reg ## _OFFSET)))

#define MPIF_R_READ(reg, val)	do { \
								val = (pif_reg_t) (((*(volatile pif_riu_t *)(MPIF_R_BASE + (MPIF_R_ADDR_CONVERT(MPIF_R_ ## reg ## _ADDR) << 2))) & MPIF_R_MASK(reg)) >> MPIF_R_ ## reg ## _OFFSET); \
							} while (0)

#define MPIF_R_WRITE(reg, val)	do { \
									pif_reg_t __reg; \
									HAL_READ_UINT16(MPIF_R_BASE + ((MPIF_R_ADDR_CONVERT(MPIF_R_ ## reg ## _ADDR)) << 2), __reg); \
									__reg &= ~MPIF_R_MASK(reg); \
									__reg |= (((pif_reg_t)val <<  MPIF_R_ ## reg ## _OFFSET) & MPIF_R_MASK(reg)); \
									HAL_WRITE_UINT16(MPIF_R_BASE + ((MPIF_R_ADDR_CONVERT(MPIF_R_ ## reg ## _ADDR)) << 2), __reg); \
								} while(0)

/*
 * cache manipulation
 */
#define MPIF_R_INIT_CACHE(cache)	(cache = 0)

#define MPIF_R_READ_CACHE(cache, reg, val)	do { \
								val = (pif_reg_t) ((cache & MPIF_R_MASK(reg)) >> MPIF_R_ ## reg ## _OFFSET); \
							} while (0)

#define MPIF_R_WRITE_CACHE(cache, reg, val)	do { \
									cache &= ~MPIF_R_MASK(reg); \
									cache |= (((pif_reg_t)val <<  MPIF_R_ ## reg ## _OFFSET) & MPIF_R_MASK(reg)); \
								} while(0)

#define MPIF_R_OR_CACHE(cache, reg, val)	do { \
									cache |= (((pif_reg_t)val <<  MPIF_R_ ## reg ## _OFFSET) & MPIF_R_MASK(reg)); \
								} while(0)

#define MPIF_R_ASSIGN_CACHE(cache, reg, val)	do { \
									cache = (((pif_reg_t)val <<  MPIF_R_ ## reg ## _OFFSET) & MPIF_R_MASK(reg)); \
								} while(0)

#define MPIF_R_IS_SET_CACHE(cache, reg) 	(cache & MPIF_R_MASK(reg))

#define MPIF_R_LOAD_CACHE(cache, addr)	HAL_READ_UINT16(MPIF_R_BASE + ((MPIF_R_ADDR_CONVERT(addr)) << 2), cache);

#define MPIF_R_STORE_CACHE(cache, addr)	HAL_WRITE_UINT16(MPIF_R_BASE + ((MPIF_R_ADDR_CONVERT(addr)) << 2), cache);



/***************************************************************
*
*	slave macro
*
***************************************************************/

/*
 * register address convert
 */
#if PIF_B_BANK_SUPPORT
#define SPIF_R_ADDR_CONVERT(addr)       pif_reg_s_addr_convert(addr)
#else
#define SPIF_R_ADDR_CONVERT(addr)         (addr)
#endif

/*
 * register read / write
 */
#define SPIF_R_MASK(reg)	((pif_reg_t)(((1 << SPIF_R_ ## reg ## _LEN) - 1) << (SPIF_R_ ## reg ## _OFFSET)))

#define SPIF_R_READ(reg, val)	do { \
								val = (pif_reg_t) (((*(volatile pif_riu_t *)(SPIF_R_BASE + (SPIF_R_ADDR_CONVERT(SPIF_R_ ## reg ## _ADDR) << 2))) & SPIF_R_MASK(reg)) >> SPIF_R_ ## reg ## _OFFSET); \
							} while (0)


#define SPIF_R_WRITE(reg, val)	do { \
									pif_reg_t __reg; \
									HAL_READ_UINT16(SPIF_R_BASE + SPIF_R_ADDR_CONVERT(SPIF_R_ ## reg ## _ADDR << 2), __reg); \
									__reg &= ~SPIF_R_MASK(reg); \
									__reg |= (((pif_reg_t)val <<  SPIF_R_ ## reg ## _OFFSET) & SPIF_R_MASK(reg)); \
									HAL_WRITE_UINT16(SPIF_R_BASE + SPIF_R_ADDR_CONVERT(SPIF_R_ ## reg ## _ADDR << 2), __reg); \
								} while(0)
/*
 * cache manipulation
 */

#define SPIF_R_INIT_CACHE(cache)	(cache = 0)

#define SPIF_R_READ_CACHE(cache, reg, val)	do { \
								val = (pif_reg_t) ((cache & SPIF_R_MASK(reg)) >> SPIF_R_ ## reg ## _OFFSET); \
							} while (0)

#define SPIF_R_WRITE_CACHE(cache, reg, val)	do { \
									cache &= ~SPIF_R_MASK(reg); \
									cache |= (((pif_reg_t)val <<  SPIF_R_ ## reg ## _OFFSET) & SPIF_R_MASK(reg)); \
								} while(0)

#define SPIF_R_LOAD_CACHE(cache, addr)	HAL_READ_UINT16(SPIF_R_BASE + ((SPIF_R_ADDR_CONVERT(addr)) << 2), cache);

#define SPIF_R_STORE_CACHE(cache, addr)	HAL_WRITE_UINT16(SPIF_R_BASE + ((SPIF_R_ADDR_CONVERT(addr)) << 2), cache);


/***************************************************************
*
*	data structure
*
***************************************************************/

typedef struct pif_stat_s {
	unsigned long intr_cnt;
	unsigned long retry_cnt;
	unsigned long err_cnt_read32;
	unsigned long err_cnt_write32;
	unsigned long access;
	unsigned long access_read;
	unsigned long access_write;
	unsigned long access32;
	unsigned long access32_read;
	unsigned long access32_write;
	unsigned long max_access;
	unsigned long max_access32;
	unsigned long max_read32;
	unsigned long max_write32;
	unsigned long start;
} pif_stat_t;

typedef struct pif_cb_s {
    /*
    * interrupt handler
    */
    void (*intr_cb)(void);
    unsigned char event_status;
    pif_intr_state_t intr_state;

    /*
    * read data
    */
    pif_reg_t *read_buf_p;

    /*
    * user data
    */
    void (*user_cb)(pif_err_t status, void *data_p);
    void *user_data_p;

    /*
    * statistics
    */
    pif_stat_t	stat;

    pif_flags_t flags; /* PIF_F_XXX */
} pif_cb_t;

typedef struct pif_config_s {
    unsigned char width;
} pif_config_t;


/***************************************************************
*
*	function prototypes
*
***************************************************************/

/*
 * init and reset
 */
pif_err_t pif_init(void) __attribute__((longcall));
void pif_hw_init(void) __attribute__((longcall));
pif_err_t pif_slave_init(pif_sid_t sid, pif_config_t *config_p) __attribute__((longcall));
unsigned long pif_reg_m_addr_convert(unsigned long addr) __attribute__((longcall));

#ifdef __cplusplus
extern "C" {
#endif
pif_err_t pif_write_slave(pif_sid_t sid, pif_addr_t addr, pif_reg_t data);
pif_err_t pif_read_slave(pif_sid_t sid, pif_addr_t addr, pif_reg_t *data_p);

pif_err_t pif_slave_dar_path_user(pif_sid_t sid, unsigned char enable);


/*
 * read
 */
pif_err_t pif_read_req(pif_sid_t sid, pif_addr_t addr, pif_reg_t *val_p, void (*user_cb)(pif_err_t status, void *user_data_p), void *user_data_p);
pif_err_t pif_read(pif_sid_t sid, pif_addr_t addr, pif_reg_t *val_p);
pif_err_t pif_read32(pif_sid_t sid, pif_addr_t addr, pif_reg_t *val_p);
pif_err_t pif_read32_enhanced(pif_sid_t sid, pif_addr_t addr, pif_reg_t *val_p);

/*
 * write
 */
pif_err_t pif_write_req(pif_sid_t sid, pif_addr_t addr, pif_reg_t val, void (*user_cb)(pif_err_t status, void *user_data_p), void *user_data_p);
pif_err_t pif_write(pif_sid_t sid, pif_addr_t addr, pif_reg_t val);
pif_err_t pif_write32(pif_sid_t sid, pif_addr_t addr, pif_reg_t val);
pif_err_t pif_write32_enhanced(pif_sid_t sid, pif_addr_t addr, pif_reg_t data);

/*
 * block read
 */
pif_err_t pif_block_read(pif_sid_t sid, pif_dma_addr_t addr, pif_dma_len_t2 len);
pif_err_t pif_block_read_nonblocking(pif_sid_t sid, pif_dma_addr_t addr, pif_dma_len_t2 len);
pif_err_t pif_block_read_req(pif_sid_t sid, pif_dma_addr_t addr, pif_dma_len_t2 len, void (*user_cb)(pif_err_t status, void *user_data_p), void *user_data_p);

/*
 * block write
 */
pif_err_t pif_block_write(pif_sid_t sid, pif_dma_addr_t addr, pif_dma_len_t2 len);
pif_err_t pif_block_write_nonblocking(pif_sid_t sid, pif_dma_addr_t addr, pif_dma_len_t2 len);
pif_err_t pif_block_write_req(pif_sid_t sid, pif_dma_addr_t addr, pif_dma_len_t2 len, void (*user_cb)(pif_err_t status, void *user_data_p), void *user_data_p);

pif_err_t pif_block_wait_for_complete(void);

/*
 * interrupt handler
 */
void pif_intr_handler(void);

/***************************************************************
*
*	control block (internal use)
*
***************************************************************/

extern pif_cb_t pif_cb;

/*
 * debug
 */
void pif_dump_register();
#ifdef __cplusplus
}
#endif


#endif	/* #ifndef __PIF_H__ */

