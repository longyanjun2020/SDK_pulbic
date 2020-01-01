#ifndef __DWL_PARAM_FRAME_H__
#define __DWL_PARAM_FRAME_H__

#ifdef __DWL_PARAM_FRAME_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define PARAM_START_FRAME     0x31
#define PARAM_DATA_FRAME      0x32
#define PARAM_ACK             0x33
#define PARAM_END_FRAME       0x34
#define PARAM_NAK             0x35

#define PARAM_RET_OK                  0
#define PARAM_RET_CHKSUM_ERROR       -1
#define PARAM_RET_INVALID_INPUT      -2
#define PARAM_RET_MALLOC_FAILED      -3

/*
 * a parameter frame is constructed by:
 * param_frame_header_t + param_payload_t + checksum
 */

#pragma pack(1)
typedef __packed struct
{
    u8 frame_type;
    u32 payload_size;
} param_frame_header_t;

typedef __packed struct
{
    u32 id;
    u32 length;
    u32 data[1];
} param_payload_t;

typedef __packed struct
{
    param_frame_header_t header;
    param_payload_t payload;
} param_frame_t;

INTERFACE s32 dwl_GetParamFrame(__packed param_frame_t **frame);

#undef INTERFACE
#endif

