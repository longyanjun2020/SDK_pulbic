#ifndef _MMPF_SF_H_
#define _MMPF_SF_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#if defined(__RTK_OS__)
#include "cpu_mem_map_mercury5.h"
#include "drv_flash_lowl_ht_pub.h"
#endif
//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define SF_BUS_REENTRY_PROTECT      (1)	//< 0: disable SF BUS reentry protect; 1: enable SF BUS reentry protect>

#define SPI_NORFLASH_MAX_NUM        0x20 // Maximum member numbers of array m_pSpiNORProfile[SPINORFLASHMaxNUM]    
#define ERR_CHECK_RETURN(bERR)      if (bERR) {return bERR;}
#define SIF_DBG_LEVEL               (0) 

/* SF Command */
#define WRITE_STATUS1               0x01 // For write status register1
#define PAGE_PROGRAM                0x02
#define READ_DATA                   0x03
#define WRITE_DISABLE               0x04
#define EXIT_OTP_MODE               0x04
#define READ_STATUS1                0x05 // For read status register1
#define WRITE_ENABLE                0x06
#define FAST_READ_DATA              0x0B
#define BURST_READ_WITH_WRAP        0x0C
#define WRITE_STATUS3               0x11 // For write status register3
#define READ_STATUS3                0x15 // For read status register3
#define SECTOR_ERASE                0x20
#define CLEAR_SR                    0x30
#define WRITE_STATUS2               0x31 // For write status register2
#define QUAD_PAGE_PROGRAM           0x32
#define READ_STATUS2                0x35 // For read status register2
#define ENABLE_QPI                  0x38
#define ENTER_OTP_MODE              0x3A
#define DUAL_FAST_READ_DATA         0x3B // Need Removed
#define FAST_READ_DUAL_OUT          0x3B
#define PROG_SECURITY_REG           0x42
#define ERASE_SECURITY_REGISTER     0x44
#define READ_SECURITY_REG           0x48
#define READ_UNIQUE_ID              0x4B
#define VOLATILE_SR_WRITE_ENABLE    0x50
#define BLOCK_ERASE                 0x52
#define CHIP_ERASE                  0x60
#define ENABLE_RESET_COMMAND        0x66
#define FAST_READ_QUAD_OUT          0x6B
#define QUAD_FAST_READ_DATA         0x6B // Need Removed
#define EBSY                        0x70
#define ERASE_PROGRAM_SUSPEND       0x75
#define SET_BURST_WITH_WRAP         0x77
#define ERASE_PROGRAM_RESUME        0x7A
#define DBSY                        0x80
#define RESET_COMMAND               0x99
#define READ_DEVICE_ID              0x9F
#define RELEASE_DEEP_POWER_DOWN     0xAB
#define ADDR_AUTO_INC_WRITE         0xAD
#define EN4B                        0xB7
#define DEEP_POWER_DOWN             0xB9
#define FAST_READ_DUAL_IO           0xBB
#define SET_READ_PARAMETERS         0xC0
#define OCTAL_WORD_READ_QUAD_IO     0xE3
#define WORD_READ_QUAD_IO           0xE7
#define EX4B                        0xE9
#define FAST_READ_QUAD_IO           0xEB
#define DISABLE_QPI                 0xFF

/* SF Device ID */
#define EON_EN25F10                 0x1C3111
#define EON_EN25F20                 0x1C3112
#define EON_EN25F40                 0x1C3113
#define EON_EN25F80                 0x1C3114
#define EON_EN25Q16A                0x1C3015
#define EON_EN25Q32A                0x1C3016
#define EON_EN25QH128A              0x1C7018

#define WINBOND_25X10               0xEF3011
#define WINBOND_25X20               0xEF3012
#define WINBOND_25X40               0xEF3013
#define WINBOND_25X80               0xEF3014
#define WINBOND_25Q80               0xEF4014
#define WINBOND_25Q16               0xEF4015
#define WINBOND_25Q32               0xEF4016
#define WINBOND_25Q64               0xEF4017
#define WINBOND_25Q128              0xEF4018
#define WINBOND_25Q32DW             0xEF6016
#define WINBOND_25Q256FV            0xEF6019

#define MXIC_25L512                 0xC22010
#define MXIC_25L1005                0xC22011
#define MXIC_25L2005                0xC22012
#define MXIC_25L4005                0xC22013
#define MXIC_25L8005                0xC22014
//#define MXIC_25L3206              0xC22016        // CarDV, not suppoprt, same ID as KH25L3233F, but block size is 64KB.
#define KH25L3233F                  0xC22016
#define MXIC_25L6406E               0xC22017
#define MXIC_25L12835F              0xC22018

#define GD_25Q32B                   0xC84016
#define GD_25Q64B                   0xC84017
#define GD_25Q128B                  0xC84018

#define SST_25VF080B                0xBF258E

#define ESMT_25L16                  0x8C2015
#define ESMT_25L16PA                0x8C2115
#define ESMT_64L                    0x8C4117

// Spansion Flash
#define S25FL004A                   0x00010212
#define S25FL016A                   0x00010214
#define S25FL032A                   0x00010215
#define S25FL064A                   0x00010216  /* Supposed support */
#define S25FL128P                   0x00012018  /*only S25FL128P0XMFI001, Uniform 64KB secotr*/
                                                /*not support S25FL128P0XMFI011, Uniform 256KB secotr*/
                                                /*because #define SPI_BLOCK_SIZE 65536 */

/* Status Register1 (BitMap) */
#define WRITE_IN_PROGRESS           0x01 // Read Only
#define WRITE_ENABLE_LATCH          0x02 // Read Only
#define BLOCK_PROTECT_BITS          0x1C
#define TOP_BOTTOM_PROTECT_BIT      0x20
#define SECT_BLOCK_PROTECT_BIT      0x40
#define STATUS_REGISTER_PROTECT0    0x80

/* Status Register2 (BitMap) */
#define STATUS_REGISTER_PROTECT1    0x01
#define QUAD_ENABLE_BIT             0x02 // Enable this bit before ENABLE_QPI command
#define SECURITY_REGISTER_LOCK_BITS 0x3C // OTP (One Time Programe) bits
#define COMPLEMENT_PROTECT_BIT      0x40
#define SUSPEND_STAUTS_BIT          0x80 // Read Only

// SF Security Register
#define P_FAIL                      1<<5
#define E_FAIL                      1<<6

//FMS CMD Definition
#define MMPF_FMS_CMD_GET_DEVICE_SIZE        3 /* Returns the size of the device       */
#define MMPF_FMS_CMD_GET_DEVICE_ID          6 /* Returns the manufacturer+device code */

//==============================================================================
//
//                              ENUMERATIONS
//
//==============================================================================

typedef enum _MMPF_SIF_SR_INDEX
{
    MMPF_SIF_SR_INDEX1 = 1,
    MMPF_SIF_SR_INDEX2,
    MMPF_SIF_SR_INDEX3,
    MMPF_SIF_SR_NUM
} MMPF_SIF_SR_INDEX;

typedef  MMP_ERR (*pFuncProtection)(MMP_BOOL bEnable);

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMPF_SIF_INFO {
    MMP_ULONG ulDevId;          // Device ID
    MMP_ULONG ulSFSectorSize;   // Size per sector in unit of byte
    MMP_ULONG ulSFBlockSize;    // Size per Block in unit of byte
    MMP_ULONG ulSFTotalSize;    // Total size in unit of byte
} MMPF_SIF_INFO;

typedef  struct _SPI_NOR_PROFILE {
    MMP_ULONG   DeviceID;               //Device ID , check spec for it	
    MMP_ULONG   TotalSize;              //size of Bytes for total module	
    MMP_ULONG   SIFCLKDividor;          //parameter to create <ulSifClkDiv> Example: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor;
    MMP_ULONG   SectorSIZE;             //size of Bytes for each Sectpr 
    MMP_ULONG   BlockSIZE;              //size of Bytes for each Block	

    MMP_UBYTE   ReadDualSPI;            //Capability to support Dual SPI when reading,check SPEC <could not active if Quad-SPI read is active>
    MMP_UBYTE   EnableVolatileWrite;    //cmd<50H>,speedup the write Volatile SR process
    MMP_UBYTE   FourByteAddress;        // Enable 4 bytes address type, (1)4 bytes , (0)3 bytes
    MMP_UBYTE   SupportAAIWrite;        //Capaility to support AAI-Write <SST>
    MMP_UBYTE   SupportClearSR;         //Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    MMP_UBYTE   ADPMode;                //Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP	
    MMP_UBYTE   SR4ByteAdd;             //Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    MMP_UBYTE   SRBit4ByteAdd;          //Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    MMP_UBYTE   SR4WriteProt[3];        //Refer spec. to set 128K protect
    MMP_UBYTE   BP4WpStsBits[3];        //WP Relative Bits
        
    /* Command for Read/Write/Erase */
    MMP_UBYTE   ReadDataCMD3Byte;       //Command for read data <3 Byte Address>
    MMP_UBYTE   FastReadDataCMD3Byte;   //Command for fast read data <3 Byte Address>
    MMP_UBYTE   DualReadDataCMD3Byte;   //Command for Dual fast read data <3 Byte Address>
    MMP_UBYTE   WriteDataCMD3Byte;      //Command for write data <3 Byte Address>
    MMP_UBYTE   ReadDataCMD4Byte;       //Command for read data <4 Byte Address>
    MMP_UBYTE   FastReadDataCMD4Byte;   //Command for fast read data <4 Byte Address>
    MMP_UBYTE   DualReadDataCMD4Byte;   //Command for Dual fast read data <4 Byte Address>
    MMP_UBYTE   WriteDataCMD4Byte;      //Command for write data <4 Byte Address>
    MMP_UBYTE   EraseSectorCMD3Byte;    //Command for Erase Sector <3 Byte Address>
    MMP_UBYTE   EraseSectorCMD4Byte;    //Command for Erase Sector <4 Byte Address>
    MMP_UBYTE   RdScurRegCMD1Byte;      //Command for Read Security register <1 Byte Address>    
    pFuncProtection	pFuncProtect;       //Customize protection function
} SPI_NOR_PROFILE;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_SF_Register(MMP_UBYTE ubSFIndex , SPI_NOR_PROFILE *pArrayAdd);
MMP_ERR MMPF_SF_ClearCommand(void);
MMP_ERR MMPF_SF_ResetDev(void);
MMP_ERR MMPF_SF_ENEX4B(MMP_UBYTE ADPStatus);
MMP_ERR MMPF_SF_CheckCmdSent(void);
MMP_ERR MMPF_SF_ReadStatus(MMP_UBYTE ubSRIdx, MMP_UBYTE *ubStatus);
MMP_ERR MMPF_SF_WriteStatus(MMP_UBYTE ubSRIdx, MMP_UBYTE ubStatus);
MMP_ERR MMPF_SF_WriteStatus2Byte(MMP_UBYTE ubSRIdx, MMP_USHORT wData);
MMP_ERR MMPF_SF_EnableWrite(void);
MMP_ERR MMPF_SF_EnableWriteSR(void);
MMP_ERR MMPF_SF_DisableWrite(void);
MMP_ERR MMPF_SF_SetIdBufAddr(MMP_ULONG ulAddr);
MMP_ERR MMPF_SF_SetTmpAddr(MMP_ULONG ulStartAddr);
MMP_ERR MMPF_SF_GetTmpAddr(MMP_ULONG *ulStartAddr);
MMP_ERR MMPF_SF_InitialInterface(void);
MMP_ERR MMPF_SF_Reset(void);
MMPF_SIF_INFO *MMPF_SF_GetSFInfo(void);
MMP_ERR MMPF_SF_ReadDevId(MMP_ULONG *ulDmaAddr);
MMP_ERR MMPF_SF_ReadData(MMP_ULONG ulSFAddr, MMP_ULONG ulDmaAddr, MMP_ULONG ulByteCount);
MMP_ERR MMPF_SF_FastReadData(MMP_ULONG ulSFAddr, MMP_ULONG ulDmaAddr, MMP_ULONG ulByteCount);
MMP_ERR MMPF_SF_WriteData(MMP_ULONG ulSFAddr, MMP_ULONG ulDmaAddr, MMP_ULONG ulByteCount);
MMP_ERR MMPF_SF_EraseSector(MMP_ULONG ulSFAddr);
MMP_ERR MMPF_SF_EraseBlock(MMP_ULONG ulSFAddr);
MMP_ERR MMPF_SF_ResetClock(void);
MMP_ERR MMPF_SF_EraseChip(void);
MMP_ERR MMPF_SF_AaiWriteData(MMP_ULONG ulSFAddr, MMP_ULONG ulDmaAddr, MMP_ULONG ulByteCount);
MMP_ERR MMPF_SF_EBSY(void);
MMP_ERR MMPF_SF_DBSY(void);
MMP_ERR MMPF_SF_ReleasePowerDown(void);
MMP_ERR MMPF_SF_PowerDown(void);
MMP_ERR MMPF_SF_ReadUniqueId(MMP_UBYTE *ulDmaAddr);
MMP_ERR MMPF_SF_EnableCrcCheck(MMP_BOOL bEnable);
MMP_USHORT MMPF_SF_GetCRC(void);
MMP_ERR MMPF_SF_BusAcquire(MMP_ULONG SIFSEMID, MMP_ULONG ulTimeout);
MMP_ERR MMPF_SF_BusRelease(MMP_ULONG SIFSEMID);

#endif //_MMPF_SF_H_
