/**
 * @page Analog BaseBand Management Public Interface
 *
 *
 * @section intro_sec Introduction
 *
 * This document describes the Analog BaseBand Management Public Interface
 *
 *  <hr>
 * @section SectionMMI2ABB 1. MMI to ABB Interface
 *
 * @li @ref vm_abbPowerCtrl
 * @li @ref vm_abbAdcAcquire
 * @li @ref vm_abbAdcTouchscreenIrqCtrl
 *
 *  <hr>
 * @section SectionABB2MMI 2. System to MMI
 *
 *  \li @ref VM_ABB_ADC_RESULT_IND      message sent when a ADC measurement is finished
 *  \li @ref VM_ABB_TOUCHSCREEN_PEN_DETECT_IND      message sent when a Touchscreen Pen press is detected
 *
 *  <hr>
 * @section Usage 3. Usage
 *
 *
 */


/*!
 * @file  vm_abb.h
 * @brief MMI to Analog BaseBand Public Interface
 *
 *  This file defines the Analog BaseBand Management Public interface that is offered to the MMI
 *
 *  The interface allows to :
 *   \li
 *
 */

#ifndef __VM_ABB_H__
#define __VM_ABB_H__

#include "vm_types.ht"
#include "sys_sys_vm_sys.h"

#include "vm_msgof.hc"

/**
 * @brief List of messages sent by System management to Customer tasks
 *
 */
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "vm_abb_message_define__.hi"
};

/*
 * @brief  Max Number of channels to measure consecutively
 *
 */
#define VM_ABB_ADC_NB_MAX_CHANNELS 4

/*
 * @brief Structure containing the results of a ADC conversion
 *
 */
typedef struct {
    u16 nb_channels;
    u16 data[VM_ABB_ADC_NB_MAX_CHANNELS]; ///< adc result data
} DrvAbbAdcResults_t;

#endif /* __VM_ABB_H__*/
