/**
* @file    mmi_req_sim.h
* @brief   The file handles all the SIM/SEC request function to RIL
* @author  christine.tai@mstarsemi.com
* 
*/
#ifndef __MMI_REQ_SIM_H__
#define __MMI_REQ_SIM_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_simsrv_def.h"
#include "mmi_stksrv_def.h"

#include "mmi_if_sim.h"

enum
{
	PWON_WSATP_0,         //USB Modem Active path 0 (SIM1)
	PWON_WSATP_1          //USB Modem Active path 1 (SIM2)
};
typedef u16 PWON_WSATP_e;

#ifdef _MSIM_
#include "mmi_simsrv.h"
void mmi_sim_set_SIMSRVPTR(void * ptr);
void mmi_sim_set_STKSRVPTR(void * ptr);
void mmi_sim_ready_req();
#endif
void mmi_sim_prtStr(u32 level, u8 *pStr);


#ifdef __3G_RIL_MMI__
void mmi_sim_file_status_req(u8 u8ModuleID, u16 FileID, SIMSRV_SIM_PHASE_e eSIMPhase);
void mmi_sim_file_read_req(u8 u8ModuleID, u16 FileID, u16 Length, SIMSRV_SIM_PHASE_e eSIMPhase);
#else //#ifdef __3G_RIL_MMI__
void mmi_sim_file_status_req(u8 u8ModuleID, u16 FileID);
void mmi_sim_file_read_req(u8 u8ModuleID, u16 FileID, u16 Length);
#endif //#ifdef __3G_RIL_MMI__ 
void mmi_sim_lp_read_req(u8 u8ModuleID, u16 Index);
void mmi_sim_lp_query_req(u8 u8ModuleID);
void mmi_sim_lp_write_req(u8 u8ModuleID, u16 Index, u32 Value);

#ifdef __3G_RIL_MMI__
void mmi_sim_sst_req(u8 DualID);
#endif // __3G_RIL_MMI__

void mmi_sec_pin_enable_req(u8 u8ModuleID, u8 *pPinValue);
void mmi_sec_pin_disable_req(u8 u8ModuleID, u8 *pPinValue);
void mmi_sec_pin_verify_req(u8 u8ModuleID, SIMSRV_PIN_TYPE_e type, u8 *pPinValue);
void mmi_sec_pin_change_req(u8 u8ModuleID, SIMSRV_PIN_TYPE_e type, u8 *pOld, u8 *pNew);
void mmi_sec_pin_unblock_req(u8 u8ModuleID, SIMSRV_PIN_TYPE_e type, u8 *pPUK, u8 *pPIN);
void mmi_sec_pin_status_req(u8 u8ModuleID);
void mmi_sec_fac_lock_status_req(u8 u8ModuleID, SIM_FAC_TYPE_e FacType);
#ifdef __3G_RIL_MMI__
void mmi_sec_gid_req(u8 u8ModuleID);
#endif // __3G_RIL_MMI__

void mmi_stk_user_action_req(u8 u8ModuleID, STKSRV_CommandType_e CmdType, STKSRV_ACTION_TYPE_e ActionType, u8 u8MenuID);
void mmi_stk_respond_req(u8 u8ModuleID, STKSRV_CommandType_e CmdType,STKSRV_RSP_RSLT_e RespondType, u8* pData, u16 u16DataLen);
void mmi_stk_reset_timer_req(u8 u8ModuleID, u8 u8Timeout);
void mmi_stk_setlanguage_req(u8 u8ModuleID, u16 iso639Code);

#ifdef __3G_RIL_MMI__
void mmi_stk_download_profile_req(u8 u8ModuleID);
#endif // __3G_RIL_MMI__


void mmi_pwof_req(u8 u8ModuleID, PWOF_Type_e CmdType);
void mmi_pwon_req(u8 u8ModuleID, PWON_Type_e CmdType);
void mmi_pwon_wsatp_req(u8 u8ModuleID, PWON_WSATP_e CmdWsatpe);

#ifdef __3G_RIL_MMI__
void mmi_pwon_fake_req(u8 u8ModuleID, PWON_Type_e CmdType);
#endif // __3G_RIL_MMI__

#ifndef SIMDBG_GETCHAR
#define SIMDBG_GETCHAR(idx,len,str) (((idx)<(len))?(str[idx]):('0'))
#endif
#endif /* __MMI_REQ_SIM_H__ */
