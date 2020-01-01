/**
* @file mmi_emu_msgdef.h
*
*
* @version $Id: mmi_emu_msgdef.h 15190 2008-10-16 03:22:39Z christine.tai $
*
*/

#ifndef __MMI_EMU_MSGDEF_H__
#define __MMI_EMU_MSGDEF_H__

#include "ABL_gss.h"

typedef struct
{
	u32                 userValue;
	ABL_GssErrCode_e    nRetCode;
	ABL_GssInfo_t       *pGssInfo;
} mmi_EmuMsgBody_t;

typedef struct
{
	MediaRspId_e	eTransRspId;
} mmi_EmuResMgrMsgBody_t;

#endif /* __MMI_EMU_MSGDEF_H__ */

