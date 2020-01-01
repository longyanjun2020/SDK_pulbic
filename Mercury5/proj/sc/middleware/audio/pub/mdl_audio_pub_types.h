#ifndef __MDL_AUDIO_PUB_TYPES_H__
#define __MDL_AUDIO_PUB_TYPES_H__

#include "mdl_aud_forward.h"

/**
 * \brief Middleware audio return type
 */
opaque_enum(MdlAudRet_e_)
{
    MDL_AUD_RET_OK = 0,
    MDL_AUD_RET_FAIL,
    MDL_AUD_RET_SKIP,
    MDL_AUD_RET_PARAM_ERROR,
    MDL_AUD_RET_MEM_ALLOC_ERROR,
    MDL_AUD_RET_REJECT,
    MDL_AUD_RET_ABORT,
    MDL_AUD_RET_PATH_ERROR,
    MDL_AUD_RET_TIMEOUT,
    MDL_AUD_RET_WRONG_STATE,
    MDL_AUD_RET_NO_SUPPORT,
};

#endif // __MDL_AUDIO_PUB_TYPES_H__

