#ifndef _BEE_SCH_H_
#define _BEE_SCH_H_

#ifdef __CRASH_NOTIFY_SMS__

#include "sys_bee.hi"

typedef enum BeeListAddMode_e
{
	BEE_LIST_ADD_MODE_NEW,
	BEE_LIST_ADD_MODE_MOVE,
	BEE_LIST_ADD_MODE_NUM
}BeeListAddMode_et;


ReqItem_st *bee_SchGetFirstReq(BeeStateType_et eBeeStateType);
ReqItem_st *bee_SchGetNextReq(BeeStateType_et eBeeStateType, ReqItem_st *psReqItem);

bool bee_SchIsSameTypeReqExec(BeeApId_et eApId);
u32 bee_SchGetFirstSameTypeReq(BeeStateType_et eBeeStateType, BeeApId_et eApId);
void bee_SchDelSameTypeReq(BeeStateType_et eBeeStateType, BeeApId_et eApId);

void bee_SchSleepReq(u32 u32SeqId);
void bee_SchWakeupReq(u32 u32SeqId);
bool bee_SchChgState(BeeStateType_et eBeeSrcStateType, BeeStateType_et eBeeDstStateType, u32 u32SeqId);

u32 bee_AddReq(BeeStateType_et eBeeStateType, ReqItem_st *psReqItem, BeeListAddMode_et eMode);
void bee_DelReq(BeeStateType_et eBeeStateType, u32 u32SeqId);
bool bee_MovReq(BeeStateType_et eBeeSrcStateType, BeeStateType_et eBeeDstStateType, u32 u32SeqId);
ReqItem_st *bee_RmvReq(BeeStateType_et eBeeStateType, u32 u32SeqId);

u32	bee_GenSeqId(void);

#ifdef __CRASH_NOTIFY_SMS_TEST_CASE__
void bee_TestCase1(void);

#endif

#define BEE_MAX_RETRY_TIMES		20
#define BEE_NO_SEQ_ID			0xFFFFFFFF
#define BEE_SCORE_BOARD_MAX_NUM	0xFF

#endif
#endif
