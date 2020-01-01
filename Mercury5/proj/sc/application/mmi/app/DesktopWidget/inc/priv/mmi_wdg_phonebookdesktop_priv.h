/**
 * @file    mmi_wdg_phonebookdesktop_priv.h
 * @brief   The internal structure of the phonebook desktopwidget

 */

#ifndef __MMI_WDG_PHONEBOOKDESKTOP_PRIV_H__
#define __MMI_WDG_PHONEBOOKDESKTOP_PRIV_H__

#if defined (__GADGETS_MMI__) || defined(__3D_UI_IDLE_MULTIPAGE__)

#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_settingapp.h"
#include "mmi_common_util.h"
#include "mmi_common_cfg.h"
#include "rs_layout_id.h"
#include "mmi_coresrv.h"
#include "mmi_common_rai_id.h"
#include "mmi_phbsrv.h"
#include "mmi_phbapp.h"
#include "mmi_launcher_cc.h"
#include "mmi_launcher_em.h"
#include "mmi_launcher_mca.h"
#include "mmi_launcher_phb.h"
#include "mmi_launcher_security.h"
#include "mmi_launcher_ussd.h"
#include "mmi_srv_phb.h"
#include "mmi_sssrv.h"
#include "mmi_srv_sim.h"
#include "mmi_srv_cc.h"
#include "mmi_srv_cfg.h"
#include "mmi_ccsrv_def.h"

/*************************************************************************/
/*   For Definition                                                      */
/*************************************************************************/
#define    DESKTOP_TITLE_COLOR                          (0xFFA0A0A0)   
#define    DESKTOP_ITEM_TEXT_UNFOCUS_COLOR              (0xFF6C6E70)   
#define    DESKTOP_PHB_MAX_NUM                          (12)
#define    DESKTOP_PHB_EMPTY_DEFAULT_NUM                (4)
/*************************************************************************/
/*   For Enumeration                                                     */
/*************************************************************************/
enum
{
    DESKTOPPHB_CALL_BTN = 0,
    DESKTOPPHB_SEND_BTN,
    DESKTOPPHB_MENU,
    DESKTOPPHB_NO_TARGET,
    DESKTOPPHB_BTN_MAX_NUM = DESKTOPPHB_NO_TARGET      
};
typedef u8 DesktopTargetId_e;

enum
{
    DESKTOPPHB_CALL_TYPE_EMERGENCYCALL = 0,
    DESKTOPPHB_CALL_TYPE_NORMALCALL,
#ifdef __IP_CALL_MMI__
    DESKTOPPHB_CALL_TYPE_IPCALL,
#endif
    DESKTOPPHB_CALL_TYPE_MAX_NUM
};
typedef u8 DesktopCallType_e;

enum
{
    DESKTOPPHB_MSG_TYPE_SMS = 0,
    DESKTOPPHB_MSG_TYPE_MMS,
    DESKTOPPHB_MSG_TYPE_MAX_NUM
};
typedef u8 DesktopMsgType_e;

enum
{
    DESKTOPPHB_STATUS_LOADING = 0,
    DESKTOPPHB_STATUS_READY,
    DESKTOPPHB_STATUS_MAX_NUM
};
typedef u8 DesktopStatus_e;

/*************************************************************************/
/*   For Structure                                                       */
/*************************************************************************/
typedef struct{    
    MmiPhbNumber_t    atNumber[DESKTOP_PHB_MAX_NUM];
} MmiShortcutPhbData_t;

// For storing subwidget position and dimension
typedef struct{
    Rect_t rcWidget;
    boolean bIsEnable;        // If this subwidget handles event
}BtnGeometryInfo_t;

typedef struct
{
    DECLARE_BASECLASS_DESKTOPWIDGET
    IWidget                                 *pTitleTxtWdg;        
    IWidget                                 *pCallBtnWdg;
    IWidget                                 *pSendBtnWdg;    
    IWidget                                 *pLoadingWdg;        
    IWidget                                 *pMenuWdg;
    IPHBSRV                                 *pPhbSrv;  
    IImage                                  *pContactImg[DESKTOP_PHB_MAX_NUM];
    BtnGeometryInfo_t                       tBtnGeoInfo[DESKTOPPHB_BTN_MAX_NUM];
    u8                                      nSelectedIdx;
    DesktopTargetId_e                       ePressTarget;
    MmiShortcutPhbData_t                    *tPhbData;
    MmiPhbContactContent_t                  *tPhbContact;  
    DesktopStatus_e                         eDskPhbStatus;
} PhonebookDesktopWdg_t;

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_WDG_PHONEBOOKDESKTOP_PRIV_H__
/*=============================================================*/
// end of file
