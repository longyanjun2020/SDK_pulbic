#ifndef __DRV_PM_CHIP__
#define __DRV_PM_CHIP__

#define RIU_BASE_ADDR           0x1F000000

#define REG_ADDR_BASE_PM_CHIP     GET_REG8_ADDR( RIU_BASE_ADDR, 0x1E00 )

#define GET_REG8_ADDR(x, y)  	(x+(y)*2-((y)&1))
#define GET_REG16_ADDR(x, y)  	(x+(y)*4)

#define CHIP_ID_NONE   (0x0000)
#define CHIP_ID_M5     (0x00D9)
#define CHIP_ID_M5U    (0x00EE)

#ifndef U8
#define U8   unsigned char
#endif
#ifndef U16
#define U16  unsigned short
#endif
#ifndef U32
#define U32  unsigned long
#endif

#define DIP_ROTATE_ENHANCE (0)

void DrvPM_ReadChipInfo(void);
U16 DrvPM_ForceChipID(U16 ForceChipID);
U16 DrvPM_GetChipID(void);
U8 DrvPM_GetChipVersion(void);
U8 DrvPM_GetChipRevision(void);

#endif
