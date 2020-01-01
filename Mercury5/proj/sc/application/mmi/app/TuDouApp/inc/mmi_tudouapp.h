////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __MMI_TUDOUAPP_H__
#define __MMI_TUDOUAPP_H__
//#include "mmi_mae_window.h"

typedef u16 MAE_WndId;
typedef u16 MAE_WChar;
typedef u32 MAE_Ret;

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

//#ifdef __WLAN_MMI__ //CFGIT_CONNECT_WAP_CONNECT_SET" is undefined
#define TUDOU_APP_FEATURE_WAP
//#endif
#ifdef __MMI_KING_MOVIE__
#define TUDOU_APP_FEATURE_KING_MOVIE
#endif
#ifndef __NAND_MMI__
    #define TUDOU_APP_SUSPEND_MEMORY_FREE
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    TUDOU_FEATURE_WAP = 0,
    TUDOU_FEATURE_KINGMOVIE = 1,
    TUDOU_FEATURE_END
} TuDouFeature_e;
/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret TuDouAppNew(MAE_ClsId id, void **ppObj);
u16* TuDouUtf8ToUCS2(u16** pUnicode, const u8* pUTF8);
u8*  TuDouUCS2ToAscii(u8** pAscii, const u16* pUnicode);
u16* TuDouAsciiToUCS2(u16** pUnicode, const u8* pAscii);
char* TuDouitoa(char* dest, s32 v);
int TuDouatoi(const char *nptr);
MAE_Ret TuDouConvertKBToMB(MAE_WChar ** MB, char *KB);
const char *TuDouGetClientPF(void);
const char *TuDouGetClientSubPF(void);
const char *TuDouGetClientProjId(void);
const char *TuDouGetClientChId(void);
const char *TuDouGetClientSubChId(void);
boolean TudouGetFeatureFlag(u16 type);
void _TuDouUpdateImageAfterParseTempFile(IApplet *pIApplet);
MAE_Ret _TuDouParseTempFile(IApplet *pIApplet , MAE_WndId nWndId);
#endif /* __MMI_TUDOUAPP_H__ */
