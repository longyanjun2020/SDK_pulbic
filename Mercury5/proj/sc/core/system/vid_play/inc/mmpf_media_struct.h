/**
 @file mmpf_media_struct.h
 @brief Header function of common media structure
 @author SW. Yang
 @author Truman Yang
 @version 1.0 Original Version
*/

#ifndef _MMPF_MEDIA_STRUCT_H_
#define _MMPF_MEDIA_STRUCT_H_

#include "includes_fw.h"
#include "mmp_media_def.h"

/**
 @brief video output frame
*/
typedef struct
{
    MMP_UBYTE   *data[3];        ///< point to video raw data, 0 : Y(or R), 1 : U(or G), 2 : V(or B)
    MMP_ULONG64 time;
    MMP_ULONG   QP;
    MMP_ULONG   frameID;
    MMP_UBYTE   is_been_refreshed;
    MMP_BOOL    bKeyFrame;
    MMP_ULONG   ulFlag;
} MMP_MEDIA_FRAME;

#endif