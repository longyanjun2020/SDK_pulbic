#ifndef __MMI_COMMON_EM_TYPE_H__
#define __MMI_COMMON_EM_TYPE_H__
/*
 * Data type definition for emApp that is needed by other libraries
 *
 */

 typedef enum
{
  EMAPType_NORMAL = 0,      /* unknown reason. */
  EMAPType_IMEI,
  EMAPType_SOFTWARE_VER,
  EMAPType_FACTORY_INFO,
  EMAPType_WIFI_PRODUCTION,
  EMAPType_RESET_FACTORY,
  EMAPType_RESET_FACTORY_FOR_TOOL,
  EMAPType_TOUCH_SCREEN_FWUPDATE,
  EMAPType_WIFI_ALL_TEST,
  EMAPType_BT_ALL_TEST,
  EMAPType_WIFI_PRODUCTION_TX,
  EMAPType_END,
} EmAppApStartType_e;  /* All start reasons for launching EM AP */

#endif //__MMI_COMMON_EM_TYPE_H__
