//==============================================================================
//
//  File        : mmp_ldc_inc.h
//  Description : INCLUDE File for the LDC Driver Function
//  Author      : Eroy Yang
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_LDC_INC_H_
#define _MMP_LDC_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_graphics_inc.h"
#include "mmp_scal_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_LDC_SLICE_NUM				(5)
#define MAX_LDC_SNR_NUM					(2)

#define MAX_LDC_SRC_BUF_NUM				(3)
#define MAX_LDC_OUT_BUF_NUM				(3)

#define LDC_STITCH_BLENDING_EN			(0)
#define LDC_STITCH_BLENDING_BLK_NUM		(4)
#define LDC_STITCH_BLENDING_BLK_WIDTH	(32)
#define LDC_STITCH_BLENDING_DYM_THD     (1)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_LDC_RES_MODE {
  	MMP_LDC_RES_MODE_FHD = 0,	// 1920x1080
  	MMP_LDC_RES_MODE_HD,		// 1280x720
  	MMP_LDC_RES_MODE_WVGA,		// 848x480
  	MMP_LDC_RES_MODE_MS_736P,	// MultiSlice 736x736P
  	MMP_LDC_RES_MODE_MS_1080P,	// MultiSlice 1920x1080P
  	MMP_LDC_RES_MODE_MS_1536P,	// MultiSlice 1536x1536P
 	MMP_LDC_RES_MODE_NOT_SUPPORT,
 	MMP_LDC_RES_MODE_NUM
} MMP_LDC_RES_MODE;

typedef enum _MMP_LDC_FPS_MODE {
	MMP_LDC_FPS_MODE_120P = 0,
  	MMP_LDC_FPS_MODE_60P,
  	MMP_LDC_FPS_MODE_50P,
  	MMP_LDC_FPS_MODE_30P,
  	MMP_LDC_FPS_MODE_24P,
  	MMP_LDC_FPS_MODE_15P,
 	MMP_LDC_FPS_MODE_NOT_SUPPORT,
 	MMP_LDC_FPS_MODE_NUM
} MMP_LDC_FPS_MODE;

typedef enum _MMP_LDC_RUN_MODE {
	MMP_LDC_RUN_MODE_DISABLE = 0,
	MMP_LDC_RUN_MODE_SINGLE_RUN,
	MMP_LDC_RUN_MODE_MULTI_RUN,
	MMP_LDC_RUN_MODE_MULTI_SLICE,
	MMP_LDC_RUN_MODE_NUM
} MMP_LDC_RUN_MODE;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

// LDC Preview Buffer Information
typedef struct _MMP_LDC_SRC_BUFINFO 
{
    MMP_ULONG  			ulInYBuf[MAX_LDC_SRC_BUF_NUM];	///< LDC source Y buffer (Pipe3)
    MMP_ULONG  			ulInUBuf[MAX_LDC_SRC_BUF_NUM]; 	///< LDC source U buffer (Pipe3)
    MMP_ULONG  			ulInVBuf[MAX_LDC_SRC_BUF_NUM]; 	///< LDC source V buffer (Pipe3)
    MMP_USHORT 			usInBufCnt;						///< LDC source buffer count
} MMP_LDC_SRC_BUFINFO;

// LDC Link Pipe Information
typedef struct  _MMP_LDC_LINK
{
    MMP_UBYTE     	    srcPipeID;
    MMP_UBYTE     	    prvPipeID;
    MMP_UBYTE     	    encPipeID;
    MMP_UBYTE     	    swiPipeID;
    MMP_UBYTE		    jpgPipeID;
} MMP_LDC_LINK;

// LDC Module Attribute
typedef struct _MMP_LDC_ATTR 
{
	MMP_BOOL			bLdcEnable;
    MMP_UBYTE   		ubInputPath;
    MMP_USHORT  		usInputStX;
    MMP_USHORT  		usInputStY;
    MMP_USHORT  		usInputW;
    MMP_USHORT 	 		usInputH;
    MMP_UBYTE   		ubInputXratio;
    MMP_UBYTE   		ubInputYratio;
    MMP_BOOL    		bOutCrop;
    MMP_USHORT  		usOutputStX;
    MMP_USHORT  		usOutputStY;
    MMP_USHORT  		usOutputW;
    MMP_USHORT  		usOutputH;
    MMP_UBYTE			ubOutLineDelay;
    MMP_ULONG			ulDmaAddr;
} MMP_LDC_ATTR;

// Multi-Slice Information
typedef struct _MMP_LDC_MULTI_SLICE_INFO 
{
	MMP_USHORT				usSliceNum[MAX_LDC_SNR_NUM];
	
	/* Stitch Output Buffer */
	MMP_ULONG               ulLdcOutStoreYAddr[MAX_LDC_OUT_BUF_NUM];
	MMP_ULONG               ulLdcOutStoreUAddr[MAX_LDC_OUT_BUF_NUM];
	MMP_ULONG               ulLdcOutStoreVAddr[MAX_LDC_OUT_BUF_NUM];
	
	#if (LDC_STITCH_BLENDING_EN)
	/* Stitch Blending Buffer */
	MMP_ULONG               ulLdcBlendBlkYAddr[LDC_STITCH_BLENDING_BLK_NUM][MAX_LDC_OUT_BUF_NUM];
	MMP_ULONG               ulLdcBlendBlkUAddr[LDC_STITCH_BLENDING_BLK_NUM][MAX_LDC_OUT_BUF_NUM];
	MMP_ULONG               ulLdcBlendBlkVAddr[LDC_STITCH_BLENDING_BLK_NUM][MAX_LDC_OUT_BUF_NUM];
	#endif

	/* Graphics Relative */
    MMP_GRAPHICS_BUF_ATTR 	sGraBufAttr;
    MMP_GRAPHICS_RECT		sGraRect[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
    
    /* LDC Relative */
	MMP_USHORT				*pusSnr0LdcPosTbl[2][MAX_LDC_SLICE_NUM];
	MMP_ULONG				*pulSnr0LdcDeltaTbl[12][MAX_LDC_SLICE_NUM];
	MMP_USHORT				*pusSnr1LdcPosTbl[2][MAX_LDC_SLICE_NUM];
	MMP_ULONG				*pulSnr1LdcDeltaTbl[12][MAX_LDC_SLICE_NUM];

    MMP_LDC_ATTR			sLdcAttr[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
    MMP_UBYTE				ubScaleRatioH[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
    MMP_UBYTE				ubScaleRatioV[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];

    /* Scaler Relative */
    MMP_SCAL_FIT_RANGE		sFitRange[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
    MMP_SCAL_GRAB_CTRL		sGrabCtl[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
    
    /* Icon Relative */
    MMP_USHORT				usIconFrmW[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
    MMP_USHORT				usIconFrmH[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
    
    /* IBC Relative */
    MMP_ULONG				ulDstPosX[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
    MMP_ULONG				ulDstPosY[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
    MMP_ULONG           	ulLineOffset[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
    MMP_ULONG           	ulCbrLineOffset[MAX_LDC_SNR_NUM][MAX_LDC_SLICE_NUM];
} MMP_LDC_MULTI_SLICE_INFO;

// Multi-Slice Block Information
typedef struct _MMP_LDC_MULTI_SLICE_BLOCKINFO 
{	
	/* Graphics Relative */
    MMP_GRAPHICS_RECT		sGraInRect;
    /* LDC Relative */
    MMP_GRAPHICS_RECT		sLdcOutRect;
    MMP_USHORT				usScaleRatioH;
    MMP_USHORT				usScaleRatioV;
    /* IBC Relative */
    MMP_ULONG				ulDstPosX;
    MMP_ULONG				ulDstPosY;
	/* LDC Relative */
	MMP_USHORT				*pusLdcPosTbl[2];
	MMP_ULONG				*pulLdcDeltaTbl[12];
} MMP_LDC_MULTI_SLICE_BLOCKINFO;

//==============================================================================
//
//                              EXTERN VARIABLE
//
//==============================================================================

extern MMP_ULONG 	m_ulDscLdcMaxSrcW;
extern MMP_ULONG 	m_ulDscLdcMaxSrcH;

extern MMP_ULONG 	m_ulLdcFrmDoneCnt;

#endif //_MMP_LDC_INC_H_
