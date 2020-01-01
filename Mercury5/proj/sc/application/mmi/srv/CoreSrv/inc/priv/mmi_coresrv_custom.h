/**
 * @file mmi_coresrv_custom.h
 *
 * 
 * Class Id: 
 *
 * @version $Id:$
 */
#ifndef __MMI_CORESRV_CUSTOM_H__
#define __MMI_CORESRV_CUSTOM_H__

#include "mdl_gpd_pub.h"

//Year Min:2008 Max:2037
//Mark this code. Year is set according to compiler.
//#define CORESRV_SYS_FACTORY_YEAR  (2009)
//Month Min:01 Max:12
#define CORESRV_SYS_FACTORY_MONTH   (01)
//Day Min:01 Max:31
#define CORESRV_SYS_FACTORY_DAY     (01)

#ifdef __BREATHLIGHT_MMI__
extern const MdlGpdLedPattern_t LedPatternDefault[];
extern const MdlGpdLedPattern_t LedPattern0[];
extern const MdlGpdLedPattern_t LedPattern1[];
#endif /* __BREATHLIGHT_MMI__ */

#endif /* __MMI_CORESRV_CUSTOM_H__ */
