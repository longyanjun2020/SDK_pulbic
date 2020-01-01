#ifndef __MMI_SOKOBANAPP_H__
#define __MMI_SOKOBANAPP_H__

#include "mmi_mae_common_def.h"
#include "mmi_sokobanapp_priv.h"

/*
 * When SokobanApp is built as a sldlm (static load, dynamic link module), 
 * some functions/variables should be set as exception so that
 * the sldlm module can be loaded successfully.
 * The functions/variables associated with loading/unloading the sldlm
 * cannot be put into the sldm.
 * They should be given the __DLM_SOKOBAN_FREE__ attribute so that
 * they are free from being compressed by the sldlm mechanism.
 *
 * To reduce the number of veneers, the attribute is set to be the same
 * with dpm.
 * */
#if defined(__DLM_SOKOBANAPP_MMI__) && defined(__arm) && defined(__TARGET__)
#define __DLM_SOKOBANAPP_FREE__ __attribute__((section(".sldpm_free")))
#else
#define __DLM_SOKOBANAPP_FREE__
#endif

__DLM_SOKOBANAPP_FREE__ MAE_Ret SokobanAppNew(MAE_ClsId id, void **ppObj);
#endif

