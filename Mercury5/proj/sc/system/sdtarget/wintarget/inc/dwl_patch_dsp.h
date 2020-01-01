#ifndef __DWL_PATCH_DSP_H__
#define __DWL_PATCH_DSP_H__

#include "stdcomp.h"
#include "dwl_patch_tbl.h"
#include "dwl_patch.h"

#ifdef __DWL_PATCH_DSP_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef __packed struct
{
    u8 id;
    u32 offset;
    u32 size;
    u32 crc32;
} patch_bin_info_t;

typedef __packed struct
{
    u8 header_version;
    u8 patch_num;
    u8 has_mapping_table:1;
    u8 dwl_all_patch:1;
    u8 reserved_flags:6;
    u8 reserved;
    patch_bin_info_t patches[1];
} dsp_patch_header_t;

INTERFACE s32 patch_dsp_parse_header(u8 *header, u32 size, patch_info_t *info);
INTERFACE s32 patch_dsp_download(u32 size);

#undef INTERFACE
#endif // #ifndef __DWL_PATCH_DSP_H__

