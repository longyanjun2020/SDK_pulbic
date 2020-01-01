//==============================================================================
//
//  File        : mmpd_ccir.c
//  Description : Ritian CCIR Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

/**
*  @file mmpd_ccir.c
*  @brief The CCIR control functions
*  @author Penguin Torng
*  @version 1.0
*/

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpf_display.h"
#include "mmpf_ccir.h"
#include "mmpd_system.h"		// CarDV
//#include "AHC_Config_SDK.h"

/** @addtogroup MMPD_Display
 *  @{
 */

// CarDV +++
#if defined(CCIR656_ENABLE_TEST_PATTERN)
typedef struct _RGBTerm {
  MMP_UBYTE R;
  MMP_UBYTE G;
  MMP_UBYTE B;
} RGBTerms;

typedef struct _YUVTerm {
  MMP_UBYTE Y;
  MMP_UBYTE U;
  MMP_UBYTE V;
} YUVTerms;

typedef union {
   RGBTerms rgb;
   YUVTerms yuv;
} Pixel;

#define COLORBAR        0
#define WITH_BORDER     1
#define PATTERN         COLORBAR

#define CCIR656_720X480 0
#define CCIR656_720X576 1

#define CCIR_27MHZ      0
#define CCIR_54MHZ      1
#define CCIR_RESOL CCIR656_720X480

#if (CCIR_RESOL == CCIR656_720X480)
#define CCIRClOCK       CCIR_27MHZ
#define CCIR656_WIDTH   720
#define CCIR656_HEIGHT  480
#define H_ACT_PIXEL     720
#define H_TOTAL_BLK     138
#define V_ACT_LINE      480
#define F1_TOP_BLK      26
#define F1_BOT_BLK      19
#endif
#endif
// CarDV ---

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPD_Display_SetCCIROutput
//  Description : 
//------------------------------------------------------------------------------
MMP_ERR MMPD_Display_SetCCIROutput( MMP_DISPLAY_CONTROLLER  controller,
                                    MMP_CCIR_ATTR           ccirAttr)
{
    #if defined(ALL_FW)
    MMPF_Display_SetOutputDev(controller, MMP_DISPLAY_CCIR);
    return MMPF_CCIR_ConfigCCIR(&ccirAttr);
    #else
    return MMP_ERR_NONE;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPD_CCIR_SetDisplayBufAddr
//  Description : 
//------------------------------------------------------------------------------
MMP_ERR MMPD_CCIR_SetDisplayBufAddr(MMP_ULONG ulBaseAddr)
{
    return MMPF_CCIR_SetPedBufferAddr(ulBaseAddr);
}

//------------------------------------------------------------------------------
//  Function    : MMPD_CCIR_SetDisplayRefresh
//  Description : 
//------------------------------------------------------------------------------
/** @brief Enable display refresh

The function check if CCIR output is enabled. If not, CCIR output will be
enabled. Otherwise, do nothing.

@return It reports the status of the operation.
*/
MMP_ERR MMPD_CCIR_SetDisplayRefresh(void)
{
    #if defined(ALL_FW)
	return MMPF_CCIR_SetRefresh();
    #else
    return MMP_ERR_NONE;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPD_CCIR_DisableDisplay
//  Description : 
//------------------------------------------------------------------------------
/** @brief Disable CCIR display refresh

The function disables the CCIR display.

@return It reports the status of the operation.
*/
MMP_ERR MMPD_CCIR_DisableDisplay(void)
{
    #if defined(ALL_FW)
	return MMPF_CCIR_StopRefresh();
    #else
    return MMP_ERR_NONE;
    #endif
}

// CarDV +++
#if defined(CCIR656_ENABLE_TEST_PATTERN)
MMP_ULONG DisplayDrawHorizontalSegment1(MMP_ULONG pDrawAddr, MMP_DISPLAY_COLORMODE DrawFormat, Pixel PixelVal, MMP_USHORT PixelCnt)
{
    MMP_ULONG i;

    RTNA_DBG_Str(0, FG_BLUE("### DisplayDrawHorizontalSegment1 -\r\n"));
    
    switch(DrawFormat) {
    case MMP_DISPLAY_COLOR_RGB888:
        for(i=0;i<PixelCnt;i++) {
            //B
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.rgb.B;
            pDrawAddr+=1;
            //G
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.rgb.G;
            pDrawAddr+=1;
            //R
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.rgb.R;
            pDrawAddr+=1;
        }
        break;
    case MMP_DISPLAY_COLOR_YUV422:
        for(i=0;i<PixelCnt/2;i++) {
            //U
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.yuv.U;
            pDrawAddr+=1;
            //Y
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.yuv.Y;
            pDrawAddr+=1;
            //V
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.yuv.V;
            pDrawAddr+=1;
            //Y
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.yuv.Y;
            pDrawAddr+=1;
        }
        break;
      }
    return pDrawAddr;
}

MMP_ULONG DisplayDrawVerticalSegment1(MMP_ULONG pDrawAddr, MMP_DISPLAY_COLORMODE DrawFormat, Pixel PixelVal, 
                                      MMP_USHORT drawheight, MMP_USHORT drawidth, MMP_USHORT lineoffset)
{
    MMP_ULONG i,j;

    RTNA_DBG_Str(0, FG_BLUE("### DisplayDrawVerticalSegment1 -\r\n"));

    switch(DrawFormat) {
    case MMP_DISPLAY_COLOR_YUV422:
        for(i=0;i<drawheight;i++) {
            for(j=0;j<drawidth;j++) {
            //U
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.yuv.U;
            pDrawAddr+=1;
            //Y
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.yuv.Y;
            pDrawAddr+=1;
            //V
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.yuv.V;
            pDrawAddr+=1;
            //Y
            *((MMP_UBYTE*)(pDrawAddr)) = PixelVal.yuv.Y;
             pDrawAddr+=1;           
            }
            pDrawAddr += (lineoffset-4*drawidth);
        }
        break;
      }
    return pDrawAddr;
}

MMP_ULONG GetDrawAddrOffset(MMP_ULONG pixel, MMP_ULONG line, MMP_ULONG width, MMP_ULONG height,MMP_DISPLAY_COLORMODE DrawFormat)
{
    if(DrawFormat == MMP_DISPLAY_COLOR_YUV422)
    {
        return  (pixel/2)*4 + width*line*2;
    }
    else if (DrawFormat == MMP_DISPLAY_COLOR_RGB888)
    {
        return width*height*3;
    }    
    return 0;
}

void DisplayDrawPic1(MMP_ULONG DrawAddr, MMP_ULONG width, MMP_ULONG height, MMP_ULONG DrawType)
{
    //MMP_ULONG              y;
    Pixel                  pixelval;
    MMP_ULONG              lineoffset; 
    MMP_ULONG              curDrawAddr;
    //MMP_ULONG              lastLineDrawAddr;
    MMP_ULONG              offset;

    RTNA_DBG_Str(0, FG_BLUE("### DisplayDrawPic1 -\r\n"));

    lineoffset = width*2;
    #if (PATTERN == WITH_BORDER)
    /*draw pattern for test*/
    curDrawAddr =   DrawAddr;
    pixelval.yuv.Y=29;     
    pixelval.yuv.U=235;
    pixelval.yuv.V=107;    
    DisplayDrawHorizontalSegment1(curDrawAddr, MMP_DISPLAY_COLOR_YUV422,pixelval,width*7);

    offset=GetDrawAddrOffset(0,7,width,height,MMP_DISPLAY_COLOR_YUV422);
    pixelval.yuv.Y=29; 
    pixelval.yuv.U=235;
    pixelval.yuv.V=107;
    DisplayDrawVerticalSegment1(curDrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,height-8,5,lineoffset);

    offset=GetDrawAddrOffset(width-10,8,width,height,MMP_DISPLAY_COLOR_YUV422);
    pixelval.yuv.Y=235; 
    pixelval.yuv.U=128;
    pixelval.yuv.V=128;
    DisplayDrawVerticalSegment1(curDrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,height-8,5,lineoffset);

    pixelval.yuv.Y=235; 
    pixelval.yuv.U=128;
    pixelval.yuv.V=128;
    offset=GetDrawAddrOffset(0,height-7,width,height,MMP_DISPLAY_COLOR_YUV422);
    DisplayDrawHorizontalSegment1(DrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,width*7);               

    RTNA_DBG_Str0("offset=\r\n");
    RTNA_DBG_Long0(offset);
    #endif
    
    #if (PATTERN == COLORBAR)
    pixelval.yuv.Y=235;     
    pixelval.yuv.U=0;
    pixelval.yuv.V=0;    
    offset=GetDrawAddrOffset(0,0,width,height,MMP_DISPLAY_COLOR_YUV422);
    DisplayDrawVerticalSegment1(DrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,height,width/16,lineoffset);
    pixelval.yuv.Y=210; 
    pixelval.yuv.U=16;
    pixelval.yuv.V=146;
    offset=GetDrawAddrOffset(width/8*1,0,width,height,MMP_DISPLAY_COLOR_YUV422);
    DisplayDrawVerticalSegment1(DrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,height,width/16,lineoffset);
    
    pixelval.yuv.Y=170;     
    pixelval.yuv.U=166;
    pixelval.yuv.V=16;    
    offset=GetDrawAddrOffset((width/8)*2,0,width,height,MMP_DISPLAY_COLOR_YUV422);
    DisplayDrawVerticalSegment1(DrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,height,width/16,lineoffset);
    pixelval.yuv.Y=145; 
    pixelval.yuv.U=54;
    pixelval.yuv.V=34;
    offset=GetDrawAddrOffset((width/8)*3,0,width,height,MMP_DISPLAY_COLOR_YUV422);
    DisplayDrawVerticalSegment1(DrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,height,width/16,lineoffset);
    
    pixelval.yuv.Y=107;     
    pixelval.yuv.U=202;
    pixelval.yuv.V=221;    
    offset=GetDrawAddrOffset((width/8)*4,0,width,height,MMP_DISPLAY_COLOR_YUV422);
    DisplayDrawVerticalSegment1(DrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,height,width/16,lineoffset);
    pixelval.yuv.Y=82; 
    pixelval.yuv.U=90;
    pixelval.yuv.V=240;
    offset=GetDrawAddrOffset((width/8)*5,0,width,height,MMP_DISPLAY_COLOR_YUV422);
    DisplayDrawVerticalSegment1(DrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,height,width/16,lineoffset);
    
    pixelval.yuv.Y=41;     
    pixelval.yuv.U=240;
    pixelval.yuv.V=110;    
    offset=GetDrawAddrOffset((width/8)*6,0,width,height,MMP_DISPLAY_COLOR_YUV422);
    DisplayDrawVerticalSegment1(DrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,height,width/16,lineoffset);
    pixelval.yuv.Y=0; 
    pixelval.yuv.U=128;
    pixelval.yuv.V=128;
    offset=GetDrawAddrOffset((width/8)*7,0,width,height,MMP_DISPLAY_COLOR_YUV422);
    DisplayDrawVerticalSegment1(DrawAddr+offset,MMP_DISPLAY_COLOR_YUV422,pixelval,height,width/16,lineoffset);
    
    #endif
}

void DrawPattern(void) 
{
#if 0
    MMP_ULONG addr=AHC_CCIR656_PREVIEW_ADDR;//0x4000000;

    RTNA_DBG_Str(0, FG_BLUE("### DrawPattern -\r\n"));

    DisplayDrawPic1(addr,CCIR656_WIDTH,CCIR656_HEIGHT,1);
#endif    
}

MMP_ERR MMPD_CCIR_SetCCIR656Output(void)
{
    RTNA_DBG_Str(0, FG_BLUE("### MMPD_CCIR_SetCCIR656Output\r\n"));
    
    //LCD_intial(0,0x0F,0xEF); //polarity
    //MEMSET((void *)AHC_CCIR656_PREVIEW_ADDR, 0x0, 0xA8C00);
    //DrawPattern();
    
    return MMP_ERR_NONE;
}
#endif
// CarDV ---

/// @}
