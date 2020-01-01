#ifndef _MMPF_VIDDEC_DEF_H_
#define _MMPF_VIDDEC_DEF_H_

#include "mmpf_typedef.h"
#include "mmp_err.h"
#include "mmpf_media_struct.h"
#include "mmp_vidplay_inc.h"

/**********************************************************************************************************/
/* the proto-type of video APIs*/



/**
 @brief                                 Alloc nessary memory for the codec
 @param[in]     h                       the video codec instance
 @param[in]     mem_start_addr          legal video memory start addr
 @param[in]     mem_end_addr            legal video memory end addr
 @return        MMP_ERR
*/
typedef MMP_ERR     (VIDDEC_AllocMem_Func)(MMP_HANDLE *h, MMP_ULONG mem_start_addr, MMP_ULONG mem_end_addr);

/**
 @brief                                 Connect the video codec with the input bitstream bufffer
 @param[in]     h                       the video codec instance
 @param[in]     buf                     bitstream buffer
 @param[out]    buf_size                buffer size
 @return        MMP_ERR
*/
typedef MMP_ERR     (VIDDEC_ConnectBSBuf_Func)(MMP_HANDLE *h, MMP_UBYTE *buf, MMP_ULONG buf_size, MMP_ULONG buf_type);

/**
 @brief                                 Init video codec by decoding video headers
 @param[in]     h                       the video codec instance
 @param[in]     buf                     bitstream buffer
 @param[in]     length                  header size
 @param[in]     width                   video width,  if the width  is not zero, the video width  is assigned by outside.
 @param[in]     height                  video height, if the height is not zero, the video height is assigned by outside.
 @param[in]     decode_header           decode headers or not, if this is FALSE, the codec does not init complete here.
 @return        MMP_ERR
*/
typedef MMP_ERR     (VIDDEC_Init_Func)(MMP_HANDLE *h,MMP_UBYTE* buf, MMP_ULONG length, MMP_ULONG width, MMP_ULONG height,MMP_UBYTE decode_header);

/**
 @brief                         decode the video data
 @param[in]     h               the video codec instance
 @param[in]     bs_pos          the start position where the data begins from
 @param[in]     length          the length of decode data
 @param[in]     time            the time stamp belongs to the current data
 @param[out]    is_decode_done  is the decoding of the WHOLE frame is done or not
 @param[in]     param1          extension parameter, depend on diffrent codecs
 @return        MMP_MEDIA_ERROR
*/
typedef MMP_ERR     (VIDDEC_DecodeData_Func)   (MMP_HANDLE *h, MMP_ULONG bs_addr, MMP_ULONG length, MMP_ULONG64 time, MMP_ULONG *decode_done, void* param1);


/**
 @brief                 reset the video codec.
 @param[in] h           the video codec instance
 @param[in] bResetAll   reset all or not
 @return                MMP_ERR
*/
typedef MMP_ERR     (VIDDEC_DeInit_Func) (MMP_HANDLE *h,const MMP_BOOL bResetAll);


/**
 @brief         Close the video codec, if the video codec is closed, it can not be used anymore.
 @param[in] h   the video codec instance
 @return        MMP_ERR
*/
typedef MMP_ERR     (VIDDEC_Close_Func)        (MMP_HANDLE *h);

/**
 @brief                         get the reconstructed video frame
 @param[in]     h               the video codec instance
 @param[out]    output_frame    the reconstructed video frame
 @return        MMP_ERR
*/
typedef MMP_ERR     (VIDDEC_GetFrame_Func)(MMP_HANDLE *h,MMP_MEDIA_FRAME *output_frame);

/**
 @brief         tell the codec that the frame has been refreshed
 @param[in] h   the video codec instance
*/
typedef void            (VIDDEC_RefreshFrame_Func)(MMP_HANDLE *h,MMP_ULONG addr);


/**
 @brief                 get the current state of the video codec
 @param[in]     h       the video codec instance
 @param[out]    pState  current state of the codec
 @return                MMP_ERR
*/
typedef MMP_ERR     (VIDDEC_GetState_Func)(MMP_HANDLE *h,MMP_M_STATE *State);

/**
 @brief                 set the current state of the video codec
 @param[in]     h       the video codec instance
 @param[in]     state   the state
*/
typedef void            (VIDDEC_SetState_Func)(MMP_HANDLE *h,MMP_M_STATE state);

/**
 @brief                         get the reconstructed video frame
 @param[in]     h               the video codec instance
 @param[out]    output_frame    the reconstructed video frame
 @return        MMP_ERR
*/
typedef MMP_ULONG64     (VIDDEC_GetTime_Func) (MMP_HANDLE *h);

/**
 @brief                 get the general video infomation
 @param[in]     h       the video codec instance
 @param[out]    info    the general video infomation
 @return
*/
typedef void            (VIDDEC_GetInfo_Func) (MMP_HANDLE *h,MMP_VIDEO_INFO *info);

/**
 @brief         check if the frame is reconstructed or not
 @param[in] h   the video codec instance
 @return        TRUE/FALSE
*/
typedef MMP_ULONG       (VIDDEC_IsFrameDecodeDone_Func)(MMP_HANDLE *h);

/**
 @brief                     set the video frame number
 @param[in]     h           the video codec instance
 @param[in]     frame_num   frame number
*/
typedef void            (VIDDEC_SetFrameNum_Func)(MMP_HANDLE *h,MMP_ULONG frame_num);

/**
 @brief                     get the video frame number
 @param[in]     h           the video codec instance
 @return                    frame number
*/
typedef MMP_ULONG       (VIDDEC_GetFrameNum_Func)(MMP_HANDLE *h);

typedef MMP_ERR         (VIDDEC_GetFreeFrame_Func)(MMP_HANDLE *h,MMP_MEDIA_FRAME *free_frame);

/**
 @brief                 Reset the video codec if the HW is hanging on somewhere
 @param[in]     h       the video codec instance
 @return                MMP_ERR
*/
typedef MMP_ERR         (VIDDEC_Reset_Func)(MMP_HANDLE *h);

typedef MMP_ERR         (VIDDEC_FlushFrame_Func)(MMP_HANDLE *h);
#if defined(__RTK_OS__)
typedef MMP_ERR         (VIDDEC_SetCodecInf_Func)(MMP_HANDLE *h, MMP_ULONG ulTrackNo, MMP_ULONG ulCodecSize);
#endif
/**********************************************************************************************************/


/**********************************************************************************************************/
/* the definations of video function pointers */
typedef VIDDEC_AllocMem_Func*            VIDDEC_AllocMem_FuncPtr;
typedef VIDDEC_Init_Func*                VIDDEC_Init_FuncPtr;
typedef VIDDEC_ConnectBSBuf_Func*        VIDDEC_ConnectBSBuf_FuncPtr;
typedef VIDDEC_DecodeData_Func*          VIDDEC_DecodeData_FuncPtr;
typedef VIDDEC_DeInit_Func*              VIDDEC_DeInit_FuncPtr;
typedef VIDDEC_Close_Func*               VIDDEC_Close_FuncPtr;
typedef VIDDEC_GetFrame_Func*            VIDDEC_GetFrame_FuncPtr;
typedef VIDDEC_RefreshFrame_Func*        VIDDEC_RefreshFrame_FuncPtr;
typedef VIDDEC_GetState_Func*            VIDDEC_GetState_FuncPtr;
typedef VIDDEC_SetState_Func*            VIDDEC_SetState_FuncPtr;
typedef VIDDEC_GetTime_Func*             VIDDEC_GetTime_FuncPtr;
typedef VIDDEC_GetInfo_Func*             VIDDEC_GetInfo_FuncPtr;
typedef VIDDEC_IsFrameDecodeDone_Func*   VIDDEC_IsFrameDecodeDone_FuncPtr;
typedef VIDDEC_SetFrameNum_Func*         VIDDEC_SetFrameNum_FuncPtr;
typedef VIDDEC_GetFrameNum_Func*         VIDDEC_GetFrameNum_FuncPtr;
typedef VIDDEC_GetFreeFrame_Func*        VIDDEC_GetFreeFrame_FuncPtr;
typedef VIDDEC_Reset_Func*               VIDDEC_Reset_FuncPtr;
typedef VIDDEC_FlushFrame_Func*          VIDDEC_FlushFrame_FuncPtr;
#if defined(__RTK_OS__)
typedef VIDDEC_SetCodecInf_Func*         VIDDEC_SetCodecInf_FuncPtr;
#endif
/**********************************************************************************************************/


typedef struct {
    VIDDEC_AllocMem_FuncPtr          MMPF_VIDDEC_AllocMem;
    VIDDEC_Init_FuncPtr              MMPF_VIDDEC_Init;
    VIDDEC_ConnectBSBuf_FuncPtr      MMPF_VIDDEC_ConnectBSBuf;
    VIDDEC_DecodeData_FuncPtr        MMPF_VIDDEC_DecodeData;
    VIDDEC_DeInit_FuncPtr            MMPF_VIDDEC_DeInit;
    VIDDEC_Close_FuncPtr             MMPF_VIDDEC_Close;
    VIDDEC_GetFrame_FuncPtr          MMPF_VIDDEC_GetFrame;
    VIDDEC_RefreshFrame_FuncPtr      MMPF_VIDDEC_RefreshFrame;
    VIDDEC_GetState_FuncPtr          MMPF_VIDDEC_GetState;
    VIDDEC_SetState_FuncPtr          MMPF_VIDDEC_SetState;
    VIDDEC_GetTime_FuncPtr           MMPF_VIDDEC_GetTime;
    VIDDEC_GetInfo_FuncPtr           MMPF_VIDDEC_GetInfo;
    VIDDEC_IsFrameDecodeDone_FuncPtr MMPF_VIDDEC_IsFrameDecodeDone;
    VIDDEC_SetFrameNum_FuncPtr       MMPF_VIDDEC_SetFrameNum;
    VIDDEC_GetFrameNum_FuncPtr       MMPF_VIDDEC_GetFrameNum;
    VIDDEC_GetFreeFrame_FuncPtr      MMPF_VIDDEC_GetFreeFrame;
    VIDDEC_Reset_FuncPtr             MMPF_VIDDEC_Reset;
    VIDDEC_FlushFrame_FuncPtr        MMPF_VIDDEC_FlushFrame;
    #if defined(__RTK_OS__)
    VIDDEC_SetCodecInf_FuncPtr       MMPF_VIDDEC_SetCodecInf;
    #endif
} MMPF_VIDEO_FUNC;


/**
 @brief         Load the video codec, assign function pointers
 @param[in]     codec_id        MPEG4 / H.264 / H.263...etc
 @param[in]     func            the structure of function pointers
 @return        MMP_HANDLE      the handle of video codec 
*/
MMP_HANDLE MMPF_VIDEO_Open(MMP_ULONG codec_id, MMPF_VIDEO_FUNC *func);

#if (NEW_VIDEODEC_FLOW == 1)
MMP_ERR MMPF_VideoDecoder_SetBufRefreshDone(MMP_UBYTE idx);
MMP_ERR MMPF_VideoDecoder_ResetDecBuf(void);
#endif



#endif