/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
//#include "ahc_general.h"
#include "ahc_display.h"
#include "MenuCommon.h"
#include "MenuDrawCommon.h"
#include "MenuDrawingFunc.h"
#include "keyparser.h"
#include "IconPosition.h"
#include "IconDefine.h"
#include "ColorDefine.h"
#include "drawstatemsdcfunc.h"
#include "drawstatevideofunc.h"
#include "mmps_display.h"
#include "statetvfunc.h"
#include "MenuStateModeSelectMenu.h"

/*===========================================================================
 * Extern function
 *===========================================================================*/

extern void RTNA_LCD_Backlight(MMP_BOOL bEnable);
#if (USB_MODE_SELECT_EN)
extern USBMODE ubUSBSelectedMode;
#endif
extern AHC_BOOL                 gbAhcDbgBrk;
/*===========================================================================
 * Main body
 *===========================================================================*/

void DrawMSDC_USBConnect(void)
{
    UINT8   bID0 = 0;
    UINT8   bID1 = 0;
#if (USB_MODE_SELECT_EN == 0)
    RECT  	recRECT = POS_STATE_USB_CONNECT;
#endif
	UINT16 puiWidth, puiHeight,uiTemp, puiColorFormat, pulBufferAddr;
	AHC_OSD_ROTATE_DRAW_MODE rot;
	
    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_EnterDrawing(&bID0, &bID1);
    OSDDraw_ClearMainDrawBufferAll();
    OSDDraw_ClearOvlDrawOvlBufferAll();

	#ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
	#endif

    BEGIN_LAYER(bID0);
    AHC_OSDSetColor(bID0, /*0xAA000000*/OSD_COLOR_DARKGRAY2);
	AHC_OSDGetBufferAttr(bID0, &puiWidth, &puiHeight, &puiColorFormat, &pulBufferAddr);
	rot = AHC_OSDGetGuiRotateByGUI(bID0);

	if((OSD_ROTATE_DRAW_RIGHT_90 == rot)||(OSD_ROTATE_DRAW_RIGHT_270 == rot)){
		uiTemp = puiWidth;
		puiWidth = puiHeight;
		puiHeight = uiTemp;
	}
	AHC_OSDDrawFillRect(bID0,0,0,puiWidth,puiHeight);
	
	#if USB_MODE_SELECT_EN
    if(ubUSBSelectedMode == AHC_USB_MSDC_MODE)
        AHC_OSDDrawBitmap(bID0, &bmIcon_MSDC, (puiWidth>>1)-18, (puiHeight>>1)-15);
    else if(ubUSBSelectedMode == AHC_USB_PCAM_MODE)
        AHC_OSDDrawBitmap(bID0, &bmIcon_PCCAM, (puiWidth>>1)-18, (puiHeight>>1)-16);
	#else
    AHC_OSDDrawBitmap(bID0, &bmIcon_USB_Connect, recRECT.uiLeft, recRECT.uiTop);//draw 16bit bmp will hangup.
	#endif		

    AHC_SetDisplayMode(DISPLAY_MODE_PIP_DISABLE); //Disable thumbnail/playback PIP window

    OSDDraw_ExitDrawing(&bID0, &bID1);
    END_LAYER(bID0);

    RTNA_LCD_Backlight(MMP_TRUE);
}

#if 0
void ____Event_Handler____(){ruturn;} //dummy
#endif

void DrawStateMSDCUpdate(UINT32 ubEvent)
{
    switch(ubEvent)
    {
        case EVENT_NONE                           :
        break;

        case EVENT_USB_DETECT                     :
			DrawMSDC_USBConnect();
        break;

        default:
        break;
	}
}
