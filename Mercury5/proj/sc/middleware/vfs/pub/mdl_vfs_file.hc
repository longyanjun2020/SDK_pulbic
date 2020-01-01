/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 2001
*/
/****************************************************************************/
/*  File    : mdl_vfs_file.hc                                              		*/
/*--------------------------------------------------------------------------*/
/*  Scope   : file access constants						           			*/
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

#ifndef __MDL_VFS_FILE_HC__
#define __MDL_VFS_FILE_HC__

/*_____ I N C L U D E S ____________________________________________________*/

#include "vm_types.ht" 

/*_____ M A C R O S ________________________________________________________*/
#define FILE_FREE (u32)0xFFFFFFFF

// maximum number of files that could be handled simultaneously
#define NB_FILES_MAX 	VFS_NB_FILES_MAX	
#define	POS_ERR	(-(fpos_t)1)


#endif  /* __MDL_VFS_FILE_HC__ */

