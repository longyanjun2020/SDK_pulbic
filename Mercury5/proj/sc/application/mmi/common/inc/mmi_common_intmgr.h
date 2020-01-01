/**
 * @file    mmi_common_intmgr.h
 * @brief   This file should only be included in mmi_common_inttab.h and mmi_common_intmgr.c
 *          Here defines the general type and macro used for interrupt manager.
 *
 * @author  mark.yang@mstarsemi.com
 * @version $Id: mmi_common_intmgr.h 1989 2007-09-11 05:26:12Z mark.yang $
 */
 
#ifndef __MMI_COMMON_INTMGR_H__
#define __MMI_COMMON_INTMGR_H__

#include "mmi_mae_common_def.h"

enum
{
	LEVEL_DENY = FALSE,
	LEVEL_ALLOW = TRUE
};
typedef u8 IntApp_Level_e;

typedef struct AppIntTableItem_Tag
{
	const IntApp_Level_e type;
	const u32 intApps;
}AppIntTableItem_t;

#ifdef __MMI_COMMON_INTTBL_H__
#ifdef __MMI_COMMON_INTMGR_C__
error Wrong include header file or sequence for mmi_common_intmgr.h
#endif
#define INTAPP_IS_INTERRUPTIBLE(app, level, clsId) ((u32)IntMgr_CheckIntTable(&(app##_IntTable[(level)]), (MAE_ClsId)(clsId)))
#define MAKE_INTAPP_TABLE(name) extern const AppIntTableItem_t name##_IntTable[]; enum
#define INTAPP_LEVEL(level, type, intapps)	level
#endif

#ifdef __MMI_COMMON_INTMGR_C__
#ifdef __MMI_COMMON_INTTBL_H__
error Wrong include header file or sequence for mmi_common_intmgr.h
#endif
#define MAKE_INTAPP_TABLE(name) const AppIntTableItem_t name##_IntTable[] =
#define INTAPP_LEVEL(level, type, intapps)	{type, intapps}
#endif 



/**
 * Utility function for applet to check interrupt table 
 * Applet needs to define the interrupt level in this file, and add the foolowing code in GetProperty 
 * when AP manager ask AP if it allows such interruption.
 * 
 * <pre>
 * case APM_PROP_INTERRUPT_TABLE:
 *        *((u32*)outVal) = (u32)IntMgr_CheckIntTable(&(DEMO_CAL_IntTable[pThis->level]), (MAE_ClsId)outVal);
 *       return TRUE;
 * </pre>
 *
 * Note: Applet do not need to use this if the applet allow or deny interrupt always. 
 * Instead, applet just set the resutl to TRUE or FALSE for GetProperty
 */
boolean IntMgr_CheckIntTable(const AppIntTableItem_t *item, MAE_ClsId intAppClsId);

boolean IntMgr_CheckInterruptLevel(u32 nAppInterruptAllow, MAE_ClsId intAppClsId);

void IntMgr_SetInterruptLevel(const AppIntTableItem_t *item);

#define MMI_SetInterruptLevel(app, level) (IntMgr_SetInterruptLevel(&(app##_IntTable[(level)])))

#endif /* __MMI_COMMON_INTMGR_H__ */
