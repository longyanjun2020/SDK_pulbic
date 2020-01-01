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

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_mx_mp4creator.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////
#ifndef __MDL_VDR_MX_MP4CREATOR_H__
#define __MDL_VDR_MX_MP4CREATOR_H__

#include "mdl_vdr_mx_def.h"
//#define MP4MUX_EXCEPTION_HANDLER

#ifdef MP4MUX_EXCEPTION_HANDLER
#include "ms-cexcept.h"
#endif

	#if defined(MP4MUX_EXCEPTION_HANDLER)
    #define MP4MUX_EP_JUMP_BACK(err)    \
        {   \
            TRYCATCH_THROW_START    \
            e.flavor = ap_exception;    \
            e.info.int_info = err;    \
            Throw e;    \
            TRYCATCH_THROW_END  \
        }
    #else
    #define MP4MUX_EP_JUMP_BACK(err, fs_err)  vm_dbgTrace(VDR_TMT_LV1, "except err %x, FS Err %x\n", err, mx_geterrno(fs_err));
	#endif

	extern void MdlVdrWriteExceptionHandler(void);
	#define RETURN_MUX_CLOSE_ERR(err, fs_err)  \
	{   \
        MP4MUX_EP_JUMP_BACK(err, fs_err)   \
        MdlVdrWriteExceptionHandler();  \
        return; \
	}

	#if defined(MP4MUX_EXCEPTION_HANDLER)
	#define WAIT_ABORT_RETURN \
    {   \
        if (cyg_semaphore_trywait(&gMp4recAbortSem))    \
        {   \
            vm_dbgTrace((VDR_TMT_LV1, "Func=<SYMBOL> (0x%08x)]\n", __LINE__));  \
			MP4MUX_EP_JUMP_BACK(MSMERR_REC_STOP_ABORTED)   \
        }   \
	}
	#else
	extern U32 MdlVdrWriteCallback(void);
    bool MdlVdrWriteCheckException(void);
	#define WAIT_ABORT_RETURN(err)	\
	{	\
		if (FALSE == MdlVdrWriteCallback())	\
		{	\
			err = MSMERR_REC_STOP_ABORTED;   \
			return MSMERR_REC_STOP_ABORTED;	\
		}	\
		else	\
		if (FALSE == MdlVdrWriteCheckException())   \
		{   \
			err = MSMERR_FILE_WRITE_ERROR;   \
			return MSMERR_FILE_WRITE_ERROR;	\
		}   \
		else    \
		{	\
			err = MSMERR_OK;	\
		}	\
	}
	#endif

#endif // __MDL_VDR_MX_MP4CREATOR_H__
