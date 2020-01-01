/**
 * @file nccconsms.h
 * Comsms Service Layer
 *
 * Service API exposed by the consms module.
 *
 * <!-- #interface list begin -->
 * \section nccconsms Interface
 * - NCCConsms_rcvNotiSms()
 * <!-- #interface list end -->
 */

#ifndef __NCC_CONSMS_H__
#define __NCC_CONSMS_H__

#include <ncc_types.h>

/*  return value define */
#define CONSMS_IS_PUSH_AND_USED         0   /** it's push message and processed */
#define CONSMS_IS_PUSH_IGNORE           -1  /** it's push message but not processed  */
#define CONSMS_IS_CONSMS_NOT_PUSH       -2  /** it's concatenated sms,not push message */
#define CONSMS_EXCEED_MAX_SEQUENCE      -3  /**  exceed max sequence */
#define CONSMS_IS_NORMAL_SMS            -4  /** normal sms */
#define CONSMS_PARSER_PDU_ERROR         -5  /** PDU parser error  */
#define CONSMS_MEMORY_ALLOC_FAIL        -6

#ifdef __cplusplus
extern "C" {
#endif
/** receive notification of sms
  * \param  string
  * \param  len
  */
int8_t NCCConsms_rcvNotiSms(int8_t *string,int32_t len);
#ifdef __cplusplus
}
#endif

#endif
