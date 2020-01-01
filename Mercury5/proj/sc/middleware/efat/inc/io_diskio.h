#ifndef ONCE_DISKIO_H
#define ONCE_DISKIO_H
////////////////////////////////////////////////////////////////////////////////
///@file io_diskio.c
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_hal.h>
#include <infra_type.h>
#include <io_config_keys.h>
#include <io_devtab.h>

#ifdef __cplusplus
extern "C" {
#endif

struct efat_disk_identify_t
{
    char        serial[20+1];      // serial number
    char        firmware_rev[8+1]; // firmware revision
    char        model_num[40+1];   // model number
    efat_uint32  cylinders_num;     // number of cylinders         (CHS)
    efat_uint32  heads_num;         // number of heads             (CHS)
    efat_uint32  sectors_num;       // number of sectors per track (CHS)
    efat_uint32  lba_sectors_num;   // total number of sectors in LBA mode
    efat_uint32  phys_block_size;   // physical block size in sectors
    efat_uint32  max_transfer;      // Maximum transfer size in bytes
};

struct  efat_disk_partition_t
{
    efat_uint8  type;    // partition type
    efat_uint8  state;   // state 0x00 - inactive, 0x80 - active
    efat_uint32 start;   // first sector number
    efat_uint32 end;     // last sector number
    efat_uint32 size;    // size in sectors
};

struct  efat_disk_info_t
{
    efat_disk_identify_t         ident;         // identify data
    efat_disk_partition_t        partitions[4]; // partitions
    efat_addrword_t              devs[5];       // device instances
    efat_uint32                  block_size;    // logical block size
    efat_uint32                  blocks_num;    // number of blocks on disk
    efat_uint32                  phys_block_size; // physical block size
    efat_bool                    connected;     // true if device connected
    efat_ucount16                mounts;        // total number of mounts for all partitions
    struct efat_devtab_entry     devtab[4];     // Device table entries for partitions
//    disk_channel                diskchan[4];   // Disk channels for partitions
};

#ifdef __cplusplus
}
#endif

#endif  /* ONCE_DISKIO_H */
/* EOF diskio.h */
