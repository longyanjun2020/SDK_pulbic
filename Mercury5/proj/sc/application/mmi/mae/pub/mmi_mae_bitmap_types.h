/**
 * \file    mmi_mae_bitmap_types.h
 * \brief   
 *
 * @version
 */

#ifndef __MMI_MAE_BITMAP_TYPES_H__
#define __MMI_MAE_BITMAP_TYPES_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_graphic_forward.h"

/*!
 *  @brief Enum of bitblt type
 */
enum BitmapBlitType_e_
{
	BLIT_TYPE_NONE = 0,
	BLIT_TYPE_ROTATE_90CW = 1,	// src rotate 90 degree clockwise and blit to dst
	BLIT_TYPE_ROTATE_270CW = 2,	// src rotate 270 degree clockwise and blit to dst
	BLIT_TYPE_ROTATE_180CW = 3,	// src rotate 180 degree clockwise and blit to dst
};

/*!
 *  @brief Enum of transparent type
 */
enum
{
    TRANS_NONE = 0,  ///< no transparent
    TRANS_COLOR,     ///< use transparent color
    TRANS_ALPHA,      ///< use alpha mask
    TRANSPARENCY,    ///< use alpha value
    TRANS_TOTAL      ///< total number of transparent type
};
typedef u32 TransparentType_t;

/*!
 *  @brief Structure BitmapInfo
 */
struct BitmapInfo_t_
{
    u32 nWidth;                ///< number of pixels per row
    u32 nHeight;               ///< number of pixels per column
    u32 nColorScheme;         ///< color scheme
    u32 nColorDepth;          ///< number of significant bits per pixel
};

struct TransparentInfo_t_
{
	TransparentType_t tTransType;
	union
	{
		RGBColor_t  tTransColor;
		u8 nTransparency;
		struct
		{
			u8 *pAlphaMask;
			u32 nSize;
		}AlphaInfo;
	}TransData_u;
};

#endif /* __MMI_MAE_BITMAP_TYPES_H__ */

