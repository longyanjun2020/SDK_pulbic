/*
 * Copyright 2005-2006 NCC Inc. All Rights Reserved.
 * $Id: //depot/dev/base/inc/uapps/wap/nccport/nccport_browser_cert.h#2 $
 */

/*
 * <!-- #interface list begin -->
 * \section nccport_browser_cert Interface
 * - NCCPort_brwcert_getSeverAuthStore()
 * - NCCPort_brwcert_getCodeSignStore()
 * - NCCPort_brwcert_getCrlFile()
 * <!-- #interface list end -->
 */

#ifndef __NCCPORT_BROWSER_CERT_H__
#define __NCCPORT_BROWSER_CERT_H__

#include <ncc_types.h>

/**
 * Get the path and file of server auth store
 * \param none
 * \return  if NULL failed else succeed
 */
int8_t* NCCPort_brwcert_getSeverAuthStore(void);

/**
 * Get the path and file of code sign store
 * \param none
 * \return  if NULL failed else succeed
 */
int8_t* NCCPort_brwcert_getCodeSignStore(void);


/**
 * Get the path and file of CRL cert store
 * \param none
 * \return  if NULL failed else succeed
 */
int8_t* NCCPort_brwcert_getCrlFile(void);


#endif /* __NCCPORT_BROWSER_CERT_H__ */
