#ifndef __VEN__TEST_FILE_DEFINE_H__
#define __VEN__TEST_FILE_DEFINE_H__

/**
 *
 * @file    test_ven_file.h
 * @brief   This file defines the file interface definition for test.
 *
 * @author  Code.Lin
 * @version $Id: test_ven_file.h 27833 2009-04-08 12:12:22Z code.lin $
 *
 */

#include "ven_file.h"

/*! @brief SDK Test Case 100: test NOR FS related function
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_for_NOR(void);

/*! @brief SDK Test Case 100: test NAND FS related function
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_for_NAND(void);

/*! @brief SDK Test Case 101: test SD FS related function
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_for_SD(u32 ven_handle);

/*! @brief SDK Test Case 140: test space info.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *  @param  totalSize  [out] The query result for total space is in KBytes on the device
 *  @param  freeSize   [out] The query result for free space is in KBytes on the device
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_space_info(ven_file_device_type_t device, u32 * totalSize, u32 * freeSize);

/*! @brief SDK Test Case 141: test FS functions - ven_file_wmakeDir.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_makeDir(ven_file_device_type_t device);

/*! @brief SDK Test Case 142: test FS functions - ven_file_wremoveDir.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_removeDir(ven_file_device_type_t device);

/*! @brief SDK Test Case 143: test FS functions - ven_file_wremoveDirAll.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_removeDirAll(ven_file_device_type_t device);

/*! @brief SDK Test Case 144: test FS functions - ven_file_wunlink.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_unlink(ven_file_device_type_t device);

/*! @brief SDK Test Case 145: test FS functions - ven_file_wexists.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_exists(ven_file_device_type_t device);

/*! @brief SDK Test Case 146: test FS functions - ven_file_wrename.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_rename(ven_file_device_type_t device);

/*! @brief SDK Test Case 147: test FS functions - ven_file_wfopen.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_fopen(ven_file_device_type_t device);

/*! @brief SDK Test Case 148: test FS functions - ven_file_wfread.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_fread(ven_file_device_type_t device);

/*! @brief SDK Test Case 149: test FS functions - ven_file_wfwrite.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_fwrite(ven_file_device_type_t device);

/*! @brief SDK Test Case 150: test FS functions - ven_file_wfclose.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_fclose(ven_file_device_type_t device);

/*! @brief SDK Test Case 151: test FS functions - ven_file_wfseek.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_fseek(ven_file_device_type_t device);

/*! @brief SDK Test Case 152: test FS functions - ven_file_wftell.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_ftell(ven_file_device_type_t device);

/*! @brief SDK Test Case 153: test FS functions - ven_file_wfstat/ven_file_wfsetAttr/ven_file_wfgetAttr.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_attributes(ven_file_device_type_t device);

/*! @brief SDK Test Case 154: test FS functions - ven_file_wopendir/ven_file_wclosedir/ven_file_wdir_get_nb_files/ven_file_wdir_get_info.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_dirlist(ven_file_device_type_t device);

/*! @brief SDK Test Case 155: test FS functions - ven_file_wfopen.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_openMode(ven_file_device_type_t device);

/*! @brief SDK Test Case 156: test FS functions - ven_file_wgetFolderSize.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_getFolderSize(ven_file_device_type_t device);

/*! @brief SDK Test Case 157: test FS functions - ven_file_wtruncate.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_truncate(ven_file_device_type_t device);

/*! @brief SDK Test Case 158: test FS functions - ven_file_wtruncateByPath.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_truncateByPath(ven_file_device_type_t device);

/*! @brief SDK Test Case 159: test FS functions - sync. DB files for file manager.
 *
 *  @param  device     [in] Should be device type, ven_file_device_type_t
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_syncFolder(ven_file_device_type_t device);

/*! @brief SDK Test Case 101: test SD FS related function
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_advanced_write_test_cases_for_SD(u32 ven_handle);

/*! @brief SDK Test Case 102: test SD FS related function
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_advanced_read_test_cases_for_SD(u32 ven_handle);

/*! @brief report test result with fail items for latest test case
 *
 *  @param fail_counter        [out] fail items of latest test case.
 *  @param total_test_items    [out] total items of latest test case.
 *
 *  @retval void
 *
 */
void ms_ven_file_test_cases_fail_rate(u16 *fail_counter, u16 *total_test_items);

/*! @brief test partial list correctness and profile the proformance and memory usage in NOR.
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_partial_list_for_NOR(void);

/*! @brief test partial list correctness and profile the proformance and memory usage in NAND.
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_partial_list_for_NAND(void);

/*! @brief test partial list correctness and profile the proformance and memory usage in SD.
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_partial_list_for_SD(void);

/*! @brief SDK test SD ven_file_wfwrite related function
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_vt_for_SD(void);

/*! @brief SDK test SD profile start
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_profiling_for_SD(void);

/*! @brief SDK test SD profile result
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_profiling_result_for_SD(void);

/*! @brief SDK test SD FS related function in async mode
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_async_for_SD(u32 ven_handle);

/*! @brief SDK test NOR FS related function in async mode
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_async_for_NOR(void);

/*! @brief SDK test NAND FS related function in async mode
 *
 *  @param void
 *
 *  @retval TRUE if success
 *          FALSE if failed
 */
s32 ms_ven_file_test_cases_async_for_NAND(void);

static s32 _test_ven_file_findnext(ven_file_device_type_t sDeviceType);


#endif // __VEN__TEST_FILE_DEFINE_H__
