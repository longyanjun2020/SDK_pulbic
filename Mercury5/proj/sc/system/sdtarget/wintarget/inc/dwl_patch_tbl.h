#ifndef __DWL_PATCH_TBL_H__
#define __DWL_PATCH_TBL_H__

#include "stdcomp.h"
#include "dwl_patch.h"

#ifdef __DWL_PATCH_TBL_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef __packed struct
{
    u32 offset;
    u32 size;
    u8 chksum;
} patch_info_t;

typedef struct
{
    u8 patch_type;
    s32 (*parse_header)(u8 *header, u32 size, patch_info_t *patch_info);
    s32 (*download_patch)(u32 size);
} patch_t;

#undef INTERFACE
#endif // #ifndef __DWL_PATCH_TBL_H__

