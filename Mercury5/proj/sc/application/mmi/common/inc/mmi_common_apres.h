/*
Create by Nok.Wu 2008.12.15
manage AP resource.
*/
#ifndef _MMI_COMMON_APRES_H_
#define _MMI_COMMON_APRES_H_ 

#include "mmi_mae_common_def.h"
#include "mmi_mae_langcode.h"
#include "mmi_mae_class.h"
#include "mmi_mae_image.h"

#define APRES_RESID_MAX     0xFFFF
#define APRES_TEXTID_MAX    APRES_RESID_MAX
#define APRES_IMAGEID_MAX   APRES_RESID_MAX

typedef struct _APRES_TEXT_INFO_TAG
{
    u16 textid;
    MAE_WChar *buffer;
}_APRES_TEXT_INFO;

typedef struct _APRES_IMAGE_INFO_TAG
{
    u16 imageid;
    IImage *buffer;
}_APRES_IMAGE_INFO;

typedef _APRES_TEXT_INFO* (*Apres_GetTextLangLib_Callback) (MAE_LANG_CODE_e lang);
typedef _APRES_IMAGE_INFO* (*Apres_GetImageLib_Callback) (void);

MAE_WChar * Apres_GetString(IBase *pOwner,const u16 nTextID,Apres_GetTextLangLib_Callback cbGetTextLangLib);
IImage * Apres_GetImage(IBase *pOwner,const u16 nImageID,Apres_GetImageLib_Callback cbGetImageLib);

#endif

