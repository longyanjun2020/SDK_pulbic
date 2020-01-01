
#ifndef __DRV_DMA2D_H__
#define __DRV_DMA2D_H__

#ifdef INTERFACE
#undef INTERFACE
#endif

#ifdef __DRV_DMA2D_C__
#define INTERFACE
#else
#define INTERFACE extern "C"
#endif




#define CONST_DMA2D_CMD_BUF_SIZE 0x100
//#define CONST_DMA2D_MAX_CMD_BUF_SIZE 0x4000 // 32bytes * 512(HW 9 bits)
#define CONST_DMA2D_MAX_CMD_BUF_SIZE 0x200 // 32bytes * 16

typedef struct _st_dma2d_remap_ *pStDma2dRemap;

//main functions
//INTERFACE void Drv_DMA2D_Init(u32 cmdqAddr, u32 cmdqSize);
bool DrvDMA2DIsAvtive(void);

bool DrvDMA2DInit(void);
void DrvDMA2DDeInit(void);

bool DrvDMA2DIsInit(void);
bool DrvDMA2DBitBlt(PMSBLT_BITBLT pParam);
bool DrvDMA2DFillRect(PMSBLT_FILLSOLID pParam);
bool DrvDMA2DCmdFinish(void);


//accurate control
void DrvDMA2DSetQuickMode(bool bQuickMode);
bool DrvDMA2DMakeCmdFinish(u32 *outCmd);
bool DrvDMA2DMakeCmdBitBlt(PMSBLT_BITBLT pParam, u32 *outCmd);
bool DrvDMA2DMakeCmdFillRect(PMSBLT_FILLSOLID pParam, u32 *cmd);
//void DrvDMA2DGetCmd(char *buf);
void DrvDMA2DPushCmdq(u32 *outCmd);
bool DrvDMA2DIsCmdFinish(void);
void DrvDMA2DIncreaseWptr(void);
u32  DrvDMA2DGetWptr(void);
u32  DrvDMA2DGetRptr(void);
bool DrvDMA2DCmdqAvailable(void);
void DrvDMA2DIrqClr(void);
bool DrvDMA2DIsHWBitBlt(PMSBLT_BITBLT pParam);
bool DrvDMA2DIsHWFillRect(PMSBLT_FILLSOLID pParam);
void DrvDMA2DSetRemap(pStDma2dRemap pStMap);

#endif

