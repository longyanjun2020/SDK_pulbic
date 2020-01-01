/**
* @file    Mdl_tv_pub_api.h
* @version
* @brief   Public apis of TV middleware
*
*/

#ifndef __MDL_TV_PUB_API_H__
#define __MDL_TV_PUB_API_H__

#include "vm_types.ht"
#include "osdefs.hc"
#include "Mdl_tv_pub_forward.h"




/**
 * @brief Start a polling timer which will call atv_pollingSync periodically.
 * @param[in] nInterval polling interval in ms.
 * @retval void
 */
void MdlTvStartPolling(u32 nInterval);

/**
 * @brief Stop the polling timer.
 * @retval void
 */
void MdlTvStopPolling(void);


/**
 * @brief Release TV driver module.
 * @param[in] eModule module type 
 * @retval bool Success or not.
 */
bool MdlTvReleaseModule(Mdl_Tv_Sldlm_Module_e eModule);

/**
 * @brief Load TV driver module.
 * @param[in] eModule module type 
 * @retval bool success or not
 */ 
bool MdlTvLoadModule(Mdl_Tv_Sldlm_Module_e eModule);


/**
 * @brief Query if the driver module is already loaded.
 * @param[in] eModule module type 
 * @retval Mdl_Tv_Sldlm_Status_e Ready or not. (MDL_TV_SLDLM_READY / MDL_TV_SLDLM_NOT_READY)
 */
Mdl_Tv_Sldlm_Status_e MdlTvQuerySldlmStatus(Mdl_Tv_Sldlm_Module_e eModule);


#endif //__MDL_TV_PUB_API_H__
