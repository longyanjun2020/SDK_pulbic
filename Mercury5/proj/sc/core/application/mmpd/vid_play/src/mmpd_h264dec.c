/** @file mmpd_h264dec.c
 *  @brief Implementation for H.264 decoder device driver
 *  @author SWYang
 *  @version 1.0 Initial Version
 */
#ifdef BUILD_CE
#undef BUILD_FW
#endif

#include "mmp_lib.h"
#include "mmpd_h264dec.h"
#include "mmph_hif.h"
//#include "mmpd_system.h"
//#include "ait_utility.h"

static MMP_ULONG m_ulH264InfoAddr;

/** @brief Set H264 bitstream addresses to the firmware in host-parsed memory mode

@param[in] ulVideoBSAddr The video bitstream address in the host
@param[in] ulVideoBSSize The video bitstream size in the host
@return The status of the function call
@retval MMP_MP4VD_ERR_PARAMETER The bitstream address or the video bitstream size is not the multiple of 32
*/
MMP_ERR MMPD_H264DEC_SetBitstreamAddr(const MMP_ULONG ulVideoBSAddr, const MMP_ULONG ulVideoBSSize)
{

	if ((ulVideoBSAddr | ulVideoBSSize) & 0x1F) {
		return MMP_MP4VD_ERR_PARAMETER;
	}
#if 0	
	MMPH_HIF_RegSetL(H264DEC_VLD_RINGBUF_LOWERBOUND_ADDR, ulVideoBSAddr);
	MMPH_HIF_RegSetL(H264DEC_VLD_RINGBUF_HIGHERBOUND_ADDR, ulVideoBSAddr + ulVideoBSSize);
#endif
    return MMP_ERR_NONE;
}

/**
 @brief         Config H264 memory map
 @param[in]     type    the memory type
 @param[in,out] addr    the memory address
 @param[in]     size    the memory size
 @param[in]     align   alignment
 @return        MMP_ERR
*/
MMP_ERR MMPD_H264_ConfigMem(MMP_ULONG type, MMP_ULONG *addr, MMP_ULONG size, MMP_ULONG align)
{
    MMP_ULONG mem_offset;
    MMP_ERR		mmpstatus;
   
    mem_offset = *addr & (align - 1) ;
    mem_offset = mem_offset ? (align - mem_offset) : 0;
    
    *addr += mem_offset;

    if (type == MMPD_H264_INFO_MEM) {
        m_ulH264InfoAddr = *addr;
    }
    
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, type);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, *addr);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 8, size);
    
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, H264_CONFIG_MEM_MAP | HIF_VID_CMD_H264_DEC);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);

    if (mmpstatus)
    	return mmpstatus;
    
    *addr += (size);
    
    return MMP_ERR_NONE;
}

MMP_ERR MMPD_H264_ConfigCodec(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SendCmd(GRP_IDX_VID, H264_DEC_CODEC_INIT | HIF_VID_CMD_H264_DEC);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    return MMP_ERR_NONE;
}

MMP_ERR MMPD_H264_DecodeData(MMP_ULONG dest_addr,MMP_ULONG length)
{
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 0, dest_addr);
    MMPH_HIF_SetParameterL(GRP_IDX_VID, 4, length);
     
    MMPH_HIF_SendCmd(GRP_IDX_VID, H264_DEC_DECODE_DATA | HIF_VID_CMD_H264_DEC);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    return MMP_ERR_NONE;
}

MMP_ERR MMPD_H264_IsDecodeDone(MMP_ULONG *decode_done)
{
	MMP_ERR	mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, H264_CHECK_DECODE_DONE | HIF_VID_CMD_H264_DEC);

    if (mmpstatus) {
        MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    	return mmpstatus;
    }
    *decode_done = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
    return MMP_ERR_NONE;
}

MMP_ERR MMPD_H264_GetVideoInfo(MMPD_H264_INFO *info)
{
    MMP_ERR mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    
    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_VID, H264_GET_VIDEO_INFO | HIF_VID_CMD_H264_DEC);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    if (mmpstatus)
    	return mmpstatus;
    
    MMPH_HIF_MemCopyDevToHost((MMP_UBYTE*)info,(MMP_ULONG)m_ulH264InfoAddr, sizeof(MMPD_H264_INFO));
    
    return MMP_ERR_NONE;
}

MMP_ERR MMPD_H264_GetVideoFrameAddr(MMP_ULONG *addr)
{
	MMP_ERR	mmpstatus;

    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    
    MMPH_HIF_SendCmd(GRP_IDX_VID, H264_GET_VIDEO_FRAME | HIF_VID_CMD_H264_DEC);
    if (mmpstatus) {
    	MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    	return mmpstatus;
    }
    
    *addr = MMPH_HIF_GetParameterL(GRP_IDX_VID, 0);
    
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
    return MMP_ERR_NONE;
}

MMP_ERR MMPD_H264_RefreshFrame(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_VID, 0);
    MMPH_HIF_SendCmd(GRP_IDX_VID, H264_SET_FRAME_REFRESH | HIF_VID_CMD_H264_DEC);
    MMPH_HIF_ReleaseSem(GRP_IDX_VID);
    
    return MMP_ERR_NONE;
}

#ifdef BUILD_CE
#define BUILD_FW
#endif
