#ifndef __MMI_IDLEAPP_RS_H__
#define __MMI_IDLEAPP_RS_H__
#include "mmi_rs_macro_struct.h"

#if defined(__PC_SIMULATOR__) && defined(__RS_USE_SCRIPT__)

#include "mmi_idleapp.rs"
#include "mmi_rs_macro_val.h"
#include "mmi_idleapp.rs"

#else

#include "mmi_idleapp.rs"

#endif

/*
#ifndef __TOUCH_SCREEN_MMI__ //Workaround solution for enable IdleApp to load RC definition from "mmi_idleapp_win.rs"
#define __RS_USE_SCRIPT__ 1
#endif

#ifdef __RS_USE_SCRIPT__
#include "mmi_rs_macro_val.h"
#ifdef __GADGETS_MMI__
#include "mmi_idleapp_qvgap_thm.rs"
#else
#include "mmi_idleapp_win.rs"
#endif
#endif
*/

#endif  /*__MMI_IDLEAPP_RS_H__*/
