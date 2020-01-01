#ifndef __MMI_FMR_MSGDEF_H__
#define __MMI_FMR_MSGDEF_H__

#include "ABL_Aud.h"
#include "ABL_Fmr.h"


typedef struct 
{
	ABL_FmrErrCode_e errCode;
    
	union {
        ABL_FmrChanInfo_t fmrChanInfo;

	} msgInfo;
    
} FMRMsgBody_t ;


typedef struct 
{
	MediaRspId_e	eTransRspId;
} FMRResMgrMsgBody_t;


#endif

