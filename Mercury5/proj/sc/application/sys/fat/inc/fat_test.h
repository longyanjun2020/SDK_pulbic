/****************************************************************************/
/*  File    : fat_test.h                                                  	*/
/*--------------------------------------------------------------------------*/
/*  Scope   : FAT feature test						                    	*/
/*                                                                          */
/*  Contents: 				                                    			*/
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/* 24.01.03 | NRO    |      |  new                                          */
/*----------+--------+------+-----------------------------------------------*/
/*----------+--------+------+-----------------------------------------------*/

#ifndef __FAT_TEST_H__
#define __FAT_TEST_H__

#include "vm_types.ht"

void fat_test_dir(u16 first);
void fat_test_mkdir(u8 *fileName);
void fat_test_new_file(u8 *fileName);
void fat_test_fread(u8 *fileName, u8 *buffer_out, u32 size);
void fat_test_list_units(void);
s32 fat_test_menu(u8 test);

#endif // __FAT_TEST_H__


