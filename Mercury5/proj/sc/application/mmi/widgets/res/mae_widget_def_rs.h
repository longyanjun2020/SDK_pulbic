#ifndef __MAE_WIDGET_DEF_RS_H__
#define __MAE_WIDGET_DEF_RS_H__
#include "widgets_resource.h"
#include "widgetInternal_resource.h"
#include "mae_macro_struct.h"

#if defined(__PC_SIMULATOR__) && defined(__RS_USE_SCRIPT__)

#include "mae_widget_def.rs"
#include "mae_widget_internal_def.rs"
#include "mae_macro_wdg_undef_priv.h"
#include "mae_macro_wdg_prop_val_priv.h"
#include "mmi_rs_macro_val.h"
#include "mae_widget_def.rs"
#include "mae_widget_internal_def.rs"

#else

#include "mae_widget_def.rs"
#include "mae_widget_internal_def.rs"

#endif

#endif  /*__MAE_WIDGET_DEF_RS_H__*/
 