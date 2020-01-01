#ifndef _GSENSOR_CTRL_H_
#define _GSENSOR_CTRL_H_

#include "mmp_err.h"
#include "mmpf_gsensor.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

//Task
#define GSENSOR_FLAG_GSNRINFO2CHUCK     0x00000001
#define GSENSOR_CTL_FLAG_MAX            0x80000000

//General
#if defined(MINI_BOOT) || defined(MBOOT_FW)
#define GSENSOR_DBG_MSG                         (0)     // Keep 0 when build mini-boot or MBoot
#else
#define GSENSOR_DBG_MSG                         (1)     // For ALL_FW only
#endif

//File
#define GSNR_OFFSET_FILENAME                    "SD:0:\\DATA\\GSensor_Offset.bin"
#define GSNR_TEMP_INFOFILE_DIR                  "DATA"
#define GSNR_TEMP_INFOFILE_NAME                 "GSensor_Info.txt"

//Info for AVI chuck
//#define GSNR_MAX_INFONUM                          (500)
#define GSNR_MAX_INFONUM                        (4000) // Change to bigger for reduce the possible Gsensor write to file. The memory useage is 4000*12*2 = 96000 BYTES
#define GSENSOR_MAKE_FCC(c0, c1, c2, c3)        ((MMP_ULONG)c0        | ((MMP_ULONG)c1 << 8) | \
                                                ((MMP_ULONG)c2 << 16) | ((MMP_ULONG)c3 << 24))

//Max Dyanmic Range
#define MAX_2G                                  (199)   // 1.99G
#define MAX_4G                                  (399)   // 3.99G
#define MAX_6G                                  (599)   // 5.99G
#define MAX_8G                                  (799)   // 7.99G
#define MAX_16G                                 (1599)  // 15.99G

#define GSENSOR_DATA_LEN                        (3)

#if((GSENSOR_RAW_FILE_ENABLE == 1) && (GPS_RAW_FILE_ENABLE == 1))
#define GSENSOR_RAW_HEADER      "$GSENSORD,"
#endif

#define GSENSOR_ACCELERATION_UNIT_SC7A30E       (32)
#define GSENSOR_ACCELERATION_UNIT_DMARD06       (32)
#define GSENSOR_ACCELERATION_UNIT_LIS3DH        (16)
#define GSENSOR_ACCELERATION_UNIT_GMA301        (64)
#define GSENSOR_ACCELERATION_UNIT_MC3230        (85)//per 1G valume( x/128)=(100/150)

#define GSENSOR_DEFAULT_PRERECORD_TIME  0xFFFFFFFF

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef signed short        GSNR_SBYTE;
typedef unsigned char   GSNR_SENTIVITE;

typedef struct _GSNRINFOCHUCK
{
    GSNR_SBYTE  sbX;    //X axis value
    GSNR_SBYTE  sbY;    //Y axis value
    GSNR_SBYTE  sbZ;    //Z axis value

}GSNR_INFOCHUCK, *PGSNR_INFOCHUCK;

#if (VR_VIDEO_TYPE == COMMON_VR_VIDEO_TYPE_3GP)
// ulSize shound convert to big endian, the value of ulSize includes this header
typedef struct _GSNRCHUCKHEADER
{
    MMP_ULONG ulSize;       ///< chunk size, not including the initial 8 bytes
    MMP_ULONG ulFourCC;     ///< chunk ID

}GSNR_CHUCKHDR, *PGSNR_CHUCKHDR;

#else
// ulSize is little endian, the value of ulSize does not include this header
typedef struct _GSNRCHUCKHEADER
{
    MMP_ULONG ulFourCC;     ///< chunk ID
    MMP_ULONG ulSize;       ///< chunk size, not including the initial 8 bytes

}GSNR_CHUCKHDR, *PGSNR_CHUCKHDR;

#endif
/*===========================================================================
 * Function prototype
 *===========================================================================*/
void    AHC_Gsensor_OpenInfoFile(MMP_BYTE *ubFileName);
void    AHC_Gsensor_CloseInfoFile(void);
void    AHC_Gsensor_StartRecord(void);
void    AHC_Gsensor_EndRecord(void);
void    AHC_Gsensor_EndRecord_Backup(void);
void    AHC_Gsensor_RestoreAviChuck(void);
void    AHC_Gsensor_SetInfoChuckHeader(void);
PGSNR_INFOCHUCK AHC_Gsensor_GetInfoChuckAddr(void);
MMP_ULONG AHC_Gsensor_GetInfoChuckSize(void);
PGSNR_CHUCKHDR AHC_Gsensor_GetChuckHeaderAddr(MMP_UBYTE ubSelection);
void    AHC_Gsensor_SetAttribChuckHeader(void);
PGSNR_ATTRIBUTE AHC_Gsensor_GetAttributeAddr(void);
void    AHC_Gsensor_ResetBufCtrlVariable(void);
PGSNR_INFOCHUCK AHC_Gsensor_GetLastDataAddr(void);
PGSNR_INFOCHUCK AHC_Gsensor_GetBackupDataAddr(void);
MMP_BOOL AHC_Gsensor_RawWrite(MMP_BOOL bWriteFile);
void    AHC_Gsensor_TriggerRestorePreRecordInfo( MMP_BOOL bTrigger, UINT32 ulPreRecordTime, MMP_BOOL bUseLastData );
MMP_BOOL AHC_Gsensor_NeedToRestorePreRecordInfo( UINT32* ulPreRecordTime );
void    AHC_Gsensor_FlushBackupBuffer(MMP_UBYTE ubID, MMP_BOOL bEnable);
MMP_BOOL AHC_Gsensor_NeedToFlushBackupBuffer(MMP_UBYTE ubID);

/*===========================================================================
 * Extern varible
 *===========================================================================*/


#endif
