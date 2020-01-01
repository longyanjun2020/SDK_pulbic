/*****************************************************************************************
* @btapp_view.h
*
* Comment:
*
* @version:0.0.2  @ 2009.12.01
*****************************************************************************************/
#ifndef __btapp_view__H
#define __btapp_view__H

#include "mmi_common_vtm.h"

#include "mmi_common_wdgvar.h"
#include "mmi_btapp_priv.h"

#ifdef __BLUETOOTH_MMI__

MAE_Ret BtAppCreateMainView(HWIN hWin, BtAppMain_t *pWdgList);

//*******************************************************************//

MAE_Ret BtAppCreateSearchingView(HWIN hWin, BtAppSearching_t *pWdgList);

//*******************************************************************//

MAE_Ret BtAppCreateEnterPinCodeView(HWIN hWin, BtAppAddDeviceEnterPinCode_t *pWdgList);

//*******************************************************************//

MAE_Ret BtAppCreateDeviceListOptionMenuView(HWIN hWin, BtAppDeviceListOptionMenu_t *pWdgList, bool bMenuSelect);

//*******************************************************************//

MAE_Ret BtAppCreateInputShortNameView(HWIN hWin, BtAppInputShortName_t *pWdgList);

//*******************************************************************//

MAE_Ret BtAppCreateInputShortNameOptionMenuView(HWIN hWin, BtAppInputShortNameOptionMenu_t *pWdgList);

//*******************************************************************//

MAE_Ret BtAppCreateSettingView(HWIN hWin, BtAppSetting_t *pWdgList);

//*******************************************************************//

MAE_Ret BtAppCreateInputLocalNameView(HWIN hWin, BtAppInputLocalName_t *pWdgList);

//*******************************************************************//

MAE_Ret BtAppCreateInputLocalNameOptionMenuView(HWIN hWin, BtAppInputLocalNameOptionMenu_t *pWdgList);

//*******************************************************************//

MAE_Ret BtAppCreateAddDeviceToMenuView(HWIN hWin, BtAppAddDevicetoMenu_t *pWdgList, bool bFound);

//*******************************************************************//

__SLDPM_FREE__ MAE_Ret BtAppCreateDeviceInformationView(HWIN hWin, BtAppDeviceInfo_t *pWdgList);

//*******************************************************************//

#endif // __BLUETOOTH_MMI__
#endif //__btapp_view__H
