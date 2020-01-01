#ifdef __MAP_MMI_LBS__
#ifndef __MMI_LBS_MSGDEF_H__
#define __MMI_LBS_MSGDEF_H__

#include "mmi_mae_common_def.h"

typedef enum
{
	LBS_ACTION_RSP_HTTP_200 = 0, /* must same as HTTP_200_OK */
	LBS_ACTION_RSP_HTTP_301,
	LBS_ACTION_RSP_HTTP_302,
	LBS_ACTION_RSP_HTTP_303,
	LBS_ACTION_RSP_HTTP_403,
	LBS_ACTION_RSP_HTTP_404,
	LBS_ACTION_RSP_HTTP_ERROR,
	LBS_ACTION_RSP_TIMEOUT,	
	LBS_RSP_SUCCESS,
	LBS_RSP_FAILURE,	
}LbsRspCode_t;

typedef struct 
{
	u16    *userData;
	s32     userLength;		
}LbsRspAction_t;

typedef struct 
{
	LbsRspCode_t			rspCode;	
	LbsRspAction_t              *rspAction;
} mmi_LbsMsgBody_t;

#endif /* __MMI_LBS_MSGDEF_H__ */
#endif /* __MAP_MMI_LBS__ */

