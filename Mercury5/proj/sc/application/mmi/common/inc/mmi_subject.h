/**
 * @file mmi_subject.h
 *
 * @brief  constants, enum valuse, data types and handlers about subjects can be defined here.
 *
 * @author Ted.lee@mstarsemi.com
 *         jerry-hy.liu@mstarsemi.com
 */
//////////////////////////////////////////////////////////////////////////
//==========Includes=======================
#ifndef __MMI_SUBJECT_H__
#define __MMI_SUBJECT_H__

#include "mmi_SubjectItf.h"
#include "mmi_cfgsrv.h"
#include "mmi_srvcommon.h"

//////////////////////////////////////////////////////////////////////////
//[Memory check subject]
//1.subject name
#define	MEMORY_CHECK_SBJ "MemCheck" // memory subject
#define EVT_SUBJECT_AUTOHANDLE		0x5A5A5A5A
//2.subject status: bit-aligned by using SBJSTS(a)
enum
{
	SBJ_MEMORY_HIGH = SBJSTS(0),
	SBJ_MEMORY_NORMAL = SBJSTS(1),
	SBJ_MEMORY_LOW = SBJSTS(2)
};

//3.request id
enum
{
    REQ_BT_INIT,
    REQ_BT_SENDING,
    REQ_BT_RECEIVING,
    REQ_MMS_SENDING,
    REQ_MMS_RECEIVING,
    REQ_MMS_EDITING,
    REQ_VIDEOPLAYER_PLAY,
    REQ_AUDIOPLAYER_PLAY,
    REQ_JAVA_RUNNING,
    REQ_JAVA_INSTALL,
    REQ_WIFI_USING,
    REQ_CCMTA_RUNNING,
    REQ_CAM_RECORDING,
    REQ_CAM_CAPTURING,
    REQ_ZMOL_RUNNING,
    REQ_ZYUE_RUNNING,
    REQ_TENCENTMCARE_RUNNING,
    REQ_NQQ_INIT,
    REQ_SXMENGINE_RUNNING,
    REQ_EMU_8BIT_PLAYING,
    REQ_EMU_16BIT_PLAYING,
    REQ_EMU_16BIT_MINI_PLAYING,
    REQ_TENCENTMCARE_BACKGOUND,
    REQ_MEMORYSBJ_USE,
    REQ_PICVIEWER_INIT,
    REQ_PICVIEWER_3D_DECODE
};

/*4.MemoryUsage ID
 *When modifying it, you should correct the _gMemoryUsage[] in mmi_subject.c.
 */
enum{
    DEFAULT_MEMORY_CAPACITY = 0,
    BT_INIT,
    BT_SENDING,
    BT_RECEIVING,
    MMS_SENDING,
    MMS_RECEIVING,
    MMS_EDITING,
    VIDEOPLAYER_PLAY,
    AUDIOPLAYER_PLAY,
    JAVA_RUN,
    JAVA_INSTALL,
    WIFI_USING,
    CCMTA_RUNNING,
    CAM_RECORDING,
    CAM_CAPTURING,
    ZMOL_RUN,
    ZYUE_RUN,
    TENCENTMCARE_RUN,
    NQQ_INIT,
    SXMENGINE_RUN,
    EMU_8BIT_PLAYING,
    EMU_16BIT_PLAYING,
    EMU_16BIT_MINI_PLAYING,
    TENCENTMCARE_BACKGOUND,
    MEMORYSBJ_USE,
    PICVIEWER_INIT,
    PICVIEWER_3D_DECODE,
    MEMARRAY_ENDIDX,
};


//5.Data type
typedef struct MemoryData_tag
{
    s32 nInitFreeMemorySize;
    s32 nAvailableMemory;
    boolean bAggressiveUsed;
}MemoryData_t;

//6.handler function
MAE_Ret MemorySubjectHandler
(
    SubjectAction_e eSubjectAction,
    u32 variable,
    void *pSubjectData,
    SubjectStatus_e *pSbjStatus
);

void MemorySubjectDefListener
(
    char *pSbjName,
    SubjectStatus_e eSbjStatus,
    void *pUser
);
/*
 *nMemUsageID
*enum{
DEFAULT_MEMORY_CAPACITY = 0,
BT_INIT,
BT_SENDING,
BT_RECEIVING,
MMS_SENDING,
MMS_RECEIVING,
MMS_EDITING,
VIDEOPLAYER_PLAY,
AUDIOPLAYER_PLAY,
NCC_3RD_JAVA_RUN,
WIFI_USING,
CCMTA_RUNNING,
CAM_RECORDING,
CAM_CAPTURING,
MEMARRAY_ENDIDX,
};
 */
MAE_Ret MemorySubjectSetResourceValue
(
    u32 nMemUsageID,
    s32 nAmount
);

/*
7. MAE_RET code for subject request
MAE_RET_SUCCESS           : Request is successfully made.
MAE_RET_DUPLICATE_HANDLER : Request is ignored because it is a duplicate request for the same reqId which is not released yet.
MAE_RET_FAILED            : Request is not duplicate but fails.
MAE_RET_NOT_FOUND         : Requested subject does not exist.

8. MAE_RET code for subject release
MAE_RET_SUCCESS           : Release is successfully made.
MAE_RET_NOT_FOUND         : Subject for this release does not exist.
                                                   Or request is ignored because there is no corresponding request existing.
*/



//////////////////////////////////////////////////////////////////////////
//[USB unblocking subject]
//1.subject name
#define	USB_STATUS_SBJ "USBStatus"

//2.subject status: bit-aligned by using SBJSTS(a)
enum
{
    SBJ_USB_UNBLOCK = SBJSTS(0),
    SBJ_USB_MODEM = SBJSTS(1),//modem
    SBJ_USB_STORAGE = SBJSTS(2),//mass storage
    SBJ_USB_WEBCAM = SBJSTS(3)//webcam
};

//3.request id
enum
{
    REQ_USBSRV
};

//4.variable
//The same as status enum

//5.Data type

//6.handler function
MAE_Ret USBSubjectHandler
(
    SubjectAction_e eSubjectAction,
    u32 variable,
    void *pSubjectData,
    SubjectStatus_e *pSbjStatus
);

void USBSubjectDefListener
(
    char *pSbjName,
    SubjectStatus_e eSbjStatus,
    void *pUser
);

/*
7. MAE_RET code for subject request
MAE_RET_SUCCESS           : Request is successfully made.
MAE_RET_DUPLICATE_HANDLER : Request is ignored because it is a duplicate request for the same reqId which is not released yet.
MAE_RET_NOT_FOUND         : Requested subject does not exist.

8. MAE_RET code for subject release
MAE_RET_SUCCESS           : Release is successfully made.
MAE_RET_NOT_FOUND         : Subject for this release does not exist.
                                                   Or request is ignored because there is no corresponding request existing.
*/



//////////////////////////////////////////////////////////////////////////
//[Socket unblocking subject]
//1.subject name
#define	SOCKET_STATUS_SBJ "SocketStatus"

//2.subject status: bit-aligned by using SBJSTS(a)
enum
{
    SBJ_SOCKET_UNBLOCK = SBJSTS(0),
    SBJ_SOCKET_AVAILABLE = SBJSTS(1),//Datalink available
    SBJ_SOCKET_NOTAVAILABLE = SBJSTS(2),//Datalink Not available
};

//3.request id
enum
{
    REQ_SOCKETSRV
};

//4.variable
//The same as status enum

//5.Data type

//6.handler function
MAE_Ret SocketSubjectHandler
(
    SubjectAction_e eSubjectAction,
    u32 variable,
    void *pSubjectData,
    SubjectStatus_e *pSbjStatus
);

void SocketSubjectDefListener
(
    char *pSbjName,
    SubjectStatus_e eSbjStatus,
    void *pUser
);

/*
7. MAE_RET code for subject request
MAE_RET_SUCCESS           : Request is successfully made.
MAE_RET_DUPLICATE_HANDLER : Request is ignored because it is a duplicate request for the same reqId which is not released yet.
MAE_RET_NOT_FOUND         : Requested subject does not exist.

8. MAE_RET code for subject release
MAE_RET_SUCCESS           : Release is successfully made.
MAE_RET_NOT_FOUND         : Subject for this release does not exist.
                                                   Or request is ignored because there is no corresponding request existing.
*/


//////////////////////////////////////////////////////////////////////////
//[Conflict check subject]
/*
 Note : Because of the limit from using this subject,  it does not support auto listener
 */
//1.subject name
#define        RES_CONFLICT_SBJ "ResConflictSBJ" // concurrent check subject

/*2.subject status: In RES_CONFLICT_SBJ.*/

// Status Integer Field
//------------------------------------------------------------------
//|Reserved Bits|                             ...| Group 1 |Group 0 |
//------------------------------------------------------------------
//31          28 27                             8 7       4 3       0

/*
    A: We use the normal enum variable to set status(Do not add the base of specific group).
    B: Limitation, it does not use subject center's auto-listener and set the table in sujbecttbl.c.
    C
      c.1: Every Subgroup use only 4 bits in Status Bit. And the group created earlier occupy the less significant position.
      c.2: Each subgroup in RESOURCE_CONFILICT Subject, They must use the status number less than 15.
      c.3: Because of the reserved Bits28~Bit31 in Integer to present Status used in subject center,so totally it could conclude 7 groups.
           In the other words, we don't use the most significant 4 bits in status integer.
  */

enum
{
    //The Staus' enum number setting must be less than 15.
    SBJ_MEMORY_LOAD_LOW = 0,
    SBJ_MEMORY_LOAD_NORMAL = 1,
    SBJ_MEMORY_LOAD_HIGH = 2,
    SBJ_MEMORY_LOAD_OVERLOAD = 3
};

//3.request id
/*
----------------------------------------------------
|3 Mark Bits|                                       |
----------------------------------------------------
31         29                                      0
*/
#define TOTAL_GROUPS_NUM 7
//In the Integer to show request id, the most significant 3 bits are used as the group mask.
#define GROUP_MASK_BIT_POS 29
//How many status bits to be used in the Status integer.
#define STATUS_BITS_EACH_GROUP_USED_AMOUNT 4
//Because of 4 bits used for each group, its limit is 0xF.
#define GROUP_STATUS_LIMIT_NUMBER 0xF

#define SBJ_GROUP_SPLIT(i) ((i) << GROUP_MASK_BIT_POS)
#define SBJ_GROUP_SPLIT_REVERSE(i) ((u32)((i) >> GROUP_MASK_BIT_POS))
#define RES_CONFLICT_SBJ_GROUP0   SBJ_GROUP_SPLIT(0x0U) //RES_CONFLICT SUBJECT
#define RES_CONFLICT_SBJ_GROUP1   SBJ_GROUP_SPLIT(0x1U) //For CPU-Performance  SUBJECT
#define RES_CONFLICT_SBJ_GROUP2   SBJ_GROUP_SPLIT(0x2U) //Not Used
#define RES_CONFLICT_SBJ_GROUP3   SBJ_GROUP_SPLIT(0x3U) //Not Used
#define RES_CONFLICT_SBJ_GROUP4   SBJ_GROUP_SPLIT(0x4U) //Not Used
#define RES_CONFLICT_SBJ_GROUP5   SBJ_GROUP_SPLIT(0x5U) //Not Used
#define RES_CONFLICT_SBJ_GROUP6   SBJ_GROUP_SPLIT(0x6U) //Not Used

//If you want to use ReqId as the index, this macro must be used.
#define GET_SPECIFIC_GROUP_IDX(VAR,WHICH_GROUP) ((VAR) - (WHICH_GROUP))
//When the request id is passed in, then use this GET_SPECIFIC_GROUP_IDX macro to identify the specific group.
#define SBJ_GET_GROUP_MASK(v) ((v) & (0x7U << GROUP_MASK_BIT_POS))
//In Subscribe's Listener, this macro could be used to take out the specific status in the pSbjStatus
#define GET_STATUS_FROM_GROUP(nSbjStatus, nGroup)   (((nSbjStatus) >>  (STATUS_BITS_EACH_GROUP_USED_AMOUNT*(SBJ_GROUP_SPLIT_REVERSE(nGroup)))) & GROUP_STATUS_LIMIT_NUMBER)




typedef enum
{
    REQ_CONCURRENT_START = RES_CONFLICT_SBJ_GROUP0,
    REQ_CONCURRENT_BT_ON           = SRVCOMMON_RES__BLUETOOTH_POWERON,               /* Bluetooth Power On */
    REQ_CONCURRENT_BT_OPP          = SRVCOMMON_RES__BLUETOOTH_OBJECTPUSHPROFILE,     /* Bluetooth Object Push Profile (OPP) */
    REQ_CONCURRENT_VIDEO_PLAYBACK  = SRVCOMMON_RES__VIDEO_PLAYBACK,                  /* Video Playback */
    REQ_CONCURRENT_VIDEO_RECORDING = SRVCOMMON_RES__VIDEO_RECORDING,                 /* Video Recording */
    REQ_CONCURRENT_IMAGE_CAPTURE   = SRVCOMMON_RES__IMAGE_CAPTURE,                   /* Image Capture */
    REQ_CONCURRENT_GAME_EMU        = SRVCOMMON_RES__GAME_EMU,                        /* Game */
    REQ_CONCURRENT_CAMERA_PREVIEW  = SRVCOMMON_RES__CAMERA_PREVIEW,                  /* Camera Preview */
    REQ_CONCURRENT_AUDIO_PLAYBACK  = SRVCOMMON_RES__AUDIO_PLAYBACK,                  /* Audio Playback */
    REQ_CONCURRENT_USB_PCCAM       = SRVCOMMON_RES__USB_PCCAM,                       /* PC-Cam */
    REQ_CONCURRENT_FM_RECORDING    = SRVCOMMON_RES__FM_RECORDING,                    /* FM Recording */
    REQ_CONCURRENT_CAMERA_USE, /*Use REQ_CONCURRENT_CAMERA_USE means use REQ_CONCURRENT_VIDEO_RECORDING,
                                                                  REQ_CONCURRENT_IMAGE_CAPTURE, REQ_CONCURRENT_CAMERA_PREVIEW at the same time*/
    REQ_CONCURRENT_END,
    REQ_CONCURRENT_NUM = (REQ_CONCURRENT_END - REQ_CONCURRENT_START),
} ConcurrentSection_e;


typedef enum
{
    REQ_MEMORYLOAD_START = RES_CONFLICT_SBJ_GROUP1,
    REQ_MEMORYLOAD_A2DP = REQ_MEMORYLOAD_START,
    REQ_MEMORYLOAD_WAP,
    REQ_MEMORYLOAD_MMS,
    REQ_MEMORYLOAD_MODEM,

    REQ_MEMORYLOAD_END,
    REQ_MEMORYLOAD_NUM = (REQ_MEMORYLOAD_END - REQ_MEMORYLOAD_START),
} MemoryLoadReq_e;
//4.variable
//As the same as request id


//5.Data type
typedef struct MemoryLoadInfo_t_
{
    boolean aMemReqStatus[REQ_MEMORYLOAD_NUM];
} MemoryLoadInfo_t;


typedef struct MemoryLoadData_tag
{

    u32 nMemoryLoad;
    MemoryLoadInfo_t tMemLoadInfo;
    MemoryLoadReq_e eLastReleaseID;
} MemoryLoadData_t;

typedef struct HwLimitData_tag
{

    s32 nLastIdx;
    ConcurrentSection_e eConSection[REQ_CONCURRENT_NUM];
}HwLimitData_t;

typedef struct ResConflictData_tag
{
    HwLimitData_t tHwLimit;
    MemoryLoadData_t tMemLoad;
    u32 nLastStatus;
    boolean bCreateSuccess[TOTAL_GROUPS_NUM];
}ResConflictData_t;


//6.handler function
/*Important:1. If you want to get nVariable to pass to the correct group. Use "SBJ_GET_GROUP_MASK"*/
/*Important:2. If you want to set pSbjStatus. Use "_AssignGroupStatus". */
/*Important:3. If you want to use nVariable(ReqId) as the index. Use "GET_SPECIFIC_GROUP_IDX". Except that RES_CONFLICT_SBJ_GROUP0 might use it or not. */
MAE_Ret ResConflictSubjectHandler
(
    SubjectAction_e eSubjectAction,
    u32 variable,
    void *pSubjectData,
    SubjectStatus_e *pSbjStatus
);

void ResConflictSubjectDefListener
(
    char *pSbjName,
    SubjectStatus_e eSbjStatus,
    void *pUser
);

boolean DetectResConflictStatusChanged(u32 nSbjStatus, u32 nWhichGroup);


/*
7. MAE_RET code for subject request
MAE_RET_SUCCESS           : Request is successfully made.
MAE_RET_DUPLICATE_HANDLER : Request is ignored because it is a duplicate request for the same reqId which is not released yet.
MAE_RET_NOT_FOUND         : Requested subject does not exist.
MAE_RET_BAD_PARAM
MAE_RET_CONFLICT_NOT_INDICATED,//Means that don't notify users while encounter conflict. Ex: Camera is using, BT OPP cannot run because of conflict => don't show dialog
MAE_RET_CONFLICT_BT_ON, //Confict with BT ON
MAE_RET_CONFLICT_OPP, //Confict with BT OPP
MAE_RET_CONFLICT_EMU, //Confict with EMU Game
MAE_RET_CONFLICT_VIDEO_PLAYBACK, //Confict with Video playing


8. MAE_RET code for subject release
MAE_RET_SUCCESS           : Release is successfully made.
MAE_RET_NOT_FOUND         : Subject for this release does not exist.
                                                   Or request is ignored because there is no corresponding request existing.
*/



//////////////////////////////////////////////////////////////////////////
#if defined(__APP_MMI_CHECKDISK__)
//[CheckDisk unblocking subject]
//1.subject name
#define	CHECKDISK_STATUS_SBJ "CheckDiskStatus"

//2.subject status: bit-aligned by using SBJSTS(a)
enum
{
    SBJ_CHECKDISK_UNBLOCK = SBJSTS(0),
    SBJ_CHECKDISK_CHECKDISK_NAND = SBJSTS(1),//check disk NAND
	SBJ_CHECKDISK_CHECKDISK_SD1 = SBJSTS(2),//check disk SD1
	SBJ_CHECKDISK_CHECKDISK_SD2 = SBJSTS(3),//check disk SD2
    SBJ_CHECKDISK_FORMAT_NAND = SBJSTS(4),//format NAND
	SBJ_CHECKDISK_FORMAT_SD1 = SBJSTS(5),//format SD1
	SBJ_CHECKDISK_FORMAT_SD2 = SBJSTS(6),//format SD2
};

#define SBJ_CHECKDISK_CHECKDISK_MODE(SubjectStatus) ((SBJ_CHECKDISK_CHECKDISK_NAND  == SubjectStatus) || (SBJ_CHECKDISK_CHECKDISK_SD1 == SubjectStatus) || (SBJ_CHECKDISK_CHECKDISK_SD2 == SubjectStatus))
#define SBJ_CHECKDISK_FORMAT_MODE(SubjectStatus) ((SBJ_CHECKDISK_FORMAT_NAND  == SubjectStatus) || (SBJ_CHECKDISK_FORMAT_SD1 == SubjectStatus) || (SBJ_CHECKDISK_FORMAT_SD2 == SubjectStatus))
#define SBJ_CHECKDISK_ALL	(SBJ_CHECKDISK_CHECKDISK_NAND|SBJ_CHECKDISK_CHECKDISK_SD1|SBJ_CHECKDISK_CHECKDISK_SD2|SBJ_CHECKDISK_FORMAT_NAND|SBJ_CHECKDISK_FORMAT_SD1|SBJ_CHECKDISK_FORMAT_SD2)

//3.request id
enum
{
    REQ_CHECKDISK
};

//4.variable
//The same as status enum

//5.Data type

typedef struct CheckDiskData_tag
{
    u32 nCheckDiskDescr;
    u8 nOpType;
} CheckDiskData_t;

//6.handler function
MAE_Ret CheckDiskSubjectHandler
(
    SubjectAction_e eSubjectAction,
    u32 variable,
    void *pSubjectData,
    SubjectStatus_e *pSbjStatus
);

void CheckDiskSubjectDefListener
(
    char *pSbjName,
    SubjectStatus_e eSbjStatus,
    void *pUser
);

u32 CheckDiskSubjectGetInfoHandler(char* pSubjectName, void *pUser);

/*
7. MAE_RET code for subject request
MAE_RET_SUCCESS           : Request is successfully made.
MAE_RET_DUPLICATE_HANDLER : Request is ignored because it is a duplicate request for the same reqId which is not released yet.
MAE_RET_NOT_FOUND         : Requested subject does not exist.

8. MAE_RET code for subject release
MAE_RET_SUCCESS           : Release is successfully made.
MAE_RET_NOT_FOUND         : Subject for this release does not exist.
                                                   Or request is ignored because there is no corresponding request existing.
*/

#endif

//////////////////////////////////////////////////////////////////////////
//==========Interface&Function=============

//////////////////////////////////////////////////////////////////////////
#endif	//__MMI_SUBJECT_H__



