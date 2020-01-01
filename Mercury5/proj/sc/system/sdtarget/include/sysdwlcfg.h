/******************************************************************************/
/* File    : sysdwlcfg.h                                                      */
/*----------------------------------------------------------------------------*/
/* Scope   : System downloader header file                                    */
/*                                                                            */
/******************************************************************************/
#ifndef __SYSDWLCFG_H__
#define __SYSDWLCFG_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define INTERFRAME_TIMEOUT_PERIOD   5000    /* in milisecond */
#define INIT_PACKETSIZE             1

#define SELECT_PATH_USB             0x00
#define SELECT_PATH_CONSOLE         0x01
#define SELECT_PATH_SD              0x02
#define DWLD_PATH_NUM               0x03

#define DWLD_RAMCODE_START          ((u32)&Image$$IRAM_EXEC$$ZI$$Base)
#define DWLD_RAMCODE_SIZE           ((u32)&Image$$IRAM_EXEC$$ZI$$Length)

#define DWLD_CTRL_BUF_LEN           8
#define DWLD_DEFAULT_PACKETSIZE     0x80

#define DWLD_UART_FRAME_SIZE        0x20


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
typedef struct DwlderChann_s
{
    void    (*fnInit)(void);
    void    (*fnCfg)(u8 *buf);
    s32     (*fnTx)(u8 *buf, u32 len);
    s32     (*fnRx)(u8 *buf, u32 len);
    void    (*fnFlush)(void);
    void    (*fnCleanRx)(void);
} DwlderChann_t;

typedef struct DwlderPath_s
{
    DwlderChann_t const *ptrChann;
    u16     selectPath  : 2;
    u16     reserved1   : 6;
    u16     busyBit     : 1;
    u16     doneBit     : 1;
    u16     reserved2   : 6;
} DwlderPath_t;

typedef struct DwlderGlob_s
{
    u32     u32_DataFrameCount;                     /* use to count element bytes of the receiving frame */
    u32     u32_BinaryDataLoadPacketSizeFrame;      /* use to specify element bytes count of data-load frame */
    u8      au8_CtrlFrameBuffer[DWLD_CTRL_BUF_LEN]; /* use to store element bytes of control frames */
    u8      *pu8_BinaryStoragePointer;              /* use to specify the location of data downloaded in internal RAM */
    u8      *pu8_DataStoragePointer;                /* use to specify the storage location of current receiving frame */
    u8      *pu8_currDataPointer;                   /* use to specify the current location where to put element bytes of the receiving frame */
    bool    b_BreakResetConf;
    bool    (*pf_ByteFrameTreatementProc)(struct DwlderGlob_s*, u32);   /* use to define the proc which going to treat received bytes */
    bool    (*pf_ByteFrameTreatementSubProc)(struct DwlderGlob_s*);     /* use to define the sub-proc which going to treat the header */
    bool    (*pf_FramePerforming)(struct DwlderGlob_s*);    /* use to define the proc which going to treat the received frame */
    DwlderPath_t    *pDwldPath;                             /* pointer to download path struct */
} DwlderGlob_t;


//------------------------------------------------------------------------------
// Global Variable Declarations
//------------------------------------------------------------------------------
extern  int     Image$$IRAM_EXEC$$ZI$$Base;
extern  int     Image$$IRAM_EXEC$$ZI$$Length;
#ifndef __APCS_RWPI
extern  DwlderPath_t    *ptrDwldPath;
#define PTR2DWLDPATH    ptrDwldPath
#else
extern  DwlderPath_t    **pptrDwldPath;
#define PTR2DWLDPATH    (*pptrDwldPath)
#endif


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
void    sysDwlderInit(void);
bool    sysDwlderMain(void);

#endif /* __SYSDWLCFG_H__ */
