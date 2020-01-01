#ifndef __MMI_SOKOBANAPP_PRIV_H__
#define __MMI_SOKOBANAPP_PRIV_H__

#include "mmi_baseapplet.h"
#include "mmi_SokobanApp_id.h"
#include "SokobanApp_resource.h"

typedef enum
{
	STATUS_IDLE = 0,
	STATUS_PLAY,
	STATUS_OPTION
}SokobanStatus_e;


typedef struct
{
	IBitmap *pUDBmp;
	IBitmap *pBmp;
}SokobanWndData_t;

typedef struct
{
	APPLET_BASE_ELEMENTS;
	int tmp_idx;
	int index;//map index
	int status;
	boolean bSuspendAp;
	boolean bCloseAp;
    IWidget *pSuspendImgWidget;
}mmi_SokobanApp_t;

#endif //__MMI_SOKOBANAPP_PRIV_H__
