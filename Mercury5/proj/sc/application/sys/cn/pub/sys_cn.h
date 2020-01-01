#ifndef _SYS_CN_H_
#define _SYS_CN_H_

#ifdef  __CRASH_NOTIFY_SMS__ 
#include "vm_e2p_stack.ho"

#define CN_FIELD_PRODUCT_NAME_LEN				5
#define CN_FIELD_REVISION_LEN					6
#define CN_FIELD_POOL_LEN						5
#define CN_FORMAT_STR_LEN						21
#define CN_CUS_TASK_NUM							3
#define CN_ACT_TASK_STACK_DEPTH					10
#define CN_CUS_TASK_STACK_DEPTH					10					
#define CN_REGISTER_INFO_NUM					13
#define CN_FORMAT_STRING_LEN					100
#ifndef __RTK_DIAGNOSE_ENHANCE__
#define CN_MSG_LEN								140
#else
#define CN_MSG_LEN								152
#endif

#define CN_BACKTRACE_STACK_TO_STORE				256

#define CN_FLEXIBLE_FLDS_NUM					7

#define CN_MAX_PARAM_NUM						10

#define CN_IDENT_ACT_TASK						0xD0
#define CN_IDENT_CUS_1_TASK						0xD1
#define CN_IDENT_CUS_2_TASK						0xD2
#define CN_IDENT_CUS_3_TASK						0xD3
#define CN_IDENT_POOL							0xD4
#define CN_IDENT_REGISTERS						0xD5
//1 + 1 + CN_FIELD_PRODUCT_NAME_LEN + CN_FIELD_REVISION_LEN + (sizeof(vm_Imei_t) - 1) + Ident(4)
#define CN_MIN_ESSENTIAL_INFO_LEN				25


typedef enum cnUseSetting_e{
	CN_FLDS_USE_ABORT_NO_POOL
	,CN_FLDS_USE_ABORT_POOL
	,CN_FLDS_USE_ASSERT_NO_POOL
	,CN_FLDS_USE_ASSERT_POOL
	,CN_FLDS_USE_SET_NUM
}cnUseSetting_et;

typedef struct cnBackTraceAuxBuf_s{
	u8			au8Product[CN_FIELD_PRODUCT_NAME_LEN + 1];
	u8			au8Rev[CN_FIELD_REVISION_LEN + 1];
	vm_Imei_t	imei;
	u8			au8FormatStr[CN_FORMAT_STRING_LEN + 1];
	u32			au32Params[CN_MAX_PARAM_NUM + 1];
	u32			au32Registers[CN_REGISTER_INFO_NUM];
	u32			au32ActTaskStack[CN_ACT_TASK_STACK_DEPTH];
	u32			au32Cus1TaskStack[CN_CUS_TASK_STACK_DEPTH];
	u32			au32Cus2TaskStack[CN_CUS_TASK_STACK_DEPTH];
	u32			au32Cus3TaskStack[CN_CUS_TASK_STACK_DEPTH];
	u8			u8ExhaustedPoolID;
	u32			u32Caller;
	bool		bIsAbort;
}cnBackTraceAuxBuf_st;

typedef bool (*cn_SmsCheckCond_pf_t)(void);
typedef void (*cn_SendCrashNotifyCnf_pf_t)(bool bResult);
typedef bool (*cn_SmsSubmitReq_pf_t)(void *pvData, u16 u16DataLen);

typedef struct SmsRegFunc_s{
	cn_SmsCheckCond_pf_t				pfnSmsCheckCond;
	cn_SendCrashNotifyCnf_pf_t			pfnSendCrashNotifyCnf;
	cn_SmsSubmitReq_pf_t				pfnSmsSubmitReq;
}SmsRegFunc_st;

typedef struct
{
	u8  info[140];
	u16	u16InfoLen;
} vm_CrashNotify_Ind_t;

void cn_CrashInd(void *pvData, u16 u16DataLen);
void cn_SMSInit(SmsRegFunc_st *psRegFunc);
void cn_SendCrashNotifyReq(void);
void cn_Decode(u8 *puSrc, u16 u16SrcLen, u8 *puDstBuf, u16 u16DstBufSize);
void cn_SmsSubmitCnf(bool bSuccess);
void cn_Encode(u8 *cnBackTrace);
u16 cn_CalcReportLen(u8 *puSrc, u16 u16SrcLen);

#endif
#endif
