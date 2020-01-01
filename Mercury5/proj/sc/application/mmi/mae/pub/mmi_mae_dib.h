/**
 * @file mmi_mae_dib.h
 *
 * TODO: Add desctiptions here
 *
 * @version $Id: mmi_mae_dib.h 776 2009-05-05 13:26:50Z code.lin $
 */
#ifndef __MMI_MAE_DIB_H__
#define __MMI_MAE_DIB_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_dib_forward.h"


pDIB Dib_New(u16 nWidth, u16 nHeight, u16 nBpp, u8 nAlign4);
void Dib_Rlease(pDIB pDib);
MAE_Ret Dib_SetFormat(pDIB pDib, u32 nColorScheme);
MAE_Ret Dib_GetColorScheme(pDIB pDib, u32 *pColorScheme);

#endif /* __MMI_MAE_DIB_H__ */
