/**
* @file GenEvtHdlr.h
*
* This header file defines the data structure of generic event handler.
*
*/

#ifndef __GENEVTHDLR_H__
#define __GENEVTHDLR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "GenEvtHdlrItf.h"
/*=============================================================*/
// Macro Declarations
/*=============================================================*/
#define __GEH_STGR_DEBUG__ 
#define __GEH_UTIL_DEBUG__ 

#define GEH_LEVEL   (_SYS | LEVEL_17)
#define GEH_MALLOC  GRM_MALLOC
#define GEH_MFREE   GRM_MFREE
#define GEH_MEMSET  GRM_MEMSET
#define GEH_MEMCPY  GRM_MEMCPY
#define GEH_TRACE   GRM_TRACE
#define GEH_ERROR   vm_dbgError

#define GEH_RET_IF_NULL(p, str) \
    {\
        if(NULL == (p))\
        {\
            GEH_ERROR(GEH_LEVEL, str);\
            return;                        \
        }                                  \
    }

#define GEH_RET_VAL_IF_NULL(p, v, str) \
            {                              \
        if(NULL == (p))\
        {\
            GEH_ERROR(GEH_LEVEL, str);\
            return (v);                    \
        }                                  \
    }

#define GEH_HISTORY_NUM 60
#define GEH_UTIL_HISTORY_NUM 20
#define NUM_OF_ARRAY(_ARRAY_) (sizeof(_ARRAY_)/sizeof(_ARRAY_[0]))
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef GenEvtHdlrRet_e (*GenSMPreHandler)(GenSMHdl_t pSMHdl, GenSMHandle_e eSMHandleType, GenEvtHdl_t pEvtHdl, u32 nCusData, GenSMHandler pfnSMHandler);

#if defined (__GEH_STGR_DEBUG__) || defined (__GEH_UTIL_DEBUG__)
typedef enum GenEvtHdlrHistoryOp_e_
{
    GENEVTHDLR_HISTORY_OP__SM_HANDLE_EVT,
    GENEVTHDLR_HISTORY_OP__SM_HANDLE_RESULT,
    GENEVTHDLR_HISTORY_OP__SM_TRANS_STATE,
    GENEVTHDLR_HISTORY_OP__QUEUE_EVT_IN,
    GENEVTHDLR_HISTORY_OP__QUEUE_EVT_OUT,
} GenEvtHdlrHistoryOp_e;

typedef struct GenEvtHdlrHistoryItem_t_
{
    u8 nOpType;
    u32 nId;
    u32 nData;
} GenEvtHdlrHistoryItem_t;
#endif

/*=============================================================*/
// Private Function Declaration
/*=============================================================*/
void GenSM_SetPreHandler(GenSMHdl_t pSMHdl, GenSMPreHandler pfnPreHandler);
#if defined (__GEH_STGR_DEBUG__) || defined (__GEH_UTIL_DEBUG__)
void GenEvtHdlr_WriteHistory(GenEvtHdlrHistoryOp_e eOpType, u32 nId, u32 nData, GenEvtHdlrHistoryItem_t *pHistoryTable, u8 *pLastRecIdx, u8 nHistoryNum);
#endif

#endif //__GENEVTHDLR_H__

