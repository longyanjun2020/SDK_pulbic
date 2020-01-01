/******************************************************************************/
/* File    : drv_hw_config.h                                                  */
/*----------------------------------------------------------------------------*/
/* Scope   : HW configuration header file                                     */
/*                                                                            */
/******************************************************************************/
#ifndef __DRV_HW_CONFIG_H__
#define __DRV_HW_CONFIG_H__

// Please include your customized header file
#include "hal_hw_config.h"

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define HW_CONFIG_TLV_HEADER_SIZE		0x04 	// Type:two byte, Length:two byte
#define HW_CONFIG_TLV_BUF_SIZE			0x400	// Reserved 512bytes

//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
/* HW configuration enumeration */
typedef enum {
    HW_CONFIG_MIU			= 0x11,	/* settings for Memory Interface Unit		*/
	HW_CONFIG_AUTOREFRESH	= 0x12,	/* auto-refresh MIU settings(sleep->wake-up)*/
	HW_CONFIG_SELFREFRESH	= 0x13,	/* self-refresh MIU settings(wake-up->sleep)*/
	HW_CONFIG_MEMARBITER	= 0x14,	/* memory arbiter settings					*/
	HW_CONFIG_DRAMCLKUP		= 0x15,	/* DRAM clock rate from 10MHz to 80MHz		*/
	HW_CONFIG_DRAMCLKDOWN	= 0x16,	/* DRAM clock rate from 80MHz to 10MHz		*/	
	HW_CONFIG_MMPPREBOOT	= 0x17,	/* settings in MMP pre-boot					*/
	HW_CONFIG_DBBPREBOOT	= 0x18,	/* settings in DBB pre-boot					*/
	HW_CONFIG_BOOTOPTION	= 0x19, /* Vcore/LDO/ramp/MMP_sleep settings		*/
	HW_CONFIG_REPLAYMCU		= 0x1A,	/* MCU replay functions						*/	
	HW_CONFIG_REPLAYDSP		= 0x1B	/* DSP replay functions						*/		
	// GAP
} hwType_e;


typedef enum {
	OFFSET_DELAYMS	= 0xFFFF5555,
	OFFSET_DELAYUS	= 0xFFFF6666,	
	OFFSET_POLLSET	= 0xFFFF7777,
	OFFSET_POLLCLR	= 0xFFFF8888,	
} offset_e;

typedef struct HW_CONFIG_Value_s {		/* 8bytes structure for Memory */
	unsigned int	offset;			
	unsigned int	value;			
} HW_CONFIG_Value_t;

typedef struct HW_CONFIG_s {
	unsigned short	type;				/* 2bytes: HW configuration Type	*/
	unsigned short	length;				/* 2bytes: number of HW_CONFIG_t	*/
	HW_CONFIG_Value_t	pvalueMEM[0];	/* value type(memmory, continuously)*/
} HW_CONFIG_t;

__attribute__((SECTION_NAME, optimize("no-jump-tables"), long_call, noinline)) void DrvHwConfigInit( unsigned int u32BaseAddr);
__attribute__((SECTION_NAME, optimize("no-jump-tables"), long_call, noinline)) unsigned char DrvHwConfigExec( hwType_e hwsType);


#endif /* __HW_CONFIG_H__ */
