/**
 * @file	mmi_mae_rai_id.h
 * @brief	This file defines the RAI definition in MMI.
 * @version	$Id: mmi_mae_rai_id.h 291 2009-02-27 13:08:01Z kenny.wu $
 */
#ifndef __MMI_MAE_RAI_ID_H__
#define __MMI_MAE_RAI_ID_H__
#include "mdl_vm_rai_id.h"

#define MMI_FS_RAI_ITEM_START_ID( raiId ) M_##raiId##_START = ( MMI_FS_RAI_START_ID + ((raiId & 0x000000FF) << 16) )
#define MMI_FS_RAI_ITEM_END_ID( raiId )   raiId##_END
#define MMI_FS_RAI_ITEM_NUM( raiId )      ( raiId##_END - ( MMI_FS_RAI_START_ID + ((raiId & 0x000000FF) << 16) ) )
#define MMI_DRM_RO_RAI_SIZE                   (DRM_KEY_RAI_SIZE)


#endif /*__MAE_RAI_ID_H__ */
