/**
 *
 * @file    cus_os.h
 *
 * @brief   This file defines the OS related interface for customer layer
 *          where the implementation might different between platforms.
 *          The OS related interfaces includes memory allocation, task inter-
 *          communication.
 *          ** Note **
 *          The file is new created, new add related functions should be
 *          added here!!
 *
 * @author  Xavier Fan
 * @version $Id: cus_os.h 15678 2008-10-29 06:59:18Z xavier.fan $
 *
 */

#ifndef __SYS_MSWRAPPER_CUS_OS_H__
#define __SYS_MSWRAPPER_CUS_OS_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/

/**
 * NOTE:
 *
 * The following macro is used to speed-up in MMI platform, that is a special case
 * and should not add more special case again!
 *
 */
#define CUS_OS_ALLOCATE_HEAP(_MEM_SIZE_)		cus_os_allocate_heap(_MEM_SIZE_)
#define CUS_OS_ALLOCATE_POOL(_MEM_SIZE_)		cus_os_allocate_pool(_MEM_SIZE_)
#define CUS_OS_RELEASE_HEAP(_MEM_ADDR_)			cus_os_release_heap(_MEM_ADDR_)
#define CUS_OS_RELEASE_POOL(_MEM_ADDR_)			cus_os_release_pool(_MEM_ADDR_)
#define CUS_OS_RELEASE_MEMORY(_MEM_ADDR_)		cus_os_release_memory(_MEM_ADDR_)


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION PROTOTYPE                                                */
/*--------------------------------------------------------------------------*/
void*	cus_os_allocate_heap(u32 size);
void* cus_os_allocate_pool(u32 size);
void	cus_os_release_heap(void* pMem);
void	cus_os_release_pool(void* pMem);
void	cus_os_release_memory(void* pMem);

#endif



