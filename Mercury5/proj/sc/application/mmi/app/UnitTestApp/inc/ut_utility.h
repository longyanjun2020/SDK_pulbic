/*
*
* @file ut_utility.h
*
* Class Id:
*
* @version $Id$*/
#ifndef __UT_UTILITY_H__
#define __UT_UTILITY_H__

#include "stdio.h"
#include "ut_def.h"
#include "TaskStgr_CmdHandlerItf.h"
#include "ResMgr_EvtFacItf.h"
#include "MediaCmd.h"
#include "ResMgr_MsgDefItf.h"
#include "MediaRspItf.h"

bool UtUtilityGenerateProRsp(ResMgr_AppId_e eAppId, MediaRspId_e eRspId, void *pInfo);
bool UtUtilityCameraRspTest(FILE *pFile, int nIdx);
void UtUtilityDummy(void);

#endif    /* __UT_UTILITY_H__ */
