#ifndef __DWL_PATCH_H__
#define __DWL_PATCH_H__

#ifdef __DWL_PATCH_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#include "stdcomp.h"

typedef __packed struct
{
    char sync_pattern[4];
    u8   patch_num;
    u8   reserved[6];
    u8   chksum;
} patch_protocol_start_t;

typedef __packed struct
{
    char sync_pattern[4];
    u32  header_length;
    u8   header_version;
    u8   patch_type;
    u8   reserved[1];
    u8   chksum;
} patch_file_header_t;

#define PATCH_HEADER_PARSE_DONE     0
#define PATCH_HEADER_OFFSET_SIZE    1

#define send_ACK()  dwl_SendChar(ACK)

INTERFACE s32 dwl_patch_Download(void);
INTERFACE void send_NAK(const char *strFormat, ...);

#undef INTERFACE
#endif // #ifndef __DWL_PATCH_H__

