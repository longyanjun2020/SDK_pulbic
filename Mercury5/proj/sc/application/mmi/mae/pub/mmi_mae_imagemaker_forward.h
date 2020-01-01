/**
 * @file mmi_mae_imagemaker_forward.h
 *
 * @version $Id: mmi_mae_imagemaker_forward.h $
 */
#ifndef __MMI_MAE_IMAGEMAKER_FORWARD_H__
#define __MMI_MAE_IMAGEMAKER_FORWARD_H__
#include "mmi_mae_common_def.h"

typedef u32 ImageEncType_e;

typedef u32 ImageMakerStatus_e;

typedef u32 ImgMkrRotate_e;

typedef struct ImageMakerCBData_t_ ImageMakerCBData_t;

typedef struct BmpPaletteData_t_ BmpPaletteData_t;

typedef struct ImgMkrEncData_t_ ImgMkrEncData_t;

typedef void (*PfnMAE_ImgMkr_Callback)(IBase*, ImageMakerCBData_t*);

#endif /* __MMI_MAE_IMAGEMAKER_FORWARD_H__ */
