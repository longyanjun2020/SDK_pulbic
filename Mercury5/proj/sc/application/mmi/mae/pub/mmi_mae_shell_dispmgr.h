/**
 * @file    mmi_mae_shell_dispmgr.h
 * @brief   The document describes the interface of display Manager
 * @author  steve.lee@mstarsemi.com
 * @version $Id: mmi_mae_shell_dispmgr.h 291 2009-02-27 13:08:01Z kenny.wu $
 */
 
#ifndef __MMI_MAE_SHELL_DISPMGR_H__
#define __MMI_MAE_SHELL_DISPMGR_H__
#include "mmi_mae_shell.h"

MAE_Ret MAE_Display_Init(IShell*);
MAE_Ret MAE_Display_Delete(IShell*);
void MAE_Display_UpdateScreen(IShell*);

#endif /* __MAE_SHELL_DISPMGR_H__ */
