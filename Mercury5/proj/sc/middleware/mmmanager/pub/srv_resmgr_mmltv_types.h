////////////////////////////////////////////////////////////////////////////////

/**
* @file    srv_resmgr_mmltv_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLTV_TYPES_H__
#define __SRV_RESMGR_MMLTV_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup MMLayerTv TV
    Analog TV, Digital TV
    @{
*/
    /** @defgroup MMLayerAnalogTv Analog TV
        Analog TV
        @{
    */
    /** @} */

    /** @defgroup MMLayerDigitalTv Digital TV
        Digital TV
        @{
    */
    /** @} */

/** @} */

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"
#include "srv_resmgr_mmlimage_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerTv
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseTvId_e_)
{
    /* Tv Init */
    MML_UCID_TV_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_TV),
    MML_UCID_TV_REG_NOTIFY_CALLBACK = MML_UCID_TV_INIT_BASE,              ///< 00070000 = Reg notify callback
    MML_UCID_TV_UNREG_NOTIFY_CALLBACK,                                    ///< 00070001 = Unreg notify callback
    MML_UCID_TV_OPEN,                                                     ///< 00070002 = Open
    MML_UCID_TV_CLOSE,                                                    ///< 00070003 = Close
    MML_UCID_TV_INIT_CATEGORY,

    /* Tv Get */
    MML_UCID_TV_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_TV),
    MML_UCID_TV_GET_TV_INFO = MML_UCID_TV_GET_BASE,                       ///< 00070100 = Get TV info
    MML_UCID_TV_RETRIEVE_CHANNEL_INFO,                                    ///< 00070101 = Retrieve channel info
    MML_UCID_TV_GET_CAPABILITY,                                           ///< 00070102 = Get TV capability
    MML_UCID_TV_GET_CATEGORY,

    /* Tv Set */
    MML_UCID_TV_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_TV),
    MML_UCID_TV_SET_TV_CONFIGURATION = MML_UCID_TV_SET_BASE,              ///< 00070200 = Set TV configuration
    MML_UCID_TV_SWITCH_CHANNEL,                                           ///< 00070201 = Switch channel
    MML_UCID_TV_RESET_WINDOW,                                             ///< 00070202 = Reset window
    MML_UCID_TV_SET_EMM,
    MML_UCID_TV_SET_IMAGE_STEREO_TYPE,                                    ///< 00070204 = Set image stereo type
    MML_UCID_TV_SET_IMAGE_STEREO_DEPTH,                                   ///< 00070205 = Set image stereo depth
    MML_UCID_TV_SET_CATEGORY,

    /* Tv Execute */
    MML_UCID_TV_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_TV),
    MML_UCID_TV_START_PREVIEW = MML_UCID_TV_EXECUTE_BASE,                 ///< 00070300 = Start preview
    MML_UCID_TV_STOP_PREVIEW,                                             ///< 00070301 = Stop preview
    MML_UCID_TV_SCAN_CHANNEL,                                             ///< 00070302 = Scan preview
    MML_UCID_TV_EXECUTE_CATEGORY,

    /* Force ID to be at least 32-bits */
    MML_UCID_TV_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerTv
    @brief      Response results
*/
typedef enum
{
    /* Common */
    TV_ERROR_SUCCESS = 0,
    TV_ERROR_FAIL,
    TV_ERROR_PARAMETER_INVALID,
    TV_ERROR_STATE_CHANGE,
    TV_ERROR_ACCEPT,
    TV_ERROR_IGNORE,
    TV_ERROR_REJECT,
    TV_ERROR_WEAK_SIGNAL,
    TV_ERROR_MEMORY_FAILURE,
    /* */
    TV_ERROR_NUM
} MmlTvResult_e;

/** @ingroup    MMLayerTv
    @brief      States
*/
typedef enum
{
    /* ATV/DTV */
    TV_STATE_PREVIEW_ON = 0,
    TV_STATE_PREVIEW_OFF,
    TV_STATE_RETRIEVAL,
    /* */
    TV_STATE_DONTCARE,
    TV_STATE_NUM
} MmlTvState_e;

/** @ingroup    MMLayerTv
    @brief      Events
*/
typedef enum
{
    /* Common */
    TV_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_TV),
    TV_EVENT_RUNTIME_ERROR,
    /* ATV/DTV */
    TV_EVENT_RETRIEVAL_COMPLETE,
    /* */
    TV_EVENT_DONTCARE,
    TV_EVENT_ALL,
    TV_EVENT_NUM
} MmlTvEvent_e;

/** @ingroup    MMLayerTv
    @brief      Input source types
*/
typedef enum
{
    TV_INPUT_ATV = 0,   ///< Analog TV
    TV_INPUT_MMP_DTV,       ///< Digital TV
    TV_INPUT_RAWDATA_DTV,  
    TV_INPUT_DTV,       ///< Digital TV
    /* */
    TV_INPUT_NUM
} MmlTvInputType_e;

/** @ingroup    MMLayerTv
    @brief      File-based destination
*/
typedef struct
{
    MmlImageImageCodec_e    eCodecId;
    MmlFilenameFormat_e     eFilenameFormat;
    u16                     *pFileName;
    u16  	                nFileNameSize;
} MmlTvFileParam_t;

/** @ingroup    MMLayerTv
    @brief      Info types
*/
typedef enum
{
    TV_INFOTYPE_NORMAL = 0,     ///< Normal TV info
    TV_INFOTYPE_ENGINEERING,    ///< Engineering mode TV info
    TV_INFOTYPE_CMMB,           ///< CMMB TV info
    TV_INFOTYPE_ISDBT,
    TV_INFOTYPE_ALL,            ///< All of the TV info (Normal + Engineering)
} MmlTvInfoType_e;

/** @ingroup    MMLayerTv
    @brief      Signal levels (RSSI)
*/
typedef enum
{
    TV_SIGNALLEVEL_0 = 0,    ///< No signal
    TV_SIGNALLEVEL_1,        ///< Level 1
    TV_SIGNALLEVEL_2,        ///< Level 2
    TV_SIGNALLEVEL_3,        ///< Level 3
    TV_SIGNALLEVEL_4,        ///< Level 4
    TV_SIGNALLEVEL_5,        ///< Level 5
    TV_SIGNALLEVEL_6,        ///< Level 6
    TV_SIGNALLEVEL_7,        ///< Level 7
    TV_SIGNALLEVEL_8,        ///< Level 8
    TV_SIGNALLEVEL_NUM,
} MmlTvSignalLevel_e;

/** @ingroup    MMLayerTv
    @brief      Rotation angles
*/
typedef enum
{
    TV_ROTATION_0 = 0,    ///< 0 degree
    TV_ROTATION_90,       ///< 90 degree
    TV_ROTATION_180,      ///< 180 degree
    TV_ROTATION_270,      ///< 270 degree
    /* */
    TV_ROTATION_NUM
} MmlTvRotationAngle_e;


/** @ingroup    MMLayerTv
    @brief      Hybrid TV type
*/
typedef enum
{
    TV_HYBRID_ANALOG = 0,
    TV_HYBRID_CMMB,
    TV_HYBRID_ISDBT,
    TV_HYBRID_NUM,
} MmlTvHybridType_e;


/** @ingroup    MMLayerTv
    @brief      Regions
*/
typedef enum
{
    TV_REGION_USA = 0,      /*USA*/
    TV_REGION_CANADA,       /*CANADA*/
    TV_REGION_KOREA,        /*KOREA*/
    TV_REGION_TAIWAN,       /*TAIWAN*/
    TV_REGION_MEXICO,       /*MEXICO*/
    TV_REGION_CHILE,        /*CHILE*/
    TV_REGION_VENEZUELA,    /*VENEZUELA*/
    TV_REGION_PHILIPPINES,  /*PHILIPPINES*/
    TV_REGION_JAMAICA,      /*JAMAICA*/
    TV_REGION_CHINA,        /*CHINA*/
    TV_REGION_SHENZHEN,     /*SHENZHE*/
    TV_REGION_VIETNAM,      /*VIETNAM*/
    TV_REGION_WESTERNEUROPE,/*WESTERNEUROPE*/
    TV_REGION_TURKEY,       /*TURKEY*/
    TV_REGION_UAE,          /*UAE*/
    TV_REGION_AFGHANISTAN,  /*AFGHANISTAN*/
    TV_REGION_SINGAPORE,    /*SINGAPORE*/
    TV_REGION_THAILAND,     /*THAILAND*/
    TV_REGION_CAMBODIA,     /*CAMBODIA*/
    TV_REGION_INDONESIA,    /*INDONESIA*/
    TV_REGION_MALAYSIA,     /*MALAYSIA*/
    TV_REGION_LAOS,         /*LAOS*/
    TV_REGION_PORTUGAL,     /*PORTUGAL*/
    TV_REGION_SWEDEN,       /*SWEDEN*/
    TV_REGION_PAKISTAN,     /*PAKISTAN*/
    TV_REGION_SPAIN,        /*SPAIN*/
    TV_REGION_JAPAN,        /*JAPAN*/
    TV_REGION_UK,           /*UK*/
    TV_REGION_HONGKONG,     /*HONGKONG*/
    TV_REGION_SOUTHAFRICA,  /*SOUTHAFRICA*/
    TV_REGION_BRAZIL,       /*BRAZIL*/
    TV_REGION_ARGENTINA,    /*ARGENTINA*/
    TV_REGION_INDIA,        /*INDIA*/
    TV_REGION_BURMA,        /*BURMA*/
    TV_REGION_SUDAN,        /*SUDAN*/
    TV_REGION_YEMEN,        /*YEMEN*/
    TV_REGION_PERU,         /*PERU*/
    TV_REGION_BOLIVIA,      /*BOLIVIA*/
    TV_REGION_ECUADOR,      /*ECUADOR*/
    TV_REGION_SURINAME,     /*SURINAME*/
    TV_REGION_AUSTRALIA,    /*AUSTRALIA*/
    TV_REGION_NEWZEALAND,   /*NEWZEALAND*/
    TV_REGION_COLUMBIA,     /*COLUMBIA*/
    TV_REGION_COSTARICA,    /*COSTARICA*/
    TV_REGION_HONDURAS,     /*HONDURAS*/
    TV_REGION_GERMAN,       /*GERMAN*/
    TV_REGION_ITALY,        /*ITALY*/
    TV_REGION_NUM
} MmlTvRegion_e;

/** @ingroup    MMLayerTv
    @brief      Rectangle
*/
typedef struct
{
    u16     nLeft;      ///< x-position of the top left corner of rectangle
    u16     nTop;       ///< y-position of the top left corner of rectangle
    u16     nWidth;     ///< Width of rectangle
    u16     nHeight;    ///< Height of rectangle
} MmlTvRectangle_t;

/** @ingroup    MMLayerTv
    @brief      Normal ATV info\n
                TV info is currently only available for ATV, including
                1. maximum channel number available in this region
                2. signal level 0-8, 0: no signal
*/
typedef	struct
{
    MmlTvSignalLevel_e   eSignalLevel;            ///< Indicate the received signal strength indication (RSSI)
    u32                  nMaxAvailableChannel;    ///< Maximum channel number available in this region
} MmlTvNormalAtvInfo_t;

/** @ingroup    MMLayerTv
    @brief      Engineering mode ATV info
*/
typedef	struct
{
    u16     nTfCode;       ///< The tfcode of telegent chip
    u16     nPeakAgc;      ///< The peak of telegent chip
    u16     nTotalGain;    ///< The total gain of telegent chip
    u16     bColorLock;    ///< The color lock bit of telegent chip
} MmlTvEngineeringModeAtvInfo_t;

/** @ingroup    MMLayerTv
    @brief      CA access status
*/
typedef enum
{
    TV_CAACCESS_GRANTED = 0,
    TV_CAACCESS_DENIED = 2,
    TV_CAACCESS_CLEAR = 9
} MmlTvCaAccessStatus_e;

/** @ingroup    MMLayerTv
    @brief      CMMB TV info
*/
typedef struct
{
    u8                     *pCat;
    u32                    nCatSize;
    u8  	                 *pEsg;
    u32 	                 nEsgSize;
    u8  	                 *pCaCardNumber;
    u32                    nCaCardNumberSize; 
    MmlTvCaAccessStatus_e  eCaPermission;
    MmlTvSignalLevel_e     eSignalLevel;            ///< Indicate the received signal strength indication (RSSI)
} MmlTvCmmbTvInfo_t;

/** @ingroup    MMLayerTv
    @brief      Digital ISDBT TV info
*/
typedef struct 
{        
    u8  	                 *pEpg;
    u32 	                 nEpgSize;
    MmlTvSignalLevel_e     eSignalLevel;            ///< Indicate the received signal strength indication (RSSI)
} MmlTvIsdbtTvInfo_t;




/** @ingroup    MMLayerTv
    @brief      TV info
*/
typedef struct
{
    MmlTvInfoType_e     eInfoType;     ///< What kind of info is this

    /// union of MmlTvTvInfo_t parameters
    union
    {
        MmlTvNormalAtvInfo_t            tNormalAtvInfo;             ///< Normal ATV info
        MmlTvEngineeringModeAtvInfo_t   tEngineeringModeAtvInfo;    ///< Engineering mode ATV info
        MmlTvCmmbTvInfo_t               tCmmbTvInfo;               ///< Pointer to the output CMMB TV info buffer
        MmlTvIsdbtTvInfo_t              tIsdbtTvInfo;                 ///< Pointer to the output Digital TV (ISDBT) info buffer
 	} uParam;
} MmlTvTvInfo_t;

/** @ingroup    MMLayerTv
    @brief      Scan result
*/
typedef struct
{
    u16             bAvailable;   ///< Boolean flag to indicate if channel is available
    u16             *pChannelName;   // Character array for Channel name
    u32             nChannel;     ///< 32-bit channel number (ATV)
    u32             nFrequency;   ///< 32-bit frequency in 1 MHz (DTV)
    u32             nChannelNameLength;
} MmlTvScanResult_t;

typedef struct
{
    u32             nFrequency;
    u32             nProgramServiceID;
    u8              *pProgramServiceTimeSlot;
    u8              nProgramServiceTimeSlotLength;
    u32             nEmmServiceID;
    u8              *pEmmServiceTimeSlot;
    u8              nEmmServiceTimeSlotLength;
} MmlTvFrequency_t;

/** @ingroup    MMLayerTv
    @brief      Retrieval complete info
*/
typedef struct
{
    /* The ESG data definition is still TBD */
    u8              *pBuffer;       ///< Pointer to the output ESG data
    u32             nBufferSize;    ///< Size in bytes of the output ESG data
} MmlTvRetrievalCompleteInfo_t;

/** @ingroup    MMLayerTv
    @brief      State change info
*/
typedef	struct
{
    MmlTvState_e     eState;    ///< The new state after the transition
    MmlTvEvent_e	 eCause;    ///< The cause of state change, if any
} MmlTvStateChange_t;

/** @ingroup    MMLayerTv
    @brief      Tv capability
*/
typedef struct
{
    u32     nImageStereoSupported;///< Image stereo supported bitmask
} MmlTvCapability_t;

/** @ingroup    MMLayerTv
    @brief      Notification payload
*/
typedef struct
{
    MmlTvEvent_e            eEvent;    ///< Specify the event you want to notify

    /// union of MmlTvNotify_t parameters
    union
    {
        MmlTvStateChange_t              tStateChange;              ///< Used with TV_EVENT_STATE_CHANGE event
        MmlTvResult_e                   eErrCode;                  ///< Used with TV_EVENT_RUNTIME_ERROR event
        MmlTvRetrievalCompleteInfo_t    tRetrievalCompleteInfo;    ///< Used with TV_EVENT_RETRIEVAL_COMPLETE event
	} uParam;
} MmlTvNotify_t;

/** @ingroup    MMLayerTv
    @brief      Notification callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      pTvNotify         Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlTvNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlTvNotify_t *pTvNotify);

/** @ingroup    MMLayerTv
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                             nSenderID;            ///< Sender's mailbox ID
    u32                             nUserValue;           ///< Interface self-reference
    PfnMmlTvNotifyCallback          pfnNotifyCallback;    ///< Callback function your want to register
} MmlTvNotifyCallback_t;

/** @ingroup    MMLayerTv
    @brief      Response callback prototype
    @param      nSenderID         Sender's mailbox ID
    @param      nUserValue        Interface self-reference
    @param      eErrCode          Returned result (error code)
    @param      pTvResponse       Pointer to the returned response payload
*/
struct MmlTvResponse_t_;
typedef void (*PfnMmlTvResponseCallback)(u16 nSenderID, u32 nUserValue, MmlTvResult_e eErrCode, struct MmlTvResponse_t_ *pTvResponse);

/** @ingroup    MMLayerTv
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                             nSenderID;              ///< Sender's mailbox ID
    u32                             nUserValue;             ///< Interface self-reference
    PfnMmlTvResponseCallback        pfnResponseCallback;    ///< Callback function your want to register
} MmlTvResponseCallback_t;

/** @ingroup    MMLayerTv
    @brief      Register notification callback
*/
typedef struct
{
    MmlTvEvent_e                 eEvent;            ///< Specify which event you want to handle
    MmlTvNotifyCallback_t        tNotifyCallback;   ///< Callback function you want to register
} MmlTvRegNotifyCallback_t;

/** @ingroup    MMLayerTv
    @brief      Get TV info
*/
typedef struct
{
    MmlTvInfoType_e             eInfoType;       ///< Indicate what type of the TV info to get
    union
    {
        MmlTvCmmbTvInfo_t       tCmmbTvInfo;    ///< Pointer to the output CMMB TV info buffer
        MmlTvIsdbtTvInfo_t      tIsdbtTvInfo;                 ///< Pointer to the output Digital TV (ISDBT) info buffer
 	} uParam;
} MmlTvGetTvInfo_t;

/** @ingroup    MMLayerTv
    @brief      Retrieve channel info
*/
typedef struct
{
    MmlTvFrequency_t            tFrequency;              ///< Frequency information Structure (Only used for DTV)
} MmlTvRetrieveChannelInfo_t;

/** @ingroup    MMLayerTv
    @brief      Set TV configuration
*/
typedef struct
{
    MmlTvRegion_e               eRegion;       ///< TV nation's region
    MmlTvHybridType_e           eHybridType;
    MmlTvFileParam_t            tFileParam;    ///< Record filename (full path, unicode)
} MmlTvSetTvConfiguration_t;

/** @ingroup    MMLayerTv
    @brief      Switch channel
*/
typedef struct
{
    union{
      u32                         nAtvChannel;             ///< 32-bit channel number
      MmlTvFrequency_t            tFrequency;              ///< Frequency information Structure (Only used for DTV)
    } uParam;
} MmlTvSwitchChannel_t;

/** @ingroup    MMLayerTv
    @brief      Reset window
*/
typedef struct
{
    MmlTvRectangle_t            tDisplayOutput;          ///< Display output
    MmlTvRotationAngle_e        eRotationAngle;          ///< Rotation angle
} MmlTvResetWindow_t;

/** @ingroup    MMLayerTv
    @brief      Start preview
*/
typedef struct
{
    MmlTvRectangle_t            tDisplayOutput;          ///< Display output
    MmlTvRotationAngle_e        eRotationAngle;          ///< Rotation angle
    union{
      u32                         nAtvChannel;                ///< 32-bits channel number
      MmlTvFrequency_t            tFrequency;                 ///< 32-bits DTV frequency (in 1KHz)
    } uParam;
} MmlTvStartPreview_t;

/** @ingroup    MMLayerTv
    @brief      Scan channel
*/
typedef struct
{
    u32                         nChannel;                ///< 32-bit channel number (ATV)
    u16                         *pChannelName;   // Character array for Channel name
    u32                         nChannelNameLength;
} MmlTvScanChannel_t;

typedef struct
{
    u32                         nFrequency;     ///< 32-bit frequency in 1 KHz (DTV)
} MmlTvScanFrequency_t;


typedef struct
{
    u8                         *pEmm;                   /// Pointer to EMM data buffer allocated by AP
    u16                        nEmmLength;              /// EMM buffer length
} MmlTvSetEmm_t;


/** @ingroup    MMLayerTv
    @brief      Response payload
*/
typedef struct MmlTvResponse_t_
{
    MmlTvState_e        eState;        ///< Current state
    MmlTvInputType_e    eInputType;    ///< Input source types (ATV, DTV, ...)

    union
    {
        MmlTvScanResult_t               tScanResult;           ///< Used with 'Scan channel'
        MmlTvTvInfo_t                   tTvInfo;               ///< Used with 'Get TV info'
        MmlTvStateChange_t              tStateChange;          ///< Used with 'TV_ERROR_STATE_CHANGE' result
        MmlTvCapability_t               tTvCapability;         ///< Used with 'Get TV capability'
    } uParam;
} MmlTvResponse_t;

/** @ingroup    MMLayerTv
    @brief      Tv use case parameters
*/
typedef struct
{
    u32                             nUseCaseID;
    MmlTvResponseCallback_t         *pResponseCallback;
    MmlTvResponse_t                 *pResponse;
    MmlTvInputType_e                eInputType;

    union
    {
   	    /* No parameter: 'Stop preivew, Open, Close' */

        MmlTvGetTvInfo_t              tGetTvInfo;              /* Get TV info */
        MmlTvRetrieveChannelInfo_t    tRetrieveChannelInfo;    /* Retrieve channel info */
        MmlTvSetTvConfiguration_t     tSetTvConfiguration;     /* Set TV configuration */
        MmlTvSetEmm_t                 tSetEmm;                 /* Set EMM */
        MmlTvSwitchChannel_t          tSwitchChannel;          /* Switch channel */
        MmlTvResetWindow_t            tResetWindow;            /* Reset window */
        MmlTvStartPreview_t           tStartPreview;           /* Start preview */
        MmlTvScanChannel_t            tScanChannel;            /* Scan channel */
        MmlTvScanFrequency_t          tScanFrequency;          /* Scan Frequency (for DTV) */
        MmlImageStereoType_e          eImageStereoType;        /* TV image stereo param */
        u32                           nImageStereoDepth;       /* Image stereo depth */
    } uParam;
} MmlTvUCParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLTV_TYPES_H__
