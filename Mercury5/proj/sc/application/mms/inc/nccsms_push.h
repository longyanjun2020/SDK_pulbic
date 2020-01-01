/**
 * @file nccsms_push.h
 * Sms Push Service Layer
 *
 * Service API exposed by the Sms Push module.
 *
 * <!-- #interface list begin -->
 * \section nccconsms Interface
 * - NCCSMS_checkNotiSms()
 * <!-- #interface list end -->
 */

#ifndef __NCCSMS_PUSH_H__
#define __NCCSMS_PUSH_H__

#include <ncc_types.h>

/*  return value define */
#define NCC_IS_NORMAL_SMS 0x00 // The message is normal sms
#define NCC_IS_PUSH_SMS 0x01 // The message is push sms

/** Check the sms message type sms/push
  * \param  string
  * \param  len
  */
int8_t NCCSMS_checkNotiSms(int8_t *string, int32_t len);

#endif //__NCCSMS_PUSH_H__
