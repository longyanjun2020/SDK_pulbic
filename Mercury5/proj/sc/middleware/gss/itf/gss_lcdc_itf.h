/**
 * \file gss_lcdc_itf.h
 * \brief lcdc driver	for V2751
*/

#ifndef __GSS_LCDC_ITF_H__
#define __GSS_LCDC_ITF_H__

#include "vm_types.ht"
#include "gss_ctrl.h"

#define NONE_FLIPPED 0
#define PDB_FLIPPED  1 
#define SDB_FLIPPED  2
#define BOTH_FLIPPED 3

typedef struct {
   u8 mode; // PDB,SDB,overlay,transparency
   u16 lcdc_key_color;
   bool dot_disp;
} gss_display_t;

typedef struct {
   u8 type;
   u8 format;
   u8 serial_word_lenght;
   u8 repeat;
   u8 port;
} gss_lcd_t;

typedef struct {
   u16 pdb_width;
   u16 pdb_height;
   GssCtrlPixelFormat_t pdb_pix_depth;
   u16 sdb_width;
   u16 sdb_height;
   GssCtrlPixelFormat_t sdb_pix_depth;
} gss_lcdc_t;

typedef struct {
   u8 first;
   u8 second;
   u8 third;
   u8 fourth;
   u8 fifth;
   u8 sixth;
} gss_priority_ord_t;

typedef struct {
	u8 clk_splv_ws;
	u8 clk_stlv_ws;
	u8 ssel_cont;
	u8 cs_adv;
	u8 sdc_pos;
	u8 sdc_ins;
	u8 clk_pha;
	u8 clk_pol;
	u8 cs_pol;
	u8 sdc_pol;
	u8 bus_type;
 } gss_timing_t;

typedef struct {
 u8 Tframe;
 u8 TvPulse;
} gss_FrameTParam1_t;

typedef struct {
 u8 TvDisplay;
 u8 TvStart;
} gss_FrameTParam2_t;

typedef struct {
 u8 HsyncPulseWidth;
 u8 VsyncHsyncDelay;
} gss_LineTParam1_t;

typedef struct {
 u8 EnabWidth;
 u8 Hsync2EnabDelay;
} gss_LineTParam2_t;


typedef struct {
 u8 TclkHigh;
 u8 TclkLow;
 u8 HsyncPeriod;
} gss_LineTParam3_t;

void gss_lcdc_Init(void);
u16 gss_lcdc_ReadLcdCmdReg(u16 cmd);
void gss_lcdc_WriteLcdCommand(u16 cmd,u16 data);
void gss_lcdc_WriteLcdSingleCommand(u16 cmd);
void gss_lcdc_DisplaySettings(gss_display_t *param);
void gss_lcdc_DisplayAddress(u32 p_address,u32 s_address);
void gss_lcdc_LcdSettings(gss_lcd_t *param);
void gss_lcdc_Timing(gss_timing_t *timing);
void gss_lcdc_SelectLcd(u8 lcd_nb);
bool gss_lcdc_IsSelectedLcd(u8 lcd_nb);

void gss_lcdc_TransfertBuffer(void);
void gss_lcdc_TransfertBufferCpu(u16 cmd, bool wait);
void gss_lcdc_AutoTransfertBufferCpu(u16 cmd);

void gss_lcdc_CfgLcdc(gss_lcdc_t *param);
void gss_lcdc_PowerSaveOn(void);
void gss_lcdc_PowerSaveOff(void);

void gss_lcdc_DBAddress(u32 add_pdb,u32 add_sdb);
void gss_lcdc_DBManagement(u8 pdb,u8 sdb);

void gss_lcdc_Handler(void);
void gss_lcdc_SetPort(u8 port);

void LcdcIrqCallback(void);

#endif // __GSS_LCDC_ITF_H__
