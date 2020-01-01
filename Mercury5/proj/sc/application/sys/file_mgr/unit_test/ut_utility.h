#ifndef __UT_UTILITY_H__
#define __UT_UTILITY_H__

#include "filemgr_data_types.h"

#if defined(FILE_MGR_STANDALONE_DEBUG)
#undef MALLOC
#undef FREE
#undef FREEIF

#undef SWPRINTF
#define SWPRINTF        swprintf
#define STRLEN          strlen

#define MALLOC(size)    malloc(size)
#define MEMSET(a,v,n)   memset(a,v,n)
#define MEMCPY          memcpy
#define MEMCMP          memcmp
#define MEMMOVE         memmove
#define FREE(p)         free(p)
#define FREEIF(p)       if (p != 0) {free((void*)p); p = 0;}

static u8 g_bEnableAssert = TRUE;
#define ASSERT          assert
#define GFM_ASSERT(a)      if(g_bEnableAssert) {\
							assert(a);\
							}



#define LOG_TRACE(_level_, _format_, ...)   Win32_Trace(_level_, "[TRACE] " _format_, ##__VA_ARGS__)
#define LOG_ERROR(_level_, _format_, ...)   Win32_Trace(_level_, "[ERROR] " _format_, ##__VA_ARGS__)
#define LOG_WARN(_level_, _format_, ...)    Win32_Trace(_level_, "[WARN] " _format_, ##__VA_ARGS__)
extern void Win32_Trace(u32 level, char *strFormat, ...);
#define FMGR_LEVEL      0
/*
typedef struct
{
    u8  year;			///< Year value after 1900, value range is 0~255
    u8  month;			///< Month, value range is 1~12
    u8  day;			///< Day, value range is 1~31
    u8  dayOfWeek;      ///< [1 = Monday, 7 = Sunday]
    u8  hour;			///< Hour, value range is 0~23
    u8  minute;			///< Minute, value range is 0~59
    u8  second;			///< Second, value range is 0~59
    u16 secondFracPart; ///< Fractionnal part of the second, not used now
}MAE_DateTime_t;	 ///<  This structure is identical to vm_rtcTimeFormat_t now
*/
#define MAE_JULIANDATE_START_YEAR   1900

u16 sysUtil_UCS2StringLength(const FileMgr_WChar* pStr);
void sysUtil_UCS2StringCopy(FileMgr_WChar* pDest, const FileMgr_WChar* pSource);
void sysUtil_UCS2StringNCopy(FileMgr_WChar* pDest, const FileMgr_WChar* pSource, size_t nCount);
u16 sysUtil_UCS2StringCat(FileMgr_WChar* pDest, const FileMgr_WChar* pSource);
u16 sysUtil_UCS2StringCmp(const FileMgr_WChar* pString1, const FileMgr_WChar* pString2);
s16 sysUtil_UCS2StringNCmp(const FileMgr_WChar* pString1, const FileMgr_WChar* pString2, size_t nCount);
FileMgr_WChar* sysUtil_UCS2StringDuplicate(const FileMgr_WChar *pStrSource);
u32 mmi_rtc_DateToSeconds(void *date);

u8 MsCurrTask(void);
u32 MsConsumeSem(u8 semID);
u32 MsProduceSem(u8 semID);
void MsInitSem(u8 semID, u8 nInitVal);

#define MsSend UT_FakeSend
void UT_FakeSend(u16 uDestId, void *pMsgBody);
typedef u32 MAE_Ret;
typedef unsigned int size_t;
typedef u16 MAE_WChar;
typedef u32 MAERet_t;


void CreateSemaphores();
void DestroySemaphores();

#endif

#endif //__UT_UTILITY_H__
