//------------------------------------------------------------------------------
//
//  File        : component_scl.c
//  Description : Source file of Sensor configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_component_ctl.h"
#include "os_wrap.h"
#include "aitu_calendar.h"
#include "mmpf_hif.h"
#include "component_scl.h"
#include "drv_scl_os.h"
#include "drv_scl_hvsp_io_st.h"
#include "drv_scl_dma_io_st.h"
#include "drv_scl_pnl_io_st.h"
#include "drv_scl_pnl_io.h"
#include "drv_scl_vip_io_st.h"
#include "drv_scl_vip_io.h"
#include "drv_scl_hvsp_io.h"
#include "drv_scl_dma_io.h"
#include "drv_scl_verchk.h"
#include "drv_scl_dma_st.h"
#include "drv_scl_dma.h"
#include "drv_scl_dbg.h"
#include "drv_pm_chip.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================
#define COMPONENT_SCL_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_SCL_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

#define SCL_DUMMY_ADDRESS    (-1)

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef enum
{
    E_DRV_ID_HVSP1,
    E_DRV_ID_HVSP2,
    E_DRV_ID_HVSP3,
    E_DRV_ID_SCLDMA1,
    E_DRV_ID_SCLDMA2,
    E_DRV_ID_SCLDMA3,
    E_DRV_ID_SCLDMA4,
    E_DRV_ID_VIP,
    E_DRV_ID_PNL,
    E_DRV_ID_MSYS,
    E_DRV_ID_MEM,
    E_DRV_ID_NUM,
} DrvIdType_e;

typedef enum
{
    E_DRV_SC3_SINGLE,
    E_DRV_SC3_MUTI,
    E_DRV_SC3_NUM,
} EN_DRV_SC3_TYPE;

typedef enum
{
    E_DRV_SC1_DSP,
    E_DRV_SC2_DSP,
    E_DRV_SC1_SC2_DSP,
    E_DRV_SC1_SC3_DSP,
    E_DRV_SC2_SC3_DSP,
    E_DRV_SC2_NUM,
} EN_DRV_SC2_TYPE;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct
{
    void *pVirAddr;
    u32 u32PhyAddr;
    u32 u32MIUAddr;
} SclMemConfig_t;

typedef struct
{
    void *pStackTop;
    MsTaskId_e TaskId;
} SclThreadConfig_t;

typedef void (*Task_CB) (void * );

typedef struct
{
    u32 u32Base_Y[4];
    u32 u32Base_C[4];
    u32 u32Base_Y2[4];
    u32 u32Base_C2[4];
    u16 u16Width;
    u16 u16Height;
    u16 u16Width2;
    u16 u16Height2;
    DrvSclDmaIoColorType_e enColor;
    DrvSclDmaIoMemType_e enMem;
    DrvSclDmaIoColorType_e enColorsc2;
    DrvSclDmaIoMemType_e enMemsc2;
} ScldmaSwapBufferConfig_t;

typedef struct
{
    u16 u16Src_Width;
    u16 u16Src_Height;
    u16 u16Dsp_Width;
    u16 u16Dsp_Height;
    u16 u16Dsp_Height_Off;

    DrvSclDmaIoBufferModeType_e enBufferMd;
    u16 u16BufNumber;
    DrvSclDmaIoColorType_e enColor;
    DrvSclDmaIoMemType_e enMem;
    DrvSclHvspIoSrcType_e enSrc;
    u32 u32count;
} SCL_CONFIG;

typedef struct
{
    unsigned int Count;
    DrvIdType_e  enID[5];
    DrvSclDmaIoMemType_e enMem[5];
} SclDmaGetActiveConfig_t;

typedef struct
{
    bool bEn;
    u16 u16BufNumber;
    DrvSclDmaIoBufferModeType_e enBufferMd;
    DrvSclDmaIoBufferModeType_e enBufferMdsc2;
    EN_DRV_SC3_TYPE enSC3Md;
    EN_DRV_SC2_TYPE enSC2Md;
    ScldmaSwapBufferConfig_t stSwapCfg;
    SclDmaGetActiveConfig_t   stGetActCfg;
    bool bswitchpnl;
    bool bsnp;
} SclDmaPollConfig_t;

typedef struct
{
    MMP_ULONG     address;
    MMP_UBYTE     index;
    MMP_UBYTE     ubBufUsage;
    MMP_UBYTE     ubBufUsage1;
    MMP_UBYTE     ubCH; //0:use ubBufUsage, 1:ubBufUsage1
} BufferCFG;

typedef struct
{
    MMP_UBYTE     ubBufOrderUsage;
    MMP_UBYTE     ubCurBufOrder;
} SCLOrderBufferCFG;
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

BufferCFG SCLDMA1_BufferCfg[4] =
{
    {SCL_DUMMY_ADDRESS, 0, 2, 2, 0},
    {SCL_DUMMY_ADDRESS, 1, 2, 2, 0},
    {SCL_DUMMY_ADDRESS, 2, 2, 2, 0},
    {SCL_DUMMY_ADDRESS, 3, 2, 2, 0},
};

BufferCFG SCLDMA2_BufferCfg[4] =
{
    {SCL_DUMMY_ADDRESS, 0, 2, 2, 0},
    {SCL_DUMMY_ADDRESS, 1, 2, 2, 0},
    {SCL_DUMMY_ADDRESS, 2, 2, 2, 0},
    {SCL_DUMMY_ADDRESS, 3, 2, 2, 0},
};
SCLOrderBufferCFG SCLDMA1_BufferOrderCfg[4] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
};
MMP_COMPONENT_BUFFER_INFO orderBufferInfo[4];
SCLOrderBufferCFG SCLDMA2_BufferOrderCfg[4] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
};
MMP_UBYTE gubSCL0IdxQueue[4] = {0, 0, 0, 0};
MMP_UBYTE gubSCL0CurRIdx = 0;
MMP_UBYTE gubSCL0CurWIdx = 0;
MMP_UBYTE gubSCL1IdxQueue[4] = {0, 0, 0, 0};
MMP_UBYTE gubSCL1CurRIdx = 0;
MMP_UBYTE gubSCL1CurWIdx = 0;

static MMP_COMPONENT_BASE *pCurCompSCL0;
static MMP_COMPONENT_BASE *pCurCompSCL1;
static MMP_COMPONENT_BASE *pCompSCL0[COMPONENT_SCL0_MAX_NUM];
static MMP_COMPONENT_BASE *pCompSCL1[COMPONENT_SCL1_MAX_NUM];

static SCL_CONFIG SCL0_cfg;
static SCL_CONFIG SCL1_cfg;

static SclDmaPollConfig_t stScl0dmaPollCfg;
static SclDmaPollConfig_t stScl1dmaPollCfg;

static s32 g_SCLFD[E_DRV_ID_NUM] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
s32 s32Handler[E_DRV_SCLHVSP_IO_ID_NUM] = {-1, -1, -1};

extern MMPF_OS_FLAGID       SCL_POLL_Flag;

static bool startPollSCL0 = FALSE;
static bool startPollSCL1 = FALSE;

MMP_ERR Component_SCL0_InitDevice(void *handler);
MMP_ERR Component_SCL0_UnInitDevice(void *handler);
MMP_ERR Component_SCL0_PRM_OpenDevice(void *handler);
MMP_ERR Component_SCL0_PRM_CloseDevice(void *handler);
MMP_ERR Component_SCL0_SCD_OpenDevice(void *handler);
MMP_ERR Component_SCL0_SCD_CloseDevice(void *handler);
MMP_ERR Component_SCL0_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_SCL0_GetParam(void *handler, int type, void* pParam);

MMP_ERR Component_SCL1_InitDevice(void *handler);
MMP_ERR Component_SCL1_UnInitDevice(void *handler);
MMP_ERR Component_SCL1_PRM_OpenDevice(void *handler);
MMP_ERR Component_SCL1_PRM_CloseDevice(void *handler);
MMP_ERR Component_SCL1_SCD_OpenDevice(void *handler);
MMP_ERR Component_SCL1_SCD_CloseDevice(void *handler);
MMP_ERR Component_SCL1_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_SCL1_GetParam(void *handler, int type, void* pParam);
static MMP_ERR Component_SCL0_GetBufferInfo(void *handler, MMP_ULONG *ulBufNum, void *pBufInfo);
static MMP_ERR Component_SCL1_GetBufferInfo(void *handler, MMP_ULONG *ulBufNum, void *pBufInfo);
static MMP_ERR MMP_CompSCLCtl_UpdateBuffer(void *pHandle, MMP_ULONG ulSize, void *BufInfo);
static MMP_ERR MMP_CompSCL0Ctl_EmptyBuffer(void *pHandle, MMP_ULONG ulSize, void *BufInfo);
static MMP_ERR MMP_CompSCL1Ctl_EmptyBuffer(void *pHandle, MMP_ULONG ulSize, void *BufInfo);
static MMP_ERR MMP_CompSCL0Ctl_EmptyOrderBuffer(void *pHandle, MMP_ULONG ulSize, void *BufInfo);
static MMP_ERR MMP_CompSCL1Ctl_EmptyOrderBuffer(void *pHandle, MMP_ULONG ulSize, void *BufInfo);
static MMP_ERR MMP_CompSCL0Ctl_EmptyBufferDone(void *pHandle, MMP_ULONG ulSize, void *BufInfo);
static MMP_ERR MMP_CompSCL1Ctl_EmptyBufferDone(void *pHandle, MMP_ULONG ulSize, void *BufInfo);

MMP_COMPONENT_BUFFER_INFO Component_SCL0_BufInfo[COMPONENT_SCL0_MAX_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_SCL0_OutPort[COMPONENT_SCL0_MAX_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_HANDLER_SCL0 Component_SCL0_DeviceInfo[COMPONENT_SCL0_MAX_NUM];
MMP_COMPONENT_MEMORY_INFO Component_SCL0_MemoryInfo[COMPONENT_SCL0_MAX_NUM];

MMP_COMPONENT_BASE Component_SCL0[COMPONENT_SCL0_MAX_NUM] =
{
    {
        "SCL0_PRM",
        MMP_COMPONENT_STATE_INVALID,                    // ulState
        MMP_TRUE,                                       // bRegistered
        MMP_FALSE,                                      // bByPass
        0,                                              // ubOutputPortNum
        &Component_SCL0_MemoryInfo[SCL0_COMP_PRM_CAM],  // MemoryInfo
        Component_SCL0_BufInfo[SCL0_COMP_PRM_CAM],      // BufferInfo
        NULL,                                           // pInPort
        Component_SCL0_OutPort[SCL0_COMP_PRM_CAM],      // pOutPort
        {
            &MMP_CompSCLCtl_UpdateBuffer,
            &MMP_CompSCL0Ctl_EmptyBuffer,
            &MMP_CompSCL0Ctl_EmptyOrderBuffer,
            &MMP_CompSCL0Ctl_EmptyBufferDone,
        },
        Component_SCL0_InitDevice,                      // pfInit
        Component_SCL0_PRM_OpenDevice,                  // pfOpen
        NULL,                                           // pfAllocateMemory
        NULL,                                           // pfFreeMemory
        Component_SCL0_UnInitDevice,                    // pfUnInit
        Component_SCL0_PRM_CloseDevice,                 // pfClose
        Component_SCL0_SetParam,                        // pfSetParameter
        Component_SCL0_GetParam,                        // pfGetParameter
        NULL,                                           // pfUpdateBuffer
        NULL,                                           // pfEmptyBuffer
        NULL,                                           // pfEmptyBufferDone
        Component_SCL0_GetBufferInfo,                   // pfGetBufferInfo
        &Component_SCL0_DeviceInfo[SCL0_COMP_PRM_CAM],  // DeviceInfo
    },
    {
        "SCL0_SCD",
        MMP_COMPONENT_STATE_INVALID,                    // ulState
        MMP_TRUE,                                       // bRegistered
        MMP_FALSE,                                      // bByPass
        0,                                              // ubOutputPortNum
        &Component_SCL0_MemoryInfo[SCL0_COMP_SCD_CAM],  // MemoryInfo
        Component_SCL0_BufInfo[SCL0_COMP_SCD_CAM],      // BufferInfo
        NULL,                                           // pInPort
        Component_SCL0_OutPort[SCL0_COMP_SCD_CAM],      // pOutPort
        {
            &MMP_CompSCLCtl_UpdateBuffer,
            &MMP_CompSCL0Ctl_EmptyBuffer,
            &MMP_CompSCL0Ctl_EmptyOrderBuffer,
            &MMP_CompSCL0Ctl_EmptyBufferDone,
        },
        Component_SCL0_InitDevice,                      // pfInit
        Component_SCL0_SCD_OpenDevice,                  // pfOpen
        NULL,                                           // pfAllocateMemory
        NULL,                                           // pfFreeMemory
        Component_SCL0_UnInitDevice,                    // pfUnInit
        Component_SCL0_SCD_CloseDevice,                 // pfClose
        Component_SCL0_SetParam,                        // pfSetParameter
        Component_SCL0_GetParam,                        // pfGetParameter
        NULL,                                           // pfUpdateBuffer
        NULL,                                           // pfEmptyBuffer
        NULL,                                           // pfEmptyBufferDone
        Component_SCL0_GetBufferInfo,                   // pfGetBufferInfo
        &Component_SCL0_DeviceInfo[SCL0_COMP_SCD_CAM],  // DeviceInfo
    }
};

MMP_COMPONENT_BUFFER_INFO Component_SCL1_BufInfo[COMPONENT_SCL1_MAX_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_SCL1_OutPort[COMPONENT_SCL1_MAX_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_HANDLER_SCL1 Component_SCL1_DeviceInfo[COMPONENT_SCL1_MAX_NUM];
MMP_COMPONENT_MEMORY_INFO Component_SCL1_MemoryInfo[COMPONENT_SCL1_MAX_NUM];

MMP_COMPONENT_BASE Component_SCL1[COMPONENT_SCL1_MAX_NUM] =
{
    {
        "SCL1_PRM",
        MMP_COMPONENT_STATE_INVALID,                    // ulState
        MMP_TRUE,                                       // bRegistered
        MMP_FALSE,                                      // bByPass
        0,                                              // ubOutputPortNum
        &Component_SCL1_MemoryInfo[SCL1_COMP_PRM_CAM],  // MemoryInfo
        Component_SCL1_BufInfo[SCL1_COMP_PRM_CAM],      // BufferInfo
        NULL,                                           // pInPort
        Component_SCL1_OutPort[SCL1_COMP_PRM_CAM],      // pOutPort
        {
            &MMP_CompSCLCtl_UpdateBuffer,
            &MMP_CompSCL1Ctl_EmptyBuffer,
            &MMP_CompSCL1Ctl_EmptyOrderBuffer,
            &MMP_CompSCL1Ctl_EmptyBufferDone,
        },
        Component_SCL1_InitDevice,                      // pfInit
        Component_SCL1_PRM_OpenDevice,                  // pfOpen
        NULL,                                           // pfAllocateMemory
        NULL,                                           // pfFreeMemory
        Component_SCL1_UnInitDevice,                    // pfUnInit
        Component_SCL1_PRM_CloseDevice,                 // pfClose
        Component_SCL1_SetParam,                        // pfSetParameter
        Component_SCL1_GetParam,                        // pfGetParameter
        NULL,                                           // pfUpdateBuffer
        NULL,                                           // pfEmptyBuffer
        NULL,                                           // pfEmptyBufferDone
        Component_SCL1_GetBufferInfo,                   // pfGetBufferInfo
        &Component_SCL1_DeviceInfo[SCL1_COMP_PRM_CAM],  // DeviceInfo
    },
    {
        "SCL1_SCD",
        MMP_COMPONENT_STATE_INVALID,                    // ulState
        MMP_TRUE,                                       // bRegistered
        MMP_FALSE,                                      // bByPass
        0,                                              // ubOutputPortNum
        &Component_SCL1_MemoryInfo[SCL1_COMP_SCD_CAM],  // MemoryInfo
        Component_SCL1_BufInfo[SCL1_COMP_SCD_CAM],      // BufferInfo
        NULL,                                           // pInPort
        Component_SCL1_OutPort[SCL1_COMP_SCD_CAM],      // pOutPort
        {
            &MMP_CompSCLCtl_UpdateBuffer,
            &MMP_CompSCL1Ctl_EmptyBuffer,
            &MMP_CompSCL1Ctl_EmptyOrderBuffer,
            &MMP_CompSCL1Ctl_EmptyBufferDone,
        },
        Component_SCL1_InitDevice,                      // pfInit
        Component_SCL1_SCD_OpenDevice,                  // pfOpen
        NULL,                                           // pfAllocateMemory
        NULL,                                           // pfFreeMemory
        Component_SCL1_UnInitDevice,                    // pfUnInit
        Component_SCL1_SCD_CloseDevice,                 // pfClose
        Component_SCL1_SetParam,                        // pfSetParameter
        Component_SCL1_GetParam,                        // pfGetParameter
        NULL,                                           // pfUpdateBuffer
        NULL,                                           // pfEmptyBuffer
        NULL,                                           // pfEmptyBufferDone
        Component_SCL1_GetBufferInfo,                   // pfGetBufferInfo
        &Component_SCL1_DeviceInfo[SCL1_COMP_SCD_CAM],  // DeviceInfo
    }
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____Local_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : InitSCLDevice
//  Description :
//------------------------------------------------------------------------------
static MMP_BOOL InitSCLDevice(void)
{
    if (DrvSclOsGetProbeInformation(E_DRV_SCLOS_INIT_HVSP) == 0)
    {
        if (DrvSclHvspIoInit() != E_DRV_SCLHVSP_IO_ERR_OK)
        {
            sclprintf("DrvSclHvspIoInit Fail\r\n");
            return MMP_FALSE;
        }
    }

    if (DrvSclOsGetProbeInformation(E_DRV_SCLOS_INIT_PNL) == 0)
    {
        if (DrvSclPnlIoInit() != E_DRV_SCLPNL_IO_ERR_OK)
        {
            sclprintf("DrvSclPnlIoInit Fail\r\n");
            return MMP_FALSE;
        }
    }

    if (DrvSclOsGetProbeInformation(E_DRV_SCLOS_INIT_DMA) == 0)
    {
        if (DrvSclDmaIoInit() != E_DRV_SCLDMA_IO_ERR_OK)
        {
            sclprintf("DrvSclDmaIoInit Fail\r\n");
            return MMP_FALSE;
        }
    }

    if (DrvSclOsGetProbeInformation(E_DRV_SCLOS_INIT_VIP) == 0)
    {
        if (DrvSclVipIoInit() != E_DRV_SCLVIP_IO_ERR_OK)
        {
            sclprintf("DrvSclVipIoInit Fail\r\n");
            return MMP_FALSE;
        }
    }

    Reset_DBGMG_FLAG();
    return MMP_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : CloseSCLDevice
//  Description :
//------------------------------------------------------------------------------
static int CloseSCLDevice(DrvIdType_e enDrvID)
{
    int ret = 1;
    char device_name[E_DRV_ID_NUM][50] =
    {
        {"mhvsp1"},
        {"mhvsp2"},
        {"mhvsp3"},
        {"mscldma1"},
        {"mscldma2"},
        {"mscldma3"},
        {"mscldma4"},
        {"mvip"},
        {"mpnl"},
        {"msys"},
        {"mem"},
    };

    if (enDrvID >= E_DRV_ID_NUM)
    {
        sclprintf("ID is not correct\n");
        return 0;
    }

    if (g_SCLFD[enDrvID] != -1)
    {
        switch(enDrvID)
        {
        case E_DRV_ID_HVSP1:
            DrvSclHvspIoRelease(g_SCLFD[enDrvID]);
            break;
        case E_DRV_ID_HVSP2:
            DrvSclHvspIoRelease(g_SCLFD[enDrvID]);
            break;
        case E_DRV_ID_HVSP3:
            DrvSclHvspIoRelease(g_SCLFD[enDrvID]);
            break;
        case E_DRV_ID_SCLDMA1:
            DrvSclDmaIoRelease(g_SCLFD[enDrvID]);
            break;
        case E_DRV_ID_SCLDMA2:
            DrvSclDmaIoRelease(g_SCLFD[enDrvID]);
            break;
        case E_DRV_ID_SCLDMA3:
            DrvSclDmaIoRelease(g_SCLFD[enDrvID]);
            break;
        case E_DRV_ID_SCLDMA4:
            DrvSclDmaIoRelease(g_SCLFD[enDrvID]);
            break;
        case E_DRV_ID_PNL:
            DrvSclPnlIoRelease(g_SCLFD[enDrvID]);
            break;
        case E_DRV_ID_VIP:
            DrvSclVipIoRelease(g_SCLFD[enDrvID]);
            break;
        default:
        case E_DRV_ID_MSYS:
        case E_DRV_ID_MEM:
            g_SCLFD[enDrvID] = -1;
            break;
        }

        g_SCLFD[enDrvID] = -1;

        if (g_SCLFD[enDrvID] == -1)
        {
            //sclprintf("close %s sucess\n", &device_name[enDrvID][0]);
            ret = 0;
        }
        else
        {
            sclprintf("[open]close %s %d fail\n", &device_name[enDrvID][0], g_SCLFD[enDrvID]);
            ret = 1;
        }
    }
    return ret;
}

//------------------------------------------------------------------------------
//  Function    : OpenSCLDevice
//  Description :
//------------------------------------------------------------------------------
static int OpenSCLDevice(DrvIdType_e enDrvID)
{
    int ret = 1;
    char device_name[E_DRV_ID_NUM][50] =
    {
        {"mhvsp1"},
        {"mhvsp2"},
        {"mhvsp3"},
        {"mscldma1"},
        {"mscldma2"},
        {"mscldma3"},
        {"mscldma4"},
        {"mvip"},
        {"mpnl"},
        {"msys"},
        {"mem"},
    };

    if (enDrvID >= E_DRV_ID_NUM)
    {
        sclprintf("ID is not correct\n");
        return 0;
    }

    if (g_SCLFD[enDrvID] != -1)
    {
    }
    else
    {
        switch(enDrvID)
        {
        case E_DRV_ID_HVSP1:
            g_SCLFD[enDrvID] = DrvSclHvspIoOpen(E_DRV_SCLHVSP_IO_ID_1);
            break;
        case E_DRV_ID_HVSP2:
            g_SCLFD[enDrvID] = DrvSclHvspIoOpen(E_DRV_SCLHVSP_IO_ID_2);
            break;
        case E_DRV_ID_HVSP3:
            g_SCLFD[enDrvID] = DrvSclHvspIoOpen(E_DRV_SCLHVSP_IO_ID_3);
            break;
        case E_DRV_ID_SCLDMA1:
            g_SCLFD[enDrvID] = DrvSclDmaIoOpen(E_DRV_SCLDMA_IO_ID_1);
            break;
        case E_DRV_ID_SCLDMA2:
            g_SCLFD[enDrvID] = DrvSclDmaIoOpen(E_DRV_SCLDMA_IO_ID_2);
            break;
        case E_DRV_ID_SCLDMA3:
            g_SCLFD[enDrvID] = DrvSclDmaIoOpen(E_DRV_SCLDMA_IO_ID_3);
            break;
        case E_DRV_ID_SCLDMA4:
            g_SCLFD[enDrvID] = DrvSclDmaIoOpen(E_DRV_SCLDMA_IO_ID_4);
            break;
        case E_DRV_ID_PNL:
            g_SCLFD[enDrvID] = DrvSclPnlIoOpen(E_DRV_SCLPNL_IO_ID_1);
            break;
        default:
        case E_DRV_ID_VIP:
            g_SCLFD[enDrvID] = DrvSclVipIoOpen(E_DRV_SCLVIP_IO_ID_1);
            break;
        case E_DRV_ID_MSYS:
        case E_DRV_ID_MEM:
            g_SCLFD[enDrvID] = -1;
            break;
        }

        if (g_SCLFD[enDrvID] == -1) {
            sclprintf("open %s fail\n", &device_name[enDrvID][0]);
            ret = 0;
        }
        else {
            //sclprintf("[open]open %s  %d sucess\n", &device_name[enDrvID][0],g_SCLFD[enDrvID]);
            ret = 1;
        }
    }
    return ret;
}

static u8 GetSCLDMABufferId(DrvIdType_e enType, MMP_ULONG addr)
{
    u8 idx = 0;

    if (enType == E_DRV_ID_SCLDMA1)  {
        for (idx = 0; idx < 4; idx++) {
            if (SCLDMA1_BufferCfg[idx].address == addr)
               return idx;
        }
    }
    else if (enType == E_DRV_ID_SCLDMA2) {
        for(idx = 0; idx < 4; idx++) {
            if (SCLDMA2_BufferCfg[idx].address == addr)
               return idx;
        }
    }

    return 0xFF;
}

static MMP_ULONG GetSCLDMABufferAddress(DrvIdType_e enType,int index)
{
    if (enType == E_DRV_ID_SCLDMA1) {
        return SCLDMA1_BufferCfg[index].address;
    }
    else if (enType == E_DRV_ID_SCLDMA2) {
        return SCLDMA2_BufferCfg[index].address;
    }

    return SCL_DUMMY_ADDRESS;
}

static void Request_IPM(u32 ulchannel, u16 u16Src_Width,u16 u16Src_Height)
{
    // HVSP1 Request IPM memory
    DrvSclHvspIoReqMemConfig_t stHvspReqMemCfg;

    stHvspReqMemCfg.u16Pitch = u16Src_Width;
    stHvspReqMemCfg.u16Vsize = u16Src_Height;
    stHvspReqMemCfg.u32MemSize = u16Src_Width * u16Src_Height *2 * 2;
    stHvspReqMemCfg.u32Channel = ulchannel;
    stHvspReqMemCfg = FILL_VERCHK_TYPE(stHvspReqMemCfg, stHvspReqMemCfg.VerChk_Version, stHvspReqMemCfg.VerChk_Size,DRV_SCLHVSP_VERSION);
    DrvSclHvspIoReqmemConfig(g_SCLFD[E_DRV_ID_HVSP1],&stHvspReqMemCfg);
    
}

static void Free_IPM(u32 ulchannel)
{
    DrvSclHvspIoReleaseMemConfig(g_SCLFD[E_DRV_ID_HVSP1], ulchannel);
}

static DrvSclDmaIoBufferConfig_t SetBufferConfig(DrvIdType_e enType, SCL_CONFIG stCfg, MMP_ULONG stMsysMemInfo, bool bin)
{
    u16 BufNum = 0;
    DrvSclDmaIoBufferConfig_t stSCLDMACfg;
    int BufferIdx = 0;
    u32 buffsize = stCfg.u16Dsp_Width * (stCfg.u16Dsp_Height + stCfg.u16Dsp_Height_Off); // 2bpp
    BufNum = stCfg.enBufferMd == E_DRV_SCLDMA_IO_BUFFER_MD_SINGLE ? 1 : stCfg.u16BufNumber;

    stSCLDMACfg.enBufMDType = stCfg.enBufferMd;
    stSCLDMACfg.enMemType   = stCfg.enMem;
    stSCLDMACfg.enColorType = stCfg.enColor;
    stSCLDMACfg.u16Height   = stCfg.u16Dsp_Height;
    stSCLDMACfg.u16Width    = stCfg.u16Dsp_Width;
    stSCLDMACfg.u16BufNum   = BufNum;

    stSCLDMACfg.bvFlag.btsBase_0 = stSCLDMACfg.u16BufNum >= 1 ? 1 : 0;
    stSCLDMACfg.bvFlag.btsBase_1 = stSCLDMACfg.u16BufNum >= 2 ? 1 : 0;
    stSCLDMACfg.bvFlag.btsBase_2 = stSCLDMACfg.u16BufNum >= 3 ? 1 : 0;
    stSCLDMACfg.bvFlag.btsBase_3 = stSCLDMACfg.u16BufNum >= 4 ? 1 : 0;

    if (stSCLDMACfg.enColorType == E_DRV_SCLDMA_IO_COLOR_YUV422)
    {
        for (BufferIdx = 0; BufferIdx < stSCLDMACfg.u16BufNum; BufferIdx++)
        {
            stSCLDMACfg.u32Base_Y[BufferIdx] = stMsysMemInfo + (buffsize) *2* BufferIdx;
            stSCLDMACfg.u32Base_C[BufferIdx] = stSCLDMACfg.u32Base_Y[BufferIdx]+16;
        }
    }
    else if ((stSCLDMACfg.enColorType == E_DRV_SCLDMA_IO_COLOR_YUVSep422))
    {
        for (BufferIdx = 0; BufferIdx < stSCLDMACfg.u16BufNum; BufferIdx++)
        {
            stSCLDMACfg.u32Base_Y[BufferIdx] = stMsysMemInfo + (buffsize*2*BufferIdx);
            stSCLDMACfg.u32Base_C[BufferIdx] = stSCLDMACfg.u32Base_Y[BufferIdx] + (buffsize);
            stSCLDMACfg.u32Base_V[BufferIdx] = stSCLDMACfg.u32Base_C[BufferIdx] + (buffsize/2);
        }
    }
    else if ((stSCLDMACfg.enColorType == E_DRV_SCLDMA_IO_COLOR_YUVSep420))
    {
        for (BufferIdx = 0; BufferIdx < stSCLDMACfg.u16BufNum; BufferIdx++)
        {
            stSCLDMACfg.u32Base_Y[BufferIdx] = stMsysMemInfo + (buffsize*3/2*BufferIdx);
            stSCLDMACfg.u32Base_C[BufferIdx] = stSCLDMACfg.u32Base_Y[BufferIdx] + (buffsize);
            stSCLDMACfg.u32Base_V[BufferIdx] = stSCLDMACfg.u32Base_C[BufferIdx] + (buffsize/4);
        }
    }
    else if ((stSCLDMACfg.enColorType == E_DRV_SCLDMA_IO_COLOR_YCSep422))
    {
        for (BufferIdx = 0; BufferIdx < stCfg.u16BufNumber; BufferIdx++)
        {
            stSCLDMACfg.u32Base_Y[BufferIdx] = stMsysMemInfo + (buffsize*2*BufferIdx);
            stSCLDMACfg.u32Base_C[BufferIdx] = stSCLDMACfg.u32Base_Y[BufferIdx] + (buffsize);
        }
    }
    else
    {
        for (BufferIdx = 0; BufferIdx < stCfg.u16BufNumber; BufferIdx++)
        {
            stSCLDMACfg.u32Base_Y[BufferIdx] = stMsysMemInfo + (buffsize*3/2*BufferIdx);
            if (enType == E_DRV_ID_SCLDMA1) {
                stSCLDMACfg.u32Base_Y[BufferIdx] += stCfg.u16Dsp_Height_Off * stCfg.u16Dsp_Width;
            }
            stSCLDMACfg.u32Base_C[BufferIdx] = stSCLDMACfg.u32Base_Y[BufferIdx] + (buffsize);
            if (enType == E_DRV_ID_SCLDMA1) {
                stSCLDMACfg.u32Base_C[BufferIdx] -= (stCfg.u16Dsp_Height_Off >> 1) * stCfg.u16Dsp_Width;
            }
        }
    }

    if (bin)
    {
        stSCLDMACfg.enMemType = E_DRV_SCLDMA_IO_MEM_FRM;
        stSCLDMACfg = FILL_VERCHK_TYPE(stSCLDMACfg, stSCLDMACfg.VerChk_Version, stSCLDMACfg.VerChk_Size,DRV_SCLDMA_VERSION);
        DrvSclDmaIoSetInBufferConfig(g_SCLFD[enType], &stSCLDMACfg);
    }
    else
    {
        stSCLDMACfg = (DrvSclDmaIoBufferConfig_t)FILL_VERCHK_TYPE(stSCLDMACfg, stSCLDMACfg.VerChk_Version, stSCLDMACfg.VerChk_Size,DRV_SCLDMA_VERSION);
        DrvSclDmaIoSetOutBufferConfig(g_SCLFD[enType], &stSCLDMACfg);
    }

    return stSCLDMACfg;
}

static DrvSclDmaIoActiveBufferConfig_t _SetSCLBufferRPoint(DrvIdType_e enType, DrvSclDmaIoMemType_e enMemType, u8 u8RPoint)
{
    DrvSclDmaIoActiveBufferConfig_t stSCLDMABFCfg;

    stSCLDMABFCfg.u8ActiveBuffer = (E_DRV_SCLDMA_IO_ACTIVE_BUFFER_OMX|u8RPoint);
    stSCLDMABFCfg.enMemType = enMemType;
    stSCLDMABFCfg = FILL_VERCHK_TYPE(stSCLDMABFCfg, stSCLDMABFCfg.VerChk_Version,
                                     stSCLDMABFCfg.VerChk_Size,DRV_SCLDMA_VERSION);

    DrvSclDmaIoGetOutActiveBufferConfig(g_SCLFD[enType], &stSCLDMABFCfg);
    return stSCLDMABFCfg;
}

static DrvSclDmaIoActiveBufferConfig_t _GetSCLBufferRPoint(DrvIdType_e enType, DrvSclDmaIoMemType_e enMemType)
{
    DrvSclDmaIoActiveBufferConfig_t stSCLDMABFCfg;

    stSCLDMABFCfg.enMemType = enMemType;
    stSCLDMABFCfg = FILL_VERCHK_TYPE(stSCLDMABFCfg, stSCLDMABFCfg.VerChk_Version,
                                     stSCLDMABFCfg.VerChk_Size,DRV_SCLDMA_VERSION);

    DrvSclDmaIoGetOutActiveBufferConfig(g_SCLFD[enType], &stSCLDMABFCfg);
    return stSCLDMABFCfg;
}

static void _SetSCLDMATrig(DrvIdType_e enType, DrvSclDmaIoMemType_e enMemType, bool bEn)
{
    DrvSclDmaIoTriggerConfig_t  stSCLDMATrigCfg;

    stSCLDMATrigCfg.bEn = bEn;
    stSCLDMATrigCfg.enMemType = enMemType;
    stSCLDMATrigCfg = FILL_VERCHK_TYPE(stSCLDMATrigCfg, stSCLDMATrigCfg.VerChk_Version,
                                       stSCLDMATrigCfg.VerChk_Size,DRV_SCLDMA_VERSION);

    DrvSclDmaIoSetOutTriggerConfig(g_SCLFD[enType], &stSCLDMATrigCfg);
}

static void SCL0_Adj_CurWIdx(MMP_BOOL  bOrdering, MMP_BOOL ubRealOut)
{
    MMP_UBYTE bSCL0CurWIdx = gubSCL0CurWIdx;

    if (bOrdering && ubRealOut) {
        gubSCL0CurWIdx ++;
        if (gubSCL0CurWIdx > 3) {
            gubSCL0CurWIdx = 0;
        }

        //if(gubSCL0CurWIdx == gubSCL0CurRIdx){
            //gubSCL0CurWIdx = bSCL0CurWIdx;
            //UartSendTrace(FG_RED("WRN: WIdx== RIdx=%d\r\n"),gubSCL0CurWIdx);
        //}
    }
}

static void SCL0_Adj_CurRIdx(MMP_BOOL  bOrdering,MMP_BOOL ubRealOut)
{
    MMP_UBYTE bSCL0CurRIdx = gubSCL0CurRIdx;

    //if(gubSCL0CurRIdx == gubSCL0CurWIdx){
        //UartSendTrace(FG_BLUE("WRN:RIdx==WIdx=%d\r\n"),gubSCL0CurRIdx);
        //return;
    //}

    if (bOrdering && ubRealOut) {
        gubSCL0CurRIdx ++;
        if (gubSCL0CurRIdx > 3) {
            gubSCL0CurRIdx = 0;
        }

        if(gubSCL0CurRIdx == gubSCL0CurWIdx){
            //gubSCL0CurRIdx = bSCL0CurRIdx;
            //UartSendTrace(FG_BLUE("WRN:RIdx == WIdx=%d\r\n"),gubSCL0CurRIdx);
        }
    }
}
static MMP_ERR MMP_CompSCLCtl_UpdateBuffer(void *pHandle, MMP_ULONG ulSize, void *BufInfo)
{
    return MMP_ERR_NONE;
}

static MMP_ERR MMP_CompSCL0Ctl_EmptyBuffer(void *pHandle, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_ULONG                       i = 0;
    MMP_UBYTE                       ubIndex = 0;
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)pHandle;
    MMP_COMPONENT_BASE              *pChComp = pCurCompSCL0;
    MMP_COMPONENT_BASE              *pNextComp = NULL;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_BUFFER_INFO       *pCustBuf = BufInfo;
    MMP_COMPONENT_HANDLER_SCL0      *pSCL = (MMP_COMPONENT_HANDLER_SCL0*)pComp->DeviceInfo;
    u8                              actid = 0;
    MMP_UBYTE                       ubHaveOUT = 0,ubRealOut = 0;
    MMP_BOOL                        bOrdering = MMP_FALSE;
    MMP_UBYTE                       ubCurOrder = 0;
    MMP_BOOL                        bFoundOrder = MMP_FALSE;

    if (pComp == NULL) {
        COMPONENT_SCL_DBG_ERR(1, "Component is NULL\r\n");
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }
    ubRealOut = 0;
    bOrdering = pComp->MemoryInfo->ulBufOrderInfo.bBurOder;
    ubCurOrder = pComp->MemoryInfo->ulBufOrderInfo.ubMinBufOrder;

    // Send empty buffer to every port.
    if (pChComp->ubOutputPortNum) {
        pBuf[0].bufctl.frm.ubBufUsage = pChComp->ubOutputPortNum;

        for (i = 0 ; i < pChComp->ubOutputPortNum; i++) {
            if (pChComp->pOutPort[i].State == PORT_OPEN) {
                ubHaveOUT = TRUE;
            }
        }

        if (pSCL->u16DropFrameCnt > 0) {
            pSCL->u16DropFrameCnt--;
            ubHaveOUT = FALSE;
        }

        actid = GetSCLDMABufferId(E_DRV_ID_SCLDMA1, pCustBuf->ulBufAddr);
        if(actid == 0xff){
            UartSendTrace(FG_RED( "%s get actid error #%d!\n"),__FUNCTION__,__LINE__);
            return MMP_COMPONENT_ERR_USAGE_ID;
        }

        if (ubHaveOUT) {

            if (bOrdering) {
                while(!bFoundOrder) {
                    gubSCL0IdxQueue[gubSCL0CurWIdx] = actid;
                    for (i = 0 ; i <  pChComp->ubOutputPortNum; i++) {
                        if (pChComp->pOutPort[i].State == PORT_OPEN) {
                            if (pChComp->pOutPort[i].bufInfo.ubBufOrder == ubCurOrder) {
                                SCLDMA1_BufferOrderCfg[gubSCL0CurWIdx].ubCurBufOrder = ubCurOrder;
                                bFoundOrder = MMP_TRUE;
                                break;
                            }
                        }
                    }
                    if (!bFoundOrder) {
                        ubCurOrder ++;
                        if (ubCurOrder > pChComp->MemoryInfo->ulBufOrderInfo.ubMaxBufOrder) {
                            UartSendTrace("Strange: SCL empty!Ordering over Max\n");
                            bOrdering = MMP_FALSE;
                            break;
                        }
                    }
                }
                //SCL0_Adj_CurWIdx(bOrdering);
            }

            if (pChComp == pCompSCL0[0]) {
                SCLDMA1_BufferCfg[actid].ubBufUsage  = pChComp->ubOutputPortNum;
                SCLDMA1_BufferCfg[actid].ubBufUsage1 = 0;
                SCLDMA1_BufferCfg[actid].ubCH = 0;
            }
            else {
                SCLDMA1_BufferCfg[actid].ubBufUsage  = 0;
                SCLDMA1_BufferCfg[actid].ubBufUsage1 = pChComp->ubOutputPortNum;
                SCLDMA1_BufferCfg[actid].ubCH = 1;
            }

            for (i = 0 ; i < pChComp->ubOutputPortNum; i++) {

                if (pChComp->pOutPort[i].State == PORT_OPEN) {
                    //excute component which order == ubCurOrder.
                    if ((!bOrdering) || (bOrdering && (ubCurOrder == pChComp->pOutPort[i].bufInfo.ubBufOrder))) {
                        if (bOrdering) {
                            SCLDMA1_BufferOrderCfg[gubSCL0CurWIdx].ubBufOrderUsage ++;
                            memcpy(&orderBufferInfo[gubSCL0CurWIdx], pCustBuf, sizeof(MMP_COMPONENT_BUFFER_INFO));
                        }
                        ubRealOut = 1;
                        pNextComp = pChComp->pOutPort[i].NextComponent;
                        pNextComp->pInPort->bufInfo.ulBufAddr     = pCustBuf->ulBufAddr;
                        pNextComp->pInPort->bufInfo.u64BufPhyAddr = pCustBuf->u64BufPhyAddr;
                        pNextComp->pInPort->bufInfo.ulBufAddr1 = pNextComp->pInPort->bufInfo.ulBufAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                        pNextComp->pInPort->bufInfo.u64BufPhyAddr1 = pNextComp->pInPort->bufInfo.u64BufPhyAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                        pNextComp->pInPort->bufInfo.ulTime = pCustBuf->ulTime;
                        pNextComp->pInPort->bufInfo.ulSize = pCustBuf->ulSize;
                        pNextComp->pInPort->bufInfo.ulBufBias = pComp->MemoryInfo->ulBufBias;
                        if (1/*stSclOsdCfg.bEn*/) {
                            memcpy(&(pNextComp->pInPort->bufInfo.stDateTime), MMPF_Icon_GetDateTimeAttr(0/*MMP_STICKER_ID_0*/), sizeof(AUTL_DATETIME));
                        }

                        if (pNextComp->pfEmptyBuffer) {
                            pNextComp->pfEmptyBuffer(pNextComp, ulSize, BufInfo);
                        }
                    }
                }
                else {
                    if (pChComp == pCompSCL0[0]) {
                        if(SCLDMA1_BufferCfg[actid].ubBufUsage)
                            SCLDMA1_BufferCfg[actid].ubBufUsage--;

                        if (SCLDMA1_BufferCfg[actid].ubBufUsage == 0) {
                            SCL0_Adj_CurRIdx(bOrdering,ubRealOut);
                            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA1, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                        }
                    }
                    else {
                        if(SCLDMA1_BufferCfg[actid].ubBufUsage1)
                            SCLDMA1_BufferCfg[actid].ubBufUsage1--;

                        if (SCLDMA1_BufferCfg[actid].ubBufUsage1 == 0) {
                            SCL0_Adj_CurRIdx(bOrdering,ubRealOut);
                            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA1, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                        }
                    }
                }
            }
        }
        else {
            // Minus buffer usage for current component.
            pComp->BufferInfo[ubIndex].bufctl.frm.ubBufUsage = 0;
            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA1,E_DRV_SCLDMA_IO_MEM_FRM,actid);
        }
    }

    SCL0_Adj_CurWIdx(bOrdering,ubRealOut);

    return MMP_ERR_NONE;
}

static MMP_ERR MMP_CompSCL0Ctl_EmptyOrderBuffer(void *pHandle, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_ULONG                       i = 0;
    MMP_UBYTE                       ubIndex = 0;
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)pHandle;
    MMP_COMPONENT_BASE              *pChComp = pCurCompSCL0;
    MMP_COMPONENT_BASE              *pNextComp = NULL;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_BUFFER_INFO       *pCustBuf = BufInfo;
    MMP_COMPONENT_HANDLER_SCL0      *pSCL = (MMP_COMPONENT_HANDLER_SCL0*)pComp->DeviceInfo;
    u8                              actid = 0;
    MMP_UBYTE                       ubHaveOUT = 0;
    MMP_BOOL                        bOrdering = 0;
    MMP_BOOL                        bFoundOrder = 0,bFoundOrderFail = 0;
    MMP_UBYTE                       ubCurOrder = 0;
    MMP_UBYTE                       ubOutportEnNum = 0;

    if (pComp == NULL) {
        COMPONENT_SCL_DBG_ERR(1, "Component is NULL\r\n");
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    bOrdering = pComp->MemoryInfo->ulBufOrderInfo.bBurOder;
    // Send empty buffer to every port.
    if (pChComp->ubOutputPortNum && bOrdering) {
        for (i = 0 ; i < pChComp->ubOutputPortNum; i++) {
            if (pChComp->pOutPort[i].State == PORT_OPEN) {
                ubHaveOUT = TRUE;
                ubOutportEnNum ++;
            }
        }

        if (pSCL->u16DropFrameCnt > 0) {
            pSCL->u16DropFrameCnt--;
            ubHaveOUT = FALSE;
        }

        if (ubHaveOUT) {
            if (bOrdering) {
                if (SCLDMA1_BufferOrderCfg[gubSCL0CurRIdx].ubCurBufOrder == pChComp->MemoryInfo->ulBufOrderInfo.ubMaxBufOrder) {
                    // No need to call component empty.
                    return MMP_COMPONENT_NO_NEED_ORDER;
                }

                //Start check current order.
                while(!bFoundOrder) {
                    actid = gubSCL0IdxQueue[gubSCL0CurRIdx];

                    ubCurOrder = SCLDMA1_BufferOrderCfg[gubSCL0CurRIdx].ubCurBufOrder;
                    ubCurOrder ++;

                    for (i = 0 ; i <  pChComp->ubOutputPortNum; i++) {
                        if (pChComp->pOutPort[i].State == PORT_OPEN) {
                            if (pChComp->pOutPort[i].bufInfo.ubBufOrder == ubCurOrder) {
                                SCLDMA1_BufferOrderCfg[gubSCL0CurRIdx].ubCurBufOrder = ubCurOrder;
                                bFoundOrder = MMP_TRUE;
                                break;
                            }
                        }
                    }

                    if (!bFoundOrder) {
                        ubCurOrder ++;
                        if (ubCurOrder > pChComp->MemoryInfo->ulBufOrderInfo.ubMaxBufOrder) {
                            UartSendTrace("Strange: SCL OrderEmpty!Order over Max,RIdx=%d\n",gubSCL0CurRIdx);
                            bOrdering = MMP_FALSE;
                            bFoundOrderFail = MMP_TRUE;
                            break;
                        }
                    }
                }
            }

            if(bFoundOrderFail){
                pComp->BufferInfo[ubIndex].bufctl.frm.ubBufUsage = 0;
                //actid = GetSCLDMABufferId(E_DRV_ID_SCLDMA1, pCustBuf->ulBufAddr);
                UartSendTrace(FG_RED("Strange: ulBufAddr=0x%x,actid=%d,ubCH=%d,ubBufUsage=%d\n"),pCustBuf->ulBufAddr,actid,SCLDMA1_BufferCfg[actid].ubCH,SCLDMA1_BufferCfg[actid].ubBufUsage);

                if (SCLDMA1_BufferCfg[actid].ubCH == 0) {
                    if(SCLDMA1_BufferCfg[actid].ubBufUsage)
                        SCLDMA1_BufferCfg[actid].ubBufUsage--;

                    if (SCLDMA1_BufferCfg[actid].ubBufUsage == 0) {
                        SCL0_Adj_CurRIdx(MMP_TRUE,MMP_TRUE);
                        _SetSCLBufferRPoint(E_DRV_ID_SCLDMA1, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                    }
                }
                else {
                    if(SCLDMA1_BufferCfg[actid].ubBufUsage1)
                        SCLDMA1_BufferCfg[actid].ubBufUsage1--;

                    if (SCLDMA1_BufferCfg[actid].ubBufUsage1 == 0) {
                        SCL0_Adj_CurRIdx(MMP_TRUE,MMP_TRUE);
                        _SetSCLBufferRPoint(E_DRV_ID_SCLDMA1, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                    }
                }

            }
            else{
                for (i = 0 ; i < pChComp->ubOutputPortNum; i++) {
                    if (pChComp->pOutPort[i].State == PORT_OPEN) {
                        if ((!bOrdering) || (bOrdering && (ubCurOrder == pChComp->pOutPort[i].bufInfo.ubBufOrder))) {
                            if (bOrdering) {
                                SCLDMA1_BufferOrderCfg[gubSCL0CurRIdx].ubBufOrderUsage ++;
                                pCustBuf = &orderBufferInfo[gubSCL0CurRIdx];
                               // UartSendTrace("O1: %x, %x\n", pCustBuf->ulBufAddr, gubSCL0CurRIdx);
                            }
                            pNextComp = pChComp->pOutPort[i].NextComponent;
                            pNextComp->pInPort->bufInfo.ulBufAddr     = pCustBuf->ulBufAddr;
                            pNextComp->pInPort->bufInfo.u64BufPhyAddr = pCustBuf->u64BufPhyAddr;
                            pNextComp->pInPort->bufInfo.ulBufAddr1 = pNextComp->pInPort->bufInfo.ulBufAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                            pNextComp->pInPort->bufInfo.u64BufPhyAddr1 = pNextComp->pInPort->bufInfo.u64BufPhyAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                            pNextComp->pInPort->bufInfo.ulTime = pCustBuf->ulTime;
                            pNextComp->pInPort->bufInfo.ulSize = pCustBuf->ulSize;
                            pNextComp->pInPort->bufInfo.ulBufBias = pComp->MemoryInfo->ulBufBias;
                            if (1/*stSclOsdCfg.bEn*/) {
                                memcpy(&(pNextComp->pInPort->bufInfo.stDateTime), MMPF_Icon_GetDateTimeAttr(0/*MMP_STICKER_ID_0*/), sizeof(AUTL_DATETIME));
                            }
                            if (pNextComp->pfEmptyBuffer) {
                                //if(GetCheckFPSEnable(0) && i == 0){//MFE0
                                //    Component_SCL0_CalculateFPS3();
                                //}
                                pNextComp->pfEmptyBuffer(pNextComp, ulSize, BufInfo);
                            }

                        }
                    }
                }
            }
        }
        else {

            // Minus buffer usage for current component.
            pComp->BufferInfo[ubIndex].bufctl.frm.ubBufUsage = 0;

            #if 1
            actid = gubSCL0IdxQueue[gubSCL0CurRIdx];
            #else
            actid = GetSCLDMABufferId(E_DRV_ID_SCLDMA1, pCustBuf->ulBufAddr);
            if(actid == 0xff){
                UartSendTrace(FG_RED( "%s get actid error #%d!\n"),__FUNCTION__,__LINE__);
                return MMP_COMPONENT_ERR_USAGE_ID;
            }
            #endif
            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA1,E_DRV_SCLDMA_IO_MEM_FRM,actid);
            SCL0_Adj_CurRIdx(bOrdering,MMP_TRUE);
        }
    }

    return MMP_ERR_NONE;
}

static MMP_ERR MMP_CompSCL1Ctl_EmptyBuffer(void *pHandle, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_ULONG                   i = 0;
    MMP_UBYTE                   ubIndex = 0;
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)pHandle;
    MMP_COMPONENT_BASE          *pChComp = pCurCompSCL1;
    MMP_COMPONENT_BASE          *pNextComp = NULL;
    MMP_COMPONENT_BASE          *pNext2Comp = NULL;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_BUFFER_INFO   *pCustBuf = BufInfo;
    MMP_COMPONENT_HANDLER_SCL1  *pSCL = (MMP_COMPONENT_HANDLER_SCL1*)pComp->DeviceInfo;
    u8                          actid = 0;
    MMP_UBYTE                   ubHaveOUT = 0;

    if (pComp == NULL) {
        COMPONENT_SCL_DBG_ERR(1, "Component is NULL\r\n");
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    // Send empty buffer to every port.
    if (pChComp->ubOutputPortNum) {

        pBuf[0].bufctl.frm.ubBufUsage = pChComp->ubOutputPortNum;

        for (i = 0 ; i < pChComp->ubOutputPortNum; i++) {
            if (pChComp->pOutPort[i].State == PORT_OPEN) {
                ubHaveOUT = TRUE;
            }
        }

        if (pSCL->u16DropFrameCnt > 0) {
            pSCL->u16DropFrameCnt--;
            ubHaveOUT = FALSE;
        }

        if (ubHaveOUT) {
            actid = GetSCLDMABufferId(E_DRV_ID_SCLDMA2, pCustBuf->ulBufAddr);
            if(actid == 0xff){
                UartSendTrace(FG_RED( "%s get actid error #%d!\n"),__FUNCTION__,__LINE__);
                //return MMP_COMPONENT_ERR_USAGE_ID;
            }

            if (pChComp == pCompSCL1[0]) {
                SCLDMA2_BufferCfg[actid].ubBufUsage  = pChComp->ubOutputPortNum;
                SCLDMA2_BufferCfg[actid].ubBufUsage1 = 0;
                SCLDMA2_BufferCfg[actid].ubCH = 0;
            }
            else {
                SCLDMA2_BufferCfg[actid].ubBufUsage  = 0;
                SCLDMA2_BufferCfg[actid].ubBufUsage1 = pChComp->ubOutputPortNum;
                SCLDMA2_BufferCfg[actid].ubCH = 1;
            }

            for (i = 0 ; i < pChComp->ubOutputPortNum; i++) {
                if (pChComp->pOutPort[i].State == PORT_OPEN) {
                    pNextComp = pChComp->pOutPort[i].NextComponent;
                    if (pNextComp->bByPass) {
                        pNext2Comp = pNextComp->pOutPort[i].NextComponent;
                        if (pNextComp->pOutPort[i].State == PORT_OPEN) {
                            pNext2Comp->pInPort->bufInfo.ulBufAddr     = pCustBuf->ulBufAddr;
                            pNext2Comp->pInPort->bufInfo.u64BufPhyAddr = pCustBuf->u64BufPhyAddr;
                            pNext2Comp->pInPort->bufInfo.ulBufAddr1 = pNext2Comp->pInPort->bufInfo.ulBufAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                            pNext2Comp->pInPort->bufInfo.u64BufPhyAddr1 = pNext2Comp->pInPort->bufInfo.u64BufPhyAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                            pNext2Comp->pInPort->bufInfo.ulTime = pCustBuf->ulTime;
                            pNext2Comp->pInPort->bufInfo.ulSize = pCustBuf->ulSize;
                            pNext2Comp->pInPort->bufInfo.ulBufBias = pComp->MemoryInfo->ulBufBias;
                            if (pNext2Comp->pfEmptyBuffer) {
                                pNext2Comp->pfEmptyBuffer(pNext2Comp, ulSize, BufInfo);
                            }
                        }
                        else {
                            if (pChComp == pCompSCL1[0]) {
                                SCLDMA2_BufferCfg[actid].ubBufUsage--;
                                if (SCLDMA2_BufferCfg[actid].ubBufUsage == 0) {
                                    _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                                }
                            }
                            else {
                                SCLDMA2_BufferCfg[actid].ubBufUsage1--;
                                if (SCLDMA2_BufferCfg[actid].ubBufUsage1 == 0) {
                                    _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                                }
                            }
                        }
                    }
                    else {
                        pNextComp->pInPort->bufInfo.ulBufAddr     = pCustBuf->ulBufAddr;
                        pNextComp->pInPort->bufInfo.u64BufPhyAddr = pCustBuf->u64BufPhyAddr;
                        pNextComp->pInPort->bufInfo.ulBufAddr1 = pNextComp->pInPort->bufInfo.ulBufAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                        pNextComp->pInPort->bufInfo.u64BufPhyAddr1 = pNextComp->pInPort->bufInfo.u64BufPhyAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                        pNextComp->pInPort->bufInfo.ulTime = pCustBuf->ulTime;
                        pNextComp->pInPort->bufInfo.ulSize = pCustBuf->ulSize;
                        pNextComp->pInPort->bufInfo.ulBufBias = pComp->MemoryInfo->ulBufBias;
                        if (pNextComp->pfEmptyBuffer) {
                            pNextComp->pfEmptyBuffer(pNextComp, ulSize, BufInfo);
                        }
                    }
                }
                else {
                    if (pChComp == pCompSCL1[0]) {
                        SCLDMA2_BufferCfg[actid].ubBufUsage--;
                        if (SCLDMA2_BufferCfg[actid].ubBufUsage == 0) {
                            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                        }
                    }
                    else {
                        SCLDMA2_BufferCfg[actid].ubBufUsage1--;
                        if (SCLDMA2_BufferCfg[actid].ubBufUsage1 == 0) {
                            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                        }
                    }
                }
            }
        }
        else {

            // Minus buffer usage for current component.
            pComp->BufferInfo[ubIndex].bufctl.frm.ubBufUsage = 0;

            actid = GetSCLDMABufferId(E_DRV_ID_SCLDMA2, pCustBuf->ulBufAddr);
            if(actid == 0xff){
                UartSendTrace(FG_RED( "%s get actid error #%d!\n"),__FUNCTION__,__LINE__);
                //return MMP_COMPONENT_ERR_USAGE_ID;
            }
            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
        }
    }

    return MMP_ERR_NONE;
}

static MMP_ERR MMP_CompSCL1Ctl_EmptyOrderBuffer(void *pHandle, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_ULONG                   i = 0;
    MMP_UBYTE                   ubIndex = 0;
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)pHandle;
    MMP_COMPONENT_BASE          *pChComp = pCurCompSCL1;
    MMP_COMPONENT_BASE          *pNextComp = NULL;
    MMP_COMPONENT_BASE          *pNext2Comp = NULL;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_BUFFER_INFO   *pCustBuf = BufInfo;
    MMP_COMPONENT_HANDLER_SCL1  *pSCL = (MMP_COMPONENT_HANDLER_SCL1*)pComp->DeviceInfo;
    u8                          actid = 0;
    MMP_UBYTE                   ubHaveOUT = 0;

    if (pComp == NULL) {
        COMPONENT_SCL_DBG_ERR(1, "Component is NULL\r\n");
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    // Send empty buffer to every port.
    if (pChComp->ubOutputPortNum) {

        pBuf[0].bufctl.frm.ubBufUsage = pChComp->ubOutputPortNum;

        for (i = 0 ; i < pChComp->ubOutputPortNum; i++) {
            if (pChComp->pOutPort[i].State == PORT_OPEN) {
                ubHaveOUT = TRUE;
            }
        }

        if (pSCL->u16DropFrameCnt > 0) {
            pSCL->u16DropFrameCnt--;
            ubHaveOUT = FALSE;
        }

        if (ubHaveOUT) {
            actid = GetSCLDMABufferId(E_DRV_ID_SCLDMA2, pCustBuf->ulBufAddr);
            if(actid == 0xff){
                UartSendTrace(FG_RED( "%s get actid error #%d!\n"),__FUNCTION__,__LINE__);
                //return MMP_COMPONENT_ERR_USAGE_ID;
            }
            if (pChComp == pCompSCL1[0]) {
                SCLDMA2_BufferCfg[actid].ubBufUsage  = pChComp->ubOutputPortNum;
                SCLDMA2_BufferCfg[actid].ubBufUsage1 = 0;
                SCLDMA2_BufferCfg[actid].ubCH = 0;
            }
            else {
                UartSendTrace("CALLMECOMECOME\n");
                SCLDMA2_BufferCfg[actid].ubBufUsage  = 0;
                SCLDMA2_BufferCfg[actid].ubBufUsage1 = pChComp->ubOutputPortNum;
                SCLDMA2_BufferCfg[actid].ubCH = 1;
            }

            for (i = 0 ; i < pChComp->ubOutputPortNum; i++) {
                if (pChComp->pOutPort[i].State == PORT_OPEN) {
                    pNextComp = pChComp->pOutPort[i].NextComponent;
                    if (pNextComp->bByPass) {
                        pNext2Comp = pNextComp->pOutPort[i].NextComponent;
                        if (pNextComp->pOutPort[i].State == PORT_OPEN) {
                            pNext2Comp->pInPort->bufInfo.ulBufAddr     = pCustBuf->ulBufAddr;
                            pNext2Comp->pInPort->bufInfo.u64BufPhyAddr = pCustBuf->u64BufPhyAddr;
                            pNext2Comp->pInPort->bufInfo.ulBufAddr1 = pNext2Comp->pInPort->bufInfo.ulBufAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                            pNext2Comp->pInPort->bufInfo.u64BufPhyAddr1 = pNext2Comp->pInPort->bufInfo.u64BufPhyAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                            pNext2Comp->pInPort->bufInfo.ulTime = pCustBuf->ulTime;
                            pNext2Comp->pInPort->bufInfo.ulSize = pCustBuf->ulSize;
                            pNext2Comp->pInPort->bufInfo.ulBufBias = pComp->MemoryInfo->ulBufBias;
                            if (pNext2Comp->pfEmptyBuffer) {
                                pNext2Comp->pfEmptyBuffer(pNext2Comp, ulSize, BufInfo);
                            }
                        }
                        else {
                            if (pChComp == pCompSCL1[0]) {
                                SCLDMA2_BufferCfg[actid].ubBufUsage--;
                                if (SCLDMA2_BufferCfg[actid].ubBufUsage == 0) {
                                    _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                                }
                            }
                            else {
                                SCLDMA2_BufferCfg[actid].ubBufUsage1--;
                                if (SCLDMA2_BufferCfg[actid].ubBufUsage1 == 0) {
                                    _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                                }
                            }
                        }
                    }
                    else {
                        pNextComp->pInPort->bufInfo.ulBufAddr     = pCustBuf->ulBufAddr;
                        pNextComp->pInPort->bufInfo.u64BufPhyAddr = pCustBuf->u64BufPhyAddr;
                        pNextComp->pInPort->bufInfo.ulBufAddr1 = pNextComp->pInPort->bufInfo.ulBufAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                        pNextComp->pInPort->bufInfo.u64BufPhyAddr1 = pNextComp->pInPort->bufInfo.u64BufPhyAddr + (pSCL->stOutRect.ulW * pSCL->stOutRect.ulH);
                        pNextComp->pInPort->bufInfo.ulTime = pCustBuf->ulTime;
                        pNextComp->pInPort->bufInfo.ulSize = pCustBuf->ulSize;
                        pNextComp->pInPort->bufInfo.ulBufBias = pComp->MemoryInfo->ulBufBias;
                        if (pNextComp->pfEmptyBuffer) {
                            pNextComp->pfEmptyBuffer(pNextComp, ulSize, BufInfo);
                        }
                    }
                }
                else {
                    if (pChComp == pCompSCL1[0]) {
                        SCLDMA2_BufferCfg[actid].ubBufUsage--;
                        if (SCLDMA2_BufferCfg[actid].ubBufUsage == 0) {
                            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                        }
                    }
                    else {
                        SCLDMA2_BufferCfg[actid].ubBufUsage1--;
                        if (SCLDMA2_BufferCfg[actid].ubBufUsage1 == 0) {
                            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
                        }
                    }
                }
            }
        }
        else {

            // Minus buffer usage for current component.
            pComp->BufferInfo[ubIndex].bufctl.frm.ubBufUsage = 0;

            actid = GetSCLDMABufferId(E_DRV_ID_SCLDMA2, pCustBuf->ulBufAddr);
            if(actid == 0xff){
                UartSendTrace(FG_RED( "%s get actid error #%d!\n"),__FUNCTION__,__LINE__);
                //return MMP_COMPONENT_ERR_USAGE_ID;
            }
            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
        }
    }

    return MMP_ERR_NONE;
}
static MMP_ERR MMP_CompSCL0Ctl_EmptyBufferDone(void *pHandle, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)pHandle;
    u32                             ulAddr = pComp->pInPort->bufInfo.ulBufAddr;
    u8                              actid = 0;
    MMP_BOOL                        bBufOrdering = 0;
    MMP_COMPONENT_BASE              *pSCLComp = pComp->pInPort->PrevComponent;

    bBufOrdering = pSCLComp->MemoryInfo->ulBufOrderInfo.bBurOder;
    if (bBufOrdering) {
        ulAddr = orderBufferInfo[gubSCL0CurRIdx].ulBufAddr;
    }

    actid = GetSCLDMABufferId(E_DRV_ID_SCLDMA1, ulAddr);
    if(actid == 0xff){
        UartSendTrace(FG_RED( "%s get actid error #%d!\n"),__FUNCTION__,__LINE__);
        return MMP_COMPONENT_ERR_USAGE_ID;
    }

    if (SCLDMA1_BufferCfg[actid].ubCH == 0) {
        if (bBufOrdering) {
            if (SCLDMA1_BufferOrderCfg[gubSCL0CurRIdx].ubBufOrderUsage > 0) {
                SCLDMA1_BufferOrderCfg[gubSCL0CurRIdx].ubBufOrderUsage --;
            }
            else {
                //MMP_COMPONENT_BUFFER_INFO       *pCustBuf = BufInfo;
                UartSendTrace("ERROR: SCL 0 Order pre->cur=%s->%s,actid %x,RIdx %d,WIdx %d,ulAddr=0x%x\n",pSCLComp->name,pComp->name,actid,gubSCL0CurRIdx,gubSCL0CurWIdx,ulAddr);
                UartSendTrace("INFO: SCLDMA1_BufferCfg[%x], %x,%x,%x,%x,0\n", 0,SCLDMA1_BufferCfg[0].address,SCLDMA1_BufferCfg[0].index,SCLDMA1_BufferCfg[0].ubBufUsage,SCLDMA1_BufferCfg[0].ubBufUsage1);
                UartSendTrace("INFO: SCLDMA1_BufferCfg[%x], %x,%x,%x,%x,0\n", 1,SCLDMA1_BufferCfg[1].address,SCLDMA1_BufferCfg[1].index,SCLDMA1_BufferCfg[1].ubBufUsage,SCLDMA1_BufferCfg[1].ubBufUsage1);
                UartSendTrace("INFO: SCLDMA1_BufferCfg[%x], %x,%x,%x,%x,0\n", 2,SCLDMA1_BufferCfg[2].address,SCLDMA1_BufferCfg[2].index,SCLDMA1_BufferCfg[2].ubBufUsage,SCLDMA1_BufferCfg[2].ubBufUsage1);
                UartSendTrace("INFO: SCLDMA1_BufferCfg[%x], %x,%x,%x,%x,0\n", 3,SCLDMA1_BufferCfg[3].address,SCLDMA1_BufferCfg[3].index,SCLDMA1_BufferCfg[3].ubBufUsage,SCLDMA1_BufferCfg[3].ubBufUsage1);
                UartSendTrace("INFO: SCLDMA1_BufferOrderCfg[%x], %x,%x\n", 0,SCLDMA1_BufferOrderCfg[0].ubBufOrderUsage,SCLDMA1_BufferOrderCfg[0].ubCurBufOrder);
                UartSendTrace("INFO: SCLDMA1_BufferOrderCfg[%x], %x,%x\n", 1,SCLDMA1_BufferOrderCfg[1].ubBufOrderUsage,SCLDMA1_BufferOrderCfg[1].ubCurBufOrder);
                UartSendTrace("INFO: SCLDMA1_BufferOrderCfg[%x], %x,%x\n", 2,SCLDMA1_BufferOrderCfg[2].ubBufOrderUsage,SCLDMA1_BufferOrderCfg[2].ubCurBufOrder);
                UartSendTrace("INFO: SCLDMA1_BufferOrderCfg[%x], %x,%x\n", 3,SCLDMA1_BufferOrderCfg[3].ubBufOrderUsage,SCLDMA1_BufferOrderCfg[3].ubCurBufOrder);
                UartSendTrace("INFO: orderBufferInfo %x, %x, %x, %x\n", orderBufferInfo[0].ulBufAddr,orderBufferInfo[1].ulBufAddr,orderBufferInfo[2].ulBufAddr,orderBufferInfo[3].ulBufAddr);
            }
        }

        if (SCLDMA1_BufferCfg[actid].ubBufUsage > 0)
        	SCLDMA1_BufferCfg[actid].ubBufUsage--;

        if (SCLDMA1_BufferCfg[actid].ubBufUsage == 0) {
            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA1, E_DRV_SCLDMA_IO_MEM_FRM, actid);
            SCL0_Adj_CurRIdx(bBufOrdering,MMP_TRUE);
        }
        else {
            if (bBufOrdering) {
                if ((SCLDMA1_BufferOrderCfg[gubSCL0CurRIdx].ubBufOrderUsage == 0) &&
                     SCLDMA1_BufferCfg[actid].ubBufUsage) {
                    pSCLComp->StoreDoneFunc.pfEmptyOrderBuffer((void *)pSCLComp, ulSize, BufInfo);
                }
            }
        }
    }
    else {
        if(SCLDMA1_BufferCfg[actid].ubBufUsage1)
            SCLDMA1_BufferCfg[actid].ubBufUsage1--;

        if (SCLDMA1_BufferCfg[actid].ubBufUsage1 == 0) {
            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA1, E_DRV_SCLDMA_IO_MEM_FRM, actid);
            SCL0_Adj_CurRIdx(bBufOrdering,MMP_TRUE);
        }
    }
    return MMP_ERR_NONE;
}

static MMP_ERR MMP_CompSCL1Ctl_EmptyBufferDone(void *pHandle, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)pHandle;
    u32                             ulAddr = pComp->pInPort->bufInfo.ulBufAddr;
    u8                              actid = 0;

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        actid = GetSCLDMABufferId(E_DRV_ID_SCLDMA2, ulAddr);
        if(actid == 0xff){
            UartSendTrace(FG_RED( "%s get actid error #%d!\n"),__FUNCTION__,__LINE__);
            //return MMP_COMPONENT_ERR_USAGE_ID;
        }

        if (SCLDMA2_BufferCfg[actid].ubBufUsage > 0)
            SCLDMA2_BufferCfg[actid].ubBufUsage --;
        if (SCLDMA2_BufferCfg[actid].ubBufUsage == 0) {
            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2, E_DRV_SCLDMA_IO_MEM_FRM, actid);
        }
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    actid = GetSCLDMABufferId(E_DRV_ID_SCLDMA2, ulAddr);
    if(actid == 0xff){
        UartSendTrace(FG_RED( "%s get actid error #%d!\n"),__FUNCTION__,__LINE__);
        return MMP_COMPONENT_ERR_USAGE_ID;
    }

    if (SCLDMA2_BufferCfg[actid].ubCH == 0) {
        SCLDMA2_BufferCfg[actid].ubBufUsage--;
        if (SCLDMA2_BufferCfg[actid].ubBufUsage == 0) {
            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2,E_DRV_SCLDMA_IO_MEM_FRM/*pSCL->enMem*/,actid);
        }
    }
    else {
        SCLDMA2_BufferCfg[actid].ubBufUsage1--;
        if (SCLDMA2_BufferCfg[actid].ubBufUsage1 == 0) {
            _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2,E_DRV_SCLDMA_IO_MEM_FRM/*pSCL->enMem*/,actid);
        }
    }

    return MMP_ERR_NONE;
}

static short Get_SCLPoll(int *enId)
{
    DrvSclDmaIoPollConfig_t   stPoll;
    short bpoll = 0;
    u8 u8CompVal =0;

    stPoll.pfnCb = NULL;
    stPoll.u32Timeout = 500;
    stPoll.u8pollval = POLLIN|POLLPRI|POLLERR;

    if (*enId == g_SCLFD[E_DRV_ID_SCLDMA4])
    {
        stPoll.u8pollval |= 0x4;
    }

    stPoll.u8retval = 0;

    if (!DrvSclDmaIoPoll(*enId,&stPoll))
    {
        if (stPoll.u8retval & (0x1|0x2|0x8|0x4))
        {
            if (DrvEfuse_Func4()) {
                u8CompVal = 0x2|0x4;
            }
            else {
                u8CompVal = 0x2|0x8|0x4;
            }
            if (stPoll.u8retval & (u8CompVal)) {
               sclprintf("[SCL] Revent %d\n", stPoll.u8retval);
            }

            bpoll = stPoll.u8retval;
        }
    }
    else {
        bpoll = 0xAA; // Special value for poll time out
    }
    return bpoll;
}

static void SCL_ISP_Input(u16 Width,u16 Height)
{
    DrvSclHvspIoMiscConfig_t stHvspMiscCfg;
    u8 input_tgen_buf[] =
    {
        0x18, 0x12, 0x88, 0x20, 0xFF,
        0x18, 0x12, 0x89, 0x0C, 0xFF,
        0x18, 0x12, 0x86, 0x02, 0xFF,
        0x18, 0x12, 0xE0, 0x00, 0xFF,
    };

    stHvspMiscCfg.u8Cmd = 0;
    stHvspMiscCfg.u32Size = sizeof(input_tgen_buf);
    stHvspMiscCfg.u32Addr = (u32)input_tgen_buf;
    DrvSclHvspIoSetMiscConfig(g_SCLFD[E_DRV_ID_HVSP1], &stHvspMiscCfg);
}

void SCL0_SetCurComponent(u16 CompID)
{
    pCurCompSCL0 = pCompSCL0[CompID];
}

void SCL1_SetCurComponent(u16 CompID)
{
    pCurCompSCL1 = pCompSCL1[CompID];
}

void SCL_SetCMDQUse(bool bCMDQUse)
{
    if (bCMDQUse)
        DrvSclOsSetVipSetRule(VIPDEFAULTSETRULE);
    else
        DrvSclOsSetVipSetRule(E_DRV_SCLOS_VIPSETRUle_DEFAULT);
}

bool SCL0_GetMCNREn(u16 CompID)
{
    MMP_COMPONENT_HANDLER_SCL0 *pSCL = (MMP_COMPONENT_HANDLER_SCL0 *)&Component_SCL0_Handler[CompID];

    return pSCL->bMCNR;
}

bool SCL0_GetCIIREn(u16 CompID)
{
    MMP_COMPONENT_HANDLER_SCL0 *pSCL = (MMP_COMPONENT_HANDLER_SCL0 *)&Component_SCL0_Handler[CompID];

    return pSCL->bCIIR;
}

bool SCL0_GetLDCEn(u16 CompID)
{
    MMP_COMPONENT_HANDLER_SCL0 *pSCL = (MMP_COMPONENT_HANDLER_SCL0 *)&Component_SCL0_Handler[CompID];

    return pSCL->bLDC;
}

#if 0
void _____SCL0_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : Component_SCL0_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_SCL0_InitDevice(void *handler)
{
    // Tune for "ISP FIFO FULL". TBD
    #if (DIP_ROTATE_ENHANCE)
    *(volatile unsigned short *)0x1F20289C = (DrvPM_GetChipID() == CHIP_ID_M5U)? 0x8A : 0x8B;
    #else
    *(volatile unsigned short *)0x1F20289C = 0x8B;
    #endif
    // Group Limit Mask
    *(volatile unsigned short *)0x1F2028B8 = 0;
    // Client limit mask
    *(volatile unsigned short *)0x1F202C38 = 0;
    *(volatile unsigned short *)0x1F202CB8 = 0;
    *(volatile unsigned short *)0x1F202D38 = 0;
    *(volatile unsigned short *)0x1F202DB8 = 0;

    *(volatile unsigned short *)0x1F202C00 = 0x0404;
    *(volatile unsigned short *)0x1F202C80 = 0x0404;
    *(volatile unsigned short *)0x1F202D00 = 0x0404;
    *(volatile unsigned short *)0x1F202D80 = 0x0404;
    // Test DIP client burst to 8
   //  *(volatile unsigned short *)0x1F202C48 &= ~0x30;

    // *(volatile unsigned short *)0x1F202C48 |= 0x10;

    *(volatile unsigned short *)0x1F2028C0 = 0x2010;
    // Add SCL DNR client task priority
    *(volatile unsigned short *)0x1F2028C4 = 0x2040;
    *(volatile unsigned short *)0x1F2028C8 &= ~0xFF;
    *(volatile unsigned short *)0x1F2028C8 |= 0xE4;

    // Add some designer comment setting
    *(volatile unsigned short *)0x1F2028B8 = 0;
    *(volatile unsigned short *)0x1F2028DC &= ~0xFF;
    *(volatile unsigned short *)0x1F2028DC |= 0xA;
    *(volatile unsigned short *)0x1F2028E8 &= 0xFF00;
    *(volatile unsigned short *)0x1F202240 = 0x8020;
    *(volatile unsigned short *)0x1F202244 = 0x0810;
    *(volatile unsigned short *)0x1F202248 = 0x2008;
    *(volatile unsigned short *)0x1F202260 &= 0xFF00;
    *(volatile unsigned short *)0x1F202260 |= 0xE7;
    *(volatile unsigned short *)0x1F2023C4 |= 0xFF;
    *(volatile unsigned short *)0x1F202714 = 0x0300;

    // Add group 0 client limit mask and tune priority for MVOP ISSUE [TBD]
    *(volatile unsigned short *)0x1F202C40 = 0x1004;
    *(volatile unsigned short *)0x1F202C30 = 0xF033;
    *(volatile unsigned short *)0x1F202C38 = 0x0;
    *(volatile unsigned short *)0x1F202C48 = 0xFCC;
    *(volatile unsigned short *)0x1F202C4C = 0x33;

    //MIU_Adjust_FrontCamFHD_RearCamHD_PanelHD: Issue1: Panel flash. Issue2: ISP_FIFO_FULL.
    //Bank 0x1011
    (*(volatile U16*)(0x1f000000 + (0x1011 * 0x200) + (0x11 * 4))) = 0x04C0; //0x04FF; //0x0810;
    //Bank 0x1014
    (*(volatile U16*)(0x1f000000 + (0x1014 * 0x200) + (0x30 * 4))) = 0x2040; //0x1040; //0x0840; //0x2010;
    (*(volatile U16*)(0x1f000000 + (0x1014 * 0x200) + (0x31 * 4))) = 0x2080; //0x2040;
    //Bank 0x1016
    (*(volatile U16*)(0x1f000000 + (0x1016 * 0x200) + (0x10 * 4))) = 0x2004; //0x1004; //Group0/max1 only for REQ2(DIP). DIP_R:max =0x04, DIP_S:max =0x20.
    (*(volatile U16*)(0x1f000000 + (0x1016 * 0x200) + (0x12 * 4))) = 0x0FDC; //0x0FCC;
    (*(volatile U16*)(0x1f000000 + (0x1016 * 0x200) + (0x4C * 4))) = 0xFFFE; //0xFFFF;
    (*(volatile U16*)(0x1f000000 + (0x1016 * 0x200) + (0x51 * 4))) = 0x8020; //0x4020;
    (*(volatile U16*)(0x1f000000 + (0x1016 * 0x200) + (0x52 * 4))) = 0xAA0B; //0xAAAA;

    if (InitSCLDevice() == MMP_FALSE)
       return MMP_SCALER_ERR_PARAMETER;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_SCL0_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_SCL0_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

MMP_ERR Component_SCL0_PRM_OpenDevice(void *handler)
{
    MMP_COMPONENT_BASE         *pComp       = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_SCL0 *pSCL        = (MMP_COMPONENT_HANDLER_SCL0 *)&Component_SCL0_Handler[0];
    MMP_COMPONENT_BUFFER_INFO  *pBuf        = pComp->BufferInfo;
    SCL_COMP_RECT               *pInRect    = &pSCL->stInRect;
    SCL_COMP_RECT               *pOutRect   = &pSCL->stOutRect;
    MMP_BOOL                    bCropEn     = pSCL->bCropEn;
    MMP_BOOL                    bLFEn       = pSCL->bLineOffsetEn;
    DrvSclDmaClientType_e       enClient    = pSCL->enClient;
    DrvSclHvspIoWindowConfig_t  stCropWin   = pSCL->stCropWin;
    DrvSclDmaIoBufferModeType_e enBufferMd  = pSCL->enBufferMd;
    DrvSclDmaIoColorType_e      enColor     = pSCL->enColor;
    DrvSclDmaIoMemType_e        enMem       = pSCL->enMem;
    DrvSclHvspIoSrcType_e       enSrc       = pSCL->enSrc;
    OSDConfigInfo               sclOsdCfg   = pSCL->stOsdInfo;
    u16                         bufferNum   = pSCL->u16BufNumber;
    u16                         LineOffsetNum = pSCL->u16LineOffset;

    DrvSclHvspIoScalingConfig_t stHvspScaleCfg;
    DrvSclHvspIoInputConfig_t   stHvspInCfg;
    DrvSclDmaIoTriggerConfig_t  stSCLDMATrigCfg;
    DrvSclDmaIoBufferConfig_t   stSCLDMACfg;
    DrvSclHvspIoPollConfig_t    stHvspPollCfg;
    DrvSclHvspIoSetFbManageConfig_t stHvspFBCfg;
    u32                         buffsize;
    u32                         idx;

    COMPONENT_SCL_DBG_MSG(0, "OpenSCL0 In[%d][%d][%d][%d]\r\n", pInRect->ulX, pInRect->ulY, pInRect->ulW, pInRect->ulH);
    COMPONENT_SCL_DBG_MSG(0, "OpenSCL0 Out[%d][%d][%d][%d]\r\n", pOutRect->ulX, pOutRect->ulY, pOutRect->ulW, pOutRect->ulH);

    pCompSCL0[SCL0_COMP_PRM_CAM] = pComp;

    if (OpenSCLDevice(E_DRV_ID_HVSP1) == 0) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if (OpenSCLDevice(E_DRV_ID_SCLDMA1) == 0) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if (enSrc == E_DRV_SCLHVSP_IO_SRC_ISP) {
        SCL_ISP_Input(pInRect->ulW, pInRect->ulH);
    }

    //if (DrvEfuse_Func4()) {
        //DrvSclHvspIoSetCiirConfig(g_SCLFD[E_DRV_ID_HVSP1],0);
        //MDrvSclHvspSetIpmChannel(0);
        //Request_IPM(0, pInRect->ulW,pInRect->ulH);
        // NOP
    //}
    //else
    {
        if (pSCL->bMCNR) {
            // HVSP1 Requenst IPM memory
            MDrvSclHvspSetIpmChannel(0);
            DrvSclHvspIoSetCiirConfig(g_SCLFD[E_DRV_ID_HVSP1],pSCL->bCIIR);
            Request_IPM(0, pInRect->ulW,pInRect->ulH);
        }
    }

    // ====== HVSP1 scaling configure =====
    memset(&stHvspInCfg, 0, sizeof(DrvSclHvspIoInputConfig_t));
    stHvspInCfg.stCaptureWin.u16X = 0;
    stHvspInCfg.stCaptureWin.u16Y = 0;
    stHvspInCfg.stCaptureWin.u16Width = pInRect->ulW;
    stHvspInCfg.stCaptureWin.u16Height = pInRect->ulH;
    stHvspInCfg.enSrcType = enSrc;
    stHvspInCfg = FILL_VERCHK_TYPE(stHvspInCfg, stHvspInCfg.VerChk_Version, stHvspInCfg.VerChk_Size, DRV_SCLHVSP_VERSION);
    DrvSclHvspIoSetInputConfig(g_SCLFD[E_DRV_ID_HVSP1], &stHvspInCfg);

    if (pSCL->bLDC == 0) {
        //LDC off
        memset(&stHvspFBCfg, 0, sizeof(DrvSclHvspIoSetFbManageConfig_t));
        stHvspFBCfg.enSet |= E_DRV_SCLHVSP_IO_FBMG_SET_LDCPATH_OFF;
        stHvspFBCfg = FILL_VERCHK_TYPE(stHvspFBCfg, stHvspFBCfg.VerChk_Version, stHvspFBCfg.VerChk_Size, DRV_SCLHVSP_VERSION);
        DrvSclHvspIoSetFbConfig(g_SCLFD[E_DRV_ID_HVSP1], &stHvspFBCfg);
    }

    memset(&stHvspScaleCfg, 0, sizeof(DrvSclHvspIoScalingConfig_t));
    // Set HVSP1 Input/Output Width?BHeight
    stHvspScaleCfg.u16Src_Width  = pInRect->ulW;
    stHvspScaleCfg.u16Src_Height = pInRect->ulH;
    stHvspScaleCfg.u16Dsp_Width  = pOutRect->ulW;
    stHvspScaleCfg.u16Dsp_Height = pOutRect->ulH;

    // Set Crop Window
    stHvspScaleCfg.bCropEn = bCropEn;
    stHvspScaleCfg.stCropWin.u16X      = stCropWin.u16X;
    stHvspScaleCfg.stCropWin.u16Y      = stCropWin.u16Y;
    stHvspScaleCfg.stCropWin.u16Width  = stCropWin.u16Width;
    stHvspScaleCfg.stCropWin.u16Height = stCropWin.u16Height;
    stHvspScaleCfg = FILL_VERCHK_TYPE(stHvspScaleCfg, stHvspScaleCfg.VerChk_Version,
    stHvspScaleCfg.VerChk_Size,DRV_SCLHVSP_VERSION);
    DrvSclHvspIoSetScalingConfig(g_SCLFD[E_DRV_ID_HVSP1], &stHvspScaleCfg);

    // LineOffset
    if (bLFEn) {
       DrvSclDmaSetLineOffsetEn(enClient, bLFEn);
       if (!DrvSclDmaSetYLineOffsetConfig(enClient, LineOffsetNum))
          return MMP_SCALER_ERR_LINEOFFSETNUM;
       if (enColor == E_DRV_SCLDMA_IO_COLOR_YUV422)
          if (!DrvSclDmaSetCLineOffsetConfig(enClient, LineOffsetNum))
             return MMP_SCALER_ERR_LINEOFFSETNUM;
       else if (enColor == E_DRV_SCLDMA_IO_COLOR_YUV420)
          if (!DrvSclDmaSetCLineOffsetConfig(enClient, LineOffsetNum >> 1))
             return MMP_SCALER_ERR_LINEOFFSETNUM;
    }

    // Set OSD
    DrvSclHvspIoOsdConfig_t stOsdCfg;
    stOsdCfg.bEn        = sclOsdCfg.bEn;
    stOsdCfg.enOSD_loc  = sclOsdCfg.enOSD_loc;
    stOsdCfg.bOSDBypass = sclOsdCfg.bOSDBypass;
    stOsdCfg.bWTMBypass = sclOsdCfg.bWTMBypass;

    stOsdCfg = FILL_VERCHK_TYPE(stOsdCfg, stOsdCfg.VerChk_Version, stOsdCfg.VerChk_Size, DRV_SCLHVSP_VERSION);
    //if (DrvSclHvspIoSetOsdConfig(g_SCLFD[E_DRV_ID_HVSP1], &stOsdCfg) != E_DRV_SCLHVSP_IO_ERR_OK)
    //{
    //    sclprintf("%s %d, DrvSclHvspIoSetOsdConfig fail\n", __FUNCTION__, __LINE__);
    //}

    // Set SCLDMA1
    SCL0_cfg.u16Src_Width  = stCropWin.u16Width;
    SCL0_cfg.u16Src_Height = stCropWin.u16Height;
    SCL0_cfg.u16Dsp_Width  = pOutRect->ulW;
    SCL0_cfg.u16Dsp_Height = pOutRect->ulH;
    SCL0_cfg.enBufferMd    = enBufferMd;
    SCL0_cfg.u16BufNumber  = bufferNum;
    SCL0_cfg.enColor       = enColor;
    SCL0_cfg.enMem         = enMem;
    SCL0_cfg.enSrc         = enSrc;
    SCL0_cfg.u16Dsp_Height_Off = pSCL->u16LineBias;

    buffsize = SCL0_cfg.u16Dsp_Width*(SCL0_cfg.u16Dsp_Height + SCL0_cfg.u16Dsp_Height_Off);
    // Set Buffer Address
    stSCLDMACfg = SetBufferConfig(E_DRV_ID_SCLDMA1,SCL0_cfg,(u32)MsVA2PA(pBuf[0].ulBufAddr),0);

    _SetSCLBufferRPoint(E_DRV_ID_SCLDMA1,SCL0_cfg.enMem,0x5);

    // Enable SCLDMA1 DMA
    stSCLDMATrigCfg.bEn = 1;
    stSCLDMATrigCfg.enMemType = enMem;
    stSCLDMATrigCfg = FILL_VERCHK_TYPE( stSCLDMATrigCfg,
                                        stSCLDMATrigCfg.VerChk_Version,
                                        stSCLDMATrigCfg.VerChk_Size,DRV_SCLDMA_VERSION);

    DrvSclDmaIoSetOutTriggerConfig(g_SCLFD[E_DRV_ID_SCLDMA1], &stSCLDMATrigCfg);

    {
        // trig SCLDMA1
        _SetSCLDMATrig(E_DRV_ID_SCLDMA1,SCL0_cfg.enMem,1);
        _SetSCLDMATrig(E_DRV_ID_SCLDMA1,E_DRV_SCLDMA_IO_MEM_IMI,1);

        // Set fclk1 t0 288MHz
        // W2BYTEMSK(REG_SCL_CLK_64_L,0x14,0x001F);

        stScl0dmaPollCfg.bEn = 1;
        stScl0dmaPollCfg.bswitchpnl = 1;
        stScl0dmaPollCfg.stGetActCfg.enMem[0]= SCL0_cfg.enMem;
        stScl0dmaPollCfg.stGetActCfg.enID[0] = E_DRV_ID_SCLDMA1;
        stScl0dmaPollCfg.stGetActCfg.Count   = pComp->ubOutputPortNum;//1;
        stScl0dmaPollCfg.stSwapCfg.enColor   = SCL0_cfg.enColor;
        stScl0dmaPollCfg.stSwapCfg.enMem     = SCL0_cfg.enMem;
        stScl0dmaPollCfg.stSwapCfg.u16Height = SCL0_cfg.u16Dsp_Height;
        stScl0dmaPollCfg.stSwapCfg.u16Width  = SCL0_cfg.u16Dsp_Width;

        for (idx = 0; idx < SCL0_cfg.u16BufNumber; idx++)
        {
            if (stSCLDMACfg.enColorType == E_DRV_SCLDMA_IO_COLOR_YUV420)
            {
                stScl0dmaPollCfg.stSwapCfg.u32Base_Y[idx] = (u32)MsVA2PA(pBuf[0].ulBufAddr) + ((buffsize*3/2)*idx);
            }
            else
            {
                stScl0dmaPollCfg.stSwapCfg.u32Base_Y[idx] = (u32)MsVA2PA(pBuf[0].ulBufAddr) + ((buffsize*2)*idx);
            }

            SCLDMA1_BufferCfg[idx].address    = stScl0dmaPollCfg.stSwapCfg.u32Base_Y[idx];
            SCLDMA1_BufferCfg[idx].index      = idx;
            SCLDMA1_BufferCfg[idx].ubBufUsage = pComp->ubOutputPortNum;
            SCLDMA1_BufferCfg[idx].ubCH = 0;
        }
        stScl0dmaPollCfg.u16BufNumber = SCL0_cfg.u16BufNumber;
        startPollSCL0 = TRUE;
    }

    //stHvspPollCfg.u32Timeout = 500;
    //stHvspPollCfg.u8retval = POLLIN;
    //DrvSclHvspIoPoll(g_SCLFD[E_DRV_ID_HVSP1],&stHvspPollCfg);
    _SetSCLBufferRPoint(E_DRV_ID_SCLDMA1, SCL0_cfg.enMem, 0x5);

    SCL0_SetCurComponent(SCL0_COMP_PRM_CAM);

    if (pSCL->bMCNR) {
        DrvSclVipSetMCNR(1);
        DrvSclVipSetIpmCiirRW(pSCL->bMCNR, pSCL->bCIIR);
    }
    return MMP_ERR_NONE;
}

MMP_ERR Component_SCL0_PRM_CloseDevice(void *handler)
{
    MMP_COMPONENT_HANDLER_SCL0 *pSCL        = (MMP_COMPONENT_HANDLER_SCL0 *)&Component_SCL0_Handler[0];

    pCompSCL0[SCL0_COMP_PRM_CAM] = NULL;

    stScl0dmaPollCfg.bEn = 0;
    _SetSCLDMATrig(E_DRV_ID_SCLDMA1,SCL0_cfg.enMem,0);

    if (g_SCLFD[E_DRV_ID_HVSP1] != -1)
       CloseSCLDevice(E_DRV_ID_HVSP1);

    if (g_SCLFD[E_DRV_ID_SCLDMA1] != -1)
       CloseSCLDevice(E_DRV_ID_SCLDMA1);

    if (pSCL->bMCNR) {
        DrvSclVipSetMCNR(0);
    }

    Free_IPM(0);

    startPollSCL0 = FALSE;

    return MMP_ERR_NONE;
}

MMP_ERR Component_SCL0_SCD_OpenDevice(void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_SCL0 *pSCL        = (MMP_COMPONENT_HANDLER_SCL0 *)&Component_SCL0_Handler[1];
    SCL_COMP_RECT               *pInRect    = &pSCL->stInRect;
    DrvSclHvspIoSrcType_e       enSrc       = pSCL->enSrc;
    u32                         idx;

    pCompSCL0[SCL0_COMP_SCD_CAM] = pComp;

    if (enSrc == E_DRV_SCLHVSP_IO_SRC_ISP) {
        SCL_ISP_Input(pInRect->ulW, pInRect->ulH);
    }

    //if (DrvEfuse_Func4()) {
        // NOP
    //}
    //else
    {
        if (pSCL->bMCNR) {
            // HVSP1 Requenst IPM memory
            MDrvSclHvspSetIpmChannel(1);
            DrvSclHvspIoSetCiirConfig(g_SCLFD[E_DRV_ID_HVSP1],pSCL->bCIIR);
            Request_IPM(1, pInRect->ulW,pInRect->ulH);
        }
    }

    for (idx = 0; idx < SCL0_cfg.u16BufNumber; idx++) {
        SCLDMA1_BufferCfg[idx].ubBufUsage1 = pComp->ubOutputPortNum;
    }

    SCL0_SetCurComponent(SCL0_COMP_SCD_CAM);

    if (pSCL->bMCNR) {
        DrvSclVipSetMCNR(1);
    }

    return MMP_ERR_NONE;
}

MMP_ERR Component_SCL0_SCD_CloseDevice(void *handler)
{
    MMP_COMPONENT_HANDLER_SCL0 *pSCL        = (MMP_COMPONENT_HANDLER_SCL0 *)&Component_SCL0_Handler[1];

    pCompSCL0[SCL0_COMP_SCD_CAM] = NULL;

    if (pSCL->bMCNR) {
        DrvSclVipSetMCNR(0);
    }

    Free_IPM(1);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_SCL0_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_SCL0_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_SCL0  *pSCL0      = NULL;
    MMP_COMPONENT_MEMORY_INFO   *pSCL0Mem   = NULL;
    SCL_COMP_RECT               *pSCL0Rect  = NULL;

    if (strcmp("SCL0_PRM", pComp->name) == 0) {
        pSCL0      = &Component_SCL0_Handler[0];
        pSCL0Mem   = &Component_SCL0_Memory[0];
        pSCL0Rect  = &pSCL0->stInRect;
    }
    else if (strcmp("SCL0_SCD", pComp->name) == 0) {
        pSCL0      = &Component_SCL0_Handler[1];
        pSCL0Mem   = &Component_SCL0_Memory[1];
        pSCL0Rect  = &pSCL0->stInRect;
    }
    else {
        COMPONENT_SCL_DBG_ERR(1, "[%s] UnSupport SCL Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case SCL_COMP_PARAM_IN_RECT:
        pSCL0Rect = &pSCL0->stInRect;
        memcpy(pSCL0Rect, (SCL_COMP_RECT*)pParam, sizeof(SCL_COMP_RECT));
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update InRect [%d][%d][%d][%d]\r\n",
                              pComp->name, pSCL0Rect->ulX, pSCL0Rect->ulY, pSCL0Rect->ulW, pSCL0Rect->ulH);
        break;
    case SCL_COMP_PARAM_OUT_RECT:
        pSCL0Rect = &pSCL0->stOutRect;
        memcpy(pSCL0Rect, (SCL_COMP_RECT*)pParam, sizeof(SCL_COMP_RECT));
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update OutRect [%d][%d][%d][%d]\r\n",
                              pComp->name, pSCL0Rect->ulX, pSCL0Rect->ulY, pSCL0Rect->ulW, pSCL0Rect->ulH);
        break;
    case SCL_COMP_PARAM_BUF_COUNT:
        // pSCL0Mem->ubBufNum = *(MMP_UBYTE*)pParam;
        pSCL0->u16BufNumber = *(MMP_UBYTE*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update Buf Count [%d]\r\n", pComp->name, pSCL0->u16BufNumber);
        break;
    case SCL_COMP_PARAM_BUF_SIZE:
        pSCL0Mem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update Buf Size [%d]\r\n", pComp->name, pSCL0Mem->ulBufSize);
        break;
    case SCL_COMP_PARAM_MCNR_EN:
        pSCL0->bMCNR = *(MMP_BOOL*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update MCNR [%d]\r\n", pComp->name, pSCL0->bMCNR);
        break;
    case SCL_COMP_PARAM_CIIR_EN:
        pSCL0->bCIIR = *(MMP_BOOL*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update CIIR [%d]\r\n", pComp->name, pSCL0->bCIIR);
        break;
    case SCL_COMP_PARAM_LDC_EN:
        pSCL0->bLDC = *(MMP_BOOL*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update LDC [%d]\r\n", pComp->name, pSCL0->bLDC);
        break;
    case SCL_COMP_PARAM_LINE_BIAS:
        pSCL0->u16LineBias = *(MMP_USHORT*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update Line Bias [%d]\r\n", pComp->name, pSCL0->u16LineBias);
        break;
    case SCL_COMP_PARAM_BUF_BIAS:
        pSCL0Mem->ulBufBias = *(MMP_ULONG*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update Memory Bias [%d]\r\n", pComp->name, pSCL0Mem->ulBufBias);
        break;
    default:
        COMPONENT_SCL_DBG_ERR(1, "[%s] SetParamr UnSupport Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_SCL0_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_SCL0_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_SCL0  *pSCL0Dev   = (MMP_COMPONENT_HANDLER_SCL0*) pComp->DeviceInfo;

    if ((strcmp("SCL0_PRM", pComp->name) != 0)  &&
        (strcmp("SCL0_SCD", pComp->name) != 0)) {
        COMPONENT_SCL_DBG_ERR(1, "[%s] UnSupport SCL Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case SCL_COMP_PARAM_IN_RECT:
        memcpy((void*)pParam, (void*)&(pSCL0Dev->stInRect),sizeof(SCL_COMP_RECT));
        break;
    case SCL_COMP_PARAM_OUT_RECT:
        memcpy((void*)pParam, (void*)&(pSCL0Dev->stOutRect), sizeof(SCL_COMP_RECT));
        break;
    case SCL_COMP_PARAM_MCNR_EN:
        *(MMP_BOOL*)pParam = pSCL0Dev->bMCNR;
        break;
    case SCL_COMP_PARAM_CIIR_EN:
        *(MMP_BOOL*)pParam = pSCL0Dev->bCIIR;
        break;
    case SCL_COMP_PARAM_LDC_EN:
        *(MMP_BOOL*)pParam = pSCL0Dev->bLDC;
        break;
    case SCL_COMP_PARAM_LINE_BIAS:
        *(unsigned short *)pParam = pSCL0Dev->u16LineBias;
        break;
    default:
        COMPONENT_SCL_DBG_ERR(1, "[%s] SetParamr UnSupport Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}
MMP_ERR Component_SCL0_GetBufferInfo(void *handler, MMP_ULONG *ulBufNum, void *pBufInfo)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_SCL0      *pSCL0 = pComp->DeviceInfo;
    int i = 0;
    *ulBufNum = pSCL0->u16BufNumber;
    for (i = 0 ; i < *ulBufNum; i++) {
        *(unsigned long *)pBufInfo = SCLDMA1_BufferCfg[i].address;
        pBufInfo += 4;
    }
    return MMP_ERR_NONE;
}
#if 0
void _____SCL1_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : Component_SCL1_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_SCL1_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_SCL1_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_SCL1_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

MMP_ERR Component_SCL1_PRM_OpenDevice(void *handler)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_SCL1  *pSCL       = (MMP_COMPONENT_HANDLER_SCL1 *)&Component_SCL1_Handler[0];
    MMP_COMPONENT_BUFFER_INFO   *pBuf       = pComp->BufferInfo;
    SCL_COMP_RECT               *pInRect    = &pSCL->stInRect;
    SCL_COMP_RECT               *pOutRect   = &pSCL->stOutRect;
    MMP_BOOL                    bLFEn       = pSCL->bLineOffsetEn;
    DrvSclDmaClientType_e       enClient    = pSCL->enClient;
    DrvSclDmaIoBufferModeType_e enBufferMd  = pSCL->enBufferMd;
    DrvSclDmaIoColorType_e      enColor     = pSCL->enColor;
    DrvSclDmaIoMemType_e        enMem       = pSCL->enMem;
    DrvSclHvspIoSrcType_e       enSrc       = pSCL->enSrc;
    u16                         bufferNum     = pSCL->u16BufNumber;
    u16                         LineOffsetNum = pSCL->u16LineOffset;

    DrvSclHvspIoScalingConfig_t stHvspScaleCfg;
    DrvSclHvspIoInputConfig_t   stHvspInCfg;
    DrvSclDmaIoTriggerConfig_t  stSCLDMATrigCfg;
    DrvSclDmaIoBufferConfig_t   stSCLDMACfg;
    u32                         buffsize = 0;
    u32                         idx = 0;

    COMPONENT_SCL_DBG_MSG(0, "OpenSCL1 In[%d][%d][%d][%d]\r\n", pInRect->ulX, pInRect->ulY, pInRect->ulW, pInRect->ulH);
    COMPONENT_SCL_DBG_MSG(0, "OpenSCL1 Out[%d][%d][%d][%d]\r\n", pOutRect->ulX, pOutRect->ulY, pOutRect->ulW, pOutRect->ulH);

    pCompSCL1[SCL1_COMP_PRM_CAM] = pComp;

    // Check HVSP1&SCLDMA1 is open or not ?
    if (g_SCLFD[E_DRV_ID_HVSP1] == -1)
       sclprintf("Please open HVS1 before open HVSP2\r\n");

    if (g_SCLFD[E_DRV_ID_SCLDMA1] == -1)
       sclprintf("Please open SCLDMA1 before open SCLDMA2\r\n");

    if (OpenSCLDevice(E_DRV_ID_HVSP2) == 0) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if (OpenSCLDevice(E_DRV_ID_SCLDMA2) == 0) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    // ====== HVSP2 scaling configure =====
    memset(&stHvspInCfg, 0, sizeof(DrvSclHvspIoInputConfig_t));
    stHvspInCfg.stCaptureWin.u16X = 0;
    stHvspInCfg.stCaptureWin.u16Y = 0;
    stHvspInCfg.stCaptureWin.u16Width= pInRect->ulW;
    stHvspInCfg.stCaptureWin.u16Height= pInRect->ulH;
    stHvspInCfg.enSrcType = enSrc;
    stHvspInCfg = FILL_VERCHK_TYPE(stHvspInCfg, stHvspInCfg.VerChk_Version, stHvspInCfg.VerChk_Size,DRV_SCLHVSP_VERSION);
    DrvSclHvspIoSetInputConfig(g_SCLFD[E_DRV_ID_HVSP2], &stHvspInCfg);

     memset(&stHvspScaleCfg, 0, sizeof(DrvSclHvspIoScalingConfig_t));
    // Set HVSP2 Input/Output Width?BHeight
    stHvspScaleCfg.u16Src_Width  = pInRect->ulW;
    stHvspScaleCfg.u16Src_Height = pInRect->ulH;
    stHvspScaleCfg.u16Dsp_Width  = pOutRect->ulW;
    stHvspScaleCfg.u16Dsp_Height = pOutRect->ulH;
    stHvspScaleCfg = FILL_VERCHK_TYPE(stHvspScaleCfg, stHvspScaleCfg.VerChk_Version,
    stHvspScaleCfg.VerChk_Size,DRV_SCLHVSP_VERSION);

    DrvSclHvspIoSetScalingConfig(g_SCLFD[E_DRV_ID_HVSP2], &stHvspScaleCfg);

    // LineOffset
    if (bLFEn) {
       DrvSclDmaSetLineOffsetEn(enClient, bLFEn);

       if (!DrvSclDmaSetYLineOffsetConfig(enClient, LineOffsetNum))
          return MMP_SCALER_ERR_LINEOFFSETNUM;

       if (enColor == E_DRV_SCLDMA_IO_COLOR_YUV422)
          if (!DrvSclDmaSetCLineOffsetConfig(enClient, LineOffsetNum))
             return MMP_SCALER_ERR_LINEOFFSETNUM;
       else if (enColor == E_DRV_SCLDMA_IO_COLOR_YUV420)
          if (!DrvSclDmaSetCLineOffsetConfig(enClient, LineOffsetNum >> 1))
             return MMP_SCALER_ERR_LINEOFFSETNUM;
    }

    // Set SCLDMA2
    SCL1_cfg.u16Src_Width  = pInRect->ulW;
    SCL1_cfg.u16Src_Height = pInRect->ulH;
    SCL1_cfg.u16Dsp_Width  = pOutRect->ulW;
    SCL1_cfg.u16Dsp_Height = pOutRect->ulH;
    SCL1_cfg.enBufferMd = enBufferMd; //E_DRV_SCLDMA_IO_BUFFER_MD_RING;// enBufferMd : RING?BSINGLE?BSWRING
    SCL1_cfg.u16BufNumber = bufferNum;
    SCL1_cfg.enColor = enColor; // YUV422?BYUV420
    SCL1_cfg.enMem = enMem;  // E_DRV_SCLDMA_IO_MEM_FRM?BE_DRV_SCLDMA_IO_MEM_SNP
    SCL1_cfg.enSrc = enSrc;

    buffsize = SCL1_cfg.u16Dsp_Width*SCL1_cfg.u16Dsp_Height;

    // Set Buffer Address
    stSCLDMACfg = SetBufferConfig(E_DRV_ID_SCLDMA2,SCL1_cfg,(u32)MsVA2PA(pBuf[0].ulBufAddr),0);

    _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2,SCL1_cfg.enMem,0x5);

    // Enable SCLDMA2 DMA
    stSCLDMATrigCfg.bEn = 1;
    stSCLDMATrigCfg.enMemType = enMem;
    stSCLDMATrigCfg = FILL_VERCHK_TYPE(stSCLDMATrigCfg,
                                       stSCLDMATrigCfg.VerChk_Version,
                                       stSCLDMATrigCfg.VerChk_Size,DRV_SCLDMA_VERSION);

    DrvSclDmaIoSetOutTriggerConfig(g_SCLFD[E_DRV_ID_SCLDMA2], &stSCLDMATrigCfg);

    // Ring Mode Only
    {
        // trig SCLDMA1
        //_SetDMATrig(E_DRV_ID_SCLDMA1,E_DRV_SCLDMA_IO_MEM_IMI,1);
        _SetSCLDMATrig(E_DRV_ID_SCLDMA2,SCL1_cfg.enMem,1);
        // trig SCLDMA4
        //_SetDMAinTrig(E_DRV_ID_SCLDMA4,E_DRV_SCLDMA_IO_MEM_FRM,1);

        stScl1dmaPollCfg.bEn = 1;
        stScl1dmaPollCfg.bswitchpnl = 1;
        stScl1dmaPollCfg.stGetActCfg.enMem[0]= SCL1_cfg.enMem;
        stScl1dmaPollCfg.stGetActCfg.enID[0] = E_DRV_ID_SCLDMA2;
        stScl1dmaPollCfg.stGetActCfg.Count   = pComp->ubOutputPortNum;//1;
        stScl1dmaPollCfg.stSwapCfg.enColor   = SCL1_cfg.enColor;
        stScl1dmaPollCfg.stSwapCfg.enMem     = SCL1_cfg.enMem;
        stScl1dmaPollCfg.stSwapCfg.u16Height = SCL1_cfg.u16Dsp_Height;
        stScl1dmaPollCfg.stSwapCfg.u16Width  = SCL1_cfg.u16Dsp_Width;

        for (idx=0 ;idx < SCL1_cfg.u16BufNumber; idx++)
        {
            if (stSCLDMACfg.enColorType == E_DRV_SCLDMA_IO_COLOR_YUV420)
            {
                stScl1dmaPollCfg.stSwapCfg.u32Base_Y[idx] = (u32)MsVA2PA(pBuf[0].ulBufAddr) + ((buffsize*3/2)*idx);
            }
            else
            {
                stScl1dmaPollCfg.stSwapCfg.u32Base_Y[idx] = (u32)MsVA2PA(pBuf[0].ulBufAddr) + ((buffsize*2)*idx);
            }

            SCLDMA2_BufferCfg[idx].address    = stScl1dmaPollCfg.stSwapCfg.u32Base_Y[idx];
            SCLDMA2_BufferCfg[idx].index      = idx;
            SCLDMA2_BufferCfg[idx].ubBufUsage = pComp->ubOutputPortNum;
            SCLDMA2_BufferCfg[idx].ubCH = 0;
        }

        stScl1dmaPollCfg.u16BufNumber = SCL1_cfg.u16BufNumber;

        startPollSCL1 = TRUE;
    }

    _SetSCLBufferRPoint(E_DRV_ID_SCLDMA2,SCL1_cfg.enMem,0x5);

    SCL1_SetCurComponent(SCL1_COMP_PRM_CAM);
    return MMP_ERR_NONE;
}

MMP_ERR Component_SCL1_PRM_CloseDevice(void *handler)
{
    pCompSCL1[SCL1_COMP_PRM_CAM] = NULL;

    stScl1dmaPollCfg.bEn = 0;
    _SetSCLDMATrig(E_DRV_ID_SCLDMA2,SCL1_cfg.enMem,0);

    if (g_SCLFD[E_DRV_ID_HVSP2] != -1)
       CloseSCLDevice(E_DRV_ID_HVSP2);

    if (g_SCLFD[E_DRV_ID_SCLDMA2] != -1)
       CloseSCLDevice(E_DRV_ID_SCLDMA2);

    startPollSCL1 = FALSE;

    return MMP_ERR_NONE;
}

MMP_ERR Component_SCL1_SCD_OpenDevice(void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    u32                idx = 0;

    pCompSCL1[SCL1_COMP_SCD_CAM] = pComp;

    for (idx = 0; idx < SCL1_cfg.u16BufNumber; idx++) {
        SCLDMA2_BufferCfg[idx].ubBufUsage1 = pComp->ubOutputPortNum;
    }

    SCL1_SetCurComponent(SCL1_COMP_SCD_CAM);

    return MMP_ERR_NONE;
}

MMP_ERR Component_SCL1_SCD_CloseDevice(void *handler)
{
    pCompSCL1[SCL1_COMP_SCD_CAM] = NULL;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_SCL1_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_SCL1_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_SCL1  *pSCL1      = NULL;
    MMP_COMPONENT_MEMORY_INFO   *pSCL1Mem   = NULL;
    SCL_COMP_RECT               *pSCL1Rect  = NULL;

    if (strcmp("SCL1_PRM", pComp->name) == 0) {
        pSCL1      = &Component_SCL1_Handler[0];
        pSCL1Mem   = &Component_SCL1_Memory[0];
        pSCL1Rect = &pSCL1->stInRect;
    }
    else if (strcmp("SCL1_SCD", pComp->name) == 0) {
        pSCL1      = &Component_SCL1_Handler[1];
        pSCL1Mem   = &Component_SCL1_Memory[1];
        pSCL1Rect = &pSCL1->stInRect;
    }
    else {
        COMPONENT_SCL_DBG_ERR(1, "[%s] UnSupport SCL Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case SCL_COMP_PARAM_IN_RECT:
        pSCL1Rect = &pSCL1->stInRect;
        memcpy(pSCL1Rect, (SCL_COMP_RECT*)pParam, sizeof(SCL_COMP_RECT));
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update InRect [%d][%d][%d][%d]\r\n",
                              pComp->name, pSCL1Rect->ulX, pSCL1Rect->ulY, pSCL1Rect->ulW, pSCL1Rect->ulH);
        break;
    case SCL_COMP_PARAM_OUT_RECT:
        pSCL1Rect = &pSCL1->stOutRect;
        memcpy(pSCL1Rect, (SCL_COMP_RECT*)pParam, sizeof(SCL_COMP_RECT));
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update OutRect [%d][%d][%d][%d]\r\n",
                              pComp->name, pSCL1Rect->ulX, pSCL1Rect->ulY, pSCL1Rect->ulW, pSCL1Rect->ulH);
        break;
    case SCL_COMP_PARAM_BUF_COUNT:
        // pSCL1Mem->ubBufNum = *(MMP_UBYTE*)pParam;
        pSCL1->u16BufNumber = *(MMP_UBYTE*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update Buf Count [%d]\r\n", pComp->name, pSCL1->u16BufNumber);
        break;
    case SCL_COMP_PARAM_BUF_SIZE:
        pSCL1Mem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update Buf Size [%d]\r\n", pComp->name, pSCL1Mem->ulBufSize);
        break;
    case SCL_COMP_PARAM_LINE_BIAS:
        pSCL1->u16LineBias = *(MMP_USHORT*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update MFE OFFSET [%d]\r\n", pComp->name, pSCL1->u16LineBias);
        break;
    case SCL_COMP_PARAM_BUF_BIAS:
        pSCL1Mem->ulBufBias = *(MMP_ULONG*)pParam;
        COMPONENT_SCL_DBG_MSG(1, "[%s] Update Memory Bias [%d]\r\n", pComp->name, pSCL1Mem->ulBufBias);
        break;
    default:
        COMPONENT_SCL_DBG_ERR(1, "[%s] SetParamr Unsupport Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_SCL1_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_SCL1_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_SCL1  *pSCL1Dev   = (MMP_COMPONENT_HANDLER_SCL1*) pComp->DeviceInfo;

    if ((strcmp("SCL1_PRM", pComp->name) != 0)  &&
        (strcmp("SCL1_SCD", pComp->name) != 0)) {
        COMPONENT_SCL_DBG_ERR(1, "[%s] UnSupport SCL Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case SCL_COMP_PARAM_IN_RECT:
        memcpy((void*)pParam, (void*)&(pSCL1Dev->stInRect), sizeof(SCL_COMP_RECT));
        break;
    case SCL_COMP_PARAM_OUT_RECT:
        memcpy((void*)pParam, (void*)&(pSCL1Dev->stOutRect), sizeof(SCL_COMP_RECT));
        break;
    case SCL_COMP_PARAM_LINE_BIAS:
        *(unsigned short *)pParam = pSCL1Dev->u16LineBias;
        break;
    default:
        COMPONENT_SCL_DBG_ERR(1, "[%s] SetParamr UnSupport Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}
MMP_ERR Component_SCL1_GetBufferInfo(void *handler, MMP_ULONG *ulBufNum, void *pBufInfo)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_SCL1      *pSCL1 = pComp->DeviceInfo;
    int i = 0;
    *ulBufNum = pSCL1->u16BufNumber;
    for (i = 0 ; i < *ulBufNum; i++) {
        *(unsigned long *)pBufInfo = SCLDMA2_BufferCfg[i].address;
        pBufInfo += 4;
    }
    return MMP_ERR_NONE;
}

#if 0
void _____Task_Functions_____(){}
#endif

void SCLPoll_Task(void)
{
    DrvSclDmaIoActiveBufferConfig_t stSCLDMA1BFCfg;
    DrvSclDmaIoActiveBufferConfig_t stSCLDMA2BFCfg;
    MMP_COMPONENT_BUFFER_INFO       BufferInfo;
    int                             buffsize = 0;
    int                             err_SCLDMA1 = 0;
    int                             err_SCLDMA2 = 0;
    u8                              actid = 0;
    MMPF_OS_FLAGS                   flags = 0;
    MMPF_OS_FLAGS                   waitFlags = 0;

    waitFlags = SCL0_FLAG_FRM_ACTIVE | SCL1_FLAG_FRM_ACTIVE;

    while (1)
    {
        MMPF_OS_WaitFlags(SCL_POLL_Flag, waitFlags,
                          (MMPF_OS_FLAG_WAIT_SET_ANY | MMPF_OS_FLAG_CONSUME),
                          0, &flags);

        if (flags & SCL0_FLAG_FRM_ACTIVE) {

            buffsize = (stScl0dmaPollCfg.stSwapCfg.u16Width* stScl0dmaPollCfg.stSwapCfg.u16Height) ; // 2bpp
            err_SCLDMA1 = Get_SCLPoll(&g_SCLFD[stScl0dmaPollCfg.stGetActCfg.enID[0]]);
            if (err_SCLDMA1 != 0xAA)
            {
                if (err_SCLDMA1 & (POLLIN|POLLPRI|POLLERR))
                {
                    stSCLDMA1BFCfg = _GetSCLBufferRPoint(stScl0dmaPollCfg.stGetActCfg.enID[0],stScl0dmaPollCfg.stGetActCfg.enMem[0]);

                    actid = (stSCLDMA1BFCfg.u8ActiveBuffer & 0xF);

                    if (actid != 0xF) {
                        SCLDMA1_BufferCfg[actid].address    = GetSCLDMABufferAddress(E_DRV_ID_SCLDMA1,actid);
                        SCLDMA1_BufferCfg[actid].index      = actid;
                        SCLDMA1_BufferCfg[actid].ubBufUsage = stScl0dmaPollCfg.stGetActCfg.Count;

                        BufferInfo.ulBufAddr        = SCLDMA1_BufferCfg[actid].address;
                        BufferInfo.u64BufPhyAddr    = SCLDMA1_BufferCfg[actid].address;
                        BufferInfo.ulTime           = stSCLDMA1BFCfg.u64FRMDoneTime;
                        BufferInfo.ulSize           = buffsize*3/2;

                        //stSCLDMA1BFCfg = _SetSCLBufferRPoint
                        //        (pstScldmaPollCfg->stGetActCfg.enID[0],pstScldmaPollCfg->stGetActCfg.enMem[0],actid);
                        //sclprintf("Thread : err_SCLDMA1: %d, actid: %d, Addr = %X,ubBufUsage = %d\n", err_SCLDMA1,actid,BufferInfo.ulBufAddr,SCLDMA1_BufferCfg[actid].ubBufUsage);
                        //sclprintf("Thread : enID[0]: %d, enMem[0]: %d\n", pstScldmaPollCfg->stGetActCfg.enID[0],pstScldmaPollCfg->stGetActCfg.enMem[0]);
                        if ((err_SCLDMA1 & POLLERR) ||
                            (SCLDMA1_BufferCfg[actid].address == SCL_DUMMY_ADDRESS) ||
                            (SCLDMA1_BufferCfg[actid].ubBufUsage == 0)) {
                           stSCLDMA1BFCfg = _SetSCLBufferRPoint(stScl0dmaPollCfg.stGetActCfg.enID[0],stScl0dmaPollCfg.stGetActCfg.enMem[0],actid);
                        }
                        else {
                            MMP_CompCtl_StoreBufferDone((void *)pCurCompSCL0, 0, (void *)&BufferInfo);
                        }
                   }

                }
                else {
                    if (err_SCLDMA1 == 0) {
                       stSCLDMA1BFCfg = _GetSCLBufferRPoint(stScl0dmaPollCfg.stGetActCfg.enID[0],stScl0dmaPollCfg.stGetActCfg.enMem[0]);
                       actid = (stSCLDMA1BFCfg.u8ActiveBuffer&0xF);
                       stSCLDMA1BFCfg = _SetSCLBufferRPoint(stScl0dmaPollCfg.stGetActCfg.enID[0],stScl0dmaPollCfg.stGetActCfg.enMem[0],actid);
                    }
                }
            }
            else {
                if (startPollSCL0) {
                    COMPONENT_SCL_DBG_ERR(1, "SCL TIME OUT!!!!!\n");
                }
                stSCLDMA1BFCfg = _GetSCLBufferRPoint(stScl0dmaPollCfg.stGetActCfg.enID[0],stScl0dmaPollCfg.stGetActCfg.enMem[0]);
 			    actid = (stSCLDMA1BFCfg.u8ActiveBuffer&0xF);
			    stSCLDMA1BFCfg = _SetSCLBufferRPoint(stScl0dmaPollCfg.stGetActCfg.enID[0],stScl0dmaPollCfg.stGetActCfg.enMem[0],actid);
            }
        }
        if (flags & SCL1_FLAG_FRM_ACTIVE) {

            buffsize = (stScl1dmaPollCfg.stSwapCfg.u16Width* stScl1dmaPollCfg.stSwapCfg.u16Height) ; // 2bpp
            err_SCLDMA2 = Get_SCLPoll(&g_SCLFD[stScl1dmaPollCfg.stGetActCfg.enID[0]]);

            if (err_SCLDMA2 & (POLLIN|POLLPRI|POLLERR))
            {
                stSCLDMA2BFCfg = _GetSCLBufferRPoint(stScl1dmaPollCfg.stGetActCfg.enID[0],stScl1dmaPollCfg.stGetActCfg.enMem[0]);

                actid = (stSCLDMA2BFCfg.u8ActiveBuffer & 0xF);

                if (actid != 0xF) {
                    SCLDMA2_BufferCfg[actid].address    = GetSCLDMABufferAddress(E_DRV_ID_SCLDMA2,actid);
                    SCLDMA2_BufferCfg[actid].index      = actid;
                    SCLDMA2_BufferCfg[actid].ubBufUsage = stScl1dmaPollCfg.stGetActCfg.Count;

                    BufferInfo.ulBufAddr        = SCLDMA2_BufferCfg[actid].address;
                    BufferInfo.u64BufPhyAddr    = SCLDMA2_BufferCfg[actid].address;
                    BufferInfo.ulTime           = stSCLDMA2BFCfg.u64FRMDoneTime;
                    BufferInfo.ulSize           = buffsize*3/2;

                    //stSCLDMA1BFCfg = _SetSCLBufferRPoint
                    //        (pstScldmaPollCfg->stGetActCfg.enID[0],pstScldmaPollCfg->stGetActCfg.enMem[0],actid);
                    //sclprintf("Thread : err_SCLDMA1: %d, actid: %d, Addr = %X,ubBufUsage = %d\n", err_SCLDMA1,actid,BufferInfo.ulBufAddr,SCLDMA1_BufferCfg[actid].ubBufUsage);
                    //sclprintf("Thread : enID[0]: %d, enMem[0]: %d\n", pstScldmaPollCfg->stGetActCfg.enID[0],pstScldmaPollCfg->stGetActCfg.enMem[0]);
                    if ((err_SCLDMA2 & POLLERR) ||
                        (SCLDMA2_BufferCfg[actid].address == SCL_DUMMY_ADDRESS) ||
                        (SCLDMA2_BufferCfg[actid].ubBufUsage == 0)) {
                        stSCLDMA2BFCfg = _SetSCLBufferRPoint(stScl1dmaPollCfg.stGetActCfg.enID[0],stScl1dmaPollCfg.stGetActCfg.enMem[0],actid);
                    }
                    else {
                        MMP_CompCtl_StoreBufferDone((void *)pCurCompSCL1, 0, (void *)&BufferInfo);
                    }
                }
            }
            else {
                if (err_SCLDMA2 == 0) {
                   stSCLDMA2BFCfg = _GetSCLBufferRPoint(stScl1dmaPollCfg.stGetActCfg.enID[0],stScl1dmaPollCfg.stGetActCfg.enMem[0]);
                   actid = (stSCLDMA2BFCfg.u8ActiveBuffer&0xF);
                   stSCLDMA2BFCfg = _SetSCLBufferRPoint(stScl1dmaPollCfg.stGetActCfg.enID[0],stScl1dmaPollCfg.stGetActCfg.enMem[0],actid);
               }
            }
        }
    }
}
