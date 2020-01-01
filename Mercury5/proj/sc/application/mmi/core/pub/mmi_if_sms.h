/**
 * @file    mmi_if_sms.h
 * @brief   The file handles the RIL SMS event and forward to SMS Kernel
 * @author  joe.hsu
 * 
 * @version $Id: mmi_if_sms.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */
#ifndef __MMI_IF_SMS_H__
#define __MMI_IF_SMS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"


#define MMI_SMS_PDU_SIZE_MAX 175
#define MMI_SCA_LEN_MAX      21
#define MMI_CB_PDU_SIZE_MAX  93

typedef enum
{
  MMI_SMS_SM,
  MMI_SMS_ME,
  MMI_SMS_SR,
  MMI_SMS_BM,
  MMI_SMS_NONE
}MMI_SMS_StorageArea_e;

typedef enum
{
  MMI_SMS_REC_UNREAD,             // 0 
  MMI_SMS_REC_READ,               // 1
  MMI_SMS_STO_UNSENT,             // 2
  MMI_SMS_STO_SENT,               // 3
  MMI_SMS_STATUS_INVALID = 0xFF  
}MMI_SMS_Status_e;

typedef enum
{
  MMI_SMS_NEW_SMS_BUT_MEM_FULL

}MMI_SMS_Event_e;

typedef enum
{
  MMI_SMS_RSLT_OK                   = 0,     /* Success  */
  MMI_SMS_PARTIAL_FAIL				= 300,   /* Partial Fail for MMI        */
  MMI_SMS_RSLT_SERV_RES             = 301,   /* SMS service of ME reserved  */
  MMI_SMS_RSLT_OPERA_NOTALL         = 302,   /* Operation not allowed       */
  MMI_SMS_RSLT_OPERA_NOTSUP         = 303,   /* Operation not supported     */
  MMI_SMS_RSLT_INVAL_PDUPA          = 304,   /* Invalid PDU  mode parameter */
  MMI_SMS_RSLT_INVAL_TEXTPA         = 305,   /* Invalid text mode parameter */
  MMI_SMS_RSLT_SIM_NOT_INS_SMS      = 310,   /* SIM not inserted            */
  MMI_SMS_RSLT_SIM_PIN_REQ_SMS      = 311,   /* SIM PIN required            */
  MMI_SMS_RSLT_PHSIM_PIN_REQ_SMS    = 312,   /* PH-SIM PIN required         */
  MMI_SMS_RSLT_SIM_FAIL             = 313,   /* SIM failure                 */
  MMI_SMS_RSLT_SIM_PUK_REQ_SMS      = 316,   /* SIM PUK required            */
  MMI_SMS_RSLT_INVAL_MEMIND         = 321,   /* Invalid memory index        */
  MMI_SMS_RSLT_MEM_FULL             = 322,   /* SIM memory full             */
  MMI_SMS_RSLT_ADRSMSC_UNKN         = 330,   /* SC address unknown          */
  MMI_SMS_RSLT_NO_ACK_EXPECTED      = 340,   /* no +CNMA ack. expected      */
  MMI_SMS_RSLT_UNKNOWN_ERROR        = 500,   /* Unknown SMS error */
  MMI_SMS_RSLT_ABORTED				= 501,   /* Aborted by other command */
  MMI_SMS_RSLT_MM_ESTABLIS_FAIL     = 512,   /* MM_ESTABLIS_FAIL */
  MMI_SMS_RSLT_LOWER_LAYER_FAIL     = 513,   /* LOWER_LAYER_FAIL */
  MMI_SMS_RSLT_CP_ERROR             = 514,	 /* AT_CP_ERROR */
  MMI_SMS_RSLT_PLEASE_WAIT          = 515    /* AT_PLEASE_WAIT, Busy! Init in progress*/
}MMI_SMS_Rslt_e;

typedef enum {
	national = 129,
    international = 145      
}MMI_SMS_ScaType_e;

typedef enum
{
  MMI_SMS_AREA_ME,
  MMI_SMS_AREA_SR_ME
}MMI_SMS_Area_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt;  
}MMI_SMS_BaseCnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt;
  u8 MsgReference;   
}MMI_SMS_MoCnf_t;

typedef struct 
{
  u8					SimModule;
  MMI_SMS_Rslt_e        MmiSmsRslt;
  MMI_SMS_Status_e      Status;            // read/unread/sent/unsent 
  u8                    DataLength;
  u8                    PduData[MMI_SMS_PDU_SIZE_MAX];
}MMI_SMS_ReadCnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt;
  u16 Index;            // Message stored at Index +CMGW:<index>
}MMI_SMS_StoreCnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt;
}MMI_SMS_DelCnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt;
}MMI_SMS_SetSCACnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt;
  s8 Sca[MMI_SCA_LEN_MAX+1]; 
  MMI_SMS_ScaType_e    Tosca;                  // Type of Service center address
}MMI_SMS_QuerySCACnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt;
}MMI_SMS_ModStatusCnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt; 
  u16 SmsSIMSpaceTotal;
  u16 SmsSIMSpaceUsed;
  u16 SmsMESpaceTotal;
  u16 SmsMESpaceUsed;
  u16 CBSpaceTotal;
  u16 CBSpaceUsed;
  u16 SRSpaceTotal;
  u16 SRSpaceUsed;  
}MMI_SMS_QueryStorageCnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt;  
}MMI_SMS_SetParamCnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt;
  u8 Fo;        /* first octet */
  u8 Vp;        /* valid period */
  u8 Pid;       /* PID */
  u8 Dcs;       /* DCS */  
}MMI_SMS_QueryParamCnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt;  
}MMI_SMS_SetRecvStorageCnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt; 
}MMI_SMS_SetStoreMeIndexCnf_t;

typedef struct
{
  u8			 SimModule;
  MMI_SMS_Rslt_e MmiSmsRslt; 
}MMI_SMS_SetCapacityCnf_t;

typedef struct
{
	u8					SimModule;
    MMI_SMS_Area_t		Area;           //SMS opreation store area
	u16                 Index;
    MMI_SMS_Status_e    Status;  
    u8                  DataLength;
    u8					PduData[MMI_SMS_PDU_SIZE_MAX*2];
}MMI_SMS_StoreMEReqInd_t;

typedef struct
{
  u8					 SimModule;
  MMI_SMS_StorageArea_e  StorageArea;  // +CMTI:<mem>,<index>
  u16                    Index; 
  u8                     PduData[MMI_SMS_PDU_SIZE_MAX];
  u8                     DataLength;  
}MMI_SMS_MTInd_t;

typedef struct
{
  MMI_SMS_StorageArea_e  StorageArea;  // +CBMI:<mem>,<index>
  u16                    Index; 
  u8                     PduData[MMI_SMS_PDU_SIZE_MAX];  
  u8                     DataLength;
}MMI_SMS_CBInd_t;

typedef struct
{ 
  MMI_SMS_StorageArea_e  StorageArea;  // +CDSI:<mem>,<index>
  u16                    Index; 
  u8                     PduData[MMI_SMS_PDU_SIZE_MAX];
  u8                     DataLength;  
}MMI_SMS_SRInd_t;

typedef struct
{
  MMI_SMS_Event_e  Event;
}MMI_SMS_Event_Ind_t;


typedef struct
{  
  u8                     PduData[MMI_CB_PDU_SIZE_MAX];  
  u8                     DataLength;
}MMI_CB_Ind_t;

typedef struct
{
  MMI_SMS_Rslt_e MmiSmsRslt;
}MMI_SMS_SetCBMICnf_t;

typedef struct
{
  MMI_SMS_Rslt_e MmiSmsRslt;
}MMI_SMS_SetRngCBMICnf_t;

typedef struct
{
  MMI_SMS_Rslt_e MmiSmsRslt;
}MMI_CB_ActiveCBMICnf_t;

typedef struct
{
  MMI_SMS_Rslt_e MmiSmsRslt;
}MMI_CB_ActiveRngCBMICnf_t;

typedef struct
{
  MMI_SMS_Rslt_e MmiSmsRslt;
}MMI_SMS_SetCBMTypeCnf_t;

typedef struct
{  
  u8                NbMID;      // Number of Message IDs
  u16               *MIDPtr;    // Pointer of first MID
  MMI_SMS_Rslt_e    MmiSmsRslt;
}MMI_SMS_QueryCBMICnf_t;

typedef struct
{
	MMI_SMS_Rslt_e Rslt; 
	u8			   SimModule;	
}MMI_SMS_SetStatusReportCnf_t;

typedef struct
{
	MMI_SMS_Rslt_e MmiSmsRslt; 
	u8			   SimModule;	
}MMI_SMS_SetMoreMsgCnf_t;

void mmi_sms_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_cb_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void sms_request_not_supported(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_mo_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_read_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_store_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_del_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_set_sca_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_query_sca_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_mod_status_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_query_storage_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_set_param_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_query_param_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_set_recv_storage_cnf(IBase* pRecipient, struct vm_msg *pData);

void mmi_sms_set_store_me_index_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_set_capacity_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_store_req_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_set_status_report_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_set_more_msg_cnf(IBase* pRecipient, struct vm_msg *pData);

void mmi_sms_ready_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_mt_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_cb_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_sr_ind(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_event_ind(IBase* pRecipient, struct vm_msg *pData);

void mmi_cb_set_cbmi_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_cb_set_rng_cbmi_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_cb_active_cbmi_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_cb_active_rng_cbmi_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_cb_ind(IBase* pRecipient, struct vm_msg *pData);

void mmi_sms_query_cbmi_cnf(IBase* pRecipient, struct vm_msg *pData);
void mmi_sms_set_cbm_type_cnf(IBase* pRecipient, struct vm_msg *pData);

void mmi_sms_FreeCnfInfo(IBase *pOwner, u32 lParam, u32 dParam);

#endif /* __MMI_IF_SMS_H__ */
