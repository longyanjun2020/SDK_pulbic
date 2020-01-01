/****************************************************************************/
/*   File: java_head.h                                                      */
/*                                                                          */
/*   Include all definitions for JAVA                                       */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*
* --------------------------------------------------------------------------
*  Date     | Author | Revision       | Description
* ----------+--------+----------------+-------------------------------------
*/

#ifndef __JAVA_HEAD_H__
#define __JAVA_HEAD_H__


#ifdef __JAVA_DELTA__



#include "vm_types.ht"
#include "vm_stdio.ho"
#include "cus_msg.hc"
#include "cus_os.hc"
#include "vm_kbd.h"
#include "sys_rtk_vmrtkho.h"        /* RTK interface                */
#include "drv_vm_rtc.h"         /* rtc interface */
//#include "vm_e2p.ho"        /* E2P interface                */
#include "sys_sys_vm_ftr.h"        /* Customization                */

#include "ven_os.h"
#include "ven_std.h"
#include "ven_handle.h"
#include "ven_dbg.h"
#include "ven_prim.h"
#include "Ven_graphics.h"
#include "ven_stc.h"
#include "ven_os.h"
#include "ven_stc_msgt.h"
#include "Ven_font.h"
#include "ven_sdk.h"
#include "ven_cc.h"
#include "ven_codec.h"
#include "ven_drv.h"
#include "ven_kpd.h"
#include "ven_ts.h"


#include "java_def.h"    /* open MMI compatibility */
#include "java_msg.hi"
#include "java_arc_stmsg.hi"
#include "java_prim.hc"
//#include "vm_msgt.ht"
//#include "sic_cfg.h"       /* Exported definitions          */
//#include "sic_net.h"       /* Exported definitions          */
//#include "sic_prov.h"       /* Exported definitions          */

//#define USE_ASYNC_ERROR_DIALOG // jacky add 20090113

#include "cus_os.hc"
//#include "vm_ip.hc"

#ifdef __SDK_SIMULATION__
#include <stdio.h>
#include <assert.h>
#include <string.h>
#define MSERV_ASSERT(X)   assert(X);
#else
#define MSERV_ASSERT(X)
#endif /* __SDK_SIMULATION__ */

extern u32 java_get_app_handle(void);
extern int nemomp_init_java_heap(int type);
extern void nemomp_free_java_heap(void);




#endif /* __JAVA_HEAD_H__ */

#endif /*	#ifdef __JAVA_DELTA__  */


