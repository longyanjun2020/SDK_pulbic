#ifndef __MMI_COMMON_CC_TYPE_H__
#define __MMI_COMMON_CC_TYPE_H__

#include "mmi_mae_common_def.h"
#include "mmi_ccsrv_def.h" //for MMI_CC_AP_FID_E
/*
 * Data type defintion of CCApp that is required by other libraries
 * */

typedef struct
{
	boolean	bDisable;					/* Set TRUE if other AP already decide Master or Slave*/
	u8			u8SessDualId;			/* Set DUAL_MASTER/DUAL_SLAVE if bDisable is TRUE*/
} MmiCCAPPDuoOption_t;

typedef struct
{
	MMI_CC_AP_FID_E	s32CCAppFid;
	u8	CallNumber[CCSRV_MAX_CALL_NUMBER+1];
	MAE_WChar	CallName[CCSRV_MAX_CALL_NAME+1];
	u32	u32ImageID;
	u32 u32RingtoneID;
	MmiCCAPPDuoOption_t	tDuoOption;
	boolean bSTKMakeCall;		// STK will request: Release call existed calls first, them make STK call
} MmiCCAPPMakeCallReq_t;

typedef struct
{
	MMI_CC_AP_FID_E	s32CCAppFid;
	u8	u8SessDualId;
	u8	u8AnswerBy;
#ifdef __APP_MMI_ANSWERING_MACHINE__
	boolean bEnableAnsweringMachine;
	ANSWERING_MACHINE_FAILED_TYPE_e eAnsweringMachineFailedType;
#endif
} MmiCCAPPIncomingCallInd_t;

typedef struct
{
	MMI_CC_AP_FID_E	s32CCAppFid;
	u32 nCallID;
} MmiCCAPPEndSpecificCall_t;

#endif // __MMI_COMMON_CC_TYPE_H__
