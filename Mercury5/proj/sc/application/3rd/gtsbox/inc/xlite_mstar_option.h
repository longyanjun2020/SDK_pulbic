#ifndef __XLITE_MSTAR_OPTION_H__
#define __XLITE_MSTAR_OPTION_H__

typedef enum
{
	NAND_FLASH,
	NOR_FLASH
} xlite_flash;

//是否使用debug模式，输出log
//#define XLITE_DEBUG

//MSTAR FLASH TYPE
#define xlite_mstar_flash_version			NOR_FLASH      //NAND_FLASH    NOR_FLASH
#endif
