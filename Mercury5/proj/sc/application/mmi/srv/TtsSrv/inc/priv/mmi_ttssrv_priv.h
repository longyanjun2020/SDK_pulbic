/**
* @file mmi_ttssrv_priv.h
*
* Service without using State Machine - TTSSRV
*
* Class Id: CLSID_TTSSRV
* Interface Id: IID_TTSSRV
*
*/
#ifndef __MMI_TTSSRV_PRIV_H__
#define __MMI_TTSSRV_PRIV_H__

#ifndef __TTS_UT_STANDALONE__
#include "mmi_cfgsrv.h"
#endif/* __TTS_UT_STANDALONE__ */

#include "mmi_mae_common_def.h"
#include "mmi_ttssrvstgr.h"
#include "mmi_ttssrv.h"
#include "StateMachineItf.h"
#include "SockMgrDSPortItf.h"

typedef enum
{
    TTSSRV_Status_Uninit = 0X00,
	TTSSRV_Status_Initing,
	TTSSRV_Status_Init,
	TTSSRV_Status_Uniniting,
    TTSSRV_Status_Num,
}TTSSrvStatus_e;

typedef struct TTSHandle_TAG
{
	void *pvSrv;
	void *pvOwner;
	u32	uInstanceID;
	bool bResumable;
	u16 *pUcs2;
	u16 uLen;
	boolean bAutoRelease;
    boolean bStopping;
	TTSSrvAttr_t sAttrs;
	TTSStatusUpdateCB pfnTtsUpdateCb;
	TTSSRV_HANDLESTATUS_e eStatus;
	TTSSRV_VOLUMESETTING_e eVolume;
	StateMachineHandle_t hStateMachine;
}TTSHandle_t;

/**
 * Application structure
 */
typedef struct MMI_TTSSRV_TAG
{
    DECLARE_FUNCTBL(ITTSSRV);   /// function table pointer
    u32 refCnt;                 /// reference count
#ifndef __TTS_UT_STANDALONE__
	ICFGSrv *pCfgSrv;           /// Hold the instance of Setting
#endif/* __TTS_UT_STANDALONE__ */
	u32 uLockCnt;
	TTSSrvStatus_e eCurStatus;
	TtsSrvStgrHdl_t hTtsSrvStgr;
	SockMgr_CtnrHdl_t hCtnrExec;
} MMI_TTSSRV;

typedef struct
{
    void *pvOwner;
    void *pvSrv;
    u32 uInstanceID;
    TTSLockCB pfnLockCb;
}TTSSrvAsyncData_t;

void TTS_Init(void);

#endif/* __MMI_TTSSRV_PRIV_H__ */
