//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "component_raws.h"

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void ____RAW_Component_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : MMPD_RAWPROC_SetRawSCompAttr
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_RAWPROC_SetRawSCompAttr(MMP_UBYTE ubChannel, MMP_UBYTE ubSigType,
                                     MMP_USHORT usStoreW, MMP_USHORT usStoreH, MMP_UBYTE ubBufCnt)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_ULONG   ulBufSize = 0;

    eRetErr |= Component_RawS_SetParam(&Component_RawS[ubChannel], RAWS_COMP_PARAM_WIDTH, (void*)&usStoreW);
    eRetErr |= Component_RawS_SetParam(&Component_RawS[ubChannel], RAWS_COMP_PARAM_HEIGHT, (void*)&usStoreH);
    eRetErr |= Component_RawS_SetParam(&Component_RawS[ubChannel], RAWS_COMP_PARAM_SNR_SEL, (void*)&ubChannel);
    eRetErr |= Component_RawS_SetParam(&Component_RawS[ubChannel], RAWS_COMP_PARAM_SIGNAL_TYPE, (void*)&ubSigType);

    ulBufSize = usStoreW * usStoreH * 2; // YUV422
    eRetErr |= Component_RawS_SetParam(&Component_RawS[ubChannel], RAWS_COMP_PARAM_BUF_COUNT, (void*)&ubBufCnt);
    eRetErr |= Component_RawS_SetParam(&Component_RawS[ubChannel], RAWS_COMP_PARAM_BUF_SIZE, (void*)&ulBufSize);

    return eRetErr;
}
