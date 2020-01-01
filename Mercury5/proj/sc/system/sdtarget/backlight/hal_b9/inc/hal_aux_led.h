/**
 * @file hal_aux_led.h
 * @brief AUX LED hal layer
 */
#ifndef __AUX_LED_H__
#define __AUX_LED_H__

#include "vm_types.ht"

typedef enum {
	AUX_LED_0_PER_15 = 0,
	AUX_LED_1_PER_15,
	AUX_LED_2_PER_15,
	AUX_LED_3_PER_15,
	AUX_LED_4_PER_15,
	AUX_LED_5_PER_15,
	AUX_LED_6_PER_15,
	AUX_LED_7_PER_15,
	AUX_LED_8_PER_15,
	AUX_LED_9_PER_15,
	AUX_LED_10_PER_15,
	AUX_LED_11_PER_15,
	AUX_LED_12_PER_15,
	AUX_LED_13_PER_15,
	AUX_LED_14_PER_15,
	AUX_LED_15_PER_15
} AuxLedDutyCycle_e;


typedef enum {
	AUX_LED_1 = 1,
	AUX_LED_2,
	AUX_LED_3,
	AUX_LED_4,
} AuxLedComponent_e;


/** HalAuxWLedPwmEnable
* @brief        HAL function to on/off Aux PWM
* @param[in]    on PWM on or off
* @retval       0 or 1
*
*/
s32 HalAuxWLedPwmEnable(bool bOn);

/** HalAuxWLedOutputEnable
* @brief        HAL function to on/off output
* @param[in]    nNum: The LED number (1~4)
* @param[in]    bOn: Output on or off
* @retval       0/1
*
*/
s32 HalAuxWLedOutputEnable(u8 nNum, bool bOn);

/** HalAuxWLedSetRatio
* @brief        HAL function to on/off output
* @param[in]    nRatio: ratio (0~15)
* @retval       0/1
*
*/
s32 HalAuxWLedSetRatio(u8 nRatio);

/** HalAuxWLedCurrentControl
* @brief        HAL function to control WLed current.
* @param[in]    nWLedCurrent
* @retval       0/1
*
*/
s32 HalAuxWLedCurrentControl(u8 nWLedCurrent);

/** HalAuxWLedGpoEnalbe
* @brief        HAL function to enable WLed GPO function
* @param[in]    nNum: The LED number (1~4)
* @param[in]    bOn: GPO function enable/disable
* @retval       0/1
*
*/
s32 HalAuxWLedGpoEnable(u8 nNum, bool bOn);

/** HalAuxWLedGpoOutputControl
* @brief        HAL function to control WLed GPO function high/low
* @param[in]    nNum: The LED number (1~4)
* @param[in]    bCtrl: control output high/low
* @retval       0/1
*
*/
s32 HalAuxWLedGpoOutputControl(u8 nNum, bool bCtrl);

/** HalAuxWLedFastSync
* @brief        HAL function to on/off Fast Sync mode
* @param[in]    enable: on/off
* @retval       0/1
*
*/
s32 HalAuxWLedFastSync(u8 enable);

/** HalAuxWLedExtPwm
* @brief        HAL function to on/off External PWM mode
* @param[in]    enable: on/off
* @retval       0/1
*
*/
s32 HalAuxWLedExtPwm(u8 enable);

#ifdef __WLED_SHUNT_SUPPORT__
/** HalAuxWLedSetShunt
* @brief        HAL function to set shunt (1 channel support 2 LED)
* @param[in]    channel1: 1 enable, 0 disable
* @param[in]    channel2: 1 enable, 0 disable
* @param[in]    channel3: 1 enable, 0 disable
* @param[in]    channel4: 1 enable, 0 disable
* @retval       N/A
*
*/
void HalAuxWLedSetShunt(u8 channel1, u8 channel2, u8 channel3, u8 channel4);
#endif

#endif //__AUX_LED_H__
