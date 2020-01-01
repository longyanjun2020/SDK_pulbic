/*****************************************************************************************
* @emuapp_view.h
*
* Comment:
*
* @version:0.0.2  @ 2009.12.01
*****************************************************************************************/
#ifndef __EMUAPP_VIEW_H__
#define __EMUAPP_VIEW_H__

typedef struct EMUAPP_GAME_M2LIB_VIEW_WdgList_tag
{
    IWidget *pWdgOsd;

#if defined(__EMU_VIRTUAL_KEYPAD_ENABLE__)
    IWidget *pWdgGameCtnr;
    IWidget *pWdgGameImgSelect;
    IWidget *pWdgGameImgStart;
    IWidget *pWdgGameCtnrABXY;
    IWidget *pWdgGameCtnrA;
    IWidget *pWdgGameCtnrB;
    IWidget *pWdgGameCtnrX;
    IWidget *pWdgGameCtnrY;
    IWidget *pWdgGameCtnrL;
    IWidget *pWdgGameCtnrR;
    IWidget *pWdgGameImgA;
    IWidget *pWdgGameImgB;
    IWidget *pWdgGameImgX;
    IWidget *pWdgGameImgY;
    IWidget *pWdgGameImgL;
    IWidget *pWdgGameImgR;
    IWidget *pWdgGameImgATxtL;
    IWidget *pWdgGameImgATxtM;
    IWidget *pWdgGameImgATxtR;
    IWidget *pWdgGameImgBTxtL;
    IWidget *pWdgGameImgBTxtM;
    IWidget *pWdgGameImgBTxtR;
    IWidget *pWdgGameImgXTxtL;
    IWidget *pWdgGameImgXTxtM;
    IWidget *pWdgGameImgXTxtR;
    IWidget *pWdgGameImgYTxtL;
    IWidget *pWdgGameImgYTxtM;
    IWidget *pWdgGameImgYTxtR;
    IWidget *pWdgGameImgLTxtL;
    IWidget *pWdgGameImgLTxtM;
    IWidget *pWdgGameImgLTxtR;
    IWidget *pWdgGameImgRTxtL;
    IWidget *pWdgGameImgRTxtM;
    IWidget *pWdgGameImgRTxtR;
    IWidget *pWdgGameCtnrJoystick;
    IWidget *pWdgGameImgJoystickBG;
    IWidget *pWdgGameImgJoystick;
#endif // __EMU_VIRTUAL_KEYPAD_ENABLE__
} EmuM2LibViewWdgList_t;

MAE_Ret EmuCreateM2LibView(HWIN hWin, EmuM2LibViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct EMUAPP_SETTINGS_VIEW_WdgList_tag
{
    IWidget *pWdgSettingsMenu;
} EmuSettingsViewWdgList_t;

MAE_Ret EmuCreateSettingsView(HWIN hWin, EmuSettingsViewWdgList_t *pWdgList);

//*******************************************************************//

typedef struct EMUAPP_SETTINGS_VOLUME_VIEW_WdgList_tag
{
    IWidget *pWdgSettingsVolume;
} EmuSettingsVolumeViewWdgList_t;

MAE_Ret EmuCreateSettingsVolumeView(HWIN hWin, EmuSettingsVolumeViewWdgList_t *pWdgList);

//*******************************************************************//

#if defined(__EMU_VIRTUAL_KEYPAD_ENABLE__)

#if defined(__GAME_ENGINE_EMU_16BIT__)
typedef struct EMUAPP_SELECT_KEYPAD_VIEW_WdgList_tag
{
    IWidget *pWdgSelectMenu;
} EmuSelectKeypadViewWdgList_t;

MAE_Ret EmuCreateSelectKeypadView(HWIN hWin, EmuSelectKeypadViewWdgList_t *pWdgList);
#endif // __GAME_ENGINE_EMU_16BIT__

typedef struct
{
    IWidget *pWdgKeypadBtnEMU8bitA;
    IWidget *pWdgKeypadBtnEMU8bitB;
} EmuKeypadSettingsEMU8bitViewWdgList_t;

#if defined(__GAME_ENGINE_EMU_16BIT__)
typedef struct
{
    IWidget *pWdgKeypadBtnSEMU16bitA;
    IWidget *pWdgKeypadBtnSEMU16bitB;
    IWidget *pWdgKeypadBtnSEMU16bitX;
    IWidget *pWdgKeypadBtnSEMU16bitY;
    IWidget *pWdgKeypadBtnSEMU16bitL;
    IWidget *pWdgKeypadBtnSEMU16bitR;
} EmuKeypadSettingsSEMU16bitViewWdgList_t;
#endif // __GAME_ENGINE_EMU_16BIT__

typedef struct
{
    IWidget *pWdgKeypadCtnr;
    IWidget *pWdgKeypadImgBG;
    IWidget *pWdgKeypadTxtHint;
    IWidget *pWdgKeypadBtnDefault;
    IWidget *pWdgKeypadFODefault;
    IWidget *pWdgKeypadBtnOK;
    IWidget *pWdgKeypadBtnCancel;
    IWidget *pWdgKeypadCtnrJoystick;
    IWidget *pWdgKeypadImgJoystickBG;
    IWidget *pWdgKeypadImgJoystick;
    IWidget *pWdgKeypadImgArrowBG;
    IWidget *pWdgKeypadCtnrABXY;
    IWidget *pWdgKeypadCtnrA;
    IWidget *pWdgKeypadCtnrB;
    IWidget *pWdgKeypadCtnrX;
    IWidget *pWdgKeypadCtnrY;
    IWidget *pWdgKeypadCtnrL;
    IWidget *pWdgKeypadCtnrR;
    IWidget *pWdgKeypadBtnA;
    IWidget *pWdgKeypadBtnB;
    IWidget *pWdgKeypadBtnX;
    IWidget *pWdgKeypadBtnY;
    IWidget *pWdgKeypadBtnL;
    IWidget *pWdgKeypadBtnR;
    IWidget *pWdgKeypadImgATxtL;
    IWidget *pWdgKeypadImgATxtM;
    IWidget *pWdgKeypadImgATxtR;
    IWidget *pWdgKeypadImgBTxtL;
    IWidget *pWdgKeypadImgBTxtM;
    IWidget *pWdgKeypadImgBTxtR;
    IWidget *pWdgKeypadImgXTxtL;
    IWidget *pWdgKeypadImgXTxtM;
    IWidget *pWdgKeypadImgXTxtR;
    IWidget *pWdgKeypadImgYTxtL;
    IWidget *pWdgKeypadImgYTxtM;
    IWidget *pWdgKeypadImgYTxtR;
    IWidget *pWdgKeypadImgLTxtL;
    IWidget *pWdgKeypadImgLTxtM;
    IWidget *pWdgKeypadImgLTxtR;
    IWidget *pWdgKeypadImgRTxtL;
    IWidget *pWdgKeypadImgRTxtM;
    IWidget *pWdgKeypadImgRTxtR;
    IWidget *pWdgKeypadBtnPreKeypadStyle;
    IWidget *pWdgKeypadBtnNextKeypadStyle;
    IWidget *pWdgKeypadCtnrKeypadStyleIndicator;
    IWidget *pWdgKeypadImgKeypadStyleIndicator1;
    IWidget *pWdgKeypadImgKeypadStyleIndicator2;
    IWidget *pWdgKeypadImgKeypadStyleIndicator3;
    IWidget *pWdgKeypadImgKeypadStyleIndicator4;
    IWidget *pWdgKeypadCtnrController;
    IWidget *pWdgKeypadBtnControllerOK;
    IWidget *pWdgKeypadBtnControllerCancel;
    IWidget *pWdgKeypadImgControllerBG;

    EmuKeypadSettingsEMU8bitViewWdgList_t tEMU8bitWdgList;

#if defined(__GAME_ENGINE_EMU_16BIT__)
    EmuKeypadSettingsSEMU16bitViewWdgList_t tSEMU16bitWdgList;
#endif // __GAME_ENGINE_EMU_16BIT__
} EmuKeypadSettingsViewWdgList_t;

MAE_Ret EmuCreateKeypadSettingsView(HWIN hWin, EmuKeypadSettingsViewWdgList_t *pWdgList);
#endif // __EMU_VIRTUAL_KEYPAD_ENABLE__

//*******************************************************************//
#endif //__EMUAPP_VIEW_H__
