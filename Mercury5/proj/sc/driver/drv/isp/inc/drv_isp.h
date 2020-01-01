#ifndef DRV_ISP_H
#define DRV_ISP_H
#include <drv_ms_isp_general.h>

#define FORCE_RAW_16BIT (0)

typedef void* ISP_DRV_HANDLE;

typedef enum
{
    //ISP frame start/end
    ISP_INTS_FRAME_START = 0x00000001,
    ISP_INTS_FRAME_END = 0x00000002,

    //VIF -> ISP pipe frame start
    ISP_INTS_PIPE0_VIF_FRAME_START = 0x00000004,
    ISP_INTS_PIPE1_VIF_FRAME_START = 0x00000008,
    ISP_INTS_PIPE2_VIF_FRAME_START = 0x00000010,

    //VIF -> ISP pipe frame end(line count hit)
    ISP_INTS_PIPE0_INPUT_HIT_LINE_COUNT = 0x00000020,
    ISP_INTS_PIPE1_INPUT_HIT_LINE_COUNT = 0x00000040,
    ISP_INTS_PIPE2_INPUT_HIT_LINE_COUNT = 0x00000080,

    //WDMA(RAW store) line count hit
    ISP_INTS_WDMA0_HIT_LINE_COUNT = 0x00000100,
    ISP_INTS_WDMA1_HIT_LINE_COUNT = 0x00000200,
    ISP_INTS_WDMA2_HIT_LINE_COUNT = 0x00000400,

    //WDMA(RAW store) frame end
    ISP_INTS_WDMA0_DONE = 0x00000800,
    ISP_INTS_WDMA1_DONE = 0x00001000,
    ISP_INTS_WDMA2_DONE = 0x00002000,

    //RDMA(RAW fetch) frame end
    ISP_INTS_RDMA0_DONE = 0x00004000,
    ISP_INTS_RDMA1_DONE = 0x00008000,

    //Statistics. May move to another isp event.
    ISP_INTS_AE_DONE = 0x00010000,
    ISP_INTS_AWB_DONE = 0x00020000,

    //Sclaer event.
    ISP_INTS_SCL_VS = 0x00040000,         //scaler vsync start interrupt
    ISP_INTS_SCL_VE = 0x00080000,          //scaler vsync end interrupt

	//ISP Busy
	ISP_INTS_BUSY_START = 0x00100000,
	ISP_INTS_BUSY_END   = 0x00200000,
} IspIntsEventType_e;

#if 0
typedef enum
{
    ISP_PIPE_0 = 0,
    ISP_PIPE_1 = 1,
    ISP_PIPE_2 = 2,
}ISP_PIPE_e;

typedef enum
{
    ISP_DMA_PIPE0=0,
    ISP_DMA_PIPE1=1,
    ISP_DMA_PIPE2=2,
    ISP_DMA_GENERAL=3,
}IspDmaId_e;

typedef enum
{
    ISP_DMA_POSITION_HEAD = 0,
    ISP_DMA_POSITION_TAIL = 1,
}ISP_DMA_POSITION_e;
#endif
typedef struct
{
    MS_U32 nCh;        //Input channel
    MS_U32 nFbId;      //frame buffer ID
    MS_U32 reserved;
}IspFrameBuffer_t;

typedef void (IspCallBackFunc)(unsigned int ulchannel);

////// Test API ///////
int DrvIsp_EnablePatternMode(ISP_DRV_HANDLE handle, int width, int height);

////// Pipe line control //////
int DrvIsp_PreviewLineMode(ISP_DRV_HANDLE handle, unsigned int channel, ISP_COLOR_SPACE in_cs, ISP_DATAPRECISION in_prec, ISP_CROP_RANGE in, ISP_CROP_RANGE out);
int DrvIsp_PreviewLineISPBypassMode(ISP_DRV_HANDLE handle, unsigned int channel, ISP_YUV_ORDER yuv_order, ISP_DATAPRECISION in_prec, ISP_CROP_RANGE in, ISP_CROP_RANGE out);
int DrvIsp_PreviewLineModeDisable(ISP_DRV_HANDLE handle, unsigned int channel);
int DrvIsp_PreviewRAWStoreMode(ISP_DRV_HANDLE handle, unsigned int channel, int width, int height, ISP_COLOR_SPACE in_cs, ISP_DATAPRECISION in_prec);
int DrvIsp_PreviewRAWStoreModeDisable(ISP_DRV_HANDLE handle, unsigned int channel);
int DrvIsp_PreviewRAWFetchMode(ISP_DRV_HANDLE handle, unsigned int channel, int width, int height, ISP_COLOR_SPACE in_cs, ISP_DATAPRECISION in_prec);
int DrvIsp_PreviewRAWFetchModeDisable(ISP_DRV_HANDLE handle, unsigned int channel);
int DrvIsp_UpdateRAWStoreAddress(ISP_DRV_HANDLE handle, unsigned int channel, unsigned int raw_addr);
int DrvIsp_UpdateRAWFetchAddress(ISP_DRV_HANDLE handle, unsigned int channel, unsigned int raw_addr);
int DrvIsp_SingleTriggerRAWStore(ISP_DRV_HANDLE handle, unsigned int channel);
int DrvIsp_SingleTriggerRAWFetch(ISP_DRV_HANDLE handle, unsigned int channel);

/*
int DrvIsp_SetDataMux(ISP_DRV_HANDLE *handle,
                      ISP_INOUT_CONFIG input,
                      ISP_INOUT_CONFIG output,
                      unsigned int in_addr,
                      unsigned int out_addr,
                      MS_BOOL rdma_auto,
                      MS_BOOL wdma_auto,
                      ISP_DATAPRECISION sen_prec);
*/
int DrvIsp_GetCropInfo(ISP_DRV_HANDLE handle,ISP_CROP_RANGE *pCropInfo);
int DrvIsp_WDMACapture(ISP_DRV_HANDLE handle,ISP_WDMA_ATTR wdma_attr);
int DrvIsp_WDMASetLineCnt(ISP_DRV_HANDLE handle, unsigned int channel, unsigned int iline_cnt);

//sensor IF
int DrvIsp_SensorIfDataCfg(ISP_DRV_HANDLE handle, unsigned int channel, ISP_DATAPRECISION depth, SEN_BAYER bayer_id);
int DrvIsp_SensorIfDataCfg_DataPrecision(ISP_DRV_HANDLE handle, unsigned int channel, ISP_DATAPRECISION depth);
int DrvIsp_SensorIfDataCfg_BayerFmt(ISP_DRV_HANDLE handle, unsigned int channel, SEN_BAYER bayer_id);
int DrvIsp_SensorIfCfg( ISP_DRV_HANDLE handle,
                        SIF_BUS data_bus,
                        ISP_DATAPRECISION depth,
                        SEN_BAYER bayer_id,
                        SEN_RGBIR rgbir_id,
                        CLK_POL pclk_pol,
                        CLK_POL vsync_pol,
                        CLK_POL hsync_pol,
                        MS_U32 sr_width            //sensor output width
                      );
int DrvIsp_SensorPowerOff(ISP_DRV_HANDLE handle,int idx,MS_BOOL level);
int DrvIsp_SensorReset(ISP_DRV_HANDLE handle,int idx,MS_BOOL level);

//AE statistic
int DrvIsp_AeGetStatsLen(ISP_DRV_HANDLE handle);
int DrvIsp_AeSourceSelection(ISP_DRV_HANDLE handle, MS_BOOL hdr_enable);
int DrvIsp_AeSetWin(ISP_DRV_HANDLE handle,ISP_AE_WIN win);
int DrvIsp_AeGetStats(ISP_DRV_HANDLE handle,ISP_AE_AVGS *stats);
int DrvIsp_AeStatsEnable(ISP_DRV_HANDLE handle,MS_BOOL enable);


//AWB statistic
int DrvIsp_AwbGetStatsLen(ISP_DRV_HANDLE handle);
int DrvIsp_AwbSourceSelection(ISP_DRV_HANDLE handle, MS_BOOL hdr_enable);
int DrvIsp_AwbSetWin(ISP_DRV_HANDLE handle,ISP_CROP_WIN crop_win,ISP_AWB_WIN win);
int DrvIsp_AwbGetStats(ISP_DRV_HANDLE handle,ISP_AWB_AVGS *stats);
int DrvIsp_AwbStatsEnable(ISP_DRV_HANDLE handle,MS_BOOL enable);

//Histogram statistic
int DrvIsp_HistoStatsEnable(ISP_DRV_HANDLE handle, MS_BOOL enable, int idx);
int DrvIsp_HistoSetAttr(ISP_DRV_HANDLE handle, const ISP_HISTO_ATTR *attr);
int DrvIsp_HistoSetWins(ISP_DRV_HANDLE handle, const ISP_HISTO_WIN *win, int idx);
int DrvIsp_HistoGetWins(ISP_DRV_HANDLE handle, volatile ISP_HISTO_WIN *win, int idx);
int DrvIsp_HistoGetStats(ISP_DRV_HANDLE handle,ISP_AE_HISTX *stats,int idx);

//HDR statistic
int DrvIsp_HdrStatsEnable(ISP_DRV_HANDLE handle,MS_BOOL enable);
int DrvIsp_HDRGetStats(ISP_DRV_HANDLE handle,ISP_HDR_STATS *stats);
int DrvIsp_EnableHDR(ISP_DRV_HANDLE handle, MS_BOOL enable);
int DrvIsp_EnableHDR16to12(ISP_DRV_HANDLE handle, MS_BOOL enable);
int DrvIsp_EnableDecomp(ISP_DRV_HANDLE handle, MS_BOOL enable);

//RDMA
int DrvIsp_SetRDMAAutoTrigSel(ISP_DRV_HANDLE handle, unsigned int channel, unsigned int sel);
int DrvIsp_RDMAAuto(ISP_DRV_HANDLE handle, unsigned int channel, MS_BOOL enable);


//ISP control
ISP_DRV_HANDLE DrvIsp_Open(void);
void DrvIsp_Close(ISP_DRV_HANDLE handle);
int DrvIsp_GetAeTaskID();
int DrsIsp_AeInit();
int DrvIspCreateAeTask(void);
int DrvIsp_ICPAsync(ISP_DRV_HANDLE handle,MS_BOOL enable);
int DrvIsp_InitIntFlag(void);
int DrvIsp_UnInitIntFlag(void);
void DrvIsp_SetInt(MS_S32 value);
MS_S32 DrvIsp_WaitInt(MS_S32 nIntForWait);//wait isp interrupts
int DrvIsp_Show(void); //show isp interrupt statistics
int DrvIspDpRstbyVsync(ISP_DRV_HANDLE handle,MS_BOOL enable);
//void IspIsr_WDMA_RegisterIntrCallBack(unsigned int channel, IspWDMACallBackFunc *pCallBack);
int DrvIspEnableHwRegShadow(ISP_DRV_HANDLE handle, unsigned int channel, MS_BOOL enable);
void DrvIsp_Reset(unsigned int channel);

//ISP Mload
int DrvIsp_MloadDone(ISP_DRV_HANDLE handle);
int DrvIsp_WaitMloadDone(ISP_DRV_HANDLE handle, long us_count);
int DrvIsp_MLoadTableSet(ISP_DRV_HANDLE handle, IspMloadID_e idx, const MS_U16 *table);
int DrvIsp_MLoadTableGet(ISP_DRV_HANDLE handle, IspMloadID_e idx, MS_U16 *table);
int DrvIsp_MLoadApply(ISP_DRV_HANDLE handle);
int DrvScl_MLoadApply(ISP_DRV_HANDLE handle, MS_BOOL bTrigger);
int DrvIsp_MLoadRead(ISP_DRV_HANDLE handle,int id,int sram_offset,ISP_MLOAD_OUTPUT *output);
int DrvScl_MLoadRead(ISP_DRV_HANDLE handle,int id,int sram_offset,ISP_MLOAD_OUTPUT *output);
int DrvIsp_MLoadFreeBuffer(ISP_DRV_HANDLE handle);
int DrvIsp_MLoadInitBuffer(ISP_DRV_HANDLE handle);
void DrvIsp_MLoadDump(ISP_DRV_HANDLE handle,IspMloadID_e ID, short *buf);
void DrvScl_MLoadDump(ISP_DRV_HANDLE handle,IspMloadID_e ID, short *buf);

//Job queue
int DrvIsp_DequeJob(IspFrameBuffer_t *fb);
int DrvIsp_FreeJob(IspFrameBuffer_t *fb);
//check FPS function
void SetCheckFPSEnable(u8 channel, u8 Enable);
#endif
