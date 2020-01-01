//==============================================================================
//
//  File        : statenetcgicmdfunc.h
//  Description : INCLUDE File for the StateNetCGICmdFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATE_NET_CGI_CMD_FUNC_H_
#define _STATE_NET_CGI_CMD_FUNC_H_

#if (defined(WIFI_PORT) && WIFI_PORT == 1)
/*===========================================================================
 * Include files
 *===========================================================================*/ 

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 
 void STATE_NET_CGICMD_WIRELESS_SET_FLICKER(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_AWB(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_EV(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_MOT(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_MOVIE_SIZE(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_CLIP_TIME(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_VQUALITY(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_IMAGE_SIZE(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_POWROFF_DELAY(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_AUTO_PWROFF_TIME(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_MTD(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_TIME_FMT(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_TV_SYS(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_LCD_PWRS(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_PHOTOBURST(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_TIMELAPSE(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_UPSIDEDOWN(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_SPOTMETER(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_HDR(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_Q_SHOT(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_STATUSLIGHTS(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_SOUNDINDICATOR(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_POWERSAVING(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_UIMODE(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_LOOPINGVIDEO(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_GSENSOR(UINT32 ulEvent, UINT32 ulParam);
void STATE_NET_CGICMD_WIRELESS_SET_MUTE(UINT32 ulEvent, UINT32 ulParam);


AHC_BOOL StateNetCGICmdModeInit(void* pData);
AHC_BOOL StateNetCGICmdModeShutDown(void* pData);
UINT32 StateNetCGICmdModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);

#endif //#if (defined(WIFI_PORT) && WIFI_PORT == 1)
#endif //_STATE_NET_CGI_CMD_FUNC_H_

