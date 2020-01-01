/**
 * @file mmi_simsrv_def.h
 *
 * SIMSRV structure definition
 *
 * $Id$
 */
#ifndef __MMI_SIMSRV_DEF_H__
#define __MMI_SIMSRV_DEF_H__

#include "mmi_mae_langcode.h"

#define SIMSRV_DEBUG

#define XMMI_SIM_MAX_IMSI_LEN   9   //Maximum IMSI length
#define XMMI_SIM_MAX_ECC_LEN    6   //Maximum Emergency Call Code length
#define XMMI_SIM_MAX_ECC_NUM    5   //Maximum Emergency Call Code number
#define XMMI_SIM_MAX_DEF_LANG  10   //Maximum default language stored in SIM
#define XMMI_SIM_MAX_OPNAME_LEN 20  //Maximum characters number of Operator name
#define XMMI_SIM_MAX_PIN_REMAIN_TIME        3
#define XMMI_SIM_MAX_PUK_REMAIN_TIME        10
#define XMMI_SIM_MAX_PIN2_REMAIN_TIME       3
#define XMMI_SIM_MAX_PUK2_REMAIN_TIME       10

enum
{
    SIMSRV_SIM_ACTIVE = 1 << 0
,    //SIMSRV Active indication
    SIMSRV_SIM_READY = 1 << 1
,      //SIMSRV Ready indication
    SIMSRV_SIM_ABSENCE = 1 << 2
,        //SIMSRV Absence indication
    SIMSRV_SIM_PINSTATUS = 1 << 3
 ,  //SIMSRV PIN status indication.
    SIMSRV_SIM_SIMERROR = 1 << 4
 ,  //SIMSRV SIM error indication.
    SIMSRV_SIM_INDREADY = 1 << 5
,   //SIMSRV receives SIM card present/absent inidcation status
    SIMSRV_SIM_STATUSCHANGED = 1 << 6
 ,  //SIM card status changed indication.
    SIMSRV_SIM_SIMCHANGED = 1 << 7
  , //SIM card is changed inidcation. for insert different SIM.
    SIMSRV_SIM_NEEDVERIFYPIN = 1 << 8
 ,  //Check if need to verify PIN while init state.
    SIMSRV_SIM_MASTERFILEREADY = 1 << 9
,    //SIM MF file indication. Normal for Security/PIN checking.
    SIMSRV_SIM_INITSMSREADY = 1 << 10
 ,  //Init SMS indication.
    SIMSRV_SIM_NOSIM = 1 << 11
  , //No SIM card inserted indication.
    SIMSRV_SIM_IMSIFILEREADY = 1 << 12
  , //SIM IMSI file indication. Normal for Security/SIM lock and Network lock checking.
    SIMSRV_SIM_DEACTIVATE = 1 << 13
,    //SIMSRV deactive indication
    SIMSRV_SIM_INIT_APP_START = 1 << 14
,    //notify app that init application process is started.
    SIMSRV_SIM_INIT_APP_FINISHED = 1 << 15
  , //notify app that init application process is finished.
    SIMSRV_SIM_SIM_NORSP = 1 << 16
  , //notify app that init application process is finished.
    SIMSRV_SIM_ALLMask = 0xFFFF
};
typedef u32 SIMSRV_NOTIFY_MASK_e;

typedef enum
{
    SIMSRV_STATUS_NOTREADY = 0
  , //SIMSRV doesn't know SIM card status yet. SIMSRV can't process requests.
    SIMSRV_STATUS_ABSENCE
,      //There is no SIM card inserted. SIMSRV can't process requests.
    SIMSRV_STATUS_INITIAL
,      //SIM card is inserted and at initial state. SIMSRV can only process verify PIN and unblock PIN requests.
    SIMSRV_STATUS_READY
,            //SIMSRV is ready to process all kinds of requests.
    SIMSRV_STATUS_ERROR           //SIM Error happened that SIMSRV can't process requests.
} SIMSRV_STATUS_e;

#ifdef __3G_RIL_MMI__
typedef enum
{
    SIMSRV_SIM_PHASE_1,
    SIMSRV_SIM_PHASE_2,
    SIMSRV_SIM_PHASE_2P,
    SIMSRV_SIM_PHASE_3G,
    SIMSRV_SIM_PHASE_UNKNOW
} SIMSRV_SIM_PHASE_e;
#endif // #ifdef __3G_RIL_MMI__

typedef struct
{
    u8 u8PinEnabled;        //PIN check is enabled or not
    u8 u8PinRemainTimes;    //PIN remain times.
    u8 u8PukRemainTimes;    //PUK remain times.
    u8 u8Pin2RemainTimes;   //PIN2 remain times.
    u8 u8Puk2RemainTimes;   //PUK2 remain times.
} SIMSRV_PIN_STATUS_t;

typedef enum
{
    SIMSRV_SST_CHV1_DISABLE = 0
,    //PIN1 Disable function (Service n¢X1)
    SIMSRV_SST_ADN
,                 //Abbreviated Dialing Numbers (Service n¢X2)
    SIMSRV_SST_FDN
,                 //Fixed Dialing Numbers (Service n¢X3)
    SIMSRV_SST_SMS
,                 //Short Message Storage (Service n¢X4)
    SIMSRV_SST_AoC
,                 //Advice of Charge (Service n¢X5)
    SIMSRV_SST_CCP
,                 //Capability Configuration Parameters (Service n¢X6)
    SIMSRV_SST_PLMN
,                //PLMN selector (Service n¢X7)
    SIMSRV_SST_MSISDN
,              //MSISDN (Service n¢X9)
    SIMSRV_SST_GID1
,                //Group Identifier Level 1 (Service n¢X15)
    SIMSRV_SST_GID2
,                //Group Identifier Level 2 (Service n¢X16)
    SIMSRV_SST_SPN
,                 //Service Provider Name (Service n¢X17)
    SIMSRV_SST_SDN                  //Service Dialing Numbers (Service n¢X18)
} SIMSRV_SST_FEATURE_e;

typedef enum
{
    PINTYPE_PIN1 = 1
   ,PINTYPE_PIN2 = 2
} SIMSRV_PIN_TYPE_e;

typedef enum
{
    PIN_STATE_OK = 0
   ,PIN_STATE_NOK = 1
   ,PIN_STATE_MISS = 4
} SIMSRV_PIN_STATUS_e;

typedef struct
{
    u8 u8LangNo;                        //Language number
    u8 u8Lang[XMMI_SIM_MAX_DEF_LANG];   //Language store in SIM
} SIMSRV_LANGUAGE_t;

typedef struct
{
    u8 u8ECCLen;                                    //Each ECC element length
    u8 u8ECC[XMMI_SIM_MAX_ECC_LEN + 1];                 //Each ECC element data
} SIMSRV_ECC_Element_t;

typedef struct
{
    u8 u8ECCNum;                                    //ECC number
    SIMSRV_ECC_Element_t aryECC[XMMI_SIM_MAX_ECC_NUM];  //Each ECC element
} SIMSRV_ECC_t;

typedef enum
{
    SIMSRV_FILE_NONE = 0x0000
     ,  //None.
    SIMSRV_FILE_ICCID = 0x2FE2
    ,   //ICCID file (EFICCID:2FE2)
    SIMSRV_FILE_MF = 0x3F00
    ,    //Master file (EFLP:3F00)           M
#ifdef __3G_RIL_MMI__
   SIMSRV_FILE_PL = 0x2F05 
,    // USIM doesn't have EF LP, just have EF PL. And the contain is different
#endif // __3G_RIL_MMI__
    SIMSRV_FILE_LP = 0x6F05
    ,    //Language preference (EFLP:6F05)           M
    SIMSRV_FILE_IMSI = 0x6F07
    ,  //IMSI File (EFLP:6F07)                     M
    SIMSRV_FILE_SST = 0x6F38
    ,   //SIM Service Table (EFSST:6F38)            M
    SIMSRV_FILE_ADN = 0x6F3A
    ,   //Group Identifier Level 1 (EFGID1:6F3E)    O
    SIMSRV_FILE_FDN = 0x6F3B
    ,   //Group Identifier Level 1 (EFGID1:6F3E)    O
    SIMSRV_FILE_GID1 = 0x6F3E
    ,  //Group Identifier Level 1 (EFGID1:6F3E)    O
    SIMSRV_FILE_GID2 = 0x6F3F
    ,  //Group Identifier Level 1 (EFGID1:6F3F)    O
    SIMSRV_FILE_SPN = 0x6F46
    ,   //Service Provider Name (EFSPN:6F46)        O
    SIMSRV_FILE_ONS = 0x6F14
    ,   //Operator Name String (CPHS ONS: 6F14)     O
    SIMSRV_FILE_SONS = 0x6F18
    ,  //Short Form of Operator Name string (CPHS SONS: 6F18)  O
    SIMSRV_FILE_CFF = 0x6F13
    ,   //Call Forwarding Flag (CHPS CFF: 6F13)     O
    SIMSRV_FILE_ECC = 0x6FB7    //Emergency Call Code (EFECC: 6FB7)         O
} SIMSRV_SIM_FILE_ID_e;

typedef enum
{
    SIMSRV_RESULT_OK = 0
   ,SIMSRV_RESULT_NO_RESPOND
   ,SIMSRV_RESULT_FP_NOT_FOUND
   ,SIMSRV_RESULT_MISM_INV_STATUS
   ,SIMSRV_RESULT_FAIL
   ,SIMSRV_RESULT_ERROR
} SIMSRV_RESULT_e;

typedef struct
{
    SIMSRV_RESULT_e Result;     //read file result, only SIMSRV_RESULT_OK have data.
    SIMSRV_SIM_FILE_ID_e FileID;    //requested file id.
    u32 nDataLength;            //Byte length of data.
    void *pData;                    //file data. Need to cast data type regarding to FileID.
} SIMSRV_FileReadCnf_t;
typedef struct
{
    SIMSRV_RESULT_e Result;     //read file result, only SIMSRV_RESULT_OK have data.
    SIMSRV_SIM_FILE_ID_e FileID;    //requested file id.
    u16 MemoryTotal;
    u16 FileStatus;
    u8 FileChar;
    u8 nDataLength;
} SIMSRV_FileStatusCnf_t;

typedef struct
{
    u16 u16OPNameLen;                               //Operator Name length in characters.
    MAE_WChar strOPName[XMMI_SIM_MAX_OPNAME_LEN + 1];   //Operator Name string with UCS2 format.
    u16 u16SrcOPNameLen;
} SIMSRV_OPName_t;  //for SPN, ONS and SONS
#ifdef __QUAD_SIM_DUAL_STANDBY__
typedef struct
{
    u8 MaxSimNum;           /* maximun number of SIM card supported */
    u8 MaxActiveSimNum;     /* maximun number of active SIM card supported */
    boolean Sim1MuxCtrl;
    boolean Sim2MuxCtrl;
}SIMSRV_SimInfo_t;
#endif

#ifdef __3G_RIL_MMI__
typedef struct
{
    u32 	result;
    u32     count;
    u8     num[5];	
} SIMSRV_Mecc_Info_t;
#endif //__3G_RIL_MMI__

typedef enum
{
    SIMSRV_SIM_AUTO = 0
,        //For single SIM inserted or auto select Master for two SIM inserted.
    SIMSRV_SIM_MASTER
,      //Master SIM for DUO mode.
    SIMSRV_SIM_SLAVE
,           //Slave SIM for DUO mode.
    SIMSRV_SIM_NONE         //No SIM.
} SIMSRV_SIM_ID_e;

typedef enum
{
    SIMSRV_SIM_CARD_UNKNOW = 0
,     //Not receive SIM indication yet.
    SIMSRV_SIM_CARD_NOSIM
,          //no SIM inserted for both single mode and DUO mode.
    SIMSRV_SIM_CARD_SINGLE
,         //SIM inserted for single SIM mode.
    SIMSRV_SIM_CARD_DUAL_MASTER
,    //Activated Master SIM only for DUO mode.
    SIMSRV_SIM_CARD_DUAL_SLAVE
,     //Activated Slave SIM only for DUO mode.
    SIMSRV_SIM_CARD_DUAL_BOTH       //Activated both Master and Slave SIM for DUO mode.
} SIMSRV_SIM_CARD_STATUS_e;

typedef enum
{
    SIMSRV_SIM_INSERT_UNKNOW = 0
,       //Not receive SIM indication yet.
    SIMSRV_SIM_INSERT_NOSIM
,                //No SIM inserted for both single mode and DUO mode.
    SIMSRV_SIM_INSERT_SINGLE
,               //SIM inserted for single SIM mode
    SIMSRV_SIM_INSERT_MASTER
,           //Master SIM inserted only of DUO mode.
    SIMSRV_SIM_INSERT_SLAVE
,                //Slave SIM inserted only for DUO mode.
    SIMSRV_SIM_INSERT_BOTH              //Both Master and Slave SIM are inserted for DUO mode.
} SIMSRV_SIM_INSERT_e;
#ifdef __QUAD_SIM_DUAL_STANDBY__
typedef enum
{
    SIMSRV_SIM_INSERT_NEW_UNKNOW = 0,  //Not receive SIM indication yet.
    SIMSRV_SIM_INSERT,              // SIM is inserted.
    SIMSRV_SIM_NOT_INSERT,          // SIM is not inserted.
    SIMSRV_SIM_INSERT_UNDEFINESIM //Undefined SIM card ID. 
} SIMSRV_SIM_INSERT_NEW_e;
typedef enum
{
    SIMSRV_SIMRACK_1 = 0,     //SIM1 of Master.
    SIMSRV_SIMRACK_2,          //SIM2 of Master.
    SIMSRV_SIMRACK_3,         //SIM3 of Slave.
    SIMSRV_SIMRACK_4,         //SIM4 of Slave
    SIMSRV_SIMRACK_MAX,
    SIMSRV_SIMRACK_UNKNOW
} SIMSRV_SIM_RACK_ID_e;
typedef enum
{
    SIMSRV_SIM_IND_NONE = 0x00,     //Not receive SIM indication yet.
    SIMSRV_SIM_IND_MASTER = (1 << 0),     //Receive Master SIM indicatoin only.
    SIMSRV_SIM_IND_SLAVE = (1 << 1),          //Receive Slave SIM indicatoin only.
    SIMSRV_SIM_IND_SLAVE1 = (1 << 2),
    SIMSRV_SIM_IND_SLAVE2 = (1 << 3),
    SIMSRV_SIM_IND_THREE = (SIMSRV_SIM_IND_MASTER|SIMSRV_SIM_IND_SLAVE|SIMSRV_SIM_IND_SLAVE1),
    SIMSRV_SIM_IND_QUAD = (SIMSRV_SIM_IND_MASTER|SIMSRV_SIM_IND_SLAVE|SIMSRV_SIM_IND_SLAVE1|SIMSRV_SIM_IND_SLAVE2),
    SIMSRV_SIM_IND_BOTH = (SIMSRV_SIM_IND_MASTER | SIMSRV_SIM_IND_SLAVE)          //Receive both Master and Slave SIM indicatoin.
} SIMSRV_SIM_IND_e; //check MAE_EVT_SIM_PRESENCE_IND and MAE_EVT_SIM_ABSENCE_IND for SIM.
#else
typedef enum
{
    SIMSRV_SIM_IND_NONE = 0x00
,     //Not receive SIM indication yet.
    SIMSRV_SIM_IND_MASTER = (1 << 0)
,     //Receive Master SIM indicatoin only.
    SIMSRV_SIM_IND_SLAVE = (1 << 1)
,          //Receive Slave SIM indicatoin only.
    SIMSRV_SIM_IND_BOTH = (SIMSRV_SIM_IND_MASTER | SIMSRV_SIM_IND_SLAVE)          //Receive both Master and Slave SIM indicatoin.
} SIMSRV_SIM_IND_e; //check MAE_EVT_SIM_PRESENCE_IND and MAE_EVT_SIM_ABSENCE_IND for SIM.
#endif
typedef enum
{
    SIMSRV_INITAPP_INITIAL = 0
,         //init step for init application.
    SIMSRV_INITAPP_PHONEBOOK
,       //at init phonebook stage.
    SIMSRV_INITAPP_MESSAGE
,         //at init message stage.
    SIMSRV_INITAPP_FINAL = SIMSRV_INITAPP_MESSAGE           //Receive both Master and Slave SIM indicatoin.
} SIMSRV_INITAPP_STEP_e;    //che

typedef enum
{
    SIMSRV_INITAPP_TYPE_ALL = 0
,        //all applications that need to be init
    SIMSRV_INITAPP_TYPE_PHONEBOOK
   ,SIMSRV_INITAPP_TYPE_SMS
} SIMSRV_INITAPP_TYPE_e;

#endif /* __MMI_SIMSRV_DEF_H__ */
