//==============================================================================
//
//  File        : mmp_rawproc_inc.h
//  Description : INCLUDE File for the Firmware Rawproc Control driver function
//  Author      : Ted
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_RAWPROC_INC_H_
#define _MMP_RAWPROC_INC_H_

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_RAW_COLORFMT 
{
    MMP_RAW_COLORFMT_BAYER8 = 0,
    MMP_RAW_COLORFMT_BAYER10,
    MMP_RAW_COLORFMT_BAYER12,
    MMP_RAW_COLORFMT_BAYER14,
    MMP_RAW_COLORFMT_YUV422,
    MMP_RAW_COLORFMT_NUM
} MMP_RAW_COLORFMT;

#endif // _MMP_RAWPROC_INC_H_

