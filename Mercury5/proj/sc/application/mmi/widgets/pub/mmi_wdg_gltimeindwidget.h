/**
* @file    mmi_wdg_gltimeindwidget.h
* @brief
* @version $Id: mmi_wdg_gltimeindwidget.h 37664 2010-02-12 09:36:01Z Elvis.Chen $
*/

#ifndef __MMI_WDG_GLTIMEINDWIDGET_H__
#define __MMI_WDG_GLTIMEINDWIDGET_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_window.h"



/*=============================================================*/
// type and define
/*=============================================================*/
enum
{
    GLTIMEIND_WDG_STYLE_START = 0,
    GLTIMEIND_WDG_STYLE_MINITE_SMALL = GLTIMEIND_WDG_STYLE_START,
    GLTIMEIND_WDG_STYLE_MINITE_LARGE,
    GLTIMEIND_WDG_STYLE_PAGE,
    GLTIMEIND_WDG_STYLE_SIMPLE,
    GLTIMEIND_WDG_STYLE_IDLE,

    GLTIMEIND_WDG_STYLE_NUM
};
typedef u16 GlTimeIndWidget_Style_e;

enum
{
    GLTIMEIND_WDG_DATE_NONE,
    GLTIMEIND_WDG_DATE_SMALL,
    GLTIMEIND_WDG_DATE_LARGE,
};
typedef u16 GlTimeIndWidget_Date_e;

enum
{
    GLTIMEIND_WDG_ANIMATION_TYPE_DEFAULT = 0,   // current time
    GLTIMEIND_WDG_ANIMATION_TYPE_KEYGUARD,      // from 13:55 -> 14:57

    GLTIMEIND_WDG_ANIMATION_TYPE_NUM

};
typedef u16 GlTimeIndWidget_Animation_Type;

/*=============================================================*/
// functions
/*=============================================================*/


#endif /* __MMI_WDG_GLTIMEINDWIDGET_H__ */
/*=============================================================*/
// end of file
