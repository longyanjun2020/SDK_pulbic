////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef MDL_FMR_HANDLE_H
#define MDL_FMR_HANDLE_H

#include "vm_msgof.hc"


/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define _FMR_TRACE                      vm_dbgTrace

#if defined(__SDK_SIMULATION__)
// IMPORTANT: Now simulator has task number limitation
#define MDL_FMR_MBX                 VM_MBX_CUS41
#else
#define MDL_FMR_MBX                 VM_MBX_CUS41
#endif


#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum
{
#include "mdl_fmr_message_define__.hi"
} MdlFmrCtlMsgId_e;

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    MDL_FMR_OK = 0,
    MDL_FMR_FAIL,
    MDL_INVALID_PARAM,
    MDL_FMR_REJECT,
    MDL_FMR_SEEK_FAIL,
    MDL_FMR_TASK_CRATE_FAIL,
    MDL_FMR_TASK_DESTORY_FAIL,
    MDL_FMR_MEMORY_FAIL,
    MDL_FMR_DMAWriterInit_FAIL,
    MDL_FMR_DMAReaderInit_FAIL,
    MDL_FMR_DMAWriter_FAIL,
    MDL_FMR_DMAReader_FAIL,
    MDL_FMR_RECORD_FAIL,
    MDL_FMR_FREEState  //Use for debug Ram Dump state
} MdlFmrErrCode_e;

typedef enum
{
    MDL_FMR_POWER_OFF = 0,
    MDL_FMR_POWER_ON,
} MdlFmrPower_e;

typedef enum
{
    MDL_FMR_MUTE_OFF = 0,
    MDL_FMR_MUTE_ON,
} MdlFmrMute_e;

typedef enum
{
    MDL_FMR_STEREO_OFF = 0,
    MDL_FMR_STEREO_ON,
} MdlFmrStereo_e;

typedef enum
{
    MDL_FMR_US_BAND = 0,    /**< U.S. FM band */
    MDL_FMR_JAP_BAND        /**< JAPAN FM band */
} MdlFmrBand_e;

typedef enum
{
    MDL_FMR_AREA_TAIWAN = 0,/**< TAIWAN FM area */
    MDL_FMR_AREA_CHINA      /**< CHINA FM area */
} MdlFmrArea_e;

typedef struct
{
    u32 nFreq;                /**< channel frequency */
    u16 nRSSI;                /**< Signal strength of current channel */
    u16 nStereo;              /**< Stereo/Mono status of current channel */
    s16 nArea;                /**< FM radio area setting */
    u16 nAntennaSupported;    /**< Antenna supported */
    u16 nRecordingSupported;  /**< Encoding supported */
    u16 nStereoSupported;  /**< Stereo supported */
} MdlFmrChanInfo_t;

typedef struct
{
    union
    {
        struct
        {
            u8 nReserved   :1;
            u8 nDeEmphasis :1;
            u8 nSpace      :3;
            u8 nBpfir      :3;
            u8 nRangeBand  :8;
        }field;
        u16 nAreaParam;
    }uParam;
}MdlFmrAreaParam_t;


typedef struct
{
	u32 clock;
	u32 dBm;
} MdlFmrSdClockTab_t;



/*
typedef enum
{
  MDL_FMR_DEEMPHASIS_50US = 0,
  MDL_FMR_DEEMPHASIS_75US,
} MdlFmrDeEmphasis_e;

typedef enum
{
  MDL_FMR_STEP_50KHZ = 0,
  MDL_FMR_STEP_100KHZ,
  MDL_FMR_STEP_200KHZ,
  MDL_FMR_STEP_30KHZ,
  MDL_FMR_STEP_300KHZ
} MdlFmrStepSpace_e;

typedef enum
{
  MDL_FMR_BPFIR_100KHZ = 0,
  MDL_FMR_BPFIR_120KHZ,
  MDL_FMR_BPFIR_150KHZ,
  MDL_FMR_BPFIR_200KHZ
} MdlFmrBpfir_e;

typedef enum
{
  MDL_FMR_BEGIN_66MHZ = 0,
  MDL_FMR_BEGIN_68MHZ,
  MDL_FMR_BEGIN_73MHZ,
  MDL_FMR_BEGIN_76MHZ,
  MDL_FMR_BEGIN_87_5MHZ,
  MDL_FMR_BEGIN_87_8MHZ,
  MDL_FMR_BEGIN_88MHZ,
  MDL_FMR_BEGIN_100MHZ
} MdlFmrBeginRange_e;

typedef enum
{
  MDL_FMR_END_68MHZ = 0,
  MDL_FMR_END_73MHZ,
  MDL_FMR_END_74MHZ,
  MDL_FMR_END_87_5MHZ,
  MDL_FMR_END_90MHZ,
  MDL_FMR_END_100MHZ,
  MDL_FMR_END_108MHZ
} MdlFmrEndRange_e;

typedef struct
{
    MdlFmrBeginRange_e    FmrBeginRange;
    MdlFmrEndRange_e      FmrEndRange;
    MdlFmrDeEmphasis_e    FmrDeEmphasis;
    MdlFmrStepSpace_e     FmrStepSpace;
    MdlFmrBpfir_e         FmrBpfir;

} MdlFmrAreaConfig_t;
*/

/*
typedef struct
{
    bool (* pfnFMrxPower)(u8);
    bool (* pfnFMrxTune)(u32);
    bool (* pfnFMrxSeek)(u8, u8);
    bool (* pfnFMrxBand)(u8);
    bool (* pfnFMrxMute)(u16);
    bool (* pfnFMrxStereo)(u8);
    bool (* pfnFMrxVolumeControl)(u8 vol, u8 volext);
    bool (* pfnFMrxGetChanInfo)(u32 *, u16 *, u8 *);
    bool (* pfnFMrxGetChipInfo)(u32 *, u16 *, u16 *);
    bool (* pfnFMrxSetArea)(MdlFmrArea_e);
} MdlFmrFuncTbl_t;
*/

/*=============================================================*/
// Variable definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/
void FmrxHandler(const void *pMessage);
void MdlRadioPlayCtlExterProc(void *pMessage);
void MdlRadioPlayCtlInterProc(void *pMessage);
void MMRadioRegisterUseCaseCablback(void);
MdlFmrErrCode_e _MdlFmrxGetCability(MdlFmrChanInfo_t * pChanInfo);

#endif
