/****************************************************************************/
/*  File    : sys_virtaul_mem.h                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   : Virtual Memory                                                */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/

#ifndef __SYS_SYS_VIRTUAL_MEM_H__
#define __SYS_SYS_VIRTUAL_MEM_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "sys_vm_dbg.ho"



/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef struct
{
	//u32* ptrAlignedPageTableAddr;
	u32 *ptrRealPageTableAddr;
	u32 *ptrAlignedMemAddr; 
	u32 *ptrRealMemAddr;
	u32 uAlignedSize;
	u8 used;
	u8 padding[3];
} VirtualMemoryRecord_S;


/* 
 *  Virtual Memory Allocated Table 
 *  1. The VMStartAddr must be aligned 1MB (0x00100000)
 *  2. The VMSize is also limited form 0 to 1MB (0x00100000)
 *     If VMSize is not be specified in API, 
 *     default size defined in table would be used
 *  3. _VM_Id_e in sys_sys_virtaul_mem.h should also be maintained !!
 *     Please add vm app id to _VM_Id_e.       
 */

typedef enum {
	VM_BASE     = 0,
	VM_DLM_TEXT = VM_BASE,
	VM_DLM_DATA,
	/* Following entry can be customized   */
#if 0
	VM_DLM_FREE_1,
	VM_DLM_FREE_2,
#endif
	VM_LAST
} _VM_Id_e;





/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/
#define _SYS_VM	(_SYS | LEVEL_18)
#define MAX_VIRTUAL_MEMORY_RECORD	(VM_LAST-VM_BASE)






/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/
extern u32 _sys_VM_VA2PA(u32, u32);




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*  Do Not modify following item   !!!!      */

u32 * sys_AllocateVirtualMem(u8 VMid, u32 size);
void sys_DeAllocateVirtualMem(u8 VMid);
u32 sys_VM_VA2PA(u32 vaddr);
u32 sys_check_VMid	(u32 idx);


#endif // __SYS_SYS_VIRTUAL_MEM_H__
