
/**
 * @file
 * NCC mms string Porting Layer
 *
 * NCC mms string Porting Layer Routines should be implemented
 *
 * <!-- #interface list begin -->
 * \section nccport_mms_string Interface
 * - NCCPort_mms_itoa()
 * <!-- #interface list end -->
 */

#ifndef __NCCPort_MMS_STRING_H__
#define __NCCPort_MMS_STRING_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert from an integer to ascii
 * \param val value to convert
 * \param buf space to contain ascii, provided by caller
 * \param radix 8,10,16
 * \return <ul>
 *             <li> None
 *         </ul>
 */
int8_t *NCCPort_mms_itoa(uint32_t val, int8_t * buf, uint16_t radix);

#ifdef __cplusplus
}
#endif

#endif /* __NCCPort_MMS_STRING_H__ */
