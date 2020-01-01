/**
* @file MediaRspFacItf.h
*
* This header file defines the interfaces of media response factory
*
*/

#ifndef __MEDIARSPFACITF_H__
#define __MEDIARSPFACITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_RspItf.h"
/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_RspHdl_t Media_CreateGenRsp(u32 uRspId, u16 uExecRes, u32 uCusData, void *pRspData, u16 uArrtibute);
ResMgr_RspHdl_t Media_CreateProRsp(u32 uRspId, u32 uCusData, void *pRspData);
/*Create proactive rsp with free data function, only pcm data notify use it for now*/
ResMgr_RspHdl_t Media_CreateProRspExt(u32 uRspId, u32 uCusData, void *pRspData, ResMgr_FreeCusRspData FreeData);
void MediaCmd_DestroyRsp(ResMgr_RspHdl_t pRspHdl);
#endif //__MEDIARSPFACITF_H__

