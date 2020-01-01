/**
* @file mmi_videotelephonyapp.h
*
* Class Id: CLSID_VIDEOTELEPHONYAPP
*
*/
#ifndef __MMI_VIDEOTELEPHONYAPP_H__
#define __MMI_VIDEOTELEPHONYAPP_H__

#include "mmi_mae_common_def.h"
#include "mmi_ccsrv_def.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_cc.h"

#include "mmi_vtccsrv_def.h"

typedef struct
{
	boolean	bDisable;					/* Set TRUE if other AP already decide Master or Slave*/
	u8			u8SessDualId;			/* Set DUAL_MASTER/DUAL_SLAVE if bDisable is TRUE*/
} MmiVideoTelephonyAppDuoOption_t;

typedef struct
{
	MMI_VTCC_AP_FID_E	s32CCAppFid;
	u8	CallNumber[VTCCSRV_MAX_CALL_NUMBER+1];
	MAE_WChar	CallName[VTCCSRV_MAX_CALL_NAME+1];
	u32	u32ImageID;
	u32 u32RingtoneID;
	MmiVideoTelephonyAppDuoOption_t	tDuoOption;
	boolean bSTKMakeCall;		// STK will request: Release call existed calls first, them make STK call
} MmiVideoTelephonyAppMakeCallReq_t;

typedef struct
{
	MMI_VTCC_AP_FID_E	s32CCAppFid;
	u8	u8SessDualId;
	boolean	bAnswerByBT;

} MmiVideoTelephonyAppIncomingCallInd_t;

/**
 * Functions
 */

MAE_Ret VideoTelephonyApp_New(MAE_ClsId id, void **ppObj);
void VideoTelephonyAppFreeMakeCallReqData(IBase *pIssuer, u32 nParam);
void VideoTelephonyAppFreeIncomingCallIndData(IBase *pIssuer, u32 nParam);


#endif /* __MMI_VIDEOTELEPHONYAPP_H__ */
