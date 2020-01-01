/**
 * @file mmi_mae_gps_forward.h
 *
 * @version $Id: mmi_mae_gps_forward.h $
 */
#ifndef __MMI_MAE_GPS_FORWARD_H__
#define __MMI_MAE_GPS_FORWARD_H__
#include "mmi_mae_common_def.h"

typedef_opaque_enum(MAEGpsCallBackEvent_e_, MAEGpsCallBackEvent_e);
typedef_opaque_enum(MAEGpsRetCode_e_, MAEGpsRetCode_e);
typedef_opaque_enum(MAEGpsAppId_e_, MAEGpsAppId_e);
typedef_opaque_enum(MAEGpsState_e_, MAEGpsState_e);
typedef_opaque_enum(MAEGpsCmd_e_, MAEGpsCmd_e);

typedef struct MAE_NmeaSatviewData_t_ MAE_NmeaSatviewData_t;
typedef struct MAE_NmeaGPRMC_t_ MAE_NmeaGPRMC_t;
typedef struct MAE_NmeaGPGGA_t_ MAE_NmeaGPGGA_t;
typedef struct MAE_NmeaGPGSA_t_ MAE_NmeaGPGSA_t;
typedef struct MAE_NmeaGPGSV_t_ MAE_NmeaGPGSV_t;
typedef struct MAEGpsData_t_ MAEGpsData_t;
typedef struct MAEGpsCallbackData_t_ MAEGpsCallbackData_t;

#endif /* __MMI_MAE_GPS_FORWARD_H__ */
