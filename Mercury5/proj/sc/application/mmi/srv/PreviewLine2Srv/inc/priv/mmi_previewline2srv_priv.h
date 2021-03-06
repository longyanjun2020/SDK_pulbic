/**
* @file mmi_previewline2srv_priv.h
*
* Service without using State Machine - PREVIEWLINE2SRV
* Generated by XFSM v1.0, CodeVer=v0.24  2008-21-11, 22:15:52
*
* Class Id: CLSID_PREVIEWLINE2SRV
* Interface Id: IID_PREVIEWLINE2SRV
*
* @version $Id: mmi_previewline2srv_priv.h 16984 2008-11-22 07:31:07Z mark.yang $
*/
#ifndef __MMI_PREVIEWLINE2SRV_PRIV_H__
#define __MMI_PREVIEWLINE2SRV_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_previewline2srv.h"

#define ARRAY_SIZE(a) (sizeof((a))/sizeof((a)[0]))
#define BREAKIF_DISPERROR(s,n)                                  \
                                       {                        \
                                       if(MAE_RET_SUCCESS != n) \
                                        {                       \
                                        LOG_ERROR(MMI_LEVEL_GENERAL, s);            \
                                        break;                  \
                                        }                       \
                                      }




#define DATE_STRING_LEN 10  //YYYY/MM/DD



typedef struct MMI_PREVIEWLINE2SRV_GENERICCFG_PREVIEW_TAG
{
    CFGInfo_t *pstCFGInfo;
    IMenuModel *pIMenuModel;
    boolean bUseUserValue;
    u32 u32ItemValue;
}MMI_PREVIEWLINE2SRV_GENERICCFG_PREVIEW;


typedef struct MMI_PREVIEWLINE2SRV_CONTENT_PREVIEW_TAG
{
    ContentInfo_t *pstContentInfo;
}MMI_PREVIEWLINE2SRV_CONTENT_PREVIEW;

typedef struct MMI_PREVIEWLINE2SRV_SOPTION_PREVIEW_TAG
{
    CFGInfo_t *pstSOptionInfo;
}MMI_PREVIEWLINE2SRV_SOPTION_PREVIEW;


#define NUMBER_OF_DB_QUERY_FIELD 1

/**
 * Application structure
 */
typedef struct MMI_PREVIEWLINE2SRV_TAG
{
    DECLARE_FUNCTBL(IPREVIEWLINE2SRV);    // function table pointer
    u32 refCnt;     // reference count
    /* Add custom fields below */
    ICFGSrv *pICFGSrv;
    boolean bUseUserSettings;
    u32 u32UserSettings;
    MenuItemId_e eMenuItemID;
    PREVIEWLINE2_CALLBACKFUNC_PTR pPreviewLine2CallBackFunc;
    //Each Mode PTR

    MMI_PREVIEWLINE2SRV_GENERICCFG_PREVIEW *pGenericCFGPreview;
    MMI_PREVIEWLINE2SRV_CONTENT_PREVIEW *pConentPreview;
    MMI_PREVIEWLINE2SRV_SOPTION_PREVIEW *pSOptionPreview;
} MMI_PREVIEWLINE2SRV;

#endif /* __MMI_PREVIEWLINE2SRV_PRIV_H__ */
