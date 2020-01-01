/**
 * @file    mmi_mmsrv_def.h
 * @brief   xxxx
 * @version $Id: mmi_mmsrv_def.h 23154 2009-02-18 08:33:46Z lih.wang $
 */

#ifndef __MMI_MMSRV_DEF_H__
#define __MMI_MMSRV_DEF_H__


#define MMI_MM_OPER_MAXLEN              16
#define MMI_MM_NBMAX_PLMN               16
#define MMI_MM_MAX_LONG_ALPHANUMERIC    16
#define MMI_MM_MAX_SHORT_ALPHANUMERIC   10
#define MMI_MM_LSA_MAXLEN                           6
#define MMI_MM_UNIVERSALTIME_TIMEZONE_MAXLEN        20
#define MMI_MM_SPN_MAXLEN               81

#define MMI_MM_MAXPDP_ADDR_LENGTH       4
#define MMI_MM_MAXPDP_APN_NAME_LENGTH   100
#define MMI_MM_NBMAX_NEAR               6

#define MMI_MM_NITZ_NET_INFO_TABLE_SIZE 10

#define MMI_MM_LAC_SIZE   2
#ifdef __3G_RIL_MMI__
#define MMI_MM_CID_SIZE   4
#else //#ifdef __3G_RIL_MMI__
#define MMI_MM_CID_SIZE   2
#endif //#ifdef __3G_RIL_MMI__

//u8 Bit Mask for LineStatus
#define MMSRV_LINE_STATUS_VOICE                                1
#define MMSRV_LINE_STATUS_FAX                                    2
#define MMSRV_LINE_STATUS_DATA_TELESERVICES           4
#define MMSRV_LINE_STATUS_SMS                                    8
#define MMSRV_LINE_STATUS_DATA_BEARER_SERVICE      16
#define MMSRV_LINE_STATUS_AUXILIARY_VOICE              32

#ifdef __PROGRAM_TEMP_IMEI_MMI__
#define MMI_MM_IMEI_LENGTH 15
#endif

//enum
typedef enum
{
    MMI_MMSRV_STATUS_INITIAL
,   //MM SRV is initializing
    MMI_MMSRV_STATUS_IDLE
,   //MM SRV is ready to accept request
    MMI_MMSRV_STATUS_BUSY
,   //MM SRV is busy and will reject AP's request
    MMI_MMSRV_STATUS_TERMINATE
,   //MM SRV is going to terminate
} MMI_MMSRV_Status_e;

#ifdef __3G_RIL_MMI__
typedef enum
#else // __3G_RIL_MMI__ 
enum
#endif // __3G_RIL_MMI__
{
    MMI_MMSRV_RESULT_OK = 0
,   //Success
    MMI_MMSRV_RESULT_OP_NOT_ALLOWED = 3
,   //Operation not allowed
    MMI_MMSRV_RESULT_OP_NOT_SUPPORT = 4
,   //Operation not supported
    MMI_MMSRV_RESULT_PH_SIM_PIN_REQUIRED = 5
,   //PH-SIM PIN required(SIM lock)
    MMI_MMSRV_RESULT_SIM_NOT_INSERTED = 10
,   //SIM not inserted
    MMI_MMSRV_RESULT_SIM_PIN_REQUIRED = 11
,   //SIM PIN required
    MMI_MMSRV_RESULT_SIM_PUK_REQUIRED = 12
,   //SIM PUK required
    MMI_MMSRV_RESULT_SIM_FAILURE = 13
,   //SIM failure
    MMI_MMSRV_RESULT_NO_NETWORK_SERVICE = 30
,   //No network service
    MMI_MMSRV_RESULT_NETWORK_NOT_ALLOWED = 32
,   //network not allowed - emergency calls only
    MMI_MMSRV_RESULT_RSLUT_UNKNOWN_ERROR = 500
,   //Unknown PLMN error 
    MMI_MMSRV_RESULT_PLEASE_WAIT = 515
  , //Unknown PLMN error 
    MMI_MMSRV_RESULT_INCOMING_CALL_ERROR = 520
,   //the operation is aborted because of incoming call
    MMI_MMSRV_RESULT_NETWORK_BUSY = 527
,   //Please wait, RR or MM is busy. Try it later.
    MMI_MMSRV_RESULT_LOC_UPDATE_FAIL = 528
,   //Location update failure. Emergency calls only.
    MMI_MMSRV_RESULT_SEL_FAILED = 529
,   //selection failed - emergency calls only 
    MMI_MMSRV_RESULT_NO_EMERGE_CALL = 534
,   //Emergency call is not allowed without SIM
    MMI_MMSRV_RESULT_NO_EMERGE_CALL_WITHOUT_SIM = 546
,   //Emergency call is not allowed without SIM
    MMI_MMSRV_RESULT_EMERGE_CALL_WITHOUT_SIM = 547
,   //Emergency call only without SIM
#ifdef __3G_RIL_MMI__
    MMI_MMSRV_RESULT_OPR_PARAM_MISSING = 741
,      // Operator format parameter is missing
    MMI_MMSRV_RESULT_OPR_DATA_INCORRECT = 742
,      // Operator data is in incorrect format
    MMI_MMSRV_RESULT_OPR_DATA_TOO_LONG = 743
,      //Operator data is too long
    MMI_MMSRV_RESULT_PLMN_STORE_FULL = 744
,      //PLMN data cannot be written as the PLMN store is full
    MMI_MMSRV_RESULT_CANNOT_ACCESS_PLMN_LIST = 745
,      //The SIM PLMN list cannot be changed since CPOL cannot access it
    MMI_MMSRV_RESULT_OPR_NOT_RECOGNISED = 746
,      //Operator specified is not recognised
    MMI_MMSRV_RESULT_ACT_MISSING = 747
,      //Specified access technology missing
    MMI_MMSRV_RESULT_ACT_NOT_SUPPORT = 748
,      //Specified access technology not supported    
    MMI_MMSRV_RESULT_MODEM_BUSY = 769
,      //modem is busy and not able to handle this requirement
#endif // __3G_RIL_MMI__ 
    MMI_MMSRV_RESULT_AIRPLANE_MODE_OP_NOT_ALLOWED = 996
,   //Operation not allowed in airplane mode
    MMI_MMSRV_RESULT_INTERRUPT_BY_CC = 997
,   //Interrupt by CCRingInd
    MMI_MMSRV_RESULT_NULL_ERR = 998
,   //Response data is NULL
    MMI_MMSRV_RESULT_INTERNAL_ERR = 999
,   //Internal error
#ifdef __3G_RIL_MMI__
} MMI_MMSRV_Result_e;
#else // __3G_RIL_MMI__ 
}; 
typedef u16 MMI_MMSRV_Result_e;
#endif // __3G_RIL_MMI__

#ifdef __GPRS_MMI__
enum
{
    MMI_MMSRV_GPRS_CAUSE_OK = 0
   ,/*Response OK*/
    MMI_MMSRV_GPRS_CAUSE_NORMAL_NWK_DEACT = 225
   ,/*Network request detach*/
    MMI_MMSRV_GPRS_CAUSE_NO_GPRS_SERVICE = 226
   ,/*Unsuccessful attach cause NO SERVICE*/
    MMI_MMSRV_GPRS_CAUSE_NO_ACCESS = 227
   ,/*Unsuccessful attach cause NO ACCESS*/
    MMI_MMSRV_GPRS_CAUSE_GPRS_REFUSED = 228
   ,/*Unsuccessful attach cause NO ACCESS*/
    MMI_MMSRV_GPRS_CAUSE_NWK_DEACT = 229
   ,/*PDP deactivation requested by NWK*/
    MMI_MMSRV_GPRS_CAUSE_LLC_ESTABLISH_FAIL = 230
   ,/*PDP deactivation because LLC link fail*/
    MMI_MMSRV_GPRS_CAUSE_TI_UNAVAIL = 231
   ,/*PDP deactivation cause NWK reactivation with same TI*/
    MMI_MMSRV_GPRS_CAUSE_GMM_ABORT = 232
   ,/*PDP deactivation cause GMM error*/
    MMI_MMSRV_GPRS_CAUSE_SNDCP_FAIL = 233
   ,/*PDP deactivation cause LLC or SNDCP fail*/
    MMI_MMSRV_GPRS_CASUE_GMM_ERROR = 234
   ,/*PDP unsuccessful activation cause GMM error*/
    MMI_MMSRV_GPRS_CAUSE_ACTIVATE_REJ = 235
   ,/*PDP unsuccessful activation cause NWK reject*/
    MMI_MMSRV_GPRS_CAUSE_NSAPI_UNAVAIL = 236
   ,/*PDP unsuccessful activation cause NO NSAPI available*/
    MMI_MMSRV_GPRS_CAUSE_SM_REFUSE_ACT = 237
   ,/*PDP unsuccessful activation cause SM refuse*/
    MMI_MMSRV_GPRS_CAUSE_MMI_IGNORES = 238
   ,/*PDP unsuccessful activation cause MMI ignore*/
    MMI_MMSRV_GPRS_CAUSE_NBMAX_SESSION_REACH = 239
   ,/*PDP unsuccessful activation cause Nb Max Session Reach */
    MMI_MMSRV_GPRS_CAUSE_UNKNOWN = 0xFF
   ,/*all other error*/
}; 
typedef u8 MMI_MMSRV_GPRS_LocalCause_e;
#endif //__GPRS_MMI__
enum
{
    MMI_MMSRV_REGSTAT_NOT_REG_NO_SEARCH = 0
,   //not registered, ME is not currently searching
    MMI_MMSRV_REGSTAT_REG_HOME = 1
,   //registered, home network
    MMI_MMSRV_REGSTAT_NOT_REG_SEARCH = 2
,   //not registered, ME currently searching
    MMI_MMSRV_REGSTAT_REG_DENIED = 3
,   //registration denied
    MMI_MMSRV_REGSTAT_UNKOWN = 4
,   //unknown
    MMI_MMSRV_REGSTAT_REG_ROAM = 5
,   //registered, roaming
    MMI_MMSRV_REGSTAT_EMERGENCY_ONLY = 6
,   //Emergency call only
    MMI_MMSRV_REGSTAT_NO_SERVICE = 7
,   //no service
    MMI_MMSRV_REGSTAT_AIRPLANE_MODE = 8
,   //Airplane mode, RF closed

    MMI_MMSRV_REGSTAT_NOT_READY = 0xFF
,   //Not ready

};
typedef u8 MMI_MMSRV_RegStat_e;

enum
{
    MMI_MMSRV_REGMODE_ATUOMATIC
,   //automatic mode
    MMI_MMSRV_REGMODE_MANUAL
,   //manual mode
    MMI_MMSRV_REGMODE_DEREGISTRATION
,   //deregistration
    MMI_MMSRV_REGMODE_SET_FORMAT
,   //set only <format>
    MMI_MMSRV_REGMODE_AUTO_MAN
,   //automatic/manual mode
} ;
typedef u8 MMI_MMSRV_RegMode_e;

enum
{
    MMI_MMSRV_OPER_FORMAT_LONG
,   //long alphanumeric format
    MMI_MMSRV_OPER_FORMAT_SHORT
,   //short alphanumeric format
    MMI_MMSRV_OPER_FORMAT_NUMERIC
,   //numeric format
} ;
typedef u8 MMI_MMSRV_Oper_Format_e;

enum
{
    MMI_MMSRV_OPER_STAT_UNKNOWN
,   //unknown
    MMI_MMSRV_OPER_STAT_AVAILABLE
,   //available
    MMI_MMSRV_OPER_STAT_CURRENT
,   //current
    MMI_MMSRV_OPER_STAT_FORBIDDEN
,   //forbidden
} ;
typedef u8 MMI_MMSRV_Oper_Stat_e;

typedef enum
{
    MMI_MMSRV_LINE_UNKNOWN = 0
,   //Unknown
    MMI_MMSRV_LINE_1 = 1
,   //Line 1
    MMI_MMSRV_LINE_2 = 2
,   //Line 2
    MMI_MMSRV_DATA = 3
,   //Data
    MMI_MMSRV_FAX = 4
,   //Fax
    MMI_MMSRV_LINE_NOT_READY = 255
,   //Initilize
} MMI_MMSRV_Line_Service_e;

enum
{
    MMI_MMSRV_BAND_850 = 0
,   //mono-band mode 850 MHz
    MMI_MMSRV_BAND_900
,   //mono-band mode 900 extended MHz (900E)
    MMI_MMSRV_BAND_1800
,   //mono-band mode 1800 MHz
    MMI_MMSRV_BAND_1900
,   //mono-band mode 1900 MHz
    MMI_MMSRV_BAND_850_1900
,   //dual-band mode 850/1900 MHz
    MMI_MMSRV_BAND_900_1800
,   //dual-band mode 900E (extended) / 1800 MHz
    MMI_MMSRV_BAND_900_1900
,   //dual-band mode 900E (extended) / 1900 MHz
    MMI_MMSRV_QUAD_BAND_AUTO 
,   //Quad band auto
    MMI_MMSRV_TRI_BAND_AUTO
,   //Thi band auto
    MMI_MMSRV_BAND_P900
,   //900
    MMI_MMSRV_BAND_P900_1800
,   //dual-band mode P900/1800 MHz    
    MMI_MMSRV_BAND_P900_1900
,   //dual-band mode P900/1900 MHz

}; 
typedef u8 MMI_MMSRV_Band_e;

#ifdef __3G_RIL_MMI__
typedef enum
{
    MMI_MMSRV_GSM_BAND_INVALID = 0, 
    MMI_MMSRV_GSM_BAND_PGSM = 1, // 900MHz 
    MMI_MMSRV_GSM_BAND_DCS = 2,  // 1800MHz
    MMI_MMSRV_GSM_BAND_PCS = 4,  // 1900MHz
    MMI_MMSRV_GSM_BAND_EGSM = 9,  // 880~920MHz?
    MMI_MMSRV_GSM_BAND_850 = 64,  
    MMI_MMSRV_GSM_BAND_750 = 128,
    MMI_MMSRV_GSM_BAND_AUTO = 0xFFFF 
} MMI_MMSRV_GSM_BAND_e;

typedef enum
{
    MMI_MMSRV_TDD_BAND_INVALID = 0, 
    MMI_MMSRV_TDD_BAND_A_LOWER = 1,       // 1900~1920 MHz
    MMI_MMSRV_TDD_BAND_A_UPPER = 2,        // 2010~2025 MHz 
    MMI_MMSRV_TDD_BAND_B_LOWER = 4,       // 1850~1910 MHz
    MMI_MMSRV_TDD_BAND_B_UPPER = 8,        // 1930~1990 MHz
    MMI_MMSRV_TDD_BAND_C = 16,                 // 1910~1930 MHz
    MMI_MMSRV_TDD_BAND_F = 32,             // 1880~1920 MHz  
    MMI_MMSRV_TDD_BAND_E = 64,             // 2300~2400 MHz
    MMI_MMSRV_TDD_BAND_D = 128,               // 2570~2620 MHz 
    MMI_MMSRV_TDD_BAND_AUTO = 0xFFFF 
} MMI_MMSRV_TDD_BAND_e;

typedef enum
{
    MMI_MMSRV_FDD_BAND_INVALID = 0, 
    MMI_MMSRV_FDD_BAND_I = 1,               // 2100 MHz
    MMI_MMSRV_FDD_BAND_II = 2,              // 1900 MHz
    MMI_MMSRV_FDD_BAND_III = 4,             // 1800 MHz
    MMI_MMSRV_FDD_BAND_IV = 8,             // 2100/ 1700 MHz
    MMI_MMSRV_FDD_BAND_V = 16,             // 850 MHz ( for U.S. )
    MMI_MMSRV_FDD_BAND_VI = 32,            // 850 MHz ( for Japan )
    MMI_MMSRV_FDD_BAND_VII = 64,           // 2500 MHz
    MMI_MMSRV_FDD_BAND_VIII = 128,        // 900 MHz
    MMI_MMSRV_FDD_BAND_IX = 256,          // 1700 MHz ( for Japan )
    MMI_MMSRV_FDD_BAND_AUTO = 0xFFFF 
} MMI_MMSRV_FDD_BAND_e;
#endif // __3G_RIL_MMI__

typedef enum
{
    MMI_MMSRV_PLMN_EF_PLMNSEL
,   //user controlled PLMN selector with access technology
    MMI_MMSRV_PLMN_EF_PLMNWACT
,
    MMI_MMSRV_PLMN_EF_OPLMNWACT
,   //operator controlled PLMN selector with access technology
    MMI_MMSRV_PLMN_EF_HPLMNWACT
,   //home PLMN selector with access technology
} MMI_MMSRV_PLMN_EF_e;
#ifdef __GPRS_MMI__
typedef enum
{
    MMI_MMSRV_GPRS_DETACH = 0
,   //GPRS detach
    MMI_MMSRV_GPRS_ATTACH = 1
,   //GPRS attach
    MMI_MMSRV_GPRS_DETACH_COMBINED = 2
,   //Detach GPRS and GSM service
} MMI_MMSRV_GPRS_Reg_e;

enum
{
    MMI_MMSRV_NETACCESS_GSM_ONLY = 1
,   //GSM only
    MMI_MMSRV_NETACCESS_GPRS_PREFERRED
,   //GPRS preferred
};
typedef u8 MMI_MMSRV_NetAccess_Mode_e;
#endif //__GPRS_MMI__

typedef enum
{
    MMI_MMSRV_RSSI_LEVEL_0 = 0
   ,MMI_MMSRV_RSSI_LEVEL_1
   ,MMI_MMSRV_RSSI_LEVEL_2
   ,MMI_MMSRV_RSSI_LEVEL_3
   ,MMI_MMSRV_RSSI_LEVEL_4
   ,MMI_MMSRV_RSSI_LEVEL_5
} MMI_MMSRV_RSSI_Level_e;

typedef enum
{
    MMI_MMSRV_RSSI_STATUS_OFF = 0
,   //RSSI indication On
    MMI_MMSRV_RSSI_STATUS_ON = 1
,   //RSSI indication Off
} MMI_MMSRV_RSSI_Status_e;

typedef enum
{
    MMI_MMSRV_SEARCH_SCREEN_OFF = 0
,   //The network searching screen will never prompt.
    MMI_MMSRV_SEARCH_SCREEN_ON = 1
,   //The network searching screen will prompt.
} MMI_MMSRV_SearchMode_e;

#if defined(__3G_RIL_MMI__)
enum
{
    MMI_MMSRV_NETWORK_TYPE_NONE = 0
,                //No network service
    MMI_MMSRV_NETWORK_TYPE_GSM_ONLY
,            //GSM serivce only
    MMI_MMSRV_NETWORK_TYPE_GSM_GPRS 
,            //GSM + GPRS service
    MMI_MMSRV_NETWORK_TYPE_ROAMING_GSM_ONLY 
,    //Roaming GSM serivce only
    MMI_MMSRV_NETWORK_TYPE_ROAMING_GSM_GPRS
,    //Roaming GSM + GPRS service
    MMI_MMSRV_NETWORK_TYPE_GSM_EGPRS
,               //GSM+EGPRS home
    MMI_MMSRV_NETWORK_TYPE_ROAMING_GSM_EGPRS
,      //GSM+EGPRS roaming
    MMI_MMSRV_NETWORK_TYPE_UTRAN
,      // 3G
    MMI_MMSRV_NETWORK_TYPE_HSDPA
,      // 3.5G
    MMI_MMSRV_NETWORK_TYPE_HSUPA
,      // 3.75G
    MMI_MMSRV_NETWORK_TYPE_HSPA
,      // 3.75G
    MMI_MMSRV_NETWORK_TYPE_ROAMING_UTRAN
,      // 3G
    MMI_MMSRV_NETWORK_TYPE_ROAMING_HSDPA
,      // 3.5G
    MMI_MMSRV_NETWORK_TYPE_ROAMING_HSUPA
,      // 3.75G
    MMI_MMSRV_NETWORK_TYPE_ROAMING_HSPA
,      // 3.75G


} ;
#else //__3G_RIL_MMI__
enum
{
    MMI_MMSRV_NETWORK_TYPE_NONE = 0
,   //No network service
    MMI_MMSRV_NETWORK_TYPE_GSM_ONLY = 1
,   //GSM serivce only
    MMI_MMSRV_NETWORK_TYPE_GPRS_ONLY = 2
,   //GPRS service only
    MMI_MMSRV_NETWORK_TYPE_GSM_GPRS = 3
,   //GSM + GPRS service
    MMI_MMSRV_NETWORK_TYPE_ROAMING_GSM_ONLY = 4
,   //Roaming GSM serivce only
    MMI_MMSRV_NETWORK_TYPE_ROAMING_GPRS_ONLY = 5
,   //Roaming GPRS service only
    MMI_MMSRV_NETWORK_TYPE_ROAMING_GSM_GPRS = 6
,   //Roaming GSM + GPRS service
    MMI_MMSRV_NETWORK_TYPE_EGPRS_ONLY = 7
,   //EGPRS home
    MMI_MMSRV_NETWORK_TYPE_GSM_EGPRS = 8
,   //GSM+EGPRS home
    MMI_MMSRV_NETWORK_TYPE_ROAMING_EGPRS_ONLY = 9
,   //EGPRS roaming
    MMI_MMSRV_NETWORK_TYPE_ROAMING_GSM_EGPRS = 10
,   //GSM+EGPRS roaming
};
#endif  //__3G_RIL_MMI__
typedef u8 MMI_MMSRV_NetworkType_e;

typedef enum
{
    MMI_MMSRV_CELL_ONE_SHOT = 0
   ,MMI_MMSRV_CELL_AUTO_SHOT
   ,MMI_MMSRV_CELL_STOP_AUTO
} MMI_MMSRV_CellMode_e;

typedef enum
{
    MMI_MMSRV_CELL_DUMP_MAIN_CELL_ONLY = 1
,   //Main Cell only
    MMI_MMSRV_CELL_DUMP_NEI_ALL = 2
,   //Neighbours 1 to 6
    MMI_MMSRV_CELL_DUMP_MAIN_NEI_ALL = 3
,   //Main Cell then Neighbours 1 to 6
    MMI_MMSRV_CELL_DUMP_TA = 4
,   //Main Cell Timing Advance
    MMI_MMSRV_CELL_DUMP_MAIN_TA = 5
,   //Main Cell, then Timing Advance
    MMI_MMSRV_CELL_DUMP_6 = 6
,   //Neighbours 1 to 6, then Timing Advance
    MMI_MMSRV_CELL_DUMP_7 = 7
,   //Main Cell, then Neighbours 1 to 6, then Timing Advance
    MMI_MMSRV_CELL_DUMP_RSSI = 8
,   //Main Cell RSSI indications(RxLev), in a range from 0 to 31
    MMI_MMSRV_CELL_DUMP_RSSI_MAIN = 9
,   //CSQ+Main Cell only
    MMI_MMSRV_CELL_DUMP_10 = 10
,   //CSQ+Neighbors 1 to 6
    MMI_MMSRV_CELL_DUMP_11 = 11
,   //CSQ+Main Cell, then Neighbours 1 to 6
    MMI_MMSRV_CELL_DUMP_12 = 12
,   //CSQ+Timing Advance only
    MMI_MMSRV_CELL_DUMP_13 = 13
,   //CSQ+Main Cell, then Timing Advance
    MMI_MMSRV_CELL_DUMP_14 = 14
,   //CSQ+Neighbours 1 to 6, then Timing Advance
    MMI_MMSRV_CELL_DUMP_15 = 15
,   //CSQ+Main Cell, then Neighbours 1 to 6, then Timing Advance
    MMI_MMSRV_CELL_DUMP_16 = 16
,   //<requested dump> 1 + <requested dump> 2 + <requested dump> 4 +Neighbour1 to Neighbour6 Timing Advance
} MMI_MMSRV_Cell_ReqDump_e;

typedef enum
{
    MMI_MMSRV_CFU_UNKNOWN = 0
,        
    MMI_MMSRV_LINE_LINE1
,   //Line1
    MMI_MMSRV_LINE_LINE1_CFU
,   //Line1, CFU is on
    MMI_MMSRV_LINE_LINE2
,   //Line2
    MMI_MMSRV_LINE_LINE2_CFU
,   //Line2, CFU is on
    MMI_MMSRV_LINE_DATA
,   //Data
    MMI_MMSRV_LINE_FAX
,   //Fax
} MMI_MMSRV_Line_CFU_e;

typedef enum
{
    MMI_MMSRV_CFU_DISABLE = 0
,          //Divert Call Status disabled
    MMI_MMSRV_CFU_ENABLE = 1            //Divert Call Status enabled
} MMI_MMSRV_DivertedStatus_e;

typedef enum
{
    MMI_MMSRV_DELETE_ALL = 0
,           //Delete all entry
    MMI_MMSRV_DELETE_ONE = 1            //Delete one entry
} MMI_MMSRV_Delete_Type_e;
#ifdef __GPRS_MMI__
enum
{
    MMI_MMSRV_GPRS_STATUS_ON = 0
   ,/*On*/
    MMI_MMSRV_GPRS_STATUS_OFF = 1
   ,/*Off*/
    MMI_MMSRV_GPRS_STATUS_NOT_USE = 0xFF
};
typedef u8 MMI_MMSRV_WGPRS_StatusOnOff_e;

typedef enum
{
#ifdef __3G_RIL_MMI__
    MMI_MMSRV_WGPRS_ATTACH_STATUS = 0
   ,/*ATTACH-STATUS*/
    MMI_MMSRV_WGPRS_GPRS_MULTISLOT = 4
   /**Definition of the GPRS multislot class*/
#else // __3G_RIL_MMI__
    MMI_MMSRV_WGPRS_ATTACH_STATUS = 0
   ,/*ATTACH-STATUS*/
    MMI_MMSRV_WGPRS_PDPINIT_STATUS = 1
   ,/*PDP-INIT-STATUS*/
    MMI_MMSRV_WGPRS_ACTIVABLE = 2
   ,/*Set ACTIVABLE automatically after init a define PDP context*/
    MMI_MMSRV_WGPRS_PPP_SILENT = 3
   ,/*PPP silent mode*/
    MMI_MMSRV_WGPRS_GPRS_MULTISLOT = 4
   ,/**Definition of the GPRS multislot class*/
    MMI_MMSRV_WGPRS_SLOW_CONNECT = 5
   ,/*Slow CONNECT for PALMR OS*/
    MMI_MMSRV_WGPRS_PPP_FILTER = 6
   ,/*PPP Filtering*/
    MMI_MMSRV_WGPRS_GPRS_ROAMING = 7
   ,/*Automatic GPRS roaming inter-operator*/
    MMI_MMSRV_WGPRS_EGPRS_MULTISLOT = 8
   ,/*Definition of the EGPRS multislot class*/
#endif // __3G_RIL_MMI__ 
} MMI_MMSRV_WGPRS_Mode_e;

typedef enum
{
#ifndef __3G_RIL_MMI__
    MMI_MMSRV_GPRS_MULTISLOTCLASS_0 = 0
   ,/*Multislot class 0, only available for EGPRS*/
#endif // !__3G_RIL_MMI__ 
    MMI_MMSRV_GPRS_MULTISLOTCLASS_2 = 1
   ,/*Multislot class 2*/
    MMI_MMSRV_GPRS_MULTISLOTCLASS_8 = 2
   ,/*Multislot class 8*/
    MMI_MMSRV_GPRS_MULTISLOTCLASS_10 = 3
   ,/*Multislot class 10*/
    MMI_MMSRV_GPRS_MULTISLOTCLASS_12 = 4
   ,/*Multislot class 12*/
    MMI_MMSRV_GPRS_MULTISLOTCLASS_NOT_USE = 0xFF
} MMI_MMSRV_WGPRS_MultiSlotClass_e;

typedef enum
{
    MMI_MMSRV_GPRS_MSCLASS_B = 0
   ,/*Class B*/
    MMI_MMSRV_GPRS_MSCLASS_CG = 1
   ,/*Class C in GPRS only mode*/
    MMI_MMSRV_GPRS_MSCLASS_CC = 2
   ,/*Class C in circuit switched only mode*/
    MMI_MMSRV_GPRS_MSCLASS_INVALID = 0xFF
} MMI_MMSRV_GPRS_MSClass_e;

typedef enum
{
    MMI_MMSRV_GPRS_MSCLASS_SET = 0
   ,/*Set MS Class*/
    MMI_MMSRV_GPRS_MSCLASS_QUERY = 1
   ,/*Query current MS Class*/
} MMI_MMSRV_GPRS_MSClass_ReqType_e;

typedef enum
{
    MMI_MMSRV_GPRS_PDP_TYPE_IP = 0
   ,MMI_MMSRV_GPRS_PDP_TYPE_PPP = 1
} MMI_MMSRV_GPRS_PDP_Type_e;

typedef enum
{
    MMI_MMSRV_GPRS_SESSION_DEACTIVETED = 0
   ,/*Activation*/
    MMI_MMSRV_GPRS_SESSION_ACTIVATED = 1
   ,/*Deactivation*/
    MMI_MMSRV_GPRS_SESSION_DEACTIVATEDALL = 2       /*Deactivate all*/
} MMI_MMSRV_GPRS_SessionReqType_e;

typedef enum
{
    MMI_MMSRV_GPRS_QOS_REQUESTED = 0
   ,/*requested QoS (CGQREQ)*/
    MMI_MMSRV_GPRS_QOS_MIN = 1          /*minimal QoS (CGQMIN)*/
} MMI_MMSRV_GPRS_QoS_Type_e;

typedef enum
{
    MMI_MMSRV_GPRS_QOS_SUBSCRIBED_PRECEDENCE
   ,/*Subscribed by the Network*/
    MMI_MMSRV_GPRS_QOS_HIGH_PRIORITY
   ,/*High priority*/
    MMI_MMSRV_GPRS_QOS_NORMAL_PRIORITY
   ,/*Normal priority*/
    MMI_MMSRV_GPRS_QOS_LOW_PRIORITY         /*Low priority*/
} MMI_MMSRV_GPRS_QoS_Precedence_e;

typedef enum
{
    MMI_MMSRV_GPRS_QOS_SUBSCRIBED_DELAY
   ,/*Subscribed by the Network*/
    MMI_MMSRV_GPRS_QOS_DELAY_CLASS1
   ,/*Delay class 1*/
    MMI_MMSRV_GPRS_QOS_DELAY_CLASS2
   ,/*Delay class 2*/
    MMI_MMSRV_GPRS_QOS_DELAY_CLASS3
   ,/*Delay class 3*/
    MMI_MMSRV_GPRS_QOS_DELAY_CLASS4         /*Delay class 4*/
} MMI_MMSRV_GPRS_QoS_Delay_e;

typedef enum
{
    MMI_MMSRV_GPRS_QOS_SUBSCRIBED_RELIABILITY
   ,/*Subscribed by the Network*/
    MMI_MMSRV_GPRS_QOS_RELIABILITY_CLASS1
   ,/*Unused, shall be interpreted as 2*/
    MMI_MMSRV_GPRS_QOS_RELIABILITY_CLASS2
   ,/*Unacknowledged GTP, acknowledged LLC and RLC protected data*/
    MMI_MMSRV_GPRS_QOS_RELIABILITY_CLASS3
   ,/*Unacknowledged GTP and LLC, acknowledged RLC protected data*/
    MMI_MMSRV_GPRS_QOS_RELIABILITY_CLASS4
   ,/*Unacknowledged GTP, LLC and RLC protected data*/
    MMI_MMSRV_GPRS_QOS_RELIABILITY_CLASS5       /*Unacknowledged GTP, LLC and RLC unprotected data*/
} MMI_MMSRV_GPRS_QoS_Reliability_e;

typedef enum
{
    MMI_MMSRV_GPRS_QOS_SUBSCRIBED_PEAK
   ,/*Subscribed by the Network*/
    MMI_MMSRV_GPRS_QOS_PEAK_1000
   ,/*Up to 1000 (8kbits/s)*/
    MMI_MMSRV_GPRS_QOS_PEAK_2000
   ,/*Up to 2000 (16kbits/s)*/
    MMI_MMSRV_GPRS_QOS_PEAK_4000
   ,/*Up to 4000 (32kbits/s)*/
    MMI_MMSRV_GPRS_QOS_PEAK_8000
   ,/*Up to 8000 (64kbits/s)*/
    MMI_MMSRV_GPRS_QOS_PEAK_16000
   ,/*Up to 16000 (128kbits/s)*/
    MMI_MMSRV_GPRS_QOS_PEAK_32000
   ,/*Up to 32000 (256kbits/s)*/
    MMI_MMSRV_GPRS_QOS_PEAK_64000
   ,/*Up to 64000 (512kbits/s)*/
    MMI_MMSRV_GPRS_QOS_PEAK_128000
   ,/*Up to 128000 (1024kbits/s)*/
    MMI_MMSRV_GPRS_QOS_PEAK_256000              /*Up to 256000 (2048kbits/s)*/
} MMI_MMSRV_GPRS_QoS_Peak_e;

typedef enum
{
    MMI_MMSRV_GPRS_QOS_SUBSCRIBED_MEAN
   ,/*Subscribed by the Network*/
    MMI_MMSRV_GPRS_QOS_MEAN_100
   ,/*100(~0.22 bit/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_200
   ,/*200(~0.44 bit/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_500
   ,/*500(~1.11 bit/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_1000
   ,/*1000(~2.2 bit/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_2000
   ,/*2000(~4.4 bit/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_5000
   ,/*5000(~11.1 bit/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_10000
   ,/*10000(~22 bit/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_20000
   ,/*20000(~44 bit/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_50000
   ,/*50000(~111 bit/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_100000
   ,/*100000(~0.22 kbits/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_200000
   ,/*200000(~0.44 kbits/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_500000
   ,/*500000(~1.11 kbits/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_1000000
   ,/*1000000(~2.2 kbits/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_2000000
   ,/*2000000(~4.4 kbits/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_5000000
   ,/*5000000(~11.1 kbits/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_10000000
   ,/*10000000(~22 kbits/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_20000000
   ,/*20000000(~44 kbits/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_50000000
   ,/*50000000(~111 kbits/s)*/
    MMI_MMSRV_GPRS_QOS_MEAN_BESTEFFORT = 0x1F       /*Best effort*/
} MMI_MMSRV_GPRS_QoS_Mean_e;
#endif //__GPRS_MMI__

typedef enum
{
    MMI_MMSRV_PWON_OFF_LINE
   ,/* SIM off and protocol off */
    MMI_MMSRV_PWON_NORMAL
   ,/* SIM ON and protocol on */
    MMI_MMSRV_PWON_SIM_ONLY
   ,/* SIM ON and protocol off */
    MMI_MMSRV_PWON_PROTOCAL_ONLY
   ,/* SIM Off and protocol On */
} MMI_MMSRV_Radio_OnOff_e;

typedef enum
{
    MMI_MMSRV_DUALSIM_MASTER = 1
   ,MMI_MMSRV_DUALSIM_SLAVE = 2
} MMI_MMSRV_DualSIM_Type_e;
#ifdef __GPRS_MMI__
typedef enum
{
    MMI_MMSRV_EGPRS_OFF = 0
,   //No EDGE
    MMI_MMSRV_EGPRS_ON = 1
,   //EDGE
} MMI_MMSRV_EGPRS_Status_e;
#endif //__GPRS_MMI__
#ifdef __3G_RIL_MMI__
typedef enum
{
    MMI_MMSRV_RR_ACT_GSM = 0,
    MMI_MMSRV_RR_ACT_GSM_C = 1,
    MMI_MMSRV_RR_ACT_UTRAN = 2,
    MMI_MMSRV_RR_ACT_EGPRS = 3,
    MMI_MMSRV_RR_ACT_HSDPA = 4,
    MMI_MMSRV_RR_ACT_HSUPA = 5,
    MMI_MMSRV_RR_ACT_HSPA = 6,
    MMI_MMSRV_RR_ACT_NONE = 0xFF,
} MMI_MMSRV_RR_ACT_e;    

typedef enum
{
    MMI_MMSRV_RR_ACT_MASK_GSM = 0x0001,
    MMI_MMSRV_RR_ACT_MASK_GSM_C = 0x0002,
    MMI_MMSRV_RR_ACT_MASK_UTRAN = 0x0004,
} MMI_MMSRV_RR_ACT_MASK_e; 

typedef enum
{
    MMI_MMSRV_RR_FORCE_CMD_LOCK_CELL = 0,
    MMI_MMSRV_RR_FORCE_CMD_UNLOCK_CELL = 1,
    MMI_MMSRV_RR_FORCE_CMD_LOCK_ARFCN = 2,
    MMI_MMSRV_RR_FORCE_CMD_UNLOCK_ARFCN = 3,
    MMI_MMSRV_RR_FORCE_CMD_FULL_SCAN = 4,
} MMI_MMSRV_RR_FORCE_CMD_e;  

// for modem mode
typedef enum
{
    MMI_MMSRV_RR_MUSERMODE_GSM_ONLY = 0,     /* GSM  only */
    MMI_MMSRV_RR_MUSERMODE_WCDMA,               /* WCDMA only */     
    MMI_MMSRV_RR_MUSERMODE_GSM_WCDMA,       /* GSM and WCDMA */
    MMI_MMSRV_RR_MUSERMODE_TD,                       /* TD-SCDMA  only */
    MMI_MMSRV_RR_MUSERMODE_GSM_TD                /* GSM and TD-SCDMA  */
} MMI_MMSRV_RR_MuserMode_e;  

#endif //__3G_RIL_MMI__

#ifdef __PROGRAM_TEMP_IMEI_MMI__
typedef enum
{
    MMI_MMSRV_RR_STORE_IMEI_TEMPORARY = 0, // Use the temporary IMEI until power off
} MMI_MMSRV_STORE_IMEI_Mode_e;  
#endif

//Structure
//Network Search Confirmation
typedef struct
{
    u32 numeric;  // mcc & mnc   
    MMI_MMSRV_Oper_Stat_e stat;     // unknown;available;current;forbidden
    u8 LongAlpha[MMI_MM_MAX_LONG_ALPHANUMERIC + 1];
    u8 ShortAlpha[MMI_MM_MAX_SHORT_ALPHANUMERIC + 1];
#ifdef __3G_RIL_MMI__
    MMI_MMSRV_RR_ACT_e eRrAct;
#endif //__3G_RIL_MMI__
} MMSRV_PlmnInfo_t;

typedef struct
{
    MMI_MMSRV_Result_e MrlRrRslt;
    u8 NBPlmn;                         // number of plmns in PlmnList table
    MMSRV_PlmnInfo_t PlmnInfo[MMI_MM_NBMAX_PLMN];
} MMSRV_NetworkQuerytCnf_t;

//#ifdef __3G_RIL_MMI__  // remove compiler option for CFG build
typedef struct
{
    // use bit wise to indication selected band, refer MRL definition
    u16 gsmBitmap;
    u16 fddBitmap;
    u16 tddBitmap;
    u16 padding;
} MMSRV_BandSelectionInfo_t;
//#endif //#ifdef __3G_RIL_MMI__

#ifdef __3G_RIL_MMI__
typedef struct
{
    MMI_MMSRV_Result_e   MrlRrRslt;
    MMI_MMSRV_RR_FORCE_CMD_e  command;
    u32 		ARFCNnum;           
    u32 		ARFCN[8];               
    u32 		RSSI[8];    
} MMSRV_RrForceCnf_t;

// this is for 
typedef struct
{
    u32 	result;
    u8 	bitvalue[33];
} MMSRV_McfgQueryCnf_t;

typedef struct
{
    u32 	result;
    u8       mode;   // 0: don't display PLMN, 1:display PLMN
    u8       spn[MMI_MM_SPN_MAXLEN];
} MMSRV_MspnCnf_t;

typedef struct
{
    u32 	result;
    MMI_MMSRV_RR_MuserMode_e       mode;   
} MMSRV_MuserModeCnf_t;

#endif // __3G_RIL_MMI__

//Network Registration Request
typedef struct
{
    MMI_MMSRV_RegMode_e RegMode;
    MMI_MMSRV_Oper_Format_e OperFormat;
    u8 Oper[MMI_MM_OPER_MAXLEN + 1];      
#ifdef __3G_RIL_MMI__
    MMI_MMSRV_RR_ACT_e eRrAct;
    u8 pad[2];
#else
    u8 pad[3];
#endif //__3G_RIL_MMI__    
} MMSRV_NetworkRegReq_t;

//Network Registration Indication
typedef struct
{
    MMI_MMSRV_Result_e MrlRrRslt;
    u16 Mcc;
    u16 Mnc;
    //MMI_MMSRV_RegMode_e       Mode;       //Registration mode
    MMI_MMSRV_RegStat_e Stat;       //network registration state
    u8 Lac[MMI_MM_LAC_SIZE];        //Location area code
    u8 cid[MMI_MM_CID_SIZE];        //Cell ID
#ifdef __3G_RIL_MMI__
    MMI_MMSRV_RR_ACT_e Act;
#endif // //#ifdef __3G_RIL_MMI__ 
} MMSRV_NetworkRegInd_t;

//Network Registration Information
typedef struct
{
    u16 Mcc;
    u16 Mnc;
    MMI_MMSRV_RegMode_e Mode;               //Registration mode
    MMI_MMSRV_RegStat_e Stat;               //network registration state
    MMI_MMSRV_NetworkType_e NetworkType;    //network service type
    u8 Lac[MMI_MM_LAC_SIZE];                //Location area code
    u8 cid[MMI_MM_CID_SIZE];                //Cell ID
} MMSRV_NetworkRegInfo_t;

//Registered PLMN Information, for AT+COPS?
typedef struct
{
    MMI_MMSRV_Result_e MrlRrRslt;   //Result code
    MMI_MMSRV_RegMode_e mode;
    u16 Mcc;
    u16 Mnc;
} MMSRV_RegisteredPlmnInfoCnf_t;
#ifdef __GPRS_MMI__
//GPRS Network Registration Indication
typedef struct
{
    u16 Mcc;
    u16 Mnc;
#ifdef __3G_RIL_MMI__
    MMI_MMSRV_RR_ACT_e Act;
#else //__3G_RIL_MMI__
    MMI_MMSRV_EGPRS_Status_e EdgeCap;   // 0: No EDGE, 1: EDGE
#endif //__3G_RIL_MMI__
    MMI_MMSRV_RegStat_e Stat;           //GPPRS network registration state
    u8 Lac[MMI_MM_LAC_SIZE];            //Location area code
    u8 cid[MMI_MM_CID_SIZE];            //Cell ID
} MMSRV_GPRSRegInd_t, MMSRV_GPRSRegInfo_t;
#endif //__GPRS_MMI__
typedef struct
{
    MMI_MMSRV_Result_e Result; 
    //MMSRV_NetworkRegInfo_t    NetworkInfo;    //registered network info
} MMSRV_NetworkRegCnf_t;


//Network Registration Indication
//typedef struct
//{
//  MMSRV_NetworkRegInfo_t  NetworkInfo;    //registered network info
//} MMSRV_NetworkRegInd_t;


//Update Preferred PLMN List Request
typedef struct
{
    u8 Index;
    MMI_MMSRV_Oper_Format_e OperFormat;
    u8 Oper[MMI_MM_OPER_MAXLEN + 1];
#ifdef __3G_RIL_MMI__
    u16 uActMask;
#endif // #ifdef __3G_RIL_MMI__
} MMSRV_PreferredPLMNUpdateReq_t, MMSRV_PreferredPLMNInfo_t;

//Query Preferred PLMN List Confirmation
typedef struct
{
    u8 NBPlmn;                         // number of plmns in PlmnList table
    MMSRV_PreferredPLMNInfo_t PlmnInfo[MMI_MM_NBMAX_PLMN];
    MMI_MMSRV_Result_e MrlRrRslt;
} MMSRV_PreferredPLMNQuerytCnf_t;

// Radio signal strength
typedef struct
{
    u16 Rssi;   //signal strength
    u16 Ber;    //channel bit error rate
    //MMI_MMSRV_RSSI_Level_e  Level;  //strength level enum
} MMSRV_SignalStrengthInd_t;

//Onine Request
typedef struct
{
    MMI_MMSRV_SearchMode_e SearchMode;
} MMSRV_Online_t;

//ChangeLine  Request
typedef struct
{
    MMI_MMSRV_Line_Service_e LineNum;
} MMSRV_ChangeLine_t;

typedef struct
{
    MMI_MMSRV_Result_e MrlRrRslt;
    MMI_MMSRV_Line_Service_e LineNum;
} MMSRV_ChangeLineCnf_t, MMSRV_QueryLineCnf_t;


typedef struct
{
    MMI_MMSRV_Result_e MrlRrRslt;
    u8 DivertedCallStatus[4]; //[Line1, Lin2, Data, Fax]
} MMSRV_DivertedCallCnf_t;

typedef struct
{
    MMI_MMSRV_Line_Service_e Line;
    u8 DivertedCallStatus;
} MMSRV_DivertedCallInd_t;

#ifdef __GPRS_MMI__
//WGPRS request, GPRS parameters customization
typedef struct
{
    MMI_MMSRV_WGPRS_Mode_e Mode;                /*Wavecom GPRS parameter mode*/
    u8 Cid;                                     /*PDP context identifier*/
    MMI_MMSRV_WGPRS_StatusOnOff_e Parameter;    /*On or Off*/
    MMI_MMSRV_WGPRS_MultiSlotClass_e SlotClass; /*GPRS or EGPRS multislot class number*/
} MMSRV_WGPRSReq_t;


//WGPRS query request
typedef struct
{
    MMI_MMSRV_WGPRS_Mode_e Mode;        /*Wavecom GPRS parameter mode*/
    u8 Cid;                             /*PDP context identifier*/
} MMSRV_QueryWGPRSReq_t;

//WGPRS query confirmation
typedef struct
{
    MMI_MMSRV_Result_e Rslt;
    MMI_MMSRV_WGPRS_StatusOnOff_e Parameter;    /*On or Off*/
    MMI_MMSRV_WGPRS_MultiSlotClass_e SlotClass; /*GPRS or EGPRS multislot class number*/
} MMSRV_QueryWGPRSCnf_t;


//GPRS mobile class request
typedef struct
{
    MMI_MMSRV_GPRS_MSClass_ReqType_e ReqType;   /*Request type*/
    MMI_MMSRV_GPRS_MSClass_e MSClass;           /*Mobile station class*/
} MMSRV_MSClassReq_t;


typedef struct
{
    MMI_MMSRV_Result_e Result;
    MMI_MMSRV_GPRS_MSClass_e MSClass;   /*Mobile station class*/
} MMSRV_MSClassCnf_t;


//Define PDP context request
typedef struct
{
    MMI_MMSRV_GPRS_PDP_Type_e PDPType;
    u8 Addr[4];
    u8 APN[MMI_MM_MAXPDP_APN_NAME_LENGTH + 1];
    u8 h_comp;
    u8 d_comp;
} MMSRV_GPRS_PDP_Ctx_t;


typedef struct
{
    u8 Cid;
    MMSRV_GPRS_PDP_Ctx_t PDPCtx;
} MMSRV_GPRSPDPContextAddReq_t;

typedef struct
{
    u8 Cid;
} MMSRV_GPRSPDPContextDeleteReq_t;


typedef struct
{
    MMI_MMSRV_GPRS_SessionReqType_e ReqType;
    u8 Cid;
} MMSRV_GPRSPDPContextActReq_t;


typedef struct
{
    u8 Cid;
    MMI_MMSRV_Result_e Result;
    MMI_MMSRV_GPRS_LocalCause_e LocalCause;
} MMSRV_GPRSPDPContextActCnf_t;



typedef struct
{
    MMI_MMSRV_GPRS_QoS_Type_e Type;
    MMI_MMSRV_GPRS_QoS_Precedence_e Precedence;
    MMI_MMSRV_GPRS_QoS_Delay_e Delay;
    MMI_MMSRV_GPRS_QoS_Reliability_e Reliability;
    MMI_MMSRV_GPRS_QoS_Peak_e Peak;
    MMI_MMSRV_GPRS_QoS_Mean_e Mean;
} MMSRV_GPRS_QoS_t;


typedef struct
{
    u8 Cid;
    MMSRV_GPRS_QoS_t QoS;
} MMSRV_GPRSQoSSetReq_t;


typedef struct
{
    MMI_MMSRV_GPRS_QoS_Type_e Type;
    u8 Cid;
} MMSRV_GPRSQoSQueReq_t;

typedef struct
{
    MMI_MMSRV_Result_e Result;
    MMSRV_GPRS_QoS_t QoS;
} MMSRV_GPRSQoSQueCnf_t;
#endif //__GPRS_MMI__
//Cell Info
typedef struct
{
    u8 Mcc[2];              /* Main Cell Mcc */  
    u8 Mnc;                 /* Main Cell Mnc */  
    u8 Lac[2];              /* Main Cell LAC */  
    u8 cellavailable;       /* cellidavailable*/
    u8 CellId[2];           /* Main Cell CI */ 
    u16 BcchFreq;            /* Main Cell BCCH Freq */
    u8 Bsic;                /* Main Cell BSIC*/     
    u8 RxLev;               /* Main Cell RxLev */  
    u8 RxLevFull;           /* Main Cell RxLev Full */ 
    u8 RxLevSub;            /* Main Cell RxLev Sub*/  
    u8 RxQual;              /* Main Cell RxQual */  
    u8 RxQualFull;          /* Main Cell RxQual Full */ 
    u8 RxQualSub;           /* Main Cell RxQual Sub */  
    u8 TS;                  /* Main Cell Idle TS*/
    s8 C1;                  /* c1 */
    s8 C2;                  /* c2 */
} MMSRV_ServInfo_t;

typedef struct
{
    u8 Mcc[2];               /* neighbor Mcc */         
    u8 Mnc;                  /* neighbor Mnc */             
    u8 Lac[2];               /* neighbor LAC */       
    u8 cellavailable;        /* cellidavailable */
    u8 CellId[2];            /* neighbor CI */                                    
    u8 Bsic;                 /* neighbor BSIC*/                       
    u16 BcchFreq;            /* neighbor BCCH Freq*/       
    u8 RxLev;                /* neighbor RxLev */
    s8 C1;                   /* c1 */
    s8 C2;                   /* c2 */
    u8 TA;                   /* TA */
} MMSRV_NearInfo_t;

typedef struct
{
    MMI_MMSRV_CellMode_e mode;
    MMI_MMSRV_Cell_ReqDump_e reqDump;
} MMSRV_CellInfoReq_t;


typedef struct
{
    MMI_MMSRV_Result_e Result;
    MMSRV_ServInfo_t Serving;                       /* Serving inforamtion                      */
    u8 NbNear;                                      /* Number of near cells in Near table       */
    MMSRV_NearInfo_t Near[MMI_MM_NBMAX_NEAR];
    u8 TimAdv;                                      /* Timing advance of serving cell           */
    u8 ChannelType;
    u8 ChannelMode;
} MMSRV_CellInfoCnf_t;

typedef struct
{
    s8 LocalTimeZone;                      //Local time zone
    u8 DaylightSavingTime;                 //Daylight Saving time
    u8 LSAIdentity[MMI_MM_LSA_MAXLEN + 1];   //LSA Identity
    u8 UniversalTimeAndTimeZone[MMI_MM_UNIVERSALTIME_TIMEZONE_MAXLEN + 1];   //Universal time and local time zone   "yy/MM/dd,hh:mm:ss¡Ózz"
    u8 FullName[MMI_MM_MAX_LONG_ALPHANUMERIC + 1];    //Full name
    u8 ShortName[MMI_MM_MAX_SHORT_ALPHANUMERIC + 1];  //Short Name
} MMSRV_NITZInd_t;

//Network Info record
typedef struct
{
    u8 LongAlpha[MMI_MM_MAX_LONG_ALPHANUMERIC + 1];
    u8 ShortAlpha[MMI_MM_MAX_SHORT_ALPHANUMERIC + 1];
} MMSRV_NITZNetworkInfo_t;

typedef struct
{
    MMSRV_NITZNetworkInfo_t NITZNetTable[MMI_MM_NITZ_NET_INFO_TABLE_SIZE];
    u8 currIndex;  //Keep current writing index 
} MMSRV_NITZNetworkTable_t;

#ifdef __3G_RIL_MMI__
//Network setting Info record
typedef struct
{
    MMI_MMSRV_Line_Service_e              ActiveLine;
#ifdef __3G_RIL_MMI__
    MMSRV_BandSelectionInfo_t              BandInfo;   
#else   
    MMI_MMSRV_Band_e                        BandInfo;
#endif
#ifdef __GPRS_MMI__
    MMI_MMSRV_WGPRS_StatusOnOff_e   WGPRSStatus;
    MMI_MMSRV_WGPRS_MultiSlotClass_e WGPRSMultiSlotClassInfo;
#endif //__GPRS_MMI__
} MMSRV_NetworkSettingInfo_t;
#endif //#ifdef __3G_RIL_MMI__

#ifdef __PROGRAM_TEMP_IMEI_MMI__
//Store IMEI request
typedef struct
{
    MMI_MMSRV_STORE_IMEI_Mode_e Mode; // Store IMEI mode
    MMI_MMSRV_Result_e	Result; // result
} MMSRV_StoreIMEICnf_t;
#endif

//Message Union
typedef union
{
    MMSRV_NetworkQuerytCnf_t NetworkQueryCnf;  
    MMSRV_NetworkRegCnf_t NetworkRegCnf;
    MMSRV_NetworkRegInd_t NetworkRegInd;
#ifdef __GPRS_MMI__
    MMSRV_GPRSRegInd_t GPRSRegInd;
#endif //__GPRS_MMI__
    MMSRV_SignalStrengthInd_t SignalStrengthInd;
    MMSRV_PreferredPLMNQuerytCnf_t PreferredPLMNQuerytCnf;
    MMSRV_ChangeLineCnf_t LineChangeCnf;
    MMSRV_QueryLineCnf_t LineQueryCnf;
    MMSRV_DivertedCallCnf_t DivertedCallQueryCnf;
    MMSRV_DivertedCallInd_t DivertedCallQueryInd;
#ifdef __GPRS_MMI__
    MMSRV_GPRSQoSQueCnf_t GPRSQoSQueCnf;
    MMSRV_MSClassCnf_t MSClassCnf;
    MMSRV_GPRSPDPContextActCnf_t GPRSContextActionCnf;
#endif //__GPRS_MMI__
    MMSRV_CellInfoCnf_t CellInfoCnf;
    MMSRV_NITZInd_t NITZInd;
    MMSRV_RegisteredPlmnInfoCnf_t RegisteredPlmnInfo;
#ifdef __GPRS_MMI__
    MMSRV_QueryWGPRSCnf_t WGPRSQueryCnf;
#endif //__GPRS_MMI__
#ifdef __PROGRAM_TEMP_IMEI_MMI__
    MMSRV_StoreIMEICnf_t StoreIMEICnf;
#endif
#ifdef __3G_RIL_MMI__
    MMSRV_BandSelectionInfo_t BandQueryCnf;
    MMSRV_MuserModeCnf_t      MuserModeCnf;
#endif //__3G_RIL_MMI__
} MMSRV_unMsg_t;

#endif /* __MMI_MMSRV_DEF_H__ */
