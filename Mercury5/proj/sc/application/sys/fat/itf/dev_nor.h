/****************************************************************************/
/*  File    : dev_nor.h                                              		*/
/*--------------------------------------------------------------------------*/
/* PURPOSE:																	*/
/* This file contains the high level NOR routines							*/
/*																			*/
/* NOTES:																	*/
/*																			*/
/* - The functions are written to handle a 2-card NOR stack					*/
/* - Only MMC cards with block size = 512 bytes are accepted 				*/
/*                                                                          */
/****************************************************************************/

#ifndef __DEV_NOR_H__
#define __DEV_NOR_H__

/*_____ I N C L U D E S ____________________________________________________*/
#include "vm_types.ht"
#include "dev_storage.h"

#include "sys_nor.h"

/*_____ M A C R O S ________________________________________________________*/



#define NOR_PAGE_MASK       ((u8)0x01)

/* Card Size based on 512 bytes block size */
#define NOR_SIZE_512KB        ((u32)7872 - 1)
#define NOR_SIZE_1MB        ((u32)15680 - 1)

#define NOR_512KB             ((u8)0)
#define NOR_1MB             ((u8)1)


/*_____ D E C L A R A T I O N ______________________________________________*/

/* System */
s32 	dev_nor_read_status (u16 *status);
s32 	dev_nor_init(void);
Unit_Physical_Format_t *dev_nor_format (void);
bool 	dev_nor_is_present(void);


#endif /* __DEV_NOR_H__ */

