#ifndef __MMI_EMU_BAD_LIST_H__
#define __MMI_EMU_BAD_LIST_H__

/**
 * @file    mmi_emu_bad_list.h
 * @brief   The document describes the bad ROM list
 */
#include "mmi_mae_common_def.h"

#ifdef __EMU_BAD_ROM_C__
/**
 * Bad EMU rom list
 */

typedef struct
{
	u32     nHashCode;
	char    *name;
} EMU_BAD_ROM_t;

static const EMU_BAD_ROM_t BadROMImages[] =
{
    {0x51eef79a, "Ultimate League Soccer (E)"},
    {0x08b092bd, "Super Mario Bros."},
    {0x89fdac93, "F1 racing"},
    {0x90faa618, "Sky boy"}
};

#else
extern const EMU_BAD_ROM_t BadROMImages[];
#endif //__EMU_BAD_ROM_C__

#endif //__MMI_EMU_BAD_LIST_H__
