/**
 * @file    mmi_common_lang.h
 * @brief   
 *          
 *
 * @author  
 * @version $Id: mmi_common_lang.h 31865 2009-05-25 17:04:57Z sho.ding $
 */
 
#ifndef __MMI_COMMON_LANG_H__
#define __MMI_COMMON_LANG_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_langcode.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_resource.h"

#define MAX_LANG_PACKED_NUM		MAX_LANG_PACKED



MAE_Ret MMI_Common_LANGSRV_GetAutomaticLanguageCode(MAE_LANG_CODE_e *pnMAELANGCode, IBase *pOwner);

MAE_Ret MMI_Common_VerifyLanguageCode(MAE_LANG_CODE_e nMAELANGCode, boolean *pbResult ,IBase *pOwner);

//MAE_Ret MMI_Common_GetLanguagePacked(SettingLangPacked_t *pstLangPackedBuffer, u8 u8Size ,IBase *pOwner);
__SLDPM_FREE__ MAE_Ret MMI_Common_GetLanguagePacked(MAE_LangData_t *pstLangPackedBuffer, u8 u8Size ,IBase *pOwner);

MAE_Ret MMI_Common_LanguageCodeToStr(MAE_LANG_CODE_e nMAELANGCode, MAE_WChar **ppWLangStr, IBase *pOwner);

MAE_Ret MMI_Common_SetLangcodeToMAE(IBase *pOwner,MAE_LANG_CODE_e eSelectedLangCode);

void MMI_Common_UpdateDefaultChineseInputMethodByInputLanguage(MAE_LANG_CODE_e eInputLang, IBase *pOwner);

#endif /* __MMI_COMMON_LANG_H__ */
