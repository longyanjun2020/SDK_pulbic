
#ifndef _HAL_SPINAND_H_
#define _HAL_SPINAND_H_
#include "drv_spinand_common.h"
#include "stdcomp.h"

//-------------------------------------------------------------------------------------------------
//  Macro definition
//-------------------------------------------------------------------------------------------------
#define READ_WORD(_reg)                     (*(volatile unsigned short*)(_reg))
#define WRITE_WORD(_reg, _val)              { (*((volatile unsigned short*)(_reg))) = (unsigned short)(_val); }
#define WRITE_WORD_MASK(_reg, _val, _mask)  { (*((volatile unsigned short*)(_reg))) = ((*((volatile unsigned short*)(_reg))) & ~(_mask)) | ((U16)(_val) & (_mask)); }
#define BDMA_READ(addr)                     READ_WORD(_gtHalFsp.nBDMABaseAddr + (addr<<2))
#define BDMA_WRITE(addr, val)               WRITE_WORD(_gtHalFsp.nBDMABaseAddr + (addr<<2),(val))
#define QSPI_READ(addr)                     READ_WORD(_gtHalFsp.nQspiBaseAddr + (addr<<2))
#define QSPI_WRITE(addr, val)               WRITE_WORD(_gtHalFsp.nQspiBaseAddr + (addr<<2),(val))
#define CLK_READ(addr)                      READ_WORD(_gtHalFsp.nCLK0BaseAddr + (addr<<2))
#define CLK_WRITE(addr, val)                WRITE_WORD(_gtHalFsp.nCLK0BaseAddr + (addr<<2),(val))
#define CLK_WRITE_MASK(addr, val, mask)     WRITE_WORD_MASK(_gtHalFsp.nCLK0BaseAddr + ((addr)<<2), (val), (mask))
#define CHIP_READ(addr)                     READ_WORD(_gtHalFsp.nCHIPBaseAddr + (addr<<2))
#define CHIP_WRITE(addr, val)               WRITE_WORD(_gtHalFsp.nCHIPBaseAddr + (addr<<2),(val))
#define CHIP_WRITE_MASK(addr, val, mask)    WRITE_WORD_MASK(_gtHalFsp.nCHIPBaseAddr + ((addr)<<2), (val), (mask))
#define PM_WRITE_MASK(addr, val, mask)      WRITE_WORD_MASK(_gtHalFsp.nPMBaseAddr+ ((addr)<<2), (val), (mask))
#define PM_READ(addr)                       READ_WORD(_gtHalFsp.nPMBaseAddr + (addr<<2))
#define PM_WRITE(addr, val)                 WRITE_WORD(_gtHalFsp.nPMBaseAddr + (addr<<2),(val))
#define ISP_READ(addr)                      READ_WORD(_gtHalFsp.nISPBaseAddr + (addr<<2))
//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
extern SpinandInfo_t gtSpinandInfo;
extern u8 _u8SPINANDDbgLevel;

u8 HalSpinandReadStatusRegister(u8 *u8Status, u8 u8Addr);
u8 HalSpinandWriteStatusRegister(u8 *u8Status, u8 u8Addr);
u32  HalSpinandRead(u32 u32Addr, u32 u32DataSize, u8 *pu8Data);
u32  HalSpinandWrite(u32 u32_PageIdx, u8 *u8Data, u8 *pu8_SpareBuf);
u32  HalSpinandReadID(u32 u32DataSize, u8 *pu8Data);
u32  HalSpinandRFC(u32 u32Addr, u8 *pu8Data);
void HalSpinandConfig(u32 u32PMRegBaseAddr, u32 u32NonPMRegBaseAddr);
u32  HalSpinandBlockErase(u32 u32_PageIdx);
u32  HalSpinandInit(void);
u32  HalSpinandWriteProtect(bool bEnable);
bool HalSpinandPlaneHandler(u32 u32Addr);
u32  HalSpinandSetMode(SpinandMode_e eMode);
bool HalSpinandSetCKG(u8 u8CkgSpi);
void HalSpinandCSConfig(void);
bool HalSpinandIsActive(void);
u8 HalQspiForDebug(void);


//-------------------------------------------------------------------------------------------------
//  System Data Type
//-------------------------------------------------------------------------------------------------
/// data type unsigned char, data length 1 byte
#define MS_U8       unsigned char                                            // 1 byte
/// data type unsigned short, data length 2 byte
#define MS_U16      unsigned short                                           // 2 bytes
/// data type unsigned int, data length 4 byte
#define MS_U32      unsigned long                                            // 4 bytes
/// data type unsigned int, data length 8 byte
#define MS_U64      unsigned long long                                       // 8 bytes
/// data type signed char, data length 1 byte
#define MS_S8       signed char                                              // 1 byte
/// data type signed short, data length 2 byte
#define MS_S16      signed short                                             // 2 bytes
/// data type signed int, data length 4 byte
#define MS_S32      signed long                                              // 4 bytes
/// data type signed int, data length 8 byte
#define MS_S64      signed long long                                         // 8 bytes
/// data type float, data length 4 byte
#define MS_FLOAT    float                                                    // 4 bytes
/// data type null pointer
#ifdef NULL
#undef NULL
#endif
#define NULL                        0

#define MS_BOOL     unsigned char

/// data type hardware physical address
#define MS_PHYADDR unsigned long                                    // 32bit physical address



#endif // _HAL_SPINAND_H_
