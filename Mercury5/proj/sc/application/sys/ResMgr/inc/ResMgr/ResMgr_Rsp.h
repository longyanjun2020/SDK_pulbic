/**
* @file ResMgr_Rsp.h
*
* This header file defines the data structure of command response
*
*/

#ifndef __RESMGR_RSP_H__
#define __RESMGR_RSP_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_RspItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
//#define RES_MGR_ACT_CMD_ACT_MASK                        0x000FFF00
//#define RES_MGR_ACT_GET_DEL_CMD_ACT(_RET_)              (((_RET_) & RES_MGR_ACT_CMD_ACT_MASK) >> 8)

#define RES_MGR_ACT__IS_FLAG_SET(_RET_, _FLAG_)          (_FLAG_ == (_FLAG_ & _RET_))
#define RES_MGR_ACT__IS_FLAG_NOT_SET(_RET_, _FLAG_)      (_FLAG_ != (_FLAG_ & _RET_))

#define RES_MGR_ACT__DEL_NONE                           0x00000000
#define RES_MGR_ACT__DEL_CUR_CMD                        0x00000001
#define RES_MGR_ACT__DEL_PLAY_CMD                       0x00000002

#define RES_MGR_ACT__NOT_INFORM_APP                 	0x00000004
#define RES_MGR_ACT__PLAY_AGAIN                         0x00000008
#define RES_MGR_ACT__DEL_ACT_CMD                    	0x00000010
#define RES_MGR_ACT__SKIP_ACT_CMD                    	0x00000020
#define RES_MGR_ACT__SKIP_RESTART_CMD                   0x00000040
#define RES_MGR_ACT__INFORM_STOP_SUCCESS                0x00000080
/*
    Inform applications of commands were rejected by Resource Manager due to
    invalid command request in current state.
*/
#define RES_MGR_ACT__INFORM_DENY                    	0x00000100
/*
    Inform applications of commands were rejected by Resource Manager due to
    command was merged by Resource Manager.
*/
#define RES_MGR_ACT__INFORM_MERGE                    	0x00000200
/*
    Inform applications of commands were rejected by driver due to invalid parameters
*/
#define RES_MGR_ACT__INFORM_FAILED                    	0x00000400
#define RES_MGR_ACT__CLEAR_ATTR                    	    0x00000800
#define RES_MGR_ACT__NEW_ACT_CMD                  	    0x00001000
#define RES_MGR_ACT__TERM_PLAY_CMD                      0x00002000
#define RES_MGR_ACT__REPLAY_CMD                         0x00004000
#define RES_MGR_ACT__CHECK_ACT_CMD_ATTR                 0x00008000
#define RES_MGR_ACT__HDL_RSP_EVT                        0x00010000
#define RES_MGR_ACT__SESSION_STARTED                   	0x00020000
#define RES_MGR_ACT__EXEC_RESTART                       0x00040000
#define RES_MGR_ACT__INFORM_WAIT_APPSTOP_DROP           0x00080000

/*=============================================================*/
// Structure Declarations
/*=============================================================*/
typedef struct ResMgr_Rsp_t_
{
    ResMgr_ResCategory_e eResCategory;
    ResMgrRspType_e eRspType;
    u32 uRspId;
    u32 uCusData;
    void *pRspData;
    u16 uExecRes;
    u16 uAttribute;
    u16 uCusAttribute;
	ResMgr_FreeCusRspData FreeCusRspData;
} ResMgr_Rsp_t;
/*=============================================================*/
// Function Declaration
/*=============================================================*/

#endif //__RESMGR_RSP_H__

