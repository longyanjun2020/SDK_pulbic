///////////////////////////////////////////////////////////////////////////////
// File   : wavenc_mgr_confg.h
// Author : MStar Semiconductor Inc.(CA.Wang)
// Brief  : function and wav encorder config.
///////////////////////////////////////////////////////////////////////////////
#ifndef __WAVENC_MGR_CONFG_H__
#define __WAVENC_MGR_CONFG_H__


//=============================================================================
//                                 Config.
//=============================================================================


//========= Platform Option ===========
#define ON_MONTAGE


//============ IPs Option =============
#ifndef ON_MONTAGE
//#define ENABLE_WAVENC_IMAADPCM
//#define ENABLE_WAVENC_MSADPCM
//#define ENABLE_WAVENC_ALAW
//#define ENABLE_WAVENC_MULAW
//#define ENABLE_WAVENC_PCM
#endif

//=========== Example Code ============
#ifndef ON_MONTAGE
//#define WAVECN_IMAADPCM_EXAMPLE
//#define WAVECN_MSADPCM_EXAMPLE
//#define WAVECN_ALAW_EXAMPLE
//#define WAVECN_MULAW_EXAMPLE
//#define WAVECN_PCM_EXAMPLE
#endif

//====== Measure Computing Power ======
#ifdef ON_MONTAGE
//#define WAVECN_PROFILING_ALL
//#define WAVECN_PROFILING_SPLIT
#endif

#endif // __WAVENC_MGR_CONFG_H__

