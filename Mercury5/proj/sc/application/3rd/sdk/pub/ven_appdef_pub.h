/**
 *
 * @file    ven_appdef.h
 * @brief
 *
 * @author
 * @version $Id$
 *
 */

/*===== Do not modify anything below this line =====*/
#ifdef DECLARE_VEN_APP_TABLE
#undef DECLARE_VEN_APP_TABLE
#endif

#ifdef MAKE_VEN_APP_ITEM
#undef MAKE_VEN_APP_ITEM
#endif

#ifdef MAKE_VEN_APP_ITEM_BEGIN
#undef MAKE_VEN_APP_ITEM_BEGIN
#endif

#ifdef MAKE_VEN_APP_ITEM_END
#undef MAKE_VEN_APP_ITEM_END
#endif

#ifdef DECLARE_VEN_APP_INIT_FUNC
#undef DECLARE_VEN_APP_INIT_FUNC
#endif

#ifdef DECLARE_VEN_APP_NEW_FUNC
#undef DECLARE_VEN_APP_NEW_FUNC
#endif

#ifdef DECLARE_VEN_TASK_STACK
#undef DECLARE_VEN_TASK_STACK
#endif

#ifdef DECLARE_VEN_NAME
#undef DECLARE_VEN_NAME
#endif

#if defined(__DECLARE_VEN_APP_TABLE__)

// Macro for Vendor Application
#define DECLARE_VEN_APP_TABLE(_name) \
    const VenAppTableItem_t _name##_AppTable[] =
#define MAKE_VEN_APP_ITEM_BEGIN(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    {{{_venID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask}, {_pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume}},
#define MAKE_VEN_APP_ITEM(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    {{_venID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask}, {_pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume}},
#define MAKE_VEN_APP_ITEM_END(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    {{_venID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask}, {_pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume}}};
#define DECLARE_VEN_APP_INIT_FUNC(_pfnInit)
#define DECLARE_VEN_APP_NEW_FUNC(_pfnNew)

#elif defined(__DECLARE_VEN_APP_FUNC__)

// Macro for Vendor Application
#define DECLARE_VEN_APP_TABLE(_name)
#define MAKE_VEN_APP_ITEM_BEGIN(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume)
#define MAKE_VEN_APP_ITEM(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume)
#define MAKE_VEN_APP_ITEM_END(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume)
#define DECLARE_VEN_APP_INIT_FUNC(_pfnInit) \
    extern void _pfnInit(void);
#define DECLARE_VEN_APP_NEW_FUNC(_pfnNew) \
    extern u32 _pfnNew(u16, void**);

#elif defined(__DECLARE_VEN_MMI_TABLE__)

// Macro for Vendor Application
#define DECLARE_VEN_APP_TABLE(_name) \
    const VenMmiTableItem_t _name##_MmiTable[] =
#define MAKE_VEN_APP_ITEM_BEGIN(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    {{_mmiID, _mnuStyle, _clsID, _mmiID##_MmiName},
#define MAKE_VEN_APP_ITEM(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    {_mmiID, _mnuStyle, _clsID, _mmiID##_MmiName},
#define MAKE_VEN_APP_ITEM_END(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    {_mmiID, _mnuStyle, _clsID, _mmiID##_MmiName}};
#define DECLARE_VEN_APP_INIT_FUNC(_pfnInit)
#define DECLARE_VEN_APP_NEW_FUNC(_pfnNew)

#elif defined(__ENUM_VEN_MMI_ID__)

// Macro for Vendor Application
#define DECLARE_VEN_APP_TABLE(_name) \
    extern const VenMmiTableItem_t _name##_MmiTable[]; \
    enum
#define MAKE_VEN_APP_ITEM_BEGIN(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    {_mmiID,
#define MAKE_VEN_APP_ITEM(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    _mmiID,
#define MAKE_VEN_APP_ITEM_END(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    _mmiID};
#define DECLARE_VEN_APP_INIT_FUNC(_pfnInit)
#define DECLARE_VEN_APP_NEW_FUNC(_pfnNew)

#elif defined(__ENUM_VEN_APP_ID__)

// Macro for Vendor Application
#define DECLARE_VEN_APP_TABLE(_name) \
    extern const VenAppTableItem_t _name##_AppTable[]; \
    enum
#define MAKE_VEN_APP_ITEM_BEGIN(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    {_venID,
#define MAKE_VEN_APP_ITEM(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    _venID,
#define MAKE_VEN_APP_ITEM_END(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume) \
    _venID};
#define DECLARE_VEN_APP_INIT_FUNC(_pfnInit)
#define DECLARE_VEN_APP_NEW_FUNC(_pfnNew)

#else

// Macro for Vendor Application
#define DECLARE_VEN_APP_TABLE(_name)
#define MAKE_VEN_APP_ITEM_BEGIN(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume)
#define MAKE_VEN_APP_ITEM(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume)
#define MAKE_VEN_APP_ITEM_END(_venID, _mmiID, _mnuStyle, _clsID, _task, _cpuSpeed, _intLevel, _dbgGroup, _bUseSDKTask, _pfnInit, _pfnStart, _pfnStop, _pfnSuspend, _pfnResume)
#define DECLARE_VEN_APP_INIT_FUNC(_pfnInit)
#define DECLARE_VEN_APP_NEW_FUNC(_pfnNew)

#endif

#ifdef __DECLARE_VEN_TASK_TABLE__
// Macro for Vendor task stack
#define DECLARE_VEN_TASK_STACK(_venTaskID, _cusStackSize) u32 _venTaskID##_Stack[_cusStackSize / 4];
#else
#define DECLARE_VEN_TASK_STACK(_venTaskID, _cusStackSize)
#endif // __DECLARE_VEN_TASK_TABLE__


#ifdef __DECLARE_VEN_MMI_TABLE__
// Macro for Vendor Name
#define DECLARE_VEN_NAME(_mmiID, _pEnglishName, _pSChineseName, _pTChineseName) \
    static const u16 *_mmiID##_MmiName[] = {_pEnglishName, _pSChineseName, _pTChineseName};
#else
#define DECLARE_VEN_NAME(_mmiID, _pEnglishName, _pSChineseName, _pTChineseName)
#endif // __DECLARE_VEN_MMI_TABLE__

/*===== Do not modify anything above this line =====*/


