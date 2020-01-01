/****************************************************************************/
/*  File    : sys_nor.h                                              		*/
/*--------------------------------------------------------------------------*/
/* PURPOSE:																	*/
/* This file contains the NOR FAT sector read/write function				*/
/*																			*/
/* NOTES:																	*/
/*																			*/
/*                                                                          */
/****************************************************************************/

#ifndef __SYS_NOR_H__
#define __SYS_NOR_H__

s32 	dev_nor_read_sectors (u32 sector_num, u32 nb_sectors, u8* buffer);
s32		dev_nor_write_sectors (u32 sector_num, u32 nb_sectors, u8* buffer);

#endif /* __SYS_NOR_H__ */
