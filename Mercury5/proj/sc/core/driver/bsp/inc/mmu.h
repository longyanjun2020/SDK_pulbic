//==============================================================================
//
//  File        : mmu.h
//  Description : INCLUDE File for MMU configuration
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_MMU_H_
#define _MMPF_MMU_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================
/*
 * Virtual address mapping to DRAM physical address
 * 0x41000000(VA) -> 0x01000000 (PA)
 */
#define MMU_DRAM_VA_ST              (0x400)
#define DRAM_NONCACHE_VA(a)			((a) & 0x0FFFFFFF)
#define DRAM_CACHE_VA(a)			((a) | 0x40000000) 

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void MMPF_MMU_Initialize(unsigned int *pTranslationTable,unsigned int *pCoarsePageTable);
void MMPF_MMU_Deinitialize(void);
void MMPF_MMU_CleanDCache(void);
void MMPF_MMU_InvalidateDCacheMVA(MMP_ULONG ulRegion, MMP_ULONG ulSize);
void MMPF_MMU_FlushDCacheMVA(MMP_ULONG ulRegion, MMP_ULONG ulSize);
void MMPF_MMU_FlushDCache(void);
void MMPF_MMU_FlushIDCache(void);
void MMPF_MMU_FlushIDTLB(void);
void MMPF_MMU_FlushITLB(void);
void MMPF_MMU_FlushDTLB(void);

#endif //_MMPF_MMU_H_
