
/**
 * @file
 * Browser Memory Porting Layer
 *
 * Basic memory support functions needed by NCC WAP. The only
 * function contained here is deprecated. We should try not to
 * make use of it and use CRTL_malloc, CRTL_free instead.
 *
 * <!-- #interface list begin -->
 * \section nccport_browser_mem Interface
 * - NCCPort_browser_mem_realloc()
 * <!-- #interface list end -->
 */

#ifndef __NCCPORT_BROWSER_MEM_H__
#define __NCCPORT_BROWSER_MEM_H__

#ifdef __cplusplus
extern  "C" {
#endif

#include <ncc_types.h> /**<common wap include file*/

#define WAP_OS_PRINTF NCC_KERNEL_DEBUG    /**<Define DEBUG function*/
#define WAP_OS_ASSERT NCC_KERNEL_ASSERT    /**<Define ASSERT function*/

/**
  * Realloc function of target system platform.
  * \param ptr  the old ptr
  * \param size new alloced space's size (must be greater than 0)
  * \return NULL for failure, greater than 0 otherwise
  */
void *NCCPort_browser_mem_realloc(void *ptr, int32_t size);

#ifdef __cplusplus
}
#endif

#endif /* __NCCPORT_BROWSER_MEM_H__ */

