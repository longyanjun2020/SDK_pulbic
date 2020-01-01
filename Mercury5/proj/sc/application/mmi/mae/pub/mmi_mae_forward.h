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
* @file    mmi_mae_forward.h
* @version
* @brief
*
*/
#ifndef __MMI_MAE_FORWARD_H__
#define __MMI_MAE_FORWARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"


/*=============================================================*/
// Forward declarations
/*=============================================================*/
typedef struct IBase_tag IBASE;
typedef struct IHandler_tag IHANDLER; ///< for handler related methods
typedef struct IApplet_tag IAPPLET; ///< for applet related methods
typedef struct IImage_tag IIMAGE; ///< for resource methods
typedef struct IBitmap_tag IBITMAP; ///< for resource methods
typedef struct IBitmapExt_tag IBITMAPEXT;
typedef struct IShell_tag ISHELL;
typedef struct IImageMaker_tag IIMAGEMAKER;
typedef struct IFont_tag IFONT;
typedef struct IModel_tag IMODEL;
typedef struct IArrayModel_tag IARRAYMODEL;
typedef struct IDataModel_tag IDATAMODEL;
typedef struct IInterfaceModel_tag IINTERFACEMODEL;
typedef struct IListModel_tag ILISTMODEL;
typedef struct IVectorModel_tag IVECTORMODEL;
typedef struct IBattery_tag IBATTERY;
typedef struct IClock_tag ICLOCK;
typedef struct IConfig_tag ICONFIG;
typedef struct IDisplay_tag IDISPLAY;
typedef struct IEventDB_tag IEVENTDB;
typedef struct ILogdb_tag ILOGDB;
typedef struct ILogDBMgr_tag ILOGDBMGR;
typedef struct ITaskDB_tag ITASKDB;
typedef struct ITaskDBMgr_tag ITASKDBMGR;
typedef struct IGPS_tag IGps;
typedef struct IMotionDetector_tag IMOTIONDETECTOR;
typedef struct ISensorMgr_tag ISENSORMGR;
typedef struct ISysStat_tag ISYSSTAT;
typedef struct IText_tag ITEXT;
typedef struct ITextTable_tag ITEXTTABLE;
typedef struct ITouchSrv_tag ITOUCHSRV;

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/


#ifdef __cplusplus
}
#endif

#endif
