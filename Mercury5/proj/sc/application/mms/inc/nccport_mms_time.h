
/**
 * @file
 * NCC mms time Porting Layer
 *
 * NCC mms time Porting Layer Routines should be implemented
 *
 * <!-- #interface list begin -->
 * \section nccport_mms_time Interface
 * - NCCPort_mms_getSysTime()
 * <!-- #interface list end -->
 */

#ifndef __NCCPort_MMS_TIME_H__
#define __NCCPort_MMS_TIME_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**NCCPort_MMS_TIME return value: success*/
#define NCCPort_MMS_TIME_SUCCESS                                 0
/**NCCPort_MMS_TIME return value: failed*/
#define NCCPort_MMS_TIME_FAILED                                  -1
/**NCCPort_MMS_TIME return value: invalid parameter*/
#define NCCPort_MMS_TIME_INVALID                                 -2

/**
 * Get current system time
 * \param time_sec output sec from 1970
 * \param time_msec output micro sec
 * \return <ul>
 *             <li> #NCCPort_MMS_TIME_SUCCESS		if successful
 *             <li> #NCCPort_MMS_TIME_FAILED			if failed
 *             <li> #NCCPort_MMS_TIME_INVALID		if parameter invalid
 *         </ul>
 */
int32_t NCCPort_mms_getSysTime(int32_t * time_sec, int32_t * time_msec);

#ifdef __cplusplus
}
#endif

#endif /* __NCCPort_MMS_TIME_H__ */
