/**
 *
 * @file    fms_nvram.h
 *
 * @brief   This file defines NVRAM interface
 *
 * @author  Patrick Yang
 * @version $Id: fms_nvram.h 14189 2008-09-18 04:36:19Z patrick.yang $
 *
 */

#ifndef __FMS_NVRAM_H__
#define __FMS_NVRAM_H__

#ifdef __UPGRADE_NVRAM__
//FMS NRAM erro code
typedef enum
{
    FMS_NVRAM_OK = 0,
    FMS_NVRAM_FAIL = 1,
    FMS_NVRAM_PARAM_ERROR = 2,
    FMS_NVRAM_NOT_READY = 3,
    FMS_NVRAM_RO_WRITE_ERROR = 4,
    FMS_NVRAM_RO_FLUSH_ERROR = 5,
    FMS_NVRAM_RO_READ_ERROR = 6,
    FMS_NVRAM_RW_READ_ERROR_1 = 7,
    FMS_NVRAM_RW_READ_ERROR_2 = 8,
    FMS_NVRAM_RW_READ_ERROR_3 = 9,
    FMS_NVRAM_RW_WRITE_ERROR_1 = 10,
    FMS_NVRAM_RW_WRITE_ERROR_2 = 11,
    FMS_NVRAM_RW_WRITE_ERROR_3 = 12,
    FMS_NVRAM_RW_FLUSH_ERROR_1 = 13,
    FMS_NVRAM_RW_FLUSH_ERROR_2 = 14,
    FMS_NVRAM_RW_FLUSH_ERROR_3 = 15,
    FMS_NVRAM_UPDATE_RW_STATUS_ERROR_1 = 16,
    FMS_NVRAM_UPDATE_RW_STATUS_ERROR_2 = 17,
    FMS_NVRAM_UPDATE_RW_STATUS_ERROR_3 = 18,
    FMS_NVRAM_UPDATE_RW_STATUS_ERROR_4 = 19,
    FMS_NVRAM_RW_READ_ERROR_0 = 20,
    FMS_NVRAM_RW_READ_FROM_CIS_ERROR = 21

}fms_Nvram_ErrCode;

/*
#define FMS_NVRAM_OK 0
#define FMS_NVRAM_FAIL 1
#define FMS_NVRAM_RO_WRITE_ERROR 2
#define FMS_NVRAM_RO_FLUSH_ERROR 3
#define FMS_NVRAM_RW_WRITE_ERROR_1 4
#define FMS_NVRAM_RW_WRITE_ERROR_2 5
#define FMS_NVRAM_RW_WRITE_ERROR_3 6
#define FMS_NVRAM_RW_FLUSH_ERROR_1 7
#define FMS_NVRAM_RW_FLUSH_ERROR_2 8
#define FMS_NVRAM_RW_FLUSH_ERROR_3 9
#define FMS_NVRAM_PARAM_ERROR 10
#define FMS_NVRAM_NOT_READY 11
#define FMS_NVRAM_UPDATE_RW_STATUS_ERROR_1 12
#define FMS_NVRAM_UPDATE_RW_STATUS_ERROR_2 13
#define FMS_NVRAM_UPDATE_RW_STATUS_ERROR_3 14
#define FMS_NVRAM_UPDATE_RW_STATUS_ERROR_4 15
*/

#define NANDNVRAM_RO_PARTITION_SIZE   (16*1024)
#ifdef __UPGRADE_NVRAM_ENHANCED__
#define NANDNVRAM_RW_PARTITION_SIZE   (24*1024)
#define NANDNVRAM_SMALLBLK_PARTITION_SIZE (16*1024)
#else
#define NANDNVRAM_RW_PARTITION_SIZE   (48*1024)
#endif

#define NAND_SECTOR_SIZE   (512)
/**
 * @brief FMS write NVRAM RO partition
 *
 * @param  pBuffer: Share buffer from modem
 *
 * @return  NVRAM error cde
 */
u32 fms_NvramWrite_Ro(u8 *pBuffer);


/**
 * @brief FMS write NVRAM Rw partition
 *
 * @param  pBuffer: Share buffer from modem
 *
 * @return  NVRAM error cde
 */
u32 fms_NvramWrite_Rw(u8 *pBuffer);

/**
 * @brief FMS read NVRAM Ro partition
 *
 * @param  pBuffer: Share buffer from modem
 *
 * @return  NVRAM error cde
 */
u32 fms_NvramRead_Ro(u8 *pBuffer);


/**
 * @brief FMS backup NVRAM RO partition
 *
 */
bool fms_BackupNvramROtoCIS(void);

#ifdef __UPGRADE_NVRAM_ENHANCED__
/**
 * @brief FMS read NVRAM Rw partition
 *
 * @param  pBuffer: Share buffer from modem
 *
 * @return  NVRAM error cde
 */
u32 fms_NvramRead_Rw(u8 **ppData, u16* u16Len);

bool fms_ReloadNvramRWfromCIS(u8 **ppData, u16* u16Len);

#ifdef __UPGRADE_NVRAM_ENHANCED_TEST_ONLY__
u32 fms_Nvram_IT_Modify_Nand_Ro(u32 nOffset, u32 nLen, u8 *data);

u32 fms_Nvram_IT_Modify_CIS_Ro(u32 nOffset, u32 nLen, u8 *data);

u32 fms_Nvram_IT_Modify_Nand_Rw(u32 nOffset, u32 nLen, u8 *data);

u32 fms_Nvram_IT_Modify_CIS_Rw(u32 nOffset, u32 nLen, u8 *data);
#endif //__UPGRADE_NVRAM_ENHANCED_TEST_ONLY__

#endif //__UPGRADE_NVRAM_ENHANCED__

/**
 * @brief FMS Initialize NVRAM Interface
 *
 */
void fms_NvramInterfaceInit(void);

#endif  /* __UPGRADE_NVRAM__ */

#endif  /* __FMS_NVRAM_H__ */

