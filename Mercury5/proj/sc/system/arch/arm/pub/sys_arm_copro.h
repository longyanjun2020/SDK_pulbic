/****************************************************************************/
/*  File    : sys_arm_copro.h                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   :                    */
/*                                                                          */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/*----------+--------+------+-----------------------------------------------*/
/****************************************************************************/

#ifndef __SYS_ARM_COMMON_H__
#define __SYS_ARM_COMMON_H__

//#include "cpu_mem_map.hc"
#include "sys_MsWrapper_cus_os_int_pub.h"


/* region size definitions (to be used as region_size argument)*/
#define REGION_4KB   0x0B
#define REGION_8KB   0x0C
#define REGION_16KB  0x0D
#define REGION_32KB  0x0E
#define REGION_64KB  0x0F
#define REGION_128KB 0x10
#define REGION_256KB 0x11
#define REGION_512KB 0x12
#define REGION_1MB   0x13
#define REGION_2MB   0x14
#define REGION_4MB   0x15
#define REGION_8MB   0x16
#define REGION_16MB  0x17
#define REGION_32MB  0x18
#define REGION_64MB  0x19
#define REGION_128MB 0x1A
#define REGION_256MB 0x1B
#define REGION_512MB 0x1C
#define REGION_1GB   0x1D
#define REGION_2GB   0x1E
#define REGION_4GB   0x1F

/* region access (to be used as region_size argument)*/
/* format is <Priviledge_acces>_<User_access>        */
#define REGION_NO_NO 0x0  // no access
#define REGION_RW_NO 0x1
#define REGION_RW_RO 0x2
#define REGION_RW_RW 0x3

#define DOMAIN_0    (0x0<<5)
#define DOMAIN_15    (0xF<<5)
#define DOMAIN_FIELD (0xF<<5)

#define PAGE_TRANSLATION_FAULT  0x7
#define PAGE_PERMISSION_FAULT   0xF

#define SECTION_TRANSLATION_FAULT  0x5
#define SECTION_PERMISSION_FAULT   0xF

extern void __enable_icache(void);
extern void __disable_icache(void);
extern u32 __enable_mmu(u32 *);
extern void __disable_mmu(void);
extern void __enable_itcm(u32);
extern void __enable_itcm926(u32,u32,u32);
extern void __clean_cache(void);
extern void __activate_ITCM(void);
extern void __activate_DTCM(void);
extern void __deactivate_ITCM(void);
extern void __deactivate_DTCM(void);

/***************************************************************************************
*    CP15 register access                                                              *
*                                                                                      *
*                                                                                      *
***************************************************************************************/

extern u32 read_cpsr(void);

extern void write_cpsr(u32);

extern u32 cp15_read_reg0_id_code (void);

extern u32 cp15_read_reg0_cache_type (void);

extern u32 cp15_read_reg0_tcm_status (void);

extern u32 cp15_read_reg1_control (void);

extern void cp15_write_reg1_control (u32);

extern u32 cp15_read_reg2_dcache_conf (void); // only for 946ES

extern u32 cp15_read_reg2_icache_conf (void); // only for 946ES

extern void cp15_write_reg2_dcache_conf (u32); // only for 946ES

extern void cp15_write_reg2_icache_conf (u32); // only for 946ES

extern u32 cp15_read_reg3_wbuffer_control (void);

extern void cp15_write_reg3_wbuffer_control (u32);

extern u32 cp15_read_reg5_d_access_ext (void);

extern u32 cp15_read_reg5_i_access_ext (void);

extern void cp15_write_reg5_d_access_ext (u32);

extern void cp15_write_reg5_i_access_ext (u32);

extern u32 cp15_read_reg5_d_access (void);

extern u32 cp15_read_reg5_i_access (void);

extern void cp15_write_reg5_d_access (u32);

extern void cp15_write_reg5_i_access (u32);

extern u32 cp15_read_reg6_region (int);

extern void cp15_write_reg6_region (u32,int);

extern void cp15_write_reg7_clean_and_invalidate_data_cache_entry (u32 val);

extern void cp15_write_reg7_invalidate_data_cache_entry (u32 val);

extern void cp15_write_reg7_invalidate_data_cache (void);

extern void cp15_write_reg7_flush_data_cache_entry(u32 val);

extern void cp15_write_reg7_wait_for_interrupt(void);

extern void cp15_write_reg7_drain_write_buffer(void);

extern void cp15_write_reg7_test_clean_invalidate_dcache(void);

extern void cp15_write_reg7_test_clean_dcache(void);


extern void cp15_write_reg7_invalidate_icache(void);

extern void cp15_write_reg8_invalidate_tlb(void);

extern u32 cp15_read_reg2_ttbr (void);

extern void cp15_write_reg2_ttbr (u32 val);

extern u32 cp15_read_reg3_domain_access (void);

extern void cp15_write_reg3_domain_access (u32 val);

extern u32 cp15_read_reg5_i_fault_status (void);

extern void cp15_write_reg5_i_fault_status (u32);

extern u32 cp15_read_reg5_d_fault_status (void);

extern void cp15_write_reg5_d_fault_status (u32);

extern u32 cp15_read_reg6_fault_addr (void);

extern void cp15_write_reg6_fault_addr (u32);

extern u32 cp15_read_reg15_testdebug (void); // This register should be used only for debug

extern void cp15_write_reg15_testdebug (u32); // This register should be used only for debug

extern u32 cp15_read_reg9_dtcm(void);

extern void cp15_write_reg9_dtcm(u32);

extern u32 cp15_read_reg9_itcm(void);

extern void cp15_write_reg9_itcm(u32);

extern void cp15_lock_data_cache_2_3_way(void);

extern void cp15_unlock_data_cache_2_3_way(void);


/*
 *    hgu :
 *    functions to build the translation table and retrieve its base adresse
 *
 */

/*!
 *   \brief error code to specify the result of mmu related function calls.
 */
typedef enum {
  ERR_MMU_NO_ERROR=0,               ///< There was no error
  ERR_MMU_MODIFICATION_NOT_ALLOWED, ///< The modifications are not allowed
  ERR_MMU_INVALID_SEGMENT,          ///< The specified segment is not valid
  ERR_MMU_INVALID_SIZE,             ///< The specified segment size is not valid
  ERR_MMU_INVALID_ATTRIBUTTION,     ///< The specified attribution is not valid
  ERR_MMU_FAILED,                   ///< The function call failed
  ERR_MMU_INVALID_PAGE_TALE         ///< The page table address is 0
} mmu_errorCode_e;

/*!
 *    \brief access protection constants
 */
#ifdef __INFINITY__
/*AP2[15] AP1-0[11:10] */
typedef enum {
  MMU_ACCESSPROTECTION_CUSTOM  = 0, ///< temporarily reserved for coarse table code
  MMU_ACCESSPROTECTION_NO_NO   = 0, ///< The access is customized ( used with the System and Rom flags of the CP15 Control register to tune the access )
  MMU_ACCESSPROTECTION_RW_NO   = 1, ///< The access is Read/Write for privileged accesses and forbiden otherwise
  MMU_ACCESSPROTECTION_RW_RO   = 2, ///< The access is Read/Write for privileged accesses and ReadOnly otherwise
  MMU_ACCESSPROTECTION_RW_RW   = 3, ///< The access is Read/Write
  MMU_ACCESSPROTECTOIN_UN_UN   = 4, ///< Reserved
  MMU_ACCESSPROTECTION_RO_NO   = 5, ///< The access is ReadOnly for privileged accesses  and forbiden otherwise
  MMU_ACCESSPROTECTION_RO_RO   = 6, ///< The access is ReadOnly
  MMU_ACCESSPROTECTION_UN_UN   = 7  ///< Reserved
} mmu_regionAccessType_e;

#else
typedef enum {
  MMU_ACCESSPROTECTION_CUSTOM   = 0, ///< The access is customized ( used with the System and Rom flags of the CP15 Control register to tune the access )
  MMU_ACCESSPROTECTION_RW_NO   = 1, ///< The access is Read/Write for privileged accesses and forbiden otherwise
  MMU_ACCESSPROTECTION_RW_RO   = 2, ///< The access is Read/Write for privileged accesses and ReadOnly otherwise
  MMU_ACCESSPROTECTION_RW_RW   = 3, ///< The access is Read/Write
} mmu_regionAccessType_e;
#endif
extern mmu_errorCode_e imi0_coarse_page_table_init(void);

extern mmu_errorCode_e mmu_coarse_page_table_init_low(u8 mp_or_not);
extern mmu_errorCode_e mmu_coarse_page_table_init_high(void);
extern mmu_errorCode_e mmu_coarse_page_table_config_low(u8 op, u32 start, u8 attr);

/*!
 *   \fn u32 mmu_begin_modify_translation_table(void)
 *
 *   \brief must be called before any modification of the MMU translation table
 *
 *   \return a context to use with the \ref mmu_end_modify_translation_table function
 *
 */
extern  MsIntMask_e mmu_begin_modify_translation_table(void);

/*!
 *   \fn      mmu_errorCode_e mmu_translation_table_reset(u32 domian)
 *
 *   \brief   resets the mmu table to its default values
 *            ( no cached segments, no write buffered segments, no write protected segment )
 *
 *   \return a \ref mmu_errorCode_e that specifies the function call result :
 *    - ERR_MMU_MODIFICATION_NOT_ALLOWED if the function was called but was not prepared by a \ref mmu_begin_modify_translation_table
 *    - ERR_MMU_NO_ERROR                 if the function call succeeded.
 */
extern mmu_errorCode_e mmu_translation_table_reset(u32 domian);


/*!
 *   \fn      mmu_errorCode_e mmu_set_attribution(u32 start, u32 size, u32 attribution)
 *
 *   \brief set the specified zone as attribution specified
 *
 *   The start adress must begin on a 1 MBytes Segment boundary
 *   The size must be a multiple of 1 MBytes
 *
 *   \param start the start adress of the segments to set as buffered
 *   \param size  the size of the zone to set as buffered
 *
 *   \return a \ref mmu_errorCode_e that specifies the function call result :
 *    - ERR_MMU_MODIFICATION_NOT_ALLOWED if the function was called but was not prepared by a \ref mmu_begin_modify_translation_table
 *    - ERR_MMU_INVALID_SEGMENT          if the specified segment start adress does not point to a segment boundary
 *    - ERR_MMU_INVALID_SIZE             if the specified size is not a multiple of a segment size ( 1MByte)
 *    - ERR_MMU_NO_ERROR                 if the function call succeeded.
 */
extern mmu_errorCode_e mmu_set_attribution(u32 start, u32 size, u32 attribution);

/*!
 *   \fn  mmu_errorCode_e mmu_end_modify_translation_table(u32 context)
 *
 *   \brief end the modification sequence of the Translation table
 *
 *   \param context the context returned by the \ref mmu_begin_modify_translation_table
 *
 *   \return a \ref mmu_errorCode_e that specifies the function call result
 *    - ERR_MMU_MODIFICATION_NOT_ALLOWED if the  \ref mmu_begin_modify_translation_table was not previously called
 *    - ERR_MMU_NO_ERROR                 if the function call succeeded.
 */
extern mmu_errorCode_e mmu_end_modify_translation_table(MsIntMask_e context);

/*!
 *   \fn u32 mmu_get_translation_table(void)
 *
 *   \brief returns the base adress of the translation table
 *
 *   \return 0 if there was an error, the base adress of the translation table
 *           to be used with \ref __enable_mmu otherwise
 */
extern u32 mmu_get_translation_table(void);

mmu_errorCode_e mmu_translation_table_remap(u32 vAddr, u32 pAddr, u32 size);
mmu_errorCode_e mmu_translation_table_remap_to_emmi_sldpm_neighborhood(u32 vAddr, u32 pAddr, u32 size);

extern mmu_errorCode_e mmu_coarse_page_table_init(u32 base_address);
extern mmu_errorCode_e mmu_coarse_page_table_init_test(u32 base_address);
void cp15_write_reg10_tlb_lockdown(u32 lock_addr);

#if defined(__MMU_STACK_PROTECTION__)
extern mmu_errorCode_e mmu_enableTaskStack(u8 taskId);
extern mmu_errorCode_e mmu_disableTaskStack(u8 taskId);
#endif

mmu_errorCode_e mmu_coarse_page_table_set_base(u32 base_address);
u32 mmu_coarse_page_table_get_base(void);

mmu_errorCode_e mmu_fine_page_table_set(u32 vAddr, u32 size);
mmu_errorCode_e mmu_coarse_page_table_set(u32 *ptable, u32 vAddr);

mmu_errorCode_e mmu_paging_insert_page_table_entry(u32 vAddr/* 4KB aligned */, u32 pAddr/* 4KB aligned */, u32 ap, u8 type);
mmu_errorCode_e mmu_paging_invalidate_page_table_entry(u32 vAddr/* 4KB aligned */, u8 type);
mmu_errorCode_e mmu_paging_reset_coarse_page_table(u32 vAddr/* 1MB aligned */, u8 type);

mmu_errorCode_e mmu_sldlm_insert_page_table_entry(u32 *p2ndLevelPageTable, u32 vAddr/* 4KB aligned */, u32 pAddr/* 4KB aligned */, u32 ap, u8 type);
mmu_errorCode_e mmu_sldlm_invalidate_page_table_entry(u32 *p2ndLevelPageTable, u32 vAddr/* 4KB aligned */, u8 type);
mmu_errorCode_e mmu_sldlm_reset_coarse_page_table(u32 vAddr/* 1MB aligned */, u8 type);

#endif // __SYS_ARM_COMMON_H__
