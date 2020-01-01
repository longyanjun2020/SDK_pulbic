#ifndef __MMI_ATV_MSGDEF_H__
#define __MMI_ATV_MSGDEF_H__

#include "esl_tv_itf.h"

typedef struct
{
	MAERet_t				RspCode;
	u16						*pData;
	u32						UserData;
	u32						totalChn;
	esl_TvSignalLv_e		singalLv;
	u32						ch;
	bool					isExist;
    bool                    colorLock;
    u16                     tfCode;
    u16                     totalGain;
    esl_TvInfo_t            tTvInfo;
} AtvMsgBody_t;

#endif
