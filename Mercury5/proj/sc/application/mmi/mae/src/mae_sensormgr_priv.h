/**
* @file    mae_sensormgr_priv.h
*
* @author  mark.yang@mstarsemi.com
* @version $Id: mae_sensormgr_priv.h 540 2009-03-31 11:04:04Z mark.yang $
*/
#ifndef __MAE_SENSORMGR_PRIV_H__
#define __MAE_SENSORMGR_PRIV_H__

#include "mmi_mae_common_def.h"

/**
* Register a listener to a sensor to get the information regularly.
* A instance can register only once for one sensor (and associate a call back).
*
* The sensor can be turn-on only when there exist register for that sensor,
* and can be turn-off if no one is interested in the specific sensor to save power.
*
* @param pThis Pointer to the ISensorMgr interface
* @param sensor Sensor ID
* @param delay Delay time in millisecond between each sensor value call back
* @param bSwitchContext switch context to pObj when calling the callback function.
* @param pNOtifyCb The call back function. This function will be called regularly and bring the sensor's information to client
* @param pObj object instance, bypass to the call back function
* @see ISENSORMGR_AddListener
*/
#define ISENSORMGR_AddListenerPrivExt(pThis, sensor, delay, bSwitchContext, listenOnPowerSavingMode, pNotifyCb, pObj)	GET_FUNCTBL(pThis,ISensorMgr)->AddListener(pThis, sensor, delay, bSwitchContext, listenOnPowerSavingMode, pNotifyCb, pObj)



#ifdef __MAE_SENSORMGR_C__
const u32 g_nSENSOR_NOTIFY_DELAY_MS[] =
{
	100,	/**< SENSOR_NOTIFY_DELAY_FASTEST */
	200,	/**< SENSOR_NOTIFY_DELAY_GAME */
	1000,	/**< SENSOR_NOTIFY_DELAY_NORMAL */
	500,	/**< SENSOR_NOTIFY_DELAY_UI */
};
#else // __MAE_SENSORMGR_C__
extern const u32 g_nSENSOR_NOTIFY_DELAY_MS[];
#endif // __MAE_SENSORMGR_C__

#endif //  __MAE_SENSORMGR_PRIV_H__
