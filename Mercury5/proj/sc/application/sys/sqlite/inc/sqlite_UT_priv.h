#include "sqlite_porting.h"
#include "sqlite3_priv.h"
#include "sqlite_UT.h"

typedef int s32;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned int u32;

#ifdef __STANDALONE__
#undef ASSERT
#include <assert.h>
#define ASSERT(_e_) {assert(_e_);}

#else //__STANDALONE__

#define printf(...)

#ifdef __SDK_SIMULATION__
#include <assert.h>
#define ASSERT(_e_) {assert(_e_);}

#else //__SDK_SIMULATION__

#define ASSERT(_e_) {\
    if(!(_e_)) \
{ \
    extern void ker_assert_func(u8 * str, u8 * file, u32 line); \
    ker_assert_func( #_e_, __FILE__, __LINE__); \
} \
}

#endif //__SDK_SIMULATION__

#endif //__STANDALONE__

#if SQLITE_OS_WIN
#include <iostream>
#include <fstream>
#include <stdio.h>
#else //SQLITE_OS_WIN
#ifdef __STANDALONE__

#include <stdio.h>

extern "C" {
    extern s32 fat_N_delete(u16 * fileName);
}

#define NULL 0

#else //__STANDALONE__
#include "vfs_file.ho"
#include "vfs_fat.ho"
#include "sys_MsWrapper_cus_os_util.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_timer.h"
#include "sys_rtk_vmoshi.h"
#include "string.h"

typedef union
{
    vm_osTimerMsgBody_t SQLiteTimerMsg;
} vm_msgBody_t;

#include "vm_msgt.ht"
typedef u16 wchar_t;
#endif //__STANDALONE__
#endif //SQLITE_OS_WIN

typedef void (*SQLiteUtFunc)();

typedef struct
{
    SQLiteUtFunc  getFunc;
} SQLite_UT_Table_t;

void SysSqlite_InitUTEnvironment(void);
void SysSqlite_UnInitUTEnvironment(void);
void SysSqlite_BasicTestChineseDBName(void);
void SysSqlite_BasicTestEnglishDBName(void);
void SysSqlite_BasicTest_NormalOperation(void);
void SysSqlite_BasicTest_CountOperation(void);
void SysSqlite_BasicTest_DistinctOperation(void);
void SysSqlite_BasicTest_NULLTest(void);
void SysSqlite_BasicTest_BindTest(void);
void SysSqlite_BasicTest_BindValueTest(void);
void SysSqlite_BasicTest_sqlite3_sqlTest(void);
void SysSqlite_BasicTest_sqlite3_stmt_readonlyTest(void);
void SysSqlite_BasicTest_sqlite3_data_countTest(void);
void SysSqlite_BasicTest_sqlite3_create_functionTest(void);
void SysSqlite_BasicTest_TruncateTable(void);
void SysSqlite_BasicTest_OffLineTest(void);
void SysSqlite_BasicTest_MemoryOperation(void);
void SysSqlite_BasicTest_ColOperation(void);
void SysSqlite_StressTest_Insert1000Normal(void);
void SysSqlite_StressTest_Insert1000WithoutTable(void);
void SysSqlite_StressTest_Insert1000AfterCloseDB(void);

