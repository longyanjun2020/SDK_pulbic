#ifndef _MS_MDL_CAMERA_VIDEO_H_
#define _MS_MDL_CAMERA_VIDEO_H_
#include "mdl_camera_video_pub.h"
#include "mdl_camera_api_pub.h"

 /* #define Video_Stable_CmpPixel_256_W 20
  #define Video_Stable_CmpPixel_320_W 22
  #define Video_Stable_CmpPixel_352_W 24
  #define Video_Stable_CmpPixel_400_W 26
  #define Video_Stable_CmpPixel_480_W 28

  #define Video_Stable_CmpPixel_192_H 20
  #define Video_Stable_CmpPixel_240_H 22
  #define Video_Stable_CmpPixel_288_H 24
  #define Video_Stable_CmpPixel_320_H 28
 */

typedef struct _VS_REAL_ADDR_
{
    u16 nStartX;
    u16 nStartY;
    u16 nVideoWidth ;
    u16 nVideoHeight ;
    u32 nOriAddrY;		//RAW
    u32 nOriAddrCb;
    u32 nRealAddrY;		//After Video Stabilizer
    u32 nRealAddrCb;
    u32 nRealAddrCr;
}VS_REAL_ADDR_t;

typedef struct _VS_VIDEO_CFG_
{
   u16 nVideoWidth;
   u16 nVideoHeight;
   u32 nAddrY0;
   u32 nAddrC0;
   u32 nAddrY1;
   u32 nAddrC1;
}VS_VIDEO_CFG_t;

void _VS_DoCal(ML_BUF_DUMMY_REG_e eId);
void _VS_CalSclSrcAddr(VS_REAL_ADDR_t *pCfg);
void _VS_GetSclSrcAddrIdx(SclSrcBaseAddrInfo_t *pInfo);
void _VS_SaveSclSrcAddrIdx(SclSrcBaseAddrInfo_t *pInfo);
void _VS_Reset(void);


#endif   //_MS_MDL_CAMERA_VIDEO_H_

