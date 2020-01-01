/****************************************************************************/
/*   File: ms_head.h                                                        */
/*                                                                          */
/*   Include all definitions for MSERV                                      */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*
* --------------------------------------------------------------------------
*  Date     | Author | Revision       | Description
* ----------+--------+----------------+-------------------------------------
*/

#ifndef __MS_HEAD_H__
#define __MS_HEAD_H__

#ifdef __MSERVICES__

#include "vm_types.ht"
#include "vm_stdio.ho"
#include "cus_msg.hc"
#include "cus_os.hc"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_rtk_vmrtkho.h"        /* RTK interface                */
#include "ms_defs.h"
#include "ms_init.h"
#include "ms_msg.hi"
#include "vm_msgt.ht"
#include "ms_task.h"       /* Exported definitions          */
#include "sic_net.h"       /* Exported definitions          */
#include "ms_data.h"       /* Exported definitions          */
#include "sys_vm_dbg.ho"       /* vm_dbgTrace */
#include "vm_ip.h"

#ifdef __SDK_SIMULATION__
#include <stdio.h>
#include <assert.h>
#include <string.h>
#define MSERV_ASSERT(X)   assert(X);
#else
#define MSERV_ASSERT(X)
#endif /* __SDK_SIMULATION__ */

#ifdef __SDK_SIMULATION__
extern vm_VmlClientId_t vm_VmlSubscribeServTab_1( const vm_VmlAppliServ_t * ServTab, void  ReturnMethod(vm_msg_t *), u8 MailBox);
extern bool vm_VmlAppliSubscribeParserExt_1( void (*AppliParser)(vm_msg_t *), u8 MailBox );
extern bool vm_VmlUnsubscribeServTab_1 ( vm_VmlClientId_t Client );
#endif

#ifdef __MSTAR_DUAL_SIM__
  #if defined (__MSTAR_DUAL_SIM_REDUCE_CODE__)
    extern bool vm_VmlAppliSubscribeParserMserv( void (*AppliParser)(vm_msg_t *), u8 MailBox );
    extern bool vm_VmlAppliSubscribeParserMserv_2( void (*AppliParser)(vm_msg_t *), u8 MailBox );
    extern vm_VmlClientId_t vm_VmlSubscribeServTabExt_2( const vm_VmlAppliServ_t * ServTab, void  ReturnMethod(vm_msg_t *), u8 MailBox);

  #else
    extern bool vm_VmlAppliSubscribeParserExt_2( void (*AppliParser)(vm_msg_t *), u8 MailBox );
extern vm_VmlClientId_t vm_VmlSubscribeServTab_2( const vm_VmlAppliServ_t * ServTab, void  ReturnMethod(vm_msg_t *), u8 MailBox);
  #endif
extern bool vm_VmlUnsubscribeServTab_2 ( vm_VmlClientId_t Client );
#endif

#if defined(__MSTAR_DUAL_SIM__) && defined(__MSTAR_DUAL_SIM_REDUCE_CODE__) && defined(__MSTAR_DUAL_SIM_DUP_GLOB__)
extern bool vm_VmlAppliSubscribeParserExtWithModuleId( void (*AppliParser)(vm_msg_t *), u8 MailBox, u8 ModuleId);
#endif/* __WLAN_IP_SUPPORT__ */

#define DUMP_BUFFER_LENGTH (1500)

#endif  /* __MSERVICES__ */
#endif /* __MS_HEAD_H__ */


