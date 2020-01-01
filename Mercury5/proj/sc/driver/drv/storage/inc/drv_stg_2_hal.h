
//
// drv_stg_2_hal.h
//

typedef struct _STG_2_HAL_INIT_PARA
{
    U8              LogSwitch;

} STG_2_HAL_INIT_PARA;

typedef enum
{
    E_DUAL_SD_SHARE_PWR = 0,
    E_INDEPENDANT_POWER = 1,

} E_POWER_SOURCE_MODE;

typedef enum
{
    E_PWR_ON = 0,
    E_PWR_OF = 1,

} E_POWER_SWITCH;

U8          HalStg_GetChipName(void);
void        HalStg_Init(STG_2_HAL_INIT_PARA * Stg2HalInitPara);
void        HalStg_SetupCardDetectIntr(void);
void        HalStg_SetupMieIntr(U8 u8Disk, E_MIE_MODE MieMode, E_MIE_INTR_EN_MODE IntrMode);
SLOT_STATUS HalStg_GetCardDetect(void);
U8          HalStg_SDRemoved(U8 u8Disk);
void        HalStg_DumpRegister(U8 u8Disk);
void        HalStg_RegisterCapture(U8 u8Disk, U16 * pu16Buffer);
//U8        HalStg_CmdRspBufGet(U8 u8Disk, U8 u8Addr);
//void      HalStg_CmdRspBufSet(U8 u8Disk, U8 u8Addr, U8 u8Value);
U8          HalStg_DataFifoGet(U8 u8Disk, U16 u16Addr);
//void      HalStg_DataFifoSet(U8 u8Disk, U16 u16Addr, U8 u8Value);
//void      HalStg_EnableCardInf(U8 u8Disk, U8 u8MiePath);
//void      HalStg_SetMiuAddr(U8 u8Disk, U32 u32MiuAddr);
U8          HalStg_CheckResponse(U8 u8Disk);
void        HalStg_ResetIP(U8 u8Disk);
E_IO_STS    HalStg_GetRspDMAStatus(U8 u8Disk);
E_IO_STS    HalStg_SDWaitD0High(U8 u8Disk);
//E_IO_STS    HalStg_WaitMieEvent(U8 u8Disk, U16 u16ReqVal, U32 u32WaitMs);
E_IO_STS    HalStg_SendCommand(U8 u8Disk, CMD_RSP_INFO * pCmdRspInfo);
E_IO_STS    HalStg_ReadWrite(U8 u8Disk, RW_INFO * pRwInfo);
E_IO_STS    HalStg_SetDataBus(U8 u8Disk, E_DATA_BUS DataBus);
E_IO_STS    HalStg_OpenClock(U8 u8Disk);
E_IO_STS    HalStg_ClockTest(U8 u8Disk);
U16         HalStg_CardDetectIntrGet(U8 u8Disk);
void        HalStg_CardDetectIntrSet(U8 u8Disk, U16 u16Reg);
void        HalStg_DelayMs(U32 u32Ms);
U32         HalStg_GetTimeMs(void);
U32         HalStg_SetClock(U8 u8Disk, U32 u32Clock);
void        HalStg_SwitchPad(U8 u8Disk, E_PAD_PULL PadPull);
U8          HalStg_SemaphoreLock(U8 u8Disk);
U8          HalStg_SemaphoreRles(U8 u8Disk);
S16         HalStg_SemaphoreGetCount(U8 u8Disk);
void        HalStg_Power(U8 u8Disk, U8 u8OnOff, E_POWER_SOURCE_MODE PowerMode);
void        HalStg_EmergentStopAccessInit(void);
void        HalStg_PwrSaveCtrl(U8 u8Disk, E_PWR_SAVE_EN PwrSaveEn);
U8          HalStg_PowerSaveTriggered(void);



