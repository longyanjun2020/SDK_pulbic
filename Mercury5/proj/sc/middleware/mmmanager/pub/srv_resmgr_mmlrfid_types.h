////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    srv_resmgr_mmlrfid_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLRFID_TYPES_H__
#define __SRV_RESMGR_MMLRFID_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerRfid
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseRfidId_e_)
{
    /* RFID Init */
    MML_UCID_RFID_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_RFID),
    /* targets (JS257)*/
    MML_UCID_RFID_Init  = MML_UCID_RFID_INIT_BASE,                          ///<  Init
    MML_UCID_RFID_INIT_CATEGORY,

    /* RFID Get */
    MML_UCID_RFID_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_RFID),
    MML_UCID_RFID_GET_READER_INFO = MML_UCID_RFID_GET_BASE,                 ///< Get Reader info
    MML_UCID_RFID_GET_SIM_CONTROL,
    MML_UCID_RFID_GET_CATEGORY,

    /* RFID Set */
    MML_UCID_RFID_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_RFID),
    MML_UCID_RFID_SET_SIM_CONTROL = MML_UCID_RFID_SET_BASE,                 ///< Set SIM control
    MML_UCID_RFID_SET_CATEGORY,

    /* RFID Execute */
    /* targets (JSR257) */
    MML_UCID_RFID_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_RFID),
    MML_UCID_RFID_ADD_TARGET_LISTENER = MML_UCID_RFID_EXECUTE_BASE,         ///<  Add target listener
    MML_UCID_RFID_REMOVE_TARGET_LISTENER,                                   ///<  Remove target listener
    MML_UCID_RFID_CONNECT_TARGET,                                           ///<  Connect target
    MML_UCID_RFID_DISCONNECT_TARGET,                                        ///<  Disconnect target
    MML_UCID_RFID_READ_TARGET,                                              ///<  Read target
    MML_UCID_RFID_WRITE_TARGET,                                             ///<  Write target
    MML_UCID_RFID_ISO443_EXCHANGE_DATA,                                     ///<  ISO443 exchange data
    MML_UCID_RFID_TRANSCEIVE,                                               ///<  Transceive
    MML_UCID_RFID_MF_COMMAND,                                               ///<  MF command
    MML_UCID_RFID_AUTO_SCAN,                                                ///<  Auto scan

    /* tags */
    MML_UCID_RFID_OPEN_TAG,
    MML_UCID_RFID_CLOSE_TAG,
    MML_UCID_RFID_READ_TAG,
    MML_UCID_RFID_WRITE_TAG,
    MML_UCID_RFID_LOCK_TAG,
    MML_UCID_RFID_UPGRADE_FIRMWARE,
    MML_UCID_RFID_READ_BARCODE,
    MML_UCID_RFID_EXECUTE_CATEGORY,

    /* Force ID to be at least 32-bits */
    MML_UCID_RFID_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerRfid
    @brief      Response results
*/
typedef enum
{
    /* Common */
    RFID_ERROR_SUCCESS = 0,
    RFID_ERROR_FAIL,
    RFID_ERROR_PARAMETER_INVALID,
    RFID_ERROR_STATE_CHANGE,
    RFID_ERROR_IGNORE,
    RFID_ERROR_REJECT,
    RFID_ERROR_MEMORY_FAILURE,
    RFID_ERROR_TIME_OUT,
    RFID_ERROR_RECORD_INDEX_USED,
	RFID_ERROR_OUT_OF_CAPACITY,
    /* */
    RFID_ERROR_NUM
} MmlRfidResult_e;

/** @ingroup    MMLayerRfid
    @brief      States
*/
typedef enum
{
    /* RFID */
    RFID_STATE_CLOSED = 0,
    RFID_STATE_OPENED,
    /* */
    RFID_STATE_DONTCARE,
    RFID_STATE_NUM
} MmlRfidState_e;

/** @ingroup    MMLayerRfid
    @brief      Events
*/
typedef enum
{
    /* Common */
    RFID_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_RFID),
    RFID_EVENT_RUNTIME_ERROR,
    RFID_EVENT_LISTENER_UPDATE,
    RFID_EVENT_DONTCARE,
    RFID_EVENT_ALL,
    RFID_EVENT_NUM
} MmlRfidEvent_e;

/** @ingroup    MMLayerRfid
    @brief      Target types
*/
typedef enum
{
    RFID_TARGETTYPE_RESERVED      = 0,
    RFID_TARGETTYPE_NDEF          = 0x0001,    ///< Target NDEF
    RFID_TARGETTYPE_RFID          = 0x0002,    ///< Target RFID
    RFID_TARGETTYPE_ISO14443_CARD = 0x0004,    ///< no support
    RFID_TARGETTYPE_VISUAL_TAG    = 0x0008,    ///< no support
    /* */
    RFID_TARGET_NUM
} MmlRfidTargetType_e;

/** @ingroup    MMLayerRfid
    @brief      Tag types
*/
typedef enum
{
    RFID_TAGTYPE_ALL = 0,                  ///< All supported tags
    RFID_TAGTYPE_ISO15693,                 ///< ISO15693 type
    RFID_TAGTYPE_C1G2,                     ///< C1G2 type
    RFID_TAGTYPE_ISO15693_MSTAR,           ///< ISO15693 MStar proprietary
    RFID_TAGTYPE_C1G2_MSTAR,               ///< C1G2 MStar proprietary
    RFID_TAGTYPE_ISO14443A,                ///< ISO14443A type
    RFID_TAGTYPE_ISO14443A_MF4K,           ///< ISO14443A MF4K type
    RFID_TAGTYPE_ISO14443A_MF1K,           ///< ISO14443A MF1K type
    RFID_TAGTYPE_ISO14443A_UL,             ///< ISO14443A MF_UL type
    RFID_TAGTYPE_ISO14443_4A,              ///< ISO14443_4A type
    RFID_TAGTYPE_ISO14443A_TOPAZ,          ///< ISO14443A TOPAZ/JEWEL
    RFID_TAGTYPE_ISO14443B,                ///< ISO14443B type
    RFID_TAGTYPE_ISO14443B_AT88RF04C,      ///< ISO14443B ATMEL  AT88RF04C
    RFID_TAGTYPE_ISO14443B_AT88SC0808CRF,  ///< ISO14443B ATMEL  AT88SC0808CRF
    RFID_TAGTYPE_ISO14443B_AT88SC1616CRF,  ///< ISO14443B ATMEL  AT88SC1616CRF
    RFID_TAGTYPE_ISO14443B_AT88SC3216CRF,  ///< ISO14443B ATMEL  AT88SC3216CRF
    RFID_TAGTYPE_ISO14443B_AT88SC6416CRF,  ///< ISO14443B ATMEL  AT88SC6416CRF
    RFID_TAGTYPE_ST14443B,                 ///< ST14443B type
    RFID_TAGTYPE_ISO14443_4B,              ///< ISO14443_4B type
    RFID_TAGTYPE_UNKNOWN,                  ///< Unknown media type
    RFID_TAGTYPE_TOTAL
}MmlRfidTagType_e;

/** @ingroup    MMLayerRfid
    @brief      Listener types
*/
typedef enum
{
    RFID_LISTENERTYPE_NDEF = 0,         ///< NDEF
    RFID_LISTENERTYPE_TARGET,           ///< RFID
    /* */
    RFID_LISTENERTYPE_NUM
} MmlRfidListenerType_e;

/** @ingroup    MMLayerRfid
    @brief      Scan mode
*/
typedef enum
{
    RFID_SCAN_MODE_ONCE = 0,            ///< Scan once
    RFID_SCAN_MODE_REPEAT,              ///< Scan repeatedly
    RFID_SCAN_MODE_UNKNOWN              ///< Unknown
} MmlRfidScanMode_e;

/** @ingroup    MMLayerRfid
    @brief      Block size
*/
typedef enum
{
    RFID_BLOCK_SIZE_2_BYTE = 0,         ///< 2-byte block
    RFID_BLOCK_SIZE_4_BYTE,             ///< 4-byte block
    RFID_BLOCK_SIZE_16_BYTE,            ///< 16-byte block
    RFID_BLOCK_SIZE_UNKNOWN             ///< Unknown block
} MmlRfidBlockSize_e;

/** @ingroup    MMLayerRfid
    @brief      Memory type
*/
typedef enum
{
    RFID_MEMORY_TYPE_RESERVED = 0,      ///< reserved
    RFID_MEMORY_TYPE_EPC,               ///< EPC type
    RFID_MEMORY_TYPE_TID,               ///< TID type
    RFID_MEMORY_TYPE_USER,              ///< USER type
    RFID_MEMORY_TYPE_UNKNOWN            ///< Unknown media type
} MmlRfidMemoryType_e;

/** @ingroup    MMLayerRfid
    @brief      Secured category
*/
typedef enum
{
    RFID_SECURED_CATEGORY_EAS = 0,      ///< EAS Related Operation
    RFID_SECURED_CATEGORY_SECURED_RW,   ///< Secured Read / Write
    RFID_SECURED_CATEGORY_PWD,          ///< Password Setting
    RFID_SECURED_CATEGORY_MAX
} MmlRfidSecuredCategory_e;

/** @ingroup    MMLayerRfid
    @brief      Module type
*/
typedef enum
{
    RFID_MODULETYPE_UHF = 0,            ///< UHF
    RFID_MODULETYPE_HF,                 ///< HF
    RFID_MODULETYPE_BARCODE,            ///< Bar code
    RFID_MODULETYPE_NO_SPECIFIED
} MmlRfidModuleType_e;

/** @ingroup    MMLayerRfid
    @brief      SIM mode
*/
typedef enum
{
    RFID_SIM_CONTROL_PHONE = 0,     ///< SIM controled by phone
    RFID_SIM_CONTROL_RFID           ///< SIM controled by RFID module
} MmlRfidSimControl_e;

/** @ingroup    MMLayerRfid
    @brief      Mifare operation
*/
typedef enum
{
	RFID_OPERATION_AUTHENTICATE,
	RFID_OPERATION_INCREMENT,
	RFID_OPERATION_DECREMENT,
	RFID_OPERATION_TRANSFER,
	RFID_OPERATION_RESTORE
}MmlRfidOperation_e;

/** @ingroup    MMLayerRfid
    @brief      Authenticate key index
*/
typedef enum
{
	RFID_KEY_INDEX_A				= 0,
	RFID_KEY_INDEX_B				= 1
}MmlRfidKeyIndex_e;

/** @ingroup    MMLayerRfid
    @brief      Status
*/
typedef enum
{
    /* Search Tag */
    RFID_STATUS_SEARCHTAG_ONE_TAG_FOUND = 0,
    RFID_STATUS_SEARCHTAG_TAG_NOT_MF_CLASSIC,
    RFID_STATUS_SEARCHTAG_NO_TAG_FOUND,
    RFID_STATUS_SEARCHTAG_MORE_THAN_ONE_TAG_FOUND,

    /* Authentication */
    RFID_STATUS_AUTHENTICATE_OK,
    RFID_STATUS_AUTHENTICATE_NO_TAG_TIMEOUT_FOR_RB,
    RFID_STATUS_AUTHENTICATE_FAIL_TIMEOUT_FOR_TOKENBA,
    RFID_STATUS_AUTHENTICATE_FAIL_WRONG_TOKENBA,
    RFID_STATUS_AUTHENTICATE_OTHER_THAN_KEYA_KEYB,

    /* Write */
    RFID_STATUS_WRITE_OK,
    RFID_STATUS_WRITE_NO_TAG_TIMEOUT_FOR_1ST_ACK,
    RFID_STATUS_WRITE_FAIL_1ST_NACK_NOT_ALLOW,
    RFID_STATUS_WRITE_FAIL_1ST_NACK_TRANSMISSION_ERROR,
    RFID_STATUS_WRITE_FAIL_TIMEOUT_FOR_2ND_ACK,
    RFID_STATUS_WRITE_FAIL_2ND_NACK_NOT_ALLOW,
    RFID_STATUS_WRITE_FAIL_2ND_NACK_TRANSMISSION_ERROR,

    /* Read */
    RFID_STATUS_READ_OK,
    RFID_STATUS_READ_NO_TAG_TIMEOUT,
    RFID_STATUS_READ_FAIL_GOT_ACK,
    RFID_STATUS_READ_FAIL_NACK_NOT_ALLOW,
    RFID_STATUS_READ_FAIL_NACK_TRANSMISSION_ERROR,
    RFID_STATUS_READ_FAIL_WRONG_LENGTH,
    RFID_STATUS_READD_FAIL_WRONG_PARITY,
    RFID_STATUS_READ_FAIL_WRONG_CRC,

    /* Increment/Decrement/Restore/Transfer (Value OP) */
    RFID_STATUS_VALUE_OK,
    RFID_STATUS_VALUE_NO_TAG_TIMEOUT_FOR_1ST_ACK,
    RFID_STATUS_VALUE_FAIL_1ST_NACK_NOT_ALLOW,
    RFID_STATUS_VALUE_FAIL_1ST_NACK_TRANSMISSION_ERROR,
    /* Halt */
    RFID_STATUS_HALT_OK,

    RFID_STATUS_UNEXPECTED_STATUS
}MmlRfidStatus_e;

/** @ingroup    MMLayerRfid
    @brief      Tag model
*/
typedef enum
{
    RFID_TAG_MODEL_MSR3200 = 0,             /* MStar Lyra Series */
    RFID_TAG_MODEL_MSR3260,                 /* MStar Pavo Series */
    RFID_TAG_MODEL_UNKNOWN,                 /* UNKNOWN */
    RFID_TAG_MODEL_MAX                      /*  */
} MmlRfidTagModel_e;

/** @ingroup    MMLayerRfid
    @brief      A block of memory, used to hold input/output data
*/
typedef	struct
{
    u32                 nHandle;        ///< Handle to Target
    u8                  *pBuffer;       ///< Pointer to the data buffer
    u32                 nBufferSize;    ///< Size in bytes of the data buffer
    u32                 nDataSize;      ///< Read/Write size in bytes of data in the data buffer
} MmlRfidBufferParam_t;

/** @ingroup    MMLayerRfid
    @brief      State change info
*/
typedef	struct
{
    MmlRfidState_e            eState;        ///< The new state after the transition
    MmlRfidEvent_e	          eCause;        ///< The cause of state change, if any
} MmlRfidStateChange_t;

/** @ingroup    MMLayerRfid
    @brief      NDEF add listener
*/
typedef struct
{
	u8	nNdefBitMask;
	u16	nDataLen;
	u8	*pDataBuf;                  ///< with maximun data size MML_RFID_NDEF_LISTENER_DATA_LEN
    u8  nIndex;
}MmlRfidNdefAddListener_t;

/** @ingroup    MMLayerRfid
    @brief      Target add listener
*/
typedef struct
{
	MmlRfidTargetType_e	eType;
}MmlRfidTargetAddListener_t;


/** @ingroup    MMLayerRfid
    @brief      Add listener
*/
typedef	struct
{
    MmlRfidListenerType_e    eType;

    /// union of MmlRfidAddListener_t parameters
    union
    {
        MmlRfidNdefAddListener_t    tNdefAddListener;
        MmlRfidTargetAddListener_t  tTargetAddListener;
    } uParam;
} MmlRfidAddListener_t;

/** @ingroup    MMLayerRfid
    @brief      NDEF remove listener
*/
typedef struct
{
	u8	nNdefBitMask;
	u16	nDataLen;
	u8	*pDataBuf;                  ///< with maximun data size MML_RFID_NDEF_LISTENER_DATA_LEN
    u8  nIndex;
}MmlRfidNdefRemoveListener_t;

/** @ingroup    MMLayerRfid
    @brief      Target remove listener
*/
typedef struct
{
	MmlRfidTargetType_e	eType;
}MmlRfidTargetRemoveListener_t;


/** @ingroup    MMLayerRfid
    @brief      Remove listener
*/
typedef	struct
{
    MmlRfidListenerType_e    eType;

    /// union of MmlRfidRemoveListener_t parameters
    union
    {
        MmlRfidNdefRemoveListener_t    tNdefRemoveListener;
        MmlRfidTargetRemoveListener_t  tTargetRemoveListener;
    } uParam;
} MmlRfidRemoveListener_t;

#define MML_RFID_NDEF_RT_BITMASK_EMPTY          ((u8)0x01)
#define MML_RFID_NDEF_RT_BITMASK_NFC_FORUM_RTD  ((u8)0x02)
#define MML_RFID_NDEF_RT_BITMASK_MIME           ((u8)0x04)
#define MML_RFID_NDEF_RT_BITMASK_URI            ((u8)0x08)
#define MML_RFID_NDEF_RT_BITMASK_EXTERNAL_RTD   ((u8)0x10)
#define MML_RFID_NDEF_RT_BITMASK_UNKNOWN        ((u8)0x20)
#define MML_RFID_NDEF_RT_BITMASK_UNCHANGED      ((u8)0x40)

#define	MML_RFID_NDEF_LISTENER_DATA_LEN         (152)

/** @ingroup    MMLayerRfid
    @brief      NDEF listener
*/
typedef struct
{
    u8	nDetectMask;	//MML_RFID_NDEF_RT_BITMASK_EMPTY
	u16	nDataSize;
	u8	*pData;         //with max data length MML_RFID_NDEF_LISTENER_DATA_LEN
}MmlRfidNdefListenerUpdate_t;


#define	MML_RFID_URL_NUM_MAX                    (4)
#define	MML_RFID_UID_MAX_LEN	                (10)
#define	MML_RFID_MAPPING_MAX_LEN	            (20)
#define	MML_RFID_URL_MAX_LEN	                (128)

/** @ingroup    MMLayerRfid
    @brief      RFID tag properties
*/
typedef struct
{
    u16     nType;
    u8		UIDStr[MML_RFID_UID_MAX_LEN*2+1];
	u8		UIDStrLen;
    u8		UID_Hex[MML_RFID_UID_MAX_LEN+1];
	u8		UID_Len;
    u8		mapping[MML_RFID_MAPPING_MAX_LEN+1];
    u8		url[MML_RFID_URL_NUM_MAX][MML_RFID_URL_MAX_LEN+1];
    u8		urlLen[MML_RFID_URL_NUM_MAX];
} MmlRfidTagProperties_t;

/** @ingroup    MMLayerRfid
    @brief      Target listener
*/
typedef struct
{
	u16						nTagNum;
	MmlRfidTagProperties_t	*pTagArray;
}MmlRfidTargetListenerUpdate_t;


/** @ingroup    MMLayerRfid
    @brief      Listener update
*/
typedef struct
{
	MmlRfidListenerType_e	eType;
    /// union of MmlRfidListenerUpdate_t parameters
	union
	{
		MmlRfidNdefListenerUpdate_t		    tNdefListenerUpdate;
		MmlRfidTargetListenerUpdate_t	    tTargetListenerUpdate;
	}uParam;

}MmlRfidListenerUpdate_t;

/** @ingroup    MMLayerRfid
    @brief      Connect target
*/
typedef struct
{
	MmlRfidTargetType_e	    eType;
	u8	                    *pUrl;
	u16	                    nUrlLen;
}MmlRfidConnectTarget_t;

/** @ingroup    MMLayerRfid
    @brief      Tag UID
*/
typedef struct
{
    u8                  *pUid;          ///< Tag UID
    u32                 nUidLength;     ///< Tag UID length
} MmlRfidTagUid_t;

/** @ingroup    MMLayerRfid
    @brief      Password
*/
typedef struct
{
    u8                  *pPasswordBuffer;
    u32                 nPassworkLength;
} MmlRfidPassowrd_t;

/** @ingroup    MMLayerRfid
    @brief      Block info
*/
typedef struct
{
    u16                     nBlockNum;   ///< Block number
    MmlRfidBlockSize_e      eBlockSize;  ///< Block size in byte
} MmlRfidBlockInfo_t;

/** @ingroup    MMLayerRfid
    @brief      ISO14443A response
*/
typedef struct
{
    u8                      S43A_SAK;
    u16                     S43A_ATQA;
} MmlRfidIso14443aResponse_t;

/** @ingroup    MMLayerRfid
    @brief      ISO14443B response
*/
typedef struct
{
    u8                      AT43B_APP3;
    u8                      S43B_Param;
} MmlRfidIso14443bResponse_t;


/** @ingroup    MMLayerRfid
    @brief      Tag info
*/
typedef struct
{
    MmlRfidTagType_e        eType;       ///< Tag type
    MmlRfidTagUid_t         tTagUid;     ///< Tag UID
    /// union of MmlRfidTagInfo_t parameters
    union
    {
        u16                         bIsKilled;   ///< Is this tag killed
        MmlRfidBlockInfo_t          tBlockInfo;
        MmlRfidIso14443aResponse_t  tIso144443aResponse;
        MmlRfidIso14443bResponse_t  tIso144443bResponse;

	} uParam;
} MmlRfidTagInfo_t;

/** @ingroup    MMLayerRfid
    @brief      Open tag complete
*/
typedef struct
{
    u32                     nTagInfoNum;
    MmlRfidTagInfo_t        *pTagInfo;
} MmlRfidOpenTagCompleteInfo_t;

/** @ingroup    MMLayerRfid
    @brief      Open tags
*/
typedef struct
{
    MmlRfidTagType_e        eType;              ///< tag type
    MmlRfidScanMode_e       eScanMode;          ///< Scan mode
    u32                     nRepeatTime;        ///< repeat scanning time (ms) (only for repeat scan)
    u16                     nTagInfoMaxNum;     ///< Max number of Tag info
} MmlRfidOpenTag_t;

/** @ingroup    MMLayerRfid
    @brief      Secured parameter
*/
typedef struct
{
    MmlRfidTagModel_e        eTagModel;         ///< Tag model
    MmlRfidSecuredCategory_e eCategory;         ///< Secured category
    MmlRfidPassowrd_t        tPassword;         ///< Password
} MmlRfidSecuredParam_t;

/** @ingroup    MMLayerRfid
    @brief      Access tag parameters
*/
typedef struct
{
    MmlRfidTagType_e        eType;              ///< Tag type
    MmlRfidTagUid_t         tTagUid;            ///< Tag UID
    MmlRfidMemoryType_e     eMemoryType;        ///< Memory type
    MmlRfidBlockSize_e      eBlockSize;         ///< Block size in byte
    u16                     nBlockID;           ///< Block ID
    u16                     nBufferLength;      ///< Buffer length
    u8                      *pBuffer;           ///< Buffer pointer
    /// union of MmlRfidAccessTagParam_t parameters
    union
    {
        u8                      S43B_Param;
        MmlRfidSecuredParam_t   tSecuredParam;
	} uParam;

} MmlRfidAccessTagParam_t;

/** @ingroup    MMLayerRfid
    @brief      Reader info
*/
typedef struct
{
    u16		nReaderIdLength;                    ///< Length of reader ID
	u8		*pReaderId;                         ///< Reader ID
	u16     nVersionLength;                     ///< Length of version
	u8      *pVersion;                          ///< versoin
} MmlRfidReaderInfo_t;

/** @ingroup    MMLayerRfid
    @brief      C1G2 lock parameters
*/
typedef struct {
    u8 Kill_mask;
	u8 Access_mask;
	u8 EPC_mask;
	u8 TID_mask;
	u8 User_mask;
	u8 Kill_action;
	u8 Access_action;
	u8 EPC_action;
	u8 TID_action;
	u8 User_action;
	u8 Flag;
} MmlRfidC1g2LockParam_t;

/** @ingroup    MMLayerRfid
    @brief      ISO15693_Mstar lock parameters
*/
typedef struct
{
    MmlRfidTagModel_e        eTagModel;         ///< Tag model
    MmlRfidSecuredCategory_e eCategory;         ///< Secured category
} MmlRfidIso15693MStarLockParam_t;

/** @ingroup    MMLayerRfid
    @brief      ISO15693 lock parameters
*/
typedef struct
{
    u8 Block_ID;
} MmlRfidIso15693LockParam_t;

/** @ingroup    MMLayerRfid
    @brief      Lock tag
*/
typedef struct
{
    MmlRfidTagType_e        eType;              ///< Tag type
    MmlRfidTagUid_t         tTagUid;            ///< Tag UID

    /// union of MmlRfidLockTag_t parameters
    union
    {
        MmlRfidC1g2LockParam_t          tC1g2LockParam;
        MmlRfidIso15693MStarLockParam_t tIso15693MstarLockParam;
        MmlRfidIso15693LockParam_t      tIso15693LockParam;
	} uParam;
} MmlRfidLockTag_t;

/** @ingroup    MMLayerRfid
    @brief      Authenticate key
*/
typedef struct
{
    MmlRfidKeyIndex_e   eIndex;
    u16                 nKeyLength;
    u8                  *pKey;
} MmlRfidKey_t;

/** @ingroup    MMLayerRfid
    @brief      Authenticate
*/
typedef struct
{
    MmlRfidOperation_e          eOperation;         ///< Operation type
    MmlRfidTagUid_t             tTagUid;            ///< Tag UID
    MmlRfidKey_t                tKey;               ///< key
    u8					        nBlockIndex;        ///< Block index
    s32					        nValue;             ///< Value
} MmlRfidMfCommandParam_t;

/** @ingroup    MMLayerRfid
    @brief      Notification payload
*/
typedef struct
{
    MmlRfidEvent_e	            eEvent;        ///< Specify the event you want to notify
    u32                         nHandle;       ///< 32-bit handle

    /// union of MmlRfidNotify_t parameters
    union
    {
        MmlRfidResult_e                 eErrCode;               ///< Used with 'RFID_EVENT_RUNTIME_ERROR' event
        MmlRfidListenerUpdate_t         tListenerUpdate;        ///< Used with 'RFID_EVENT_LISTENER_UPDATE'
	} uParam;
} MmlRfidNotify_t;

/** @ingroup    MMLayerRfid
    @brief      Notification callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      pRfidNotify       Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlRfidNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlRfidNotify_t *pRfidNotify);

/** @ingroup    MMLayerRfid
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                             nSenderID;           ///< Sender's mailbox ID
    u32                             nUserValue;          ///< Interface self-reference
    PfnMmlRfidNotifyCallback        pfnNotifyCallback;   ///< Callback function your want to register
} MmlRfidNotifyCallback_t;

/** @ingroup    MMLayerRfid
    @brief      Response callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      eErrCode          Returned result (error code)
    @param      pRfidResponse    Pointer to the returned response payload
*/
struct MmlRfidResponse_t_;
typedef void (*PfnMmlRfidResponseCallback)(u16 nSenderID, u32 nUserValue, MmlRfidResult_e eErrCode, struct MmlRfidResponse_t_ *pRfidResponse);

/** @ingroup    MMLayerRfid
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                             nSenderID;              ///< Sender's mailbox ID
    u32                             nUserValue;             ///< Interface self-reference
    PfnMmlRfidResponseCallback      pfnResponseCallback;    ///< Callback function your want to register
} MmlRfidResponseCallback_t;

/** @ingroup    MMLayerRfid
    @brief      Register notification callback
*/
typedef struct
{
    MmlRfidEvent_e                 eEvent;             ///< Specify which event you want to handle
    MmlRfidNotifyCallback_t        tNotifyCallback;    ///< Registration data specifying the callback function' address
} MmlRfidRegNotifyCallback_t;

/** @ingroup    MMLayerRfid
    @brief      RFID capability
*/
typedef struct
{
    u32     nVersion;
} MmlRfidCapability_t;

/** @ingroup    MMLayerRfid
    @brief      Get capability\n
                To make the interface backward compatible, the nVersion
                is used as the version number of interface input.
                Please set nVersion = current version.
*/
typedef struct
{
    u32     nVersion;               ///< Used for backward compatible (Current version = 0x0000, 2010/08/26)
} MmlRfidGetCapability_t;

/** @ingroup    MMLayerRfid
    @brief      Response payload
*/
typedef struct MmlRfidResponse_t_
{
    MmlRfidState_e          eState;       ///< Current state
    u32                     nHandle;      ///< 32-bit handle
    u32                     nUseCaseID;   ///< Use case ID

    /// union of MmlRfidResponse_t parameters
    union
    {
        MmlRfidBufferParam_t            tBufferParam;           ///< Used with 'MML_UCID_RFID_READ_TARGET'
                                                                ///<           'MML_UCID_RFID_ISO443_EXCHANGE_DATA'
                                                                ///<           'MML_UCID_RFID_TRANSCEIVE'
                                                                ///<           'MML_UCID_RFID_READ_TAG'
                                                                ///<           'MML_UCID_RFID_READ_BARCODE'
        MmlRfidReaderInfo_t             tReaderInfo;            ///< Used with 'MML_UCID_RFID_GET_READER_INFO'
        MmlRfidOpenTagCompleteInfo_t    tOpenTagCompleteInfo;   ///< Used with 'MML_UCID_RFID_OPEN_TAG'
        MmlRfidSimControl_e             eSimControl;            ///< Used with 'MML_UCID_RFID_GET_SIM_CONTROL'
        MmlRfidStatus_e                 eStatus;                ///< Used with 'MML_UCID_RFID_MF_COMMAND'
        MmlRfidListenerType_e           eListenerType;          ///< Used with 'MML_UCID_RFID_ADD_TARGET_LISTENER'
	} uParam;
} MmlRfidResponse_t;

/** @ingroup    MMLayerRfid
    @brief      RFID use case parameters
*/
typedef struct
{
	u32                                 nUseCaseID;             ///< Use case ID
	MmlRfidResponseCallback_t           *pResponseCallback;     ///< Pointer to the response callback registration data
	MmlRfidResponse_t                   *pResponse;             ///< Pointer to the response payload

    /// union of MmlRfidUCParam_t parameters
	union
	{
        u32                                 nHandle;            ///< Used with 'MML_UCID_RFID_CLOSE_TARGET','MML_UCID_RFID_READ_TARGET'
        u16                                 bEnable;            ///< Used with 'MML_UCID_RFID_AUTO_SCAN'
        MmlRfidConnectTarget_t              tConnectTarget;     ///< Used with 'MML_UCID_RFID_CONNECT_TARGET'
        MmlRfidAddListener_t                tAddListener;       ///< Used with 'MML_UCID_RFID_ADD_TARGET_LISTENER'
        MmlRfidRemoveListener_t             tRemoveListener;    ///< Used with 'MML_UCID_RFID_REMOVE_TARGET_LISTENER'
        MmlRfidBufferParam_t                tBufferParam;       ///< Used with 'MML_UCID_RFID_WRITE_TARGET','MML_UCID_RFID_ISO443_EXCHANGE_DATA'
                                                                ///<           'MML_UCID_RFID_TRANSCEIVE'
                                                                ///<           'MML_UCID_RFID_READ_BARCODE'
        MmlRfidOpenTag_t                    tOpenTag;           ///< Used with 'MML_UCID_RFID_OPEN_TAG'
        MmlRfidAccessTagParam_t             tReadTag;           ///< Used with 'MML_UCID_RFID_READ_TAG'
        MmlRfidAccessTagParam_t             tWriteTag;          ///< Used with 'MML_UCID_RFID_WRITE_TAG'
        MmlRfidSimControl_e                 eSimControl;        ///< Used with 'MML_UCID_RFID_SET_SIM_CONTROL'
        MmlRfidLockTag_t                    tLockTag;           ///< Used with 'MML_UCID_RFID_LOCK_TAG'
        MmlRfidMfCommandParam_t             tMfCommandParam;    ///< Used with 'MML_UCID_RFID_MF_COMMAND'
	} uParam;
} MmlRfidUCParam_t;
/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLRFID_TYPES_H__

