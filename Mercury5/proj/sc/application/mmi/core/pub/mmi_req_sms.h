/**
 * @file    mmi_req_sms.h
 * @brief   The file handles all the message request function to RIL
 * @author  joe.hsu
 * 
 * @version $Id: mmi_req_sms.h 30004 2009-05-05 12:33:45Z jorena.ku $
 */
#ifndef __MMI_REQ_SMS_H__
#define __MMI_REQ_SMS_H__


#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_if_sms.h"

/*
#define MMI_SMS_PDU_SIZE_MAX 175
#define MMI_SCA_LEN_MAX      21

typedef enum
{
  MMI_SMS_SM,
  MMI_SMS_ME,
  MMI_SMS_SR,
  MMI_SMS_BM  
}MMI_SMS_StorageArea_e;

typedef enum
{
  MMI_SMS_REC_UNREAD,             // 0 
  MMI_SMS_REC_READ,               // 1
  MMI_SMS_STO_UNSENT,             // 2
  MMI_SMS_STO_SENT,               // 3
  MMI_SMS_STATUS_INVALID = 0xFF  
}MMI_SMS_Status_e;
*/
#define MMI_CB_MID_NUM_MAX  10

typedef struct
{
  u8 SimModule;
  u8 DataLength;
  u8 PduData[MMI_SMS_PDU_SIZE_MAX];
}MMI_SMS_MoReq_t;

typedef struct
{
  u8					 SimModule;
  MMI_SMS_StorageArea_e  StorageArea;      // AT+CPMS  SIM/flash/Status Report/CBM
  u16                    Index;            // Index of a certain storage area 
}MMI_SMS_ReadReq_t;                 // Read a certain message

typedef struct
{
  u8					 SimModule;
  MMI_SMS_StorageArea_e  StorageArea;      // AT+CPMS SIM/flash/Status Report/CBM
  MMI_SMS_Status_e		 Status;
  u8                     SmscByteLen; //prefix number of bytes of the PduData is the Smsc data
  u8                     DataLength;  //The number of bytes of the PduData (Including the Smsc Byte Len)
  u8                     PduData[MMI_SMS_PDU_SIZE_MAX]; 
}MMI_SMS_StoreReq_t;

typedef enum
{
  MMI_DEL_INDEX,
  MMI_DEL_READ,
  MMI_DEL_READ_SENT,
  MMI_DEL_READ_SENT_UNSENT,
  MMI_DEL_ALL
}MMI_SMS_DelFlag_t;
typedef struct
{
  u8					 SimModule;
  MMI_SMS_StorageArea_e  StorageArea;   // AT+CPMS SIM/flash/Status Report/CBM
  u8                     Index;
  MMI_SMS_DelFlag_t      DelFlag;
}MMI_SMS_DelReq_t;

/*
typedef enum {
	national = 129,
    international = 145      
}MMI_SMS_ScaType_e;
*/

typedef struct
{
  u8				   SimModule;
  s8 Sca[MMI_SCA_LEN_MAX+1];
  MMI_SMS_ScaType_e    Tosca;                   // Type of Service center address
}MMI_SMS_SetSCAReq_t;

typedef struct
{
  u8					SimModule;
  MMI_SMS_StorageArea_e StorageArea;   // AT+CPMS SIM/flash/Status Report/CBM
  u16                   Location;
  MMI_SMS_Status_e      NewStatus;     // The status to change to
}MMI_SMS_ModStatusReq_t;

typedef enum
{
  MMI_VP_12H = 143,
  MMI_VP_1D = 167,
  MMI_VP_3D = 169,
  MMI_VP_1W = 173,
  MMI_VP_MAX = 255
}MMI_SMS_VP_e;
typedef struct
{
  u8			SimModule;
  u8			Fo;        /* first octet */
  MMI_SMS_VP_e	Vp;        /* valid period */
  u8			Pid;       /* PID */
  u8			Dcs;       /* DCS */
}MMI_SMS_SetParamReq_t;

typedef struct
{
  u8					SimModule;
  MMI_SMS_StorageArea_e RecvStorage;  
}MMI_SMS_SetRecvStorageReq_t;


typedef enum
{
  MMI_ME_SMS_READ,
  MMI_ME_SMS_STORE,
  MMI_ME_SMS_DELETE
}MMI_SMS_OP_t;

typedef enum
{
  MMI_READ_SUCCESSFULLY,
  MMI_READ_UNSUPPORT_STORAGE,
  MMI_READ_NOT_FOUND,
  MMI_READ_OUT_OF_RANGE,
  MMI_STORE_SUCCESSFULLY,
  MMI_STORE_NOT_SUPPORTED,
  MMI_STORE_MEMORY_FULL,
  MMI_STORE_OUT_OF_RANGE,
  MMI_STORE_CLASS2,
  MMI_DELETE_SUCCESSFULLY,
  MMI_DELETE_NOT_SUPPORTED,
  MMI_DELETE_LOCATION_EMPTY,
  MMI_DELETE_OUT_OF_RANGE,
  MMI_UNKNOW_ERROR
}MMI_SMS_OPRslt_t;

typedef struct
{
  u8				 SimModule;
  MMI_SMS_Area_t	 Area;           //SMS opreation store area
  MMI_SMS_OP_t		 Opeartion;      //SMS opreation type
  MMI_SMS_OPRslt_t   Result;         //Result of the operation
  u16                Index;          //Index of SMS , only needed when operation is sotre
}MMI_SMS_SetStoreMeIndexReq_t;

typedef struct
{
  u8				 SimModule;
  MMI_SMS_Area_t	 Area;           //SMS opreation store area
  u16                Sent;
  u16                Unsent;
  u16                Read;
  u16                Unread;
  u16                max;
  u16                used; 
}MMI_SMS_SetCapacityReq_t;

typedef struct
{
  u8   SimModule;
  u8   NbMID;     // Number of Message IDs
  u16 MIDPtr[MMI_CB_MID_NUM_MAX];    // Array of first MID  	
}MMI_CB_SetCBMIReq_t;

typedef enum
{
  MMI_SMS_CBMODE_ACTIVATED        = 0,      /* activation of CBM reception      */
  MMI_SMS_CBMODE_DEACTIVATED      = 1       /* de-activation of CBM reception   */

}MMI_SMS_CBMode_e;

typedef struct
{
  u8				SimModule;
  MMI_SMS_CBMode_e	Mode;
  u8				NbMID;     // Number of Message IDs
  u16				MIDPtr[MMI_CB_MID_NUM_MAX];    // Array of first MID  	
}MMI_CB_ActiveCBMIReq_t;

typedef struct
{
  u8				SimModule;
  MMI_SMS_CBMode_e	Mode;
  u8				NbMID;     // Number of Message IDs  
  u16	            sMIDPtr[MMI_CB_MID_NUM_MAX];	               // Array of start MID
  u16	            eMIDPtr[MMI_CB_MID_NUM_MAX];	               // Array of end MID

}MMI_CB_ActiveRngCBMIReq_t;


// need to been modified
typedef struct
{
  MMI_SMS_CBMode_e  mode;       // activate or de-activate CBM
  u8                NbMID;      // Number of Message IDs
  u16               sMIDPtr[MMI_CB_MID_NUM_MAX];    // Array of start MID  
  u16               eMIDPtr[MMI_CB_MID_NUM_MAX];    // Array of end MID
}MMI_SMS_SetCBMTypeReq_t;

typedef struct
{	
	u8					SimModule;
	u8					Value;
}MMI_SMS_SetStatusReportReq_t;

enum
{
  MMI_MORE_MSG_SEND_DIABLE        = 0,      /* diable CMMS      */
  MMI_MORE_MSG_SEND_KEEP_LINK     = 1       /* enable CMMS   */
};
typedef u8 MMI_SMS_SetMoreMsgMode_e;

typedef struct
{
  u8 SimModule;
  MMI_SMS_SetMoreMsgMode_e Mode; 
}MMI_SMS_SetMoreMsgReq_t;

void mmi_sms_mo_req(MMI_SMS_MoReq_t *pSmMoReq);
void mmi_sms_read_req(MMI_SMS_ReadReq_t *pSmReadReq);
void mmi_sms_store_req(MMI_SMS_StoreReq_t *pSmStoreReq);
void mmi_sms_del_req(MMI_SMS_DelReq_t *pSmDelReq);
void mmi_sms_set_sca_req(MMI_SMS_SetSCAReq_t *pSmSetScaReq);
void mmi_sms_query_sca_req(u8 simModule);
void mmi_sms_mod_status_req(MMI_SMS_ModStatusReq_t *pSmModStatusReq);
void mmi_sms_query_storage_req(u8 simModule);
void mmi_sms_set_param_req(MMI_SMS_SetParamReq_t *pSmSetParamReq);
void mmi_sms_query_param_req(u8 simModule);
void mmi_sms_set_recv_storage_req(MMI_SMS_SetRecvStorageReq_t *pSmSetRecvStorageReq);
void mmi_sms_set_capacity_req(MMI_SMS_SetCapacityReq_t *pSmSetCapacityReq);
void mmi_sms_set_store_me_index_req(MMI_SMS_SetStoreMeIndexReq_t *pSmSetStoreMeIndexReq);
void mmi_sms_set_status_report_req(MMI_SMS_SetStatusReportReq_t *pSmSetStatusReportReq);
void mmi_sms_set_more_msg_req(MMI_SMS_SetMoreMsgReq_t *pSmSetMoreMsgReq);

void mmi_sms_abort_req(u8 simModule);

void mmi_cb_set_cbmi_req(MMI_CB_SetCBMIReq_t *pCbSetCbmiReq);
void mmi_cb_activ_cbmi_req(MMI_CB_ActiveCBMIReq_t *pCbActiveCbmiReq);
void mmi_cb_activ_rng_cbmi_req(MMI_CB_ActiveRngCBMIReq_t *pCbActiveRngCbmiReq);

void mmi_sms_query_cbmi_req(void);

void mmi_sms_set_cbm_type_req(MMI_SMS_SetCBMTypeReq_t *pSmSetCbmTypeReq);

#ifdef __Test_SMS__
void mmi_sms_register_msg_req(IBase *pInstance);
void mmi_sms_dereg_msg_req(IBase *pInstance);
#endif

#endif /* __MMI_REQ_SMS_H__ */
