#ifndef PARSET_H
#define PARSET_H

#include "avp_videc_s.h"
#include "avp_parsetcommon.h"
#include "avp_avcPrivate.h"

err_type get_SPS(AVC_HANDLE *hp);
err_type get_PPS(AVC_HANDLE *hp, pic_parameter_set_rbsp_t *pps);
#endif
