#ifndef _MMPD_RAWPROC_H_
#define _MMPD_RAWPROC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_ERR MMPD_RAWPROC_SetRawSCompAttr(MMP_UBYTE ubChannel, MMP_UBYTE ubSnrType,
                                     MMP_USHORT usStoreW, MMP_USHORT usStoreH, MMP_UBYTE ubBufCnt);

#endif //_MMPD_RAWPROC_H_
