/** @file cus_os_test.c
 * @author Piazza.Lo
 * @date 05/13/2010
 *
 * OS service test cases.
 */

#include "osdefs.hc"
#include "vm_types.ht"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "sys_MsWrapper_cus_os_flag.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys_rtk_hv.h"
#include "mdl_vfs_file.ho"
#include "drv_timer_types.h"
#include "drv_timer_api.h"
#include "sys_sys_rand.h"


typedef union{
	u32 userdata;
} Body_test_t;


#ifdef Body_t
#undef Body_t
#endif

#define Body_t Body_test_t

#include "stdmsg.ht"

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "sys_MsWrapper_cus_os_message_define__.hi"
};

/************************************************************************/
/*                                                   Macros                                                              */
/************************************************************************/
//#define OS_TEST_EXT // enable additional test

#ifndef INCLUDE_IN_FILE

#define _RESULT_STR_SIZE 100

#define _SDK_TEST_FUNC(_FnName) static void _FnName(void)

#define ven_std_sprintf sprintf

#define ven_std_strlen strlen

#ifdef __I_SW__

#define VEN_TEST_PRINT_INFO_LINE(x) cliPrintf("[CUS_OS_TEST:%d] %s\n\r", __LINE__, x)

#else

#define VEN_TEST_PRINT_INFO_LINE(x) NULL

#endif

#define VEN_TEST_CHECK_RESULT(x) ((x) ? VEN_TEST_PRINT_INFO_LINE("Pass") : VEN_TEST_PRINT_INFO_LINE("Fail"))

#endif

#define KERNEL_TEST_GENERAL_STACK_SIZE 3072

#define CAT_KERNEL_SIZE (sizeof(aKernelTestItemTbl)/sizeof(_SdkTestItem_t))

/************************************************************************/
/*                                                   Types                                                               */
/************************************************************************/
_SDK_TEST_FUNC(_test_OS_MsInitSem_);
_SDK_TEST_FUNC(_test_OS_MsInitSemExtend_);
_SDK_TEST_FUNC(_test_OS_MsProduceSem_);
_SDK_TEST_FUNC(_test_OS_MsConsumeSem_);
_SDK_TEST_FUNC(_test_OS_MsPollSem_1_);
_SDK_TEST_FUNC(_test_OS_MsPollSem_2_);
_SDK_TEST_FUNC(_test_OS_MsConsumeSemDelay_1_);
_SDK_TEST_FUNC(_test_OS_MsConsumeSemDelay_2_);
_SDK_TEST_FUNC(_test_OS_MsProduceSemRtkReady_);
_SDK_TEST_FUNC(_test_OS_MsConsumeSemRtkReady_);
_SDK_TEST_FUNC(_test_OS_MsGetSemCount_);
_SDK_TEST_FUNC(_test_OS_MsStartTimer_);
_SDK_TEST_FUNC(_test_OS_MsStartPeriodicTimer_);
_SDK_TEST_FUNC(_test_OS_MsStopTimer_);
_SDK_TEST_FUNC(_test_OS_MsIsTimerActive_);
_SDK_TEST_FUNC(_test_OS_MsStartCbTimer_);
_SDK_TEST_FUNC(_test_OS_MsAllocateMem_1_);
_SDK_TEST_FUNC(_test_OS_MsAllocateMem_2_);
_SDK_TEST_FUNC(_test_OS_MsMemoryReAllocate_);
_SDK_TEST_FUNC(_test_OS_MsLinkMemory_);
_SDK_TEST_FUNC(_test_OS_MsGetPoolMemory_);
_SDK_TEST_FUNC(_test_OS_MsGetHeapMemory_);
_SDK_TEST_FUNC(_test_OS_MsHeapRealloc_);
_SDK_TEST_FUNC(_test_OS_MsReleaseHeapMemory_);
_SDK_TEST_FUNC(_test_OS_MsReleaseMemory_);
_SDK_TEST_FUNC(_test_OS_MsIsPoolMemory_);
_SDK_TEST_FUNC(_test_OS_MsIsHeapMemory_);
_SDK_TEST_FUNC(_test_OS_MsQueryMemRealSize_);
_SDK_TEST_FUNC(_test_check_os_ready);
_SDK_TEST_FUNC(_test_os_tick);
_SDK_TEST_FUNC(_test_ms_sleep);
_SDK_TEST_FUNC(_test_flag_init);
_SDK_TEST_FUNC(_test_flag_destroy);
_SDK_TEST_FUNC(_test_flag_set_bits);
_SDK_TEST_FUNC(_test_flag_mask_bits);
_SDK_TEST_FUNC(_test_flag_wait_1);
_SDK_TEST_FUNC(_test_flag_wait_2);
_SDK_TEST_FUNC(_test_flag_wait_3);
_SDK_TEST_FUNC(_test_flag_wait_4);
_SDK_TEST_FUNC(_test_flag_timed_wait_1);
_SDK_TEST_FUNC(_test_flag_timed_wait_2);
_SDK_TEST_FUNC(_test_flag_poll_1);
_SDK_TEST_FUNC(_test_flag_poll_2);
_SDK_TEST_FUNC(_test_flag_peek);
_SDK_TEST_FUNC(_test_flag_waiting);
_SDK_TEST_FUNC(_test_msg_send);
_SDK_TEST_FUNC(_test_msg_send_ext);
_SDK_TEST_FUNC(_test_msg_send_prio);
_SDK_TEST_FUNC(_test_msg_set_threshold);
_SDK_TEST_FUNC(_test_msg_send_with_threshold);
_SDK_TEST_FUNC(_test_msg_recv);
_SDK_TEST_FUNC(_test_msg_recv_no_wait_1);
_SDK_TEST_FUNC(_test_msg_recv_no_wait_2);
_SDK_TEST_FUNC(_test_msg_status);
_SDK_TEST_FUNC(_test_OS_sem_0);
_SDK_TEST_FUNC(_test_OS_sem_1);
_SDK_TEST_FUNC(_test_OS_flag_0);
_SDK_TEST_FUNC(_test_OS_int_0);
_SDK_TEST_FUNC(_test_OS_mbox_0);
#ifdef OS_TEST_EXT // additional test
_SDK_TEST_FUNC(_test_OS_schedule_0);
_SDK_TEST_FUNC(_test_OS_timer_measure_);
#endif
#if defined (__MMAP__)
_SDK_TEST_FUNC(_test_OS_mmap_0);
_SDK_TEST_FUNC(_test_OS_mmap_1);
_SDK_TEST_FUNC(_test_OS_mmap_2);
_SDK_TEST_FUNC(_test_OS_mmap_3);
_SDK_TEST_FUNC(_test_OS_mmap_4);
#endif
#if defined (__DPM__)
_SDK_TEST_FUNC(_test_demand_paging_0);
#endif
_SDK_TEST_FUNC(_test_aligned_memory_0);
#ifdef __FIXME__
_SDK_TEST_FUNC(_test_aligned_memory_1);
#endif
_SDK_TEST_FUNC(_test_OS_hmem_0);
_SDK_TEST_FUNC(_test_OS_hmem_1);
_SDK_TEST_FUNC(_test_OS_hmem_2);
_SDK_TEST_FUNC(_test_OS_hmem_3);
_SDK_TEST_FUNC(_test_OS_hmem_4);
_SDK_TEST_FUNC(_test_OS_hmem_5);
_SDK_TEST_FUNC(_test_OS_hmem_6);
_SDK_TEST_FUNC(_test_OS_hmem_7);
_SDK_TEST_FUNC(_test_OS_hmem_8);
_SDK_TEST_FUNC(_test_OS_hmem_9);
_SDK_TEST_FUNC(_test_OS_hmem_10);
_SDK_TEST_FUNC(_test_OS_hmem_11);
_SDK_TEST_FUNC(_test_OS_hmem_12);
_SDK_TEST_FUNC(_test_OS_hmem_13);
_SDK_TEST_FUNC(_test_OS_hmem_14);
_SDK_TEST_FUNC(_test_OS_hmem_15);
_SDK_TEST_FUNC(_test_OS_hmem_16);
_SDK_TEST_FUNC(_test_OS_hmem_17);

_SDK_TEST_FUNC(_test_OS_MsAllocateNonCacheMem_0);
_SDK_TEST_FUNC(_test_OS_MsAllocateNonCacheMem_1);
#if defined(__TIME_SLICE_SCHEDULE__)
_SDK_TEST_FUNC(_test_OS_MsTimeSliceScheduling);
#endif
_SDK_TEST_FUNC(_test_OS_mutex);

#ifndef INCLUDE_IN_FILE
typedef void (*_TEST_FUNC_PTR)(void);

enum
{
	_SDKTEST_CAT_START,
	_SDKTEST_CAT_AUTO = _SDKTEST_CAT_START,
	_SDKTEST_CAT_FS,
	_SDKTEST_CAT_OS,
	_SDKTEST_CAT_GRAPHICS,
	_SDKTEST_CAT_CODEC,
	_SDKTEST_CAT_TIME,
	_SDKTEST_CAT_SETTING,
	_SDKTEST_CAT_NET,
	_SDKTEST_CAT_EDITOR,
	_SDKTEST_CAT_PHB,
	_SDKTEST_CAT_FILEBROWSE,
	_SDKTEST_CAT_SMS,
	_SDKTEST_CAT_WMA,
	_SDKTEST_CAT_CC,
	_SDKTEST_CAT_CLIPBOARD,
	_SDKTEST_CAT_DRV,
	_SDKTEST_CAT_SYS,
	_SDKTEST_CAT_UI,
	_SDKTEST_CAT_UTIL,
	_SDKTEST_CAT_CAMERA,
	_SDKTEST_CAT_WAP,
	_SDKTEST_CAT_GPS,
	_SDKTEST_CAT_STC,
	_SDKTEST_CAT_KERNEL,
	_SDKTEST_CAT_KPD,

	_SDKTEST_CAT_SUM
};

typedef enum
{
    SDK_TEST_ITEM_AUTO_NO_CONFIRM,
    SDK_TEST_ITEM_AUTO_CONFIRM,
    SDK_TEST_ITEM_NO_AUTO
} _SdkTestItemType;

typedef struct _SdkTestItem_tag
{
    _TEST_FUNC_PTR     pFnTest;
    u8                *pTestName;
    u16                TestCaseCat;
    u16                TestCaseNum;
    _SdkTestItemType   AutoType;
} _SdkTestItem_t;
#endif

typedef struct
{
    Header_t Header;
    Body_t Body;
} KerTestMsg_t;

typedef struct {
	void *ptr;
	u32 size;
} Mem_t;

/************************************************************************/
/*                                                   Functions                                                          */
/************************************************************************/
static void emptyInit(void *userdata);
static void emptyParser(vm_msg_t *pMessage);
static void __test_os_sem_entry_0(void *userdata);
static void __test_os_sem_entry_1(void *userdata);
static void __test_os_sem_entry_2(void *userdata);
static void __test_os_sem_entry_3(void *userdata);
static void __test_os_flag_entry_0(void *userdata);
static void __test_os_flag_entry_1(void *userdata);
static void __test_os_flag_entry_2(void *userdata);
static void __test_os_int_entry_0(void *userdata);
static void __test_os_int_entry_1(void *userdata);
static void __test_os_int_entry_2(void *userdata);
static void __test_os_int_entry_3(void *userdata);
#ifdef OS_TEST_EXT // additional task schedule test
static void __test_OS_schedule_init_0(void *userdata);
static void __test_OS_schedule_init_1(void *userdata);
static void __test_OS_schedule_init_2(void *userdata);
#endif
#if defined (__MMAP__)
static void __test_os_mmap_entry_0(void *userdata);
static void __test_os_mmap_entry_1(void *userdata);
static void __test_os_mmap_entry_2(void *userdata);
#endif

/************************************************************************/
/*                                                   Variables                                                          */
/************************************************************************/
static const _SdkTestItem_t aKernelTestItemTbl[] =
{
#if defined(__TARGET__)
    {_test_OS_MsInitSem_,       (u8*)"test MsInitSem",       _SDKTEST_CAT_KERNEL, 0, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsInitSemExtend_,        (u8*)"test MsInitSemExtend",        _SDKTEST_CAT_KERNEL,  1, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsProduceSem_,           (u8*)"test MsProduceSem",           _SDKTEST_CAT_KERNEL,  2, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsConsumeSem_,          (u8*)"test MsConsumeSem",           _SDKTEST_CAT_KERNEL,  3, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsPollSem_1_,            (u8*)"test MsPollSem 1",            _SDKTEST_CAT_KERNEL, 4, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsPollSem_2_,            (u8*)"test MsPollSem 2",            _SDKTEST_CAT_KERNEL, 5, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsConsumeSemDelay_1_,    (u8*)"test MsConsumeSemDelay 1",    _SDKTEST_CAT_KERNEL, 6, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsConsumeSemDelay_2_,    (u8*)"test MsConsumeSemDelay 2",    _SDKTEST_CAT_KERNEL, 7, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsProduceSemRtkReady_,   (u8*)"test MsProduceSemRtkReady",    _SDKTEST_CAT_KERNEL, 8, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsConsumeSemRtkReady_,   (u8*)"test MsConsumeSemRtkReady",    _SDKTEST_CAT_KERNEL, 9, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsGetSemCount_,          (u8*)"test MsGetSemCount",    _SDKTEST_CAT_KERNEL, 10, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsStartTimer_,           (u8*)"test MsStartTimer",           _SDKTEST_CAT_KERNEL, 11, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsStartPeriodicTimer_,   (u8*)"test MsStartPeriodicTimer",   _SDKTEST_CAT_KERNEL, 12, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsStopTimer_,            (u8*)"test MsStopTimer",            _SDKTEST_CAT_KERNEL, 13, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsIsTimerActive_,        (u8*)"test MsIsTimerActive",        _SDKTEST_CAT_KERNEL, 14, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#else
    {_test_OS_MsStartCbTimer_,         (u8*)"test MsStartCbTimer",         _SDKTEST_CAT_KERNEL, 15, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#endif
    ,{_test_OS_MsStartCbTimer_,         (u8*)"test MsStartCbTimer",         _SDKTEST_CAT_KERNEL, 15, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsAllocateMem_1_,        (u8*)"test MsAllocateMem_1",        _SDKTEST_CAT_KERNEL, 16, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsAllocateMem_2_,        (u8*)"test MsAllocateMem_2",        _SDKTEST_CAT_KERNEL, 17, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsMemoryReAllocate_,     (u8*)"test MsMemoryReAllocate",     _SDKTEST_CAT_KERNEL, 18, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsLinkMemory_,           (u8*)"test MsLinkMemory",           _SDKTEST_CAT_KERNEL, 19, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsGetPoolMemory_,        (u8*)"test MsGetPoolMemory",        _SDKTEST_CAT_KERNEL, 20, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsGetHeapMemory_,        (u8*)"test MsGetHeapMemory",        _SDKTEST_CAT_KERNEL, 21, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsHeapRealloc_,          (u8*)"test MsHeapRealloc",          _SDKTEST_CAT_KERNEL, 22, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsReleaseHeapMemory_,    (u8*)"test MsReleaseHeapMemory",    _SDKTEST_CAT_KERNEL, 23, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsReleaseMemory_,  (u8*)"test MsReleaseMemory",  _SDKTEST_CAT_KERNEL, 24, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsIsPoolMemory_,         (u8*)"test MsIsPoolMemory",         _SDKTEST_CAT_KERNEL, 25, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsIsHeapMemory_,         (u8*)"test MsIsHeapMemory",         _SDKTEST_CAT_KERNEL, 26, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsQueryMemRealSize_,     (u8*)"test MsQueryMemRealSiz",      _SDKTEST_CAT_KERNEL, 27, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_check_os_ready,    (u8*)"check os ready", _SDKTEST_CAT_KERNEL, 28, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_os_tick,    (u8*)"get os tick", _SDKTEST_CAT_KERNEL, 29, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_ms_sleep,    (u8*)"task sleep", _SDKTEST_CAT_KERNEL, 30, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_init,    (u8*)"flag init", _SDKTEST_CAT_KERNEL, 31, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_destroy,    (u8*)"flag destroy", _SDKTEST_CAT_KERNEL, 32, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_set_bits,    (u8*)"flag set bits", _SDKTEST_CAT_KERNEL, 33, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_mask_bits,    (u8*)"flag set bits", _SDKTEST_CAT_KERNEL, 34, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_wait_1,    (u8*)"flag wait 1", _SDKTEST_CAT_KERNEL, 35, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_wait_2,    (u8*)"flag wait 2", _SDKTEST_CAT_KERNEL, 36, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_wait_3,    (u8*)"flag wait 3", _SDKTEST_CAT_KERNEL, 37, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_wait_4,    (u8*)"flag wait 4", _SDKTEST_CAT_KERNEL, 38, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_timed_wait_1,    (u8*)"flag timed wait 1", _SDKTEST_CAT_KERNEL, 39, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_timed_wait_2,    (u8*)"flag timed wait 2", _SDKTEST_CAT_KERNEL, 40, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_poll_1,    (u8*)"flag poll 1", _SDKTEST_CAT_KERNEL, 41, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_poll_2,    (u8*)"flag poll 2", _SDKTEST_CAT_KERNEL, 42, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_peek,    (u8*)"flag peek", _SDKTEST_CAT_KERNEL, 43, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_flag_waiting,    (u8*)"flag waiting", _SDKTEST_CAT_KERNEL, 44, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_msg_send,    (u8*)"msg send", _SDKTEST_CAT_KERNEL, 45, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#if defined(__TARGET__)
    ,{_test_msg_send_ext,    (u8*)"msg send extend", _SDKTEST_CAT_KERNEL, 46, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#endif
    ,{_test_msg_send_prio,    (u8*)"msg send with priority", _SDKTEST_CAT_KERNEL, 47, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_msg_set_threshold,    (u8*)"msg set threshold", _SDKTEST_CAT_KERNEL, 48, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_msg_send_with_threshold,    (u8*)"msg send with threshold", _SDKTEST_CAT_KERNEL, 49, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_msg_recv,    (u8*)"msg receive", _SDKTEST_CAT_KERNEL, 50, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_msg_recv_no_wait_1,    (u8*)"msg receive no wait 1", _SDKTEST_CAT_KERNEL, 51, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_msg_recv_no_wait_2,    (u8*)"msg receive no wait 2", _SDKTEST_CAT_KERNEL, 52, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_msg_status,    (u8*)"msg status", _SDKTEST_CAT_KERNEL, 53, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_sem_0,       (u8*)"semaphore 0", _SDKTEST_CAT_KERNEL, 54, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_sem_1,       (u8*)"semaphore 1", _SDKTEST_CAT_KERNEL, 55, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_flag_0,       (u8*)"flag 0", _SDKTEST_CAT_KERNEL, 56, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_int_0,       (u8*)"interrupt 0, this case need 70s to test", _SDKTEST_CAT_KERNEL, 57, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_mbox_0,       (u8*)"mail box 0", _SDKTEST_CAT_KERNEL, 58, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#ifdef OS_TEST_EXT // additional test
    ,{_test_OS_schedule_0,       (u8*)"task schedule test 0", _SDKTEST_CAT_KERNEL, 59, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_timer_measure_,       (u8*)"task timer measure 0", _SDKTEST_CAT_KERNEL, 60, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#endif
#if defined (__MMAP__)
    ,{_test_OS_mmap_0,       (u8*)"mmap one map", _SDKTEST_CAT_KERNEL, 61, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_mmap_1,       (u8*)"mmap three map 0", _SDKTEST_CAT_KERNEL, 62, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_mmap_2,       (u8*)"mmap three map 1", _SDKTEST_CAT_KERNEL, 63, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_mmap_3,       (u8*)"mmap multi-thread", _SDKTEST_CAT_KERNEL, 64, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_mmap_4,       (u8*)"mmap write", _SDKTEST_CAT_KERNEL, 65, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#endif
#if defined (__DPM__)
    ,{_test_demand_paging_0,       (u8*)"demand paging 0", _SDKTEST_CAT_KERNEL, 66, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#endif
    ,{_test_aligned_memory_0,       (u8*)"aligned memory 0", _SDKTEST_CAT_KERNEL, 67, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#ifdef __FIXME__
    ,{_test_aligned_memory_1,       (u8*)"aligned memory 1", _SDKTEST_CAT_KERNEL, 68, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#endif
    ,{_test_OS_hmem_0,       (u8*)"GMM 0", _SDKTEST_CAT_KERNEL, 70, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_1,       (u8*)"GMM 1", _SDKTEST_CAT_KERNEL, 71, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_2,       (u8*)"GMM 2", _SDKTEST_CAT_KERNEL, 72, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_3,       (u8*)"GMM 3", _SDKTEST_CAT_KERNEL, 73, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_4,       (u8*)"GMM 4", _SDKTEST_CAT_KERNEL, 74, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_5,       (u8*)"GMM 5", _SDKTEST_CAT_KERNEL, 75, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_6,       (u8*)"GMM 6", _SDKTEST_CAT_KERNEL, 76, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_7,       (u8*)"GMM 7", _SDKTEST_CAT_KERNEL, 77, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_8,       (u8*)"GMM 8", _SDKTEST_CAT_KERNEL, 78, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_9,       (u8*)"GMM 9", _SDKTEST_CAT_KERNEL, 79, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_10,   (u8*)"GMM 10", _SDKTEST_CAT_KERNEL, 80, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_11,   (u8*)"GMM 11", _SDKTEST_CAT_KERNEL, 81, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_12,   (u8*)"GMM 12", _SDKTEST_CAT_KERNEL, 82, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_13,   (u8*)"GMM 13", _SDKTEST_CAT_KERNEL, 83, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_14,   (u8*)"GMM 14", _SDKTEST_CAT_KERNEL, 84, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_15,   (u8*)"GMM 15", _SDKTEST_CAT_KERNEL, 85, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_16,   (u8*)"GMM 16", _SDKTEST_CAT_KERNEL, 86, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_hmem_17,   (u8*)"GMM 17", _SDKTEST_CAT_KERNEL, 87, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsAllocateNonCacheMem_0,   (u8*)"Uncached Allocation 0", _SDKTEST_CAT_KERNEL, 88, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
    ,{_test_OS_MsAllocateNonCacheMem_1,   (u8*)"Uncached Allocation 1", _SDKTEST_CAT_KERNEL, 89, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#if defined(__TIME_SLICE_SCHEDULE__)
	,{_test_OS_MsTimeSliceScheduling, (u8*)"time-slice scheduling", _SDKTEST_CAT_KERNEL, 90, SDK_TEST_ITEM_AUTO_NO_CONFIRM}
#endif
    ,{_test_OS_mutex, (u8*)"mutext test", _SDKTEST_CAT_KERNEL, 90, SDK_TEST_ITEM_AUTO_NO_CONFIRM}

};

static MsTaskId_e KerTestTaskId[4];
static u32 q = 0, q1, q2, q3;
static u8 KerTestOutput[_RESULT_STR_SIZE];
Ms_Flag_t KerTestFlag[3];

static MsTaskCreateArgs_t KerTestTaskArgs[4] =
{
    {CUS63_PRIO, 0, NULL, emptyInit, emptyParser, NULL, &KerTestTaskId[0] , NULL, FALSE},
    {CUS62_PRIO, 0, NULL, emptyInit, emptyParser, NULL, &KerTestTaskId[1] , NULL, FALSE},
    {CUS61_PRIO, 0, NULL, emptyInit, emptyParser, NULL, &KerTestTaskId[2] , NULL, FALSE},
    {CUS60_PRIO, 0, NULL, emptyInit, emptyParser, NULL, &KerTestTaskId[3] , NULL, FALSE}
};

/************************************************************************/
/*                                                   Functions                                                          */
/************************************************************************/

#ifdef __I_SW__

#include "vm_stdio.ho"
#include "sys_sys_isw_cli.h"

extern char *wait_for_command(void);
static int KerTest(CLI_t * pCli, char * p);

CliParseToken_t g_atKernelMenuTbl[] =
{
    { "test", "Input test case num (999 for all)", "", KerTest, NULL},
    PARSE_TOKEN_DELIMITER
};

static int KerTest(CLI_t * pCli, char * p)
{
	u32 choice, i;
	char *pCmd;

	pCmd = CliTokenPop(pCli);
	choice = atoi(pCmd);

	if (999 == choice)
	{
		for (i=0;i<CAT_KERNEL_SIZE;i++)
		{
			cliPrintf("[Test %d] %s begin\n\r", i, aKernelTestItemTbl[i].pTestName);
			aKernelTestItemTbl[i].pFnTest();
			cliPrintf("[Test %d] end\n\r", i);
		}
	}
	else if (CAT_KERNEL_SIZE > choice)
	{
		cliPrintf("[Test %d] %s begin\n\r", choice, aKernelTestItemTbl[choice].pTestName);
		aKernelTestItemTbl[choice].pFnTest();
		cliPrintf("[Test %d] end\n\r", choice);
	}
	else
	{
		cliPrintf("Wrong test case number\n\r");
	}

	return eCLI_PARSE_OK;
}
#endif

static void emptyInit(void *userdata) {}
static void emptyParser(vm_msg_t *pMessage) {}

static void __test_os_sem_entry_0(void *userdata)
{
	s16 semCount = 0;

	MsConsumeSem(CUS_KERNELTEST_SEM_0);
	if (0 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_0: step 1 Fail, %d", q);
		return;
	}
	q++;
	MsProduceSem(CUS_KERNELTEST_SEM_1);
	MsConsumeSem(CUS_KERNELTEST_SEM_0);
	if (2 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_0: step 2 Fail, %d", q);
		return;
	}
	q++;
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &semCount);
	if (0 < semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_0: step 3 Fail, %d", semCount);
		return;
	}
	if (CUS_OS_OK == MsPollSem(CUS_KERNELTEST_SEM_0))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_0: step 4 Fail");
		return;
	}
	MsProduceSem(CUS_KERNELTEST_SEM_0);
	if (3 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_0: step 5 Fail, %d", q);
		return;
	}
	q++;
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &semCount);
	if (0 >= semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_0: step 6 Fail, %d", semCount);
		return;
	}
	MsProduceSem(CUS_KERNELTEST_SEM_1);
	MsGetSemCount(CUS_KERNELTEST_SEM_2, &semCount);
	if (0 < semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_0: step 7 Fail, %d", semCount);
		return;
	}
	MsConsumeSem(CUS_KERNELTEST_SEM_2);
	if (5 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_0: step 8 Fail, %d", q);
		return;
	}
	q++;
	ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_0: Pass");
}

static void __test_os_sem_entry_1(void *userdata)
{
	s16 semCount = 0;

	MsGetSemCount(CUS_KERNELTEST_SEM_1, &semCount);
	if (0 >= semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_1: step 1 Fail, %d", semCount);
		return;
	}
	MsConsumeSem(CUS_KERNELTEST_SEM_1);
	if (1 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_1: step 2 Fail, %d", q);
		return;
	}
	q++;
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &semCount);
	if (0 < semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_1: step 3 Fail, %d", semCount);
		return;
	}
	MsProduceSem(CUS_KERNELTEST_SEM_0);
	MsConsumeSem(CUS_KERNELTEST_SEM_1);
	if (4 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_1: step 4 Fail, %d", q);
		return;
	}
	q++;
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &semCount);
	if (0 >= semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_1: step 5 Fail, %d", semCount);
		return;
	}
	if (CUS_OS_OK != MsPollSem(CUS_KERNELTEST_SEM_0))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_1: step 6 Fail");
		return;
	}
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &semCount);
	if (0 < semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_1: step 7 Fail, %d", semCount);
		return;
	}
	MsProduceSem(CUS_KERNELTEST_SEM_2);
	MsConsumeSem(CUS_KERNELTEST_SEM_0);
	ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_1: Not reached");
}

static void __test_os_sem_entry_2(void *userdata)
{
	s16 semCount = 0;

	MsConsumeSem(CUS_KERNELTEST_SEM_0);
	if (0 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_2: step 1 Fail, %d", q);
		return;
	}
	q++;
	MsProduceSem(CUS_KERNELTEST_SEM_1);
	MsConsumeSem(CUS_KERNELTEST_SEM_0);
	if (2 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_2: step 2 Fail, %d", q);
		return;
	}
	q++;
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &semCount);
	if (0 < semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_2: step 3 Fail, %d", semCount);
		return;
	}
	if (CUS_OS_OK == MsConsumeSemDelay(CUS_KERNELTEST_SEM_0, 10))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_2: step 4 Fail");
		return;
	}
	MsProduceSem(CUS_KERNELTEST_SEM_0);
	if (3 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_2: step 5 Fail, %d", q);
		return;
	}
	q++;
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &semCount);
	if (0 >= semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_2: step 6 Fail, %d", semCount);
		return;
	}
	MsProduceSem(CUS_KERNELTEST_SEM_1);
	MsGetSemCount(CUS_KERNELTEST_SEM_2, &semCount);
	if (0 < semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_2: step 7 Fail, %d", semCount);
		return;
	}
	MsConsumeSem(CUS_KERNELTEST_SEM_2);
	if (5 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_2: step 8 Fail, %d", q);
		return;
	}
	q++;
	ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_2: Pass");
}

static void __test_os_sem_entry_3(void *userdata)
{
	s16 semCount = 0;

	MsGetSemCount(CUS_KERNELTEST_SEM_1, &semCount);
	if (0 >= semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_3: step 1 Fail, %d", semCount);
		return;
	}
	MsConsumeSem(CUS_KERNELTEST_SEM_1);
	if (1 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_3: step 2 Fail, %d", q);
		return;
	}
	q++;
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &semCount);
	if (0 < semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_3: step 3 Fail, %d", semCount);
		return;
	}
	MsProduceSem(CUS_KERNELTEST_SEM_0);
	MsConsumeSem(CUS_KERNELTEST_SEM_1);
	if (4 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_3: step 4 Fail, %d", q);
		return;
	}
	q++;
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &semCount);
	if (0 >= semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_3: step 5 Fail, %d", semCount);
		return;
	}
	if (CUS_OS_OK != MsConsumeSemDelay(CUS_KERNELTEST_SEM_0, 10))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_3: step 6 Fail");
		return;
	}
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &semCount);
	if (0 < semCount)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_3: step 7 Fail, %d", semCount);
		return;
	}
	MsProduceSem(CUS_KERNELTEST_SEM_2);
	MsConsumeSem(CUS_KERNELTEST_SEM_0);
	ven_std_sprintf((char*)KerTestOutput, "__test_os_sem_entry_3: Not reached");
}

static void __test_os_flag_entry_0(void *userdata)
{
	if (0 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 1 Fail");
		return;
	}
	MsFlagSetbits(&KerTestFlag[0], 0x1);
	if (1 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 2 Fail");
		return;
	}
	MsFlagSetbits(&KerTestFlag[0], 0x3);
	if (3 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 3 Fail");
		return;
	}
	MsFlagMaskbits(&KerTestFlag[0], ~0x5);
	if (2 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 4 Fail");
		return;
	}
	MsFlagSetbits(&KerTestFlag[0], ~0);
	if ((~0) != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 5 Fail");
		return;
	}
	MsFlagMaskbits(&KerTestFlag[0], 0);
	if (0 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 6 Fail");
		return;
	}
	if (0 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 7 Fail, %d", q);
		return;
	}
	q++;
	MsFlagSetbits(&KerTestFlag[1], 0x4);
	if (0x4 != MsFlagPeek(&KerTestFlag[1]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 8 Fail");
		return;
	}
	if (1 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 9 Fail, %d", q);
		return;
	}
	q++;
	MsFlagSetbits(&KerTestFlag[1], 0x18);
	MsFlagWait(&KerTestFlag[1], 0x11, MS_FLAG_WAITMODE_AND|MS_FLAG_WAITMODE_CLR);
	if (0 != MsFlagPeek(&KerTestFlag[1]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 10 Fail");
		return;
	}
	if (3 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 11 Fail, %d", q);
		return;
	}
	q++;
	MsFlagSetbits(&KerTestFlag[0], 0x2);
	MsFlagWait(&KerTestFlag[1], 0x10, MS_FLAG_WAITMODE_AND);
	MsFlagSetbits(&KerTestFlag[0], 0x1);
	MsFlagWait(&KerTestFlag[1], 0x11, MS_FLAG_WAITMODE_AND|MS_FLAG_WAITMODE_CLR);
	MsFlagWait(&KerTestFlag[2], 0x2, MS_FLAG_WAITMODE_OR);
	if (20 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 12 Fail, %d", q);
		return;
	}
	MsFlagTimedWait(&KerTestFlag[2], 0x10, MS_FLAG_WAITMODE_AND, 20);
	if (21 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: step 13 Fail, %d", q);
		return;
	}
	q++;
	MsFlagWait(&KerTestFlag[0], 0x1, MS_FLAG_WAITMODE_OR);
	ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_0: Not reached");
}

static void __test_os_flag_entry_1(void *userdata)
{
	MsFlagWait(&KerTestFlag[1], 0xc, MS_FLAG_WAITMODE_AND);
	if (2 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 1 Fail, %d", q);
		return;
	}
	q++;
	if (0x10 != MsFlagPeek(&KerTestFlag[1]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 2 Fail");
		return;
	}
	MsFlagSetbits(&KerTestFlag[1], 0x1);
	MsFlagWait(&KerTestFlag[0], 0x3, MS_FLAG_WAITMODE_OR);
	if (4 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 3 Fail, %d", q);
		return;
	}
	q++;
	if (0 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 4 Fail");
		return;
	}
	MsFlagSetbits(&KerTestFlag[1], 0xf0);
	MsFlagWait(&KerTestFlag[0], 0x5, MS_FLAG_WAITMODE_AND|MS_FLAG_WAITMODE_CLR);
	if (0 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 5 Fail");
		return;
	}
	if (0x80 != MsFlagPeek(&KerTestFlag[1]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 6 Fail");
		return;
	}
	if (5 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 7 Fail, %d", q);
		return;
	}
	q++;
	MsFlagMaskbits(&KerTestFlag[1], 0);
	if (0 != MsFlagPeek(&KerTestFlag[1]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 8 Fail");
		return;
	}
	MsFlagSetbits(&KerTestFlag[0], 0x55);
	if (0x55 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 9 Fail");
		return;
	}
	if (0x55 != MsFlagPoll(&KerTestFlag[0], 0x3, MS_FLAG_WAITMODE_OR))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 10 Fail");
		return;
	}
	if (0 != MsFlagPoll(&KerTestFlag[0], 0xf, MS_FLAG_WAITMODE_AND))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 11 Fail");
		return;
	}
	if (0 != MsFlagPoll(&KerTestFlag[0], 0xa, MS_FLAG_WAITMODE_OR))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 12 Fail");
		return;
	}
	if (0x54 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 13 Fail");
		return;
	}
	if (0x54 != MsFlagPoll(&KerTestFlag[0], 0xf, MS_FLAG_WAITMODE_OR|MS_FLAG_WAITMODE_CLR))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 14 Fail");
		return;
	}
	if (0 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 15 Fail");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}
	MsFlagSetbits(&KerTestFlag[0], 0x50);
	if (0x50 != MsFlagPoll(&KerTestFlag[0], 0x10, MS_FLAG_WAITMODE_AND|MS_FLAG_WAITMODE_CLR))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 16 Fail");
		return;
	}
	if (0 != MsFlagPeek(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 17 Fail");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}
	MsFlagMaskbits(&KerTestFlag[0], 0);
	if (FALSE != MsFlagWaiting(&KerTestFlag[0]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 18 Fail");
		return;
	}
	MsSleep(10);
	if (TRUE != MsFlagWaiting(&KerTestFlag[1]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 19 Fail");
		return;
	}
	MsFlagSetbits(&KerTestFlag[1], ~0);
	if (TRUE != MsFlagWaiting(&KerTestFlag[1]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 20 Fail");
		return;
	}
	MsFlagSetbits(&KerTestFlag[1], 0x11);
	if (FALSE != MsFlagWaiting(&KerTestFlag[1]))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 21 Fail");
		return;
	}
	q = 20;
	MsFlagSetbits(&KerTestFlag[2], 0x2);
	MsFlagSetbits(&KerTestFlag[2], 0x2);
	if (20 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 21 Fail, %d", q);
		return;
	}
	MsFlagTimedWait(&KerTestFlag[2], 0x20, MS_FLAG_WAITMODE_AND, 10);
	if (22 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: step 22 Fail, %d", q);
		return;
	}
	q++;
	ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_1: Pass");
}

static void __test_os_flag_entry_2(void *userdata)
{
	MsFlagWait(&KerTestFlag[1], 0x60, MS_FLAG_WAITMODE_OR);
	MsFlagSetbits(&KerTestFlag[0], 0x4);
	MsFlagWait(&KerTestFlag[1], 0x11, MS_FLAG_WAITMODE_AND|MS_FLAG_WAITMODE_CLR);
	MsFlagWait(&KerTestFlag[2], 0x2, MS_FLAG_WAITMODE_OR);
	if (20 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_2: step 1 Fail, %d", q);
		return;
	}
	if (0 != MsFlagTimedWait(&KerTestFlag[2], 0x40, MS_FLAG_WAITMODE_AND, 5))
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_2: step 2 Fail");
		return;
	}
	if (20 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_2: step 3 Fail, %d", q);
		return;
	}
	q++;
	MsFlagSetbits(&KerTestFlag[2], 0x10);
	MsFlagWait(&KerTestFlag[0], 1, MS_FLAG_WAITMODE_OR);
	ven_std_sprintf((char*)KerTestOutput, "__test_os_flag_entry_2: Not reached");
}

static void __test_os_int_entry_0(void *userdata)
{
	u32 i = 0;

	while((i++)<10000)
	{
		q++;
		MsSleep(1);
	}
}

static void __test_os_int_entry_1(void *userdata)
{
	u32 i = 0, j = 0;
	MsIntMask_e itMask;

	while((i++)<10000)
	{
		itMask= MsDisableInterrupt();
		for (;j<100;j++)
		{
			if ((j%2) == 0)
				q++;
			else
				q--;
		}
		q++;
		MsEnableInterrupt(itMask);
		MsSleep(1);
	}
}

static void __test_os_int_entry_2(void *userdata)
{
	u32 i = 0, j = 0;
	MsIntMask_e itMask;

	while((i++)<10000)
	{
		itMask= MsDisableInterruptUser();
		for (;j<100;j++)
		{
			if ((j%2) == 0)
				q++;
			else
				q--;
		}
		q++;
		MsEnableInterruptUser(itMask);
		MsSleep(1);
	}
}

static void __test_os_int_entry_3(void *userdata)
{
	u32 i = 0, j = 0;

	while((i++)<10000)
	{
		MsEnterRegion();
		for (;j<100;j++)
		{
			if ((j%2) == 0)
				q++;
			else
				q--;
		}
		q++;
		MsLeaveRegion();
		MsSleep(1);
	}
}

static void __test_os_mbox_parser_0(vm_msg_t *pMessage)
{
	MsMsg_t *pMsg = (MsMsg_t*)pMessage;

	if (pMsg == NULL)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mbox_parser_0: Null message");
		return;
	}
	else if (pMsg->Header.TypMsg == VM_OS_TIMER_EXPIRED)
	{
		if (KERNEL_TEST_MSG1 != MsGetMsgAsTimerID(pMsg))
		{
			ven_std_sprintf((char*)KerTestOutput, "__test_os_mbox_parser_0: Wrong timer message 0x%4x", MsGetMsgAsTimerID(pMsg));
			return;
		}
		q++;
		if (20 == q)
			MsStartTimer(KERNEL_TEST_MSG2, MsCurrTask(), 500);
		else
			MsStartTimer(KERNEL_TEST_MSG1, MsCurrTask(), 1);
	}
	else if (pMsg->Header.TypMsg == KERNEL_TEST_MSG0)
	{
		q++;
	}
	else if (pMsg->Header.TypMsg == KERNEL_TEST_MSG1)
	{
		q++;
		MsStartTimer(KERNEL_TEST_MSG1, MsCurrTask(), 1);
	}
	else
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mbox_parser_0: Unknown message 0x%4x", pMsg->Header.TypMsg);
		return;
	}
}


#if defined (__MMAP__)
#include "sys_sys_mmap_mgr.h"

void __test_os_mmap_entry_0(void *userdata)
{
	u32 tmp = 0, nSrc = 0, nDst = 0;
	VFS_FILE *testfd = 0, *testfd2 = 0;
	VFS_File_Info_t finfo;
	u32 flen = 0, len = 0;
	static u8 ttt[3999];

	testfd = file_fopen( (u16*) L"/CARD/sysbt/tmp0.txt", (ascii *)"r");
	if (NULL == testfd)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_0: open /CARD/sysbt/tmp0.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	if(FAT_NO_ERROR != file_finfo(testfd, &finfo))
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_0: get /CARD/sysbt/tmp0.txt fileinfo failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	flen = finfo.Size;

	testfd2 = file_fopen( (u16*) L"/CARD/sysbt/tmpout0.txt", (ascii *)"w");
	if (NULL == testfd2)
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_0: open /CARD/sysbt/tmpout0.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	tmp = (u32)Msmmap(NULL, flen, PROT_READ, MAP_PRIVATE, (int)testfd, 0);
	if (NULL == tmp)
	{
		file_fclose(testfd);
		file_fclose(testfd2);
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_0: mmap %d len=%d failed", testfd, flen);
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	nSrc = tmp;
	nDst = nSrc + flen;
	do
	{
		len = ((nDst-tmp)>=sizeof(ttt)) ? sizeof(ttt) : (nDst-tmp);
		memcpy((void*)&ttt[0], (void*)tmp, len);
		file_fwrite(testfd2, (u8*)&ttt[0], len);
		tmp += sizeof(ttt);
		MsSleep(DrvTimerMs2Ostick(3));
	} while(tmp < nDst);

	Msmunmap((void*)nSrc, flen);

	file_fclose(testfd);
	file_fclose(testfd2);

	ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_0: Pass");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

	q++;
}

static void __test_os_mmap_entry_1(void *userdata)
{
	u32 tmp = 0, nSrc = 0, nDst = 0;
	VFS_FILE *testfd = 0, *testfd2 = 0;
	VFS_File_Info_t finfo;
	u32 flen = 0, len = 0;
	static u8 ttt[3999];

	testfd = file_fopen((u16*) L"/CARD/sysbt/tmp1.txt", (ascii *)"r");
	if (NULL == testfd)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_1: open /CARD/sysbt/tmp1.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	if(FAT_NO_ERROR != file_finfo(testfd, &finfo))
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_1: get /CARD/sysbt/tmp1.txt fileinfo failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	flen = finfo.Size;

	testfd2 = file_fopen((u16*) L"/CARD/sysbt/tmpout1.txt", (ascii *)"w");
	if (NULL == testfd2)
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_1: open /CARD/sysbt/tmpout1.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	tmp = (u32)Msmmap(NULL, flen, PROT_READ, MAP_PRIVATE, (int)testfd, 0);
	if (NULL == tmp)
	{
		file_fclose(testfd);
		file_fclose(testfd2);
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_1: mmap %d len=%d failed", testfd, flen);
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	nSrc = tmp;
	nDst = nSrc + flen;
	do
	{
		len = ((nDst-tmp)>=sizeof(ttt)) ? sizeof(ttt) : (nDst-tmp);
		memcpy((void*)&ttt[0], (void*)tmp, len);
		file_fwrite(testfd2, (u8*)&ttt[0], len);
		tmp += sizeof(ttt);
		MsSleep(DrvTimerMs2Ostick(2));
	} while(tmp < nDst);

	Msmunmap((void*)nSrc, flen);

	file_fclose(testfd);
	file_fclose(testfd2);

	ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_1: Pass");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

	q++;
}

static void __test_os_mmap_entry_2(void *userdata)
{
	u32 tmp = 0, nSrc = 0, nDst = 0;
	VFS_FILE *testfd = 0, *testfd2 = 0;
	VFS_File_Info_t finfo;
	u32 flen = 0, len = 0;
	static u8 ttt[3999];

	testfd = file_fopen((u16*) L"/CARD/sysbt/tmp2.txt", (ascii *) "r");
	if (NULL == testfd)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_2: open /CARD/sysbt/tmp2.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	if(FAT_NO_ERROR != file_finfo(testfd, &finfo))
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_2: get /CARD/sysbt/tmp0.txt fileinfo failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	flen = finfo.Size;

	testfd2 = file_fopen((u16*)L"/CARD/sysbt/tmpout2.txt", "w");
	if (NULL == testfd2)
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_2: open /CARD/sysbt/tmpout2.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	tmp = (u32)Msmmap(NULL, flen, PROT_READ, MAP_PRIVATE, (int)testfd, 0);
	if (NULL == tmp)
	{
		file_fclose(testfd);
		file_fclose(testfd2);
		ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_2: mmap %d len=%d failed", testfd, flen);
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	nSrc = tmp;
	nDst = nSrc + flen;
	do
	{
		len = ((nDst-tmp)>=sizeof(ttt)) ? sizeof(ttt) : (nDst-tmp);
		memcpy((void*)&ttt[0], (void*)tmp, len);
		file_fwrite(testfd2, (u8*)&ttt[0], len);
		tmp += sizeof(ttt);
		MsSleep(DrvTimerMs2Ostick(1));
	} while(tmp < nDst);

	Msmunmap((void*)nSrc, flen);

	file_fclose(testfd);
	file_fclose(testfd2);

	ven_std_sprintf((char*)KerTestOutput, "__test_os_mmap_entry_2: Pass");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

	q++;
}

#endif

#if defined(__TARGET__)
// 200
static void _test_OS_MsInitSem_(void)
{
    s16 initial_value, assign_initial_value, assign_current_value;
    s16 ret;
    rtk_Semaphor_t   *PtrSem;

    initial_value = 10;

	ret = MsInitSem(CUS_KERNELTEST_SEM_0, initial_value) ;

    PtrSem = Rtk_Ptr1stSem + CUS_KERNELTEST_SEM_0 ;
    assign_initial_value = PtrSem->InitValue ;
    assign_current_value = PtrSem->CurrentValue ;

    ven_std_sprintf((char*)KerTestOutput, "initial =%d and current =%d", assign_initial_value, assign_current_value) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_OK) && (assign_initial_value==initial_value) && (assign_current_value==initial_value)) ;
}

// 201
static void _test_OS_MsInitSemExtend_(void)
{
    s16 initial_value, current_value, assign_initial_value, assign_current_value;
    s16 ret;
    rtk_Semaphor_t   *PtrSem;

    initial_value = 10, current_value=6;

    ret = MsInitSemExtend(CUS_KERNELTEST_SEM_0, initial_value, current_value);

    PtrSem = Rtk_Ptr1stSem + CUS_KERNELTEST_SEM_0 ;
    assign_initial_value = PtrSem->InitValue ;
    assign_current_value = PtrSem->CurrentValue ;

	ven_std_sprintf((char*)KerTestOutput, "initial=%d and current=%d", assign_initial_value, assign_current_value) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_OK) && (assign_initial_value==initial_value) && (assign_current_value==current_value)) ;

}

// 202
static void _test_OS_MsProduceSem_(void)
{
    s16 initial_value, current_value, result_value1;
    s16 ret;

    initial_value = 10, current_value = 9;

    MsInitSemExtend(CUS_KERNELTEST_SEM_0, initial_value, current_value);
    ret = MsProduceSem(CUS_KERNELTEST_SEM_0);

	MsGetSemCount(CUS_KERNELTEST_SEM_0, &result_value1);

    ven_std_sprintf((char*)KerTestOutput, "initial=%d, Produce1 =%d", initial_value, result_value1 ) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_OK) && (result_value1==initial_value) ) ;

}


// 203
static void _test_OS_MsConsumeSem_(void)
{
    s16 initial_value, result_value1, result_value2;
    s16 ret1, ret2;

    initial_value = 10;

    MsInitSem(CUS_KERNELTEST_SEM_0, initial_value);
    ret1 = MsConsumeSem(CUS_KERNELTEST_SEM_0);
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &result_value1);
    ret2 = MsConsumeSem(CUS_KERNELTEST_SEM_0);
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &result_value2);

    ven_std_sprintf((char*)KerTestOutput, "initial =%d, Consume1 =%d, Consume2 =%d", initial_value, result_value1, result_value2) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret1==RTK_OK) && (ret2==RTK_OK) && \
		(result_value1==initial_value-1) && (result_value2==initial_value-2) ) ;

}

// 204
static void _test_OS_MsPollSem_1_(void)
{
    s16 initial_value, result_value1;
    s16 ret;

    initial_value = 10;

    MsInitSem(CUS_KERNELTEST_SEM_0, initial_value);
    ret = MsPollSem(CUS_KERNELTEST_SEM_0);
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &result_value1);

	ven_std_sprintf((char*)KerTestOutput, "initial=%d, Poll value=%d", initial_value, result_value1) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_OK) && (result_value1==initial_value-1)) ;

}

// 205
static void _test_OS_MsPollSem_2_(void)
{
    s16 initial_value, result_value1 ;
    s16 ret;

    initial_value = 0;

    MsInitSem(CUS_KERNELTEST_SEM_0, initial_value);
    ret = MsPollSem(CUS_KERNELTEST_SEM_0);
	MsGetSemCount(CUS_KERNELTEST_SEM_0, &result_value1);

	ven_std_sprintf((char*)KerTestOutput, "initial=%d, Poll value=%d", initial_value, result_value1) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_UNIT_NOAVAIL) && (result_value1==initial_value)) ;

}


// 206
static void _test_OS_MsConsumeSemDelay_1_(void)
{
    s16 initial_value, result_value1 ;
    s16 ret, waiting_time;

	initial_value = 10, waiting_time = 100 ;
    MsInitSem(CUS_KERNELTEST_SEM_0, initial_value);
    ret = MsConsumeSemDelay(CUS_KERNELTEST_SEM_0, waiting_time);

	MsGetSemCount(CUS_KERNELTEST_SEM_0, &result_value1);

	ven_std_sprintf((char*)KerTestOutput, "initial=%d, Poll value=%d", initial_value, result_value1) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_OK) && (result_value1==initial_value-1) ) ;

}


// 207
static void _test_OS_MsConsumeSemDelay_2_(void)
{
    s16 initial_value, result_value1;
    s16 ret, waiting_time, pass_time;

    initial_value = 0, waiting_time = 100 ;

    MsInitSem(CUS_KERNELTEST_SEM_0, initial_value);
	pass_time = MsGetOsTick();
    ret = MsConsumeSemDelay(CUS_KERNELTEST_SEM_0, waiting_time);
	pass_time = MsGetOsTick() - pass_time ;

	MsGetSemCount(CUS_KERNELTEST_SEM_0, &result_value1);

	ven_std_sprintf((char*)KerTestOutput, "initial=%d, Poll value=%d, pass_time = %d", \
		initial_value, result_value1, pass_time) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_NO_MESSAGE) && (result_value1==initial_value) && ((pass_time-waiting_time)<=10)) ;

}


// 208
static void _test_OS_MsProduceSemRtkReady_(void)
{
    s16 initial_value, cureent_value, result_value1;
    s16 ret;

    initial_value = 10, cureent_value=9 ;

    MsInitSemExtend(CUS_KERNELTEST_SEM_0, initial_value, cureent_value);
    ret = MsProduceSemRtkReady(CUS_KERNELTEST_SEM_0);

	MsGetSemCount(CUS_KERNELTEST_SEM_0, &result_value1);

	ven_std_sprintf((char*)KerTestOutput, "initial=%d, produce value=%d", initial_value, result_value1) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_OK) && (result_value1==initial_value) ) ;

}

// 209
static void _test_OS_MsConsumeSemRtkReady_(void)
{
    s16 initial_value, result_value1;
    s16 ret;

    initial_value = 10;

    MsInitSem(CUS_KERNELTEST_SEM_0, initial_value);
    ret = MsConsumeSemRtkReady(CUS_KERNELTEST_SEM_0);

	MsGetSemCount(CUS_KERNELTEST_SEM_0, &result_value1);

	ven_std_sprintf((char*)KerTestOutput, "initial=%d, Consume=%d", initial_value, result_value1) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_OK) && (result_value1==initial_value-1) ) ;

}

// 210
static void _test_OS_MsGetSemCount_(void)
{
    s16 initial_value, result_value1;
    s16 ret;
    rtk_Semaphor_t   *PtrSem;

    initial_value = 10;
    PtrSem = Rtk_Ptr1stSem + CUS_KERNELTEST_SEM_0 ;

    MsInitSem(CUS_KERNELTEST_SEM_0, initial_value);
    ret = MsGetSemCount(CUS_KERNELTEST_SEM_0, &result_value1);

    ven_std_sprintf((char*)KerTestOutput, "initial=%d, GetSemCount=%d", initial_value, result_value1) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_OK) && (result_value1==PtrSem->CurrentValue) ) ;

}

// 211
static void _test_OS_MsStartTimer_(void)
{
    u32       tid = 1936 ;
    s32       waittin_time=100, pass_time=-1;
	MsMailbox_e mboxID = (Rtk_NbOfMBox-1) ;
    MsOsErr_e     ret;
    MsObj_t    Obj;

	RtkInitMailBox(mboxID);
    pass_time = MsGetOsTick();
    ret = MsStartTimer((MsTimerId_e)tid, mboxID, waittin_time);
    MsReceive(mboxID, &Obj, NULL);
    pass_time = MsGetOsTick() - pass_time;

    ven_std_sprintf((char*)KerTestOutput, "type=%d, tid=%d, pass time=%d", Obj.Type, MsGetMsgAsTimerID(Obj.Msg), pass_time) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_OK)  && (pass_time>=waittin_time-2) && (pass_time<=waittin_time+2) ) ;
}


// 212
static void _test_OS_MsStartPeriodicTimer_(void)
{
    u32       tid = 1936 ;
    s32       waittin_time=100, pass_time=-1;
	MsMailbox_e mboxID = (Rtk_NbOfMBox-1) ;
    MsOsErr_e     ret;
    MsObj_t    Obj;
	s32 TIMER_SUCCESS=TRUE, i;


	RtkInitMailBox((MsMailbox_e)(Rtk_NbOfMBox-1));

    ret = MsStartPeriodicTimer(tid, mboxID, waittin_time);

    pass_time = MsGetOsTick();
	for(i=0; i<3; ++i){
		MsReceive((MsMailbox_e)(Rtk_NbOfMBox-1), &Obj, NULL);
		TIMER_SUCCESS &= (tid==MsGetMsgAsTimerID(Obj.Msg)) ;
	}
    pass_time = MsGetOsTick() - pass_time;

    ven_std_sprintf((char*)KerTestOutput, "msg id= %d, pass time=%d",MsGetMsgAsTimerID(Obj.Msg), pass_time) ;

	MsStopTimer(tid);

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((ret==RTK_OK)  && (pass_time>=waittin_time*3) && (pass_time<=waittin_time*3+5) \
		 && TIMER_SUCCESS ) ;
}


// 213
static void _test_OS_MsStopTimer_(void)
{
    u32       tid = 1936 ;
    s32       waittin_time=100 ;
	MsMailbox_e mboxID = (Rtk_NbOfMBox-1) ;
	s32 remaining_time=-1;


    MsStartTimer(tid, mboxID, waittin_time);
	MsSleep(waittin_time-60);
    remaining_time = MsStopTimer(tid);

    ven_std_sprintf((char*)KerTestOutput, "remaining_time=%d", remaining_time) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT( (remaining_time<=60+1) ) ;
}


// 214
static void _test_OS_MsIsTimerActive_(void)
{
    u32       tid = 1936 ;
    s32       waittin_time=100;
	MsMailbox_e mboxID = (Rtk_NbOfMBox-1) ;
    bool IsActive1, IsActive2;

    MsStartTimer(tid, mboxID, waittin_time);
	IsActive1 = MsIsTimerActive(tid) ;
	MsStopTimer(tid);
	IsActive2 = MsIsTimerActive(tid) ;

    ven_std_sprintf((char*)KerTestOutput, "IsActive1=%d, IsActive2=%d", IsActive1, IsActive2) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT((IsActive1==TRUE) && (IsActive2==FALSE)) ;
}
#endif // __TARGET__

// 215
s8  t_count= 0;
static void tmp_send_msg(MsTimerId_e eTimerID, u32 UserData){
	t_count++;
}

static void _test_OS_MsStartCbTimer_(void)
{
    u32       tid = 1936 ;
    s32       cb_success=TRUE;
	u32 tmp_UserData = 1936;

	t_count = 0 ;
    MsStartCbTimer((MsTimerId_e*)&tid, tmp_send_msg, tmp_UserData, 50, 100);
	MsSleep(460);
	MsStopTimer(tid);
	cb_success &= (t_count==5) ;

    MsStartCbTimer((MsTimerId_e*)&tid, tmp_send_msg, tmp_UserData, 50, 0);
	MsSleep(55);
	cb_success &= (t_count==6) ;
	cb_success &= !MsIsTimerActive(tid) ;


    ven_std_sprintf((char*)KerTestOutput, "t_count = %d", t_count) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT( cb_success ) ;

}

#define TEST_OS_MEM_SIZE	44

// 216
static void _test_OS_MsAllocateMem_1_(void)
{
    bool ALLOCATE_SUCCESS = TRUE;
    void *MemoryPtr = NULL;

	MemoryPtr= MsAllocateMem( TEST_OS_MEM_SIZE);
    ALLOCATE_SUCCESS &= (MemoryPtr!=NULL);
    MsReleaseMemory(MemoryPtr);

    ven_std_sprintf((char*)KerTestOutput, "ALLOCATE_SUCCESS = %d", ALLOCATE_SUCCESS) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT( ALLOCATE_SUCCESS ) ;
}


// 217
static void _test_OS_MsAllocateMem_2_(void)
{
    bool ALLOCATE_SUCCESS = TRUE;
    void *MemoryPtr = NULL;

    MemoryPtr = MsAllocateMem(100000000);
    ALLOCATE_SUCCESS &= (MemoryPtr!=NULL);

    ven_std_sprintf((char*)KerTestOutput, "ALLOCATE_SUCCESS = %d", ALLOCATE_SUCCESS) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT( !ALLOCATE_SUCCESS ) ;
}


// 218
static void _test_OS_MsMemoryReAllocate_(void)
{
    bool REALLOCATE_SUCCESS = TRUE;
    int *MemoryPtr = NULL;
	int  ORI_VALUE = 50, NEW_VALUE=-1, ORI_SIZE=TEST_OS_MEM_SIZE, NEW_SIZE=TEST_OS_MEM_SIZE*2;

	MemoryPtr = (int *)MsAllocateMem( ORI_SIZE );
	(*MemoryPtr) = ORI_VALUE ;
	MemoryPtr = (int*)MsMemoryReAllocate( MemoryPtr, NEW_SIZE );
	REALLOCATE_SUCCESS &= ((*MemoryPtr)==ORI_VALUE) ;
	NEW_VALUE = ORI_VALUE ;
	REALLOCATE_SUCCESS &= (MsQueryMemRealSize(MemoryPtr)>=NEW_SIZE) ;
	MsReleaseMemory(MemoryPtr);

    ven_std_sprintf((char*)KerTestOutput, "REALLOCATE_SUCCESS = %d, %d", REALLOCATE_SUCCESS, NEW_VALUE) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT( REALLOCATE_SUCCESS ) ;
}


// 219
static void _test_OS_MsLinkMemory_(void)
{
    bool RELEASE_SUCCESS = TRUE;
    void *MemoryPtr = NULL;
	u32 ret;

    MemoryPtr = MsAllocateMem( TEST_OS_MEM_SIZE );
    MsLinkMemory(MemoryPtr);
    ret = MsReleaseMemory(MemoryPtr);
	RELEASE_SUCCESS &= (MemoryPtr!=NULL);
	ret &= (MsIsPoolMemory(MemoryPtr)?(ret==RTK_NOT_RELEASED):(ret==RTK_NOT_HEAP_RELEASE));

	MsReleaseMemory(MemoryPtr);

    ven_std_sprintf((char*)KerTestOutput, "release success? %d", ret) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT(ret && RELEASE_SUCCESS ) ;
}



static void * _test_get_pool_memory_(u32 Size)
{
	extern u8 _RtkQueryPoolStatus(u8, rtk_memoryContext_t *, rtk_PtrRegion_e, u16 *, u16 *, u16*, u16 *);

	void *MemoryPtr = NULL;
	u8 PoolId;
	rtk_MaskImage_t			MaskInt;
	u16				totalClusters = 0;
	u16				usedClusters	= 0;
	u16				clusterLength	= 0;
	u8 round = 1 ;

#ifndef  __SDK_SIMULATION__
	MaskInt = RTK2_DISABLE_K();
	while( !MemoryPtr )
	{
		// since MsGetPoolMemory call _RtkFindBestPoolGeneric( size"+1", ... ) to get PoolId, we must add 1 for query correct pool status
		MsFindBestPool(Size*round+1, &PoolId);
		_RtkQueryPoolStatus(PoolId, &(((pMemHandle_t)ms_memoryhandle)->rtkCtxt), RTK_PTR_STACK, &clusterLength, &totalClusters, &usedClusters, NULL);
		if( totalClusters > usedClusters )
		{
			/* adding above error handling to avoid querying memory from a pool without free memory (it cause assert)*/
#endif

			MemoryPtr = MsGetPoolMemory( Size*round );

#ifndef  __SDK_SIMULATION__
		}
		round++ ;
	}
	RTK2_ENABLE_K(MaskInt);
#endif


	return MemoryPtr;

}



// 220
static void _test_OS_MsGetPoolMemory_(void)
{
	bool ALLOCATE_SUCCESS = TRUE, IsPool =TRUE;
	void *MemoryPtr = NULL;

	MemoryPtr = _test_get_pool_memory_(TEST_OS_MEM_SIZE);
	ALLOCATE_SUCCESS &= (MemoryPtr!=NULL);
	IsPool &= MsIsPoolMemory(MemoryPtr);
	MsReleaseMemory(MemoryPtr);


	ven_std_sprintf((char*)KerTestOutput, "ALLOCATE_SUCCESS = %d", ALLOCATE_SUCCESS) ;

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
	VEN_TEST_CHECK_RESULT( ALLOCATE_SUCCESS && IsPool ) ;
}

// 221
static void _test_OS_MsGetHeapMemory_(void)
{
    bool ALLOCATE_SUCCESS = TRUE;
    void *MemoryPtr = NULL;
	u32 i;

	for(i=1; i<4; ++i){
		MemoryPtr = MsGetHeapMemory( 50*i );
		ALLOCATE_SUCCESS &= MsIsHeapMemory(MemoryPtr);
		MsReleaseMemory(MemoryPtr);
    }

    ven_std_sprintf((char*)KerTestOutput, "ALLOCATE_SUCCESS = %d", ALLOCATE_SUCCESS) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT( ALLOCATE_SUCCESS ) ;
}

// 222
static void _test_OS_MsHeapRealloc_(void)
{
    bool REALLOCATE_SUCCESS = TRUE;
    int *MemoryPtr = NULL;
	int  ORI_VALUE = 50, NEW_VALUE=-1, ORI_SIZE=TEST_OS_MEM_SIZE, NEW_SIZE=TEST_OS_MEM_SIZE*2;

	MemoryPtr = (int *)MsGetHeapMemory( ORI_SIZE );
	(*MemoryPtr) = ORI_VALUE ;
	MemoryPtr = (int*)MsHeapRealloc( MemoryPtr, NEW_SIZE );
	NEW_VALUE = (*MemoryPtr) ;
	REALLOCATE_SUCCESS &= (NEW_VALUE==ORI_VALUE) ;
	MsReleaseHeapMemory(MemoryPtr);

    ven_std_sprintf((char*)KerTestOutput, "MemoryPtr = 0x%x, RELEASE_SUCCESS = %d", (unsigned int)MemoryPtr, REALLOCATE_SUCCESS) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT( REALLOCATE_SUCCESS ) ;
}

// 223
static void _test_OS_MsReleaseHeapMemory_(void)
{
    bool RELEASE_SUCCESS = TRUE;
    void *MemoryPtr = NULL;

	MemoryPtr = MsGetHeapMemory( TEST_OS_MEM_SIZE );
	MsReleaseHeapMemory(MemoryPtr);
	RELEASE_SUCCESS &= (MemoryPtr==NULL);

    ven_std_sprintf((char*)KerTestOutput, "MemoryPtr = 0x%x, RELEASE_SUCCESS = %d", (unsigned int)MemoryPtr, RELEASE_SUCCESS) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT( RELEASE_SUCCESS ) ;
}


// 224
static void _test_OS_MsReleaseMemory_(void)
{
	u8 RELEASE_SUCCESS=TRUE;
	void *MemoryPtr = NULL;

	MemoryPtr = _test_get_pool_memory_(TEST_OS_MEM_SIZE);
	MsReleaseMemory(MemoryPtr);
	RELEASE_SUCCESS = (MemoryPtr==NULL?RELEASE_SUCCESS:FALSE);
	MemoryPtr = MsGetHeapMemory( TEST_OS_MEM_SIZE);
	MsReleaseMemory(MemoryPtr);
	RELEASE_SUCCESS = (MemoryPtr==NULL?RELEASE_SUCCESS:FALSE);

	ven_std_sprintf((char*)KerTestOutput, "RELEASE_SUCCESS = %d", RELEASE_SUCCESS) ;

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
	VEN_TEST_CHECK_RESULT( RELEASE_SUCCESS ) ;
}



// 225
static void _test_OS_MsIsPoolMemory_(void)
{
	u8 ALLOCATE_SUCCESS=TRUE;
	void *MemoryPtr = NULL;

	MemoryPtr = _test_get_pool_memory_(TEST_OS_MEM_SIZE);
	ALLOCATE_SUCCESS &= MsIsPoolMemory(MemoryPtr);
	MsReleaseMemory(MemoryPtr);

	MemoryPtr = MsGetHeapMemory( TEST_OS_MEM_SIZE );
	ALLOCATE_SUCCESS &= !MsIsPoolMemory(MemoryPtr);
	MsReleaseMemory(MemoryPtr);

	ven_std_sprintf((char*)KerTestOutput, "ALLOCATE_SUCCESS = %d", ALLOCATE_SUCCESS) ;

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
	VEN_TEST_CHECK_RESULT( ALLOCATE_SUCCESS ) ;
}


// 226
static void _test_OS_MsIsHeapMemory_(void)
{
	u8 ALLOCATE_SUCCESS=TRUE;
	void *MemoryPtr = NULL;

	MemoryPtr = MsGetHeapMemory( TEST_OS_MEM_SIZE );
	ALLOCATE_SUCCESS &= MsIsHeapMemory(MemoryPtr);
	MsReleaseMemory(MemoryPtr);

	MemoryPtr = _test_get_pool_memory_(TEST_OS_MEM_SIZE);
	ALLOCATE_SUCCESS &= !MsIsHeapMemory(MemoryPtr);
	MsReleaseMemory(MemoryPtr);

	ven_std_sprintf((char*)KerTestOutput, "ALLOCATE_SUCCESS = %d", ALLOCATE_SUCCESS) ;

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
	VEN_TEST_CHECK_RESULT( ALLOCATE_SUCCESS ) ;
}

static void _test_OS_MsAllocateNonCacheMem_0(void)
{
	u8 ALLOCATE_SUCCESS=TRUE;
	void *MemoryPtr = NULL;

	MemoryPtr = MsAllocateNonCacheMem( TEST_OS_MEM_SIZE );
	ALLOCATE_SUCCESS &= MsIsHeapMemory(MemoryPtr);

  if (MemoryPtr)
  {
    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_0: ptr=0x%x, nSize=%d, nAligned=%d , nActual=%d", (unsigned int)MemoryPtr, TEST_OS_MEM_SIZE, 1<<6, MsQueryMemRealSize(MemoryPtr));
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
  }

  if ((u32)MemoryPtr&((1<<6)-1))
	  ALLOCATE_SUCCESS &= FALSE;

  MsReleaseMemory(MemoryPtr);

	ven_std_sprintf((char*)KerTestOutput, "ALLOCATE_SUCCESS = %d", ALLOCATE_SUCCESS) ;
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
	VEN_TEST_CHECK_RESULT( ALLOCATE_SUCCESS ) ;
}


static void _test_OS_MsAllocateNonCacheMem_1(void)
{
	u8 ALLOCATE_SUCCESS=TRUE;
	void *MemoryPtr = NULL;

  int size = 1025;

	MemoryPtr = MsAllocateNonCacheMem( size );
	ALLOCATE_SUCCESS &= MsIsHeapMemory(MemoryPtr);

  if (MemoryPtr)
  {
    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_1: ptr=0x%x, nSize=%d, nAligned=%d , nActual=%d", (unsigned int)MemoryPtr, size, 1<<6, MsQueryMemRealSize(MemoryPtr));
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    if ((u32)MemoryPtr&((1<<6)-1))
      ALLOCATE_SUCCESS &= FALSE;

    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_1: write cached ptr=0x%x, value = 0x%x", (u32)MsVA2PA(MemoryPtr), 0x12345678);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    *(u32 *)MsVA2PA(MemoryPtr) = 0x12345678;
    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_1: read cached ptr=0x%x, value = 0x%x", (u32)MsVA2PA(MemoryPtr), *(u32 *)MsVA2PA(MemoryPtr));
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_1: read uncached ptr=0x%x, value = 0x%x", (u32)MemoryPtr, *(u32 *)MemoryPtr);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_1: write uncached ptr=0x%x, value = 0x%x", (u32)MemoryPtr, 0x87654321);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    *(u32 *)MemoryPtr = 0x87654321;
    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_1: read cached ptr=0x%x, value = 0x%x", (u32)MsVA2PA(MemoryPtr), *(u32 *)MsVA2PA(MemoryPtr));
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_1: read uncached ptr=0x%x, value = 0x%x", (u32)MemoryPtr, *(u32 *)MemoryPtr);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_1: flush cached ptr=0x%x", (u32)MsVA2PA(MemoryPtr));
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    sys_flush_data_cache_buffer((u32)MsVA2PA(MemoryPtr), size);
    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_1: read cached ptr=0x%x, value = 0x%x", (u32)MsVA2PA(MemoryPtr), *(u32 *)MsVA2PA(MemoryPtr));
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    ven_std_sprintf((char*)KerTestOutput, "_test_OS_MsAllocateNonCacheMem_1: read uncached ptr=0x%x, value = 0x%x", (u32)MemoryPtr, *(u32 *)MemoryPtr);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    MsReleaseMemory(MemoryPtr);

    ven_std_sprintf((char*)KerTestOutput, "ALLOCATE_SUCCESS = %d", ALLOCATE_SUCCESS) ;
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT( ALLOCATE_SUCCESS ) ;
  }
  else
    VEN_TEST_CHECK_RESULT( 0 ) ;
}


// 227
static void _test_OS_MsQueryMemRealSize_(void)
{
    u8 QUERY_SIZE_SUCCESS=TRUE;
	void *MemoryPtr;
	u32 i ;

	for(i=1; i<10;i++){
		MemoryPtr = MsAllocateMem( i*2 );
		QUERY_SIZE_SUCCESS &= (i*2 <= MsQueryMemRealSize(MemoryPtr));
		MsReleaseMemory(MemoryPtr);
	}

    ven_std_sprintf((char*)KerTestOutput, "QUERY_SIZE_SUCCESS = %d", QUERY_SIZE_SUCCESS) ;

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput) ;
    VEN_TEST_CHECK_RESULT( QUERY_SIZE_SUCCESS ) ;
}

// 228
static void _test_check_os_ready(void)
{
    bool isReady = FALSE;

    isReady = MsCheckOsReady();

    VEN_TEST_CHECK_RESULT(isReady == TRUE);
}

// 229
static void _test_os_tick(void)
{
    u32 t0 = 0, t1 =0;
    u32 delta_t = 0;

    t0 = MsGetOsTick();
    MsSleep(1000);
    t1 = MsGetOsTick();

    delta_t = t1 - t0;
    VEN_TEST_CHECK_RESULT((delta_t - 1000) < 50);
}

static void _test_os_tick_ext(void)
{

    u64 t0 = 0, t1 =0;
    u64 delta_t = 0;

    u32 a1, a0;

    a0 = t0 = MsGetOsTickExt();
    MsSleep(5000);
    a1 = t1 = MsGetOsTickExt();

    delta_t = t1 - t0;

    ven_std_sprintf((char*)KerTestOutput, "MsGetOsTickExt t0/t1 (%d/%d) ticks", a0, a1);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    ven_std_sprintf((char*)KerTestOutput, "MsGetOsTickExt t0/t1 (%d/%d) sec", RTK_TICK_TO_S(t0), RTK_TICK_TO_S(t1));

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT((delta_t - 5000) < 10);
}

// 230
static void _test_ms_sleep(void)
{
    u32 t0 = 0, t1 =0;
    u32 delta_t = 0;

    t0 = MsGetOsTick();
    MsSleep(1000);
    t1 = MsGetOsTick();

    delta_t = t1 - t0;

    ven_std_sprintf((char*)KerTestOutput, "time elapse = %d", delta_t);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT( (delta_t - 1000) < 10);
}

// 231
static void _test_flag_init(void)
{
    Ms_Flag_t test_flag;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);

    // check value
    VEN_TEST_CHECK_RESULT( (test_flag.FlagId >> 0)  && (test_flag.FlagState == RTK_FLAG_INITIALIZED) );

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 232
static void _test_flag_destroy(void)
{
    Ms_Flag_t test_flag;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // destroy the flag
    MsFlagDestroy(&test_flag);

    VEN_TEST_CHECK_RESULT(test_flag.FlagState == RTK_FLAG_DESTROY);
}

// 233
static void _test_flag_set_bits(void)
{
    Ms_Flag_t test_flag;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x0000ABBA);

    ven_std_sprintf((char*)KerTestOutput, "flag value = 0x%x", test_flag.FlagValue);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT(test_flag.FlagValue == 0x0000ABBA);

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 234
static void _test_flag_mask_bits(void)
{
    Ms_Flag_t test_flag;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x0000ABBA);
    // mask bits
    MsFlagMaskbits(&test_flag, ~0x00000BB0);

    ven_std_sprintf((char*)KerTestOutput, "flag value = 0x%x", test_flag.FlagValue);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT(test_flag.FlagValue == 0x0000A00A);

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 235
static void _test_flag_wait_1(void)
{
    Ms_Flag_t test_flag;
    rtk_flag_value_t value = 0;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x0000ABBA);
    // wait flag
    value = MsFlagWait(&test_flag, 0x00000BB0, RTK_FLAG_WAITMODE_AND);

    ven_std_sprintf((char*)KerTestOutput, "return value = 0x%x", value);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT( (test_flag.FlagValue == 0x0000A00A) && (value == 0x0000ABBA) );

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 236
static void _test_flag_wait_2(void)
{
    Ms_Flag_t test_flag;
    rtk_flag_value_t value = 0;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x0000ABBA);
    // wait flag
    value = MsFlagWait(&test_flag, 0x0000ABBA, RTK_FLAG_WAITMODE_AND | RTK_FLAG_WAITMODE_CLR);

    ven_std_sprintf((char*)KerTestOutput, "return value = 0x%x", value);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT( (test_flag.FlagValue == 0x00000000)  && (value == 0x0000ABBA) );

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 237
static void _test_flag_wait_3(void)
{
    Ms_Flag_t test_flag;
    rtk_flag_value_t value = 0;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x0000ABBA);
    // wait flag
    value = MsFlagWait(&test_flag, 0x00000FF0, RTK_FLAG_WAITMODE_OR);

    ven_std_sprintf((char*)KerTestOutput, "return value = 0x%x", value);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT( (test_flag.FlagValue == 0x0000A00A) &&  (value == 0x0000ABBA)  );

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 238
static void _test_flag_wait_4(void)
{
    Ms_Flag_t test_flag;
    rtk_flag_value_t value = 0;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x0000ABBA);
    // wait flag
    value = MsFlagWait(&test_flag, 0x00000BB0, RTK_FLAG_WAITMODE_OR | RTK_FLAG_WAITMODE_CLR);

    ven_std_sprintf((char*)KerTestOutput, "return value = 0x%x", value);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT( (test_flag.FlagValue == 0x00000000) &&  (value == 0x0000ABBA) );

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 239
static void _test_flag_timed_wait_1(void)
{
    Ms_Flag_t test_flag;
    rtk_flag_value_t value = 0;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x0000ABBA);
    // wait flag
    value = MsFlagTimedWait(&test_flag, 0x0000ABBA, RTK_FLAG_WAITMODE_AND | RTK_FLAG_WAITMODE_CLR, 0);

    ven_std_sprintf((char*)KerTestOutput, "return value = 0x%x", value);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT( (test_flag.FlagValue == 0x00000000) &&  (value == 0x0000ABBA));

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 240
static void _test_flag_timed_wait_2(void)
{
    Ms_Flag_t test_flag;
    u32 t0 = 0, t1 = 0;
    u32 delta_t = 0;
    rtk_flag_value_t value = 0;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0xABBA0000);
    // get os tick for t0
    t0 = MsGetOsTick();
    // wait flag
    value = MsFlagTimedWait(&test_flag, 0x0000ABBA, RTK_FLAG_WAITMODE_AND | RTK_FLAG_WAITMODE_CLR, 1000);
    // get os tick for t1
    t1 = MsGetOsTick();

    delta_t = t1 -t0;

    ven_std_sprintf((char*)KerTestOutput, "delta_t = %d, return value = 0x%x", delta_t, value);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT( ((delta_t -1000) < 10) && (test_flag.FlagValue == 0xABBA0000) && (value == 0x00000000));

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 241
static void _test_flag_poll_1(void)
{
    Ms_Flag_t test_flag;
    rtk_flag_value_t value = 0;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x00000000);
    // wait flag
    value = MsFlagPoll(&test_flag, 0x0000ABBA, RTK_FLAG_WAITMODE_AND | RTK_FLAG_WAITMODE_CLR);

    ven_std_sprintf((char*)KerTestOutput, "return value = 0x%x", value);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT( (test_flag.FlagValue == 0x00000000) &&  (value == 0x00000000));

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 242
static void _test_flag_poll_2(void)
{
    Ms_Flag_t test_flag;
    rtk_flag_value_t value = 0;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x0000ABBA);
    // wait flag
    value = MsFlagPoll(&test_flag, 0x0000ABBA, RTK_FLAG_WAITMODE_AND | RTK_FLAG_WAITMODE_CLR);

    ven_std_sprintf((char*)KerTestOutput, "return value = 0x%x", value);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT( (test_flag.FlagValue == 0x00000000) &&  (value == 0x0000ABBA));

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 243
static void _test_flag_peek(void)
{
    Ms_Flag_t test_flag;
    rtk_flag_value_t value = 0;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x0000ABBA);
    // wait flag
    value = MsFlagPeek(&test_flag);

    ven_std_sprintf((char*)KerTestOutput, "return value = 0x%x", value);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT( value == 0x0000ABBA );

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

// 244
static void _test_flag_waiting(void)
{
    //u8 output[_RESULT_STR_SIZE];
    Ms_Flag_t test_flag;
    bool isWaiting = FALSE;

    memset(&test_flag, 0, sizeof(Ms_Flag_t));
    // init the flag
    MsFlagInit(&test_flag);
    // set bits
    MsFlagSetbits(&test_flag, 0x0000ABBA);
    // wait flag
    isWaiting = MsFlagWaiting(&test_flag);

    VEN_TEST_CHECK_RESULT( isWaiting == FALSE );

    // destroy the flag
    MsFlagDestroy(&test_flag);
}

static void __test_msg_send_prio_0(void *userdata)
{
	MsSleep(10000);
}

static void setup_auto_test_mailbox(u32 ID)
{
	KerTestTaskArgs[ID].AppliInit = __test_msg_send_prio_0;
	KerTestTaskArgs[ID].AppliParser = emptyParser;
	KerTestTaskArgs[ID].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[ID].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[ID].StackSize);
	strcpy(KerTestTaskArgs[ID].TaskName, "task0");
	MsCreateTask(&KerTestTaskArgs[ID]);
	MsStartTask(KerTestTaskId[ID]);
}

static void destory_auto_test_mailbox(u32 ID)
{
	MsDeleteTask(KerTestTaskId[ID]);
	MsReleaseMemory(KerTestTaskArgs[ID].pStackTop);
}


// 245
static void _test_msg_send(void)
{
	bool isPass = FALSE;
	MsOsErr_e ret = RTK_OK;
	MsMailbox_e mboxId = 0;
	MsMsg_t Msg;
	MsMsg_t* pMsgRecv;
	MsObj_t MsgObjRecv;
	u32 mbxID = 0 ;

	setup_auto_test_mailbox(mbxID);
	mboxId = KerTestTaskId[mbxID] ;

	memset(&Msg, 0, sizeof(MsMsg_t) );
	Msg.Header.Length = sizeof(MsMsg_t);
	Msg.Header.MbxSrc = mboxId;
	Msg.Header.MbxDst = mboxId;
	Msg.Header.TypMsg = 0xABCD;

	// send message
	ret = MsSend(mboxId, &Msg);
	if(ret != RTK_OK)
	{
		destory_auto_test_mailbox(mbxID);
		VEN_TEST_CHECK_RESULT(FALSE);
		return;
	}
	// receive message
	isPass = MsReceiveNoWait(mboxId, &MsgObjRecv, NULL);

	pMsgRecv = (MsMsg_t*) MsgObjRecv.Msg;
	if( pMsgRecv )
	{
		ven_std_sprintf((char*)KerTestOutput, "ret = %d, mboxID = %d, msg = 0x%x", ret,mboxId, pMsgRecv->Header.TypMsg);
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		VEN_TEST_CHECK_RESULT( (isPass == TRUE) && ( pMsgRecv->Header.TypMsg == 0xABCD) );
	}
	else
	{

		VEN_TEST_CHECK_RESULT(FALSE);
	}

	destory_auto_test_mailbox(mbxID);

}



#if defined(__TARGET__)
// 247
static void _test_msg_send_ext(void) // TODO: need test?
{
#ifdef __RTK_SEND_SUSPENSION__
	u32 t0, t1, delta_t;
	MsOsErr_e ret = RTK_OK;
	MsMailbox_e mboxId = 0;
	MsMsg_t *Msg;
	MsMsg_t *Msg2;
	u32 mbxID = 0 ;

	setup_auto_test_mailbox(mbxID);
	mboxId = KerTestTaskId[mbxID] ;

	// disable scheduler
	MsEnterRegion();

	// set limit msg number
	rtk_Mailboxes[ mboxId ].limitMsgNum = 1;

	// enable scheduler
	MsLeaveRegion();

	Msg = (MsMsg_t*)MsAllocateMem(sizeof(MsMsg_t));
	memset(Msg, 0, sizeof(MsMsg_t) );
	Msg->Header.Length = sizeof(MsMsg_t);
	Msg->Header.MbxSrc = mboxId;
	Msg->Header.MbxDst = mboxId;
	Msg->Header.TypMsg = 0xABCD;

	Msg2 = (MsMsg_t*)MsAllocateMem(sizeof(MsMsg_t));
	memset(Msg2, 0, sizeof(MsMsg_t) );
	Msg2->Header.Length = sizeof(MsMsg_t);
	Msg2->Header.MbxSrc = mboxId;
	Msg2->Header.MbxDst = mboxId;
	Msg2->Header.TypMsg = 0xEFEF;


	// send 1st message
	ret = MsSend(mboxId, Msg);
	// send 2nd message
	t0 = MsGetOsTick();
	ret = MsSendExt(mboxId, Msg2, 1000);
	t1 = MsGetOsTick();

	delta_t = t1 - t0;
	ven_std_sprintf((char*)KerTestOutput, "ret = %d, mboxID = %d, delta_t = %d", ret, mboxId, delta_t);
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT( ((delta_t -1000) < 10) && (ret == RTK_MAILBOX_FULL) );

	// Msg is free in destory mailbox
	destory_auto_test_mailbox(mbxID);
#else
	VEN_TEST_CHECK_RESULT(FALSE);
#endif
}
#endif // __TARGET__

// 248
static void _test_msg_send_prio(void)
{
	bool isPass = FALSE;
	MsOsErr_e ret = RTK_OK;
	MsMailbox_e mboxId = 0;
	MsMsg_t Msg;
	MsMsg_t* pMsgRecv;
	MsObj_t MsgObjRecv;
	u32 mbxID = 0 ;

	setup_auto_test_mailbox(mbxID);
	mboxId = KerTestTaskId[mbxID] ;

	memset(&Msg, 0, sizeof(MsMsg_t) );
	Msg.Header.Length = sizeof(MsMsg_t);
	Msg.Header.MbxSrc = mboxId;
	Msg.Header.MbxDst = mboxId;
	Msg.Header.TypMsg = 0xABCD;

	// send message
	ret = MsSendWithPrio(mboxId, &Msg);
	if(ret != RTK_OK)
	{
		destory_auto_test_mailbox(mbxID);
		VEN_TEST_CHECK_RESULT(FALSE);
		return;
	}

	// receive message
	isPass = MsReceiveNoWait(mboxId, &MsgObjRecv, NULL);

	pMsgRecv = (MsMsg_t*) MsgObjRecv.Msg;
	if( pMsgRecv )
	{
		ven_std_sprintf((char*)KerTestOutput, "ret = %d, mboxID = %d, msg = 0x%x", ret, mboxId, pMsgRecv->Header.TypMsg);
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		VEN_TEST_CHECK_RESULT( (isPass == TRUE) && (pMsgRecv->Header.TypMsg == 0xABCD) );

	}
	else
	{
		VEN_TEST_CHECK_RESULT(FALSE);
	}


	destory_auto_test_mailbox(mbxID);
}




// 251
static void _test_msg_set_threshold(void)
{
#if defined(__RTK_SEND_SUSPENSION__) && defined(__TARGET__)
	MsOsErr_e ret = RTK_OK;
	MsMailbox_e mboxId = 0;
	MsMsg_t Msg;
	MsObj_t MsgObjRecv;
	u32 bkCurrTaskID;
	u32 mbxID = 0 ;

	setup_auto_test_mailbox(mbxID);
	mboxId = KerTestTaskId[mbxID] ;

	// disable scheduler & replace Rtk_CurrentTask
	MsEnterRegion();
	bkCurrTaskID = Rtk_CurrentTask;
	Rtk_CurrentTask = mboxId;

	// set threshold
	MsSetMbxThreshold(mboxId, 1);
	// set limit msg number
	rtk_Mailboxes[mboxId].limitMsgNum = 100;

	// restore Rtk_CurrentTask and enable scheduler
	Rtk_CurrentTask = bkCurrTaskID;
	MsLeaveRegion();

	memset(&Msg, 0, sizeof(MsMsg_t) );
	Msg.Header.Length = sizeof(MsMsg_t);
	Msg.Header.MbxSrc = mboxId;
	Msg.Header.MbxDst = mboxId;
	Msg.Header.TypMsg = 0xABCD;

	// send 1st message
	ret = MsSendWithThreshold(mboxId, &Msg);
	// send 2nd message
	ret = MsSendWithThreshold(mboxId, &Msg);


	ven_std_sprintf((char*)KerTestOutput, "mboxID = %d", mboxId);
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT( ret == MS_MAILBOX_OVER_THRESHOLD );

	// receive 1st message
	MsReceiveNoWait(mboxId, &MsgObjRecv, NULL);
	destory_auto_test_mailbox(mbxID);
#else
	VEN_TEST_CHECK_RESULT(FALSE);
#endif
}

// 252
static void _test_msg_send_with_threshold(void)
{
#if defined(__RTK_SEND_SUSPENSION__) && defined(__TARGET__)
	MsOsErr_e ret = RTK_OK;
	MsMailbox_e mboxId = 0;
	MsMsg_t Msg;
	MsObj_t MsgObjRecv;
	u32 bkCurrTaskID;
	u32 mbxID = 0 ;

	setup_auto_test_mailbox(mbxID);
	mboxId = KerTestTaskId[mbxID] ;

	// disable scheduler & replace Rtk_CurrentTask
	MsEnterRegion();
	bkCurrTaskID = Rtk_CurrentTask;
	Rtk_CurrentTask = mboxId;

	// set threshold
	MsSetMbxThreshold(mboxId, 1);
	// set limit msg number
	rtk_Mailboxes[mboxId].limitMsgNum = 100;

	// restore Rtk_CurrentTask and enable scheduler
	Rtk_CurrentTask = bkCurrTaskID;
	MsLeaveRegion();

	memset(&Msg, 0, sizeof(MsMsg_t) );
	Msg.Header.Length = sizeof(MsMsg_t);
	Msg.Header.MbxSrc = mboxId;
	Msg.Header.MbxDst = mboxId;
	Msg.Header.TypMsg = 0xABCD;

	// send 1st message
	ret = MsSendWithThreshold(mboxId, &Msg);
	// send 2nd message
	ret = MsSendWithThreshold(mboxId, &Msg);


	ven_std_sprintf((char*)KerTestOutput, "mboxID = %d", mboxId);
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT( ret == MS_MAILBOX_OVER_THRESHOLD );

	// receive 1st message
	MsReceiveNoWait(mboxId, &MsgObjRecv, NULL);
	destory_auto_test_mailbox(mbxID);
#else
	VEN_TEST_CHECK_RESULT(FALSE);
#endif
}

// 253
static void _test_msg_recv(void)
{
	bool isPass = FALSE;
	MsOsErr_e ret = RTK_OK;
	MsMailbox_e mboxId = 0;
	MsMsg_t Msg;
	MsMsg_t* pMsgRecv;
	MsObj_t MsgObjRecv;
	u32 mbxID = 0 ;

	setup_auto_test_mailbox(mbxID);
	mboxId = KerTestTaskId[mbxID] ;

	memset(&Msg, 0, sizeof(MsMsg_t) );
	Msg.Header.Length = sizeof(MsMsg_t);
	Msg.Header.MbxSrc = mboxId;
	Msg.Header.MbxDst = mboxId;
	Msg.Header.TypMsg = 0xABCD;

	// send message
	ret = MsSend(mboxId, &Msg);
	if(ret != RTK_OK)
	{
		destory_auto_test_mailbox(mbxID);
		VEN_TEST_CHECK_RESULT(FALSE);
		return;
	}
	// receive message
	isPass = MsReceive(mboxId, &MsgObjRecv, NULL);

	pMsgRecv = (MsMsg_t*) MsgObjRecv.Msg;
	ven_std_sprintf((char*)KerTestOutput, "mboxID = %d", mboxId);
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT( (isPass == TRUE) && (pMsgRecv->Header.TypMsg == 0xABCD) );

	destory_auto_test_mailbox(mbxID);
}



// 255
static void _test_msg_recv_no_wait_1(void)
{
	bool isPass = FALSE;
	MsOsErr_e ret = RTK_OK;
	MsMailbox_e mboxId = 0;
	MsMsg_t Msg;
	MsMsg_t* pMsgRecv;
	MsObj_t MsgObjRecv;
	u32 mbxID = 0 ;

	setup_auto_test_mailbox(mbxID);
	mboxId = KerTestTaskId[mbxID] ;

	memset(&Msg, 0, sizeof(MsMsg_t) );
	Msg.Header.Length = sizeof(MsMsg_t);
	Msg.Header.MbxSrc = mboxId;
	Msg.Header.MbxDst = mboxId;
	Msg.Header.TypMsg = 0xABCD;

	// send message
	ret = MsSend(mboxId, &Msg);
	if(ret != RTK_OK)
	{
		destory_auto_test_mailbox(mbxID);
		VEN_TEST_CHECK_RESULT(FALSE);
		return;
	}
	// receive message
	isPass = MsReceiveNoWait(mboxId, &MsgObjRecv, NULL);

	pMsgRecv = (MsMsg_t*) MsgObjRecv.Msg;
	ven_std_sprintf((char*)KerTestOutput, "ret = %d, mboxID = %d, msg = 0x%x", ret, mboxId, pMsgRecv->Header.TypMsg);
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT( (isPass == TRUE) && ( pMsgRecv->Header.TypMsg == 0xABCD) );

	destory_auto_test_mailbox(mbxID);
}

// 256
static void _test_msg_recv_no_wait_2(void)
{
    	bool isPass = FALSE;
    	MsMailbox_e mboxId = 0;
	MsObj_t MsgObjRecv;
	u32 mbxID = 0 ;

	setup_auto_test_mailbox(mbxID);
	mboxId = KerTestTaskId[mbxID] ;

	// receive message
	isPass = MsReceiveNoWait(mboxId, &MsgObjRecv, NULL);

	ven_std_sprintf((char*)KerTestOutput, "isPass = %d, mboxID = %d", isPass, mboxId);
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT( isPass == FALSE );

	destory_auto_test_mailbox(mbxID);
}

// 257
static void _test_msg_status(void)
{
	bool isPass = FALSE;
	MsOsErr_e ret = RTK_OK;
	MsMailbox_e mboxId = 0;
	MsMsg_t Msg;
	MsObj_t MsgObjRecv;
	u32 limit, max, current;
	u32 mbxID = 0 ;

	setup_auto_test_mailbox(mbxID);
	mboxId = KerTestTaskId[mbxID] ;


	memset(&Msg, 0, sizeof(MsMsg_t) );
	Msg.Header.Length = sizeof(MsMsg_t);
	Msg.Header.MbxSrc = mboxId;
	Msg.Header.MbxDst = mboxId;
	Msg.Header.TypMsg = 0xABCD;

	// send message
	ret = MsSend(mboxId, &Msg);
	if(ret != RTK_OK)
	{
		destory_auto_test_mailbox(mbxID);
		VEN_TEST_CHECK_RESULT(FALSE);
		return;
	}
	// get mbox status
	isPass = MsMboxStatus(mboxId, &limit, &max, &current);

	ven_std_sprintf((char*)KerTestOutput, "mboxID = %d, isPass = %d, current = %d", mboxId, isPass, current);
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT( (isPass == TRUE) && (current == 1) );

	// receive message
	isPass = MsReceiveNoWait(mboxId, &MsgObjRecv, NULL);

	destory_auto_test_mailbox(mbxID);
}

/* pre condiction: priority task1 > task2 */
static void _test_OS_sem_0(void)
{
	q = 0;
	MsInitSemExtend(CUS_KERNELTEST_SEM_0, 1, 1);
	MsInitSemExtend(CUS_KERNELTEST_SEM_1, 1, 0);
	MsInitSemExtend(CUS_KERNELTEST_SEM_2, 1, 0);

	KerTestTaskArgs[0].AppliInit = __test_os_sem_entry_0;
	KerTestTaskArgs[0].AppliParser = emptyParser;
	KerTestTaskArgs[0].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[0].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[0].StackSize);
	strcpy(KerTestTaskArgs[0].TaskName, "task0");
	KerTestTaskArgs[1].AppliInit = __test_os_sem_entry_1;
	KerTestTaskArgs[1].AppliParser = emptyParser;
	KerTestTaskArgs[1].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[1].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[1].StackSize);
	strcpy(KerTestTaskArgs[1].TaskName, "task1");

	KerTestTaskArgs[0].Priority = CUS62_PRIO + 1 ;

	MsCreateTask(&KerTestTaskArgs[0]);
	MsCreateTask(&KerTestTaskArgs[1]);

	MsStartTask(KerTestTaskId[0]);
	MsStartTask(KerTestTaskId[1]);

	MsSleep(50);

	MsDeleteTask(KerTestTaskId[0]);
	MsDeleteTask(KerTestTaskId[1]);

	MsReleaseMemory(KerTestTaskArgs[0].pStackTop);
	MsReleaseMemory(KerTestTaskArgs[1].pStackTop);

	KerTestTaskArgs[0].Priority = CUS63_PRIO ;

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

}

/* pre condiction: priority task1 > task2 */
static void _test_OS_sem_1(void)
{
	q = 0;
	MsInitSemExtend(CUS_KERNELTEST_SEM_0, 1, 1);
	MsInitSemExtend(CUS_KERNELTEST_SEM_1, 1, 0);
	MsInitSemExtend(CUS_KERNELTEST_SEM_2, 1, 0);

	KerTestTaskArgs[0].AppliInit = __test_os_sem_entry_2;
	KerTestTaskArgs[0].AppliParser = emptyParser;
	KerTestTaskArgs[0].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[0].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[0].StackSize);
	strcpy(KerTestTaskArgs[0].TaskName, "task0");
	KerTestTaskArgs[1].AppliInit = __test_os_sem_entry_3;
	KerTestTaskArgs[1].AppliParser = emptyParser;
	KerTestTaskArgs[1].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[1].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[1].StackSize);
	strcpy(KerTestTaskArgs[1].TaskName, "task1");

	KerTestTaskArgs[0].Priority = CUS62_PRIO + 1 ;

	MsCreateTask(&KerTestTaskArgs[0]);
	MsCreateTask(&KerTestTaskArgs[1]);

	MsStartTask(KerTestTaskId[0]);
	MsStartTask(KerTestTaskId[1]);

	MsSleep(50);

	MsDeleteTask(KerTestTaskId[0]);
	MsDeleteTask(KerTestTaskId[1]);

	MsReleaseMemory(KerTestTaskArgs[0].pStackTop);
	MsReleaseMemory(KerTestTaskArgs[1].pStackTop);

	KerTestTaskArgs[0].Priority = CUS63_PRIO ;

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}

/* pre condiction: equal priority */
static void _test_OS_flag_0(void)
{
	q = 0;
	MsFlagInit(&KerTestFlag[0]);
	MsFlagInit(&KerTestFlag[1]);
	MsFlagInit(&KerTestFlag[2]);

	KerTestTaskArgs[0].AppliInit = __test_os_flag_entry_0;
	KerTestTaskArgs[0].AppliParser = emptyParser;
	KerTestTaskArgs[0].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[0].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[0].StackSize);
	strcpy(KerTestTaskArgs[0].TaskName, "task0");
	KerTestTaskArgs[1].AppliInit = __test_os_flag_entry_1;
	KerTestTaskArgs[1].AppliParser = emptyParser;
	KerTestTaskArgs[1].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[1].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[1].StackSize);
	strcpy(KerTestTaskArgs[1].TaskName, "task1");
	KerTestTaskArgs[2].AppliInit = __test_os_flag_entry_2;
	KerTestTaskArgs[2].AppliParser = emptyParser;
	KerTestTaskArgs[2].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[2].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[2].StackSize);
	strcpy(KerTestTaskArgs[2].TaskName, "task2");

	KerTestTaskArgs[0].Priority = KerTestTaskArgs[1].Priority = KerTestTaskArgs[2].Priority = CUS62_PRIO ;

	MsCreateTask(&KerTestTaskArgs[0]);
	MsCreateTask(&KerTestTaskArgs[1]);
	MsCreateTask(&KerTestTaskArgs[2]);

	MsStartTask(KerTestTaskId[0]);
	MsStartTask(KerTestTaskId[1]);
	MsStartTask(KerTestTaskId[2]);

	MsSleep(50);

	MsDeleteTask(KerTestTaskId[0]);
	MsDeleteTask(KerTestTaskId[1]);
	MsDeleteTask(KerTestTaskId[2]);

	MsFlagDestroy(&KerTestFlag[0]);
	MsFlagDestroy(&KerTestFlag[1]);
	MsFlagDestroy(&KerTestFlag[2]);

	MsReleaseMemory(KerTestTaskArgs[0].pStackTop);
	MsReleaseMemory(KerTestTaskArgs[1].pStackTop);
	MsReleaseMemory(KerTestTaskArgs[2].pStackTop);


	KerTestTaskArgs[0].Priority= CUS63_PRIO ;
	KerTestTaskArgs[1].Priority = CUS62_PRIO ;
	KerTestTaskArgs[2].Priority = CUS61_PRIO ;

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}

static void _test_OS_int_0(void)
{
	q = 0;

	KerTestTaskArgs[0].AppliInit = __test_os_int_entry_0;
	KerTestTaskArgs[0].AppliParser = emptyParser;
	KerTestTaskArgs[0].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[0].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[0].StackSize);
	strcpy(KerTestTaskArgs[0].TaskName, "task0");
	KerTestTaskArgs[1].AppliInit = __test_os_int_entry_1;
	KerTestTaskArgs[1].AppliParser = emptyParser;
	KerTestTaskArgs[1].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[1].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[1].StackSize);
	strcpy(KerTestTaskArgs[1].TaskName, "task1");
	KerTestTaskArgs[2].AppliInit = __test_os_int_entry_2;
	KerTestTaskArgs[2].AppliParser = emptyParser;
	KerTestTaskArgs[2].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[2].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[2].StackSize);
	strcpy(KerTestTaskArgs[2].TaskName, "task2");
	KerTestTaskArgs[3].AppliInit = __test_os_int_entry_3;
	KerTestTaskArgs[3].AppliParser = emptyParser;
	KerTestTaskArgs[3].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[3].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[3].StackSize);
	strcpy(KerTestTaskArgs[3].TaskName, "task3");

	MsCreateTask(&KerTestTaskArgs[0]);
	MsCreateTask(&KerTestTaskArgs[1]);
	MsCreateTask(&KerTestTaskArgs[2]);
	MsCreateTask(&KerTestTaskArgs[3]);

	MsStartTask(KerTestTaskId[0]);
	MsStartTask(KerTestTaskId[1]);
	MsStartTask(KerTestTaskId[2]);
	MsStartTask(KerTestTaskId[3]);

	MsSleep(15000);

	MsDeleteTask(KerTestTaskId[0]);
	MsDeleteTask(KerTestTaskId[1]);
	MsDeleteTask(KerTestTaskId[2]);
	MsDeleteTask(KerTestTaskId[3]);

	MsReleaseMemory(KerTestTaskArgs[0].pStackTop);
	MsReleaseMemory(KerTestTaskArgs[1].pStackTop);
	MsReleaseMemory(KerTestTaskArgs[2].pStackTop);
	MsReleaseMemory(KerTestTaskArgs[3].pStackTop);

	if (40000 != q)
		ven_std_sprintf((char*)KerTestOutput, "_test_os_int_0: Fail, %d", q);
	else
		ven_std_sprintf((char*)KerTestOutput, "_test_os_int_0: Pass");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}

static void _test_OS_mbox_0(void)
{
	Msg_t *msg = NULL;
	u32 i, preTick = 0, curTick = 0;

	q = 0;

	KerTestTaskArgs[0].AppliInit = emptyInit;
	KerTestTaskArgs[0].AppliParser = __test_os_mbox_parser_0;
	KerTestTaskArgs[0].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[0].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[0].StackSize);
	strcpy(KerTestTaskArgs[0].TaskName, "task0");

	MsCreateTask(&KerTestTaskArgs[0]);
	MsStartTask(KerTestTaskId[0]);

	for (i=0;i<10;i++)
	{
		msg = (Msg_t*)MsAllocateMem(sizeof(Header_t));
		msg->Header.TypMsg = KERNEL_TEST_MSG0;
		msg->Header.MbxSrc = CUS14_MBX;
		msg->Header.MbxDst = KerTestTaskId[0];
		msg->Header.Length = 0;

		MsSend(KerTestTaskId[0], (void*)msg);
	}

	msg = (Msg_t*)MsAllocateMem(sizeof(Header_t));
	msg->Header.TypMsg = KERNEL_TEST_MSG1;
	msg->Header.MbxSrc = CUS14_MBX;
	msg->Header.MbxDst = KerTestTaskId[0];
	msg->Header.Length = 0;

	MsSend(KerTestTaskId[0], (void*)msg);

	preTick = MsGetOsTick();
	MsSleep(50);
	curTick = MsGetOsTick();
	if (curTick > (preTick+51) || curTick < (preTick+49))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_os_mbox_0: Get OS tick Fail, 0x%8x 0x%8x", preTick, curTick);
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	}

	if (20 != q)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_os_mbox_0: step 1 Fail, %d", q);
	}

	MsStopTimer(KERNEL_TEST_MSG2);

	MsSleep(500);

	if (20 != q)
		ven_std_sprintf((char*)KerTestOutput, "_test_os_mbox_0: step 2 Fail, %d", q);
	else
		ven_std_sprintf((char*)KerTestOutput, "_test_os_mbox_0: Pass");

	MsDeleteTask(KerTestTaskId[0]);

	MsReleaseMemory(KerTestTaskArgs[0].pStackTop);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}


#if defined (__MMAP__)

static void _test_OS_mmap_0(void)
{
	u32 tmp = 0, nSrc = 0, nDst = 0;
	VFS_FILE *testfd = 0, *testfd2 = 0;
	VFS_File_Info_t finfo;
	u32 flen = 0, len = 0;
	static u8 ttt[2048];

	testfd = file_fopen((u16 *)L"/CARD/sysbt/tmp0.txt", (ascii *)"r");
	if (NULL == testfd)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_0: open /CARD/sysbt/tmp0.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	if(FAT_NO_ERROR != file_finfo(testfd, &finfo))
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_0: get /CARD/sysbt/tmp0.txt fileinfo failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	flen = finfo.Size;

	testfd2 = file_fopen((u16 *)L"/CARD/sysbt/tmpout0.txt", (ascii *)"w");
	if (NULL == testfd2)
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_0: open /CARD/sysbt/tmpout0.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	tmp = (u32)Msmmap(NULL, flen, PROT_READ, MAP_PRIVATE, (int)testfd, 0);
	if (NULL == tmp)
	{
		file_fclose(testfd);
		file_fclose(testfd2);
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_0: mmap %d len=%d failed", testfd, flen);
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	nSrc = tmp;
	nDst = nSrc + flen;
	do
	{
		len = ((nDst-tmp)>=sizeof(ttt)) ? sizeof(ttt) : (nDst-tmp);
		memcpy((void*)&ttt[0], (void*)tmp, len);
		file_fwrite(testfd2, (u8*)&ttt[0], len);
		tmp += sizeof(ttt);
	} while(tmp < nDst);

	file_fclose(testfd2);
	file_fclose(testfd);

	Msmunmap((void*)nSrc, flen);

	ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_0: Pass");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}


static void _test_OS_mmap_1(void)
{
	u32 tmp = 0, nSrc = 0, nDst = 0;
	int idd;
	VFS_FILE *testfd = 0, *testfd2 = 0;
	VFS_File_Info_t finfo;
	u32 flen = 0, len = 0;
	static u8 ttt[2048];
	u8 fname[64];
	u16 flname[32];

	testfd = file_fopen((u16 *)L"/CARD/sysbt/tmp0.txt", (ascii*)"r");
	if (NULL == testfd)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_1: open /CARD/sysbt/tmp0.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	if(FAT_NO_ERROR != file_finfo(testfd, &finfo))
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_1: get /CARD/sysbt/tmp0.txt fileinfo failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	flen = finfo.Size;

	for (idd=0;idd<3;idd++)
	{
		ven_std_sprintf((char*)fname, "/CARD/sysbt/tmpout%d.txt", idd);
		u8bitStrTouStr(flname, fname);
		testfd2 = file_fopen(flname, "w");
		if (NULL == testfd2)
		{
			file_fclose(testfd);
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_1: open %s failed", fname);
			VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
			return;
		}

		tmp = (u32)Msmmap(NULL, flen, PROT_READ, MAP_PRIVATE, (int)testfd, 0);
		if (NULL == tmp)
		{
			file_fclose(testfd);
			file_fclose(testfd2);
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_1: mmap %d len=%d failed", testfd, flen);
			VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
			return;
		}

		file_fseek(testfd, 0, SEEK_SET);

		nSrc = tmp;
		nDst = nSrc + flen;
		do
		{
			len = ((nDst-tmp)>=sizeof(ttt)) ? sizeof(ttt) : (nDst-tmp);
			memcpy((void*)&ttt[0], (void*)tmp, len);
			file_fwrite(testfd2, (u8*)&ttt[0], len);
			tmp += sizeof(ttt);
		} while(tmp < nDst);

		Msmunmap((void*)nSrc, flen);

		file_fclose(testfd2);
	}

	file_fclose(testfd);

	ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_1: Pass");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}


static void _test_OS_mmap_2(void)
{
	u32 tmp[3], nSrc = 0, nDst = 0;
	int idd;
	VFS_FILE *testfd[3], *testfd2[3];
	VFS_File_Info_t finfo;
	u32 flen[3], len = 0;
	static u8 ttt[2048];
	u8 fname[64];
	u16 flname[32];

	for (idd=0;idd<3;idd++)
	{
		ven_std_sprintf((char*)fname, "/CARD/sysbt/tmp%d.txt", idd);
		u8bitStrTouStr(flname, fname);
		testfd[idd] = file_fopen(flname, "r");
		if (NULL == testfd[idd])
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_2: open %s failed", fname);
			VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
			return;
		}

		ven_std_sprintf((char*)fname, "/CARD/sysbt/tmpout%d.txt", idd);
		u8bitStrTouStr(flname, fname);
		testfd2[idd] = file_fopen(flname, "w");
		if (NULL == testfd2[idd])
		{
			file_fclose(testfd[0]);
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_2: open %s failed", fname);
			VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
			return;
		}

		if(FAT_NO_ERROR != file_finfo(testfd[idd], &finfo))
		{
			file_fclose(testfd[idd]);
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_2: get %s fileinfo failed", fname);
			VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
			return;
		}

		flen[idd] = finfo.Size;

		tmp[idd] = (u32)Msmmap(NULL, flen[idd], PROT_READ, MAP_PRIVATE, (int)(testfd[idd]), 0);
		if (NULL == tmp)
		{
			file_fclose(testfd[idd]);
			file_fclose(testfd2[0]);
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_2: mmap %d len=%d failed", testfd[idd], flen);
			VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
			return;
		}
	}

	for (idd=0;idd<3;idd++)
	{
		nSrc = tmp[idd];
		nDst = nSrc + flen[idd];
		do
		{
			len = ((nDst-tmp[idd])>=sizeof(ttt)) ? sizeof(ttt) : (nDst-tmp[idd]);
			memcpy((void*)&ttt[0], (void*)tmp[idd], len);
			file_fwrite(testfd2[idd], (u8*)&ttt[0], len);
			tmp[idd] += sizeof(ttt);
		} while(tmp[idd] < nDst);

		Msmunmap((void*)nSrc, flen[idd]);

		file_fclose(testfd2[idd]);
		file_fclose(testfd[idd]);
	}

	ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_2: Pass");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}


static void _test_OS_mmap_3(void)
{
	q = 0;

	KerTestTaskArgs[0].AppliInit = __test_os_mmap_entry_0;
	KerTestTaskArgs[0].AppliParser = emptyParser;
	KerTestTaskArgs[1].AppliInit = __test_os_mmap_entry_1;
	KerTestTaskArgs[1].AppliParser = emptyParser;
	KerTestTaskArgs[2].AppliInit = __test_os_mmap_entry_2;
	KerTestTaskArgs[2].AppliParser = emptyParser;

	MsCreateTask(&KerTestTaskArgs[0]);
	MsCreateTask(&KerTestTaskArgs[1]);
	MsCreateTask(&KerTestTaskArgs[2]);

	MsStartTask(KerTestTaskId[0]);
	MsStartTask(KerTestTaskId[1]);
	MsStartTask(KerTestTaskId[2]);

	while(3 != q)
		MsSleep(VM_RTK_MS_TO_TICK(5000));

	MsDeleteTask(KerTestTaskId[0]);
	MsDeleteTask(KerTestTaskId[1]);
	MsDeleteTask(KerTestTaskId[2]);

	ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_3: Pass");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}

static void _test_OS_mmap_4(void)
{
	u32 tmp = 0, nSrc = 0, nDst = 0;
	VFS_FILE *testfd = 0, *testfd2 = 0;
	VFS_File_Info_t finfo;
	u32 flen = 0, len = 0;
	static u8 ttt[2048];

	testfd = file_fopen((u16 *)L"/CARD/sysbt/tmp0.txt", "(ascii*)r+");
	if (NULL == testfd)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_4: open /CARD/sysbt/tmp0.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	if(FAT_NO_ERROR != file_finfo(testfd, &finfo))
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_4: get /CARD/sysbt/tmp0.txt fileinfo failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	flen = finfo.Size;

	testfd2 = file_fopen((u16 *)L"/CARD/sysbt/tmpout0.txt", (ascii*)"w");
	if (NULL == testfd2)
	{
		file_fclose(testfd);
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_4: open /CARD/sysbt/tmpout0.txt failed");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	tmp = (u32)Msmmap(NULL, flen, PROT_READ|PROT_WRITE, MAP_PRIVATE, (int)testfd, 0);
	if (NULL == tmp)
	{
		file_fclose(testfd);
		file_fclose(testfd2);
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_4: mmap %d len=%d failed", testfd, flen);
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		return;
	}

	nSrc = tmp;
	nDst = nSrc + flen;
	*(u8*)nSrc = 0xFF;
	do
	{
		len = ((nDst-tmp)>=sizeof(ttt)) ? sizeof(ttt) : (nDst-tmp);
		memcpy((void*)&ttt[0], (void*)tmp, len);
		file_fwrite(testfd2, (u8*)&ttt[0], len);
		tmp += sizeof(ttt);
		*((u8*)tmp-1) = 0xFF;
	} while(tmp < nDst);

	*((u8*)nSrc+4) = 0xFF;

	Msmunmap((void*)nSrc, flen);

	file_fclose(testfd2);
	file_fclose(testfd);

	ven_std_sprintf((char*)KerTestOutput, "_test_OS_mmap_4: Pass");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}

#endif


#if defined (__DPM__)
#include "sys_sys_dpm_mgr.h"

static void _test_demand_paging_0(void)
{
#if defined(__TARGET__)
#if defined (__RTK_OVER_R2__)
#define TEST_DP_DLM_1 0
#define TEST_DP_DLM_2 0

    DrvUartDebugTrace("_test_demand_paging_0\n");
#else
#define DPM_PTE_TEST 0
#define DPM_MODE_CHECK 0
#define DPM_PERM_TEST 0
#define DPM_DATA_TEST 0
#define DPM_TEXT_TEST 0

#if DPM_PTE_TEST
u8* buf;
#endif

#if DPM_MODE_CHECK
u32 cp15c1;
#endif

#if DPM_PERM_TEST
u8* buf;
#endif

#if DPM_DATA_TEST
extern u8 testDpDataDpmInit(void);
u32 vaddr;
s32 dpmfd;
u8  tmp_buf[MMU_PAGE_SIZE];
#endif

#if DPM_TEXT_TEST
extern u8 testDpTextDpmInit(void);
extern int testram1_func(int x);
extern int testram2_func(int x);
extern int testram3_func(int x);
extern int testram4_func(int x);
extern int testram5_func(int x);
extern int testram6_func(int x);
extern int testram7_func(int x);
extern int testram8_func(int x);
extern int testram9_func(int x);
extern int testram10_func(int x);
int ret;
#endif

    sys_UartPrintf("_test_demand_paging_0\n");
    ven_std_sprintf((char*)KerTestOutput, "_test_demand_paging_0");
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
#endif

#if defined (__DPM__)

#if DPM_PTE_TEST
    sys_dpm_insert_page_table_entry(0xD0000000, 0x00001000, MMU_ACCESSPROTECTION_RW_RO);
    buf = (u8*)0xD0000000;
    sys_UartPrintf("buf 0xD0000000 = 0x%x, 0x%x \n", *buf, *(buf + 1));
    buf = (u8*)0x00001000;
    sys_UartPrintf("buf 0x00001000 = 0x%x, 0x%x \n", *buf, *(buf + 1));
#endif

#if DPM_MODE_CHECK
    sys_UartPrintf("cpsr = 0x%x \n", read_cpsr());
    cp15c1 = cp15_read_reg1_control();
    sys_UartPrintf("cp15c1 = 0x%x \n", cp15c1);
#endif

#if DPM_PERM_TEST
    buf = (u8*)0xD0001000;
    *buf = 0xA;
    sys_UartPrintf("buf 0xD0001000 = 0x%x \n", *buf);
#endif

#if DPM_DATA_TEST
    testDpDataDpmInit();
    for (vaddr = TEST_DP_DATA_START_ADDR; vaddr < TEST_DP_DATA_END_ADDR; vaddr += MMU_PAGE_SIZE)
    {
        memcpy((void*)tmp_buf, (void *)vaddr, MMU_PAGE_SIZE);
        dpmfd = fat_N_open(L"/NAND/dp_data_out.bin", O_RDWR);
        if (dpmfd < 0)
        {
    		ven_std_sprintf((char*)KerTestOutput, "open /NAND/dp_data_out.bin failed");
	    	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		    _ASSERT(0);
        }

        fat_N_seek(dpmfd, vaddr - TEST_DP_DATA_START_ADDR, SEEK_SET);
        fat_N_write(dpmfd, (u8*)tmp_buf, MMU_PAGE_SIZE);
        fat_N_close(dpmfd);
    }
#endif

#if DPM_TEXT_TEST
    sys_UartPrintf("Load$$DP_SECT$$Base = 0x%x\n", (u32)&Load$$DP_SECT$$Base);
    sys_UartPrintf("Image$$DP_SECT$$Base = 0x%x\n", (u32)&Image$$DP_SECT$$Base);
    sys_UartPrintf("Image$$DP_SECT$$Length = 0x%x\n", (u32)&Image$$DP_SECT$$Length);
    sys_UartPrintf("Image$$DP_SECT$$Limit = 0x%x\n", (u32)&Image$$DP_SECT$$Limit);

    testDpTextDpmInit();

    ret = testram1_func(3);
    sys_UartPrintf("testram1_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram1_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram2_func(3);
    sys_UartPrintf("testram2_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram2_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram3_func(3);
    sys_UartPrintf("testram3_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram3_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram4_func(3);
    sys_UartPrintf("testram4_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram4_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram5_func(3);
    sys_UartPrintf("testram5_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram5_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram6_func(3);
    sys_UartPrintf("testram6_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram6_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram7_func(3);
    sys_UartPrintf("testram7_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram7_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram8_func(3);
    sys_UartPrintf("testram8_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram8_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram9_func(3);
    sys_UartPrintf("testram9_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram9_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram10_func(3);
    sys_UartPrintf("testram10_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram10_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

#endif

#endif //__DPM__

#if TEST_DP_DLM_1

    testDpDlmInit();

    u32 idx;
    u32 vaddr = 0xd9300000;
    u32 pteIdx;
    u8 *phyPage;
    u32 phyPageIdx;
    u32 victimOfIdxTable;

    pDlmPageTableEntry_t pDlmPageTableEntry, pPreDlmPageTableEntry;
    for (idx = 0; idx < 128; idx++)
    {
        pDlmPageTableEntry = DlmTextPageEntryFind(&testDpDlmCtrlBlk, vaddr, &pteIdx);
        DrvUartDebugTrace("vaddr = 0x%x, pDlmPageTableEntry = 0x%x, pteIdx = %d\n", vaddr, (u32)pDlmPageTableEntry, pteIdx);

        phyPage = DlmTextGetPage(&testDpDlmCtrlBlk, &phyPageIdx, pteIdx, &pPreDlmPageTableEntry, &victimOfIdxTable);
        DrvUartDebugTrace("phyPage = 0x%x, phyPageIdx = %d\n", (u32)phyPage, phyPageIdx);
        DrvUartDebugTrace("pPreDlmPageTableEntry = 0x%x, victimOfIdxTable = %d\n", (u32)pPreDlmPageTableEntry, victimOfIdxTable);

        vaddr+=0x2000;
    }

#endif // TEST_DP_DLM_1

#if TEST_DP_DLM_2

    testDpDlmInit();

    int ret, ret1, ret2, ret3, ret4;
    ret1 = testram1_func(3);
    DrvUartDebugTrace("testram1_func = %d\n", ret1);
    ven_std_sprintf((char*)KerTestOutput, "testram1_func = %d", ret1);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret2 = testram2_func(3);
    DrvUartDebugTrace("testram2_func = %d\n", ret2);
    ven_std_sprintf((char*)KerTestOutput, "testram2_func = %d", ret2);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret3 = testram3_func(3);
    DrvUartDebugTrace("testram3_func = %d\n", ret3);
    ven_std_sprintf((char*)KerTestOutput, "testram3_func = %d", ret3);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret4 = testram4_func(3);
    DrvUartDebugTrace("testram4_func = %d\n", ret4);
    ven_std_sprintf((char*)KerTestOutput, "testram4_func = %d", ret4);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram5_func(3);
    DrvUartDebugTrace("testram5_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram5_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram6_func(3);
    DrvUartDebugTrace("testram6_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram6_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram7_func(3);
    DrvUartDebugTrace("testram7_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram7_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram8_func(3);
    DrvUartDebugTrace("testram8_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram8_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    ret = testram9_func(3);
    DrvUartDebugTrace("testram9_func = %d\n", ret);
    ven_std_sprintf((char*)KerTestOutput, "testram9_func = %d", ret);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

    testDpDlmDeInit();

#endif // TEST_DP_DLM_2
#else
    VEN_TEST_CHECK_RESULT(FALSE);
#endif
}
#endif

static void _test_aligned_memory_0(void)
{
	void *alignedBuf;
	u32 nSize, idx=0, succ=0, fail=0, failAligned=0, freefail=0;
	u8 nRan;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	for (idx=0;idx<100000;idx++)
	{
		nSize = sys_Random32()%(1<<18); // Maximum alloc size 256KB
		nRan =  sys_Random8()%16; // Maximum aligned at 32KB

		if (0 == nSize)
			nSize = 1;

		alignedBuf = MsHMEMGetHeapMemoryExt(ms_memoryhandle, nSize, nRan, 0);

		if (NULL == alignedBuf)
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_aligned_memory_0: ptr=0x%08X, nSize=%d, nAligned=%d alloc failed", (unsigned int)alignedBuf, nSize, 1<<nRan);
			VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
			fail++;
		}
		else if ((u32)alignedBuf&((1<<nRan)-1))
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_aligned_memory_0: ptr=0x%08X, nSize=%d, nAligned=%d align failed", (unsigned int)alignedBuf, nSize, 1<<nRan);
			VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
			failAligned++;
		}
		else
		{
			MsHMEMCheckHeapMemory(alignedBuf);
			succ++;
		}

		if (RTK_OK != MsHMEMFree(alignedBuf, 0))
			freefail++;

		alignedBuf = NULL;
	}

	ven_std_sprintf((char*)KerTestOutput, "_test_aligned_memory_0: Pass, succ=%u, fail=%u, failAligned=%u, freefail=%u", succ, fail, failAligned, freefail);
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}

#ifdef __FIXME__
static void _test_aligned_memory_1(void)
{
	u32 *buf = NULL;
	u32 ret = 1, nSize = 0, nIdx = 0, idx = 0, alloc = 0, allocfail = 0, ratio = 0;
	u8 nRan = 0;
	ghStatus_t AStatus;
	VFS_FILE *vfile = NULL;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	buf = (u32*)MsAllocateMem(300*sizeof(void*));
	if (!buf)
	{
		ret = 0;
		goto TO_RESULT;
	}

	memset(buf, 0, 300*sizeof(void*));

	vfile = file_fopen((u16*)L"/CARD/sysbt/memprofile.txt", (ascii*)"w+");
	if (!vfile)
	{
		ret = 0;
		goto TO_RESULT;
	}
	ven_std_sprintf((char*)KerTestOutput, "mallocSize align alloc allocfail maxFree ratio\n");
	file_fwrite(vfile, KerTestOutput, ven_std_strlen((char *)KerTestOutput));

	MsHMEMQueryHeapStatus(ms_memoryhandle, &AStatus);
	ratio = (AStatus.MaxFreeSize*100)/AStatus.TotalFreeSize;
	ven_std_sprintf((char*)KerTestOutput, "%u %u %u %u %u %u\n", nSize, 1<<nRan, alloc, allocfail, AStatus.MaxFreeSize, ratio);
	file_fwrite(vfile, KerTestOutput, ven_std_strlen((char *)KerTestOutput));

	for (idx=0;idx<300000;idx++)
	{
		nIdx = sys_Random32()%300;

		if (buf[nIdx])
		{
			MsReleaseMemory(buf[nIdx]);
			continue;
		}
		else
		{
			nSize = sys_Random32()%(1<<18); // Maximum alloc size 256KB
			nRan =  0;

			if (0 == nSize)
				nSize = 1;

			alloc++;

			if (idx%10)
			{
				// to fix parasoft warning
				*(buf+nIdx) = (u32)MsGetHeapMemory(nSize);
			}
			else
			{
				nRan =  sys_Random8()%16; // Maximum aligned at 32KB
				// to fix parasoft warning
				*(buf+nIdx) = (u32)MsGetHeapMemoryExt(nSize, nRan, 0);
			}
		}

		if (0 == buf[nIdx] || 0 == (idx%1000))
		{
			if (0 == buf[nIdx])
				allocfail++;

			MsHMEMQueryHeapStatus(ms_memoryhandle, &AStatus);
			ratio = (AStatus.MaxFreeSize*100)/AStatus.TotalFreeSize;
			ven_std_sprintf((char*)KerTestOutput, "%u %u %u %u %u %u\n", nSize, 1<<nRan, alloc, allocfail, AStatus.MaxFreeSize, ratio);
			file_fwrite(vfile, KerTestOutput, ven_std_strlen((char *)KerTestOutput));
		}
	}

TO_RESULT:
	for (idx=0;idx<300;idx++)
	{
		if (buf[idx])
			MsReleaseMemory(buf[idx]);
	}

	if (buf)
		MsReleaseMemory(buf);

	if (vfile)
		file_fclose(vfile);

	VEN_TEST_CHECK_RESULT(ret);
}
#endif

#ifdef OS_TEST_EXT // additional schedule test
static void __test_OS_schedule_init_0(void *userdata)
{
	ven_std_sprintf((char*)KerTestOutput, "Task 0 init...\n");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

	while(1)
	{
		ven_std_sprintf((char*)KerTestOutput, "Task 0 running\n");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		MsSleep(150);
	}
}

static void __test_OS_schedule_init_1(void *userdata)
{
	ven_std_sprintf((char*)KerTestOutput, "Task 1 init...\n");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

	KerTestTaskArgs[2].AppliInit = __test_OS_schedule_init_2;
	KerTestTaskArgs[2].AppliParser = emptyParser;
	KerTestTaskArgs[2].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[2].pStackTop = MsAllocateMem(KerTestTaskArgs[2].StackSize);
	strcpy(KerTestTaskArgs[2].TaskName, "task2");

	MsCreateTask(&KerTestTaskArgs[2]);
	MsStartTask(KerTestTaskId[2]);
	while(1)
	{
		ven_std_sprintf((char*)KerTestOutput, "Task 1 running\n");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		MsSleep(100);
	}
}

static void __test_OS_schedule_init_2(void *userdata)
{
	ven_std_sprintf((char*)KerTestOutput, "Task 2 init...\n");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

	while(1)
	{
		ven_std_sprintf((char*)KerTestOutput, "Task 2 running\n");
		VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
		MsSleep(50);
	}
}

static void _test_OS_schedule_0(void)
{
	q = 0;
	MsInitSemExtend(CUS_KERNELTEST_SEM_0, 1, 1);
	MsInitSemExtend(CUS_KERNELTEST_SEM_1, 1, 0);
	MsInitSemExtend(CUS_KERNELTEST_SEM_2, 1, 0);

	KerTestTaskArgs[0].AppliInit = __test_OS_schedule_init_0;
	KerTestTaskArgs[0].AppliParser = emptyParser;
	KerTestTaskArgs[0].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[0].pStackTop = MsAllocateMem(KerTestTaskArgs[0].StackSize);
	strcpy(KerTestTaskArgs[0].TaskName, "task0");
	KerTestTaskArgs[1].AppliInit = __test_OS_schedule_init_1;
	KerTestTaskArgs[1].AppliParser = emptyParser;
	KerTestTaskArgs[1].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[1].pStackTop = MsAllocateMem(KerTestTaskArgs[1].StackSize);
	strcpy(KerTestTaskArgs[1].TaskName, "task1");

	MsCreateTask(&KerTestTaskArgs[0]);
	MsCreateTask(&KerTestTaskArgs[1]);

	MsStartTask(KerTestTaskId[0]);
	MsStartTask(KerTestTaskId[1]);

	// never go back
	MsConsumeSem(CUS_KERNELTEST_SEM_2);
	//MsSleep(50);

	//MsDeleteTask(KerTestTaskId[0]);
	//MsDeleteTask(KerTestTaskId[1]);

	MsReleaseMemory(KerTestTaskArgs[0].pStackTop);
	MsReleaseMemory(KerTestTaskArgs[1].pStackTop);
	MsReleaseMemory(KerTestTaskArgs[2].pStackTop);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}

#include "vm_rtc.h"
static u32 cb_counter = 0;
static u32 start_tick = 0;
static u32 tick_total_low = 0;
static u32 tick_total_high = 0;

static void my_cb(MsTimerId_e eTimerID, u32 UserData){
	u32 countX =0;
	u32 tick_pre = 0;
	vm_rtcTimeFormat_t time;

	// sumary total tick
	tick_pre = start_tick;
	start_tick = MsGetOsTick();
	if(start_tick >= tick_pre)
	{
		if((35612 - tick_total_low) < (start_tick - tick_pre))
		{
			tick_total_high++;
			tick_total_low = (start_tick - tick_pre) - (35612 - tick_total_low);
		}
		else
		{
			tick_total_low += (start_tick - tick_pre);
		}
	}
	else
	{
		if((35612 - tick_total_low) < (35612 - tick_pre + start_tick))
		{
			tick_total_high++;
			tick_total_low = (35612 - tick_pre + start_tick) - (35612 - tick_total_low);
		}
		else
		{
			tick_total_low += (35612 - tick_pre + start_tick);
		}
	}

	DrvRtcGetTime(&time);
	UartSendTrace("(%d) time = %d:%d:%d.%d\n", cb_counter, time.Hour ,time.Minute,  time.Second, time.SecondFracPart);
	UartSendTrace("        ostick = (0x%x, 0x%x)\n", tick_total_high, tick_total_low);
	cb_counter++;
};
static void _test_OS_timer_measure_(void)
{
    u32       tid = 1936 ;
    s32       cb_success=TRUE;
	u32 tmp_UserData = 1936;

	t_count = 0 ;
    MsStartCbTimer((MsTimerId_e*)&tid, my_cb, tmp_UserData, 1000*10, 1000*10); // 46.38 sec
	MsSleep(460);
}
#endif

#define HMEM_TEST_BUFF_SIZE (1 << 20)		// 1MB
#define HMEM_TEST_BUFF1_SIZE (400*1024)	// 400KB
#define HMEM_TEST_BUFF2_SIZE (300*1024)	// 300KB
#define HMEM_TEST_POOL_SIZE (100 * 1024) 	// 100KB

static const gpDesc_t PoolDesc[] =
{
  	{293, 70}, // 20 KB
	{150, 137}, // 20 KB
	{74, 277}, // 20 KB
	{39, 533}, // 20 KB
	{20, 1029} // 20 KB
};

static const u32 PoolDescNum = sizeof(PoolDesc) / sizeof(gpDesc_t);

static void _test_OS_hmem_0(void)
{
	void *HmemUTBuf = NULL;
	u32 handle = 0;
	void *pMem = NULL;
	u8 ret = 1, idx;
	ghStatus_t AStatus;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, HMEM_TEST_BUFF_SIZE, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_0: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (0 == (handle=MsHMEMCreate(HmemUTBuf, HMEM_TEST_BUFF_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_0: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	pMem = MsHMEMMalloc(handle, HMEM_TEST_BUFF_SIZE, 0);
	if (pMem)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_0: memory malloc 1 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	for (idx=0;;idx++)
	{
		pMem = MsHMEMMalloc(handle, 1<<idx, 0);
		if (NULL == pMem)
			break;
	}

	MsHMEMQueryHeapStatus(handle, &AStatus);

	if (AStatus.MaxFreeSize >= (u32)(1<<idx))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_0: memory malloc 2 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

TO_RESULT:
	if (handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}


static void _test_OS_hmem_1(void)
{
	void *HmemUTBuf = NULL;
	u32 handle = 0;
	void *pMem = NULL;
	int i, ret = 1;
	ghStatus_t AStatus;
	ghStatus_t BStatus;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, HMEM_TEST_BUFF_SIZE, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_1: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (0 == (handle=MsHMEMCreate(HmemUTBuf, HMEM_TEST_BUFF_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_1: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	MsHMEMQueryHeapStatus(handle, &AStatus);

	for (i=0;;i++)
	{
		pMem = MsHMEMGetHeapMemory(handle, 1<<i, 0);
		if (NULL == pMem)
			break;

		MsHMEMReleaseHeapMemory(pMem, 0);
	}

	MsHMEMQueryHeapStatus(handle, &BStatus);

	if (((AStatus.TotalFreeSize+AStatus.TotalAllocSize+AStatus.MemOverhead) != (BStatus.TotalFreeSize+BStatus.TotalAllocSize+BStatus.MemOverhead))
		|| (AStatus.TotalFreeSize != BStatus.TotalFreeSize)
		|| (AStatus.MaxFreeSize != BStatus.MaxFreeSize)
		|| (AStatus.MaxTotalAllocSize >= BStatus.MaxTotalAllocSize))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_1: check report 1 failed\n");
		ret = 0;
		goto TO_RESULT;
	}


	for (i=0;;i++)
	{
		pMem = MsHMEMGetHeapMemory(handle, 1<<i, 0);
		if (NULL == pMem)
			break;
	}

	MsHMEMQueryHeapStatus(handle, &BStatus);

	if (((AStatus.TotalFreeSize+AStatus.TotalAllocSize+AStatus.MemOverhead) != (BStatus.TotalFreeSize+BStatus.TotalAllocSize+BStatus.MemOverhead))
		|| (AStatus.TotalFreeSize <= BStatus.TotalFreeSize)
		|| (AStatus.MaxFreeSize <= BStatus.MaxFreeSize))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_1: check report 2 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

TO_RESULT:
	if (handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}


static void _test_OS_hmem_2(void)
{
	void *HmemUTBuf = NULL;
	u32 handle = 0;
	void *pMem = NULL;
	u32 i = 32, j, k, ret = 1;
	ghStatus_t AStatus, BStatus;
	gpStatus_t CStatus;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, HMEM_TEST_BUFF_SIZE, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_2: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (0 == (handle=MsHMEMCreate(HmemUTBuf, HMEM_TEST_BUFF_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_2: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (RTK_OK != (ret=MsHMEMInitializePool(handle, (pgpDesc_t)&PoolDesc, PoolDescNum)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_2: pool init failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	MsHMEMQueryHeapStatus(handle, &AStatus);

	for (j = 0; j < PoolDescNum; j++)
	{
		for (k = 0; k < PoolDesc[j].ClusterNum; k++)
			pMem = MsHMEMGetPoolMemory(handle, PoolDesc[j].ClusterSize, 0);
	}

	if (RTK_OK != MsHMEMReleasePoolMemory(pMem, 0))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_2: free 1 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (NULL == MsHMEMGetPoolMemory(handle, PoolDesc[j-1].ClusterSize, 0))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_2: alloc 1 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	MsHMEMQueryHeapStatus(handle, &BStatus);

	for (i = 0; i < PoolDescNum; i++)
	{
		MsHMEMQueryPoolStatus(handle, i, &CStatus);
		if (CStatus.CurrUsedClusters != CStatus.ClusterNum
			|| CStatus.CurrUsedClusters != PoolDesc[i].ClusterNum)
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_2: pool verify failed\n");
			ret = 0;
			goto TO_RESULT;
		}
	}

	if (((AStatus.TotalFreeSize+AStatus.TotalAllocSize+AStatus.MemOverhead) != (BStatus.TotalFreeSize+BStatus.TotalAllocSize+BStatus.MemOverhead))
		|| (AStatus.TotalFreeSize != BStatus.TotalFreeSize)
		|| (AStatus.MaxFreeSize != BStatus.MaxFreeSize))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_2: check report failed\n");
		ret = 0;
		goto TO_RESULT;
	}

TO_RESULT:
	if (handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}


static void _test_OS_hmem_3(void)
{
	void *HmemUTBuf = NULL;
	u32 handle1 = 0, handle2 = 0;
	void *buf1 = NULL, *buf2 = NULL;
	void *p1Mem = NULL, *p2Mem = NULL;
	int i = 6, ret = 1;
	ghStatus_t A1Status, A2Status;
	ghStatus_t B1Status, B2Status;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, HMEM_TEST_BUFF_SIZE, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_3: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	buf1 = HmemUTBuf;
	buf2 = (void*)(((u32)HmemUTBuf+HMEM_TEST_BUFF1_SIZE+50*1024+3) & ~3);

	if (0 == (handle1=MsHMEMCreate(buf1, HMEM_TEST_BUFF1_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_3: handle1 create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (0 == (handle2=MsHMEMCreate(buf2, HMEM_TEST_BUFF1_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_3: handle2 create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	MsHMEMQueryHeapStatus(handle1, &A1Status);
	MsHMEMQueryHeapStatus(handle2, &A2Status);

	p1Mem = (void*)1;
	p2Mem = (void*)1;

	for (;;)
	{
		if (NULL != p1Mem)
		{
			p1Mem = MsHMEMGetHeapMemory(handle1, 1<<i, 0);
			if (NULL != p1Mem
				&& ((p1Mem < buf1 || p1Mem > (void*)((u32)buf1+HMEM_TEST_BUFF1_SIZE))
					|| !MsHMEMIsHeapMemory(p1Mem)))
			{
				ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_3: handle1 allocate memory out of range\n");
				ret = 0;
				goto TO_RESULT;
			}
		}

		p2Mem = MsHMEMGetHeapMemory(handle2, 1<<i, 0);
		if (NULL != p2Mem
			&& ((p2Mem < buf2 || p2Mem > (void*)((u32)buf2+HMEM_TEST_BUFF1_SIZE))
				|| !MsHMEMIsHeapMemory(p2Mem)))
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_3: handle2 allocate memory out of range\n");
			ret = 0;
			goto TO_RESULT;
		}

		if (NULL == p1Mem && NULL == p2Mem)
			break;
		i++;
	}

	MsHMEMQueryHeapStatus(handle1, &B1Status);
	MsHMEMQueryHeapStatus(handle2, &B2Status);

	if (memcmp(&B1Status, &B2Status, sizeof(ghStatus_t)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_3: memcmp 1 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (memcmp(&B1Status, &B2Status, sizeof(ghStatus_t)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_3: memcmp 2 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

TO_RESULT:
	if (handle1)
		MsHMEMClose(handle1);

	if (handle2)
		MsHMEMClose(handle2);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}


static void _test_OS_hmem_4(void)
{
	void *HmemUTBuf = NULL;
	u32 handle1 = 0, handle2 = 0;
	void *buf2 = NULL;
	void *pH1PMem = NULL, *pH1HMem = NULL, *pH2PMem = NULL, *pH2HMem = NULL;
	int ret;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, HMEM_TEST_BUFF_SIZE, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_4: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (0 == (handle1=MsHMEMCreate(HmemUTBuf, HMEM_TEST_BUFF_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_4: handle1 create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (RTK_OK != MsHMEMInitializePool(handle1, (pgpDesc_t)&PoolDesc, PoolDescNum))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_4: handle1 pool init failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (NULL == (buf2=MsHMEMGetHeapMemory(handle1, HMEM_TEST_BUFF1_SIZE, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_4: handle2 create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (0 == (handle2=MsHMEMCreate(buf2, HMEM_TEST_BUFF1_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_4: handle2 create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (RTK_OK != (ret=MsHMEMInitializePool(handle2, (pgpDesc_t)&PoolDesc, PoolDescNum)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_4: handle2 pool init failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	pH1PMem = MsHMEMGetPoolMemory(handle1, 1024, 0);
	pH1HMem = MsHMEMGetHeapMemory(handle1, 1024, 0);
	pH2PMem = MsHMEMGetPoolMemory(handle2, 1024, 0);
	pH2HMem = MsHMEMGetHeapMemory(handle2, 1024, 0);

	if (NULL == pH1PMem || NULL == pH1HMem
		|| NULL == pH2PMem || NULL == pH2HMem)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_4: get pool or heap memory failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (FALSE == MsHMEMIsPoolMemory(pH1PMem)
		|| FALSE == MsHMEMIsPoolMemory(pH2PMem)
		|| TRUE == MsHMEMIsPoolMemory(pH1HMem)
		|| TRUE == MsHMEMIsPoolMemory(pH2HMem))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_4: handle1 abnormally manage memory\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (TRUE == MsHMEMIsHeapMemory(pH1PMem)
		|| TRUE == MsHMEMIsHeapMemory(pH2PMem)
		|| FALSE == MsHMEMIsHeapMemory(pH1HMem)
		|| FALSE == MsHMEMIsHeapMemory(pH2HMem))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_4: handle2 abnormally manage memory\n");
		ret = 0;
		goto TO_RESULT;
	}

	MsHMEMReleasePoolMemory(pH1PMem, 0);
	MsHMEMReleaseHeapMemory(pH1HMem, 0);
	MsHMEMReleasePoolMemory(pH2PMem, 0);
	MsHMEMReleaseHeapMemory(pH2HMem, 0);

TO_RESULT:
	if (handle2)
		MsHMEMClose(handle2);

	if (buf2)
		MsHMEMFree(buf2, 0);

	if (handle1)
		MsHMEMClose(handle1);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}


static void _test_OS_hmem_5(void)
{
	void *HmemUTBuf = NULL;
	u32 handle1 = 0, handle2 = 0;
	void *buf1 = NULL, *buf2 = NULL, *buf3 = NULL, *buf4 = NULL;
	int ret = 1;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, HMEM_TEST_BUFF_SIZE, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_5: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	buf1 = (void*)((u32)HmemUTBuf+300*1024);

	if (0 == (handle1=MsHMEMCreate(buf1, HMEM_TEST_BUFF1_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_5: handle1 create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	buf2 = (void*)((u32)HmemUTBuf + HMEM_TEST_BUFF1_SIZE + 100*1024);

	if (0 != MsHMEMCreate(buf2, HMEM_TEST_BUFF1_SIZE))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_5: handle 1 is abnormally created\n");
		ret = 0;
		goto TO_RESULT;
	}

	buf3 = HmemUTBuf;

	if (0 != MsHMEMCreate(buf3, HMEM_TEST_BUFF1_SIZE))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_5: handle 2 is abnormally created\n");
		ret = 0;
		goto TO_RESULT;
	}

	buf4 = (void*)((u32)HmemUTBuf+500*1024);

	if (0 == (handle2=MsHMEMCreate(buf4, 100*1024)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_5: handle2 create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

TO_RESULT:
	if (handle2)
		MsHMEMClose(handle2);

	if (handle1)
		MsHMEMClose(handle1);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}


static void _test_OS_hmem_6(void)
{
	void *HmemUTBuf = NULL;
	u32 handle = 0;
	void *pMem[10] = {NULL};
	int i, ret = 1;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, HMEM_TEST_BUFF_SIZE, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_6: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (0 == (handle=MsHMEMCreate(HmemUTBuf, HMEM_TEST_BUFF1_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_6: handle1 create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (NULL == (pMem[0]=MsHMEMMalloc(handle, 95*1024, 0))
		|| NULL == (pMem[1]=MsHMEMMalloc(handle, 90*1024, 0))
		|| NULL == (pMem[2]=MsHMEMMalloc(handle, 10*1024, 0))
		|| NULL == (pMem[3]=MsHMEMMalloc(handle, 40*1024, 0))
		|| NULL == (pMem[4]=MsHMEMMalloc(handle, 20*1024, 0))
		|| NULL == (pMem[5]=MsHMEMMalloc(handle, 140*1024, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_6: get heap memory precondition fail\n");
		ret = 0;
		goto TO_RESULT;
	}

	MsHMEMFree(pMem[1], 0);
	pMem[1] = NULL;
	MsHMEMFree(pMem[3], 0);
	pMem[3] = NULL;
	MsHMEMFree(pMem[5], 0);
	pMem[5] = NULL;

	if (NULL == (pMem[1]=MsHMEMMalloc(handle, 130*1024, 0))
		|| NULL == (pMem[3]=MsHMEMMalloc(handle, 80*1024, 0))
		|| NULL == (pMem[5]=MsHMEMMalloc(handle, 30*1024, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_6: get heap memory 1 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (NULL != MsHMEMMalloc(handle, 50*1024, 0))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_6: get heap memory 2 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	MsHMEMFree(pMem[4], 0);
	pMem[4] = NULL;
	MsHMEMFree(pMem[5], 0);
	pMem[5] = NULL;

	if (NULL == (pMem[4]=MsHMEMMalloc(handle, 50*1024, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_6: get heap memory 3 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	for (i = 1; i < sizeof(pMem)/sizeof(void*) ; i++)
	{
		if (pMem[i])
		{
			if (NULL != MsHMEMMalloc(handle, 290*1024, 0))
			{
				ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_6: get heap memory 4 failed\n");
				ret = 0;
				goto TO_RESULT;
			}

			MsHMEMFree(pMem[i], 0);
			pMem[i] = NULL;
		}
	}

	if (NULL == MsHMEMMalloc(handle, 290*1024, 0))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_6: get heap memory 5 failed\n");
		ret = 0;
		goto TO_RESULT;
	}

TO_RESULT:
	if (handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}

static void __test_OS_hmem_7_init_0(void *userdata)
{
	u32 handle = (u32)userdata;
	int idx = 0;
	KerTestMsg_t *Msg;

	while((idx++)<1000)
	{
		Msg = (KerTestMsg_t*)MsHMEMMalloc(ms_memoryhandle, sizeof(KerTestMsg_t), 0);
		Msg->Header.Length = sizeof(KerTestMsg_t);
		Msg->Header.MbxSrc = MsCurrTask();
		Msg->Header.MbxDst = KerTestTaskId[3];
		if (MsCurrTask() == KerTestTaskId[0])
			Msg->Header.TypMsg = KERNEL_TEST_MSG0;
		else if (MsCurrTask() == KerTestTaskId[1])
			Msg->Header.TypMsg = KERNEL_TEST_MSG1;
		else
			Msg->Header.TypMsg = KERNEL_TEST_MSG2;
		Msg->Body.userdata = (u32)MsHMEMMalloc(handle, idx, 0);
		MsSend(KerTestTaskId[3], Msg);
		MsSleep(3);
	}
	q++;
}

static void __test_OS_hmem_7_parser_0(vm_msg_t *pMessage)
{
	KerTestMsg_t *pMsg = (KerTestMsg_t*)pMessage;

	if (pMsg == NULL)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_OS_hmem_7_parser_0: Null message");
		q+=10;
	}
	else if (pMsg->Header.TypMsg == VM_OS_TIMER_EXPIRED)
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_OS_hmem_7_parser_0: wrong timer message");
		q+=10;
	}
	else if (pMsg->Header.TypMsg == KERNEL_TEST_MSG0)
	{
		MsHMEMFree((void*)pMsg->Body.userdata, 0);
		q1++;
	}
	else if (pMsg->Header.TypMsg == KERNEL_TEST_MSG1)
	{
		MsHMEMFree((void*)pMsg->Body.userdata, 0);
		q2++;
	}
	else if (pMsg->Header.TypMsg == KERNEL_TEST_MSG2)
	{
		MsHMEMFree((void*)pMsg->Body.userdata, 0);
		q3++;
	}
	else
	{
		ven_std_sprintf((char*)KerTestOutput, "__test_OS_hmem_7_parser_0: Unknown message 0x%4x", pMsg->Header.TypMsg);
		q+=10;
	}
}

static void _test_OS_hmem_7(void)
{
	void *HmemUTBuf = NULL;
	static u8 HmemUTBuf1[HMEM_TEST_BUFF1_SIZE];
	u32 handle1 = 0, handle2 = 0;
	int ret = 1;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	KerTestTaskId[0] = 0;
	KerTestTaskId[1] = 0;
	KerTestTaskId[2] = 0;
	KerTestTaskId[3] = 0;

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, HMEM_TEST_BUFF_SIZE, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_7: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (0 == (handle1=MsHMEMCreate(HmemUTBuf, HMEM_TEST_BUFF1_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_7: handle1 create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (RTK_OK != MsHMEMInitializePool(handle1, (pgpDesc_t)&PoolDesc, PoolDescNum))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_7: handle1 pool init failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (0 == (handle2=MsHMEMCreate(HmemUTBuf1, HMEM_TEST_BUFF1_SIZE)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_7: handle2 create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (RTK_OK != MsHMEMInitializePool(handle2, (pgpDesc_t)&PoolDesc, PoolDescNum))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_7: handle2 pool init failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	q = q1 = q2 = q3 = 0;

	KerTestTaskArgs[0].AppliInit = __test_OS_hmem_7_init_0;
	KerTestTaskArgs[0].AppliParser = emptyParser;
	KerTestTaskArgs[0].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[0].pStackTop = (u32*)MsHMEMMalloc(ms_memoryhandle, KerTestTaskArgs[0].StackSize, 0);
	KerTestTaskArgs[0].pInitArgs = (void*)ms_memoryhandle;
	strcpy(KerTestTaskArgs[0].TaskName, "task1");
	KerTestTaskArgs[1].AppliInit = __test_OS_hmem_7_init_0;
	KerTestTaskArgs[1].AppliParser = emptyParser;
	KerTestTaskArgs[1].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[1].pStackTop = (u32*)MsHMEMMalloc(ms_memoryhandle, KerTestTaskArgs[1].StackSize, 0);
	KerTestTaskArgs[1].pInitArgs = (void*)handle1;
	strcpy(KerTestTaskArgs[1].TaskName, "task2");
	KerTestTaskArgs[2].AppliInit = __test_OS_hmem_7_init_0;
	KerTestTaskArgs[2].AppliParser = emptyParser;
	KerTestTaskArgs[2].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[2].pStackTop = (u32*)MsHMEMMalloc(ms_memoryhandle, KerTestTaskArgs[2].StackSize, 0);
	KerTestTaskArgs[2].pInitArgs = (void*)handle2;
	strcpy(KerTestTaskArgs[2].TaskName, "task3");
	KerTestTaskArgs[3].AppliInit = emptyInit;
	KerTestTaskArgs[3].AppliParser = __test_OS_hmem_7_parser_0;
	KerTestTaskArgs[3].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[3].pStackTop = (u32*)MsHMEMMalloc(ms_memoryhandle, KerTestTaskArgs[3].StackSize, 0);
	strcpy(KerTestTaskArgs[3].TaskName, "task4");

	MsCreateTask(&KerTestTaskArgs[0]);
	MsCreateTask(&KerTestTaskArgs[1]);
	MsCreateTask(&KerTestTaskArgs[2]);
	MsCreateTask(&KerTestTaskArgs[3]);

	MsStartTask(KerTestTaskId[0]);
	MsStartTask(KerTestTaskId[1]);
	MsStartTask(KerTestTaskId[2]);
	MsStartTask(KerTestTaskId[3]);

	while(3 > q)
		MsSleep(VM_RTK_MS_TO_TICK(500));

TO_RESULT:
	if (KerTestTaskId[0])
	{
		MsDeleteTask(KerTestTaskId[0]);
		KerTestTaskId[0] = 0;
		MsHMEMFree(KerTestTaskArgs[0].pStackTop, 0);
		KerTestTaskArgs[0].pStackTop = NULL;
	}

	if (KerTestTaskId[1])
	{
		MsDeleteTask(KerTestTaskId[1]);
		KerTestTaskId[1] = 0;
		MsHMEMFree(KerTestTaskArgs[1].pStackTop, 0);
		KerTestTaskArgs[1].pStackTop = NULL;
	}

	if (KerTestTaskId[2])
	{
		MsDeleteTask(KerTestTaskId[2]);
		KerTestTaskId[2] = 0;
		MsHMEMFree(KerTestTaskArgs[2].pStackTop, 0);
		KerTestTaskArgs[2].pStackTop = NULL;
	}

	if (KerTestTaskId[3])
	{
		MsDeleteTask(KerTestTaskId[3]);
		KerTestTaskId[3] = 0;
		MsHMEMFree(KerTestTaskArgs[3].pStackTop, 0);
		KerTestTaskArgs[3].pStackTop = NULL;
	}

	if (handle1)
		MsHMEMClose(handle1);

	if (handle2)
		MsHMEMClose(handle2);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	if (q > 3 || 3000 != (q1+q2+q3))
		ret = 0;
	VEN_TEST_CHECK_RESULT(ret);
}


#define HTABLE_NUM 20
static void _test_OS_hmem_8(void)
{
	void *HmemUTBuf = NULL;
	int ret = 1, idx = 0;
	u32 hTable[HTABLE_NUM] = {0};
	const gpDesc_t testPoolDesc[] =
	{
		{50, 137} // 6.7 KB
	};

	memset(KerTestOutput, 0, sizeof(KerTestOutput));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, HMEM_TEST_BUFF_SIZE, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_8: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	for (idx=0;idx<HTABLE_NUM;idx++)
	{
		hTable[idx] = (u32)MsHMEMCreate((void*)((u32)HmemUTBuf+idx*30*1024), 25*1024);
		if (0 == hTable[idx])
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_8: handle create failed\n");
			ret = 0;
			goto TO_RESULT;
		}

		if (RTK_OK != MsHMEMInitializePool(hTable[idx], (pgpDesc_t)&testPoolDesc, sizeof(testPoolDesc)/sizeof(gpDesc_t)))
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_8: pool init failed\n");
			ret = 0;
			goto TO_RESULT;
		}
	}

	for (idx=1;idx<=10000;idx++)
	{
		MsHMEMMalloc(hTable[idx%HTABLE_NUM], idx, 0);
	}

	MsHMEMProfiling();

TO_RESULT:
	for (idx=0;idx<HTABLE_NUM;idx++)
	{
		if (hTable[idx])
		{
			MsHMEMClose(hTable[idx]);
			hTable[idx] = 0;
		}
	}

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}

static void _test_OS_hmem_9(void)
{
	void *HmemUTBuf = NULL, *pMem[10];
	int ret = 1, i;
	u32 handle = 0;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));
	memset(pMem, 0, sizeof(pMem));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, 2<<20, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_9: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	handle = (u32)MsHMEMCreate((void*)HmemUTBuf, 2<<20);
	if (0 == handle)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_9: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (FALSE == MsHMEMVMACreate(handle, 0xDE000000, 0x400000, VMA_PAGE_4K))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_9: vma create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	for (i=1;i<6;i++)
	{
		pMem[i] = MsHMEMMalloc(handle, i<<10, 0);
		if (NULL == pMem[i])
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_9: vmalloc size=%d failed\n", i<<10);
			ret = 0;
			goto TO_RESULT;
		}
	}

TO_RESULT:
	for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
	{
		if (pMem[i])
		{
			MsHMEMFree(pMem[i], 0);
			pMem[i] = NULL;
		}
	}

	MsHMEMVMADestroy(handle);

	if (0 < handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}

static void _test_OS_hmem_10(void)
{
	void *HmemUTBuf = NULL, *pMem[10];
	int ret = 1, i, j;
	u32 handle = 0;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));
	memset(pMem, 0, sizeof(pMem));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, 2<<20, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_10: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	handle = (u32)MsHMEMCreate((void*)HmemUTBuf, 2<<20);
	if (0 == handle)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_10: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (FALSE == MsHMEMVMACreate(handle, 0xDE000000, 0x400000, VMA_PAGE_4K))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_10: vma create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	for (i=1, j=100;i<6;i++, j+=100)
	{
		pMem[i] = MsHMEMMalloc(handle, j<<10, 0);
		if (NULL == pMem[i])
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_10: vmalloc size=%d failed\n", i<<10);
			ret = 0;
			goto TO_RESULT;
		}
	}

	MsHMEMFree(pMem[3], 0);
	pMem[3] = NULL;

	pMem[6] = MsHMEMMalloc(handle, 600<<10, 0);
	if (NULL == pMem[6])
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_10: vmalloc size=%d failed\n", 6<<10);
		ret = 0;
		goto TO_RESULT;
	}

	memset(pMem[6], 'a', 600<<10);

TO_RESULT:
	for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
	{
		if (pMem[i])
		{
			MsHMEMFree(pMem[i], 0);
			pMem[i] = NULL;
		}
	}

	MsHMEMVMADestroy(handle);

	if (0 < handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}

static void _test_OS_hmem_11(void)
{
	void *HmemUTBuf = NULL;
	int ret = 1, i, j;
	u32 handle = 0;
	Mem_t pMem[10];

	memset(KerTestOutput, 0, sizeof(KerTestOutput));
	memset(pMem, 0, sizeof(pMem));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, 2<<20, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_11: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	handle = (u32)MsHMEMCreate((void*)HmemUTBuf, 2<<20);
	if (0 == handle)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_11: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (FALSE == MsHMEMVMACreate(handle, 0xDE000000, 0x400000, VMA_PAGE_4K))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_11: vma create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	for (i=1, j=100;i<6;i++, j+=100)
	{
		pMem[i].size = j<<10;
		pMem[i].ptr = MsHMEMMalloc(handle, pMem[i].size, 0);
		if (NULL == pMem[i].ptr)
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_11: vmalloc size=%d failed\n", pMem[i].size);
			ret = 0;
			goto TO_RESULT;
		}
	}

	MsHMEMFree(pMem[1].ptr, 0);
	pMem[1].ptr = NULL;

	MsHMEMFree(pMem[3].ptr, 0);
	pMem[3].ptr = NULL;

	pMem[6].size = (557<<10)+123;
	pMem[6].ptr = MsHMEMMalloc(handle, pMem[6].size, 0);
	if (NULL == pMem[6].ptr)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_11: vmalloc size=%d failed\n", pMem[6].size);
		ret = 0;
		goto TO_RESULT;
	}

	pMem[7].size = (324<<10)+789;
	pMem[7].ptr = MsHMEMMalloc(handle, pMem[7].size, 0);
	if (NULL == pMem[7].ptr)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_11: vmalloc size=%d failed\n", pMem[7].size);
		ret = 0;
		goto TO_RESULT;
	}

	MsHMEMFree(pMem[4].ptr, 0);
	pMem[4].ptr = NULL;

	pMem[4].size = (423<<10)+456;
	pMem[4].ptr = MsHMEMMalloc(handle, pMem[4].size, 0);
	if (NULL == pMem[4].ptr)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_11: vmalloc size=%d failed\n", pMem[4].size);
		ret = 0;
		goto TO_RESULT;
	}

	for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
	{
		if (pMem[i].ptr)
			memset(pMem[i].ptr, 'a'+i, pMem[i].size);
	}

TO_RESULT:
	for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
	{
		if (pMem[i].ptr)
		{
			MsHMEMFree(pMem[i].ptr, 0);
			pMem[i].ptr = NULL;
		}
	}

	MsHMEMVMADestroy(handle);

	if (0 < handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}

static void _test_OS_hmem_12(void)
{
	void *HmemUTBuf = NULL;
	int ret = 1, i, j;
	u32 handle = 0;
	Mem_t pMem[100];

	memset(KerTestOutput, 0, sizeof(KerTestOutput));
	memset(pMem, 0, sizeof(pMem));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, 1<<20, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_12: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	handle = (u32)MsHMEMCreate((void*)HmemUTBuf, 1<<20);
	if (0 == handle)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_12: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (FALSE == MsHMEMVMACreate(handle, 0xDE000000, 0x400000, VMA_PAGE_4K))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_12: vma create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	for (i=0;i<5000000;i++)
	{
		j = sys_Random8()%(sizeof(pMem)/sizeof(pMem[0]));
		if (NULL == pMem[j].ptr)
		{
			pMem[j].size = sys_Random32()%(512<<10);
			pMem[j].ptr = MsHMEMMalloc(handle, pMem[j].size, 0);
			if (pMem[j].ptr)
				memset(pMem[j].ptr, j, pMem[j].size);
		}
		else
		{
			MsHMEMFree(pMem[j].ptr, 0);
			pMem[j].ptr = NULL;
		}

		if (0 == i%1000)
			MsSleep(1);
	}

TO_RESULT:
	for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
	{
		if (pMem[i].ptr)
		{
			MsHMEMFree(pMem[i].ptr, 0);
			pMem[i].ptr = NULL;
		}
	}

	MsHMEMVMADestroy(handle);

	if (0 < handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}

static void _test_OS_hmem_13(void)
{
	void *HmemUTBuf = NULL;
	int ret = 1, i, j;
	u32 handle = 0;
	Mem_t pMem[10];

	memset(KerTestOutput, 0, sizeof(KerTestOutput));
	memset(pMem, 0, sizeof(pMem));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, 2<<20, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_13: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	handle = (u32)MsHMEMCreate((void*)HmemUTBuf, 2<<20);
	if (0 == handle)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_13: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (FALSE == MsHMEMVMACreate(handle, 0xDE000000, 0x400000, VMA_PAGE_1K))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_13: vma create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	for (i=1, j=100;i<6;i++, j+=100)
	{
		pMem[i].size = j<<10;
		pMem[i].ptr = MsHMEMMalloc(handle, pMem[i].size, 0);
		if (NULL == pMem[i].ptr)
		{
			ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_13: vmalloc size=%d failed\n", pMem[i].size);
			ret = 0;
			goto TO_RESULT;
		}
	}

	MsHMEMFree(pMem[1].ptr, 0);
	pMem[1].ptr = NULL;

	MsHMEMFree(pMem[3].ptr, 0);
	pMem[3].ptr = NULL;

	pMem[6].size = (557<<10)+123;
	pMem[6].ptr = MsHMEMMalloc(handle, pMem[6].size, 0);
	if (NULL == pMem[6].ptr)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_13: vmalloc size=%d failed\n", pMem[6].size);
		ret = 0;
		goto TO_RESULT;
	}

	pMem[7].size = (324<<10)+789;
	pMem[7].ptr = MsHMEMMalloc(handle, pMem[7].size, 0);
	if (NULL == pMem[7].ptr)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_13: vmalloc size=%d failed\n", pMem[7].size);
		ret = 0;
		goto TO_RESULT;
	}

	MsHMEMFree(pMem[4].ptr, 0);
	pMem[4].ptr = NULL;

	pMem[4].size = (423<<10)+456;
	pMem[4].ptr = MsHMEMMalloc(handle, pMem[4].size, 0);
	if (NULL == pMem[4].ptr)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_13: vmalloc size=%d failed\n", pMem[4].size);
		ret = 0;
		goto TO_RESULT;
	}

	for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
	{
		if (pMem[i].ptr)
			memset(pMem[i].ptr, 'a'+i, pMem[i].size);
	}

TO_RESULT:
	for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
	{
		if (pMem[i].ptr)
		{
			MsHMEMFree(pMem[i].ptr, 0);
			pMem[i].ptr = NULL;
		}
	}

	MsHMEMVMADestroy(handle);

	if (0 < handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}

static void _test_OS_hmem_14(void)
{
	void *HmemUTBuf = NULL;
	int ret = 1, i, j;
	u32 handle = 0;
	Mem_t pMem[100];

	memset(KerTestOutput, 0, sizeof(KerTestOutput));
	memset(pMem, 0, sizeof(pMem));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, 1<<20, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_14: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	handle = (u32)MsHMEMCreate((void*)HmemUTBuf, 1<<20);
	if (0 == handle)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_14: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (FALSE == MsHMEMVMACreate(handle, 0xDE000000, 0x400000, VMA_PAGE_1K))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_14: vma create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	for (i=0;i<5000000;i++)
	{
		j = sys_Random8()%(sizeof(pMem)/sizeof(pMem[0]));
		if (NULL == pMem[j].ptr)
		{
			pMem[j].size = sys_Random32()%(512<<10);
			pMem[j].ptr = MsHMEMMalloc(handle, pMem[j].size, 0);
			if (pMem[j].ptr)
				memset(pMem[j].ptr, j, pMem[j].size);
		}
		else
		{
			MsHMEMFree(pMem[j].ptr, 0);
			pMem[j].ptr = NULL;
		}

		if (0 == i%1000)
			MsSleep(1);
	}

TO_RESULT:
	for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
	{
		if (pMem[i].ptr)
		{
			MsHMEMFree(pMem[i].ptr, 0);
			pMem[i].ptr = NULL;
		}
	}

	MsHMEMVMADestroy(handle);

	if (0 < handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}


static void _test_OS_hmem_15(void)
{
	extern void* MsHMEMGetHeapMemoryAtEnd(u32 Handle, u32 nMemSize, u32 lr);
	void *HmemUTBuf = NULL;
	int ret = 1, i;
	u32 handle = 0;
	void *pMem[10];
	ghStatus_t sStatus;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));
	memset(pMem, 0, sizeof(pMem));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, 50<<10, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_15: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	handle = (u32)MsHMEMCreate((void*)HmemUTBuf, 50<<10);
	if (0 == handle)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_15: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	MsHMEMQueryHeapStatus(handle, (pghStatus_t)&sStatus);

	pMem[0] = MsHMEMMalloc(handle, (2<<10)+1, 0);
	pMem[1] = MsHMEMMalloc(handle, (2<<10)+33, 0);
	pMem[2] = MsHMEMMalloc(handle, (2<<10)+65, 0);
	pMem[3] = MsHMEMMalloc(handle, (2<<10)+97, 0);
	pMem[4] = MsHMEMMalloc(handle, (2<<10)+129, 0);

	pMem[5] = MsHMEMGetHeapMemoryAtEnd(handle, 36800, 0);
	memset(pMem[5], 'a', 36800);

	MsHMEMQueryHeapStatus(handle, (pghStatus_t)&sStatus);

	MsHMEMFree(pMem[0], 0);
	pMem[0] = NULL;

	MsHMEMQueryHeapStatus(handle, (pghStatus_t)&sStatus);

	MsHMEMFree(pMem[2], 0);
	pMem[2] = NULL;

	MsHMEMQueryHeapStatus(handle, (pghStatus_t)&sStatus);

	MsHMEMFree(pMem[4], 0);
	pMem[4] = NULL;

	MsHMEMQueryHeapStatus(handle, (pghStatus_t)&sStatus);

	MsHMEMFree(pMem[5], 0);
	pMem[5] = NULL;

	MsHMEMQueryHeapStatus(handle, (pghStatus_t)&sStatus);

	pMem[5] = MsHMEMGetHeapMemoryAtEnd(handle, 26800, 0);
	memset(pMem[5], 'a', 26800);

	MsHMEMQueryHeapStatus(handle, (pghStatus_t)&sStatus);

TO_RESULT:
	for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
	{
		if (pMem[i])
		{
			MsHMEMFree(pMem[i], 0);
			pMem[i] = NULL;
		}
	}

	MsHMEMQueryHeapStatus(handle, (pghStatus_t)&sStatus);

	if (0 < handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}

static void _test_OS_hmem_16(void)
{
	extern void* MsHMEMMallocAtEnd(u32 Handle, u32 nMemSize, u32 lr);
	extern s32 MsHMEMHeapWalkStatus(u32 Handle);
	void *HmemUTBuf = NULL;
	int ret = 1, i, j, k;
	u32 handle = 0;
	void *pMem[10];
	ghStatus_t sStatus;

	memset(KerTestOutput, 0, sizeof(KerTestOutput));
	memset(pMem, 0, sizeof(pMem));

	if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, 500<<10, 0)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_16: buffer malloc failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	handle = (u32)MsHMEMCreate((void*)HmemUTBuf, 500<<10);
	if (0 == handle)
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_16: handle create failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	if (RTK_OK != (ret=MsHMEMInitializePool(handle, (pgpDesc_t)&PoolDesc, PoolDescNum)))
	{
		ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_16: pool init failed\n");
		ret = 0;
		goto TO_RESULT;
	}

	pMem[0] = MsHMEMMallocAtEnd(handle, (2<<10)+1, 0);
	pMem[1] = MsHMEMMallocAtEnd(handle, (2<<10)+33, 0);

	for (j = 0; j < PoolDescNum; j++)
	{
		for (k = 0; k < PoolDesc[j].ClusterNum; k++)
			pMem[2] = MsHMEMGetPoolMemory(handle, PoolDesc[j].ClusterSize, 0);
	}

	MsHMEMHeapWalkStatus(handle);

	for (j = 0; j < PoolDescNum; j++)
	{
		pMem[2] = MsHMEMMallocAtEnd(handle, PoolDesc[j].ClusterSize, 0);
	}

	MsHMEMHeapWalkStatus(handle);

TO_RESULT:
	for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
	{
		if (pMem[i])
		{
			MsHMEMFree(pMem[i], 0);
			pMem[i] = NULL;
		}
	}

	MsHMEMQueryHeapStatus(handle, (pghStatus_t)&sStatus);

	if (0 < handle)
		MsHMEMClose(handle);

	if (HmemUTBuf)
		MsHMEMFree(HmemUTBuf, 0);

	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
	VEN_TEST_CHECK_RESULT(ret);
}

static void _test_OS_hmem_17(void)
{
    void *HmemUTBuf = NULL, *pMem[10], *ptr;
    int ret = 1, i, j;
    u32 handle = 0;
    HMVMB_t vmb;

    memset(KerTestOutput, 0, sizeof(KerTestOutput));
    memset(pMem, 0, sizeof(pMem));

    if (NULL == (HmemUTBuf=MsHMEMMalloc(ms_memoryhandle, 2<<20, 0)))
    {
        ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_17: buffer malloc failed\n");
        ret = 0;
        goto TO_RESULT;
    }

    handle = (u32)MsHMEMCreate((void*)HmemUTBuf, 2<<20);
    if (0 == handle)
    {
        ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_17: handle create failed\n");
        ret = 0;
        goto TO_RESULT;
    }

    if (FALSE == MsHMEMVMACreate(handle, 0xDE000000, 0x400000, VMA_PAGE_4K))
    {
        ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_17: vma create failed\n");
        ret = 0;
        goto TO_RESULT;
    }

    for (i=1, j=100;i<6;i++, j+=100)
    {
        pMem[i] = MsHMEMMalloc(handle, j<<10, 0);
        if (NULL == pMem[i])
        {
            ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_17: vmalloc size=%d failed\n", i<<10);
            ret = 0;
            goto TO_RESULT;
        }
    }

    MsHMEMFree(pMem[3], 0);
    pMem[3] = NULL;

    pMem[6] = MsHMEMMalloc(handle, 600<<10, 0);
    if (NULL == pMem[6])
    {
        ven_std_sprintf((char*)KerTestOutput, "_test_OS_hmem_17: vmalloc size=%d failed\n", 6<<10);
        ret = 0;
        goto TO_RESULT;
    }

    ptr = pMem[6];

    do {
        ptr = MsHMEMVMAWalk(ptr, &vmb);
        ptr = vmb.next;
    } while(ptr);

    memset(pMem[6], 'a', 600<<10);

TO_RESULT:
    for (i=0;i<sizeof(pMem)/sizeof(pMem[0]);i++)
    {
        if (pMem[i])
        {
            MsHMEMFree(pMem[i], 0);
            pMem[i] = NULL;
        }
    }

    MsHMEMVMADestroy(handle);

    if (0 < handle)
        MsHMEMClose(handle);

    if (HmemUTBuf)
        MsHMEMFree(HmemUTBuf, 0);

    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
    VEN_TEST_CHECK_RESULT(ret);
}




volatile int countqueue[3]={0};

void TestTsScheduleTaskInit(void* usrdata)
{
	MsEnterRegion();
	memset(KerTestOutput, 0, sizeof(KerTestOutput));
	ven_std_sprintf((char*)KerTestOutput, "task init");
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

	MsLeaveRegion();
}

void TestTsScheduleTaskParser(vm_msg_t* arg)
{
    u32 tEnd = MsGetOsTick() + RTK_MS_TO_TICK(3000);

	do
    {
	    countqueue[0]++;
        if(MsGetOsTick()>tEnd)
            break;
	}
	while(1);
}
void TestTsScheduleTaskParser1(vm_msg_t* arg)
{
	u32 tEnd = MsGetOsTick() + RTK_MS_TO_TICK(3000);

	do
    {
	    countqueue[1]++;
        if(MsGetOsTick()>tEnd)
            break;
	}
	while(1);
}
void TestTsScheduleTaskParser2(vm_msg_t* arg)
{
	u32 tEnd = MsGetOsTick() + RTK_MS_TO_TICK(3000);

	do
    {
	    countqueue[2]++;
        if(MsGetOsTick()>tEnd)
            break;
	}
	while(1);
}



#if defined(__TIME_SLICE_SCHEDULE__)
static void _test_OS_MsTimeSliceScheduling(void)
{
    MsTaskCreateArgs_t TaskArgs;
    Msg_t *msg = NULL;
   // extern rtk_Task_t *rtk_Tasks[RTK_MAX_TASKS];

    strcpy(TaskArgs.TaskName, "DTask1");
    TaskArgs.AppliInit = TestTsScheduleTaskInit;
    TaskArgs.AppliParser = TestTsScheduleTaskParser;
    TaskArgs.ImmediatelyStart = TRUE;
    TaskArgs.StackSize = 8192;
    TaskArgs.Priority = 9;
    TaskArgs.pInitArgs = NULL;
    TaskArgs.TaskId = &KerTestTaskId[0];
    TaskArgs.pStackTop = MsAllocateMem(8192);
    TaskArgs.TimeSliceLeft = RTK_MS_TO_TICK(5);
    TaskArgs.TimeSliceMax = RTK_MS_TO_TICK(5);
    if(MS_OK != MsCreateTask(&TaskArgs))
        _ERROR((_RTK|FATAL, "ERROR"));

    strcpy(TaskArgs.TaskName, "DTask2");
	TaskArgs.AppliParser = TestTsScheduleTaskParser1;
    TaskArgs.TaskId = &KerTestTaskId[1];
    TaskArgs.pStackTop = MsAllocateMem(8192);
    if(MS_OK != MsCreateTask(&TaskArgs))
        _ERROR((_RTK|FATAL, "ERROR"));

    strcpy(TaskArgs.TaskName, "DTask3");
	TaskArgs.AppliParser = TestTsScheduleTaskParser2;
    TaskArgs.TaskId = &KerTestTaskId[2];
    TaskArgs.pStackTop = MsAllocateMem(8192);
    if(MS_OK != MsCreateTask(&TaskArgs))
        _ERROR((_RTK|FATAL, "ERROR"));


    //rtk_Tasks[g_uTaskId1].TimeSliceLeft = rtk_Tasks[g_uTaskId1].TimeSliceMax = 10;
	countqueue[0]=countqueue[1]=countqueue[2]=0;
    memset(KerTestOutput, 0, sizeof(KerTestOutput));

    // Send messages to tasks
    // Fake message to trigger task loop
    msg = (Msg_t*)MsAllocateMem(sizeof(Header_t));
	msg->Header.TypMsg = KERNEL_TEST_MSG0;
	msg->Header.MbxSrc = CUS14_MBX;
	msg->Header.MbxDst = KerTestTaskId[0];
	msg->Header.Length = 0;
    MsSend(KerTestTaskId[0], msg);

    //rtk_Tasks[g_uTaskId2].TimeSliceLeft = rtk_Tasks[g_uTaskId2].TimeSliceMax = 10;
    msg = (Msg_t*)MsAllocateMem(sizeof(Header_t));
    msg->Header.TypMsg = KERNEL_TEST_MSG1;
	msg->Header.MbxSrc = CUS14_MBX;
	msg->Header.MbxDst = KerTestTaskId[1];
	msg->Header.Length = 0;
    MsSend(KerTestTaskId[1], msg);

    //rtk_Tasks[g_uTaskId3].TimeSliceLeft = rtk_Tasks[g_uTaskId3].TimeSliceMax = 10;
    msg = (Msg_t*)MsAllocateMem(sizeof(Header_t));
    msg->Header.TypMsg = KERNEL_TEST_MSG2;
	msg->Header.MbxSrc = CUS14_MBX;
	msg->Header.MbxDst = KerTestTaskId[2];
	msg->Header.Length = 0;
    MsSend(KerTestTaskId[2], msg);

	MsSleep(RTK_MS_TO_TICK(3000));
	MsDeleteTask(KerTestTaskId[0]);
	MsDeleteTask(KerTestTaskId[1]);
	MsDeleteTask(KerTestTaskId[2]);

	ven_std_sprintf((char*)KerTestOutput, "1st count %d - %d - %d",countqueue[0],countqueue[1],countqueue[2]);
    VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

   // test MsCreateTaskMs
    strcpy(TaskArgs.TaskName, "DTask1");
    TaskArgs.AppliInit = TestTsScheduleTaskInit;
    TaskArgs.AppliParser = TestTsScheduleTaskParser;
    TaskArgs.ImmediatelyStart = TRUE;
    TaskArgs.StackSize = 8192;
    TaskArgs.Priority = 9;
    TaskArgs.pInitArgs = NULL;
    TaskArgs.TaskId = &KerTestTaskId[0];
    TaskArgs.pStackTop = MsAllocateMem(8192);
    TaskArgs.TimeSliceLeft = 5;
    TaskArgs.TimeSliceMax = 5;
    if(MS_OK != MsCreateTaskMs(&TaskArgs))
        _ERROR((_RTK|FATAL, "ERROR"));

    strcpy(TaskArgs.TaskName, "DTask2");
	TaskArgs.AppliParser = TestTsScheduleTaskParser1;
    TaskArgs.TaskId = &KerTestTaskId[1];
    TaskArgs.pStackTop = MsAllocateMem(8192);
    if(MS_OK != MsCreateTaskMs(&TaskArgs))
        _ERROR((_RTK|FATAL, "ERROR"));

    strcpy(TaskArgs.TaskName, "DTask3");
	TaskArgs.AppliParser = TestTsScheduleTaskParser2;
    TaskArgs.TaskId = &KerTestTaskId[2];
    TaskArgs.pStackTop = MsAllocateMem(8192);
    if(MS_OK != MsCreateTaskMs(&TaskArgs))
        _ERROR((_RTK|FATAL, "ERROR"));



	countqueue[0]=countqueue[1]=countqueue[2]=0;
    memset(KerTestOutput, 0, sizeof(KerTestOutput));

    // Send messages to tasks
    // Fake message to trigger task loop
    msg = (Msg_t*)MsAllocateMem(sizeof(Header_t));
	msg->Header.TypMsg = KERNEL_TEST_MSG0;
	msg->Header.MbxSrc = CUS14_MBX;
	msg->Header.MbxDst = KerTestTaskId[0];
	msg->Header.Length = 0;
    MsSend(KerTestTaskId[0], msg);

    msg = (Msg_t*)MsAllocateMem(sizeof(Header_t));
    msg->Header.TypMsg = KERNEL_TEST_MSG1;
	msg->Header.MbxSrc = CUS14_MBX;
	msg->Header.MbxDst = KerTestTaskId[1];
	msg->Header.Length = 0;
    MsSend(KerTestTaskId[1], msg);

    msg = (Msg_t*)MsAllocateMem(sizeof(Header_t));
    msg->Header.TypMsg = KERNEL_TEST_MSG2;
	msg->Header.MbxSrc = CUS14_MBX;
	msg->Header.MbxDst = KerTestTaskId[2];
	msg->Header.Length = 0;
    MsSend(KerTestTaskId[2], msg);

	MsSleep(RTK_MS_TO_TICK(3000));
	MsDeleteTask(KerTestTaskId[0]);
	MsDeleteTask(KerTestTaskId[1]);
	MsDeleteTask(KerTestTaskId[2]);

    ven_std_sprintf((char*)KerTestOutput, "2nd count %d - %d - %d",countqueue[0],countqueue[1],countqueue[2]);
	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);
}
#endif

Ms_Mutex_t mutexA;
Ms_Mutex_t mutexB;

void testMutex(vm_msg_t* arg)
{
    UartSendTrace("lock mutexB\n");
    MsMutexLock(&mutexB);
    UartSendTrace("lock mutexA\n");
    MsMutexLock(&mutexA);
    UartSendTrace("unlock mutexB\n");
    MsMutexUnlock(&mutexB);
   // UartSendTrace("lock mutexC\n");
    //MsMutexLock(&mutexC);
    UartSendTrace("lock mutexB\n");
    MsMutexLock(&mutexB);
    UartSendTrace("unlock mutexA\n");
    MsMutexUnlock(&mutexA);
    UartSendTrace("unlock mutexB\n");
    MsMutexUnlock(&mutexB);
    UartSendTrace("testMutex return\n");
}

static void _test_OS_mutex(void)
{
    Msg_t *msg = NULL;
	MsInitMutex(&mutexA);
    MsInitMutex(&mutexB);

	KerTestTaskArgs[0].AppliInit = TestTsScheduleTaskInit;
	KerTestTaskArgs[0].AppliParser = testMutex;
	KerTestTaskArgs[0].StackSize = KERNEL_TEST_GENERAL_STACK_SIZE;
	KerTestTaskArgs[0].pStackTop = (u32*)MsAllocateMem(KerTestTaskArgs[0].StackSize);
	strcpy(KerTestTaskArgs[0].TaskName, "task0");
	KerTestTaskArgs[0].Priority = 30;
    KerTestTaskArgs[0].TaskId = &KerTestTaskId[0];

	MsCreateTask(&KerTestTaskArgs[0]);
	MsStartTask(KerTestTaskId[0]);

    msg = (Msg_t*)MsAllocateMem(sizeof(Header_t));
	msg->Header.TypMsg = KERNEL_TEST_MSG0;
	msg->Header.MbxSrc = CUS14_MBX;
	msg->Header.MbxDst = KerTestTaskId[0];
	msg->Header.Length = 0;
    MsSend(KerTestTaskId[0], msg);

	MsSleep(RTK_MS_TO_TICK(3000));

	MsDeleteTask(KerTestTaskId[0]);


	MsReleaseMemory(KerTestTaskArgs[0].pStackTop);



	VEN_TEST_PRINT_INFO_LINE(KerTestOutput);

}