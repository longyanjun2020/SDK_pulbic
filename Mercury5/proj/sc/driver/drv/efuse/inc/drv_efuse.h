#ifndef __DRV_EFUSE__
#define __DRV_EFUSE__

#define RIU_BASE_ADDR           0x1F000000

#define REG_ADDR_BASE_EFUSE     GET_REG8_ADDR( RIU_BASE_ADDR, 0x2000 )

#define GET_REG8_ADDR(x, y)  	(x+(y)*2-((y)&1))
#define GET_REG16_ADDR(x, y)  	(x+(y)*4)

#ifndef NULL
#define NULL	((void*)0)
#endif
#ifndef BIT0
#define BIT0	(1<<0)
#endif
#ifndef BIT1
#define BIT1	(1<<1)
#endif
#ifndef BIT2
#define BIT2	(1<<2)
#endif
#ifndef BIT3
#define BIT3	(1<<3)
#endif
#ifndef BIT4
#define BIT4	(1<<4)
#endif
#ifndef BIT5
#define BIT5	(1<<5)
#endif
#ifndef BIT6
#define BIT6	(1<<6)
#endif
#ifndef BIT7
#define BIT7	(1<<7)
#endif
#ifndef BIT8
#define BIT8	(1<<8)
#endif
#ifndef BIT9
#define BIT9	(1<<9)
#endif
#ifndef BIT10
#define BIT10	(1<<10)
#endif
#ifndef BIT11
#define BIT11	(1<<11)
#endif
#ifndef BIT12
#define BIT12	(1<<12)
#endif
#ifndef BIT13
#define BIT13	(1<<13)
#endif
#ifndef BIT14
#define BIT14	(1<<14)
#endif
#ifndef BIT15
#define BIT15	(1<<15)
#endif

#ifndef U8
#define U8   unsigned char
#endif
#ifndef U16
#define U16  unsigned short
#endif
#ifndef U32
#define U32  unsigned long
#endif

#define GGININDER (12)

U32 DrvEfuse_ReadEFUSE(U32 u32Offset);
void DrvEfuse_Check(void);
U8 DrvEfuse_Func1(void);
U8 DrvEfuse_Func2(void);
U8 DrvEfuse_Func3(void);
U8 DrvEfuse_Func4(void);
U8 DrvEfuse_Func5(void);
void DrvEfuse_Check_GG1(U32 u32GG);
void DrvEfuse_Check_GG2(U32 u32GG);
void DrvEfuse_ReadUniqueID6B( U8* pbyUniqueID );  //Note: pbyUniqueID is a 6-bytes array

#endif
