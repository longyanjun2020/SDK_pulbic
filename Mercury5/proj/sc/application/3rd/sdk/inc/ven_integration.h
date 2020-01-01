/**
 *
 * @file    ven_integration.h
 * @brief
 *
 * @author
 * @version $Id$
 *
 */
#ifndef __VEN_INTEGRATION_H_
#define __VEN_INTEGRATION_H_

#include "ven_types.h"
#include "ven_std.h"

#define VEN_INTEGRATION

enum
{
    CPU_SPEED_LOW = FALSE,  ///< Let CPU be at low speed when executing vendor application
    CPU_SPEED_HIGH = TRUE,  ///< Let CPU be at high speed when executing vendor application
};
typedef u8 VenApp_CpuSpeedProfile_e;

enum
{
    MNU_STYLE_STATIC = FALSE,   ///< There is an existing menu entry for vendor application
    MNU_STYLE_DYNAMIC = TRUE,   ///< Vedor application would be listed in mainmenu -> applications -> more
};
typedef u8 VenApp_MenuEntryStyle_e;

enum
{
    VEN_TASK_1 = 0,
    VEN_TASK_2,
    VEN_TASK_3,
    VEN_TASK_4,
    VEN_TASK_5,
    VEN_TASK_6,
    VEN_TASK_NUM,
    VEN_TASK_INVALID,
};
typedef u8 VenApp_TaskId_e;

enum
{
    /* Priority > MMI task */
    /* VEN_TASK_PRIO_1 > VEN_TASK_PRIO_2 > VEN_TASK_PRIO_3 > VEN_TASK_PRIO_4 > VEN_TASK_PRIO_5 */
    VEN_TASK_PRIO_1 = 16,
    VEN_TASK_PRIO_2 = 15,
    VEN_TASK_PRIO_3 = 14,
    VEN_TASK_PRIO_4 = 13,
    VEN_TASK_PRIO_5 = 12,
    /* Priority < MMI task */
    /* VEN_TASK_PRIO_6 > VEN_TASK_PRIO_7 > VEN_TASK_PRIO_8 > VEN_TASK_PRIO_9 > VEN_TASK_PRIO_10 */
    VEN_TASK_PRIO_6 = 7,
    VEN_TASK_PRIO_7 = 6,
    VEN_TASK_PRIO_8 = 5,
    VEN_TASK_PRIO_9 = 3,
    VEN_TASK_PRIO_10 = 2
};
typedef u8 VenApp_TaskPriority_e;

typedef struct VenAppAttribute_Tag
{
    // SDK level
    u8 venId;
    // Task level attribute
    VenApp_TaskId_e task;                 ///< Vendor task
    VenApp_CpuSpeedProfile_e cpuSpeed;    ///< Vendor default CPU speed profile
    u8 intLevel;                          ///< Vendor interrupt level
    u32 dbgGroup;                         ///< Vendor debug trace group
    bool bUseSDKTask;                     ///< TRUE if vendor is arranged in SDK reserved tasks
} VenAppAttribute_t;

typedef void (*CUS_VEN_INIT_FUNC_PTR)(void);    ///< Pointer of vendor initialization function when vendor task is initialized

typedef bool (*CUS_VEN_STC_START_FUNC_PTR)(const VenAppAttribute_t*, void*, u32);
typedef bool (*CUS_VEN_STC_STOP_FUNC_PTR)(const VenAppAttribute_t*);
typedef bool (*CUS_VEN_STC_SUSPEND_FUNC_PTR)(const VenAppAttribute_t*);
typedef bool (*CUS_VEN_STC_RESUME_FUNC_PTR)(const VenAppAttribute_t*);
typedef bool (*CUS_VEN_STC_STATUS_IND_FUNC_PTR)(const VenAppAttribute_t*, u8, void*, u32);

typedef struct VenStcFnTbl_tag
{
    CUS_VEN_INIT_FUNC_PTR          pfnInit;
    CUS_VEN_STC_START_FUNC_PTR     pfnStart;
    CUS_VEN_STC_STOP_FUNC_PTR      pfnStop;
    CUS_VEN_STC_SUSPEND_FUNC_PTR   pfnSuspend;
    CUS_VEN_STC_RESUME_FUNC_PTR    pfnResume;
    CUS_VEN_STC_STATUS_IND_FUNC_PTR pfnStatusInd;
} VenAppFnTbl_t;

typedef struct VenAppTableItem_Tag
{
    const VenAppAttribute_t attribute;
    VenAppFnTbl_t fnTbl;
} VenAppTableItem_t;

typedef struct VenMmiTableItem_Tag
{
    u32 mmiApId;                          ///< Vendor MMI ID
    VenApp_MenuEntryStyle_e mnuStyle;     ///< Vendor menu entry style
    u16 clsId;                            ///< Vendor Class Id
    const u16 **ppName;                   ///< Pointer to pointer of vendor Name table
} VenMmiTableItem_t;

#define GET_VEN_APP_TABLE(_name, _pTable) _pTable = &_name##_AppTable[0]
#define GET_VEN_APP_ITEM(_name, _index, _pItem) _pItem = &_name##_AppTable[_index]
#define GET_VEN_MMI_TABLE(_name, _pTable) _pTable = &_name##_MmiTable[0]
#define GET_VEN_MMI_ITEM(_name, _index, _pItem) _pItem = &_name##_MmiTable[_index]
#define GET_VEN_MMI_NAME(_mmiID, _ppable) *_ppable = _mmiID##_MmiTable

#endif  /* __VEN_INTEGRATION_H_ */

