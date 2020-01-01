/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 2001
*/
/****************************************************************************/
/*  File    : dev_fat.hc                                               		*/
/*--------------------------------------------------------------------------*/
/*  Scope   : FAT16 file-system constants           						*/
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/* 23.12.02 |   NRO  |      |  Creation                                     */
/*----------+--------+------+-----------------------------------------------*/ 
/****************************************************************************/

#ifndef __VFS_FAT_HC__
#define __VFS_FAT_HC__

/*_____ I N C L U D E S ____________________________________________________*/
#include "vm_types.ht" 


/*_____ M A C R O S ________________________________________________________*/

#define STREAMING         ((u8)2)

#define FREE_CLUSTER      ((u16)0x0000)  /* free cluster value in FAT    */
#define LAST_CLUSTER      ((u16)0xFFFF)  /* last file cluster in FAT     */
#define BAD_CLUSTER       ((u16)0xFFF7)  /* bad cluster value in FAT     */

#define ATTR_HIDDEN       ((u8)0x02)      /* Hidden File Attribute */
#define ATTR_SYSTEM       ((u8)0x04)      /* System File Attribute */
#define ATTR_DIRECTORY    ((u8)0x10)      /* Directory Attribute */
#define ATTR_ARCHIVE      ((u8)0x20)      /* Archive Attribute */
#define ATTR_LFN_ENTRY    ((u8)0x0F)      /* LFN entry attribute */

#define FILE_NOT_EXIST    		((u8)0x00)      /* current file does not exist  */
#define FILE_DELETED      		((u8)0xE5)      /* current file is deleted      */

#define LFN_SEQ_MASK      		((u8)0x3F)      /* LFN sequence number mask     */

#define ODD_EVEN_MASK     		((u8)0x01)      /* the odd / even test mask     */

#define MAX_CLUSTERS12    		((u16)4084)    /* FAT12 if < FAT16 else */
/* Format Info */
#define ENTRY_SIZE          	((u8)32)        /* directory entry size         */
#define NB_ENTRIES_PER_SECTOR	((u8)16)    	/* nb entries per sector = SECTOR_SIZE/ENTRY_SIZE         */
#define NB_ROOT_ENTRY     		((u16)512)
#define NB_RESERVED       		((u8)1)         /* number of reserved sectors */
#define NB_FATS           		((u8)2)
#define HARD_DISK         		((u8)0xF8)      /* hard disk device */
#define FAT_DRIVE_NUMBER  		((u8)0x81)
#define FAT_EXT_SIGN      		((u8)0x29)

/* FAT definition */
/* For LFN name, the name will be build with MAX_LFN_ENTRIES entries        */
/* That means tha the max file name length is                               */
/* 12 + (MAX_LFN_ENTRIES - 1 ) * 13                                         */
/* Size in pdata zone is 256 bytes.                                         */
/* gl_buffer use 32 bytes in pdata                                          */
/* We need 15 bytes for scrolling display                                   */
/* Maximum size for LFN name is 256 - 32 - 15 = 209 bytes                   */
/* And so MAX_LFN_ENTRIES = (209 - 12) / 13 + 1 = 16                        */
/* And size of LFN string is                                                */
/* MAX_FILENAME_LEN = 12 + (MAX_LFN_ENTRIES - 1) * 13 + 15 + 1 + 1          */
/*                                                           |   |          */
/*                                  +1 because we start at 0 -   |          */
/*                                  +1 for '\0' character    -----          */

#define ENTRIES_PER_FILE   ((u8)3)       

/* maximum number of LFN entries */
#define MAX_LFN_ENTRIES   ((u8)16)       
/* maximum number of LFN entries */
#define ABSOLUTE_MAX_CHAR_LFN   ((u16)255)  /* in a LFN FAT16, a name is limited to 256 Unicode chararacters*/

#define MAX_FILE_FRAGMENT_NUMBER ((u8)128) /* maximum number of authorized */
                                            /* fragment for a file          */
#define MAX_ROOT_ENTRIES 			((u16)512)    /* maximum number of entries in root */
#define MAX_ROOT_FILE 			((u16)MAX_ROOT_ENTRIES/ENTRIES_PER_FILE)    /* maximum number of file in root */


#define MAX_DIRECTORY_GAP_FILE ((u16)(65535))
/*#define MAX_DIRECTORY_GAP_FILE ((u8)(255))*/
                                            /* maximum delta between 2      */
                                            /* specified entries            */
                                            /* Can be replace 255 or 65535  */
                                            /* case of type used for        */
                                            /* fat_directory_chain          */

#define READ_WRITE_MASK		0x3
#define NO_MORE_CLUSTER		0xFFFFFFFF

#define NB_FILES_MAX_OPENED VFS_NB_FILES_MAX

/*_____ M A C R O S ________________________________________________________*/

#define UPCASE(_c_) (((_c_>0x60)&&(_c_<0x7B)) ? (_c_-0x20) : _c_)
#define MIN(_x_,_y_) (((u32)_x_>(u32)_y_) ? _y_ : _x_)

#define FAT_DATE(_year_,_month_,_day_) ((_year_<<25)|(_month_<<21)|(_day_<<16))
#define FAT_TIME(_hour_,_minute_,_second_) ((_hour_<<11)|(_minute_<<5)|(_second_>>1))

#endif  /* __VFS_FAT_HC__ */

