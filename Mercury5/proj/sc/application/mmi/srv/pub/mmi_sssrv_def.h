/**
 * @file    mmi_sssrv_def.h
 * @brief   xxxx
 * @version $Id: mmi_sssrv_def.h 18722 2008-12-19 10:57:29Z sho.ding $
 */

#ifndef __MMI_SSSRV_DEF_H__
#define __MMI_SSSRV_DEF_H__

#include "mmi_mae_common_def.h"

#define MAX_SS_NUMBER_LEN   21       // The max. length of the number to be forwarded to
#define MAX_SS_CB_PWD_LEN   8        // The max. length of the barring network code
#define MAX_SS_CWXINFO_NO   13       // The max. number of the call waiting info
#define MAX_SS_CFXINFO_NO   9        // The max. number of the call divert info
#define MAX_SS_CBXINFO_NO   13       // The max. number of the call barring info
#define MAX_SS_SEND_USSD_LEN     80      // The max. length of the send USSD string
#define MAX_SS_RECEIVE_USSD_LEN     320     // The max. length of the receive USSD string
#define MAX_SS_TIME_TO_WAIT 20       // Default Call Divert time to wait

#define MAX_SS_CURRENCY_LENGTH 3
#define MAX_SS_PPU_LENGTH  8
#define MAX_SS_PIN2_LENGTH 8
#define MAX_SS_CCM_LENGTH  8
#define MAX_SS_ACM_LENGTH  8
#define MAX_SS_AMM_LENGTH  8

#define MAX_SS_REQUEST_STRING_LENGTH  80

//Lih:TBD
#define SSSRV_DCS_DEFAULT_ALPHA_LANG_UNSPECIFIED      15      //Default alphabet data coding
#define SSSRV_DCS_MESSAGE_UCS2                        17      //03.38, UCS2; message preceded by language indication
#define SSSRV_DCS_GENERAL_DEFAULT_ALPHA               64      //General Data Coding: default alphabet data coding
#define SSSRV_DCS_GENERAL_8_BIT_DATA                  68      //General Data Coding: 8 bit data
#define SSSRV_DCS_GENERAL_UCS2                        72      //General Data Coding: UCS2 data coding


//enum
typedef enum
{
    SSSRV_STATUS_UNKNOWN
,   //SS SRV is not exist
    SSSRV_STATUS_INITIAL
,   //SS SRV is initializing
    SSSRV_STATUS_IDLE
,      //SS SRV is ready to accept request
    SSSRV_STATUS_BUSY
,       //SS SRV is busy and will reject AP's request
    SSSRV_STATUS_TERMINATE
 ,  //SS SRV is terminating and MS will power off
} MMI_SSSRV_Status_e;

typedef enum
{
    SSSRV_SS_RESULT_OK = 0
,             //ok
    SSSRV_SS_ERR_UNKNOWN_ERROR = 1
,     //unknow error
    SSSRV_SS_ERR_NOT_ALLOWED = 3
,           //opearation not allowed
    SSSRV_SS_ERR_NOT_SUPPORTED = 4
,       //opearation not support
    SSSRV_SS_ERR_PH_SIM_PIN_REQUIRED = 5
  , //PH-SIM PIN required(SIM lock)
    SSSRV_SS_ERR_SIM_NOT_INSERTED = 10
,     //SIM not inserted
    SSSRV_SS_ERR_SIM_PIN_REQUIRED = 11
,     //SIM PIN required
    SSSRV_SS_ERR_SIM_PUK_REQUIRED = 12
,     //SIM PUK required
    SSSRV_SS_ERR_SIM_FAILURE = 13
,          //SIM failure
    SSSRV_SS_ERR_INCORRECT_PWD = 16
,          //password incorrect
    SSSRV_SS_ERR_SIM_PIN2_REQUIRED = 17
,     //SIM PIN2 required
    SSSRV_SS_ERR_SIM_PUK2_REQUIRED = 18
,     //SIM PUK2 required
    SSSRV_SS_ERR_NO_NETWORK_SERVICE = 30
,    //no network service
    SSSRV_SS_ERR_INTERNAL_ERR = 999      //SS Service internal error
} MMI_SSSRV_SS_Result_e;

typedef enum
{
    SSSRV_SS_STATUS_DEACTIVATE = 0
,   //deactivate.
    SSSRV_SS_STATUS_ACTIVATE = 1
,       //activate
    SSSRV_SS_STATUS_UNKNOWN = 2       //unknown
} MMI_SSSRV_SS_Status_e;

typedef enum
{
    SSSRV_REQTYPE_DEACTIVATE
,   // 0 disable
    SSSRV_REQTYPE_ACTIVATE
,     // 1 enable
    SSSRV_REQTYPE_INTERROGATE
 ,  // 2 interrogate
    SSSRV_REQTYPE_REGISTER
,     // 3 registration
    SSSRV_REQTYPE_ERASE         // 4 erasure unconditional
} MMI_SSSRV_ReqType_e;

enum
{
    SSSRV_NUMBER_TYPE_NATIONAL = 129
,           //national number
    SSSRV_NUMBER_TYPE_INTERNATIONAL = 145       //international number (include "+")
} ;
typedef u8 MMI_SSSRV_Number_Type_e;


typedef enum
{
    SSSRV_CFX_UNCONDITIONAL = 0
,    //unconditional
    SSSRV_CFX_BUSY = 1
,             //mobile busy
    SSSRV_CFX_NOREPLY = 2
,          //no reply
    SSSRV_CFX_NOTREACHABLE = 3
,     //not reachable
    SSSRV_CFX_ALL = 4
,              //all call forwarding
    SSSRV_CFX_ALL_CONDITIONAL = 5
 ,  //all conditional call forwarding
    SSSRV_CFX_UNKNOWN = 255     //Unknown
} MMI_SSSRV_CFX_Reason_e;

typedef enum
{
    SSSRV_CALLCLASS_VOICE = 1
,      //Voice call
    SSSRV_CALLCLASS_DATA = 2
,       //Data call (bearer service)
    SSSRV_CALLCLASS_FAX = 4
,        //Fax call
    SSSRV_CALLCLASS_V_D_F = 7
,      //Voice, data and fax
    SSSRV_CALLCLASS_SMS = 8
,        //SMS
#ifdef __3G_RIL_MMI__
   SSSRV_CALLCLASS_V_D_F_S = 15 
,        // in 27.007, if you want to query SMS status, you need add 8
#endif //__3G_RIL_MMI__
    /*ATD*/
    SSSRV_BS_ALLTS = 10
,                // all telephony services
    SSSRV_BS_TELEPHONY = 11
,           // telephony
    SSSRV_BS_TS_DATAALL = 12
,           // all data telephony services
    SSSRV_BS_SMS = 16
,           // Short message services
    SSSRV_BS_TS_VOICE_GROUP = 17
,       // voice group call
    SSSRV_BS_TS_VOICE_BROADCAST = 18
,   // voice broadcast
    SSSRV_BS_TS_BUTSMS = 19
,            // all telephony but SMS
    SSSRV_BS_ALLBEARER = 20
,           // All bearer services
    SSSRV_BS_ALLCDA = 21
,               // all asynchronous data
    SSSRV_BS_ALLCDS = 22
,               // all synchronous data
    SSSRV_BS_CSYNCH = 24
,               // all data circuit synchronous
    SSSRV_BS_CASYNC = 25
,               // all data circuit asynchronous
    SSSRV_BS_ALLPDS = 26
,               // all dedicated packet access
    SSSRV_BS_ALLPAD = 27
,               // all dedicated PAD accesss
    SSSRV_BS_ALL_GPRS = 99
,             // all GPRS bearer services
    SSSRV_CALLCLASS_NOCLASS = 0xFF  //No class specified
} MMI_SSSRV_CallClass_e;

typedef enum
{
    SSSRV_CBX_BAOC = 0
,      //0, all outgoing calls
    SSSRV_CBX_BAOIC
,         //1, all outgoing international calls
    SSSRV_CBX_BAOIC_R
,       //2, Barr Outgoing. International Calls except toHome Country
    SSSRV_CBX_BAIC
,          //3, all incoming calls
    SSSRV_CBX_BAIC_R
,        //4, all incoming calls when roaming
    SSSRV_CBX_BALL
,          //5, all calls
    SSSRV_CBX_ABOC
,          // 6, all outgoing barring services
    SSSRV_CBX_ABIC
,          // 7, all imcoming barring services
    SSSRV_CBX_UNKNOWN = 255  // 255, Unknown
} MMI_SSSRV_CBX_Type_e;

typedef enum
{
    SSSRV_USSD_NO_ACTION_REQUIRED = 0
,          //no further user action required
    SSSRV_USSD_ACTION_REQUIRED = 1
,             //further user action required
    SSSRV_USSD_TERMINATED_BY_NETWORK = 2
,       //USSD terminated by network
    SSSRV_USSD_OTHER_CLIENT_RESPONSED = 3
,      //other local client has responded
    SSSRV_USSD_NOT_SUPPORTED = 4
,               //operation not supported
    SSSRV_USSD_NETWORK_TIMEOUT = 5
,             //network timeout
    SSSRV_USSD_NOT_USE = 255                    //This field is not use
} MMI_SSSRV_USSD_Status_e;


typedef enum
{
    USSD_ACTION_TYPE_USER_INITIAL
,          //USSDReq
    USSD_ACTION_TYPE_USER_RESPONSE
,         //USSDRsp
    USSD_ACTION_TYPE_NETWORK_INITIAL
,       //USSDNot
    USSD_ACTION_TYPE_NETWORK_CONFIRM
,       //USSDCnf
    USSD_ACTION_TYPE_NETWORK_INDICATION
,    //USSDInd
    SS_RELATED_ACTION_TYPE
,                 //SS related action
} MMI_SSSRV_USSD_Action_Type_e;

typedef enum
{
    USSD_SIM_TYPE_USER_DETERMINE = 0
  , //Let user select
    USSD_SIM_TYPE_MASTER
,           //Master SIM
    USSD_SIM_TYPE_SLAVE
,            //Slave SIM
} MMI_SSSRV_USSD_SIM_Type_e;


typedef enum
{
    SSSRV_CUG_NO_INFORMAION = 0
,        //no information (default)
    SSSRV_CUG_SUPPRESS_OA = 1
,      //suppress OA
    SSSRV_CUG_SUPPRESS_PREF = 2
,        //suppress preferential CUG
    SSSRV_CUG_SUPPRESS_OA_PREF = 3  //suppress OA and preferential CUG
} MMI_SSSRV_CUGInfo_e;


typedef enum
{
    SSSRV_AOC_QUERY = 0
,    //Query CCM value.
    SSSRV_AOC_DEACTIVATE = 1
,   //Deactivation CCM value report.
    SSSRV_AOC_ACTIVATE = 2  //Activation CCM value report.
} MMI_SSSRV_AOC_ReqType_e;

typedef enum
{
    SSSRV_AOC_STATUS_DEACTIVATE = 1
,    //Deactivation CCM value report.
    SSSRV_AOC_STATUS_ACTIVATE = 2   //Activation CCM value report.
} MMI_SSSRV_AOC_Status_e;

typedef enum
{
    SSSRV_ACM_QUERY = 0
,    //Query ACM value.
    SSSRV_ACM_RESET = 1     //Reset ACM value.
} MMI_SSSRV_ACM_ReqType_e;

typedef enum
{
    SSSRV_AMM_QUERY = 0
,    //Query AMM value.
    SSSRV_AMM_UPDATE = 1        //Update AMM value.
} MMI_SSSRV_AMM_ReqType_e;

typedef enum
{
    SSSRV_PUC_QUERY = 0
,    //Query PUC value.
    SSSRV_PUC_UPDATE = 1        //Update PUC value.
} MMI_SSSRV_PUC_ReqType_e;

typedef enum
{
    SSSRV_REQUEST_TYPE_NONE = 0
,     //none 
    SSSRV_REQUEST_TYPE_CFX
,         //Call Divert
    SSSRV_REQUEST_TYPE_CBX
,         //Call Barring
    SSSRV_REQUEST_TYPE_CWX
,         //Call Waiting
    SSSRV_REQUEST_TYPE_PWD
,         //change barring password
    SSSRV_REQUEST_TYPE_USSD
,        //USSD
    SSSRV_REQUEST_TYPE_CUG_SET
,     //User Group set
    SSSRV_REQUEST_TYPE_CUG_QUE
,     //User Group query
    SSSRV_REQUEST_TYPE_AOC_SET
,     //AoC set
    SSSRV_REQUEST_TYPE_AOC_QUE
,     //AoC query
    SSSRV_REQUEST_TYPE_ACM
,         //Accumulated Call Meter
    SSSRV_REQUEST_TYPE_AMM
,         //Accumulated Call Meter maximum
    SSSRV_REQUEST_TYPE_PUC
,         //Price per Unit and Currnecy
    SSSRV_REQUEST_TYPE_CLX          //Line Identity query
} SSSRV_REQUEST_TYPE_e;

typedef enum
{
    SSSRV_CI_CLIP
   ,SSSRV_CI_CLIR
   ,SSSRV_CI_COLP
   ,SSSRV_CI_NOT_SUPPORT
} MMI_SSSRV_CI_ReqType_e;

//Structure
//Call Divert Request
typedef struct
{
    MMI_SSSRV_ReqType_e ReqType;                   // activate/deactivate/erase/interrogate
    MMI_SSSRV_CFX_Reason_e CfxReason;              // cfx condition            
    u8 u8DivertTo[MAX_SS_NUMBER_LEN + 1];          // divert to number
    MMI_SSSRV_Number_Type_e NbType;                // type of telephone number
    MMI_SSSRV_CallClass_e CallClass;               // call class
    u8 u8NoReplyTime;                              // time to wait when CF condition is no reply
    u8 u8UssdString[MAX_SS_SEND_USSD_LEN + 1];     // the SS string entered by user
} SSSRV_CallDivertReq_t;

//Call Divert Confirmation
typedef struct
{
    MMI_SSSRV_SS_Status_e Status;                  // active or deactive
    MMI_SSSRV_CallClass_e CallClass;               // call class
    u8 u8DivertTo[MAX_SS_NUMBER_LEN + 1];          // divert to number
    MMI_SSSRV_Number_Type_e NbType;                // type of telephone number
    u8 u8NoReplyTime;                              // time to wait when CF condition is no reply
} SSSRV_CfxInfo_t;

typedef struct
{
    MMI_SSSRV_SS_Result_e Result;
    u8 u8NbCfxInfo;                                // classfication according to call class
    SSSRV_CfxInfo_t CfxInfo[MAX_SS_CFXINFO_NO];    // array of structures
} SSSRV_CallDivertCnf_t;


//Call Waiting Request
typedef struct
{
    MMI_SSSRV_ReqType_e ReqType;       // activate/deactivate/interrogate               
    MMI_SSSRV_CallClass_e CallClass;     // voice/data/fax/all
    u8 u8UssdString[MAX_SS_SEND_USSD_LEN + 1];  // The SS string entered by user
} SSSRV_CallWaitingReq_t;


//Call Waiting Confirmation
typedef struct
{
    MMI_SSSRV_CallClass_e CallClass;  // call class
    MMI_SSSRV_SS_Status_e Status;     // active or deactive
} SSSRV_CwxInfo_t;

typedef struct
{
    MMI_SSSRV_SS_Result_e Result;
    u8 NbCwxInfo;
    SSSRV_CwxInfo_t CwxInfo[MAX_SS_CWXINFO_NO];
} SSSRV_CallWaitingCnf_t;

//Line Identity query Request
typedef struct
{
    MMI_SSSRV_CI_ReqType_e ClxType;
} SSSRV_ClxInt_t;

//Line Identity query Confirmation
typedef struct
{
    MMI_SSSRV_SS_Result_e Result;
    MMI_SSSRV_SS_Status_e NetworkStatus;    // the subscriber status in the network 
    u8 TaStatus;         // NbClxInfo;
} SSSRV_ClxCnf_t;

//Call Barring Request
typedef struct
{
    MMI_SSSRV_ReqType_e ReqType;                   // activate/deactivate/interogate
    MMI_SSSRV_CBX_Type_e CbxType;                   // call barring type
    MMI_SSSRV_CallClass_e CallClass;                    // call class
    u8 Password[MAX_SS_CB_PWD_LEN + 1];  // password
    u8 u8UssdString[MAX_SS_SEND_USSD_LEN + 1];  // The SS string entered by user
} SSSRV_CallBarringReq_t;

//Call Barring Confirmation
typedef struct
{
    MMI_SSSRV_SS_Status_e Status;
    MMI_SSSRV_CallClass_e CallClass;
} SSSRV_CbxInfo_t;

typedef struct
{
    MMI_SSSRV_SS_Result_e Result;
    u8 NbCbxInfo;
    SSSRV_CbxInfo_t CbxInfo[MAX_SS_CBXINFO_NO];
} SSSRV_CallBarringCnf_t;

//Change Barring Password Request
typedef struct
{
    MMI_SSSRV_CBX_Type_e CbxType;                    // call barring type
    u8 CurrentPwd[MAX_SS_CB_PWD_LEN + 1];
    u8 NewPwd[MAX_SS_CB_PWD_LEN + 1];
    u8 u8UssdString[MAX_SS_SEND_USSD_LEN + 1];  // The SS string entered by user
} SSSRV_ChangeBarringPwdReq_t;

//Change Barring Password Confirmation
typedef struct
{
    MMI_SSSRV_SS_Result_e Result;  // OK or Error
} SSSRV_ChangeBarringPwdCnf_t;

//USSD Request
typedef struct
{
    MMI_SSSRV_USSD_Action_Type_e ActionType; //USSD_ACTION_TYPE_USER_INITIAL or USSD_ACTION_TYPE_USER_RESPONSE
    u8 CodScheme; 
    u8 data[MAX_SS_SEND_USSD_LEN + 1];
} SSSRV_USSDReq_t
,SSSRV_USSDRsp_t;

//USSD Confirmation
typedef struct
{
    MMI_SSSRV_USSD_Status_e Indication;                 
    u8 CodScheme;
    u16 DataLength;
    u8 data[MAX_SS_RECEIVE_USSD_LEN + 1];
} SSSRV_USSDCnf_t
,SSSRV_USSDInd_t
,SSSRV_USSDNot_t;

//USSD Error
typedef struct
{
    MMI_SSSRV_SS_Result_e Result;
    MMI_SSSRV_USSD_Status_e Status;
} SSSRV_USSDErr_t;


//Closed User Group Request
typedef struct
{
    MMI_SSSRV_SS_Status_e Status;  //CUG activation mode
    u8 Index;   //CUG index, 0-10
    MMI_SSSRV_CUGInfo_e Info;   //CUG actions
} SSSRV_UserGroupReq_t;

typedef struct
{
    MMI_SSSRV_SS_Result_e Result;   //Result code
    MMI_SSSRV_SS_Status_e Status;  //CUG activation mode
    u8 Index;   //CUG index, 0-10
    MMI_SSSRV_CUGInfo_e Info;   //CUG actions
} SSSRV_UserGroupQueCnf_t;


//Advise of Charge Request
typedef struct
{
    MMI_SSSRV_AOC_ReqType_e RegType;    //Query or reset ACM value.
} SSSRV_AOCReq_t;

typedef struct
{
    MMI_SSSRV_SS_Result_e Result;                           //Result code
    u8 CCMValue[MAX_SS_CCM_LENGTH + 1]; //Current call meter value
} SSSRV_AOCCnf_t;

typedef struct
{
    u32 Pad;    //padding
} SSSRV_AOCQueReq_t;

typedef struct
{
    MMI_SSSRV_SS_Result_e Result;   //Result code
    MMI_SSSRV_AOC_Status_e Status;  //Activate/Deactivate
} SSSRV_AOCQueCnf_t;

typedef struct
{
    MMI_SSSRV_ACM_ReqType_e RegType;                    //Query or reset ACM value.
    u8 Pin2[MAX_SS_PIN2_LENGTH + 1];    //Pin2
} SSSRV_ACMReq_t;

typedef struct
{
    MMI_SSSRV_SS_Result_e Result;                           //Result code
    u8 ACMValue[MAX_SS_ACM_LENGTH + 1]; //Accumulated call meter value
} SSSRV_ACMCnf_t;

typedef struct
{
    MMI_SSSRV_AMM_ReqType_e RegType;                        //Query or update AMM value.
    u8 Pin2[MAX_SS_PIN2_LENGTH + 1];        //Pin2
    u8 ACMmax[MAX_SS_AMM_LENGTH + 1];   //Accumulated call meter maximum value
} SSSRV_ACMMaxReq_t;

typedef struct
{
    MMI_SSSRV_SS_Result_e Result;                           //Result code
    u8 ACMmax[MAX_SS_AMM_LENGTH + 1];   //Accumulated call meter maximum value
} SSSRV_ACMMaxCnf_t;

typedef struct
{
    MMI_SSSRV_PUC_ReqType_e RegType;                            //Query or update PCU settings.
    u8 Pin2[MAX_SS_PIN2_LENGTH + 1];            //Pin2
    u8 Ppu[MAX_SS_PPU_LENGTH + 1];          //Price per unit
    u8 Currency[MAX_SS_CURRENCY_LENGTH + 1];    //Currency code
} SSSRV_PUCReq_t;

typedef struct
{
    MMI_SSSRV_SS_Result_e Result;                               //Result code
    u8 Ppu[MAX_SS_PPU_LENGTH + 1];              //Price per unit
    u8 Currency[MAX_SS_CURRENCY_LENGTH + 1];    //Currency code
} SSSRV_PUCCnf_t;


//CSSI Notification
typedef struct
{
    u8 ServiceCode; //manufacturer specific service code
    u8 Index;           //Closed User Group call, with CUG <index>
} SSSRV_CssiNot_t;


//Message Union
typedef union
{
    SSSRV_CallDivertReq_t CallDivertReq;
    SSSRV_CallBarringReq_t CallBarringReq;
    SSSRV_CallWaitingReq_t CallWaitingReq;
    SSSRV_ChangeBarringPwdReq_t ChangeBarringPwdReq;
    SSSRV_ClxInt_t CLXCnf;
} SSSRV_unReqMsg_t;

typedef union
{
    SSSRV_CallDivertCnf_t CallDivertCnf;
    SSSRV_CallBarringCnf_t CallBarringCnf;
    SSSRV_CallWaitingCnf_t CallWaitingCnf;
    SSSRV_USSDCnf_t USSDCnf;
    SSSRV_USSDInd_t USSDInd;
    SSSRV_USSDErr_t USSDErr;
    SSSRV_USSDNot_t USSDNot;
    SSSRV_UserGroupQueCnf_t CUGCnf;
    SSSRV_AOCCnf_t AOCCnf;
    SSSRV_AOCQueCnf_t AOCQueCnf;
    SSSRV_ACMCnf_t ACMCnf;
    SSSRV_ACMMaxCnf_t AMMCnf;
    SSSRV_PUCCnf_t PUCCnf;
    SSSRV_ClxCnf_t CLXCnf;
} SSSRV_unMsg_t;

//Create USSD AP structure
typedef union
{
    SSSRV_USSDReq_t USSDReq;
    SSSRV_USSDNot_t USSDNot;
} SSSRV_unUSSDAppMsg_t;

typedef struct
{
    MMI_SSSRV_USSD_SIM_Type_e SIMType;
    MMI_SSSRV_USSD_Action_Type_e ReqType;       
    SSSRV_unUSSDAppMsg_t ReqData;
} SSSRV_CreateUSSDAppReq_t;

#endif /* __MMI_SSSRV_DEF_H__ */
