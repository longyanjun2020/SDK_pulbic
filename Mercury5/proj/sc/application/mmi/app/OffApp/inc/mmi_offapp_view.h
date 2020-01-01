/*****************************************************************************************
* @offapp_view.h
*
* Comment:
*
* @version:0.0.2  @ 2009.12.01
*****************************************************************************************/
#ifndef __offapp_view__H
#define __offapp_view__H

enum //VID_OFFAPP_POWEROFFANIM_enum
{
    WID_OFFAPP_ANIM_CNTR=0x1100,
    WID_OFFAPP_ANIM_IMAGE,
#ifdef __DUAL_LCD__
    WID_OFFAPP_SUB_ANIM_CNTR,
    WID_OFFAPP_SUB_ANIM_IMAGE,
#endif
}; //VID_OFFAPP_POWEROFFANIM_enum

typedef struct
{
    IWidget *pOffAnimCntr;
    IWidget *pOffAnimImage;
}OffAnimWdgList_t;

//*******************************************************************//
enum //VID_OFFAPP_NETWORK_enum
{
    WID_OFFAPP_NETWORK_CNTR=0x1100,
    WID_OFFAPP_NETWORK_IMAGE,
}; //VID_OFFAPP_NETWORK_enum

typedef struct
{
    IWidget *pOffNetCntr;
    IWidget *pOffNetImage;
}OffNetWdgList_t;

//*******************************************************************//
enum //VID_OFFAPP_IFONE_MAINVIEW_enum
{
    WID_OFFAPP_IFONE_CNTR=0x1100,
    WID_OFFAPP_IFONE_BGIMAGE,
    WID_OFFAPP_IFONE_FADE,
    WID_OFFAPP_IFONE_BTNIMAGE,
    WID_OFFAPP_IFONE_BTN,
    WID_OFFAPP_IFONE_SLIDE,
}; //VID_OFFAPP_IFONE_MAINVIEW_enum

typedef struct
{
    IWidget *pIfnAbsCntr;
    IWidget *pIfnBgImage;
    IWidget *pIfnFade;
    IWidget *pIfnBtnImage;
    IWidget *pIfnBtn;
    IWidget *pIfnSlide;
}OffIfnWdgList_t;

//*******************************************************************//
enum //VID_OFFAPP_SWITCHDUALMODE_enum
{
    WID_SM_MENU=0x1100,
}; //VID_OFFAPP_SWITCHDUALMODE_enum

typedef struct
{
    IWidget *pSmMenu;
}SmMenuWdgList_t;

//*******************************************************************//
#endif //__offapp_view__H
