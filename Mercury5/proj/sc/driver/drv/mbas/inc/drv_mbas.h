#ifndef __DRV_MBAS_H__
#define __DRV_MBAS_H__

#include <hal_mbas.h>

extern u32 text_lma_start;
extern u32 text_lma_end;
extern u32 rodata_lma_start;
extern u32 rodata_lma_end;

#define MMP_MBAS0_BASE  0x80000000
#define TEXT_LMA_START      ((u8 *)&text_lma_start)
#define TEXT_LMA_END        ((u8 *)&text_lma_end)
#define RODATA_LMA_START    ((u8 *)&rodata_lma_start)
#define RODATA_LMA_END      ((u8 *)&rodata_lma_end)

typedef enum MBAS_ACTION_E
{
     GET = 0x00
    ,SET = 0x01
} MBAS_ACTION_ET;

typedef enum MBAS_TYPE_E
{
    TYPE_READ = 0x00,
    TYPE_WRITE = 0x01
} MBAS_TYPE_ET;

typedef enum MBAS_PERMISSION_E
{
     PERM_NONE = 0x00
    ,PERM_RD = 0x01
    ,PERM_RW = 0x02
    ,PERM_GEN_OFF = 0x03
    ,PERM_MAX = 0x04
} MBAS_PERMISSION_ET;

typedef struct MBAS_LOG_ITEM_S
{
	MBAS_TYPE_ET type;
	u32 addr;
} MBAS_LOG_ITEM_ST;

//#define MBAS_TRIGGER_ASSERT
#define MBAS_LOG_ITEM_MAX	10

typedef struct MBAS_LOG_S
{
	u32 hit_count;
	u32 cur_idx;
	MBAS_LOG_ITEM_ST array[MBAS_LOG_ITEM_MAX];
} MBAS_LOG_ST;

#endif 	    /* !__DRV_ETMI_H__ */

