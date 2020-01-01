/**
* @file    mmi_mae_sensormgr_forward.h
* @version $Id: mmi_mae_sensormgr_forward.h $
*/
#ifndef __MMI_MAE_SENSORMGR_FORWARD_H__
#define __MMI_MAE_SENSORMGR_FORWARD_H__
#include "mmi_mae_common_def.h"

typedef_opaque_enum(SENSOR_e_, SENSOR_e);
typedef_opaque_enum(SENSOR_NOTIFY_DELAY_e_, SENSOR_NOTIFY_DELAY_e);

typedef struct GSensorInfo_t_ GSensorInfo_t;

typedef struct GSensorDevInfo_t_ GSensorDevInfo_t;

typedef struct LightValue_t_ LightValue_t;

typedef struct AtmosphericValue_t_ AtmosphericValue_t;

typedef struct TemperatureValue_t_ TemperatureValue_t;

typedef union SensorInfo_u_ SensorInfo_u;

typedef union SensorDevInfo_u_ SensorDevInfo_u;

#endif //  __MMI_MAE_SENSORMGR_FORWARD_H__
