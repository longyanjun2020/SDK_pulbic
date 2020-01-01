/**
 * @file mmi_mae_rightsdb.h
 * @brief   The document describes the interface of IRightsDB
 * IEventDB represent event record(s) in calendar application.
 *
 * @author
 * @version $Id: mmi_mae_rightsdb.h  $
 */
#ifndef __MMI_MAE_RIGHTSDB_H__
#define __MMI_MAE_RIGHTSDB_H__
/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_vectormodel.h"
#include "mmi_mae_arraymodel.h"
#include "mmi_base_util.h"
#include "mdl_vfs_struct.h"
/*-------------------------------------------------------------------------*/

#define RO_KEY_LEN         16   //in bytes
#define RO_FILENAME_LEN    VFS_FAT_SPEC_FULLNAME_LEN   //13 for 8.3 filename, 256 for log filename

typedef enum DrmMethod_e_
{
	DRM_METHOD_FL = 0,
	DRM_METHOD_CD,
	DRM_METHOD_SD,
} DrmMethod_e;

typedef enum DrmAction_e_
{
    DRM_ACTION_NONE = 0,
    DRM_ACTION_PLAY = (0x0001),
	DRM_ACTION_DISPLAY = (0x0001<<1),
	DRM_ACTION_EXECUTE = (0x0001<<2),
	DRM_ACTION_PRINT = (0x0001<<3),
	DRM_ACTION_UNLIMITED = 0xFFFF, //for FL case
} DrmAction_e;


enum
{
    DRM_PLAY_ACTION_IDX = 0,
	DRM_DISPLAY_ACTION_IDX,
	DRM_EXECUTE_ACTION_IDX,
	DRM_PRINT_ACTION_IDX,
    DRM_ACT_NUM
};



typedef struct
{
    u32 nCount;
    u32 nUsedCount;
}DrmCount_t;

typedef struct
{
    MAE_DateTime_t tStart;
    MAE_DateTime_t tEnd;
    boolean bValid;
    boolean bStartTimeValid;
    boolean bEndTimeValid;
}DrmDateTime_t;

typedef struct
{
    MAE_DateTime_t tInterval;
    MAE_DateTime_t tStart;
    MAE_DateTime_t tEnd;
    boolean bValid;
    boolean bUsed;
}DrmInterval_t;

typedef struct DrmActionRights_t_
{
	DrmInterval_t   tInterval;
	DrmDateTime_t   tDataTime;
    DrmCount_t      tCount;
    boolean         bNoConstrainted;
} DrmActionRights_t;

typedef struct HashKey_t_
{
	u32     nUID;				        /* unique ID for hash mapping */
    u32     nHash;                      /* hash index */
    u32     nCrc;                       /* check sum of Content UID (to save RAI space) */
} HashKey_t;

typedef struct RightsLink_t_
{
    u16 nIndex;
    u16 nPrevUID;                         /* index to prev rights */
    u16 nNextUID;                         /* index to next rights */
} RightsLink_t;

typedef struct DrmRightsObject_t_
{
	u32                 nUID;				        /* unique ID for this rights Object */
    u32                 nHash;                      /* hash index */
    u32                 nCrc;                       /* check sum of Content UID */
    float               fVersion;                   /* rights verison */
    u8                  *pKey;                      /* encryption/decryption key */
    MAE_WChar           *pFilename;                 /* content file name */
    DrmAction_e         eAction;                    /* available actions */
    DrmActionRights_t   tRights[DRM_ACT_NUM];       /* rights for all action */
    RightsLink_t        tLink;                      /* point to next/prev index */
} DrmRightsObject_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define RIGHTSDB_RO_NUID_SIZE							(sizeof(u32))
#define RIGHTSDB_RO_NHASH_SIZE					        (sizeof(u32))
#define RIGHTSDB_RO_NCRC_SIZE						    (sizeof(u32))
#define RIGHTSDB_RO_FVERSION_SIZE					    (sizeof(float))
#define RIGHTSDB_RO_KEY_SIZE						    (sizeof(u8) * RO_KEY_LEN)
#define RIGHTSDB_RO_FILENAME_SIZE					    (sizeof(MAE_WChar) * RO_FILENAME_LEN)
#define RIGHTSDB_RO_ACTION_MASK_SIZE					(sizeof(DrmAction_e))
#define RIGHTSDB_RO_ACTION_RIGHTS_SIZE			        (sizeof(DrmActionRights_t) * DRM_ACT_NUM)
#define RIGHTSDB_RO_LINK_SIZE			                (sizeof(RightsLink_t))

#define RIGHTSDB_RO_COLUMN_NUM							(9)

#define RIGHTSDB_RO_RECORD_SIZE		\
	(   RIGHTSDB_RO_NUID_SIZE+RIGHTSDB_RO_NHASH_SIZE+RIGHTSDB_RO_NCRC_SIZE+\
        RIGHTSDB_RO_FVERSION_SIZE+RIGHTSDB_RO_KEY_SIZE+RIGHTSDB_RO_FILENAME_SIZE+\
        RIGHTSDB_RO_ACTION_MASK_SIZE+RIGHTSDB_RO_ACTION_RIGHTS_SIZE+\
	    RIGHTSDB_RO_LINK_SIZE   )
/////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    MAE_RIGHTSDB_MASK_INSERTED = 0x01,
    MAE_RIGHTSDB_MASK_UPDATED = 0x02,
    MAE_RIGHTSDB_MASK_DELETED = 0x04,
    MAE_RIGHTSDB_MASK_ALL = (s32)0xFFFFFFFF
} MAE_RightsDB_Notify_e;



#define INHERIT_IRightsDB(IName) \
	INHERIT_IBase(IName); \
    MAE_Ret (*InstallRights)				(IName* IRightsDB, u8* pCid, DrmRightsObject_t* pRightsObject);\
    MAE_Ret (*GetRights)				    (IName* IRightsDB, u8* pCid, DrmRightsObject_t** ppRightsObject);\
	MAE_Ret (*GetRightsByUID)               (IName* IRightsDB, u32 nUID, DrmRightsObject_t **ppOutRightsObject);\
    MAE_Ret (*GetRightsUIDList)             (IName* IRightsDB, ArrayClass_t** ppArray, IBase* pOwner);\
    MAE_Ret (*GetRightsLink)                (IName* IRightsDB, HashKey_t* pHashKey, ArrayClass_t** ppArray, IBase* pOwner);\
    MAE_Ret (*DeleteRightsByUID)	        (IName* IRightsDB,  u32 nUID);\
	MAE_Ret (*DeleteAll)	                (IName* IRightsDB);\
	MAE_Ret (*SweepInvalidRights)           (IName* IRightsDB, u32 *pSweepCnt);\
	MAE_Ret (*UpdateRights)                 (IName* IRightsDB, DrmRightsObject_t *pRightsObject);\
    MAE_Ret (*GetUsageInfo)                 (IName* IRightsDB, u16 *pSize, u16 *pUsedNum)
DEFINE_INTERFACE(IRightsDB);

#define IRightsDB_AddRef(p)					    GET_FUNCTBL(p, IRightsDB)->AddRef(p)
#define IRightsDB_Release(p)				    GET_FUNCTBL(p, IRightsDB)->Release(p)
#define IRightsDB_QueryInterface(p,s,t)		    GET_FUNCTBL(p, IRightsDB)->QueryInterface(p,s,t)

#define IRightsDB_InstallRights(p,s,t)			GET_FUNCTBL(p, IRightsDB)->InstallRights(p,s,t)
#define IRightsDB_GetRights(p,s,t)			    GET_FUNCTBL(p, IRightsDB)->GetRights(p,s,t)
#define IRightsDB_GetRightsByUID(p,s,t)			GET_FUNCTBL(p, IRightsDB)->GetRightsByUID(p,s,t)
#define IRightsDB_GetRightsUIDList(p,s,t)	    GET_FUNCTBL(p, IRightsDB)->GetRightsUIDList(p,s,t)
#define IRightsDB_GetRightsLink(p,s,t,u)	    GET_FUNCTBL(p, IRightsDB)->GetRightsLink(p,s,t,u)

#define IRightsDB_DeleteRightsByUID(p,s)		GET_FUNCTBL(p, IRightsDB)->DeleteRightsByUID(p,s)
#define IRightsDB_DeleteAll(p)	                GET_FUNCTBL(p, IRightsDB)->DeleteAll(p)
#define IRightsDB_SweepInvalidRights(p,s)       GET_FUNCTBL(p, IRightsDB)->SweepInvalidRights(p,s)
#define IRightsDB_UpdateRights(p,s)             GET_FUNCTBL(p, IRightsDB)->UpdateRights(p,s)
#define IRightsDB_GetUsageInfo(p,s,t)           GET_FUNCTBL(p, IRightsDB)->GetUsageInfo(p,s,t)


void freeif_rightsobject(DrmRightsObject_t **ppRightsObject);

#ifndef FREEIF_RIGHTSOBJECT
    #define FREEIF_RIGHTSOBJECT(ptr) freeif_rightsobject(&(ptr))
#endif



void MAE_RightsDB_Init(void);

MAE_Ret MAERightsDB_New(MAE_ClsId nClsID, void **ppObj);

#endif /* __MAE_EVENTDB_H__ */


