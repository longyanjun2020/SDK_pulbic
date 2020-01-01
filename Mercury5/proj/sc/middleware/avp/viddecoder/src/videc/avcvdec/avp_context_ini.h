
/*!
 *************************************************************************************
 * \file context_ini.h
 *
 * \brief
 *    CABAC context initializations
 *
 * \author
 *    Main contributors (see contributors.h for copyright, address and affiliation details)
 *    - Detlev Marpe                    <marpe@hhi.de>
 *    - Heiko Schwarz                   <hschwarz@hhi.de>
 **************************************************************************************
 */


#ifndef AVC_CONTEXT_INI_H
#define AVC_CONTEXT_INI_H

#include "avp_ctx.h"
void init_contexts(MotionTextureInfoContexts *mt, uint1 high_profile, uint1 interlace, uint8 slice_type, uint8 model_number, int8 qp);

#endif
