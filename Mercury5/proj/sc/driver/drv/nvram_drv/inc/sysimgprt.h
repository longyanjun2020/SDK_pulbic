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
#include "nvram_stdcomp.h"


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
/* adler32.c -- compute Adler-32 checksum */
#define BASE 65521L     /* largest prime smaller than 65536 */
#define NMAX 5552
/* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

#define DO1(buf,i)  {s1 += buf[i]; s2 += s1;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);

/* ========================================================================= */



/******************************************************************************/
/* Typedefs                                                                   */
/******************************************************************************/
typedef struct SysImageHeader_s {
    u32     magic;              /* magic number = SYS_IMAGE_MAGIC_NUMBER */
    char    imageName[SYS_IMAGE_NAME_SIZE];     /* image name */
    u32     imageChecksum;      /* image checksum */
    u32     imageVma;           /* image virtual memory addr */
    u32     imageLen;           /* image length in bytes */
    u16     imageType;          /* image type */
    u32     version;            /* software version of image */
                /* B1: major, B2: minor, B3B4: build number */
    u32     releaseDate;        /* image release date */
                /* B1B2: year, B3: month, B4: day */
    u32     headerChecksum;     /* checksum of this entry */
} SysImageHeader_t, *SysImageHeader_ptr;

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
    u16  imageType;          /* image type */
    u32 isDefault;          /* is it default image? */
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


static unsigned long
adler32(const unsigned char *buf, unsigned long len)
{
	unsigned long s1, s2, k;

	if (len == 0)
	{
		return  1L;
	}
    else
    {	/* init adler32 checksum */
        s1 = 1;
        s2 = 0;
    }

    while (len > 0)
    {
        k = len < NMAX ? len : NMAX;
        len -= k;
        while (k >= 64)
        {
			asm (
				"\tb.prefetch 16(%0)\n"
				: : "r"(buf)
			);
			DO16(buf);
			buf += 16;
			asm (
				"\tb.prefetch 16(%0)\n"
				: : "r"(buf)
			);
			DO16(buf);
			buf += 16;
			asm (
				"\tb.prefetch 16(%0)\n"
				: : "r"(buf)
			);
			DO16(buf);
			buf += 16;
			asm (
				"\tb.prefetch 16(%0)\n"
				: : "r"(buf)
			);
			DO16(buf);
			buf += 16;
            k -= 64;
        }
		asm (
			"\tb.prefetch 0(%0)\n"
			"\tb.prefetch 16(%0)\n"
			"\tb.prefetch 32(%0)\n"
			"\tb.prefetch 48(%0)\n"
			: : "r"(buf)
		);
		if (k != 0)
		do
		{
			s1 += *buf++;
			s2 += s1;
		} while (--k);
        s1 %= BASE;
        s2 %= BASE;
    }
    return (s2 << 16) | s1;
}

#endif /* __SYSIMGPRT_H__ */
