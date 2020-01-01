/*****************************************************************************\
    This software is protected by Copyright and the information
    contained herein is confidential. Distribution, reproduction
    as well as exploitation and transmission of its contents is
    not allowed except if expressly permitted. Infringments
    result in damage claims.
    Copyright : Morning Star 2006/11 ~ 2010

  File    : bltpattern.h

  Contents: Two major types here:
  1. draw monochrome bitmaps
  2. Draw olorful bitmaps

  Historical :
--------------------------------------------------------------------------
   Date   | Author | Err  |  Modification
----------+--------+------+-----------------------------------------------
 16.11.06 | Alex   |      |  Create
----------+--------+------+-----------------------------------------------
\*****************************************************************************/
#if 1
#include "bltpattern_pub.h"
#else

#include <string.h>
#include "vm_types.ht"
#include "dispbasicgrap_pub.h"
#include "msgdidef.h"

#ifndef _DISP_DRAW_PICTURES_H_
#define _DISP_DRAW_PICTURES_H_

//===============================================
//    Constant
//===============================================
// Lzss compression algorithm
#define LZSS_N          1024 // size of ring buffer
#define LZSS_F          18   // upper limit for match_length
#define LZSS_THRESHOLD  2    // encode string into position and length
                             // if match_length is greater than this.
//===============================================
//    Structures
//===============================================
//ROP3, PATPAINT, 0x00FB0A09

//===============================================
//    functions
//===============================================
#ifdef _DISP_DRAW_PICTURES_BODY_
    //bool IsAbleToDrawPicSW(void *param);
    u32  MonoPatternCopySW(PMSBLT_PATTPAINT pParam);
    u32  ColorPatternCopySW(PMSBLT_PATTCOPY pParam);
#else  //_DISP_DRAW_PICTURES_BODY_
    //extern bool IsAbleToDrawPicSW(void *param);
    extern u32  MonoPatternCopySW(PMSBLT_PATTPAINT pParam);
    extern u32  ColorPatternCopySW(PMSBLT_PATTCOPY pParam);
#endif //_DISP_DRAW_PICTURES_BODY_

#endif //_DISP_DRAW_PICTURES_H_
#endif

