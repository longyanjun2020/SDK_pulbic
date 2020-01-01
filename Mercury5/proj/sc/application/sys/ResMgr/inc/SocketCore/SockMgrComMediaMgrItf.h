#ifndef _SOCKMGR_COMMEDIAMGR_ITF_H_
#define _SOCKMGR_COMMEDIAMGR_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"
#include "SockMgrResItf.h"
#include "SockMgrResCtrlItf.h"
#include "SockMgrBearerMgrItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* SockMgr_ComMediaMgrHdl_t ;
typedef SockMgr_ResCtrl_TraverseResCB SockMgr_ComMedia_TraverseAllComMediaCB ;

typedef enum
{
	E_SOCKMGR_COMMEDIA_VML1 = 0,
	E_SOCKMGR_COMMEDIA_VML2,
#ifdef __VML_WIFI_COMMEDIA__
    E_SOCKMGR_COMMEDIA_VML_WIFI,
#endif/* __WLAN_IP_SUPPORT__ */
	E_SOCKMGR_COMMEDIA_SOCKMGR,
	E_SOCKMGR_COMMEDIA_NUM ,
}SockMgr_ComMedia_e;

typedef struct
{
	SockMgr_ResCtrl_InitData_t sResCtrl_InitData ;
}SockMgr_ComMediaMgr_InitData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_ComMediaMgrHdl_t SockMgr_ComMediaMgr_Init(SockMgr_ComMediaMgr_InitData_t *psComMediaMgrInitData) ;
void SockMgr_ComMediaMgr_UnInit(SockMgr_ComMediaMgrHdl_t hBearerMgr) ;
__SLDPM_FREE__ SockMgr_ComMediaHdl_t SockMgr_ComMediaMgr_GetComMedia(SockMgr_ComMediaMgrHdl_t hComMediaMgr, SockMgr_ComMedia_e eComMediaID) ;
bool SockMgr_ComMediaMgr_IsSupportBearer(SockMgr_ComMediaMgrHdl_t hComMediaMgr, SockMgr_ComMedia_e eComMediaID, SockMgr_Bearer_e eBearerID) ;
void SockMgr_ComMediaMgr_TraverseAllComMedia(SockMgr_ComMediaMgrHdl_t hComMediaMgr, SockMgr_ComMedia_TraverseAllComMediaCB cbTraverseAllComMedia, void *pvCusData) ;

#endif/* _SOCKMGR_COMMEDIAMGR_ITF_H_ */
