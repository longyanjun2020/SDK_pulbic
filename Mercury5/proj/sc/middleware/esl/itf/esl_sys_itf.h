/**
 *
 * @file    esl_sys_itf.h
 *
 * @brief   This file defines the Enahcned Service Layer of system interface
 *
 * @author  Gary Lu
 * @version $Id: esl_sys_itf.h 19811 2009-01-05 08:09:29Z pauli.leong $
 *
 */
#ifndef __ESL_SYS_ITF_H__
#define __ESL_SYS_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"
#include "sys_vm_dbg.ho"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_SYS_ITF__
#define DefExtern
#else
#define DefExtern extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/**
 *  @brief The enumeration defines the return code of the amera interface function.
 */
typedef enum{
  ESL_SYS_OK,               /**< Function complete successfully */ 
  ESL_SYS_FAIL,             /**< Function fail */
  ESL_SYS_PARAM_ERROR,      /**< The input parameter is wrong */
  ESL_SYS_MEM_ALLOC_ERROR,  /**< Can not allocate available memory from OS */
  ESL_SYS_REJECT,           /**< Request reject because of other function's confliction */
  ESL_SYS_ABORT,            /**< Request abort because of incorrect sequence */  
  ESL_SYS_TIMEOUT           /**< Request command to MMP is no response */
} esl_SysErrCode_e;

/**
 *  @brief The enumeration defines the firmware type of every mulitmedia functions.
 */
typedef enum{
  ESL_SYS_FW_BASIC,    /**< Basic FW */ 
  ESL_SYS_FW_VDO_H263, /**< Video -H.263 playing FW */  
  ESL_SYS_FW_VDO_H264, /**< Video -H.264 playing FW */  
  ESL_SYS_FW_VDO_IPTV, /**< Video -IPTV playing FW */ 
} esl_SysFW_e;

#if 0 // This funciton is replaced by MDL cpu
/**
 *  @brief The enumeration defines the requested CPU speed.
 */
typedef enum{
  ESL_SYS_FAST,       /**< Fast CPU speed 158 Mhz */ 
  ESL_SYS_SLOW,       /**< Fast CPU speed 26 Mhz */  
  ESL_SYS_UNKNOWN,    /**< Unknow CPU speed */  
} esl_SysSpeed_e;
#endif

/**
 *  @brief The structure defines the current status of MMP
 */
typedef enum {
  ESL_SYS_MMP_ACTIVE,    /**< MMP Active mode */
  ESL_SYS_MMP_BYPASS,    /**< MMP Bypass mode */
  ESL_SYS_MMP_PWR_DOWN,  /**< MMP Power Down mode */
  ESL_SYS_MMP_KICK,      /**< MMP Kick */
} esl_SysMmpStatus_e;

#if 0 // This funciton is replaced by MDL cpu
/**
 *  @brief The structure defines the CPU speed request function
 */
typedef enum {
  ESL_SYS_MMI_REQ        = 0x00000001,    /**< MMI function speed profile request */
  ESL_SYS_MMP_REQ        = 0x00000002,    /**< MMP function speed profile request */
  ESL_SYS_DEVICE_REQ     = 0x00000004,    /**< GPD device function speed profile request */
  ESL_SYS_IMGDECODE_REQ  = 0x00000008,    /**< Image codec function speed profile request */
  ESL_SYS_VFS_REQ        = 0x00000010,    /**< File System function speed profile request */
  ESL_SYS_SDK_REQ        = 0x00000020,    /**< SDK service speed profile request */
  ESL_SYS_BT_REQ         = 0x00000040,    /**< BT service speed profile request */
  ESL_SYS_IPTV_REQ       = 0x00000080,    /**< IPTV service speed profile request */
  ESL_SYS_RAI_ACCESS_REQ = 0x00000100,    /**< RAI access speed profile request */
  ESL_SYS_DSR_REQ        = 0x00000200,    /**< DSR function speed profile request */  
  ESL_SYS_MMIEXT_REQ     = 0x00000400     /**< MMIExt function speed profile request */
#ifdef __AUDIOCODEC__ 
 ,ESL_SYS_DECODE_REQ     = 0x00000800     /**< Decode function speed profile request */  
#endif
#if defined(__WLAN_DRV__)
 ,ESL_SYS_WIFI_REQ       = 0x00001000     /**< Wifi function speed profile request */  
#endif
} esl_SysFunReq_e;
#endif

/**
 *  @brief The enumeration defines type of the system notification.
 */
typedef enum {
  ESL_SYS_NOTIFY_MMP_RESET = 0,       /**< Notify when Multimedia processor reset                 */

  ESL_SYS_NOTIFY_EFS_CRASH,           /**< in B2, M3 will not trigger this event again            */
  ESL_SYS_NOTIFY_EFS_MOUNT_OK,        /**< would be replaced by ESL_SYS_NOTIFY_CARD_DEVICE_CRASH  */
  ESL_SYS_NOTIFY_EFS_MOUNT_FAIL,      /**< would be replaced by ESL_SYS_NOTIFY_CARD_DEVICE_FIXED  */

  ESL_SYS_NOTIFY_CARD_DEVICE_CRASH,   /**< indicate MMI something wrong in CARD FAT device, need MMI to fix by format operation
                                           NOTE: if MMI does not do anything, there is a hardware limitation will cause target
                                                 can not detect SD card at next boot-up                                         */
  ESL_SYS_NOTIFY_CARD_DEVICE_FIXED,   /**< indicate MMI the crashed CARD FAT has been fixed, MMI can use it again               */
  ESL_SYS_NOTIFY_NAND_DEVICE_CRASH,   /**< indicate MMI something wrong in NAND FAT device, need MMI to fix by format operation */
  ESL_SYS_NOTIFY_NAND_DEVICE_FIXED,   /**< indicate MMI the crashed NAND FAT has been fixed, MMI can use it again               */
  ESL_SYS_NOTIFY_ALL
} esl_SysNotifyType_e;


/**
 *  @brief The enumeration defines the action for command timeout
 */
typedef enum {
  ESL_SYS_RESET_MMP,
  ESL_SYS_TIMEOUT_EXCEPTION,
} esl_SysCmdTimeOutAction_e;


/*
 *  @brief The enumeration defines mode of SD card.
 */
typedef enum {
  ESL_SYS_NO_CARD = 0,  /**< No SD Card Insert                            */
  ESL_SYS_UNKNOWN_MODE, /**< SD Card Status is Unknown                    */
  ESL_SYS_1_BIT_MODE,   /**< SD Card is running under 1-bit mode, slowly  */
  ESL_SYS_4_BIT_MODE,   /**< SD Card is running under expected 4-bit mode */
} esl_SysCardMode_e;


/**
 *  @brief The sturcture defines the MMP system date and time.
 */
typedef struct {
  u16   year;    /**< Year   */
  u8    month;   /**< Month  */
  u8    day;     /**< Day    */
  u8    hour;    /**< Hour   */
  u8    minute;  /**< Minute */
  u8    second;  /**< Second */
} esl_SysDateTime_t;

/**
 *  @brief The sturcture defines the MMP register access information
 */
typedef struct
{
  u32  addr;    /**< MMP address */
  u16  *data;   /**< MMP data    */
  u32  len;     /**< MMP READ/WRITE data length  */
  bool isWr;    /**< Register READ/WRITE control */
} esl_SysDbgInfo_t;

/**
 *  @brief The sturcture defines the MMP bist test information
 */
typedef struct
{
  u32  bistStatus;     /**< MMP bist status */
  u32  bistInfo[2];    /**< MMP bist information */
} esl_SysBistInfo_t;

/**
 *  @brief The sturcture defines the MMP capability information
 */
typedef struct
{
  u8  *pCapBuf; /**< Capability information */
  u32 bufSize;  /**< Buffer size */
} esl_SysCapInfo_t;

/**
 *  @brief The sturcture defines the return value for application layer (MMI) query.
 */
typedef struct{
  union {
    esl_SysCapInfo_t sysCapInfo;     /**< MMP capability buffer */
  }param;  
} esl_SysInfo_t;

/**
 *  @brief The sturcture defines the notificaiton structure for application layer (MMI).
 */
typedef struct {
  esl_SysNotifyType_e  notifyTyp;    /**< Type of system notification */
} esl_SysNotifyInfo_t;

/**
 *  @brief Notification function, Application needs to provide the function entry 
 *
 * @param senderID      : Sender task id. 
 * @param userValue      : Reference value for indicating different sender in same task or check msg response.
 * @param pVdoNotifyInfo : Notified information returned by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_SysNotifyCb)(u16 senderID, u32 userValue, esl_SysNotifyInfo_t *pSysNotifyInfo);

/**
 *  @brief Call back function, MMI need to provide the function entity 
 *
 * @param senderID      : Sender task id. 
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param status        : The status return by Multimedia task to know process success or fail.
 * @param pCamGetInfo   : Query data return by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_SysCb)(u16 senderID, u32 userValue, esl_SysErrCode_e errCode, esl_SysInfo_t *pSysGetInfo);

/**
 *  @brief Callback informatoin structure supported for application layer (MMI)
 */
typedef struct{
  u16        senderID;  /**< Sender ID */    
  u32        userValue; /**< Reference value for indicating different sender in same task or check msg response. */
  esl_SysCb  pfnCb;     /**< Call back function that called by Media task after process finished. */
} esl_SysCb_t;

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct{
  u16              senderID;   /**< Sender ID */     
  u32              userValue;  /**< Reference value for indicating different sender in same task or check msg response. */
  esl_SysNotifyCb  pfnNotifyCb;/**< Notification call back function that called by Media task after receiving the notification. */
} esl_SysNotifyCb_t;


/**
 *  @brief Call back function, MMI need to provide the function entity to get the system date and time.
 *
 * @param None
 *
 * @return None
 */
typedef void (*esl_SysGetDateTimeCB)(esl_SysDateTime_t *pSysDateTime);


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/



#endif /* __ESL_SYS_ITF_H__ */

