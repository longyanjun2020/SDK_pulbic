#ifndef __MMI_CALLERLOCATIONAPP_RS_H__
#define __MMI_CALLERLOCATIONAPP_RS_H__
#include "mmi_rs_macro_struct.h"

#if defined(__PC_SIMULATOR__) && defined(__RS_USE_SCRIPT__)

#include "mmi_callerlocationapp.rs"
#include "mmi_rs_macro_val.h"
#include "mmi_callerlocationapp.rs"

#else

#include "mmi_callerlocationapp.rs"

#endif

/*
#ifdef __RS_USE_SCRIPT__
#include "mmi_rs_macro_val.h"
#ifdef __LCM_LANDSCAPE_QVGA_MMI__
#include "mmi_callerlocationapp_thm_land_qvga.rs"
#else
#include "mmi_callerlocationapp_qvgap_thm.rs"
#endif
#endif
*/

#endif  /*__MMI_CALLERLOCATIONAPP_RS_H__*/
