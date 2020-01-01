

#ifndef __MAE_COMMON_WINDOW_H__
#define __MAE_COMMON_WINDOW_H__

#include "mmi_common_storage_mgr.h"
#include "mmi_srv_accessory.h"
#include "mmi_common_vtm.h"


#define COMMON_SELECT_WND_CFG_NO_USE    0

typedef enum
{
    COMMON_SELECT_STORAGE_POPUP,
    COMMON_SELECT_STORAGE_FULL_SCREEN,
    COMMON_SELECT_STORAGE_POPUP_FOR_JAVA_AMS,//Java could only install in card one. this window jsut show storage 1 and phone items.
    COMMON_SELECT_STORAGE_POPUP_EXCECT_NOR,
    MAX_COMMON_WINDOW_TYPE
}CommonWindowType;
typedef u8 CommonWindowType_e;

typedef enum
{
    COMM_SELECT_WND_ACTION,

    COMM_WND_ACTION_FAIL
}CommWndAction_e;

typedef enum
{
    COMM_WND_UNKNOW_ERROR,
    COMM_WND_SD_STATUS_CHANGE,
}CommWndActionFailCode;
typedef u32 CommWndActionFailCode_e;

typedef struct CommWindowMsg_t_
{
    CommWndAction_e eCommWndAction;
}CommWindowMsg_t;

typedef struct {
	SoftkeyID_e nLSK;
	SoftkeyID_e nCSK;
	SoftkeyID_e nRSK;
	boolean bUserDefineSK;
	void *pUserData;
} CommWindowInfo_t;

typedef MAE_Ret (*PFN_CommWndFunc)(void* pCusHandle, const CommWindowMsg_t *pWndMsg, void* pParam1, void* pParam2 );

typedef struct CommStorageSelectWndData_t_
{
    IApplet *pApplet;
    PopUpSelectWdgList_t tPopWdgList;
    MenuWdgList_t tMenuWdgList;
    PFN_CommWndFunc pfnCommWndHdl;
    SrvAccessoryPlugStatusCB pfnPlugStatusCB;
    u32 nSelectedID;
}CommStorageSelectWndData_t;

typedef struct CommFullScnOptMenuWndData_t_
{
    IApplet *pApplet;
    OptionMenuWdgList_t tWdgList;
}CommFullScnOptMenuWndData_t;


MAE_Ret MMI_CreateCommonSelectWindow
(
    IApplet *pOwner,
    CommonWindowType_e eWndType,
    MAE_WChar *pTitleText,
    CommWindowInfo_t *pWndInfo,
    PFN_CommWndFunc pfnCommWndHdl
);

MAE_Ret MMI_CreateCommonSelectWindowWithMediaType(
 IApplet *pOwner,
 CommonWindowType_e eWndType,
 MAE_WChar *pTitleText,
 CommWindowInfo_t *pWndInfo,
 PFN_CommWndFunc pfnCommWndHdl,
 CommonMediaType_e eCommonMediaType
 );

void MMI_CreateCommonGetStorageMenuItemData(WdgStaticMenuItem_t *pMenuItem, u8 size, CommWindowInfo_t *pWndInfo, WdgMenuItemType_e eItemType);
void MMI_CreateCommonGetStorageMenuItemDataWithMediaType(WdgStaticMenuItem_t *pMenuItem, u8 size, CommWindowInfo_t *pWndInfo, WdgMenuItemType_e eItemType, CommonMediaType_e eCommonMediaType);

#endif //__MAE_COMMON_WINDOW_H__

