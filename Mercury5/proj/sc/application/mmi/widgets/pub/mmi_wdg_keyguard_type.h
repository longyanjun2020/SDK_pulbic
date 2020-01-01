
#ifndef _WISE_KEYGUARD_TYPE_H_
#define _WISE_KEYGUARD_TYPE_H_

typedef enum
{
    SLIDESWITCH_SIM1,
    SLIDESWITCH_SIM2
} SlideSwitchSimType_e;
//typedef u8 BallSlideSimType_e;

typedef struct
{
    SlideSwitchSimType_e 			eSimType;
    u32                     nMissCallNum;
} MissCallInfo_t;

typedef struct
{
    u32    nUnReadCallNum;
}UnReadMsgInfo_t;


typedef enum
{
   KGD_UNLOCK_DEFAULT,
   KGD_UNLOCK_DIALER,   ///START AP DIALER.
   KGD_UNLOCK_MESSAGE,  ///START AP MESSAGE CENTER.
   KGD_UNLOCK_CAMERA,   ///START AP CAMERA
   KGD_UNLOCK_EMAIL,    ///START AP CAMERA
   KGD_UNLOCK_MAINMENU, ///START AP TO MAINMENU
   KGD_UNLOCK_PHB,
   KGD_UNLOCK_MUSIC,    ///START AP QWPlayer
   KGD_UNLOCK_BE_QUIET, /// MAKE PHONE BE QUIET
   KGD_UNLOCK_TOTAL
} eKeyGuardStartType;
#ifdef __MMI_MULTI_KEYGUARD__

/*
*!!!IMPORTANT!!!
*REMEMBER TO update following places at the same time,
*and the sequence should be the same.
*   tTotalKGDStyle -------- mmi_keyguardapp.c
*   eKeyGuardStyle -------- mmi_wdg_keyguard_type.h
*   g_MainmenuData -------- mmi_keyguardsetting_menuitem.h
*/
typedef enum
{
#ifdef __MMI_KEYGUARD_DEFAULT__
   KGD_STYLE_DEFAULT,         ///ballslide
#endif //__MMI_KEYGUARD_DEFAULT__
#ifdef __MMI_KEYGUARD_SENSE__
   KGD_STYLE_SENSE,           ///sense switch
#endif
#ifdef __MMI_KEYGUARD_SLIDESWITCH__
   KGD_STYLE_SLIDESWITCH,
#endif
#ifdef __MMI_KEYGUARD_HONEYCOMB__
   KGD_STYLE_SWITCHNONEYCOMB,
#endif //__MMI_KEYGUARD_HONEYCOMB__
#ifdef __MMI_KEYGUARD_DOUBLESLIDE__
   KGD_STYLE_DOUBLESLIDE,
#endif //__MMI_KEYGUARD_DOUBLESLIDE__
#ifdef __MMI_KEYGUARD_TRANSFORMER__
   KGD_STYLE_TRANSFORMER,
#endif //__MMI_KEYGUARD_TRANSFORMER__
#ifdef __MMI_KEYGUARD_ZIPPER__
   KGD_STYLE_ZIPPER,
#endif //__MMI_KEYGUARD_ZIPPER__
#ifdef __MMI_KEYGUARD_RADIAN__
   KGD_STYLE_RADIAN,
#endif //__MMI_KEYGUARD_RADIAN__
#ifdef __MMI_KEYGUARD_CYCLE__
   KGD_STYLE_CYCLESLIDE,
#endif //
#ifdef __MMI_KEYGUARD_GOTO__
	  KGD_STYLE_GOTOSLIDE,
#endif //
#ifdef __MMI_KEYGUARD_POINTGRID__
	  KGD_STYLE_POINTGRID,
#endif //
#ifdef __MMI_KEYGUARD_HTC__
         KGD_STYLE_HTCSLIDE,
#endif //__MMI_KEYGUARD_HTC__
#ifdef __MMI_KEYGUARD_CHINESEINK__
   KGD_STYLE_CHINESEINK,
#endif //__MMI_KEYGUARD_CHINESEINK__
#ifdef __MMI_KEYGUARD_METALCORE__
   KGD_STYLE_METALCORE,
#endif //__MMI_KEYGUARD_METALCORE__
   KGD_STYLE_TOTAL_STYLE

}eKeyGuardStyle;

#endif//__MMI_MULTI_KEYGUARD__
#endif/*_WISE_KEYGUARD_TYPE_H_ */


