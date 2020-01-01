/// @ait_only
/** @file mmpd_mp4vdec.c
@brief MPEG4 and H.263 decoder
@author Truman Yang
 
@version 1.1
*/

/** @addtogroup MMPD_MP4VDEC
 *  @{
 */

#ifdef BUILD_CE
#undef BUILD_FW
#endif

#include "mmp_lib.h"
#include "mmpd_mp4vdec.h"
#include "mmph_hif.h"
#include "mmpd_system.h"
//#include "ait_utility.h"// for PRINTF


//==============================================================================
//
//                              VARIABLES
//
//==============================================================================


//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

#if 0 // for IDE function name list by section
void _____Property_Interface_____(){}
#endif

/** @name Set Properties
@{
These functions set the properties.
*/

/** @brief Set the deblock buffers

@param[in] ulY Y output buffer starting address
@param[in] ulU U output buffer starting address
@param[in] ulV V output buffer starting address
@param[in] usWidth The width of the video
@param[in] usHeight The height of the video
@return Always MMP_ERR_NONE for success
*/
MMP_ERR MMPD_MP4VDEC_SetDeblockBuffers(const MMP_ULONG ulY, const MMP_ULONG ulU, const MMP_ULONG ulV,
                                    const MMP_USHORT usWidth, const MMP_USHORT usHeight)
{   
    return MMP_ERR_NONE;
}


/** @brief Set bitstream addresses to the firmware in host-parsed memory mode

@param[in] ulVideoBSAddr The video bitstream address in the host
@param[in] ulVideoBSSize The video bitstream size in the host
@return The status of the function call
@retval MMP_MP4VD_ERR_PARAMETER The bitstream address or the video bitstream size is not the multiple of 32
*/
MMP_ERR MMPD_MP4VDEC_SetBitstreamAddr(const MMP_ULONG ulVideoBSAddr, const MMP_ULONG ulVideoBSSize)
{
    return MMP_ERR_NONE;
}

/** @brief Set the video auxiliary buffers

@param[in] ulMVPred Motion vector prediction buffer starting address
@param[in] ulDataPartition Data partition buffer starting address
@param[in] ulHPredict Horizontal prediction buffer starting address
@param[in] ulVPredict Vertical prediction buffer starting address
@return Always MMP_ERR_NONE for sucess
*/
MMP_ERR MMPD_MP4VDEC_SetAuxiliaryBuffers(const MMP_ULONG ulMVPred, const MMP_ULONG ulDataPartition, 
                                                 const MMP_ULONG ulHPredict, const MMP_ULONG ulVPredict)
{
    return MMP_ERR_NONE;
}

/** @brief Set the video auxiliary buffers

@param[in] ulY Y output buffer starting address
@param[in] ulU U output buffer starting address
@param[in] ulV V output buffer starting address
@param[in] usWidth The width of the video
@param[in] usHeight The height of the video
@param[in] usBufferUsed The number of buffers. It's used to adjust the reference address
@return Always MMP_ERR_NONE for success
*/
MMP_ERR MMPD_MP4VDEC_SetVideoOutBuffers(const MMP_ULONG ulY, const MMP_ULONG ulU, const MMP_ULONG ulV,
                                        const MMP_USHORT usWidth, const MMP_USHORT usHeight,
                                        const MMP_USHORT usBufferUsed)
{
    return MMP_ERR_NONE;
}
// end of properties
/// @}

#if 0 // for IDE function name list by section
void _____Operations_____(){}
#endif

/** @brief Init the decoder

@param[in] bHaveFirmware If the firmware exist or not.
@param[in] callback The callback functions
@return Always return success
*/
MMP_ERR MMPD_MP4VDEC_Init(void)
{
    return MMP_ERR_NONE;
}

/// @end_ait_only

/** @} */ // end of MMPD_3GPPLAY

#ifdef BUILD_CE
#define BUILD_FW
#endif
