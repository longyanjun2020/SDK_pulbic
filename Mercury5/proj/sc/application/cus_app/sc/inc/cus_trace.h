#ifndef __CUS_TRACE_H__
#define __CUS_TRACE_H__

#include "vm_types.ht"

typedef struct
{
    u32 ident;
    u32 diaglevel;	
} cus_TrcLevel_t;


#ifdef __EM_MMI_SHOW_INDICATOR__

typedef enum
{
    CUS_SHOW_IND_TRC_OFF_ID = 0,
    CUS_SHOW_IND_TRC_SAVING_ID = 1,
    CUS_SHOW_IND_TRC_AUDIO_ID = 2,
    CUS_SHOW_IND_TRC_DBBMMP_ID = 3,
    CUS_SHOW_IND_TRC_DF_ID = 4,
    CUS_SHOW_IND_TRC_L1_ID = 5,
    CUS_SHOW_IND_TRC_ON_ID = 6,
    CUS_SHOW_IND_TRC_PS_ID = 7,
    CUS_SHOW_IND_TRC_SIM_ID = 8,
    CUS_SHOW_IND_TRC_UD_ID = 9,
    CUS_SHOW_IND_TRC_WARNING_ID = 10,
    CUS_SHOW_IND_TRC_MAX_ID
} cus_ShowIndTrc_e;

#endif

//if change , must modify trcGroup in cus_trace.c
typedef enum
{
    CUS_TRACE_AUDIO_1 = 1,
    CUS_TRACE_AUDIO_2,
    CUS_TRACE_AUDIO_3,
    CUS_TRACE_DEFAULT,    		
    CUS_TRACE_SMS,
    CUS_TRACE_MMS,
    CUS_TRACE_WAP,
    CUS_TRACE_JAVA,
    CUS_TRACE_SS,
    CUS_TRACE_BT,
    CUS_TRACE_USB,
    CUS_TRACE_CAM,
    CUS_TRACE_FS,
    CUS_TRACE_FM,
    CUS_TRACE_ATV,
    CUS_TRACE_QQ
} cus_TrcProfile_e;

typedef enum
{
   TYPE_CUS_TRACE_VIA_SMS,
   TYPE_CUS_TRACE_VIA_SD,
   TYPE_CUS_TRACE_AUDIO_1,
   TYPE_CUS_TRACE_AUDIO_2,
   TYPE_CUS_TRACE_AUDIO_3,
   TYPE_CUS_TRACE_DEFAULT,
    TYPE_CUS_TRACE_SMS,         
   TYPE_CUS_TRACE_MMS,
   TYPE_CUS_TRACE_WAP,
   TYPE_CUS_TRACE_JAVA,
   TYPE_CUS_TRACE_SS,
   TYPE_CUS_TRACE_BT,
   TYPE_CUS_TRACE_USB,
   TYPE_CUS_TRACE_CAM,
   TYPE_CUS_TRACE_FS,
   TYPE_CUS_TRACE_FM,
   TYPE_CUS_TRACE_ATV,
   TYPE_CUS_TRACE_QQ,
} cus_TrcType_e;

void cus_TrcSetGroupLevel(cus_TrcLevel_t *trcLevel);
void cus_TrcSetGroupIdLevel(cus_TrcLevel_t *trcLevel);
void cus_TrcGroup(u8 group);
s32 cus_TrcEnalbe(u8 mode);
s32 cus_TrcDisable(u8 mode);
void cus_TrcEnableAudioDump(u16 u16Pcmid);
void cus_TrcDisableAudioDump(void);	
#if defined(__ENABLE_REDIRECT_DEFAULT_TRC__)
void cus_TrcEnableDef(void);
#endif

void cus_TrcReset(void);
//bool cus_TaskInfo_Filter (u8 TskId);
void cus_TrcDisplayReq(u8 *string);
void cus_TrcStopDisplayReq(void);

#endif

