/****************************************************************************\
  \file     em_itf_pub_types.h
  \brief    prototype of EM API and other definitions
  \date     2007/10/03
  \version  1.00
  \author   Peterwei Wang
  \warning

--------------------------------------------------------------------------
  Historical :
-----------------------------------------------------------------------------
    Date  | Author  | Err  |  Modification
----------+---------+------+-----------------------------------------------
----------+---------+------+-----------------------------------------------
\****************************************************************************/
#ifndef __EM_ITF_PUB_TYPES_H__
#define __EM_ITF_PUB_TYPES_H__

#include "vm_types.ht"
#include "em_itf_pub_forward.h"

#include "drv_vm_rtc.h"			// TODO : include forward instead
//#include "mdl_bat_pars_pub.h"	// TODO : include forward instead

#include "vm_abb_pub.h"				// TODO : include types instead
#include "dev_acc_pub_types.h"

opaque_enum(LcdTestColor_t_)
{
    LCD_COLOR_RED = 0,
    LCD_COLOR_GREEN,
    LCD_COLOR_BLUE,
    LCD_COLOR_WHITE,
    LCD_COLOR_BLACK
};

struct acc_Data_t_
{
    u16 nb_acc;
    u16 acc_status[ACC_MAX];
};

struct adc_Data_t_
{
    u16 nb_channels;
    u16 adcChannel[VM_ABB_ADC_NB_MAX_CHANNELS];
};


/**
 * @brief The enumeration defines the AEC configuration type.
 */
opaque_enum(em_VoiceAecCfg_e_)
{
  EM_AEC_CFG_HANDSET_HEADSET = 0,
  EM_AEC_CFG_SPEAKERPHONE,
  EM_AEC_CFG_MAX
};

/**
 * @brief The enumeration defines the AEC parameter type.
 */
opaque_enum(em_VoiceAecParam_e_)
{
  EM_AEC_FIXED_DELAY = 0,     /* AEC fixed delay (1-3) */
  EM_AEC_NS_MIN_WEIGHT,       /* NS Min weigh (3276-16383) */
  EM_AEC_MAX_CNG_MAG,         /* Max CNG magnitude (0-32767) */
  EM_AEC_NLP_MIN,             /* NLP MIN Gain (1-32767) */
  EM_AEC_NLP_SHIFT,           /* NLP Shift (1-13) */
  EM_AEC_DT_THR,              /* DT detector threshold (5-8) */
  EM_AEC_DT_SENS_THR,         /* DT detector sensitivity threshold (8192-12287) */
  EM_AEC_FREQ_DT_THR,         /* Freq. domain DT detector tune threshold (1-32767) */
  EM_AEC_LPF_CUT_OFF,         /* Number of subbands for freq. domain DT detector (1-64) */
  EM_AEC_ENHANCED_NS_ENABLE,  /* AEC Enhanced NS enable or disable  */
  EM_AEC_PARAM_TYPE_MAX
};

/*=============================================================*/
// Variable definition
/*=============================================================*/
extern bool g_bTSTest;		// em_test.c

#endif//__EM_ITF_PUB_TYPES_H__
