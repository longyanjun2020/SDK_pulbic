/******************************************************************************/
/* File    : sysimgprt.h                                                      */
/*----------------------------------------------------------------------------*/
/* Scope   : System Image Partition Info. header file                         */
/*                                                                            */
/******************************************************************************/
#ifndef __SYSIMGPRT_H__
#define __SYSIMGPRT_H__

/******************************************************************************/
/*  Includes                                                                  */
/******************************************************************************/
#include "stdcomp.h"


/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
/* Image Header definitions */
#define SYS_IMAGE_MAGIC_NUMBER      0x35913727  /* 35913727 is a prime number */
#define SYS_IMAGE_NAME_SIZE         16
#define SYS_IMAGE_HEADER_SIZE       sizeof(SysImageHeader_t)
#define SYS_STREAM_BLOCK_SIZE       512

/* Partition Table definitions */
#define SYS_PTABLE_MAGIC_NUMBER     0x57081391  /* 57081391 is a prime number */
#define SYS_PT_SIZE                 2048        /* partition table size, 1 page now */
#define SYS_PT_ENTRY_SIZE           sizeof(SysPTableEntry_t)    /* size of each entry */
#define SYS_PT_NUM_OF_ENTRY         20

#define SYS_PART_NUM_MMPBOOTLDR     0x00
#define SYS_PART_NUM_IMGPRT         0x01
#define SYS_PART_NUM_PHYCUS         0x02
#define SYS_PART_NUM_FATUSER        0x03


#define SYS_MAX_BOOTLOADER_SIZE     0x10000     /* 64KB */
#define SYS_MAX_BOOTLOADER_COUNT    0x10


/******************************************************************************/
/* Typedefs                                                                   */
/******************************************************************************/
typedef struct SysImageHeader_s {
    u32     magic;              /* magic number = SYS_IMAGE_MAGIC_NUMBER */
    char    imageName[SYS_IMAGE_NAME_SIZE];     /* image name */
    u32     imageChecksum;      /* image checksum */
    u32     imageVma;           /* image virtual memory addr */
    u32     imageLen;           /* image length in bytes */
    u32     imageType;          /* image type */
    u32     version;            /* software version of image */
                /* B1: major, B2: minor, B3B4: build number */
    u32     releaseDate;        /* image release date */
                /* B1B2: year, B3: month, B4: day */
    u32     headerChecksum;     /* checksum of this entry */
} SysImageHeader_t, *SysImageHeader_ptr;

typedef struct CompressHeader_s {
    u32     orignal_imageSize;    /* orignal image size (bytes)*/
    u32     compressedSize;       /* compressed image size (bytes)*/
    u32     comType;              /* compress algorithm type */
    u32     reserved;             /* reserved*/
} CompressHeader_t, *CompressHeader_ptr;


enum IMAGE_TYPE_E {
    IMAGE_TYPE_NONE = 0,            /* default */
    IMAGE_TYPE_PARTTABLE = 1,       /* partition table image */
    IMAGE_TYPE_LOADER = 2,          /* loader image */
    IMAGE_TYPE_DIAG = 3,            /* diagnostic image */
    IMAGE_TYPE_CONFIGDATA = 4,      /* configuration data image */
    IMAGE_TYPE_BOARDINFO = 5,       /* board information image */
    IMAGE_TYPE_BOARDSETTING = 6,    /* board setting image */
    IMAGE_TYPE_HOSTRUNTIME = 7,     /* host runtime image */
    IMAGE_TYPE_MMPRUNTIME = 8,      /* mmp runtime image */
    IMAGE_TYPE_PRISENSORTAB = 9,    /* primary sensor table image */
    IMAGE_TYPE_SECSENSORTAB = 10,   /* secondary sensor table image */
};

enum STORAGE_TYPE_E {
   STORAGE_TYPE_NAND = 0,
   STORAGE_TYPE_CF,
   STORAGE_TYPE_NOR,
   STORAGE_TYPE_UNKNOWN
};


typedef struct SysPTableEntry_s {
    u32  imageLma;           /* load memory addr of this image partition */
    u32  imageSize;          /* size of this image partition */
    u32  imageType;          /* image type */
    bool isDefault;          /* is it default image? */
} SysPTableEntry_t, *SysPTableEntry_ptr;

typedef struct SysPartTable_s {
    u32  magic;              /* magic number = SYS_PTABLE_MAGIC_NUMBER */
    u32  storageType;
    u32  entryNum;
    u32  tableSize;
    SysPTableEntry_t    entries[SYS_PT_NUM_OF_ENTRY];
    u8   reserved[SYS_PT_SIZE - (SYS_PT_NUM_OF_ENTRY*SYS_PT_ENTRY_SIZE) -
                  (4 * sizeof(u32))];
                /* reserved, should be all zero */
} SysPartTable_t, *SysPartTable_ptr;

#endif /* __SYSIMGPRT_H__ */
