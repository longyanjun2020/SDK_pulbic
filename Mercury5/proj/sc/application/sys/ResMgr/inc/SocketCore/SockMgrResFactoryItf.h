#ifndef _SOCKMGR_RESFACTORY_ITF_H_ 
#define _SOCKMGR_RESFACTORY_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void *SockMgr_ResHdl_t ;
typedef void (*OwnerCopyCB)    (void *pvDest, void *pvSrc, u16 uSize) ;
typedef void (*OwnerClearCB)   (void *pvOwner, u16 uSize) ;
typedef bool (*OwnerCmpCB)     (void *pvCurOwner, void *pvOwner) ;

typedef enum
{
	E_SOCKMGR_RES_BEARER = 0,
	E_SOCKMGR_RES_DATALINK,
	E_SOCKMGR_RES_COMMEDIA,
	E_SOCKMGR_RES_SOCKET,
	E_SOCKMGR_RES_NUM,
}SockMgr_Res_e;

typedef struct
{
	SockMgr_Res_e  eResType  ;
	u16 uOwnerNum ;
}SockMgr_ResCreateData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_ResHdl_t SockMgr_ResFactory_Create(SockMgr_ResCreateData_t *psResCreateData);
void SockMgr_ResFactory_Destroy(SockMgr_ResHdl_t hRes, void *pvDestroyData);


#endif/* _SOCKMGR_RESFACTORY_ITF_H_ */
