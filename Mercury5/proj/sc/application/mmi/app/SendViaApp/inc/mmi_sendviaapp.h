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

/**
 * @file    mmi_sendviaapp.h
 * @version
 * @brief   send by app
 *
 */

#ifndef __MMI_SENDVIAAPP_H__
#define __MMI_SENDVIAAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
	SENDVIA_SENDTYPE_PLAINTEXT,
	SENDVIA_SENDTYPE_OBJECT

} SENDVIAPP_SENDTYPE_e;

typedef enum
{
	SENDVIA_FILETYPE_VCALENDAR,
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__        
	SENDVIA_FILETYPE_VCARD,
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__	
	SENDVIA_FILETYPE_VTODO,
	SENDVIA_FILETYPE_GENERAL,   // For files other than vCalendar, vCard and vToDo, such as Image, Music, Video, Voice memo, etc.
 	SENDVIA_FILETYPE_VGPSINFO,  // Send SMS orr MMS on map applet

} SENDVIAAPP_FILETYPE_e;

typedef struct
{
	SENDVIAAPP_FILETYPE_e eFileType;
    u32 nFileHandleID;
    u32 nId;
    u32 nType;
    u32 nGroup;
	boolean bNeedToDeleteFile;
    MAE_WChar *pUrl;
    MAE_WChar *pContent;

} SENDVIAAPP_SENDDATA_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret SendviaAppNew(MAE_ClsId id, void **ppObj);
void SendviaPreNew(void);
void SendviaFreeStartData(IBase* pIssuer, u32 nParam);
void SendviaLaunchApCb(void *pvUserData, MAE_Ret nRspCode);

#endif /* __MMI_SENDVIAAPP_H__ */
