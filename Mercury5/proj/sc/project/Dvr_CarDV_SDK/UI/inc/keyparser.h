
//==============================================================================
//
//  File        : keyparser.h
//  Description : INCLUDE File for the StateKeyParser function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _KEYPARSER_H_
#define _KEYPARSER_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

#include "MenuCommon.h"
#include "ahc_message.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/


/*===========================================================================
 * Enum define
 *===========================================================================*/

#if (SUPPORT_TOUCH_PANEL || SUPPORT_TOUCH_KEY)
typedef enum _VideoRecTouchButtonID{
    VIDEO_TOUCH_ID_NONE = EVENT_INDEX_DV,
    VIDEO_TOUCH_ID_MENU,        //1
    VIDEO_TOUCH_ID_MODE,        //2
    VIDEO_TOUCH_ID_FOCUS,
    VIDEO_TOUCH_ID_PLAYBACK,

    VIDEO_TOUCH_ID_WIDE ,        //5
    VIDEO_TOUCH_ID_TELE = VIDEO_TOUCH_ID_WIDE + 3,        //8
    VIDEO_TOUCH_ID_REC  = VIDEO_TOUCH_ID_TELE + 5,         //13
    VIDEO_TOUCH_ID_PAGE1,
    VIDEO_TOUCH_ID_PAGE2
    
}VideoRecTouchButtonID;

typedef enum _CaptureTouchButtonID{
    CAPT_TOUCH_ID_NONE = EVENT_INDEX_DSC,
    CAPT_TOUCH_ID_MENU,
    CAPT_TOUCH_ID_MODE,
    CAPT_TOUCH_ID_FOCUS,
    CAPT_TOUCH_ID_PLAYBACK,

    CAPT_TOUCH_ID_WIDE ,                         //5
    CAPT_TOUCH_ID_TELE = CAPT_TOUCH_ID_WIDE + 3, //8
    CAPT_TOUCH_ID_CAPT = CAPT_TOUCH_ID_TELE + 5,
    CAPT_TOUCH_ID_PAGE1,
    CAPT_TOUCH_ID_PAGE2
}CaptureTouchButtonID;

typedef enum _ThumbnailTouchButtonID{
    THUMB_TOUCH_ID_NONE = EVENT_INDEX_THUMBNAIL,
    THUMB_TOUCH_ID_MENU,
    THUMB_TOUCH_ID_MODE,
    THUMB_TOUCH_ID_PREVIEW,
    THUMB_TOUCH_ID_PAGEUP ,
    THUMB_TOUCH_ID_PAGEDOWN = THUMB_TOUCH_ID_PAGEUP + 2,
    THUMB_TOUCH_ID_FILE01,
    THUMB_TOUCH_ID_FILE02,
    THUMB_TOUCH_ID_FILE03,
    THUMB_TOUCH_ID_FILE04,
    THUMB_TOUCH_ID_FILE05,
    THUMB_TOUCH_ID_FILE06,
    THUMB_TOUCH_ID_EDIT_YES,
    THUMB_TOUCH_ID_EDIT_NO
}ThumbnailTouchButtonID;

typedef enum _JpgPlaybackTouchButtonID{
    JPGPB_TOUCH_ID_NONE = EVENT_INDEX_PHOTO_PB,
    JPGPB_TOUCH_ID_EXIT,
    JPGPB_TOUCH_ID_PREV,
    JPGPB_TOUCH_ID_NEXT,
    JPGPB_TOUCH_ID_ROTATE, 
    JPGPB_TOUCH_ID_ZOOMIN,
    JPGPB_TOUCH_ID_ZOOMOUT,
    JPGPB_TOUCH_ID_SLIDE, 
    JPGPB_TOUCH_ID_OSDSHOW,
    JPGPB_TOUCH_ID_MENU,    
    JPGPB_TOUCH_ID_PAGE1,
    JPGPB_TOUCH_ID_PAGE2    
}JpgPlaybackTouchButtonID;

typedef enum _MovPlaybackTouchButtonID{
    MOVPB_TOUCH_ID_NONE = EVENT_INDEX_VIDEO_PB,
    MOVPB_TOUCH_ID_EXIT,
    MOVPB_TOUCH_ID_PREV,
    MOVPB_TOUCH_ID_BKWD,
    MOVPB_TOUCH_ID_PLAY,
    MOVPB_TOUCH_ID_FRWD,
    MOVPB_TOUCH_ID_NEXT,
    MOVPB_TOUCH_ID_ROTATE, 
    MOVPB_TOUCH_ID_OSDSHOW,
    MOVPB_TOUCH_ID_MENU,     
    MOVPB_TOUCH_ID_PAGE1,
    MOVPB_TOUCH_ID_PAGE2     
}MovPlaybackTouchButtonID;

typedef enum _SlideShowTouchButtonID{
    SLIDESHOW_TOUCH_ID_NONE = EVENT_INDEX_SLIDESHOW,
    SLIDESHOW_TOUCH_ID_EXIT,
    SLIDESHOW_TOUCH_ID_PREV,
    SLIDESHOW_TOUCH_ID_BKWD,
    SLIDESHOW_TOUCH_ID_PLAY,
    SLIDESHOW_TOUCH_ID_FRWD,
    SLIDESHOW_TOUCH_ID_NEXT,
    SLIDESHOW_TOUCH_ID_ROTATE, 
    SLIDESHOW_TOUCH_ID_ZOOMIN,
    SLIDESHOW_TOUCH_ID_ZOOMOUT,
    SLIDESHOW_TOUCH_ID_OSDSHOW,
    SLIDESHOW_TOUCH_ID_MENU,     
    SLIDESHOW_TOUCH_ID_PAGE1,
    SLIDESHOW_TOUCH_ID_PAGE2     
}SlideShowTouchButtonID;
#endif

#if defined(CFG_REC_CALI_ON_AS_KEY_DOWN)
    #define CFG_REC_CALI_ON         EVENT_KEY_DOWN
    #define CFG_REC_CALI_OFF        EVENT_KEY_UP
#elif defined(CFG_REC_CALI_ON_AS_KEY_UP)
    #define CFG_REC_CALI_ON         EVENT_KEY_UP
    #define CFG_REC_CALI_OFF        EVENT_KEY_DOWN
#else
    #undef CFG_REC_CALI_ON
    #undef CFG_REC_CALI_OFF
#endif

/*===========================================================================
 * Function prototype
 *===========================================================================*/
#if (USB_MODE_SELECT_EN)
UINT32 KeyParser_USBModeSelectEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
#endif
UINT32 	VideoRecTouchEvent(UINT32 ulEvent, UINT32 ulParam);
UINT32 	CaptureTouchEvent(UINT32 ulEvent, UINT32 ulParam);
UINT32 	ThumbnailTouchEvent(UINT32 ulEvent, UINT32 ulParam);
UINT32 	MovPlaybackTouchEvent(UINT32 ulEvent, UINT32 ulParam);
UINT32 	JpgPlaybackTouchEvent(UINT32 ulEvent, UINT32 ulParam);
UINT32 	SlideShowTouchEvent(UINT32 ulEvent, UINT32 ulParam);

//void 	KeyParser_AddTouchOffset(PSMENUTOUCHBUTTON pButton);
//void 	KeyParser_ResetTouchVariable(void);
//void 	KeyParser_GetTouchPoint(UINT32 ulParam, PPOINT pPoint);
//void 	KeyParser_TouchItemRegister(SMENUTOUCHBUTTON *pButton, UINT8 ItemNum);
UINT32 	KeyParser_CaptureEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
UINT32 	KeyParser_VideoRecEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
UINT32 	KeyParser_ThumbnailEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
UINT32 	KeyParser_JpgPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
UINT32 	KeyParser_MovPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
UINT32 	KeyParser_HdmiEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
UINT32 	KeyParser_TVEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
UINT32 	KeyParser_MsdcEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
UINT32 	KeyParser_AudPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
UINT32 	KeyParser_NetPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
UINT32  KeyParser_NetStreamingEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);
UINT32  KeyParser_NetStreaming2ParentEvent(UINT32 *pulMsgId, UINT32 *pulEvent, UINT32 *pulParam);
UINT32  KeyParser_NetCGICmd2ParentEvent(UINT32 *pulMsgId, UINT32 *pulEvent, UINT32 *pulParam);
UINT32  KeyParser_NetCGICmdEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);
#endif   // _KEYPARSER_H_ 
