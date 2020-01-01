#ifndef __MMI_LICENSEMGRAPP_ID_H__
#define __MMI_LICENSEMGRAPP_ID_H__

typedef enum
{
    LICENSEMGR_WND_MAIN = WND_ID_APP_BASE,
    LICENSEMGR_WND_OPTION,
    LICENSEMGR_WND_DETAIL

}LicenseMgrId_e;

typedef enum
{
    MNU_DETAIL = 0,
    MNU_DELETE,
    MNU_DELETEALL,
    MNU_SWEEP,    
}LicenseMgrOptMenuId_e;

typedef enum
{
    WDG_SUMMARY = 0,
    WDG_DRMTYPE,
    WDG_USAGECOUNTLABEL,
    WDG_USAGECOUNT    
}LicenseMgrDetailWndWdgId_e;

#endif //__MMI_LICENSEMGRAPP_ID_H__

