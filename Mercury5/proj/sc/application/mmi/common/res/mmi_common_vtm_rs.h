#ifndef __MMI_COMMON_VTM_RS_H__
#define __MMI_COMMON_VTM_RS_H__
#include "Common_resource.h"
#include "mmi_rs_macro_struct.h"

#if defined(__PC_SIMULATOR__) && defined(__RS_USE_SCRIPT__)

#include "mmi_common_vtm.rs"
#include "mmi_rs_macro_val.h"
#include "mmi_common_vtm.rs"

#else

#include "mmi_common_vtm.rs"

#endif

#endif  /*__MMI_COMMON_VTM_RS_H__*/
