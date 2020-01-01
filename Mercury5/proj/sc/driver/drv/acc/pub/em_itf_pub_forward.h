/****************************************************************************\
  \file     em_itf_pub.h
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
#ifndef __EM_ITF_PUB_FORWARD_H__
#define __EM_ITF_PUB_FORWARD_H__

#include "vm_types.ht"

opaque_enum(LcdTestColor_t_);
typedef enum LcdTestColor_t_ LcdTestColor_t;

typedef struct acc_Data_t_ acc_Data_t;
typedef struct adc_Data_t_ adc_Data_t;

opaque_enum(em_VoiceAecCfg_e_);
typedef enum em_VoiceAecCfg_e_ em_VoiceAecCfg_e;

opaque_enum(em_VoiceAecParam_e_);
typedef enum em_VoiceAecParam_e_ em_VoiceAecParam_e;

#endif	//__EM_ITF_PUB_FORWARD_H__
