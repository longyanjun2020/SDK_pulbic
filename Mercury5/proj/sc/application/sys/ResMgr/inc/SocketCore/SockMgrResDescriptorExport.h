#if !defined(_SOCKMGR_RESDESCRIPTOR_EXPORT_H_)
#    define  _SOCKMGR_RESDESCRIPTOR_EXPORT_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrResExport.h"
#include "SockMgrResCtrlExport.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef struct
{
	u16           uOwnerNum     ;
	u16           uOwnerSize    ;
	OwnerCopyCB   cbOwnerCopy   ;
	OwnerClearCB  cbOwnerClear  ;
	OwnerCmpCB    cbIsOwnerEqual;
}SockMgr_ResDescriptr_t;

typedef struct
{
	SockMgr_ResDescriptr_t *psSlotOwnerDescriptor ;
	void *pvSlotInitData ;
}SockMgr_SlotDescriptor_t;

typedef struct
{
	SockMgr_DataLink_e eDataLinkType ;
	SockMgr_ResDescriptr_t *psDataLinkOwnerDescriptor ;
	u16 uMaxSlotNum ;
	SockMgr_SlotDescriptor_t *psSlotDescriptorTable ;
	void *pvDataLinkInitData ;
}SockMgr_DataLinkDescriptor_t;

typedef struct
{
	SockMgr_ComMedia_e      eComMediaID ;
	SockMgr_ResDescriptr_t *psComMediaOwnerDescriptor ;
	void *pvComMediaInitData ;
}SockMgr_ComMediaDescriptor_t;

typedef struct
{
	SockMgr_ComMedia_e      eBearerID ;
	SockMgr_ResDescriptr_t *psBearerOwnerDescriptor ;
	u16 uMaxDataLinkNum ;
	SockMgr_DataLinkDescriptor_t *psDataLinkDescriptorTable ;
	void *pvBearerInitData ;
}SockMgr_BearerDescriptor_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif/* _SOCKMGR_RESDESCRIPTOR_EXPORT_H_ */
