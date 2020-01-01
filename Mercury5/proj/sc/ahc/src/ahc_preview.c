//==============================================================================
//
//  File        : AHC_preview.c
//  Description : AHC preview function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 
#include "ahc_common.h"
#include "ahc_preview.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

/*===========================================================================
 * Global varible
 *===========================================================================*/ 
static AHC_WINDOW_RECT          gsCustomerRearPrevWindow 	= {0, 0, 0, 0};
static AHC_WINDOW_RECT          gsCustomerFrontPrevWindow 	= {0, 0, 0, 0};
/*===========================================================================
 * Extern function
 *===========================================================================*/ 
//------------------------------------------------------------------------------
//  Function    : AHC_PreviewWindowOp
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This API set/get Preview window of Front Cam / Rear Cam
 
 Parameters: 
 @param[in]     op      AHC_PREVIEW_WINDOW_OP_GET to set window rect,AHC_PREVIEW_WINDOW_OP_SET to set window rect
                        AHC_PREVIEW_WINDOW_FRONT/AHC_PREVIEW_WINDOW_REAR to choice window
 @param[in/out] pRect   in get window case, this is addressed to the memory of structure AHC_WINDOW_RECT which will be updated.
                        in set window case, use this addresed memory to set window rect.
 @retval return 0 is success ,others are unknow operations.
*/
UINT32	AHC_PreviewWindowOp(UINT32 op, AHC_WINDOW_RECT * pRect)
{
    UINT32 subop, win;
    
    subop = op & AHC_PREVIEW_WINDOW_OP_MASK;
    win   = op & AHC_PREVIEW_WINDOW_MASK;
    
    if (subop == AHC_PREVIEW_WINDOW_OP_GET)
    {
        if (win == AHC_PREVIEW_WINDOW_FRONT)
            memcpy(pRect, &gsCustomerFrontPrevWindow, sizeof(AHC_WINDOW_RECT));
        else
            memcpy(pRect, &gsCustomerRearPrevWindow, sizeof(AHC_WINDOW_RECT));
    }
    else if (subop == AHC_PREVIEW_WINDOW_OP_SET)
    {
        if (win == AHC_PREVIEW_WINDOW_FRONT)
            memcpy(&gsCustomerFrontPrevWindow, pRect, sizeof(AHC_WINDOW_RECT));
        else
            memcpy(&gsCustomerRearPrevWindow, pRect, sizeof(AHC_WINDOW_RECT));
    }
    else {
        return -1;
    }
    
    return 0;
}
 
 