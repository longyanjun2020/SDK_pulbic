/**
 * \file    mae_font_priv.h
 * \brief   The document describes the private data structure used in mae_font.c
 *
 * @version
 */

#ifndef __MAE_FONT_PRIV_H__
#define __MAE_FONT_PRIV_H__

/******************************/
/*        INCLUDE             */
/******************************/
#include "mmi_mae_interface_def.h"
#include "mmi_mae_font.h"

/******************************/
/*        DEFINITION          */
/******************************/
typedef struct
{
	DECLARE_FUNCTBL(IFont);     ///< Function table
	u32         nRefCnt;        ///< Reference count
	FontBase_t  *pIFontBase;
}_Font_t;

#endif
