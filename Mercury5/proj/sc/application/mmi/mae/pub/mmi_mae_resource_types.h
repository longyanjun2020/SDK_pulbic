#ifndef __MMI_MAE_RESOURCE_TYPES_H__
#define __MMI_MAE_RESOURCE_TYPES_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_customization_types.h"
#include "mmi_mae_langcode.h"

#define RESOURCEID_SIZE CUSID_SIZE // NIC address + timestamp+'\0' ( 6+4+1 )

struct MAE_MenuTable_t_
{
	u16 nTextId;
	u16 nNextSiblingIdx;
	u16 nNumOfChild;
	u16 nLeftSKId;
	u16 nMiddleSKId;
	u16 nRightSKId;

#ifdef EXCEL_GEN
	u16 nLevel;
	u8* pTextString;
	u8* pMenuItemString;
#endif

};

opaque_enum(MAE_MenuInfo_e_)
{
    MAE_MENUINFO_TEXTID,
    MAE_MENUINFO_NEXT_SIBLING_IDX,
    MAE_MENUINFO_NUM_OF_CHILD,
    MAE_MENUINFO_LEFT_SK_ID,
    MAE_MENUINFO_MIDDLE_SK_ID,
    MAE_MENUINFO_RIGHT_SK_ID
};

struct MAE_LangData_t_
{
	MAE_LANG_CODE_e eLangCode;
	u16 *pLangName;
};

opaque_enum(MAE_InputIME_e_)
{
    MAE_INPUT_IME_MY,
    MAE_INPUT_IME_ZI
};

struct MAE_InputLangData_t_
{
	MAE_LANG_CODE_e eLangCode;
	u16 *pLangName;
    u16 u16LangLen;
	u16 nNumArray;
};

struct MAE_InputData_t_
{
	u8* pArrayName;
	u8* pArrayData;
};

opaque_enum(MAE_Handwrite_e_)
{
    MAE_HANDWRITE_SINOVOICE
};


#endif // __MMI_MAE_RESOURCE_TYPES_H__
