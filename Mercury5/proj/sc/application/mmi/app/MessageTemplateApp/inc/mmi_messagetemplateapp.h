/**
* @file mmi_messagetemplateapp.h
*
* Class Id: CLSID_MTA
* 
*

*/
#ifndef __MMI_MESSAGETEMPLATEAPP_H__
#define __MMI_MESSAGETEMPLATEAPP_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"

typedef enum
{
	MTA_START_MODE_NORMAL,
	MTA_START_MODE_PICK,
}MtaStartMode_e;

typedef struct{
    
   MtaStartMode_e eLaunchMode;
   
}MtaLaunch_t;


/**
 * Functions
 */
MAE_Ret MTA_New(MAE_ClsId id, void **ppObj);
void MtaPreNew(void);


#endif /* __MMI_MESSAGETEMPLATEAPP_H__ */
