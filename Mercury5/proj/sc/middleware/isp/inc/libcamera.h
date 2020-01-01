#ifndef LIBCAMERA_H
#define LIBCAMERA_H
//#include <vm_types.ht>
#include "drv_isp.h"

#define LIBCAMERA_DMSG(args...) do{}while(0)
#define LIBCAMERA_EMSG(args...) UartSendTrace(args)
#define LIBCAMERA_VMSG(args...) do{}while(0)


typedef unsigned char       bool;
typedef unsigned char       u8;
typedef signed   char       s8;
typedef unsigned short      u16;
typedef signed   short      s16;
typedef unsigned int        u32;
typedef signed   int        s32;
typedef unsigned long       ul32;
typedef unsigned long long  u64;
typedef signed   long long  s64;

#define MAX_SUPPORT_SENSOR_NUM     4
#define MAX_SENSOR_FILENAME_LENGTH    128

u32 ISP_GetActiveChannel(void);
void ISP_SetActiveChannel(u32 ulchannel);
void ISP_SetHDR16to12EnableChannel(u32 ulchannel, bool enable);
void ISP_SetChannelMode(u32 ulchannel, bool bisp_enable);
void ISP_Get3AFrameCount(u32 ulchannel,
    u32 *pu32ISP3AFramePeriodTotal, u32 *pu32ISP3AFrameCountDoAe, u32 *pu32ISP3AFrameCountDoAwb, u32 *pu32ISP3AFrameCountDoIq,
    u32 *pu32ISP3AFrameCountSetShutter, u32 *pu32ISP3AFrameCountSetGain,
    u32 *pu32ISP3AFrameCountShadowFrameStart, u32 *pu32ISP3AFrameCountShadowFrameEnd);
void ISP_Set3AFrameCount(u32 ulchannel,
    u32 u32ISP3AFramePeriodTotal, u32 u32ISP3AFrameCountDoAe, u32 u32ISP3AFrameCountDoAwb, u32 u32ISP3AFrameCountDoIq,
    u32 u32ISP3AFrameCountSetShutter, u32 u32ISP3AFrameCountSetGain,
    u32 u32ISP3AFrameCountShadowFrameStart, u32 u32ISP3AFrameCountShadowFrameEnd);

void SetIspBypass(bool bIspBypass);
bool GetIspBypass(void);
void ISP_BypassMode(void);

void ISP_3A_IQ_Init(u32 ulchannel, bool hdr_enable, u32 iqcfgidx, bool dual_bayer_sensor);
void ISP_3A_IQ_UnInit(u32 ulchannel);
void ISP_SetRdmaTrigMask(u32 ulchannel, u8 mask);
u8 ISP_GetRdmaTrigMask(u32 ulchannel);

#if defined(__RTK_OS__)
void cameraLoadIQAPIFile(u32 nChannel, u32 napi_num);
#endif
int cameraSensorSetIQFile(u32 nChannel); //TBD. It should be assigned by each sensor.
int cameraGetResolution(u32 nChannel, u32 *pWidth, u32 *pHeight, u32 *pFPS, u32 nId);
void cameraSetDrvHandle(ISP_DRV_HANDLE pisp_drv);
ISP_DRV_HANDLE cameraGetDrvHandle();
void cameraLoadIQFile(u32 nChannel, void **hnd);

void cameraVIF2ISPFrameStartRegisterIntrCallBack(unsigned int channel, IspCallBackFunc *pCallBack);
void cameraVIF2ISPFrameEndRegisterIntrCallBack(unsigned int channel, IspCallBackFunc *pCallBack);
void cameraISPFrameStartRegisterIntrCallBack(unsigned int channel, IspCallBackFunc *pCallBack);
void cameraISPFrameEndRegisterIntrCallBack(unsigned int channel, IspCallBackFunc *pCallBack);
void cameraWDMADoneRegisterIntrCallBack(unsigned int channel, IspCallBackFunc *pCallBack);
void cameraWDMALineCntRegisterIntrCallBack(unsigned int channel, IspCallBackFunc *pCallBack);
void cameraRDMADoneRegisterIntrCallBack(unsigned int channel, IspCallBackFunc *pCallBack);

int MdlIspWaitHWInit(void);




#endif
