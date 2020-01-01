/**
 * @file mmi_statusbarsrv_priv.h
 *
 * State Machine Service - STATUSBARSRV
 *
 * $Id: mmi_statusbarsrv_priv.h 36192 2009-07-21 15:42:48Z sho.ding $
 */
#ifndef __MMI_STATUSBARSRV_PRIV_H__
#define __MMI_STATUSBARSRV_PRIV_H__

#if defined (__G3D_MMI__)
#define __MMI_STATUSBAR_SUPPORT_POWER_SAVE__
#endif

#include "mmi_mae_common_def.h"
#include "mmi_statusbarsrv.h"
#include "mmi_mae_clock.h"
#include "mmi_mae_clock_types.h"
#include "mmi_mae_vectormodel.h"
#include "mmi_mae_battery.h"
#include "mmi_profilesrv.h"
#include "mmi_common_cfg.h"
#include "mmi_mmsrv.h"
#include "mmi_mae_datamodel.h"
#include "mmi_ccsrv.h"
#include "mmi_accessorysrv.h"
#include "mmi_smssrv.h"
#include "mmi_audioplayersrv.h"
#include "mmi_smstransactionsrv.h"
#include "mmi_simsrv.h"
#include "mmi_btsrv.h"
#include "mmi_fmradiosrv.h"
#include "mmi_cphssrv.h"
#include "mmi_cphssrv_def.h"
#include "mmi_alarmsrv.h"
#include "mmi_cfgsrv.h"
#include "mmi_usbsrv.h"
#include "mmi_vendorsrv.h"
#include "mmi_filemgr.h"
#include "mmi_if_sys.h"
#include "mmi_wlansrv.h"
#include "mmi_socketsrv.h"

#ifdef __MMI_STATUSBAR_SUPPORT_POWER_SAVE__
#include "mmi_coresrv.h"
#endif
#if ((!defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)) || defined(__MMI_STATUSBAR_SUPPORT_MISSED_CALL__) || defined(__MMI_STATUSBAR_SUPPORT_MISSED_CALL_DUAL__))
#include "mmi_calllogsrv.h"
#endif

#ifdef __NCCQQ_MMI__
#include "mmi_qqsrv.h"
#endif


#ifdef __MMS_MMI_CDMMS__
#include "mmi_mmssrv.h"

#define STATUSBAR_MSK_SMS_TRANS     0x01
#define STATUSBAR_MSK_MMS_TRANS     0x02
#endif

#ifdef __EMAIL_MMI__
#include "mmi_emailsrv.h"

#define STATUSBAR_MSK_EMAIL_TRANS   0x04
#endif



//static const u8 nLevelTable[] = { 0, 9, 15, 21, 27 }; //MMI mapping table
//static const u8 nLevelTable[] = { 0, 1, 7, 12, 15, 19 }; //Old XMMI mapping table


#define STATUSBAR_RSSI_MAX_INVALID_COUNT  2  //Max ignored RSSI number
#define STATUSBAR_RSSI_LEVEL_INSENSITIVE  2  //Ignored RxLevel range
#define STATUSBAR_RSSI_MAX_CHANGE_LEVEL   1  //Max allowed changed level.



//#define STATUSBAR_RSSI_LEV_SIZE  sizeof(statusbar_rssi_level_table)/sizeof(statusbar_rssi_level_table[0])\

#define STATUSBAR_WAP_TRANS_TIMER 3000
#define STATUSBAR_M2_RESET_TIMER 1000

//u16 Bit Mask for CC/SS Queue
#define STATUSBAR_CCSSQUEUE_MSK_CC_VOICE 1
#define STATUSBAR_CCSSQUEUE_MSK_CC_VIDEO 2
#define STATUSBAR_CCSSQUEUE_MSK_SS_L1    4
#define STATUSBAR_CCSSQUEUE_MSK_SS_L1CFU 8
#define STATUSBAR_CCSSQUEUE_MSK_SS_L2    16
#define STATUSBAR_CCSSQUEUE_MSK_SS_L2CFU 32

//u16 Bit Mask for WAP/MSG Queue
#define STATUSBAR_WAPMSGQUEUE_MSK_WAP_TRANSMITTING 1
#define STATUSBAR_WAPMSGQUEUE_MSK_MSG_SIMFULL      2
#define STATUSBAR_WAPMSGQUEUE_MSK_MSG_PHONEFULL    4
#define STATUSBAR_WAPMSGQUEUE_MSK_MSG_NEWMSG       8
#define STATUSBAR_WAPMSGQUEUE_MSK_MSG_VOICEMAIL    16
#define STATUSBAR_WAPMSGQUEUE_MSK_MSG_UNREADMSG    32
#define STATUSBAR_WAPMSGQUEUE_MSK_MSG_TRANSMITTING 64
#define STATUSBAR_WAPMSGQUEUE_MSK_MSG_UNREADMSG1    128
#define STATUSBAR_WAPMSGQUEUE_MSK_MSG_UNREADMSG2    256

//u32 Bit Mask for OTHER Queue
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_MEMCARD    1
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_MPLAYER          (1 << 1)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_FMRADIO          (1 << 2)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_USB              (1 << 3)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_BLUETOOTH        (1 << 4)
#ifdef __BLUETOOTH_OBEX_MMI__
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_BLUETOOTH_OBEX   (1 << 5)
#endif // __BLUETOOTH_OBEX_MMI__
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_ALARM            (1 << 6)
#ifndef __MMI_STATUSBAR_SUPPORT_PROFILE_STATUS__
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_HEADSET          (1 << 7)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_SOUND_SILENT     (1 << 8)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_VIBRATE          (1 << 9)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_BT_HEADFREE      (1 << 10)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_BT_HEADSET       (1 << 11)
#ifdef __BLUETOOTH_A2DP_MMI__
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_BT_A2DP          (1 << 12)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_BT_HEADSET_A2DP  (1 << 13)
#endif // __BLUETOOTH_A2DP_MMI__
#endif // !__MMI_STATUSBAR_SUPPORT_PROFILE_STATUS__
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_MPLAYER_PAUSE    (1 << 14)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_CUSTOM_ICON_1    (1 << 15)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_MEMCARD_CONNECT  (1 << 16)
#ifdef __MMI_STATUSBAR_SUPPORT_MISSED_CALL__
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_MISSCALL         (1 << 17)
#endif
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_BLOCKCALL_MASTER	(1 << 18)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_BLOCKCALL_SLAVE	(1 << 19)
#endif
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_CUSTOM_IMAGE     (1 << 20)

#if defined(__APP_MMI_CHECKDISK__)
#define STATUSBAR_OTHERQUEUE_MSK_OTHER_CHECK_DISK       (1 << 21)
#endif

// u16 Bit Mask for memory card access
#define STATUSBAR_MEM_CARD_ACCESS_BY_FILE_MGR		1
#define STATUSBAR_MEM_CARD_ACCESS_BY_DB				2
#define STATUSBAR_MEM_CARD_ACCESS_BY_SDK			4

// u16 Bit Mask for MissCall Queue
#define STATUSBAR_BTQUEUE_MISS_CALL_ON_MASTER	    	1
#define STATUSBAR_BTQUEUE_MISS_CALL_ON_SLAVE 			2


#define BREAKIF_DISPERROR(n,s) {\
                                if(MAE_RET_SUCCESS != n) \
                                {\
                                  LOG_ERROR(MMI_LEVEL_GENERAL, s,n);\
                                  break; \
                                }\
                              }
/*   //use the macro define in "mmi_mae_common_def.h"
#define BREAKIFNULL(p) {\
                         if( NULL == (p))\
                         {\
                            nRetVal = MAE_RET_OUT_OF_MEMORY;\
                            LOG_ERROR(MMI_LEVEL_GENERAL, "{Failed to allocate memory");\
                            break;\
                         }\
                        }
*/
#define STATUSBAR_SETBIT(queue, mask) {\
                                          queue |= mask; \
                                      }

#define STATUSBAR_REMOVEBIT(queue, mask) {\
                                             if(queue & mask) \
                                             { \
                                                 queue ^= mask; \
                                             } \
                                         }
	 
#ifdef __MMI_STATUSBAR_SUPPORT_PROFILE_STATUS__
typedef enum
{
    STATUSBAR_BT_DEVICE_NONE = STATUSBAR_BT_DEVICE_BASE,
    STATUSBAR_BT_DEVICE_HFP_ONLY,
    STATUSBAR_BT_DEVICE_A2DP_ONLY,
    STATUSBAR_BT_DEVICE_HFP_A2DP,
    STATUSBAR_BT_DEVICE_STATUS_NUM
} StatusBar_BT_Device_Status_e;
#endif // __MMI_STATUSBAR_SUPPORT_PROFILE_STATUS__

/**
 * Application structure
 */
typedef struct MMI_STATUSBARSRV_TAG
{
    DECLARE_FUNCTBL(ISTATUSBARSRV);   // function table pointer
    u32 refCnt;     // reference count
    /* Add custom fields below */
#ifdef __MMI_STATUSBAR_SUPPORT_POWER_SAVE__
    ICORESRV    *pICoreSrv;
#endif
    IBattery *pIBattery;
    IUSBSRV *pIUSBSrv;
    IPROFILESRV *pIProfileSrv;
    IMMSRV *pIMMSrv;
#ifdef __MMI_DISPLAY_GPRS_TRAFFIC__
    ISOCKETSRV *pISocketSrv;
#endif
    ICCSRV *pICCSrv;
    ISMI *pSMISrv;
    ISMS *pSMSSrv;
#ifdef __MMS_MMI_CDMMS__
    IMMS *pMMSSrv;
#endif

#ifdef __EMAIL_MMI__
    IEMAILSRV *pEMAILSrv;
#endif

    ITXI *pTXISrv;
    IAUDIOPLAYERSRV *pIMPlayerSrv;
    IACCESSORYSRV *pIAccessorySrv;
#ifdef __BLUETOOTH_MMI__
    IBTSRV *pBTSrv;
#endif
#ifdef __APP_MMI_FM_RADIO__
    FmrSrvHdl_t pIFMRadioSrv;
#endif
    ICPHSSRV *pICPHSSrv;
#ifdef __DUAL_SIM_MMI__
    ISIMSRV *pISIMSrv;
#endif
    //#ifdef __UI_STYLE_MMI_IFONE__
    IALARMSRV *pIAlarmSrv;
    ICFGSrv *pICFGSrv;
    IClock *pIClock;
#if ((!defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)) || defined(__MMI_STATUSBAR_SUPPORT_MISSED_CALL__) || defined(__MMI_STATUSBAR_SUPPORT_MISSED_CALL_DUAL__))
	ICALLLOGSRV *pICallLogSrv;
#endif
	IVENDORSRV  *pVendorSrv;
#ifdef __WLAN_MMI__
	IWLANSRV *pWLANSrv;
#endif

#ifdef __NCCQQ_MMI__
    IQQSRV *pQQSrv;
    StatusBar_QQSrvStatus_e nQQSrvStatus;
#endif

	FileMgrHandleID_t nFileMgrHandle;
#if defined(__DUAL_CARD__)
	FileMgrHandleID_t nFileMgrHandle2;
#endif
    //#endif

    IVectorModel *pIStatusModel; /* Resulting 8 dimensional Vector model which StatusBar Widget listener to*/
    /* Format: {Batt, RSSI, NetworkType, UsrProfile, CC+SS, WAP+MSG, WAP+MSG, Other} */
    ModelListener_t BattModelListener;
    ModelListener_t USBModelListener;
    ModelListener_t ProfileModelListener;
    ModelListener_t AccessoryModelListener;
	ModelListener_t vendorSrvListener;              // Model listener of vendor event
#if (defined(__MMI_STATUSBAR_SUPPORT_MISSED_CALL__) || defined(__MMI_STATUSBAR_SUPPORT_MISSED_CALL_DUAL__))
	ModelListener_t CallLogModelListener;
#endif
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
	ModelListener_t BlockCallModelListener;
#endif
    //#ifdef __UI_STYLE_MMI_IFONE__
    ModelListener_t CFGModelListener;
    ClockListener_t ClockModelListener;
    //#endif
    StatusBar_Batt_e nBattStatus;
#ifdef __DUAL_BATT_MMI__
	StatusBar_Batt_e nBattStatus_Slave;
#endif
#ifdef __MMI_STATUSBAR_SUPPORT_PROFILE_STATUS__
    StatusBar_ProfileStatus_e eProfileStatus; /* Profile Status */
    StatusBar_BT_Device_Status_e eBTStatus; /* BT Status */
#else
    StatusBar_UsrProfileInd_e nUsrProfileInd;   /* REMOVED */
#endif // __MMI_STATUSBAR_SUPPORT_PROFILE_STATUS__
    StatusBar_RSSI_e nRSSIStatus;
    StatusBar_NetworkType_e nNetworkType; /* Network Type+ Home Zone Indication */
    u16 nCCSSQueue;                       /* u16 bitwise queue for CC and SS Indication */
#ifdef __DUAL_SIM_MMI__
    COMMON_SIM_CARD_STATUS_e nSIMCardStatus;
    StatusBar_RSSI_e nRSSIStatus_Slave;
    StatusBar_NetworkType_e nNetworkType_Slave;
    u16 nCCSSQueue_Slave;                       /* u16 bitwise queue for CC and SS Indication */
#endif
    u16 nWAPMSGQueue;                     /* u16 bitwise queue for WAP and MSG Indication */
    u32 nOtherQueue;                      /* u32 bitwise queue for OTHER Indication */
    u16 nMissCallQueue;
    u16 nMemCardAccess;			/* u16 bitwise number for memory card access */

    MAEBatteryLevel_e nLastBattLvl;     /* Previously reported Battery Level */
#ifdef __DUAL_BATT_MMI__
    MAEBatteryLevel_e nLastBattLvl_Slave;
#endif

    //#ifdef __UI_STYLE_MMI_IFONE__
    //u16 nSoundModeQueue;                      /* u16 bitwise queue for SoundMode Indication */
    MAE_WChar *pWTimeStr;
    StatusBar_NetworkType_e nRoaming; /* Network roaming Indication */
    StatusBar_NetworkType_e nEGPRS_GRPS; /* Network GPRS/EGPRS Indication */
    StatusBar_MissCallType_e nMissCallType;
    //#endif
#ifdef __WLAN_MMI__
    StatusBar_WiFiType_e    nWiFiStatus;
#endif

    StatusBar_BGStatus_e nBGStatus;

    /* For Charging and WAP Animation */
    boolean bWAPTrans;
    boolean bVoiceMailLine1;
    boolean bVoiceMailLine2;
    boolean bVoiceMailLine1_Slave;
    boolean bVoiceMailLine2_Slave;
    boolean bTerminateState;
    boolean bNetworkCamped;

    StatusBar_RSSI_e ePrevRSSI;
    u8 nRssiIgoredCount; //For count ignored RSSI number
#ifdef __MMI_DISPLAY_GPRS_TRAFFIC__
    boolean bNetworkHasTraffic_Master; // Record traffic status on SIM1
#endif
#ifdef __DUAL_SIM_MMI__
    StatusBar_RSSI_e ePrevRSSI_Slave;
    boolean bNetworkCamped_Slave;
    u8 nRssiIgoredCount_Slave; //For count ignored RSSI number
#ifdef __MMI_DISPLAY_GPRS_TRAFFIC__
    boolean bNetworkHasTraffic_Slave; // Record traffic status on SIM2
#endif
#endif
    boolean bAirplaneMode;
	IImage *pCustomImg[STATUSBAR_CUSTOM_ICON_NUM];
	u32 nCustomIndex;
	u8 nStatusbarImage;
#ifdef __TENCENT_MCARE__
    u16 nBlinkingImg;
#endif

#if defined(__MMS_MMI_CDMMS__) || defined(__EMAIL_MMI__)
    u8 nMsgTransStatus;
#endif
} MMI_STATUSBARSRV;

#endif /* __MMI_STATUSBARSRV_PRIV_H__ */
