////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MDRV_HVSP_H
#define _MDRV_HVSP_H



#define MDRV_HVSP_CROP_NUM  2
#define DNRBufferMode 1 // depend on DNR Buffer
#define IPMPATH
//-------------------------------------------------------------------------------------------------
//  Defines & Structure
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_MDRV_HVSP_ID_1,
    E_MDRV_HVSP_ID_2,
    E_MDRV_HVSP_ID_3,
    E_MDRV_HVSP_ID_MAX,     //I1 has 3 HVSP
}EN_MDRV_HVSP_ID_TYPE;
typedef enum
{
    E_MDRV_HVSP_SRC_ISP,       ///< input source: ISP
    E_MDRV_HVSP_SRC_BT656,     ///< input source: BT656
    E_MDRV_HVSP_SRC_DRAM,      ///< input source: DRAM
    E_MDRV_HVSP_SRC_HVSP,      ///< input source: HVSP1
    E_MDRV_HVSP_SRC_PAT_TGEN,  ///< input source: PATGEN
    E_MDRV_HVSP_SRC_NUM,       ///< The max number of input source
}EN_MDRV_HVSP_SRC_TYPE;

typedef enum
{
    E_MDRV_HVSP_COLOR_RGB,     ///< color format:RGB
    E_MDRV_HVSP_COLOR_YUV444,  ///< color format:YUV444
    E_MDRV_HVSP_COLOR_YUV422,  ///< color format:YUV422
    E_MDRV_HVSP_COLOR_YUV420,  ///< color format:YUV420
    E_MDRV_HVSP_COLOR_NUM,     ///< The max number of color format
}EN_MDRV_HVSP_COLOR_TYPE;

typedef enum
{
    E_MDRV_HVSP_MCNR_YCM_R  = 0x1,    ///< IP only read
    E_MDRV_HVSP_MCNR_YCM_W  = 0x2,    ///< IP only write
    E_MDRV_HVSP_MCNR_YCM_RW = 0x3,    ///< IP R/W
    E_MDRV_HVSP_MCNR_CIIR_R = 0x4,    ///< IP only read
    E_MDRV_HVSP_MCNR_CIIR_W = 0x8,    ///< IP only write
    E_MDRV_HVSP_MCNR_CIIR_RW = 0xC,    ///< IP R/W
    E_MDRV_HVSP_MCNR_NON = 0x10,    ///< IP none open
}EN_MDRV_HVSP_MCNR_TYPE;

typedef enum
{
    E_MDRV_HVSP_IPMPATH_R  = 0x1,    ///< IP only read
    E_MDRV_HVSP_IPMPATH_W  = 0x2,    ///< IP only write
    E_MDRV_HVSP_IPMPATH_RW = 0x3,    ///< IP R/W
    E_MDRV_HVSP_IPMPATH_NON = 0x10,    ///< IP none open
}EN_MDRV_HVSP_IPMPATH_TYPE;


typedef enum
{
    E_MDRV_HVSP_PAT_TGEN_TIMING_1920_1080_30,   // FHD PT GEN
    E_MDRV_HVSP_PAT_TGEN_TIMING_1024_768_60,    // HD PT gEN
    E_MDRV_HVSP_PAT_TGEN_TIMING_640_480_60,     // SD PT GEN
    E_MDRV_HVSP_PAT_TGEN_TIMING_UNDEFINED,      // random size
    E_MDRV_HVSP_PAT_TGEN_TIMING_MAX,            // 4type
}EN_MDRV_HVSP_PAT_TGEN_TIMING_TYPE;

typedef enum
{
    E_MDRV_HVSP_MISC_CMD_SET_REG = 0,

    E_MDRV_HVSP_MISC_CMD_MAX,           // MISC set 1 type
}EN_MDRV_HVSP_MISC_CMD_TYPE;

typedef enum
{
    EN_MDRV_HVSP_OSD_LOC_AFTER  = 0,    ///< after hvsp
    EN_MDRV_HVSP_OSD_LOC_BEFORE = 1,    ///< before hvsp
}EN_MDRV_HVSP_OSD_LOC_TYPE;

typedef enum
{
    EN_MDRV_HVSP_MONITOR_CROPCHECK  = 1,    ///< crop
    EN_MDRV_HVSP_MONITOR_DMA1FRMCHECK = 2,    ///< dma1frm
    EN_MDRV_HVSP_MONITOR_DMA1SNPCHECK = 3,    ///< dma1frm
    EN_MDRV_HVSP_MONITOR_DMA2FRMCHECK = 4,    ///< dma1frm
    EN_MDRV_HVSP_MONITOR_DMA3FRMCHECK = 5,    ///< dma1frm
}EN_MDRV_HVSP_MONITOR_TYPE;

typedef enum
{
    EN_MDRV_HVSP_CALLPATGEN_STATIC  = 0,    ///< crop
    EN_MDRV_HVSP_CALLPATGEN_DYNAMIC = 1,    ///< dma1frm
}EN_MDRV_HVSP_CALLPATGEN_TYPE;
typedef enum
{
    EN_MDRV_HVSP_FBMG_SET_LDCPATH_ON      = 0x1,
    EN_MDRV_HVSP_FBMG_SET_LDCPATH_OFF     = 0x2,
    EN_MDRV_HVSP_FBMG_SET_DNR_Read_ON     = 0x4,
    EN_MDRV_HVSP_FBMG_SET_DNR_Read_OFF    = 0x8,
    EN_MDRV_HVSP_FBMG_SET_DNR_Write_ON    = 0x10,
    EN_MDRV_HVSP_FBMG_SET_DNR_Write_OFF   = 0x20,
    EN_MDRV_HVSP_FBMG_SET_DNR_BUFFER_1    = 0x40,
    EN_MDRV_HVSP_FBMG_SET_DNR_BUFFER_2    = 0x80,
    EN_MDRV_HVSP_FBMG_SET_UNLOCK          = 0x100,
    EN_MDRV_HVSP_FBMG_SET_DNR_COMDE_ON    = 0x200,
    EN_MDRV_HVSP_FBMG_SET_DNR_COMDE_OFF   = 0x400,
    EN_MDRV_HVSP_FBMG_SET_DNR_COMDE_265OFF   = 0x800,
    EN_MDRV_HVSP_FBMG_SET_PRVCROP_ON      = 0x1000,
    EN_MDRV_HVSP_FBMG_SET_PRVCROP_OFF     = 0x2000,
}EN_MDRV_HVSP_FBMG_SET_TYPE;
typedef struct
{
    u16 u16X;        ///< crop frame start x point
    u16 u16Y;        ///< crop frame start y point
    u16 u16Width;    ///< crop width size
    u16 u16Height;   ///< crop height size
}ST_MDRV_HVSP_WINDOW_CONFIG;
typedef struct
{
    bool  bInterlace;      ///< is interlace or progressive
    u16 u16Htotal;       ///< Htt
    u16 u16Vtotal;       ///< Vtt
    u16 u16Vfrequency;   ///< Vfreq
}ST_MDRV_HVSPTIMING_CONFIG;

typedef struct
{
    u32 u32Riubase;
    u32 u32IRQNUM;//scl
    u32 u32CMDQIRQNUM;//cmdq
}ST_MDRV_HVSP_INIT_CONFIG;


typedef struct
{
    u32 u32IRQNum;
    u32 u32CMDQIRQNum;//cmdq
}ST_MDRV_HVSP_SUSPEND_RESUME_CONFIG;

typedef struct
{
    EN_MDRV_HVSP_MCNR_TYPE enRW;
    u32 u32YCPhyAddr;
    u32 u32MPhyAddr;
    u32 u32CIIRPhyAddr;
    u16 u16Width;
    u16 u16Height;
    u32  u32MemSize;
}ST_MDRV_HVSP_IPM_CONFIG;

typedef struct
{
    bool  bEn;
    u16 u16X;
    u16 u16Y;
    u16 u16Width;
    u16 u16Height;
}ST_MDRV_HVSP_CROP_WINDOW_CONFIG;
typedef struct
{
    void* idclk;
    void* fclk1;
    void* fclk2;
    void* odclk;
}ST_MDRV_HVSP_CLK_CONFIG;

typedef struct
{
    u16 u16Src_Width;
    u16 u16Src_Height;
    u16 u16Dsp_Width;
    u16 u16Dsp_Height;
    ST_MDRV_HVSP_CROP_WINDOW_CONFIG stCropWin;
    ST_MDRV_HVSP_CLK_CONFIG       *stclk;      ///< clk framework
}ST_MDRV_HVSP_SCALING_CONFIG;

typedef struct
{
    bool bOSDEn;    ///< OSD en
    bool bOSDBypass;    ///< OSD en
    bool bWTMBypass;    ///< OSD en
}ST_MDRV_HVSP_OSD_ONOFF_CONFIG;

typedef struct
{
    EN_MDRV_HVSP_OSD_LOC_TYPE enOSD_loc;    ///< OSD locate
    ST_MDRV_HVSP_OSD_ONOFF_CONFIG stOsdOnOff;
}ST_MDRV_HVSP_OSD_CONFIG;
typedef struct
{
    bool bMask; ///<Mask enable
    bool u8idx; ///<mask id
    ST_MDRV_HVSP_WINDOW_CONFIG stMaskWin;      ///< Mask info
}ST_MDRV_HVSP_PRIMASK_CONFIG;

typedef struct
{
    EN_MDRV_HVSP_SRC_TYPE        enSrcType;
    EN_MDRV_HVSP_COLOR_TYPE      enColor;
    ST_MDRV_HVSP_WINDOW_CONFIG   stCaptureWin;
    ST_MDRV_HVSPTIMING_CONFIG    stTimingCfg;
    ST_MDRV_HVSP_CLK_CONFIG       *stclk;
}ST_MDRV_HVSP_INPUT_CONFIG;
typedef struct
{
    bool  bCropEn;     ///< post crop En
    u16 u16X;        ///< crop frame start x point
    u16 u16Y;        ///< crop frame start y point
    u16 u16Width;    ///< crop frame width
    u16 u16Height;   ///< crop frame height
    bool  bFmCntEn;    ///< Is use CMDQ to set
    bool  u8FmCnt;     ///< when frame count
    ST_MDRV_HVSP_CLK_CONFIG       *stclk;  ///<clk framework
}ST_MDRV_HVSP_POSTCROP_CONFIG;

typedef struct
{
    u16 u16X;            ///< x vs input src
    u16 u16Y;            ///< y vs input src
    u16 u16Width;        ///< display width
    u16 u16Height;       ///< display height
    u16 u16crop2inWidth; ///< framebuffer width
    u16 u16crop2inHeight;///< framebuffer height
    u16 u16crop2OutWidth; ///< after crop width
    u16 u16crop2OutHeight;///< after crop height
}ST_MDRV_HVSP_SCINFORM_CONFIG;
typedef struct
{
    bool   u8Cmd;      ///< register value
    u32   u32Size;    ///< number
    u32   u32Addr;    ///< bank&addr
}ST_MDRV_HVSP_MISC_CONFIG;

//-------------------------------------------------------------------------------------------------
//  Prototype
//-------------------------------------------------------------------------------------------------
#ifndef _MDRV_HVSP_C
#define INTERFACE extern
#else
#define INTERFACE
#endif
INTERFACE bool MDrv_HVSP_Init(EN_MDRV_HVSP_ID_TYPE enHVSP_ID, ST_MDRV_HVSP_INIT_CONFIG *pCfg);
INTERFACE bool MDrv_HVSP_Exit(bool bCloseISR);
INTERFACE void MDrv_HVSP_Release(EN_MDRV_HVSP_ID_TYPE enHVSP_ID);
INTERFACE void MDrv_HVSP_SetPriMaskInstId(bool u8Id);
INTERFACE void MDrv_HVSP_Open(EN_MDRV_HVSP_ID_TYPE enHVSP_ID);
INTERFACE void MDrv_VIP_SetMCNRConpressForDebug(bool bEn);
INTERFACE bool MDrv_HVSP_SetOSDConfig(EN_MDRV_HVSP_ID_TYPE enHVSP_ID, ST_MDRV_HVSP_OSD_CONFIG*pCfg);
INTERFACE bool MDrv_HVSP_SetInputConfig(EN_MDRV_HVSP_ID_TYPE enHVSP_ID, ST_MDRV_HVSP_INPUT_CONFIG *pCfg);
INTERFACE void MDrv_HVSP_SetPatTgenStatus(bool bEn);
INTERFACE bool MDrv_HVSP_SetScalingConfig(EN_MDRV_HVSP_ID_TYPE enHVSP_ID, ST_MDRV_HVSP_SCALING_CONFIG *pCfg );
INTERFACE bool MDrv_HVSP_SetInitIPMConfig(EN_MDRV_HVSP_ID_TYPE enHVSP_ID, ST_MDRV_HVSP_IPM_CONFIG *pCfg);
INTERFACE bool MDrv_HVSP_SetMiscConfig(ST_MDRV_HVSP_MISC_CONFIG *pCfg);
INTERFACE bool MDrv_HVSP_SetPostCropConfig(EN_MDRV_HVSP_ID_TYPE enHVSP_ID, ST_MDRV_HVSP_POSTCROP_CONFIG *pCfg);
INTERFACE void MDrv_HVSP_SetMemoryAllocateReady(bool bEn);
INTERFACE bool MDrv_HVSP_GetSCLInform(EN_MDRV_HVSP_ID_TYPE enHVSP_ID, ST_MDRV_HVSP_SCINFORM_CONFIG *pstCfg);
INTERFACE void MDrv_HVSP_IDCLKRelease(ST_MDRV_HVSP_CLK_CONFIG* stclk);
INTERFACE bool MDrv_HVSP_SetMiscConfigForKernel(ST_MDRV_HVSP_MISC_CONFIG *pCfg);
INTERFACE u32 MDrv_HVSP_HWMonitor(bool u8flag);
INTERFACE bool MDrv_HVSP_InputVSyncMonitor(void);
INTERFACE void MDrv_HVSP_SetPollWait(void *filp, void *pWaitQueueHead, void *pstPollQueue);
INTERFACE bool MDrv_HVSP_Suspend(EN_MDRV_HVSP_ID_TYPE enHVSP_ID, ST_MDRV_HVSP_SUSPEND_RESUME_CONFIG *pCfg);
INTERFACE bool MDrv_HVSP_Resume(EN_MDRV_HVSP_ID_TYPE enHVSP_ID, ST_MDRV_HVSP_SUSPEND_RESUME_CONFIG *pCfg);
#if 0 // ToDo
INTERFACE ssize_t MDrv_HVSP_ClkFrameworkShow(char *buf,ST_MDRV_HVSP_CLK_CONFIG* stclk);
INTERFACE ssize_t MDrv_HVSP_OsdShow(char *buf);
INTERFACE ssize_t MDrv_HVSP_OdShow(char *buf);
INTERFACE ssize_t MDrv_HVSP_FBMGShow(char *buf);
INTERFACE void MDrv_HVSP_OsdStore(const char *buf,EN_MDRV_HVSP_ID_TYPE enHVSP_ID);
INTERFACE ssize_t MDrv_HVSP_IntsShow(char *buf);
INTERFACE ssize_t MDrv_HVSP_ProcShow(char *buf);
INTERFACE ssize_t MDrv_HVSP_SCIQShow(char *buf, EN_MDRV_HVSP_ID_TYPE enHVSP_ID);
INTERFACE void MDrv_HVSP_SCIQStore(const char *buf,EN_MDRV_HVSP_ID_TYPE enHVSP_ID);
INTERFACE ssize_t MDrv_HVSP_DbgmgFlagShow(char *buf);
INTERFACE ssize_t MDrv_HVSP_monitorHWShow(char *buf,int VsyncCount ,int MonitorErrCount);
INTERFACE void MDrv_HVSP_SetCLKForcemode(bool bEn);
INTERFACE void MDrv_HVSP_SetCLKOnOff(void* adjclk,bool bEn);
INTERFACE void MDrv_HVSP_SetCLKRate(void* adjclk,u8 u8Idx);
#endif

INTERFACE void * MDrv_HVSP_GetWaitQueueHead(void);
INTERFACE bool MDrv_HVSP_GetCMDQDoneStatus(void);
INTERFACE bool MDrv_HVSP_SetFbManageConfig(EN_MDRV_HVSP_FBMG_SET_TYPE enSet);
INTERFACE u8   Mdrv_HVSP_GetFrameBufferCountInformation(void);
INTERFACE bool MDrv_HVSP_SetPriMaskConfig(ST_MDRV_HVSP_PRIMASK_CONFIG stCfg);
INTERFACE bool MDrv_HVSP_SetPriMaskTrigger(bool bEn);

#undef INTERFACE
#endif
