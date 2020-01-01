
/**
 * @file
 * Provisioning Service Layer
 *
 * Service API exposed by the Provisioning.
 *
 * <!-- #interface list begin -->
 * \section svc_prov_interface Interface
 * - svc_prov_getData()
 * - svc_prov_register()
 * <!-- #interface list end -->
 */

#ifndef __SVC_PROV_H__
#define __SVC_PROV_H__

//#include <string.h>
//#include <stdlib.h>
#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAXPINLEN   80   /**< pin length */
#define MAXMACLEN   80  /**< mac length */

/** macro define of application ID */
#define PROV_MAX_APP            11      /**< max number  of application types */

#define PROV_INTERNET_PROFILE       0       /**< PXLOGICAL */
#define PROV_DATA_ACCOUNT       1       /**< NAPDEF */
#define PROV_BROWSING           2       /**<W2            Browsing */
#define PROV_MMS            3       /**<W4            MMS */
#define PROV_SYNCML_DATA_SYNC       4       /**<W5            SyncML Data Synchronization */
#define PROV_SYNCML_DM          5       /**<W7            SyncML Device Management */
#define PROV_IMPS_WV            6       /**<wA            IMPS (WV) */
#define PROV_EMAIL_SMTP         7       /**<25            Email, SMTP */
#define PROV_EMAIL_POP3         8       /**<110           Email, POP3 */
#define PROV_EMAIL_IMAP4        9       /**<143           Email, IMAP4 */
#define PROV_STREAMING_MEDIA        10      /**<554           Streaming Media */

/**
 * Parse the PROV object and save them
 * \param   secCode      The SEC type
 * \param   macCode      The MAC code
 * \param   docbuf          The body part of (wb)xml document
 * \param   buflen          The length of the body in bytes.
 * \param   XmlType      wbxml/xml/si
 *
 * \return  <ul>
 *              <li>when successful, return TRUE
 *              <li>when failed, return FALSE
 *          </ul>
 */
int32_t NCCPush_prov_getData(int32_t secCode,int8_t *macCode,int8_t *buffer,int32_t bufferLen,int8_t XmlType);


/**
 * Register the  functions  for different configure module
 * \param   id          id of the configure module
 * \param   configFunc      the point of function called by configure module to get configure infomations
 *
 * \return  <ul>
 *              <li>when successful, return TRUE
 *              <li>when failed, return FALSE
 *          </ul>
 */
int32_t NCCPush_prov_register(int32_t id, int32_t (*configFunc)(void * param1, void * param2, void * param3, void * param4, void * param5));

/**
 * verify pin code when sec code is used
 * @param  secCode
 *      the sec type
 * @param  pinCode
 *      the pin code string
 * @param   macCode
 *      mac code
 * @param  buffer
 *      the provision body data
 * @param   bufferLen
 *      the length of provision body
 * @return
 *      return TRUE, if success,otherwise return FALSE.
 */
int32_t NCCProv_verifyPinCode(int32_t secCode, int8_t *pinCode, int8_t *macCode,
    int8_t *buffer, int32_t bufferLen);

void NCCPush_prov_cleanUp(void);

#ifdef __cplusplus
}
#endif

#endif /* __SVC_PROV_H__ */
