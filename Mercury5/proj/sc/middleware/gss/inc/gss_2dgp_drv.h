/**
 * \file gss_2dgp_drv.h
 * \brief 2dgp driver for V2751
*/

#ifndef __GSS_2DGP_DRV_H__
#define __GSS_2DGP_DRV_H__

typedef enum {
     NONE=0,
     LOAD,
     SAVE,
     MOVE,
     PATTERN_FILL,
     SOLID_FILL,
     LINE_DRAW
} operation_2dgp_t;

void gss_2dgp_Init(void);

void gss_2dgp_SetCtrl(u16 ctrl);
u16 gss_2dgp_GetCtrl(void);

void gss_2dgp_OperationCtrl(u8 operation);
void gss_2dgp_ROP(u8 rop);

void gss_2dgp_TransparencyEnable(bool active);
bool gss_2dgp_TransparencyIsEnabled(void);

void gss_2dgp_AlphaBlendingEnable(bool active);
bool gss_2dgp_AlphaBlendingIsEnabled(void);
void gss_2dgp_SetAlphaBlendingLvl(u8 level);
u8 gss_2dgp_GetAlphaBlendingLvl(void);

void gss_2dgp_SetPitch(u8 pitch);
u8 gss_2dgp_GetPitch(void);

void gss_2dgp_SrcJumpModeEnable(bool active);
bool gss_2dgp_SrcJumpModeIsEnabled(void);
void gss_2dgp_DstJumpModeEnable(bool active);
bool gss_2dgp_DstJumpModeIsEnabled(void);

void gss_2dgp_SetDirMove(bool PosOrNeg);
bool gss_2dgp_GetDirMove(void);
void gss_2dgp_StartOperation(void);
bool gss_2dgp_IsOn(void);
bool gss_2dgp_IsBusy(void);
void gss_2dgp_ClrStatus(void);

void gss_2dgp_SetSrcAddr(u32 mem_addr);
u32 gss_2dgp_GetSrcAddr(void);
void gss_2dgp_SetDstAddr(u32 mem_addr);
u32 gss_2dgp_GetDstAddr(void);

void gss_2dgp_SetBitBltWidth(u16 width);
u16 gss_2dgp_GetBitBltWidth(void);
void gss_2dgp_SetBitBltHeight(u16 height);
u16 gss_2dgp_GetBitBltHeigth(void);

void gss_2dgp_SetKeyColor(u16 KeyColor);
u16 gss_2dgp_GetKeyColor(void);

void gss_2dgp_SetPatternParam(u8 pattern_width,u8 pattern_height);

void gss_2dgp_SetLineDrawStart(u16 x,u16 y);
void gss_2dgp_GetLineDrawStart(u16 *x,u16 *y);
void gss_2dgp_SetLineDrawEnd(u16 x,u16 y);
void gss_2dgp_GetLineDrawEnd(u16 *x,u16 *y);

#endif //__GSS_2DGP_DRV_H__
