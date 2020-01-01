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
* @file    mmi_picviewerapp_util.h
* @version
* @brief   Picture viewer customization header file
*
*/

#ifndef __MMI_PICVIEWERAPP_CUSTOM_H__
#define __MMI_PICVIEWERAPP_CUSTOM_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_common_util.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define PICVIEWER_TRANSITION_DURATION   250
#ifdef  __G_SENSOR_MMI__
#define PICVIEWER_GROTATE_TRANSITION_DURATION   50
#endif  /* __G_SENSOR_MMI__ */
#define PICVIEWER_NUMBER_OF_TRANSITION_TYPE   6   // The number of the transition type. skip TRANSITION_FLASH. It is easily thought as a bug by user.
#define PICVIEWER_NUMBER_OF_DIRECTION 4
#define PICVIEWER_ZOOM_AUTO_DECODE_TIME   500
#define PICVIEWER_SLIDESHOW_TIMER   3000    // Slide show timer
#define PICVIEWER_BATCH_SEARCH_FILE_NUM (200)   // Need to consider memory usage

#ifdef  __G_SENSOR_MMI__
#define __GMOTION_ROTATE__
#define __GMOTION_SHAKE__
#define PICVIEWER_ORIENTATION_BASE   ORIENTATION_PORTRAIT
#endif  /* __G_SENSOR_MMI__ */
#endif
