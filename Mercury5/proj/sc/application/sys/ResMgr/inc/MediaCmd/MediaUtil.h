/**
* @file MediaRsp.h
*
* This header file defines the data structures of Media Response
*
*/

#ifndef __MEDIARSP_H__
#define __MEDIARSP_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Rsp.h"
#include "MediaRspItf.h"
#include "MediaCmn.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
bool Media_IsAudRecordFormatSupport(u32 uCapTab, u16 uFormat);
bool Media_IsAudPlaybackFormatSupport(u32 uCapTab, u16 uFormat);
bool Media_IsVdoRecordFormatSupport(u32 uCapTab, u16 uFormat);
bool Media_IsVdoPlaybackFormatSupport(u32 uCapTab, u16 uFormat);
bool Media_IsFormatSupport(Media_CapabilityTab_t *pCapTab, Media_FormatGroup_e eGroup, Media_Format_e eFormat);
bool Media_IsPlaybackFormatSupport(Media_CapabilityTab_t *pCapTab, Media_Format_e eFormat);
bool Media_IsVdoCodecSupport(Media_CapabilityTab_t *pCapTab, Media_VdoCodec_e eVdoCodec);
bool Media_IsAudCodecSupport(Media_CapabilityTab_t *pCapTab, Media_AudCodec_e eAudCodec);
bool Media_IsVdoEncFpsSuppport(Media_CapabilityTab_t *pCapTab, Media_VdoEncodeFps_e eVdoEncFps);
bool Media_IsVdoEncResSupport(Media_CapabilityTab_t *pCapTab, Media_VdoCodec_e eVdoCodec, Media_VdoEncodeRes_e eVdoEncRes);
u32 Media_EmuMaxRomSize(Media_CapabilityTab_t *pCapTab);
/**
 *  _Media_Codec_Retrieve_Buff_info
 *  @brief  malloc ringbuff need memory and do size and address 32 byte alignments
 *
 *	@param  u8srcbuf		--> buff data source address
 *  @param  u32len			--> buff data source length
 *  @param  pInfo			--> buff sample rate
 *
 *  @retval MAE_RET_SUCCESS  Success
 *  @retval MAE_RET_FAILED   Failed
 */
ResMgr_ErrorCode_e Media_RetrieveBuffInfo(Media_Format_e eDataFormat, u8 *u8srcbuf, u32 u32len, u8 *u8cachebuf, Media_AudCodecInfo_t *pInfo);

void Media_InitItf(Media_CmnItf_t const *pMediaItf);
const Media_CmnItf_t* Media_GetItf(void);
#endif //__MEDIARSP_H__

