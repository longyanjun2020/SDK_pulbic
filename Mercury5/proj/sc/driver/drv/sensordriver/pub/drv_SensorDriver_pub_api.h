

/*drv_SensorDriver_pub_api.h*/
#ifndef _DRV_SENSOR_DRIVER_PUB_API_H__
#define _DRV_SENSOR_DRIVER_PUB_API_H__

u8 fn_Sensor_GetFramerate15VideoTable(void);
void fn_Sensor_BriSet_new(U16 u16Bri);
void fn_Sensor_ContrastSet_new(U16 u16Cont);
#if defined(__DEVICE_INFO__)
u16 DrvSenGetCamStrInfo(u8 id, char *pStr, u16 maxLen);
#endif

#endif //_DRV_SENSOR_DRIVER_PUB_API_H__



