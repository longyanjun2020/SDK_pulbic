/**
 * @file mmi_profilesrv_util_priv.h
 *
 *
 * @version $Id: mmi_profilesrv_util_priv.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */
#ifndef __MMI_PROFILESRV_UTIL_PRIV_H__
#define __MMI_PROFILESRV_UTIL_PRIV_H__

#include "mmi_profilesrv_priv.h"

#define FieldSize( type, field ) sizeof( ((type *) 0)->field )



#if defined(__arm__) && defined(__ARMCC_VERSION)
//#undef offsetof
//#include <stddef.h>
//#define ItemPOS(type, field) __INTADDR__(offsetof(type, field))
//#define offsetof(t, memb) ((__CLIBNS size_t)__INTADDR__(&(((t *)0)->memb)))
#define FieldPOS(type, field) ((u32)__INTADDR__ (&(((type*)0)->field)))
#else
#define FieldPOS(type, field) ((u32)&((type*)0)->field)
#endif

#define ARRAY_SIZE(a) (sizeof((a))/sizeof((a)[0]))



typedef struct ProfileSettingsInfo_TAG
{
    CFGItemID_e eCFGItemID;
    u16 u16POS;
    u16 u16CGFItemSize;
}ProfileSettingsInfo_t;

extern const  CFGItemID_e CFGITEM_ID[];
extern const u32 NumofProfileSettingItems;



MAE_Ret _PROFILESRV_Util_SyncSettingAPtoCurrentProfileSettings(MMI_PROFILESRV *pThis, ProfileSettings_t *pstProfileSettings);

MAE_Ret _PROFILESRV_Util_GetProfileSettings(MMI_PROFILESRV *pThis, ProfileID_e eProfileID, ProfileSettings_t *pstProfileSettings, boolean bGetDeafultSettings); 
MAE_Ret _PROFILESRV_Util_SetProfileSettings(MMI_PROFILESRV *pThis, ProfileID_e eProfileID, ProfileSettings_t *pstProfileSettings);

MAE_Ret _PROFILESRV_Util_ApplyProfileSettingstoSettingAP(MMI_PROFILESRV *pThis, ProfileSettings_t *pstProfileSettings, CFGSetItemInfo *pCFGSetItemInfo, boolean bSetToCFG);

MAE_Ret _PROFILESRV_Util_ProfileSettingsBoundaryCheck(MMI_PROFILESRV *pThis, ProfileSettings_t *pstProfileSettings);
#endif //__MMI_PROFILESRV_UTIL_PRIV_H__

