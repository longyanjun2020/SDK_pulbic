/*****************************************************************************************
* @callerlocationapp_view.h
*
* Comment:
*
* @author @mstarsemi.com
* @       @mstarsemi.com
*****************************************************************************************/
#ifndef __callerlocationapp_view__H
#define __callerlocationapp_view__H

MAE_Ret CallerLocationAppCreateMainView(HWIN hWin, MenuWdgList_t *pWdgList);
//*******************************************************************//

MAE_Ret CallerLocationAppCreateQueryView(HWIN hWin, CallerLocationQueryWdgList_t *pWdgList);
MAE_Ret CallerLocationAppSetQueryView(HWIN hWin, CallerLocationQueryWdgList_t *pWdgList);
//*******************************************************************//

MAE_Ret CallerLocationAppCreateHelpView(HWIN hWin, PopUpInfoWdgList_t *pWdgList);
//*******************************************************************//


#endif //__callerlocationapp_view__H
