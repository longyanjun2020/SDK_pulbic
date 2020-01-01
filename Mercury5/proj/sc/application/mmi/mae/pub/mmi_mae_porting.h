#ifndef __MMI_MAE_PORTING_H__
#define __MMI_MAE_PORTING_H__
/**
 * NOTE: Should not include any MMI related header here because
 * MAE will include this header for those extern variables and
 * functions 
 */
 ///MAE Pub Header
#include "mmi_mae_common_def.h"
#include "mmi_mae_dib_forward.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_touchsrv.h"
#include "mmi_mae_common_content.h"
#include "mmi_mae_clock.h"
#include "mmi_mae_clock_base.h"
#include "mmi_mae_clock_types.h"
#include "mmi_mae_display_types.h"
#include "mmi_mae_mime_type.h"
#include "mmi_mae_font_forward.h"
#include "mmi_mae_bitmap_forward.h"
#include "mmi_mae_customization_forward.h"
#include "mmi_mae_shell_memory_forward.h"

/*=============================================================*/
// lcd info
/*=============================================================*/
extern const u32 g_nMainLcdWidth;
extern const u32 g_nMainLcdHeight;
extern const ColorScheme_t g_nMainLcdClrScheme;
extern const u32 g_nMainLcdBPP;

#ifdef __DUAL_LCD__
extern const u32 g_nSubLcdWidth;
extern const u32 g_nSubLcdHeight;
extern const ColorScheme_t g_nSubLcdClrScheme;
extern const u32 g_nSubLcdBPP;
#endif
/*=============================================================*/
// Customization data
/*=============================================================*/
extern const u32 g_nCusImgBaseID;
extern const u32 g_nCusMelodyBaseID;
//for font default code
extern const u16 g_nIDefaultCode;
/*=============================================================*/
// for touch srv
/*=============================================================*/
MAERet_t MaePl_TouchSrvRegMsg(IShell *pShell, ITouchSrv *pTouchSrv);
MAERet_t MaePl_TouchSrvDeregMsg(IShell *pShell, ITouchSrv *pTouchSrv);
void MaePl_TouchSrvSetCalibration(MAE_TS_Calibration_t *pCalibrationData);
void MaePl_TouchSrvSetCalibrationMode(boolean bOn);
void MaePl_TouchSrvSetPollingTime(u16 nDelay);
void MaePl_TouchSrvGetResistance(u32 *xResistance, u32 *yResistance);
MAERet_t MaePl_TouchSrcEnableTouch(void);
MAERet_t MaePl_TouchSrcDisableTouch(void);
MAERet_t MaePl_TouchSrvGetTscrType(MAETscrType_e *pTscrType);

/*=============================================================*/
// for content
/*=============================================================*/

/**
 * Check if this item should install into content DB or not
 */
extern boolean MaePl_ContentIsExcludedPath(MAE_WChar *pPath, MAE_WChar *pName);
/**
 * Return the upper folder nId of build-in folders
 */
extern int MaePl_ContentGetParentCategoryIDForBuildInCategory(int nCId);
/*=============================================================*/
// for MIME type
/*=============================================================*/
extern const u16 g_nFILTERIDTypeCount;
extern const MAE_MIME_et *g_pFILTERID_BASE_MIME_TYPE[];
/**
 * Return the mime type nId for the given extension name
 */
extern MAE_MIME_et MaePl_MIME_FileExtToID(const MAE_WChar* pExt);

/**
 * Return the MIME type nId for the given mime type string
 */
extern MAE_MIME_et MaePl_MIME_StringToID(const char* pExt);

/*=============================================================*/
// for clock/RTC
/*=============================================================*/
extern const TimeZoneRule_t g_tMAE_Clock_timeZoneTbl[]; //< for customized timezone and daylight saving time rules
void MaePl_RtcInit(void);
void MaePl_RtcSetTimeZone(MAE_TimeZone_Field_e timeZoneField, MAE_TimeZone_e timeZone);
MAE_Ret MaePl_RtcGetTime(MAE_DateTime_t *pUTCDateTime);
MAE_Ret MaePl_RtcGetTimeRange(MAE_DateTime_t *pMinUTCDateTime, MAE_DateTime_t *pMaxUTCDateTime);
MAE_Ret MaePl_RtcSetTime(MAE_DateTime_t *pUTCDateTime);
u32 MaePl_RtcDateToSeconds(MAE_DateTime_t *pDateTime);
MAE_Ret MaePl_RtcSecondsToDate(u32 seconds, MAE_DateTime_t *pDateTime);
MAE_Ret MaePl_RtcConvertWeekday(MAE_DateTime_t *pUTCDateTime);
boolean MaePl_RtcIsValidDateTime(MAE_DateTime_t *pDateTime);
u32 MaePl_RtcGetUTCTimeInSeconds(void);
void MaePl_RtcMinuteTick(MAE_DateTime_t *pDateTime);

/*=============================================================*/
// for timer
/*=============================================================*/
extern const u32 g_nTimerBase;
MAE_Ret MaePl_TimerInit(void);
MAERet_t MaePl_TimerTerminate(void);
MAE_Ret MaePl_TimerStart(u16 nTimerID, boolean bCyclic, u32 nTimerValue);
u32 MaePl_TimerStop(u16 nTimerID);
boolean MaePl_TimerActive(u16 nTimerID);

/*=============================================================*/
// for memory
/*=============================================================*/
#ifdef __SDK_SIMULATION__
void *MaePl_MemoryAllocateGeneric(u32 size, u32 currentLr, int __mline__, char *__mfile__);
void *MaePl_MemoryAllocateHeap(u32 size, u32 currentLr, int __mline__, char *__mfile__);
void *MaePl_MemoryReAllocateGeneric(void *ptr, u32 size, u32 currentLr, int __mline__, char *__mfile__);
void *MaePl_MemoryReAllocateHeap(void *ptr, u32 size, u32 currentLr, int __mline__, char *__mfile__);
void *MaePl_MemoryClusterAllocateGeneric(MaeMenCluster_e nClusterId, u32 size, u32 currentLr, int __mline__, char *__mfile__);
void *MaePl_MemoryClusterReAllocateGeneric(MaeMenCluster_e nClusterId, void *ptr, u32 size, u32 currentLr, int __mline__, char *__mfile__);
void *MaePl_Memcpy(void *s1, const void *s2, size_t n);

void *MaePl_MemoryAllocateGenericEx(u32 size, u32 currentLr, int __mline__, char *__mfile__);
void *MaePl_MemoryAllocateHeapEx(u32 size, u32 currentLr, int __mline__, char *__mfile__);
void *MaePl_MemoryReAllocateGenericEx(void *ptr, u32 size, u32 currentLr, int __mline__, char *__mfile__);
void *MaePl_MemoryReAllocateHeapEx(void *ptr, u32 size, u32 currentLr, int __mline__, char *__mfile__);
#else
void *MaePl_MemoryAllocateGeneric(u32 size, u32 currentLr);
void *MaePl_MemoryAllocateHeap(u32 size, u32 currentLr);
void *MaePl_MemoryReAllocateGeneric(void *ptr, u32 size, u32 currentLr);
void *MaePl_MemoryReAllocateHeap(void *ptr, u32 size, u32 currentLr);
void *MaePl_MemoryClusterAllocateGeneric(MaeMenCluster_e nClusterId, u32 size, u32 currentLr);
void *MaePl_MemoryClusterReAllocateGeneric(MaeMenCluster_e nClusterId, void *ptr, u32 size, u32 currentLr);

void *MaePl_MemoryAllocateGenericEx(u32 size, u32 currentLr);
void *MaePl_MemoryAllocateHeapEx(u32 size, u32 currentLr);
void *MaePl_MemoryReAllocateGenericEx(void *ptr, u32 size, u32 currentLr);
void *MaePl_MemoryReAllocateHeapEx(void *ptr, u32 size, u32 currentLr);
#endif // __SDK_SIMULATION__
s32 MaePl_MemoryFree(void *ptr, u32 currentLr);
s32 MaePl_MemoryFreeEx(void *ptr, u32 currentLr);
s32 MaePl_MemoryClusterFree(void *ptr, u32 currentLr);
boolean MaePl_MemoryIsHeap(void *ptr);
boolean MaePl_MemoryIsPool(void *ptr);
void MAEPl_MemoryClusterInit(MAECluster_tbl_t *pClusterTbl);
void MAEPl_MemoryClusterUnInit(void);

MAE_Ret MaePl_MemoryExtEnable(boolean bEnable);

#ifdef __DEBUG_POOL__
#ifndef __PC_SIMULATOR__
void *MaePl_MemoryAllocateAux(u32 size);
s32 MaePl_MemoryFreeAux(void *ptr);
void *MaePl_MemoryReallocAux(void *ptr, u32 size);
#endif // __PC_SIMULATOR__
#endif // __DEBUG_POOL__
s32 MaePl_QueryMemorySize(void *ptr);

/*=============================================================*/
// for dib
/*=============================================================*/
pDIB MaePl_DibCreateSurface(u16 width, u16 height, u16 bpp, u8 bAlign4);
void MaePl_DibDestroySurface(pDIB pDib);
MAE_Ret MaePl_DibSetFormat(pDIB pDib, u32 nColorScheme);
MAE_Ret MaePl_DibGetColorScheme(pDIB pDib, u32 *pColorScheme);

/*=============================================================*/
// for display
/*=============================================================*/
extern const u8 nMMISupportLayer;
extern const u8 nMMIDefaultUILayer;
extern const u8 nMMIG3DLayer;

enum {
	DISP_ML_VIDEO_TYPE = 0,
	DISP_ML_GRAPHIC_0_TYPE,
	DISP_ML_GRAPHIC_1_TYPE,
	DISP_ML_G3D_TYPE,
	DISP_ML_MAX
};
typedef u8 DisplayLayerType_t;

typedef struct{
	s32    		x;
	s32    		y;
	pDIB    	pDib;
	Rect_t      UpdateRegion;
	DisplayLayerType_t  eType;
}DisplayLayerConfig_t;

typedef struct{
	DisplayLayerConfig_t Layer[MMI_DISP_LAYER_TOTAL];
	boolean isFire;
}DisplayUpdateML_t;

pDIB MaePl_DisplayInit(MAEDispId_t nId);
void MaePl_DisplayTerminate(MAEDispId_t nId, pDIB pDib);
void MaePl_DisplayUpdateDeviceDib(MAEDispId_t nId, pDIB pDib, Rect_t *pRC, boolean bUpdateQuick);
void MaePl_DisplayUpdateDeviceDibML(MAEDispId_t id, DisplayUpdateML_t *pUpdateParam);
void MaePl_DisplayUpdateUserDib(MAEDispId_t nId, pDIB pDib, boolean bUpdateQuick);

// Lock/unlock display buffer to avoid multiple tasks accessing the buffer at the same time
MAE_Ret MaePl_DisplayLock(void);
MAE_Ret MaePl_DisplayUnlock(void);
void MaePl_DisplayFlush( MAEDispId_t nId );
boolean MaePl_IsMdlScreenLayerEnable(MAEDispId_t nId);

/*=============================================================*/
// for g3d
/*=============================================================*/

/*=============================================================*/
// for device
/*=============================================================*/
void MaePl_LCDPowerOn(MAE_DispId_t id, boolean isOn);
void MaePl_AppEnterSleepMode(boolean isAllowed);

/*=============================================================*/
// for font
/*=============================================================*/
MAE_Ret MaePl_FontInit( boolean bLoadDefault );
MAE_Ret MaePl_FontFree( void );
MAE_Ret MaePl_FontMesureText( FontBase_t *pIFont, 
                                    u32 nFontCate,
                                    u32 nFontSize,
	                                const MAE_WChar *pcText, 
	                                u32 nChars, 
	                                u32 nOffset,
	                                u32 nSubLen,
	                                u32 nMaxWidth, 
                        			u32 *pnFits, 
                        			u32 *pnPixels,
                        			u32 nType,
                                	u32 nSkip,
                                	boolean bDispStr );
MAE_Ret MaePl_FontDrawText( FontBase_t *pIFont, 
							  u32 nFontCate,
	                          u32 nFontSize,          // Size
	                          BitmapBase_t *pDst,     // Destination BitmapBase
	                          s32 nX,                 // start x
	                          s32 nY,                 // start y
	                          const MAE_WChar *pcText,  // text buffer pointer
                              u32 nChars,             // number of text character
                              RGBColor_t sClrFg,        // foreground color
                              RGBColor_t sClrBg,        // background color
                              const Rect_t *psRect,     // Client area
                              u32 nType,
                              u32 *pColors,
                              u8 nNumColor );
MAE_Ret MaePl_FontGetInf( FontBase_t *pIFont, 
							 u32 nFontCate,
                           	 u32 nFontSize,
                           	 u32 nType, 
                          	 FontInfo_t *psInfo );
MAE_Ret MaePl_FontCreateGlyphDib( FontBase_t *pIFont,
                            			u32 nFontCat,
  				                        u32 nFontSize,
                				        u32 nType,
				                        u16 nCode,
                				        pDIB *ppDib );
boolean MaePl_IsUpdateFinish(MAEDispId_t nId,  pDIB pDib);

#endif //__MMI_MAE_PORTING_H__

