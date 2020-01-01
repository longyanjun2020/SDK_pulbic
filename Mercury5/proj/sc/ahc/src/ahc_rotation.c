//==============================================================================
//
//  File        : AHC_rotation.c
//  Description : AHC rotation function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "Config_SDK.h"
#include "ahc_rotation.h"
#include "ahc_display.h"
#include "ahc_sensor.h"
#include "ahc_parameter.h"
#include "MenuSetting.h"
#include "mmpf_sf.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/

static UINT8 m_ubRotateSrc = SRC_MAX;

/*===========================================================================
 * Main body
 *===========================================================================*/ 

AHC_BOOL AHC_GetFlipSelection(UINT8 ubCtrl,UINT8* pSelection,UINT8* pbLinkMenu)
{
    if(ubCtrl == CTRL_BY_MENU)
    {
        *pSelection = MENU_FLIP_SELECT;
        *pbLinkMenu = AHC_TRUE;
    }
    else if(ubCtrl == CTRL_BY_KEY)
    {
        *pSelection = KEY_FLIP_SELECT;
        *pbLinkMenu = KEY_FLIP_LINK_MENU;
    }
    else if(ubCtrl == CTRL_BY_HALL_SNR)
    {
        *pSelection = HALL_SNR_FLIP_SELECT;
        *pbLinkMenu = HALL_SNR_FLIP_LINK_MENU;
    }
    else if(ubCtrl == CTRL_BY_G_SNR)
    {
        *pSelection = G_SNR_FLIP_SELECT;
        *pbLinkMenu = G_SNR_FLIP_LINK_MENU;
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_CheckOSDFlipEn(UINT8 ubCheck)
{
    UINT8    ubOSDFlipEn = 0;
    UINT8    ubSelect1   = 0, ubSelect2   = 0, ubSelect3   = 0, ubSelect4   = 0;
    UINT8    ubLinkMenu1 = 0, ubLinkMenu2 = 0, ubLinkMenu3 = 0, ubLinkMenu4 = 0;

    if(ubCheck & CTRL_BY_MENU)
        AHC_GetFlipSelection(CTRL_BY_MENU, &ubSelect1, &ubLinkMenu1);

    if(ubCheck & CTRL_BY_KEY)
        AHC_GetFlipSelection(CTRL_BY_KEY, &ubSelect2, &ubLinkMenu2);

    if(ubCheck & CTRL_BY_HALL_SNR)
        AHC_GetFlipSelection(CTRL_BY_HALL_SNR, &ubSelect3, &ubLinkMenu3);

    if(ubCheck & CTRL_BY_G_SNR)
        AHC_GetFlipSelection(CTRL_BY_G_SNR, &ubSelect4, &ubLinkMenu4);

    ubOSDFlipEn = ((ubSelect1 & FLIP_OSD) | (ubSelect2 & FLIP_OSD) | (ubSelect3 & FLIP_OSD) | (ubSelect4 & FLIP_OSD)) ;

    return (ubOSDFlipEn)?(AHC_TRUE):(AHC_FALSE);
}

AHC_BOOL AHC_CheckSNRFlipEn(UINT8 ubCheck)
{
    UINT8    ubSNRFlipEn = 0;
    UINT8    ubSelect1   = 0, ubSelect2   = 0, ubSelect3   = 0, ubSelect4   = 0;
    UINT8    ubLinkMenu1 = 0, ubLinkMenu2 = 0, ubLinkMenu3 = 0, ubLinkMenu4 = 0;

    if(ubCheck & CTRL_BY_MENU)
        AHC_GetFlipSelection(CTRL_BY_MENU, &ubSelect1, &ubLinkMenu1);

    if(ubCheck & CTRL_BY_KEY)
        AHC_GetFlipSelection(CTRL_BY_KEY, &ubSelect2, &ubLinkMenu2);

    if(ubCheck & CTRL_BY_HALL_SNR)
        AHC_GetFlipSelection(CTRL_BY_HALL_SNR, &ubSelect3, &ubLinkMenu3);

    if(ubCheck & CTRL_BY_G_SNR)
        AHC_GetFlipSelection(CTRL_BY_G_SNR, &ubSelect4, &ubLinkMenu4);

    ubSNRFlipEn = ((ubSelect1 & FLIP_SNR) | (ubSelect2 & FLIP_SNR) | (ubSelect3 & FLIP_SNR) | (ubSelect4 & FLIP_SNR)) ;

    return (ubSNRFlipEn)?(AHC_TRUE):(AHC_FALSE);
}

AHC_BOOL AHC_CheckLinkWithMenu(UINT8 ubCheck)
{
    UINT8    ubLinkMenu  = 0;
    UINT8    ubSelect1   = 0, ubSelect2   = 0, ubSelect3   = 0, ubSelect4   = 0;
    UINT8    ubLinkMenu1 = 0, ubLinkMenu2 = 0, ubLinkMenu3 = 0, ubLinkMenu4 = 0;

    if(ubCheck & CTRL_BY_MENU)
        AHC_GetFlipSelection(CTRL_BY_MENU, &ubSelect1, &ubLinkMenu1);

    if(ubCheck & CTRL_BY_KEY)
        AHC_GetFlipSelection(CTRL_BY_KEY, &ubSelect2, &ubLinkMenu2);

    if(ubCheck & CTRL_BY_HALL_SNR)
        AHC_GetFlipSelection(CTRL_BY_HALL_SNR, &ubSelect3, &ubLinkMenu3);

    if(ubCheck & CTRL_BY_G_SNR)
        AHC_GetFlipSelection(CTRL_BY_G_SNR, &ubSelect4, &ubLinkMenu4);

    //ubLinkMenu = (ubLinkMenu1| ubLinkMenu2 | ubLinkMenu3 | ubLinkMenu4) ;
    ubLinkMenu = (ubLinkMenu2 | ubLinkMenu3 | ubLinkMenu4) ;

    return (ubLinkMenu)?(AHC_TRUE):(AHC_FALSE);
}

void AHC_SetRotateSrc(UINT8 src)
{
    m_ubRotateSrc = src;
}

UINT8 AHC_GetRotateSrc(void)
{
    return m_ubRotateSrc;
}

AHC_BOOL AHC_LinkLCDStatusToPara(UINT32 wValue)
{
    AHC_BOOL ubOSDFlipEn,ubLinkMenu;

    switch( AHC_GetRotateSrc() )
    {
        case SRC_KEY:
            ubOSDFlipEn = AHC_CheckOSDFlipEn(CTRL_BY_KEY);
            ubLinkMenu  = AHC_CheckLinkWithMenu(CTRL_BY_KEY);
        break;
        case SRC_HALL_SNR:
            ubOSDFlipEn = AHC_CheckOSDFlipEn(CTRL_BY_HALL_SNR);
            ubLinkMenu  = AHC_CheckLinkWithMenu(CTRL_BY_HALL_SNR);
        break;
        case SRC_G_SNR:
            ubOSDFlipEn = AHC_CheckOSDFlipEn(CTRL_BY_G_SNR);
            ubLinkMenu  = AHC_CheckLinkWithMenu(CTRL_BY_G_SNR);
        break;
        default:
            ubOSDFlipEn = AHC_FALSE;
            ubLinkMenu  = AHC_TRUE;
        break;
    }

    if(ubOSDFlipEn && ubLinkMenu)
    {
        MenuSettingConfig()->uiLCDRotate = (wValue==AHC_LCD_REVERSE)?(LCD_ROTATE_ON):(LCD_ROTATE_OFF);
    }
    return AHC_TRUE;
}


AHC_BOOL AHC_SetKitDirection(UINT8 LCDdir, AHC_BOOL bSetLCD, UINT8 SNRdir, AHC_BOOL bSetSnr)
{
//There is a problem when HDMI connecting and 0x8000_2BBF = 0xA5 (AHC_LCD_Direction).
#if (TVOUT_PREVIEW_EN)
    if (AHC_IsTVConnectEx()) {
        bSetLCD = AHC_FALSE;
    }
#endif
#if (HDMI_PREVIEW_EN)
    if (AHC_IsHdmiConnect()) {
        bSetLCD = AHC_FALSE;
    }
#endif
    if (bSetLCD)
    {
        if (LCDdir == AHC_LCD_NORMAL)
            AHC_LCD_Direction(LCD_0_DEGREE);
        else if (LCDdir == AHC_LCD_REVERSE)
            AHC_LCD_Direction(LCD_180_DEGREE);
    }

    if (bSetSnr)
    {
        if (AHC_SNR_IsSnrInitialized(gsAhcPrmSensor))
        {
            if (SNRdir == AHC_SNR_NORMAL)
                AHC_SNR_SetFlipDir(gsAhcPrmSensor, SENSOR_0_DEGREE);
            else if (SNRdir == AHC_SNR_REVERSE)
                AHC_SNR_SetFlipDir(gsAhcPrmSensor, SENSOR_180_DEGREE);
        }
    }

    return AHC_TRUE;
}

AHC_BOOL AHC_PreSetLCDDirection(void)
{
    #define INVALID_DATA    0xFF

    MMP_UBYTE checkSum = 0;
    MMP_USHORT i;
    MMP_UBYTE ubLCDStatus, ubSNRStatus, ubLCDSetting;
    MMP_ULONG SF_DestAddr;
    MMP_UBYTE tempBuf[MENU_STATUS_REGION_SIZE];
    MMPF_SIF_INFO *info;

    info = MMPF_SF_GetSFInfo();

    SF_DestAddr = info->ulSFTotalSize - MENU_STATUS_REGION_SIZE;

    MMPF_MMU_FlushDCacheMVA((MMP_ULONG)tempBuf, sizeof(tempBuf));
    MMPF_SF_ReadData(SF_DestAddr, (MMP_ULONG) &tempBuf, MENU_STATUS_REGION_SIZE);

    for (i = 0; i < SETTING_TOTAL_ITEMS; i++) {
        checkSum += tempBuf[MENU_STATUS_REGION_SIZE - 1 - i];    
        //RTNA_DBG_PrintByte(0, tempBuf[sizeof(tempBuf) - 1 - i]);
    }

    printc("Check sum = 0x%02X\r\n", checkSum);

    if (SETTING_CHECK_VALUE != checkSum) {
        RTNA_DBG_Str(0, FG_RED("AHC_PreSetLCDDirection: Check sum is invaild !!!\r\n"));
        ubSNRStatus  = AHC_SNR_NORMAL;
        ubLCDStatus  = (MenuSettingConfig()->uiLCDRotate == LCD_ROTATE_OFF) ? AHC_LCD_NORMAL : AHC_LCD_REVERSE;
        ubLCDSetting = MenuSettingConfig()->uiLCDRotate;
        Menu_WriteLcdSnrTVHdmiStauts2SF();
    }
    else {
        ubSNRStatus  = tempBuf[SNR_STATUS_OFFSET];
        ubLCDStatus  = tempBuf[LCD_STATUS_OFFSET];
        ubLCDSetting = tempBuf[LCD_MENU_SETTING_OFFSET];
    }

    printc("Read From SF SNR %d LCD %d Menu %d\r\n",ubSNRStatus, ubLCDStatus, ubLCDSetting);

    //Set OSD/Sensor Status
    ubLCDStatus = (MenuSettingConfig()->uiLCDRotate == LCD_ROTATE_ON) ? (AHC_LCD_REVERSE) : (AHC_LCD_NORMAL);

    AHC_SetParam(PARAM_ID_LCD_STATUS, ubLCDStatus);
    AHC_SNR_SetSnrDirStatus(ubSNRStatus);
    // Purpose: run SetSensorDefaultPosition to right initial setting of _snpos
    // 720P@30 and defined SENSOR_UPSIDE_DOWN => PIP window has garbage on the buttom
    AHC_SetKitDirection(ubLCDStatus, AHC_FALSE, ubSNRStatus, AHC_FALSE);

    return AHC_TRUE;
}
