/**
 * \file gss_ctrl.h
 * \brief Graphic sub system top level control driver	for V2751
*/

#ifndef __GSS_CTRL_H__
#define __GSS_CTRL_H__

#include "vm_types.ht"
#include "msgdidef.h"
/*
typedef enum  {
	GSS_PDB = 0,
	GSS_SDB
}GssDisplay_t;
by AlexDebug */
#define GssDisplay_t    u32 
#define GSS_PDB         MAIN_PANEL
#define GSS_SDB         SUB_PANEL
//====================>> By AlexDebug
/*
typedef enum  {
	GSS_8BPP = 0,//MSCOLORFORMAT_RGB8_332
	GSS_16BPP,   //MSCOLORFORMAT_RGB16_565
	GSS_24BPP,   //MSCOLORFORMAT_RGB24_888
	GSS_PWR_DWN
}GssCtrlPixelFormat_t;
*/
#define GssCtrlPixelFormat_t    MSCOLOR_FORMAT
#define GSS_8BPP                MSCOLORFORMAT_RGB8_332
#define GSS_16BPP               MSCOLORFORMAT_RGB16_565
#define GSS_24BPP               MSCOLORFORMAT_RGB24_888
#define GSS_PWR_DWN             MAX_AVAILABLE_SURFACE_FORMAT_ID

typedef enum  {
	GSS_CISI_BUFFER = 0,
	GSS_JPEG_BUFFER,
	GSS_2DGP_BUFFER
}GssDiplayInput_t;

typedef enum  {
	GSS_UNSYNCHRONIZED = 0, 
	GSS_HALF_SYNCHRO, // half-synchronized, CISI buffer READY signal / VSYNC free
	GSS_FULL_SYNCHRO, // full-synchronized, CISI buffer READY signal / VSYNC locked
	GSS_MJPEG_DEC //MJPEG decoding
} GssSynchro_t;

typedef enum  {
	GSS_PRIO_LCDC = 0,
	GSS_PRIO_CISI,
	GSS_PRIO_JPEG,
	GSS_PRIO_DMA,
	GSS_PRIO_BRIDGE,
	GSS_PRIO_2DGP
} GssCtrlPriority_t;

typedef enum  {
	GSS_PRIO_SOFTWARE = 0,
	GSS_PRIO_ROUND_ROBIN
} GssPriorityMngt;

#define INT_2DGP_EOP 		0
#define INT_CISI_EOP 		1
#define INT_CISI_PIXOVF 		2
#define INT_JPEG_EOP 		3
#define INT_JPEG_ADDOVF 	4
#define INT_JPEG_MISDATA 	5
#define INT_JPEG_CFGERR 	6
#define INT_LCDC_EOP 		7
#define INT_AHB_2DGP_ERR 	16
#define INT_AHB_CISI_ERR 	17
#define INT_AHB_JPEG_ERR 	18
#define INT_AHB_LCDC_ERR 	19

#define NB_PRIORITIES 6

void gss_ctrl_ConfigDiplayBuffer(GssDisplay_t display, u16 width, u16 height, GssCtrlPixelFormat_t format);
void gss_ctrl_GetConfigDiplayBuffer(GssDisplay_t display, u16 *width, u16 *height, GssCtrlPixelFormat_t *format);
void gss_ctrl_PwrDown(GssDisplay_t display);
void gss_ctrl_SetDisplayAddr(GssDisplay_t display, u32 addr);
void gss_ctrl_GetDisplayAddr(GssDisplay_t display, u32 *addr);
void gss_ctrl_SelectDisplayBuffer(GssDiplayInput_t input,  GssDisplay_t display);
void gss_ctrl_SetR2BAddr(u32 addr);
void gss_ctrl_SetDblBufAddr(u32 addr);
void gss_ctrl_SetSynchroMode(GssSynchro_t synchro);
void gss_ctrl_DoubleBuffering(bool activate);
void gss_ctrl_SetPriority(GssPriorityMngt mngt, GssCtrlPriority_t priorities[NB_PRIORITIES]);
u32 gss_ctrl_ReadIrqRawStatus(void);
void gss_ctrl_MaskIrq(u8 irq);
void gss_ctrl_UnMaskIrq(u8 irq);
void gss_ctrl_ClearIrq(u8 irq);
void gss_ctrl_Handler(void);
void gss_ctrl_EnableIrq(void);
u32 gss_ctrl_GetMemorySize(void);
void gss_ctrl_Init(void);

#endif // __GSS_CTRL_H__
