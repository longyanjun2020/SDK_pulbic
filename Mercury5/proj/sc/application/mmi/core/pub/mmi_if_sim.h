/**
 * @file    mmi_if_sim.h
 * @brief   The file handles the RIL SIM/SEC event and forward to SIM/SEC service
 * @author  christine.tai@mstarsemi.com
 * 
 */
#ifndef __MMI_IF_SIM_H__
#define __MMI_IF_SIM_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_simsrv_def.h"
#include "mmi_stksrv_def.h"

typedef enum
{
	SIM_RSLT_OK						 = 0,
	SIM_RSLT_NO_RESPOND				 = 0xFFFF,
    SIM_RSLT_NORMAL_ENDING           = 0x9000, /**< normal ending of the cmd     */
    SIM_RSLT_RESP_DATA_LG            = 0x9F00, /**< lower byte = data length     */
    SIM_RSLT_MEMORY_PROBLM           = 0x9240, /**< memory problem               */
    SIM_RSLT_UPDATE_X_RETRY          = 0x9200, /**< lower byte= upd after x retry*/
    SIM_RSLT_NO_EF_SELECTED          = 0x9400, /**< no EF selected               */
    SIM_RSLT_OUT_OF_RANGE            = 0x9402, /**< out of range (invalid addres)*/
    SIM_RSLT_FP_NOT_FOUND            = 0x9404, /**< file/pattern not found       */
    SIM_RSLT_FILE_INCONSIST          = 0x9408, /**< file inconsistent w. the cmd */
    SIM_RSLT_NO_CHV_INITIAL          = 0x9802, /**< no CHV initialised           */
    SIM_RSLT_CHV_VERIF_FAIL          = 0x9804, /**< see GSM 11.11 p47            */
    SIM_RSLT_MISM_CHV_STATUS         = 0x9808, /**< in contradiction w CHV status*/
    SIM_RSLT_MISM_INV_STATUS         = 0x9810, /**< in cont. w invalidation stat.*/
    SIM_RSLT_CHV_BLOCKED             = 0x9840, /**< see SM 11.11 p47             */
    SIM_RSLT_MAX_VAL_REACHED         = 0x9850, /**< max value reached (increase) */
    SIM_RSLT_WRONG_P3                = 0x6700, /**< incorrect parameter P3       */
    SIM_RSLT_WRONG_P1_P2             = 0x6B00, /**< incorrect parameter P1 or P2 */
    SIM_RSLT_WRONG_INS_CODE          = 0x6D00, /**< unknown instruct. code in cmd*/
    SIM_RSLT_WRONG_INS_CLASS         = 0x6E00, /**< wrong instruct. class in cmd */
    SIM_RSLT_PROB_NO_DIAG            = 0x6F00, /**< tech. probl. w no diagnostic */
    SIM_RSLT_TLK_APPLI_BUSY          = 0x9300, /**< SIM Toolkit application busy */
    SIM_RSLT_TLK_FETCH_IND           = 0x9100, /**< lower byte = data length     */
    SIM_RSLT_TLK_DATA_DOWNLOAD_ERROR = 0x9E00  /**< lower byte = data length     */

} SIM_Rslt_e;

typedef struct
{
	SIM_Rslt_e	Result;
	u16			SimFile;
	u16			MemoryTotal;
	u16			FileStatus;
	u8			FileChar;
	u8			DataLength;
	u8			CHV1Status;
	u8			UNBKCHV1Status;
	u8			CHV2Status;
	u8			UNBKCHV2Status;
} SIM_FileStatusCnf_t;

typedef struct
{
	SIM_Rslt_e Result;
	u16 SimFile;	
	u8 *PtrData;
} SIM_FileReadCnf_t;

typedef struct
{
	SIM_Rslt_e Result;
	u32 Lang;	
} SIM_LpFileReadCnf_t;

typedef struct
{
	SIM_Rslt_e Result;
	u32 Number;	
} SIM_LpFileQueryCnf_t;

#ifdef __3G_RIL_MMI__
typedef struct
{
    u32 	result;
    u32     sst;   // 0:2G table, 1:3G table
    u8       allocated[21];	
    u8       activated[21];
} SIM_Msst_Cnf_t;
#endif //__3G_RIL_MMI__

typedef enum
{
	PIN_TYPE_PIN1 = 1,
	PIN_TYPE_PIN2 = 2
} SIM_PIN_TYPE_e;

typedef enum
{
	PIN_STATUS_NOK	= 0,
	PIN_STATUS_OK	= 1,
	PIN_STATUS_NOT_READY	= 2,
	PIN_STATUS_MISS	= 4
} SIM_PIN_STATUS_e;

typedef struct
{
	SIM_PIN_TYPE_e		PinType;
	SIM_PIN_STATUS_e	Status;	
	u8					RemAttpNum;
} SEC_PinRequestCnf_t;

typedef struct
{
	u8 Pin1RemAttpNum;	
	u8 Pin2RemAttpNum;	
	u8 Puk1RemAttpNum;	
	u8 Puk2RemAttpNum;	
} SEC_PinStatusCnf_t;

typedef enum
{
    SIM_FAC_PS      =  0,       // SIM lock facility with a 8 digits password
    SIM_FAC_SC      =  1,       // PIN enabled (<mode = 1>)/disabled (<mode> = 0)
    SIM_FAC_AO      =  2,       // BAOC (Barr All Outgoing Calls)
    SIM_FAC_OI      =  3,       // BOIC (Barr Outgoing International Calls)
    SIM_FAC_OX      =  4,       // BOIC-exHC (Barr Outgoing International Calls except to Home Country)
    SIM_FAC_AI      =  5,       // BAIC (Barr All Incoming Calls)
    SIM_FAC_IR      =  6,       // BIC-Roam (Barr Incoming Calls when Roaming outside home country)
    SIM_FAC_AB      =  7,       // All Barring services
    SIM_FAC_AG      =  8,       // All outGoing barring services
    SIM_FAC_AC      =  9,       // All inComing barring services
    SIM_FAC_P2      = 10,       // Manage SIM PIN2/CHV2
    SIM_FAC_FD      = 11,       // SIM Fixed Dailing Numbers (FDN) memory feature (PIN2/CHV2 is required as <password>)
    SIM_FAC_PN      = 12,       // Network lock with a 8 digit password (NCK)
    SIM_FAC_PU      = 13,       // Network Subset lock with a 8 digit password (NSCK)
    SIM_FAC_PP      = 14,       // Service Provider lock with a 8 digit password (SPCK)
    SIM_FAC_PC      = 15        // Corporate lock with a 8 digit password (CCK)
} SIM_FAC_TYPE_e;

typedef enum
{
    SIM_FAC_STATUS_NOT_ACTIVE      =  0,        // Facility lock status not activate
    SIM_FAC_STATUS_ACTIVE          =  1,        // Facility lock status activate
  
} SIM_FAC_STATUS_e;

typedef struct
{
	SIM_FAC_TYPE_e   FacType;
	SIM_FAC_STATUS_e Status;	
} SEC_FacStatusCnf_t;

typedef struct
{
   u8 PinEnabled;           /* PIN enabled      */
   u8 PinRemainAtt;         /* PIN remain       */
   u8 PinBlocked;           /* PIN blocked      */
   u8 PukRemainAtt;         /* PUK remain       */
   u8 PukBlocked;           /* PUK blocked      */
   u8 Pin2RemainAtt;        /* PIN2 remain      */
   u8 Pin2Blocked;          /* PIN2 blocked     */
   u8 Puk2RemainAtt;        /* PUK2 remain      */
   u8 Puk2Blocked;          /* PUK2 blocked     */
   
} SEC_SimPinPuk_t;

typedef union{	    
    SIM_FileStatusCnf_t		SimFileStatusCnf;  
    SIM_FileReadCnf_t		SimFileReadCnf;
	SIM_LpFileReadCnf_t 	SimLpFileReadCnf;
	SIM_LpFileQueryCnf_t	SimLpFileQueryCnf;
	SEC_PinRequestCnf_t		SecPinRequestCnf;
	SEC_PinStatusCnf_t  	SecPinStatusCnf;
	SEC_SimPinPuk_t		SecPukBlockInd;
	SEC_FacStatusCnf_t      SecFacStatusCnf;
#ifdef __3G_RIL_MMI__
    SIM_Msst_Cnf_t          SimMsstCnf;
#endif // __3G_RIL_MMI__
} SIM_unMsg_t;

void mmi_sim_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_sec_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void mmi_sim_presence_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sim_absence_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sim_rack_open_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sim_rack_close_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sim_file_status_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sim_file_read_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sim_error_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sim_lp_read_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sim_lp_query_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sim_lp_write_cnf_if(IBase* pRecipient, struct vm_msg *pData);

#ifdef __3G_RIL_MMI__
void mmi_sim_imsi_read_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sim_sst_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#endif  // __3G_RIL_MMI__ 

void mmi_sec_pin_enable_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#ifndef __3G_RIL_MMI__
void mmi_sec_pin_disable_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#endif // !__3G_RIL_MMI__
void mmi_sec_pin_verify_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sec_pin_change_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sec_pin_unblock_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sec_pin_status_cnf_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sec_puk_blocked_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_sec_query_fac_lock_cnf_if(IBase* pRecipient, struct vm_msg *pData);

#ifdef __3G_RIL_MMI__
void mmi_sec_mgid_cnf_if(IBase* pRecipient, struct vm_msg *pData);
#endif // __3G_RIL_MMI__

void mmi_stk_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void mmi_stk_setup_menu_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_select_item_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_display_text_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_get_inkey_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_get_input_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_setup_call_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_play_tone_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_refresh_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_send_ss_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_send_sms_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_send_ussd_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_send_dtmf_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_setup_event_list_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_setup_idle_text_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_language_notification_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_launch_browser_ind_if(IBase* pRecipient, struct vm_msg *pData);
#ifdef __3G_RIL_MMI__
void mmi_stk_open_channel_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_receive_data_ind_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_stk_send_data_ind_if(IBase* pRecipient, struct vm_msg *pData);
#endif // __3G_RIL_MMI__
void mmi_stk_error_ind_if(IBase* pRecipient, struct vm_msg *pData);

void mmi_pwof_msg_parser(IBase* pRecipient, struct vm_msg *pData);
void mmi_pwof_rsp_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_pwon_rsp_if(IBase* pRecipient, struct vm_msg *pData);
void mmi_pwon_wsatp_rsp_if(IBase* pRecipient, struct vm_msg *pData);
#ifdef __SIM_NO_RSP_HANDLING__
void mmi_sim_no_rsp_ind_if(IBase* pRecipient, struct vm_msg *pData);
#endif //__SIM_NO_RSP_HANDLING__
static void request_not_supported(IBase* pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_SIM_H__ */
