
/**
 * @file
 * NCC mms Config Porting Layer
 *
 * NCC mms Config Porting Layer Routine should be implemented
 *
 * <!-- #interface list begin -->
 * \section nccport_mms_config Interface
 * - NCCPort_mmscfg_getWapHeader()
 * <!-- #interface list end -->
 */

#ifndef __NCCPort_MMS_CONFIG_H__
#define __NCCPort_MMS_CONFIG_H__
#include <ncc_types.h>
#include <nccmms_cps.h>
#include <nccmms_fs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**config operation success*/
#define NCCPort_MMS_CONFIG_SUCCESS                               0
/**config operation failed*/
#define NCCPort_MMS_CONFIG_FAILED                                -1
/**config operation invalid argument*/
#define NCCPort_MMS_CONFIG_INVALID                               -2

/**
 * get Wap Header of special Mobile
 * \param **wap_header configuration
 * \return <ul>
 *      <li>#NCCPort_MMS_CONFIG_SUCCESS if success
 *      <li>#NCCPort_MMS_CONFIG_FAILED  if failed
 *      <li>#NCCPort_MMS_CONFIG_INVALID if parameter invalid
 *     </ul>
 */
int32_t NCCPort_mmscfg_getWapHeader(int8_t ** wap_header);

void NCCPort_mmscfg_readNetProfile(T_MmsFs_Config *mmsConfig);

#ifdef __cplusplus
}
#endif

#endif /* __NCCPort_MMS_CONFIG_H__ */
