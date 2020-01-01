/**
 * \file gss_lcdc_drv.h
 * \brief lcdc low level driver	for V2751
*/

#ifndef __GSS_LCDC_DRV_H__
#define __GSS_LCDC_DRV_H__

#include "vm_types.ht"

#define LCD_WRITE 0
#define LCD_READ 1

#define MODE_CMD 0
#define MODE_DATA 1

/**
 * \brief A0 position for serial mode
 */
#define WORD_START 0
#define WORD_END   1


#define PDB 0
#define SDB 1
#define BOTH_DB 2

#define CISI 0
#define JPEG 1
#define GP2D 2 

#define PIX_8BPP  0
#define PIX_16BPP 1
#define PIX_24BPP 2
#define PIX_12BPP 3



#define RGB_16_BPP   8

#define PRIMARY 0
#define SECONDARY 1
#define OVERLAY 2
#define TRANSPARENCY 3
/**
 * \brief OLD
 */
#define RGB          0
/**
 * \brief OLD
 */
#define BLUE  0x001f 
#define RED   0xF800 
#define GREEN 0x7c0  
#define WHITE 0xFFFF  

/**
 * \brief DESTINATION FORMAT
 */
#define DST_TYPE_PARALLEL_18  0
#define DST_TYPE_PARALLEL_16  1
#define DST_TYPE_PARALLEL_8   2
#define DST_TYPE_SERIAL_3     3
#define DST_TYPE_SERIAL_4     4
#define DST_TYPE_RGB          5
/**
 * \brief port selection
 */
#define CHIP_SELECT_LCD_0     0
#define CHIP_SELECT_LCD_1     1
/**
 * \brief Dot mapping
 */
#define DST_FORMAT(X)         (X)<<4
#define PIX_INV               1<<9
#define BLACK_SCREEN          1<<10
#define LCD_REPEAT(X)         (X)<<12
#define LCDC_SWL(X)           (X)<<16


/**
 * \brief TIMING CONTROL
 */
#define BUS_TYPE_80XX     0
#define BUS_TYPE_68XX     1

#define _CANIS_LCD_ON_G1_  1    /* CR-1196: enable CANIS (B1) LCD driver over G1 SW */


typedef struct {
 u8 RGBBusMode;
 u8 RGBOrder;
 u8 ClkPhase;
 u8 ClkPol;
 u8 HsyncPol;
 u8 VsyncPol;
 u8 EnaPol;
 u8 EnaClk;
} gss_MiscParam_t;


void gss_lcdc_SwStart(void);

bool gss_lcdc_IsBusy(void);

u16 gss_lcdc_ReadReg(void);

void gss_lcdc_SetOvlStartAddr(u32 addr);
u32 gss_lcdc_GetOvlStartAddr(void);

void gss_lcdc_TransfertToLcd(u32 start_address,u8 nb_param);
void gss_lcdc_TransfertDisplayBuffer(void);

void gss_lcdc_SetTransparencyColor(u16 color);
u16 gss_lcdc_GetTransparencyColor(void);

void gss_lcdc_SetDotDisplay(bool mode);
bool gss_lcdc_GetDotDisplay(void);

void gss_lcdc_SetTransfertMode(u8 mode);
u8 gss_lcdc_GetTransfertMode(void);

void gss_lcdc_SetDestinationFormat(u32 reg);
u32 gss_lcdc_GetDestinationFormat(void);

void gss_lcdc_SetDstPortType(u8 type);
u8 gss_lcdc_GetDstPortType(void);

void gss_lcdc_SetSelectedLcd(u8 lcd);
u8 gss_lcdc_GetSelectedLcd(void);

void gss_lcdc_SetTimingCtl(u32 reg);
u32 gss_lcdc_GetTimingCtl(void);

void gss_lcdc_SetA0Polarity(u8 pol);

void gss_lcdc_SetSrcFmt(u32 reg);
u32 gss_lcdc_GetSrcFmt(void);

void gss_lcdc_SetCmdCtrl(u32 reg);
u32 gss_lcdc_GetCmdCtrl(void);

void gss_lcdc_SetRnW(u8 mode);
u8 gss_lcdc_GetRnW(void);

void gss_lcdc_SetBlackScreen(bool enable);
void gss_lcdc_SetInvertPixel(bool enable);

void gss_lcdc_SetFlipDB(bool pdb,bool sdb);

void gss_lcdc_SetConfigMode(u8 mode);
u8 gss_lcdc_GetConfigMode(void);

void gss_lcdc_SetParamStartAddr(u32 addr);
void gss_lcdc_ClrUnrunFlag(void);
bool gss_lcdc_IsUnrun(void);

void gss_lcdc_SetMiscParam(gss_MiscParam_t *pMiscParam);
void gss_lcdc_SetFTParam1(u8 TPulseWidth , u8 TFrame);
void gss_lcdc_SetFTParam2(u8 Tv_Start, u8 Tv_Display);
void gss_lcdc_SetLTParam1(u8 Vs_Hs, u8 Hs_Width);
void gss_lcdc_SetLTParam2(u8 Hs_En_Delay, u8 En_Width );
void gss_lcdc_SetLTParam3(u8 Hs_Period, u8 Clk_Low, u8 Clk_High );
void gss_lcdc_SetEndPage(u32 JumpValue);

#endif //__GSS_LCDC_DRV_H__
