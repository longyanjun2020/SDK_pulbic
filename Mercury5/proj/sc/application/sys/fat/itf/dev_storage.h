/****************************************************************************/
/*  File    : dev_storage.h                                              	*/
/*--------------------------------------------------------------------------*/
/*  Scope   : Defines constants and types that storage librairies should 	*/
/*            respect                                                       */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifndef __DEV_STORAGE_H__
#define __DEV_STORAGE_H__

#include "vm_types.ht"

/*_____ I N C L U D E S ____________________________________________________*/

#define STORAGE_NO_ERROR				1
#define STORAGE_READ_ERROR				-1	// impossible to read
#define STORAGE_RESP_ERROR				-2	// no response from storage unit
#define STORAGE_BUSY_ERROR				-3	// storage unit busy, try later
#define STORAGE_BLOCK_SIZE_ERROR		-4	// this storage unit has a non supported block size
#define STORAGE_WRITE_ERROR				-5	// impossible to write
#define STORAGE_INVALID_BLOCK_ERROR		-6	// the block is invalid, so mark it as 0XFFF7 in the FAT, 
											// and copy sector in another block
#define STORAGE_INVALID_SECTOR_ERROR	-7
#define STORAGE_BAD_PARAM_ERROR			-8	// the sector given in parameter is not in the range
#define STORAGE_NEVER_USED_SECTOR_ERROR			-9	// the sector given in parameter can not be read because never written
#define STORAGE_NOT_RECOGNIZED_ERROR	-10	// the storage unit is not recognized
#define STORAGE_NOT_PRESENT_ERROR		-11	// the storage unit is not present in the handset
#define STORAGE_NOT_INITIALIZED_ERROR	-12	// the storage unit has not been initialized
#define STORAGE_INTERFACE_ERROR			-13	// the bus or io are invalid
#define STORAGE_TOO_MANY_PARTITIONS_ERROR			-14	// it is impossible to create more than 4 partitions per storage unit
#define STORAGE_MEMORY_ERROR						-15	// rtk memory error
#define STORAGE_SIGNATURE_ERROR						-16	// signature is invalid

#define SECTOR_SIZE			512
#define MBR_ADDRESS       ((u32)0)       /* Master Boot Record address   */

#define BOOTABLE_DEVICE  ((u8)0x80)      /* the active partition state   */
#define NON_BOOTABLE_DEVICE  ((u8)0x00)      /* the active partition state   */

#define NO_FAT             		((u8)0xFF)      /* No FAT in the partition                   */
#define FAT12             		((u8)0x01)      /* FAT12 type                   */
#define FAT16_INF32M      		((u8)0x04)      /* FAT16 type < 32 Mbytes       */
#define FAT16_SUP32M      		((u8)0x06)      /* FAT16 type > 32 Mbytes       */
#define FAT32             		((u8)0x0B)      /* FAT32 type not supported     */

#define BR_SIGNATURE      		((u16)0xAA55)  /* boot record signature        */

#define NB_PARTITION_PER_UNIT	4
#define LOW(U16)   ((u8)U16)
#define HIGH(U16)  ((u8)(U16>>8))

typedef enum {
	NAND_STORAGE = 0,
	MMC_STORAGE
	 
}  Storage_e;

#define NB_STORAGES 1

/* Storage Unit Format Structure */
typedef struct  
{
	u16 	nb_cylinder; // there are nb_head tracks per cylinder
  	u8   nb_head;
	u8   	nb_sector;	// nb sectors per tracks
	u8   	nb_sectors_per_cluster;	// nb sectors per cluster, for media with fixed cluster size
} Unit_Physical_Format_t;

/* Partition Format Structure */
typedef struct  
{
	u8		boot_descriptor;
	u16 	first_cylinder; 
	u8   	first_head;
	u8   	first_sector;	
	u16 	last_cylinder; 
	u8   	last_head;
	u8   	last_sector;	// nb sectors per tracks
	u32		LBA_first_sector;
	u32 	LBA_nb_sectors;
	u8 		file_system_descriptor;
} Partition_t;

/* Storage Unit Format Structure */
typedef struct  
{
	s8 *name;
	s32 status;
	u8 nb_volumes;	// number of partitions in the Storage Unit
	s32		(*mark_block_free) (u16 /*block_num*/);
	s32		(*read_sectors)(u32 /*first_sector*/, u32 /*nb_sectors*/, u8* /*buffer*/);
	s32		(*write_sectors)(u32 /*first_sector*/, u32 /*nb_sectors*/, u8* /*buffer*/);
	Unit_Physical_Format_t* (*storage_format)(void) ;
	bool (*is_present)(void);
	Partition_t	partitions[NB_PARTITION_PER_UNIT];
	u8 first_existing_partition;
} Storage_Unit_t;


u32 dev_chs_to_lba(u16 C, u8 H, u8 S, u8 NumH, u8 NumS);
u16 dev_lba_to_cylinder(u32 LBA, u8 NumH, u8 NumS);
u8 dev_lba_to_head(u32 LBA, u8 NumH, u8 NumS);
u8 dev_lba_to_sector(u32 LBA, u8 NumS);
s32 dev_storage_list_units(u8 *nb_units, Storage_Unit_t** units);
s32 dev_storage_create_partition(Storage_Unit_t *storage, Partition_t *partition, u8 *partition_index);
s32 dev_storage_delete_partition(Storage_Unit_t *storage, u8 partition_index);
 s32 dev_storage_mask_partition(Storage_Unit_t *storage, u8 partition_index, u8 fat_descriptor);

#endif  /* __DEV_STORAGE_H__ */

