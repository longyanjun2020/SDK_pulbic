/**
 * @file    mmi_cphssrv_def.h
 * @brief   xxxx
 * @version $Id:
 */

#ifndef __MMI_CPHSSRV_DEF_H__
#define __MMI_CPHSSRV_DEF_H__

enum
{
    MMI_CPHSSRV_LINE_E_UNKNOW = 0
   ,MMI_CPHSSRV_LINE_E_START = 1
   ,MMI_CPHSSRV_LINE_1 = 1
  , //Line 1
    MMI_CPHSSRV_LINE_2 = 2
  , //Line 2
    MMI_CPHSSRV_DATA = 3
,   //Data
    MMI_CPHSSRV_FAX = 4
,    //Fax
    MMI_CPHSSRV_LINE_E_TOTAL
};
typedef u8 MMI_CPHSSRV_Line_Service_e;

#define MMI_CPHSSRV_NUM_SERVICE (MMI_CPHSSRV_LINE_E_TOTAL-MMI_CPHSSRV_LINE_E_START)

typedef enum
{
    MMI_CPHSSRV_VM_LINE1_OFF = 1
 ,  // line1 doesn't have voice mail
    MMI_CPHSSRV_VM_LINE1_ON = 2
,   // line1 has voice mail
    MMI_CPHSSRV_VM_LINE2_OFF = 3
 ,  // line2 doesn't have voice mail
    MMI_CPHSSRV_VM_LINE2_ON = 4
,   // line2 has voice mail
    MMI_CPHSSRV_VM_DATA = 5
   ,MMI_CPHSSRV_VM_FAX = 6,
} MMI_CPHSSRV_VM_Status_e;

typedef enum
{
    MMI_CPHSSRV_VM_OFF = 0
   ,MMI_CPHSSRV_VM_ON = 1
} MMI_CPHSSRV_VM_Check_e;

// result map to api_mrl_cphs.h : Mrl_CPHS_Rslt_e
typedef enum
{
    MMI_CPHSSRV_RESULT_RSLT_OK = 0
   ,/* Success                                          */
    MMI_CPHSSRV_RESULT_OPERATION_NOT_ALLOWED = 3
   ,/* Operation not allowed                            */
    MMI_CPHSSRV_RESULT_OPERATION_NOT_SUPPORTED = 4
   ,/* Operation not supported                          */
    MMI_CPHSSRV_RESULT_SIM_NOT_INSERTED = 10
   ,/* SIM not inserted                                 */
    MMI_CPHSSRV_RESULT_SIM_FAILURED = 13
   ,/* SIM failured                                     */
    MMI_CPHSSRV_RESULT_NO_NETWORK_SERVICE = 30
   ,/* No network service                               */
    MMI_CPHSSRV_RESULT_RSLT_UNKNOWN_ERROR = 500
   ,/* Unknown SMS error                                */
    MMI_CPHSSRV_RESULT_PIN_DEACT_FORBIDDEN = 526
   ,/* PIN deactivation forbidden with this SIM card    */
    MMI_CPHSSRV_RESULT_PUK1_BURNED = 553
   ,/* PUK1 code is burned but PIN1/CHV1 code is OK     */
    MMI_CPHSSRV_RESULT_SIM_BLOCKED = 554       /* SIM blocked. (PIN1/CHV1 PUK1 codes are burned)   */
}MMI_CPHSSRV_Result_e;

enum
{
    MMI_CPHS_DEACTIVE
,     // 0
    MMI_CPHS_ACTIVE
,       // 1  
    MMI_CPHS_INTERROGATE
 ,  // 2
    MMI_CPHS_NONE          // 3
};
typedef u8 MMI_CPHS_Mode_e;

typedef enum
{
    MMI_CPHS_VOICE_MAIL_INDICATOR = 1
  , // 1
    MMI_CPHS_MAIL_BOX_NUMBER = 2
  , // 2        
    MMI_CPHS_ALTERNATE_LINE_SERVICE = 3
  , // 3
    MMI_CPHS_DIVERTED_CALL_INDICATOR = 4
  , // 4
    MMI_CPHS_NETWORK_OPERATOR_NAME = 5
  , // 5
    MMI_CPHS_INFORMATION = 6
  , // 6
    MMI_CPHS_CUSTOMER_SERVICE_PROFILE = 7  // 7  
}MMI_CPHS_FCTLD_e;
#define MMI_CPHSSRV_NUM_FCTLD    7

enum
{
    MMI_TYPE_EMPTY = 0
   ,MMI_TYPE_UNKNOW = 0xFE
,            //Not get the confirm of the voice mail number request yet
    MMI_TYPE_NONE = 0xFF
,           //Get fail response from the voice mail number request
    MMI_NATIONAL_TYPE = 129
   ,MMI_INTERNATIONAL_TYPE = 145
};
typedef u8 MMI_CPHS_Type_e;

#define MailNumberSize 20   //Mrl_CPHS_MAIL_BOX_SIZE
#define MailNameSize 20     //Mrl_CPHS_MAIL_BOX_SIZE

#ifdef __3G_RIL_MMI__
typedef enum
{
  MMI_NON_TYPE_LONG_FORMAT_OPERATOR_NAME, // 0
  MMI_NON_TYPE_SHORT_FORMAT_OPERATOR_NAME, // 1
  MMI_NON_TYPE_DEFAULT_FORMAT_OPERATOR_NAME // 2
  
} MMI_CPHS_NON_FORMATE_e;
#endif // __3G_RIL_MMI__

// voice mail status ind
typedef struct
{
    u8 u8Line;
    u8 u8VoiceMailLineStatus;
} CPHSSRV_VMInd_t; 

// query voice mail cnf
typedef struct
{
    MMI_CPHSSRV_Result_e eMrlCphsRslt;
    u8 au8VoiceMailLineStatus[4];
} CPHSSRV_QueryVMCnf_t; 

// query line status
typedef struct
{
    MMI_CPHSSRV_Result_e eMrlCphsRslt;
    u8 u8Activeline;
} CPHSSRV_QueryLineCnf_t;

typedef struct
{
    MMI_CPHSSRV_Result_e eMrlCphsRslt;
    u8 MailLineStatus[MMI_CPHSSRV_NUM_SERVICE];
    u8 MailNumber[MMI_CPHSSRV_NUM_SERVICE][MailNumberSize];
    u8 Type[MMI_CPHSSRV_NUM_SERVICE];
    u8 MailName[MMI_CPHSSRV_NUM_SERVICE][MailNameSize];
}CPHSSRV_QueryMailBoxCnf_t; 

typedef struct
{
    MMI_CPHSSRV_Result_e eMrlCphsRslt;
}CPHSSRV_SetMailBoxNumberCnf_t; 

typedef struct
{
    MMI_CPHSSRV_Result_e eMrlCphsRslt;
}CPHSSRV_SetResponse_t; 

// read cphs functionality cnf
typedef struct
{
    MMI_CPHSSRV_Result_e eMrlCphsRslt;
    u8 bActivate[MMI_CPHSSRV_NUM_FCTLD];
} CPHSSRV_ReadFunctionalityCnf_t; 

#ifdef __3G_RIL_MMI__
#define MMI_CPHSSRV_OPERATOR_NAME_MAX_SIZE 31
typedef struct
{
  MMI_CPHSSRV_Result_e eMrlCphsRslt;
  u8 OperatorName[MMI_CPHSSRV_OPERATOR_NAME_MAX_SIZE];
  u8 ShortName[MMI_CPHSSRV_OPERATOR_NAME_MAX_SIZE];
} CPHSSRV_NetworkOperatorCnf_t;
#endif // __3G_RIL_MMI__

//Message Union
typedef union
{
    CPHSSRV_VMInd_t tVMInd;
    CPHSSRV_QueryVMCnf_t tQueryVMCnf;
    CPHSSRV_QueryLineCnf_t tQueryLineCnf;
    CPHSSRV_QueryMailBoxCnf_t tQueryMailBoxCnf;
    CPHSSRV_SetMailBoxNumberCnf_t tSetMailBoxCnf;
    CPHSSRV_SetResponse_t tSetResponse;
    CPHSSRV_ReadFunctionalityCnf_t tReadFunctionalityCnf;
#ifdef __3G_RIL_MMI__
    CPHSSRV_NetworkOperatorCnf_t tQueryNonCnf;
#endif // __3G_RIL_MMI__
} CPHSSRV_unMsg_t;

#endif /* __MMI_CPHSSRV_DEF_H__ */
