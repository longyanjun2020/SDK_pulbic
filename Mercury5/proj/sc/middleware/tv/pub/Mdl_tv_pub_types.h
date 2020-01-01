
/**
* @file    Mdl_tv_pub_types.h
* @version
* @brief   Public types of TV middleware
*/


#ifndef __MDL_TV_PUB_TYPES_H__
#define __MDL_TV_PUB_TYPES_H__

#include "Mdl_tv_pub_forward.h"
#include "vm_msgof.hc"


/**
 * @brief TV SLDLM status.
 */
opaque_enum(Mdl_Tv_Sldlm_Status_e_){
  MDL_TV_SLDLM_READY,            /** MDL_TV_SLDLM_READY         Request None SLDLM is ready to use */
  MDL_TV_SLDLM_NOT_READY,        /** MDL_TV_SLDLM_NOT_READY     SLDLM is not ready */
  MDL_TV_SLDLM_FAIL,             /** MDL_TV_SLDLM_FAIL          SLDLM load fail */
};


/**
 * @brief TV SLDLM type
 */
opaque_enum(Mdl_Tv_Sldlm_Module_e_){
  MDL_TV_SLDLM_ATV,              /** MDL_TV_SLDLM_ATV           ATV SLDLM */   
  MDL_TV_SLDLM_NONE,
};


#ifdef __DLM_ATV_DRV__
#include "sys_sys_dlm_mgr.h"
#define ATV_SLDLM_SOURCE DLM_FROM_CUS
#endif


#ifndef __ATV_AUD_LINEIN__
/**
 * @brief ATV audio channel is defined as Music Channel (I2S)
 */
#define ATV_AUD_CHANNEL MDL_AUD_MUSIC_CHANNEL
#else
/**
 * @brief ATV audio channel is defined as Line-in.
 */
#define ATV_AUD_CHANNEL MDL_AUD_LINEIN_CHANNEL
#endif

/**
 * @brief DTV audio channel is defined as Music Channel (I2S)
 */
#define DTV_AUD_CHANNEL MDL_AUD_MUSIC_CHANNEL

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "mdl_tv_message_define__.hi"
};

#endif //__MDL_TV_PUB_TYPES_H__



