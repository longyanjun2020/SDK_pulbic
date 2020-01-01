//
// create by msz paul.liu
//
#ifndef __MMI_CLSRV_CUS_H__
#define __MMI_CLSRV_CUS_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"

#ifndef CL_ZONEID_UNKNOW
#define CL_ZONEID_UNKNOW 	0
#endif

//#define NUMERIC_NUM 	10     //only 0...9
#define CL_MAX_SEGMENT_LEN 	7
#define CL_MAX_LEVEL_NUM 	8

//---------------------------------------------------------------------------
typedef struct CL_SEGMENT_MASK_TAG
{
	u32  maskcount;
	u16  *maskcodes;
}CL_SEGMENT_MASK;
//---------------------------------------------------------------------------
// 最近查询到的号段缓存起来，每次查询时先查这个表，提高速度
#define CL_LATEST_MAX 20
// Segment length only support CL_MAX_SEGMENT_LEN
typedef struct CL_LATEST_RECORD_TAG
{
	u8 	segment[CL_MAX_SEGMENT_LEN];
	u16	zonecode;
}CL_LATEST_RECORD;

//---------------------------------------------------------------------------
#ifndef __STATIC_CALLER_LOCATION__
#define CL_FILE_MARK_STR  {'s','e','g',0x01}
#define CL_FILE_NAME    L"fs:/CARD/uxCL_0086.seg"
#endif //__STATIC_CALLER_LOCATION__
//---------------------------------------------------------------------------
#define CL_MAX_PREFIX_LEN 	11    // 最大的前缀长度+1
#define CL_MAX_PREFIX_NUM 	40    // 最大的前缀数
//---------------------------------------------------------------------------
typedef struct CL_PREFIX_TAG
{
	s8 prefix[CL_MAX_PREFIX_LEN];
	u8 length;
}CL_PREFIX;
//---------------------------------------------------------------------------
typedef struct CL_LEVEL_DATA_TAG
{
	u32 offset;
	u32 maskcount;
}CL_LEVEL_DATA;
//---------------------------------------------------------------------------
typedef struct CL_FILE_HEAD_TAG
{
	u8  mark[4];
	CL_LEVEL_DATA level[CL_MAX_LEVEL_NUM];
	u8  unused[60];
	CL_PREFIX prefix[CL_MAX_PREFIX_NUM];
	u8  unused2[32];
}CL_FILE_HEAD;

#ifndef MEMCMP
#define MEMCMP(s,t,n) memcmp(s,t,n)
#endif


////////////////////////////////////
#endif
