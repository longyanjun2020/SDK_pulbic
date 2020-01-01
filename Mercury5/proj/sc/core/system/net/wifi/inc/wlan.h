#include "net_cfg.h"

#if (WIFI_DRIVER_TYPE == WIFI_DRIVER_BCM)
#include "wlan_BCM.h"
#elif (WIFI_DRIVER_TYPE == WIFI_DRIVER_MTK)
#include "wlan_MTK.h"
#elif (WIFI_DRIVER_TYPE == WIFI_DRIVER_RTK)
#include "wlan_RTK.h"
#elif (WIFI_DRIVER_TYPE == WIFI_DRIVER_ATBM)
#include "wlan_ATBM.h"
#endif
