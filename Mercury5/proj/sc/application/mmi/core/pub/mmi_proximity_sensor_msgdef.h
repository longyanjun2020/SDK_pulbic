/**
* @file mmi_paisensor_msgdef.h
*
*
* @version $Id: mmi_paisensorr_msgdef.h 15893 2008-11-04 14:51:24Z mark.yang $
*
*/

#ifndef __MMI_PAISENSOR_MSGDEF_H__
#define __MMI_PAISENSOR_MSGDEF_H__

#include "mmi_mae_common_def.h"

typedef struct
{
    u32 userValue;
    u16 senderID;
    u16 nIndicator;
    u16 dataL;                    /**< data--L thro */
    u16 dataH;                    /**< data--H thro */
    u16 op_flag;		/*1:intp on; 0:intp off*/
} mmi_GpdPaiSensorNotifyMsgBody_t;
#endif /* __MMI_PAISENSOR_MSGDEF_H__ */

