/** @file sys_rtk_ramdump.h
 * @author Piazza.Lo
 * @date 07/08/2009
 *
 * Ram dump interface.
 */

#ifndef __SYS_RTK_RAMDUMP_H__
#define __SYS_RTK_RAMDUMP_H__

#include "vm_types.ht"

/************************************************************************/
/*                                                  Functions                                                           */
/************************************************************************/

/**
 * @brief Check whether it need to do ram dump.
 * @param None.
 * @return None.
 */
extern bool IsNeedRamDump(void);


/**
 * @brief Return ram dump flag
 * @param None.
 * @return None.
 */
extern u32 GetRamDumpFlag(void);


/**
 * @brief Return ram dump flag writeen by WriteRamDumpFlag
 * @param None.
 * @return None.
 */
extern u32 GetRamDumpFlagWrite(void);


/**
 * @brief Read ram dump flag from e2p.
 * @param None.
 * @return None.
 */
extern void ReadRamDumpFlag(void);


/**
 * @brief Write ram dump flag to e2p.
 * @param u32 value.
 * @return None.
 */
extern void WriteRamDumpFlag(u32 value);

/**
 * @brief Return ram dump result.
 * @param None.
 * @return None.
 */
extern u32 GetRamDumpResult(void);


/**
 * @brief Prepare ram dump information.
 * @param bPrintBackTrace check need to print message into backtrace.
 * @return None.
 */
extern void PrepareRamDumpInfo(bool bPrintBackTrace);


/**
 * @brief Prepare M3 ram dump information.
 * @param bPrintBackTrace check need to print message into backtrace.
 * @return None.
 */
extern void PrepareM3RamDumpInfo(bool bPrintBackTrace);


/**
 * @brief Do M3 ram dumping.
 * @param None.
 * @return None.
 */
extern void DoM3RamDump(void);


/**
 * @brief Do ram dumping.
 * @param None.
 * @return Ram dump result.
 */
extern u32 DoRamDump(void);


/**
 * @brief Create ram dump stor directory.
 * @param None.
 * @return None.
 */
extern void CreateRamDumpDir(void);

#endif //__SYS_RTK_RAMDUMP_H__


