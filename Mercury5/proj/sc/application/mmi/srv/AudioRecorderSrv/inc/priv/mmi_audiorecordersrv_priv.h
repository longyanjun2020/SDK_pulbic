/**
* @file mmi_audiorecordersrv_priv.h
*

*
* Class Id: CLSID_AUDIORECORDERSRV
*
*
* @version $Id: mmi_audiorecordersrv_priv.h 41616 2009-09-28 11:40:02Z lih.wang $
*/
#ifndef __MMI_AUDIORECORDERSRV_PRIV_H__
#define __MMI_AUDIORECORDERSRV_PRIV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_audiorecordersrv.h"
/*-------------------------------------------------------------------------*/
typedef enum AudioRecSrvGetFileReason_e_
{
    AUDIO_REC_SRV_GET_FILE_REASON__NORMAL_STOP
   ,AUDIO_REC_SRV_GET_FILE_REASON__FULL_SPACE
   ,AUDIO_REC_SRV_GET_FILE_REASON__REC_ERROR
   ,AUDIO_REC_SRV_GET_FILE_REASON__INVALID
} AudioRecSrvGetFileReason_e;

typedef struct AudioRecSrvCusInfo_t_
{
    u32 nSrvInstId;
    u32 nSrvClientInsId;
    u16 nAppId;
    void *pfnCb;
} AudioRecSrvCusInfo_t;

typedef struct AudioRecSrvGetFileCusInfo_t_
{
    u32 nSrvInstId;
    u32 nSrvClientInsId;
    u16 nAppId;
    AudioRecSrvGetFileReason_e nReason;
    void *pData;
} AudioRecSrvGetFileCusInfo_t;

/*-------------------------------------------------------------------------*/
#endif /* __MMI_AUDIORECORDERSRV_PRIV_H__ */
