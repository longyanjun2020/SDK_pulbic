#ifndef _MS_MSD_FN_XFER_H_
#define _MS_MSD_FN_XFER_H_

typedef struct
{
    U8   opcode;
    U8   lun;
    U32  d32;
    U32  f32;
    U8   reserved[6];
} CBWCB;

typedef struct
{
    U32 signature;
    U32 tag;
    U32 dxfer_length;
    U8  dir_flag;
    U8  max_lun;
    U8  cmd_length;
    U8  unused;
    U8  cmd_bytes[16];
} MSDFN_BOT_CBW_STRU;

typedef struct
{
    U32 signature;
    U32 tag;
    U32 residue;
    U8  status;
    U8  unused1;
    U8  unused2;
    U8  unused3;
} MSDFN_BOT_CSW_STRU;

U8 USB_MSDFN_BOT_Calc_Case(MSDFN_BOT_CBW_STRU cbw,USB_VAR *gUSBStruct);
U8 USB_MSDFN_BOT_Err_Hndlr(MSDFN_BOT_CBW_STRU cbw,U8 sts,USB_VAR *gUSBStruct);
void USB_MSDFN_Decode_CBW(U8 *cbwP, MSDFN_BOT_CBW_STRU *cbw);
void USB_MSDFN_Encode_CSW(MSDFN_BOT_CSW_STRU *csw, U8 *cswP);
void USB_Endpoint_Bulk_In_Stall(USB_VAR *gUSBStruct);
void USB_Endpoint_Bulk_Out_Stall(USB_VAR *gUSBStruct);

#ifdef RAMDISK
#define RamDiskSize (64*1024)
extern U8 Storage_Mem[RamDiskSize];
extern U32 volatile Storage_Mem_Addr;
void RamDisk_Init(void);
U8 format(U32 Storage_Bass_Addr);
#endif  // RAMDISK

#endif   //_MS_MSD_FN_XFER_H_
