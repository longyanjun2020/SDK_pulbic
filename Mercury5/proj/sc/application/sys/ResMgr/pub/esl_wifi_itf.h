/**
 *
 * @file    esl_wifi_itf.h
 *
 * @brief   This module defines the WiFi Service Layer interface of WiFi serivce
 *
 * @author  Cooper chiou
 * @version $Id: esl_wifi_itf.h 13504 2009-07-28 13:42:10Z cooper.chiou $
 *
 */
#ifndef __ESL_WIFI_ITF_H__
#define __ESL_WIFI_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_WIFI_ITF__
#define DefExtern
#else
#define DefExtern extern
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

#define EMA_LEVEL_WIFI          _CUS2 | LEVEL_17

#define ESL_WIFI_DATA_LEN       (512)

#define ESL_MAX_CERT_PATH_LEN   (266) // This value must be the same as FILEMGR_MAX_FILEPATH_SIZE

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The enumeration defines the return code of the WiFi interface
 */
typedef enum
{
    ESL_WIFI_OK,                        /**< Function complete successfully     */
    ESL_WIFI_FAIL,                      /**< Function common fail               */
    ESL_WIFI_PARAM_ERROR,               /**< The input parameter is wrong       */
    ESL_WIFI_MEM_ALLOC_ERROR,           /**< Can not allocate memory from OS    */
    ESL_WIFI_REJECT,                    /**< Request rejected because of other function's confliction */
    ESL_WIFI_ABORT,                     /**< Request aborted because of incorrect sequence */
    ESL_WIFI_TIMEOUT,                   /**< Request no response timeout, this error is returned by call back function */
    ESL_WIFI_FIFO_INIT_FAIL             /**< WiFi FIFO initialize failed        */

} esl_WifiErrCode_e;

/**
 *  @brief The enumeration defines the command of WiFi WPA
 */
typedef enum
{
    ESL_WIFI_CMD_OPEN = 0x00043001,      /**< Open WiFi interface and be ready for connection                       */
    ESL_WIFI_CMD_STOP,                   /**< Stop WiFi interface. RF should be turn off to save power              */
    ESL_WIFI_CMD_RESET,                  /**< Reset WiFi hardware and restart software module                       */
    ESL_WIFI_CMD_SET_SCAN,               /**< Ask WiFi driver scan nearby Access Point                              */
    ESL_WIFI_CMD_CONNECT,                /**< Specifies SSID or BSSID to connect                                    */
    ESL_WIFI_CMD_DISCONNECT,             /**< Disconnect current Access Point                                       */
    ESL_WIFI_CMD_SET_CONFIGURATION,      /**< Set WiFi configuration                                                */
    ESL_WIFI_CMD_POWER_SAVING,           /**< Enable Power saving                                                   */
    ESL_WIFI_CMD_GET_SCAN_RESULT,        /**< Ask WiFi driver to report detailed information of nearby Access Point */
    ESL_WIFI_CMD_GET_CONFIGURATION,      /**< Get WiFi configuration                                                */
    ESL_WIFI_CMD_GET_BSS,                /**< Get WiFi BSS                                                          */
    ESL_WIFI_CMD_STOP_SCAN,              /**< Ask Wifi hardware to stop scan nearby Access Point                    */
    ESL_WIFI_CMD_SET_BT_STATUS,          /**< Set BT status                                                         */
    ESL_WIFI_CMD_SET_FW_TEST,            /**< Set WiFi fimware test                                                 */
    ESL_WIFI_CMD_GET_FW_TEST_RESULT,     /**< Get WiFi fimware test result                                          */
    ESL_WIFI_CMD_SET_HW_REG,             /**< Set hardware register                                                 */
    ESL_WIFI_CMD_GET_HW_REG,             /**< Get hardware register                                                 */
    ESL_WIFI_CMD_SET_RXFILTER,           /**< Set rx filter                                                         */
    ESL_WIFI_CMD_GET_RXFILTER_RESULT,    /**< Get rx filter result                                                  */
    ESL_WIFI_CMD_GET_AQU_VER,            /**< Get Aquarius SW version                                               */
    ESL_WIFI_CMD_SET_GSM_STATUS,         /**< Set GSM/GPRS status                                                   */
    ESL_WIFI_CMD_SET_RF_REG,             /**< Set RF register                                                   */
    ESL_WIFI_CMD_GET_RF_REG,             /**< Get RF register                                                 */
} esl_WifiCmd_e;

/**
 *  @brief The enumeration defines the WIFI status change event.
 */
typedef enum
{
    ESL_WIFI_EVENT_CONNECT_FAIL = 0x00044001,   /**< Connection Timeout             */
    ESL_WIFI_EVENT_CONNECTED,                   /**< Connection is set up           */
    ESL_WIFI_EVENT_DISCONNECTED,                /**< Disconnect with AP             */
    ESL_WIFI_EVENT_ROMMING,                     /**< The signal of current connected AP is too weak and another AP with stronger signal is found */
    ESL_WIFI_EVENT_SCAN_DONE,                   /**< Wifi scan done, need to get scan result             */
    ESL_WIFI_EVENT_PASSWORD_FAIL,               /**< Connection failed due to the wrong password         */
    ESL_WIFI_EVENT_FW_TEST_DONE,                /**< WiFi firmware test done        */
    ESL_WIFI_EVENT_CERT_FAIL,                   /**< 0x00044008 */
    ESL_WIFI_EVENT_UNKNOWN_ISSUER,              /**< 0x00044009 */
    ESL_WIFI_EVENT_UNTRUSTED_ROOT,              /**< 0x0004400A */
    ESL_WIFI_EVENT_INVALID_TIME,                /**< 0x0004400B */
    ESL_WIFI_EVENT_INVALID_SIGNATURE,           /**< 0x0004400C */
    ESL_WIFI_EVENT_REVOKED,                     /**< 0x0004400D */
    ESL_WIFI_EVENT_INVALID_USAGE,               /**< 0x0004400E */
    ESL_WIFI_EVENT_FAIL_UNKNOW                  /**< 0x0004400F */
} esl_WifiEvent_e;

/**
 *  @brief The enumeration defines type of the WiFi notification.
 */
typedef enum
{
    ESL_WIFI_NOTIFY_QUEUE_LOW_WATERMARK,          /**< Notify when queue reach low watermark    */
    ESL_WIFI_NOTIFY_QUEUE_HIGH_WATERMARK,         /**< Notify when queue reach high watermark   */
    ESL_WIFI_NOTIFY_FREE_LOW_WATERMARK,           /**< Notify when free buffer reach low watermark   */
    ESL_WIFI_NOTIFY_FREE_HIGH_WATERMARK,          /**< Notify when free buffer reach high watermark   */
    //ESL_WIFI_NOTIFY_WPA_EVENT,                  /**< Notify when receive WPA event      */
    ESL_WIFI_NOTIFY_WIFI_STATUS_UPDATE,           /**< Notify when WIFI status change      */
    ESL_WIFI_NOTIFY_MAX

} esl_WifiNotifyType_e;


/**
 *  @brief The sturcture defines WPA data information.
 */
typedef struct
{
    u32     dataLen;                    /**< Data length    */
    u8      *pData;                     /**< Data pointer   */
} esl_WifiData_t;


/**
 *  @brief Wifi WPA command parameters
 */
typedef struct
{
    esl_WifiCmd_e       cmdId;          /**< WPA command id         */
    esl_WifiData_t      cmdData;        /**< WPA command data       */
    esl_WifiData_t      evtData;        /**< WPA received event data       */

} esl_WifiCmd_t;


/**
 *  @brief Wifi WPA receive event parameters
 */
typedef struct
{
    esl_WifiData_t      evtData;        /**< WPA received event data       */

} esl_WifiEvent_t;


/**
 *  @brief The sturcture defines the FIFO queue ID.
 */
typedef struct
{
    u32                 txQId;          /**< TX queue id            */
    u32                 rxQId;          /**< RX queue id            */
} esl_WifiQId_t;


/**
 *  @brief The sturcture defines the return information for application layer (MMI).
 */
typedef struct
{
    esl_WifiCmd_t        cmdData;
    esl_WifiEvent_t      evtData;
    esl_WifiQId_t        QId;
} esl_WifiInfo_t;


#if 0
/**
 *  @brief Wifi WPA connect parameters
 */
typedef struct
{
    esl_WifiCmd_e       cmdId;          /**< WPA command id         */
    int                 ssid[40];       /**< index in scan list         */
    int                 sec_type;       /**< specific security type NONE, WEP40, WEP104, WPA or WPA2         */
    int                 def_key;        /**< which key is used as default key         */
    union
    {
      char wep[4][16];                  /**< key context         */
      char psk[64];
    } key;
    esl_WifiData_t      evtData;        /**< WPA received event data       */
} esl_WifiConnectData_t;
#endif


/**
 *  @brief Wifi WPA connect parameters
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u8   ssid[32];       /**< index in scan list         */
    u32  ssid_len;       /**< SSID length, 0 => use any ssid         */
    u32  security;       /**< NONE, WEP, WPA, WPA2         */
    u32  keyidx;         /**< key index 0~3         */
    u8   key[64];        /**< key context, WEP40 => 5, WEP104 =>13, WPA and RSN => 8~64        */
    u32 nCaRaiId;        /**< Ca RAI id        */
    u32 nClientRaiId;    /**< Client RAI id    */
    u16 nCaRaiSize;      /**< Ca RAI size     */
    u16 nClientRaiSize;  /**< Client RAI size */
    u8   bssid[6];       /**< BSSID         */
}esl_WifiConnectData_t;

/**
 *  @brief Wifi WPA set configuration parameters
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u8 own_addr[6];    /* own MAC address */
    u8 pad[2];         /* for alignment   */
}esl_WifiSetConfiguration_t;

/**
 *  @brief Wifi WPA set BT status
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u32 u32BtStatus;    /* the BT status */
}esl_WifiSetBTStatus_t;

/**
 *  @brief Wifi WPA fw test config
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u32 tx_rate;            // Tx rate for test packet [ 0 ~ 15]
    u32 channel;            // Test channel number [1 ~ 14]
    u32 pkt_len;            // Test packet length [0 ~ 1528]
    u32 pkt_num;            // Number of packet to send [0 ~ 0xffffffff]
    s32 pga;                // pga [-1, 0 ~ 30]
    u32 option;             // #define FW_TST_CONT_TX 0x01
                            // #define FW_TST_PROD_TX 0x02
                            // #define FW_TST_PROD_RX 0x04
    u8  dest_mac[6];        // destination MAC address
    u8  src_mac[6];         // source MAC address
    u8  pad[2];
}esl_WifiFwTstConf_t;

/**
 *  @brief Wifi WPA fw test results
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u32 total_pkt;          // the number that how many packets are sent
    u32 recv_pkt;           // the number that how many packets are received
    u32 fail_pkt;           // the number that how many packets are failed to be received
    u32 per;                // Packet error rate
    u32 oppo_pkt;
}esl_WifiFwTstResult_t;

/**
 *  @brief Wifi WPA hw register
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u8  bank;               // register bank
    u8  reg;                // register address
    u16 data;               // register value
}esl_WifiHwReg_t;

/**
 *  @brief Wifi WPA rx filter
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u32 rate;
    u32 len;
    u32 chan;
    u8 filtermac[6];
    u8 pad[2];
}esl_WifiRxFilter_t;

/**
 *  @brief Wifi WPA rx filter result
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u32 rx_pkt;
    u32 rx_fcsfitpkt;
    u32 rx_fcsfailpkt;
    u32 rx_avgagc;
    u32 rx_sdagc;
    u32 rx_agc_max;
    u32 rx_agc_min;
}esl_WifiRxFilterResult_t;

/**
 *  @brief Wifi WPA get Aquarius version
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u32 aqu_ver;           /* the Aquarius version   */
    u32 supplicant_ver;    /* the supplicant version */
}esl_WifiGetAQUVer_t;

/**
 *  @brief Wifi WPA set GSM/GPRS status
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u32 u32GSMStatus;    /* the GSM/GPRS status */
}esl_WifiSetGSMStatus_t;


/**
 *  @brief Wifi RF Register
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u8 reg;
    u8 val;
    u8 pad[2]; //is this right??
}esl_WifiRfReg_t;


/**
 *  @brief Wifi Tx Sin Tone
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u32 txsintone;
}esl_WifiTxSinTone_t;


/**
 *  @brief Wifi AQU Memory
 */
#ifdef __GNUC__
typedef struct __packed
#else
typedef __packed struct
#endif
{
    u32 addr;
    u32 val;
    u32 len;
}esl_WifiAQUMem_t;


/**
 * @brief Call back function, Application needs to provide the function entry
 *
 * @param senderID      : Sender task ID
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param errCode       : The error return by Multimedia task to know process success or fail.
 * @param pWifiInfo     : Query data return by WiFi
 *
 * @return None
 */
typedef void (*esl_WifiCb)(u16 senderID, u32 userValue, esl_WifiErrCode_e errCode, esl_WifiInfo_t *pWifiInfo);


/**
 *  @brief The sturcture defines the notificaiton value for application layer (MMI).
 */
typedef struct
{
    esl_WifiNotifyType_e    notifyType;     /**< Notification type      */
    union {
      u32                     QId;                 /**< Queue id                */
      esl_WifiEvent_e         eventID;             /**< Event id                */
      struct {
        u32                     dataSize;            /**< Data size                */
        esl_WifiCmd_e           cmdId;               /**< Command id                */
      } cmd;
    } notify;
} esl_WifiNotifyInfo_t;


/**
 *  @brief Notification Call back function, MMI need to provide the function entity
 *
 * @param senderID          : Sender task id.
 * @param userValue         : Reference value for indicating different sender in same task or check msg response.
 * @param pWifiNotifyInfo   : Notification value return by WiFi
 *
 * @return None
 */
typedef void (*esl_WifiNotifyCb)(u16 senderID, u32 userValue, esl_WifiNotifyInfo_t *pWifiNotifyInfo);

/**
 * @brief WiFi call back function structure definition
 */
typedef struct
{
    u16             senderID;           /**< Sender task ID */
    u32             userValue;          /**< Reference value for indicating different sender in same task or check msg response. */
    esl_WifiCb      pfnCb;              /**< Call back function that called by WiFi after process finished. */

} esl_WifiCb_t;

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct
{
	u16                 senderID;       /**< Sender task ID         */
	u32                 userValue;      /**< Reference value for indicating different sender in same task or check msg response. */
	esl_WifiNotifyCb    pfnNotifyCb;    /**< Notification call back function that called by WiFi after receiving the notification. */

} esl_WifiNotifyCb_t;


/**
 *  @brief Wifi RegCb parameters
 */
typedef struct
{
    u32                 txQId;          /**< TX queue id                */
    u32                 rxQId;          /**< RX queue id                */
    esl_WifiNotifyCb_t  queueHighWaterCb;    /**< Queue high watermark notify callback    */
    esl_WifiNotifyCb_t  queueLowWaterCb;     /**< Queue Low watermark notify callback     */
    esl_WifiNotifyCb_t  freeHighWaterCb;     /**< Free buffer high watermark notify callback    */
    esl_WifiNotifyCb_t  freeLowWaterCb;      /**< Free buffer Low watermark notify callback     */

} esl_WifiReg_t;

/**
 *  @brief Wifi UnRegCb parameters
 */
typedef struct
{
    u32                 txQId;          /**< TX queue id            */
    u32                 rxQId;          /**< RX queue id            */

} esl_WifiUnReg_t;


/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct
{
    esl_WifiNotifyType_e    notifyType;     /**< Notification type      */
    esl_WifiNotifyCb_t      notifyCb;       /**< Notification callback  */

} esl_WifiRegNotify_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

#if 0
/**
 * @brief Allocate buffer, init FIFO and set queue id to host driver
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
 esl_WifiErrCode_e esl_WifiInitFifo(esl_WifiCb_t *pWifiCb);


/**
 * @brief Release buffer, delete FIFO and set queue id to host driver.
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
 esl_WifiErrCode_e esl_WifiDeleteFifo(esl_WifiCb_t *pWifiCb);
#endif

/**
 * @brief Query queue ID of init FIFO to host driver.
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiQueryQueueID(esl_WifiCb_t *pWifiCb);


/**
 * @brief Send M3 command of start enqueue
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiStartEnqueue(esl_WifiCb_t *pWifiCb);


/**
 * @brief Send M3 command of start enqueue
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiStopEnqueue(esl_WifiCb_t *pWifiCb);


/**
 * @brief Register notify callback function of queue and free buffer watermark to host driver
 *
 * @param pReg                          : WiFi register structure, include tx/rx queue id, queue and free buffer watermark.
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiRegCb(esl_WifiReg_t *pReg, esl_WifiCb_t *pWifiCb);


/**
 * @brief Unregister notify callback function of queue and free buffer watermark to host driver
 *
 * @param pUnReg                        : WiFi unregister structure, include tx/rx queue id.
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiUnRegCb(esl_WifiUnReg_t *pUnReg, esl_WifiCb_t *pWifiCb);

#if 0
/**
 * @brief This function is used to send Wifi WPA OPEN command (no command data, no event data)
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiOpen(esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi WPA STOP command (no command data, no event data)
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiStop(esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi WPA RESET command (no command data, no event data)
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiReset(esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi WPA SET_SCAN command (no command data, no event data)
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiSetScan(esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi WPA GET_SCAN_RESULT command (no command data, with event data).
 *
 * @param pEventData                    : WiFi WPA event structure, include event id, event data
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiGetScanResult(esl_WifiEvent_t *pEventData, esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi WPA CONNECT command (with command data, no event data).
 *
 * @param cmd                           : WiFi WPA Command structure
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiConnect(esl_WifiConnectData_t cmd, esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi WPA DISCONNECT command (no command data, no event data)
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiDisconnect(esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi WPA SET_CONFIGURATION command(with command data, no event data).
 *
 * @param cmd                           : WiFi WPA Command structure, reserved.
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiSetConfiguration(esl_WifiSetConfiguration_t cmd, esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi WPA GET_CONFIGURATION command (no command data, with event data).
 *
 * @param pEventData                    : WiFi WPA event structure, include event id, event data
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiGetConfiguration(esl_WifiEvent_t *pEventData, esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi power saving command (no command data, no event data)
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiPowerSaving(esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi WPA GET_BSS command (no command data, with event data).
 *
 * @param pEventData                    : WiFi WPA event structure, include event id, event data
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiGetBSS(esl_WifiEvent_t *pEventData, esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi STOP_SCAN command (no command data, no event data)
 *
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiStopScan(esl_WifiCb_t *pWifiCb);



/**
 * @brief This function is used to send Wifi WPA command (Open/Stop/Reset/...), and obtained event data (maybe NULL) from callback.
 *
 * @param pCmd                          : WiFi WPA Command structure, include command id, command data
 * @param pEventData                        : WiFi WPA event structure, include event id, event data
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiSendCmd(esl_WifiCmd_t *pCmd, esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to obtain Wifi WPA event ID and data when receive WPA event notify.
 *
 * @param pEventData                        : WiFi WPA event structure, include event id, event data
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiRecvEvent(esl_WifiEvent_t *pEventData, esl_WifiCb_t *pWifiCb);


/**
 * @brief Register notification for WiFi event receiving
 *
 * @param notifyType                    : Notification selected type to register
 * @param notifyCb                      : Notification call back to info MMI when WiFi receivd notification.
 * @param pWifiCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiRegNotify(esl_WifiNotifyType_e notifyType, esl_WifiNotifyCb_t notifyCb, esl_WifiCb_t *pWifiCb);

/**
 * @brief This function is used to send Wifi WPA SET_BT_STATUS command(with command data, no event data).
 *
 * @param cmd                           : WiFi WPA Command structure, reserved.
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiSetBTStatus(esl_WifiSetBTStatus_t cmd, esl_WifiCb_t *pWifiCb);

/**
 * @brief This function is used to send Wifi WPA SET FW TEST command (with command data, no event data).
 *
 * @param cmd                           : WiFi WPA Command structure
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiSetFwTest(esl_WifiFwTstConf_t cmd, esl_WifiCb_t *pWifiCb);

/**
 * @brief This function is used to send Wifi WPA_CMD_GET_FW_TEST_RESULT command (no command data, with event data).
 *
 * @param pEventData                    : WiFi WPA event structure, include event id, event data
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiGetFwTestResult(esl_WifiEvent_t *pEventData, esl_WifiCb_t *pWifiCb);

/**
 * @brief This function is used to send Wifi WPA_CMD_SET_HW_REG command (with command data, no event data).
 *
 * @param cmd                           : WiFi WPA Command structure
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiSetHwReg(esl_WifiHwReg_t cmd, esl_WifiCb_t *pWifiCb);

/**
 * @brief This function is used to send Wifi WPA_CMD_GET_HW_REG command (no command data, with event data).
 *
 * @param pEventData                    : WiFi WPA event structure, include event id, event data
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiGetHwReg(esl_WifiHwReg_t cmd, esl_WifiEvent_t *pEventData, esl_WifiCb_t *pWifiCb);

/**
 * @brief This function is used to send Wifi WPA_CMD_SET_RXFILTER command (with command data, no event data).
 *
 * @param cmd                           : WiFi WPA Command structure
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiSetRxFilter(esl_WifiRxFilter_t cmd, esl_WifiCb_t *pWifiCb);

/**
 * @brief This function is used to send Wifi WPA_CMD_GET_RXFILTER_RESULT command (no command data, with event data).
 *
 * @param pEventData                    : WiFi WPA event structure, include event id, event data
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiGetRxFilterResult(esl_WifiEvent_t *pEventData, esl_WifiCb_t *pWifiCb);

/**
 * @brief This function is used to send Wifi WPA GET_AQU_VER command (no command data, with event data).
 *
 * @param pEventData                    : WiFi WPA event structure, include event id, event data
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiGetAQUVer(esl_WifiEvent_t *pEventData, esl_WifiCb_t *pWifiCb);

/**
 * @brief This function is used to send Wifi WPA SET_GSM_STATUS command(with command data, no event data).
 *
 * @param cmd                           : WiFi WPA Command structure, reserved.
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiSetGSMStatus(esl_WifiSetGSMStatus_t cmd, esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi ESL_WIFI_CMD_SET_RF_REG command (with command data, no event data).
 *
 * @param cmd                           : WiFi WPA Command structure
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiSetRfReg(esl_WifiRfReg_t cmd, esl_WifiCb_t *pWifiCb);


/**
 * @brief This function is used to send Wifi ESL_WIFI_CMD_GET_RF_REG command (no command data, with event data).
 *
 * @param pEventData                    : WiFi WPA event structure, include event id, event data
 * @param pWifiCb                       : Call back structure, include sender ID, userValue and call back function.
 *                                        It uses to send response message that provide by application layer(MMI)
 *                                        to inform application layer(MMI) the process in EMA is success or fail.
 *
 * @return ESL_WIFI_OK                  : Function close request success
 * @return ESL_WIFI_FAIL                : Function close request fail
 * @return ESL_WIFI_PARAM_ERROR         : Incorrect parameter setting
 * @return ESL_WIFI_MEM_ALLOC_ERROR     : Can't allocate available memory from OS
 * @return ESL_WIFI_REJECT              : Request rejected becuase of other function's confliction
 * @return ESL_WIFI_ABORT               : Request aborted becuase of incorrect sequence
 * @return ESL_WIFI_TIMEOUT             : Request no response timeout, this error is returned by call back function
 */
esl_WifiErrCode_e esl_WifiGetRfReg(esl_WifiEvent_t *pEventData, esl_WifiCb_t *pWifiCb);
#endif
#endif /* __ESL_WIFI_ITF_H__ */

