/**
 *
 * @file    fms_rai_nand.h
 *
 * @brief   This file defines RAI porting layer with NRAI interface
 *
 * @author  Xavier Fan
 * @version $Id: fms_rai_nand.c 14189 2008-09-18 04:36:19Z kevin.chang $
 *
 */
#if	!defined(__FMS_RAI_NAND_H__)
#define	__FMS_RAI_NAND_H__

#if	defined(__NAND__)

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include	"vm_types.ht"
#include	"fms_rai_base.h"
#include    "fms_atcmd.h"

#if NRAICacheDebug
extern bool IsBootingScan;
#endif
/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#define NRAI_CACHE_BLOCKS_NUM		(2)																					/*	I/O cache block number	*/
#define NRAI_CLUSTER_SIZE				(64 * 1024)																	/*	NRAI Cluster Size				*/
#define NRAI_CLUSTER_SIZE_LOG2	(16)
#define NRAI_CACHE_BLOCKS_SIZE 	(NRAI_CACHE_BLOCKS_NUM * NRAI_CLUSTER_SIZE)	/*	I/O Block size					*/





/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/
#define FRAI_PTR(_OFFSET_)										fms_nraiOffsetToPtr(_OFFSET_)	/*	offset --> pointer	*/
#define FRAI_OFS(_PTR_)												fms_nraiPtrToOffset(_PTR_)		/*	pointer--> offset		*/

#define	FMS_WRITE_FOR_RAI(_DST_,_LEN_,_SRC_)	fms_nraiWrite((u32) (_DST_), (u32)(_LEN_), (void*)(_SRC_) )
#define	FMS_ERASE_FOR_RAI(_ADDR_,_MODE_)			fms_nraiErase((u32)_ADDR_, (u32)_MODE_)




/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION IMPLEMENT                                                */
/*--------------------------------------------------------------------------*/
frai_item_t		*	fms_nraiOffsetToPtr(frai_offset_t offset);
frai_offset_t 	fms_nraiPtrToOffset(frai_item_t * pItem);
s32							fms_nraiInitMem(void * pNraiMem);
s32							fms_nraiWrite(u32 pAddress, u32 size, const void * pSrc);
s32							fms_nraiErase(u32 pAddress, u32 mode);
void						fms_nraiInitContent(void);
void						fms_nraiInitSimulator(void);
s32							fms_nraiMarkBlockDirty(frai_offset_t offset, u32 size);
void                        mark_free (frai_offset_t off, bool NeedHashPut);
void            mark_uniq(frai_offset_t off);
s32 		fms_flushBuffer(void);

#if NRAICacheDebug
void fms_rai_cache_check(frai_cache_scan_t CaseID, u32 clusterno, u8 * pData);
extern u32 gStoredCHKSUM;
extern u32 gComputedCHKSUM;
extern u32 gCheckSumHistory;
#endif
void error_mark_free(frai_offset_t NANDoff);
#if defined(USE_GET_NRAI_INFO)
void GetNRAIInfo(void);
void fms_NRAIInit(void);
#endif

extern bool IsSysStopMmp;
#endif	/*	defined(__NAND__) */

#endif	/*	!defined(__FMS_RAI_NAND_H__)	*/


