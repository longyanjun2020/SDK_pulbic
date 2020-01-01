/**
 * @file    mmi_util_fs.h
 *
 * @brief   This file defines the interface to access VML related to rai utilities.
 * @author	kenny.wu@mstatsemi.com
 *
 * @version $Id: mmi_util_fs.h 12680 2008-07-21 07:14:06Z kenny.wu $
 */

#ifndef __MAE_UTIL_FS_H__
#define __MAE_UTIL_FS_H__

#include "mmi_mae_common_def.h" 
#include "mmi_core_forward.h"
#include "mmi_mae_interface_def.h"

#define MMI_RAI_SIZE_MAX ( 30 * 1024 ) //30k bytes

typedef struct
{
    s32 mem_free;            // total byte amount of immediately available memory
    s32 mem_contig;          // byte amount of immediately available CONTIGUOUS memory
    s32 mem_avail;           // byte amount of memory available after complete garbage collection
    s32 mem_limit;           // total storage byte space
                             // (may be used as a scale factor for the other mem_xxx infos)
    s32 objects_read;        // number of objects read since last reboot
    s32 objects_created;     // number of objects created since last reboot
    s32 objects_overwritten; // number of objects overwritten since last reboot
    s32 objects_deleted;     // number of objects deleted since last reboot

    s32 sectors_erased;      // number of FLASH sectors erased since last reboot
#ifdef __NAND__
    int continuousmem[16];   // dump continuous memory space of each sector.
#endif

}mmi_raiStats_t; 

typedef u16 mmi_raiSize_t;
typedef u32 mmi_raiId_t;

typedef struct
{
	mmi_raiSize_t size;
}mmi_raiInfo_t;


/****************************************************************************/
/* TYPE DEFINITIONS                                                         */
/****************************************************************************/

/**
  * \brief Opaque handle 
  */
struct mmi_adHandle_t_
{
   u32 opaque[4];
};

/**
  * \brief Opaque iterator 
  */
typedef struct
{
   u32 opaque[4];
} mmi_adIterator_t;

/**
  * \brief Information structure 
  */
typedef struct
{
   u32   identifier;       ///< identifier 
   u32   size;             ///< entry size 
   void  *data;            ///< pointer to stored data 
   u32   remaining;        ///< remaining writable space unless finalised 
   boolean  finalised;        ///< TRUE if entry is finalised 
} mmi_adInfo_t;

/**
  * \brief Volume state 
  */
typedef struct
{
   u32 freemem;         ///< avalilable space in bytes
   u32 deletedmem;      ///< deleted space
   u32 totalmem;        ///< total space of the volume
   u16 numobjects;      ///< number of cells
   u16 numdeleted;      ///< number of deleted cells
   boolean need_recovery;  ///< if TRUE, the volume recompaction is not finished  
} mmi_adStats_t;

/**
  * \brief Volume state 
  */
typedef enum
{
   MMI_FMS_AD_ERROR,     ///< Error, volume does not exist 
   MMI_FMS_AD_READY,     ///< Volume is usable 
   MMI_FMS_AD_NOTAVAIL,  ///< Volume not available 
   MMI_FMS_AD_REPAIR,    ///< Volume under compaction or needing compaction recovery 
   MMI_FMS_AD_TO_FORMAT, ///< Volume needs to be formatted to be operational
   MMI_FMS_AD_FORMATTED  ///< Volume undergoing a format operation
} mmi_adState_e;

/** 
 * \brief Operation modes for wm_adFormat2 function
 */
typedef enum
{
   MMI_FMS_AD_FORMAT_INIT,        ///< To initialise the format process
   MMI_FMS_AD_FORMAT_CONTINUE,    ///< To actually run the format process
   MMI_FMS_AD_FORMAT_ABORT        ///< To abort the format process
} mmi_adFormatMode_e;

/** 
 * \brief list of available volumes
 */
typedef enum
{
   MMI_FMS_CUSTO_VOLUME,
   MMI_FMS_JAVASTORE_VOLUME,
   MMI_FMS_JAVAEXEC_VOLUME,
   MMI_FMS_DOTA_VOLUME,
   MMI_FMS_SOUND_VOLUME
} mmi_adToken_e;


/** 
 * \brief volume IOCTL control codes (to use with \ref vm_adVolumeIoControl)
 */
typedef enum
{
   MMI_FMS_AD_DELETE_ALL_UNCOMPLETE,
   MMI_FMS_AD_GET_FIRSTCELL_CONTENTSPTR
} mmi_adVolumeCtrlCode_e;  


/****************************************************************************/
/* EXPORTED FUNCTIONS                                                       */
/****************************************************************************/

void mmi_fs_raiInit(IBase *pIAccessory);
s32 mmi_fs_adAllocate(mmi_adToken_e i__e_Token, u32 i__u32_Ident, u32 i__u32_Size, mmi_adHandle_t *o__ps_Handle);
s32 mmi_fs_adWrite(mmi_adHandle_t *i__ps_Handle, u32 i__u32_Size, void *i__p_Buffer);
s32 mmi_fs_adResume(mmi_adHandle_t *io__ps_Handle);
s32 mmi_fs_adFinalise(mmi_adHandle_t *i__ps_Handle);
s32 mmi_fs_adRetrieve(mmi_adToken_e i__e_Token, u32 i__u32_Ident, mmi_adHandle_t *o__ps_Handle);
s32 mmi_fs_adFindInit(mmi_adToken_e i__e_Token, u32 i__u32_Min, u32 i__u32_Max, mmi_adIterator_t *o__ps_Browse);
s32 mmi_fs_adFindNext(mmi_adHandle_t *o__ps_Handle, mmi_adIterator_t *io__ps_Browse);
s32 mmi_fs_adInfo(mmi_adHandle_t *i__ps_Handle, mmi_adInfo_t *o__ps_Info);
s32 mmi_fs_adStats(mmi_adToken_e i__e_Token, mmi_adStats_t *o__ps_Stats);
s32 mmi_fs_adDelete(mmi_adHandle_t *i__ps_Handle);
s32 mmi_fs_adFormat(mmi_adToken_e i__e_Token);
s32 mmi_fs_adRecompactInit(mmi_adToken_e i__e_Token);
s32 mmi_fs_adRecompact(mmi_adToken_e i__e_Token);
mmi_adState_e mmi_fs_adVolumeState(mmi_adToken_e i__e_Token);
s32 mmi_fs_cusLoadData( u32 u32Offset, u8 *pu8Buffer, u32 u32BufferSize );


/****************************************************************************/
/* ADDITIONAL SPECIAL COMMANDS                                              */
/****************************************************************************/



/**
  * \fn		const int mmi_fs_raiWrite (vm_raiId_t ident, vm_raiSize_t size, const void * data);
  * \brief	Create or modify a random access item
  * \note   This function is likely to trigger garbage collection,
  *         therefore its response time may be over one second.
  * \param	[in] ident id of the created / modified object
  * \param	[in] size total size of the object
  * \param	[in] data object contents
  * \return	TRUE on success, FALSE if there is not enough space left or
  *         the requested size exceeds the \ref VM_FMS_RAI_SIZE_MAX limit   
  *
  */
s32 mmi_fs_raiWrite(mmi_raiId_t ident, mmi_raiSize_t size, const void * data);

/**
  * \fn		const int mmi_fs_raiWriteRawData (vm_raiId_t ident, vm_raiSize_t size, const void * data);
  * \brief	write uncompressed raw data to RAI
  * \note   When __RAI_COMPRESSION_MMI__ is on, this function writes data
  *         to RAI without compression and mmi_fs_raiWrite() writes compssed
  *         data to RAI.
  *         On the other hand, when __RAI_COMPRESSION_MMI__ is not set,
  *         this function is equivalent to mmi_fs_raiWrite(). They both
  *         write data to RAI without compression.
  *         This function is mainly for occupying RAI space in advance. One
  *         example is to write empty SMS to RAI when booting up for the
  *         first time.
  * \param	[in] ident id of the created / modified object
  * \param	[in] size total size of the object
  * \param	[in] data object contents
  * \return	TRUE on success, FALSE if there is not enough space left or
  *         the requested size exceeds the \ref VM_FMS_RAI_SIZE_MAX limit   
  *
  */
s32 mmi_fs_raiWriteRawData(mmi_raiId_t ident, mmi_raiSize_t size, const void * data);

/**
  * \fn		const int mmi_fs_raiDelete (vm_raiId_t ident);
  * \brief	Delete a random access item
  * \note   This function is likely to trigger garbage collection,
  *         therefore its response time may be over one second.
  * \param	[in] ident id of the object to delete
  * \return	TRUE on success, FALSE if the object did not exist   
  *
  */
u32 mmi_fs_raiDelete (mmi_raiId_t ident);
/**
  * \fn		const int mmi_fs_raiRead (vm_raiId_t ident, vm_raiSize_t start, vm_raiSize_t length, void * data);
  * \brief	Read a range of a the given RAI object content. \n
  *         Read operations past the object's end of data will be truncated.
  * \param	[in] ident id of the object to read from
  * \param	[in] start read start offset
  * \param	[in] length number of bytes to read
  * \param	[out] data object data receive buffer
  * \return	the number of bytes read, 0 if no object was found
  *
  */
s32 mmi_fs_raiRead (mmi_raiId_t ident, mmi_raiSize_t start, mmi_raiSize_t length, void * data);
/**
  * \fn		const int mmi_fs_raiStats (vm_raiId_t ident, vm_raiSize_t start, vm_raiSize_t length, void * data);
  * \brief	Read a range of a the given RAI object content. \n
  *         Read operations past the object's end of data will be truncated.
  * \param	[in] ident id of the object to read from
  * \param	[in] start read start offset
  * \param	[in] length number of bytes to read
  * \param	[out] data object data receive buffer
  * \return	the number of bytes read, 0 if no object was found
  *
  */
s32 mmi_fs_raiStats(mmi_raiStats_t* pStats);
/**
  * \fn		const int mmi_fs_raiInfo (vm_raiId_t ident, vm_raiInfo_t * info);
  * \brief	Get informations on a random access item
  * \param	[in] ident id of the object to get info on
  * \param	[out] info returned informations
  * \return	TRUE on success, FALSE if the object does not exist
  *
  */
boolean mmi_fs_raiInfo(u32 ident, mmi_raiInfo_t *info);


/**
  * \fn		mmi_fs_raiCheckFreeSpace
  * \brief	Check RAI free space if enough.
  * \param	[in] CheckSize 
  * \return	TRUE if free space is enough, FALSE if free space is not enough
  *
  */
boolean mmi_fs_raiCheckFreeSpace(s32 CheckSize);

/**
  * @fn		mmi_fs_raiCheckMemoryLow
  * @brief	Check if RAI free space is low.
  * @return	TRUE when the storage is less than a predefined size which is 1024 bytes now, FALSE if not
  *
  */
boolean mmi_fs_raiCheckMemoryLow(void);

/**
  * @fn		mmi_fs_raiGroupDeleteInit
  * @brief	
  * @return	
  *
  */
mmi_raiId_t *mmi_fs_raiGroupDeleteInit( mmi_raiId_t *ident, u32 number );

/**
  * @fn		mmi_fs_raiGroupDelete
  * @brief	
  * @return	
  *
  */
boolean mmi_fs_raiGroupDelete( mmi_raiId_t *ident, u32 number );

/**
  * @fn		mmi_fs_GetDeviceSize
  * @brief	
  * @return	
  *
  */
u32 mmi_fs_GetDeviceSize(void);

#endif//__MAE_UTIL_FS_H__
