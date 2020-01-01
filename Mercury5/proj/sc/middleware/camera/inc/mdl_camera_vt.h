#ifndef _MS_MDL_CAMERA_VC_H_
#define _MS_MDL_CAMERA_VC_H_
//////////////////  for VC   ////////////////////////////////////////

#if defined(__VT_3G324M__)
typedef enum
{
   BUF_NUM_0=0,
   BUF_NUM_1,
}BUF_NUM_e;


typedef enum
{
   BUF_HAS_SHOWED=0,
   BUF_NOT_SHOWED,

}BUF_SHOWED_STATUS_e;

typedef enum
{
   COPY_BUF0_FROM_BUF1=0,
   COPY_BUF1_FROM_BUF0,
}COPYBUF_OPTION_e;

typedef enum
{
   Idx_Not_Exist=0,
   Idx_Exist,

}BASEADDR_IDX_STA_e;

typedef struct  _VT_BUFFER
{
    u32          VT_EncodeBuf[4];
    u32          VT_DecodeBuf[4];
    u32          VT_EncodeSize;
    u32          VT_DecodeSize;
    u16          VT_EncodeWidth;
    u16          VT_EncodeHeight;
    u16          VT_DecodeWidth;
    u16          VT_DecodeHeight;
} VT_BUFFER_t;

void Cam_3G_VC_CopyBufAddr(COPYBUF_OPTION_e eOpt);
u8 Cam_3G_VC_SetDecodeBuf(u32 u32VC_DecodeAddrY,u32 u32VC_DecodeAddrU,u32 u32VC_DecodeAddrV);
MmlCameraResult_e Cam_3G_VC_MLLinkSet(void);
void  Cam_3G_VC_CallBackCfg(void);
void Cam_3G_VC_SclDoneCB(void);


#endif


#endif   //_MS_MDL_CAMERA_VC_H_

