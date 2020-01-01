#ifndef __MMI_MAE_WIDGETBASE_TYPE_H__
#define __MMI_MAE_WIDGETBASE_TYPE_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_widget.h"

enum
{
    BORDER_LEFT,
    BORDER_RIGHT,
    BORDER_TOP,
    BORDER_BOTTOM,
    BORDER_TOTAL
};
enum
{
    PADDING_LEFT,
    PADDING_RIGHT,
    PADDING_TOP,
    PADDING_BOTTOM,
    PADDING_TOTAL
};

typedef void (*WDG_DRAW_FUNC_PTR) (IWidget*, IDispCanvas*, s32, s32);

typedef struct
{
    PFN_WIDGET_EVT_LISTENER pfnEvtListener;   ///<
    ModelEvtCode_t nEvtCode;
    u32 nMask;
    void *pUsrData1;                    ///< a context data pointer to pass into callback function
    void *pUsrData2;                   ///< a context data2 pointer to pass into callback function
}WdgListener_t;


#define _WIDGET_BASE_ELEMENTS \
    DECLARE_FUNCTBL(IWidget);                /*!< function table pointer*/ \
    u16             RefCnt;                    /*!< reference count*/ \
    u8               nListenerMax;              /*!< max size of the listener list*/ \
    u8               nListenerCnt;              /*!< current size of the listener list*/ \
    WidgetSize_t    wsize;                    /*!< keep this widget size(width and height)*/ \
    IContainer      *ParentContainerPtr;    /*!< this container indicate which container is this widget's parent.*/ \
    IModel          *ModelPtr;                /*!< this model keeps the data for this widget.*/ \
    WdgListener_t     *pListenerList;         /*!< event listener list.*/ \
    IModel          *ViewModelPtr;            /*!< view model pointer*/ \
    WidgetHandler_t HdlData;                /*!< a structure to keep the handle event function which is user provided.*/ \
    WHANDLER_HDL_FUNC_PTR DefHdlPtr;        /*!< the original handle event function when this widget created.*/ \
    u32             Flags;                    /*!< Abilities and settings flag*/ \
	MAE_ClsId         nClsID;                    /*! <class id of created widget> */ \
	u16 nProtectedRefCnt;                           /*!< protected reference count, the reference count cannot less than this value if flag WDG_BASE_FLAG_REFCOUNT_PROTECTED is on*/ \
	ModelListener_t sMdlLsn;                  /*!<widget common model listener>*/ \
    IBase *pOwner                           /*!< the owner (context) when this widget created.*/
/*deprecated    RGBColor_t      SelectedColor*/

#if defined(__G3D_MMI__)

#define WIDGET_BASE_ELEMENTS \
    _WIDGET_BASE_ELEMENTS; \
    u16				u16SceneHandleId;
    u32               nNodeID

#else

#define WIDGET_BASE_ELEMENTS \
    _WIDGET_BASE_ELEMENTS

#endif
/**
* WidgetBase structure, no border
*/
typedef struct {
    WIDGET_BASE_ELEMENTS;
} WidgetBase_t;

/**
* WidgetBase structure to support border
*/
typedef struct {
    WIDGET_BASE_ELEMENTS;

    WDG_DRAW_FUNC_PTR     FnDrawPtr;            ///< Draw function pointer
    WidgetSize_t          CntSize;                ///< Draw size of content
    IBase                *pBGObj;                ///< background IImage/IBitmap
    RGBColor_t            BGColor;                ///< background color
    RGBColor_t            BorderColor;            ///< border color
    u8                    Border[BORDER_TOTAL];    ///< 0:left/1:right/2:top/3:bottom border pixels
    u8                    Padding[PADDING_TOTAL];///< 0:left/1:right/2:top/3:bottom padding in pixels
    u8                    BgImgAlign;           ///< background image alignment.

#if defined(__G3D_MMI__)
    u32               nBgImgRawDataID;			///< RawData ID for background image/bitmap
#endif
} WidgetBaseEx_t;

#endif // __MMI_MAE_WIDGETBASE_TYPE_H__
