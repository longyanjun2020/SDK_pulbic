
/**
 * @file
 * NCC mms Dial Porting Layer
 *
 * NCC mms Dial Porting Layer Routine should be implemented
 *
 * <!-- #interface list begin -->
 * \section nccport_mms_dial Interface
 * - NCCPort_mms_dial()
 * <!-- #interface list end -->
 */

#ifndef __NCCPort_MMS_DIAL_H__
#define __NCCPort_MMS_DIAL_H__

#include <ncc_types.h>
#include <nccmms_trans.h>

#ifdef __cplusplus
extern "C" {
#endif

/**dial operation success*/
#define NCCPort_MMS_DIAL_SUCCESS                                 0
/**dial operation failed*/
#define NCCPort_MMS_DIAL_FAILED                                  -1
/**dial operation invalid argument*/
#define NCCPort_MMS_DIAL_INVALID                                 -2

/**define mode of dialing up*/
#define DIAL_UP                                              0x1
/**define mode of dialing down*/
#define DIAL_DOWN                                            0x0

/**
 * Dial up/down
 * \param dial_config dial configuration
 * \param up_or_down dial command
 * \return <ul>
 *		<li>#NCCPort_MMS_DIAL_SUCCESS	if success
 *		<li>#NCCPort_MMS_DIAL_FAILED	if failed
 *		<li>#NCCPort_MMS_DIAL_INVALID	if parameter invalid
 *	   </ul>
 */
int32_t NCCPort_mms_dial(T_MMS_Dial_Cfg * dial_config, int32_t up_or_down);

#ifdef __cplusplus
}
#endif

#endif /* __NCCPort_MMS_DIAL_H__ */
