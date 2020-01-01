/**
 * @file mmi_venappid.h
 *
 * @author Steve.Lee
 *
 * @version $Id: mmi_venappid.h 36460 2009-07-24 03:02:22Z code.lin $
 *
 */

#ifndef __MMI_VENAPPID_H__
#define __MMI_VENAPPID_H__

#include "ven_integration.h"
/* enum for app ID */
#define __ENUM_VEN_MMI_ID__
#undef __VEN_APPTBL_H_
#include "ven_apptbl_pub.h"
#undef __ENUM_VEN_MMI_ID__

typedef u32 Mmi_VenAppID_t;

#endif /* __MMI_VENAPPID_H__ */
