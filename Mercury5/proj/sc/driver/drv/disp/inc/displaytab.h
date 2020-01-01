///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   displaytab.h
/// @author MStar Semiconductor Inc.
/// @brief  configurable variables definition
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _DISPLAYTAB_H
#define _DISPLAYTAB_H
#include <pkgconf/system.h>
//typedef AU32    U32;
//typedef AU16    U16;
//typedef AU8     U8;
//typedef AS32    S32;
//typedef AS16    S32;
//typedef AS8     S8;

#pragma pack(1)
typedef volatile struct DisplayTab_s_
{
    // Variable Type: U8/S8/U16/S16/U32/S32
    // Array Type   : AU8/AS8/AU16/AS16/AU32/AS32
    // String Type  : C8
    //C8 gu8RecDir_AUD[128];  // string
    //AU8 gu8RecDir_AUD[128]; // unsigned 8 8bits array
    //AS8 gu8RecDir_AUD[128]; // signed 8 8bits array
    //U32 u32sysclk;          // unsigned 32 bits variable
    //U32 u32sysclk;          // unsigned 32 bits variable

   //for header
   U8  header[16];//reserve 16 bytes for some information,0~15

   //for display table enable or disable
   //U16 display_table_enable;
   U8  display_table_preview_enable;//16
   U8  display_table_playback_enable;//17
   
   //for BIG3 MACE  
   //Vip0: 0x74000000+0x380*4 +reg_offset*4
   //Vip1: 0x74000000+0x400*4 +reg_offset*4
   //Vip2: 0x74000000+0x480*4 +reg_offset*4
   U32 u32MMP_Base;//0x74000000//21 
   //1Dx9 peaking
 
   U8  u8Peaking_length;//22
   U16 Peaking[18];//58
   //Direct Luma Correction(DLC) 
   U8  u8DLC_length;//59	
   U16 DLC[32];	//179
   //Black/White Level Extension(BLE/WLE) 
   U8  u8BWE_length;//180
   U16 BWE[22];//224
   //FCC/ICC/IBC/IHC/Noise Masking 	   	
   U8  u8FCC_length;//225
   U16 FCC[34];//293
   U8  ICC_length;//294
   U16 ICC[16];//326
   U8  ACK_length;//327
   U16 ACK[6];//339
   U8  u8IBC_length;//340
   U16 IBC[12];//364   
   U8  u8Noise_Masking_IHC_length;//365
   U16 Noise_Masking_IHC_[18];//401
   //for BIG3 display engine   
   U8 PQ_tuning_flag;//for tuning RGB gamma//402    
      
   U16 CSC_table[9];//display color matrix//420
   U8 Enable_DeGamma;//enable Y gamma flag//421  
   U16 DeGamma_Table[32];//Display Y gamma//485  
   U8 Enable_RGB_gamma;//display RGB gamma enable//486 
   U8 gamma_table[768];//display RGB gamma//1254

   U16 DisplayContrast; // 2 Bytes, 1256
   U16 DisplaySaturation; // 2 Bytes,1258
   U16 DisplayHue; // 2 Bytes, 1260
   U16 DisplayRGain; // 2 Bytes, 1262
   U16 DisplayGGain; // 2 Bytes, 1264
   U16 DisplayBGain; // 2 Bytes, 1266
   U16 DisplayColorCorrectionTable[9]; // 18 Bytes, 1284
   
   //for PQ tool use 
   U16 u16empty0;//1286 for 4 bytes assignment     
   U8  u8empty1;//1287 for 4 bytes assignment


} DisplayTab_s;
#pragma pack()

#endif // _DISPLAYTAB_H

