/**
* @file mmi_fdnap_callback.h
*
* State Machine Application - FDNAP
*
* Class Id: CLSID_FDNAP
*
*
* @version $Id$
*/

#ifndef __MMI_FDNAP_CALLBACK_H__
#define __MMI_FDNAP_CALLBACK_H__
#ifdef __FDN_MMI__
#include "mmi_srv_header.h"

void FdnAppSetFDNStatusCB(void *pThis, Mmi_FDNSrvSetFDNStatusCnf_t *ptCnf);

void FdnAppWriteOneContactCB(void *pThis, Mmi_FDNSrvWriteOneFDNCnf_t *ptCnf);

void FdnAppDeleteOneContactCB(void *pThis,Mmi_FDNSrvDeleteOneFDNCnf_t *ptCnf);
#endif //__FDN_MMI__
#endif /* __MMI_FDNAPP_CALLBACK_H__ */
