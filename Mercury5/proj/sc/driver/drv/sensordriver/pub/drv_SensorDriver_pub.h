
#ifndef DRV_SENSOR_DRIVER_PUB_H__
#define DRV_SENSOR_DRIVER_PUB_H__

#include "drv_SensorIF_pub.h"

#if defined(__MULTIPLE_SENSOR_TABLE_DETECTION__)
	#define CUS_DEFAULT_ADDR (0xFFFFFFFF)
	#define SENSOR_TABLE_ID (0x54435344UL)
#endif

#if !defined(__VT_3G324M__) && !defined(__SMALL_ROM_32__)  && !defined(CAMCORDER_NORMAL_MODE)  && !defined(CAMCORDER_ECONOMY_MODE)
#if !defined(__SMALL_ROM__)
    #define VDR_WITH_15FPS_DISP_2_REC
#endif
    #define VDR_WITH_15FPS_REC_2_DISP
#endif //!defined(__VT_3G324M__)
enum {
	Sensor_Special_Effect_no_Delay = 0,
	Sensor_Special_Effect_with_Delay,
};

typedef enum
{
	Err_SUCCESS =0,
	Err_FAILE ,
       //    ErrCode_SCL_BUSY,
} DrvSr_ErrCode_e;

enum SenStatus{
	SENSOR_NOT_READY,
	SENSOR_READY,
};
enum TableSelect {
	Preview_Table,
	Video_Table,
	UVC_Table,
};

typedef enum
{
  SEN_SRC_MAIN=0,
  SEN_SRC_ATV,
  SEN_SRC_SUB,
  SEN_SRC_UNKNOWN,
}SEN_SRC_e;

typedef enum // for fn_Sensor_SetPowerDown
{
	SEN_PWR_ON = 0,
	SEN_PWR_OFF,
} SEN_PWR_e;

typedef enum
{
	_50Hz = 0, // follow CAMERA_FREQUENCY_50HZ in MML_Camera.h
	_60Hz,
	AntiFlicker_Disabled,
	AntiFlicker_Enabled,
}SEN_ANTI_FLICKER_e;

typedef enum
{
    SEN_PREVIEWMODE_NORMAL = 0,        ///< Normal preview
    SEN_PREVIEWMODE_VIDEORECORDING,    ///< Video recording preview
    SEN_PREVIEWMODE_VIDEOCHAT,         ///< Video chat preview
} SenPreviewMode_e;

typedef enum
{
    SEN_SCENEMODE_OFF = 0,      ///< Off
    SEN_SCENEMODE_AUTO,         ///< Auto
    SEN_SCENEMODE_LANDSCAPE,    ///< Landscape
    SEN_SCENEMODE_PORTRAIT,     ///< Portrait
    SEN_SCENEMODE_NIGHT,        ///< Night
    SEN_SCENEMODE_SUNSET,       ///< Sunset
} SenSceneMode_e;

typedef enum
{
    SEN_WHITEBALANCEMODE_MANUAL = 0,     ///< Manual (AWB off)
    SEN_WHITEBALANCEMODE_AUTO,           ///< Auto white balance
    SEN_WHITEBALANCEMODE_CLOUDY,         ///< Cloudy
    SEN_WHITEBALANCEMODE_DAYLIGHT,       ///< Daylight
    SEN_WHITEBALANCEMODE_FLUORESCENT,    ///< Fluorescent
    SEN_WHITEBALANCEMODE_TUNGSTEN,       ///< Tungsten
} SenWhiteBalanceMode_e;

typedef enum
{
    SEN_EXPOSUREMODE_MANUAL = 0,    ///< Manual (AE off)
    SEN_EXPOSUREMODE_AUTO,          ///< Auto exposure
} SenExposureMode_e;




typedef struct _SEN_INIT_PARA_
{
    u8 nUVC;
    u8 nFrameRateTableSelect;
    SenPreviewMode_e ePreviewMode;
    u8 nPwr_on_only;
    u8 nAEEnable;
    u8 nAEMode;
    u8 nEV_Value;
    u8 nAwbMode;
    SEN_ANTI_FLICKER_e eAntiFlicker;
    u8 nEnvirCn;
    u8 nSensorFlip;
}SEN_INIT_PARA_t;

typedef enum {
	SEN_DATA_YUV422,
	SEN_DATA_JPEG,
} SenDataFormat_e;

#ifndef __5M_SENSOR_SUPPORT__

#pragma pack(1)

typedef struct SenTab_s_
{
   u8  header[16];//reserve 16 bytes for some information
 //password for sensor table, addr=0~1
   u16 u16Total_length;
 //sensor Input mode (0:YUV ,1:RGB),addr=2
   u8   u8Sensor_Inputformat;
 //sensor RGB format (0:10bit, 1:8bit),addr=3
   u8   u8Sensor_RGBformat;
 //sensor type(OV or Micron..), OV:0~29, Micron:30~59,SETi: 60~80,addr=4
   u8   u8Sensor_type;
 //for different module with the same sensor,addr=5
   u8   u8Module_type;
 // sensor frequency option,addr=6
   u8  u8Sensor_freq_index_pre;//SCLK
 //ICP engine clock settings for preview,addr=7
   u8   u8Icp_freq_index_pre;
 //ISP engine clock settings for preview,addr=8
   u8   u8Isp_freq_index_pre;
// SCL engine clock settings for preview,addr=9
   u8   u8Scl_freq_index_pre;
  //I2C initial settings
   u8   u8I2c_control;//0:by HW,1:bySW,addr=10
   u8   u8I2c_mode;//Mode 1:OmniVision,0:others,addr=11
   u8   u8Data_length;//0:data length is 1 byte,  1:data length is 2 bytes,addr=12
   u8   u8M2S_address;//0 : 8 bit address 1: 16 bit address, addr=13
   u8   u8M2S_clockfactor;// ClockFactor: 10 bits, Must be programmed less than SYSCLK /(4*M2S_frequency),addr=14
  //sensor reset settings
   u8   u8reset_mode;//0:Low active, 1:High active,addr=15
   u8   u8GPIOpin;//Gpio pin number,addr=16
   u8   u8sensorreset_delay;//ms,addr=17
 //sensor sync configuration
   u8   u8VSync_polarity;//addr=18
   u8   u8HSync_polarity;//addr=19
   u8   u8Sensor_clockpolarity;//addr=20
   u8   u8Sensor_RGBYUVorder;//addr=21
//sensor slave address & ID index and data
   u16 u16Sensor_slaveaddress;//addr=22~23
   u16 u16Sensor_IDaddress_L; //addr=24~25
   u16 u16Sensor_ID_L;//addr=26~27
   u16 u16Sensor_IDaddress_H; //addr=28~29
   u16 u16Sensor_ID_H;//addr=30~31
   u16 u16Sensor_inittable_length;//addr=32~33
   u16 sensor_initial_table[1023];//reserve 2046 bytes,addr=34~2079
	//some related settings for preview mode switch to capture mode

   u8  u8Sensor_freq_index_cap;//SCLK, addr=2080
   u32 u32PCLK_preview;//addr=2081~2084
   u32 u32Sensor_table_version;//addr=2085~2088
   //MIU,CPU,JPE engine clock settings for Preview mode,
   u8  u8miu_freq_pre;//Miu freq index,addr=2089
   u8  u8cpu_freq_pre;//CPU freq index,addr=2090
   u8  u8jpe_freq_pre;//JPE freq index,addr=2091
   u8  u8scl_freq_pre;//SCL freq index,addr=2092
   u8  u8Preview_Cap_factor;//addr=2093
   u16 u16exposure_time_index_H;//addr=2094~2095
   u16 u16exposure_time_index_L;//addr=2096~2097
   //preview table
   u16 u16Preview_tablelength;//addr=2098~2099
   u16 Preview_table[512];//addr=2010~3123
   //capture table
   u16 u16Capture_tablelength;//addr=3124~3125
   u16 Capture_table[512];//addr=3126~4149
   //AE enable settings
   u8  u8AEenable_tablelength;//addr=4150
   u16 AE_enable[16];//addr=4151~4182
   //AE disable settings
   u8  u8AEdisable_tablelength;//addr=4183
   u16 AE_disable[16];//addr=4184~4215
   //Sensor degree 0 settings
   u8 u8Sensordegree0_tablelength;//addr=4216
   u16 Sensor_degree0[8];//addr=4217~4232
   //Sensor degree 180 settings
   u8 u8Sensordegree180_tablelength;//addr=4233
   u16 Sensor_degree180[8]; //addr=4234~4249
   //AWB enable settings
   u8 u8AWBenable_tablelength;//addr=4250
   u16 AWB_enable[16];//addr=4251~4282
   //AWB disable settings
   u8 u8AWBdisable_tablelength;//addr=4283
   u16 AWB_disable[16];//addr=4284~4315
   //AE target related settings
   u8 u8AEtarget_index;//addr=4316~4317
   u16 AEtarget_tablelength;//addr=4318
   u16 u8AEtarget_table[16];//addr=4319~4350
   //Frame rate level for PC Cam, video and night mode
   u8 u8Framerate_level;//addr=4351
   //PC Cam mode frame rate level setting length and table
   u8 u16Framerate_pccam_length;//addr=4352
   u16 Framerate_pccam_table[96];//addr=4353~4544
   //Video mode frame rate level setting length and table
   u8 u16Framerate_video_length;//addr=4545
   u16 Framerate_video_table[96];//addr=4546~4737
   //Night mode frame rate level setting length and table
   u8 u16Framerate_preview_length;//addr=4738
   u16 Framerate_preview_table[96];//addr=4739~4930
  //Manual WB mode
   u8 u8Manual_WBmode;//addr=4931
   //Manual WB mode settings length and table
   u8 u8Manual_WB_length;//addr=4932
   u16 Manual_AWBtable[48];//4933~5028
  //Brightness level settings
   u8 u8Brightness_level;//addr=5029
  //Brightness table length and table
   u8 u8Manual_Brightness_length;//5030
   u16 Brightness_table[48];//5031~5126
   //Contrast level settings
   u8 u8Contrast_level;//addr=5127
  //Contrast table length and table
   u8 u8Manual_Contrast_length;//5128
   u16 Contrast_table[48];//5129~5224
   //resolution and quality related settings
   u16 u16SENSOR_WIDTH;//actual sensor full size width,addr+5225~5226
   u16 u16SENSOR_HEIGHT;//actual sensor full size Height,addr+5227~5228
   u16 u16PREVIEW_WIDTH;//sensoe preview width, addr+5229~5230
   u16 u16PREVIEW_HEIGHT;//sensoe preview width, addr+5231~5232
   u8  u8DENOISE_STR;//denoise, addr+5233
   u8  u8EDGE_STR;//Edge, addr+5234
   u8  u8SAT_ENABLE;//SAT enable,addr+5235
   u8  u8SAT_R_GAIN;//SAT_R_GAIN,addr+5236
   u8  u8SAT_G_GAIN;//SAT_G_GAIN,addr+5237
   u8  u8SAT_B_GAIN;//SAT_B_GAIN,addr+5238
   u8  u8SAT_Y_GAIN;//SAT_Y_GAIN,addr+5239
   u8  u8SAT_M_GAIN;//SAT_M_GAIN,addr+5240
   u8  u8SAT_C_GAIN;//SAT_C_GAIN,addr+5241
   u8  u8SAT_S_GAIN;//SAT_M_GAIN,addr+5242
   u8  u8AUTOBL;//Auto black level,addr+5243
   //Some related engine settings for Capture
   u8  u8Icp_freq_index_cap;//addr+5244
   u8  u8Isp_freq_index_cap;//addr+5245
   u8  u8Scl_freq_index_cap;//addr+5246
   u8  u8miu_freq_cap;//addr+5247
   u8  u8cpu_freq_cap;//addr+5248
   u8  u8jpe_freq_cap;//addr+5249
   u8  u8Sensor_freq_cap;//addr+5250
   u8  u8SensorReg_indexbyte;//addr+5251
   u8  u8SensorReg_databyte;//addr+5252
   //some settings for Capture Zoom
   u8  u8CapZoom_SCLK_Idx;//addr+5253
   u16 u16Sensor_PLL_Addr;//addr+5254~5255
   u16 u8CaptureZoom_PLL; //addr+5256~5257
   u16 u16Sensor_ClkScale_Addr;//addr+5258~5259
   u16 u8CaptureZoom_ClkScle;//addr+5260~5261
   u8  u8Preview_CapZoom_factor;//addr+5262
   u8  u8CapZoom60HZ_tablelength;//addr+5263
   u16 CapZoom_antiflicker60HZ[8];//addr+5264~5279
   u8  u8CapZoom50HZ_tablelength;//addr+5280
   u16 CapZoom_antiflicker50HZ[8];//addr+5281~5296
   //AE target level settings
   u8 u8AE_target_level;//addr+5297
   u8 u8AE_target_table_length;//addr+5298
   u16 AE_target_table[127];//addr+5299~5552
   u8 u8AE_target_level_fast;//addr+5553
   u8 u8AE_target_table_length_fast;//addr+5554
   u16 AE_target_table_fast[127];//addr+5555~5808
   //exposure time settings
   u8 u8exposure_time_mode;//addr+5809
   u8 u8EXP_register_number;//addr+5810
   u16 u16EXP_L;//addr+5811~5812
   u8 u8EXP_L_startbit;//addr+5813
   u8 u8EXP_L_stopbit;//addr+5814
   u16 u16EXP_M;//addr+5815~5816
   u8 u8EXP_M_startbit;//addr+5817
   u8 u8EXP_M_stopbit;//addr+5818
   u16 u16EXP_H;//addr+5819~5820
   u8 u8EXP_H_startbit;//addr+5821
   u8 u8EXP_H_stopbit;//addr+5822
   u8 u8Insert_Vblanking_flag;//addr+5823
   u8 u8Insert_Vblanking_reg_number;//addr+5824
   u16 u16Vblanking_register_L;//addr+5825~5826
   u8 u8Vblanking_register_L_startbit;//addr+5827
   u8 u8Vblanking_register_L_endtbit;//addr+5828
   u16 u16Vblanking_register_H;//addr+5829~5830
   u8 u8Vblanking_register_H_startbit;//addr+5831
   u8 u8Vblanking_register_H_endtbit;//addr+5832
   u16 u16Vblanking_value;//addr+5833~5834
   u32 u32exposure_reserved0;//addr+5835~5838
   u32 u32exposure_reserved1;//addr+5839~5842
   u32 u32sensor_ADC;//addr+5843~5846
   u32 u32Y_value;//addr+5847~5850
   u8 u8Preview_capture_tablelength;//addr+5851
   u16 Preview_capture[8];//addr+5852~5867
   u8 u8auto_blacklevel;//addr+5868
   u8 u8Capture_skipframe;//addr+5869
   u8 u8Sensor_delay_preview_frame;//addr+5870
   u8  u8Sensormirror_tablelength;//addr=5871
   u16 Sensor_mirror[8];//addr=5872~5887
   u8  u8sensor2_powerdown_GPIO_enable; //addr=5888,
   u8  u8sensor2_powerdown_GPIO_direction; //addr=5889,
   u8  u8sensor2_powerdown_GPIO;//addr=5890
   u8  u8sensor2_powerdown_parity;//	addr=5891
   u8  u8sensor1_powerdown_parity;//	addr=5892
   u8  u8Sensorflip_tablelength;//addr=5893
   u16 Sensor_flip[8];//addr=5894~5909
   u16 u16MaxZoom_width;//5910~5911
   u16 u16Minzoom_height;//5912~5913
   u8  u8AF_mode;//addr=5914
   u8  u8AF_enable;//5915
   u16 u16AF_table_length;//5916~5917
   u16 AF_table[7168];//14K,5918~20253
   u8  sensor_ID_page_enable;//20254
   u8  senosr_ID_page_length;//20255
   u16 senosr_ID_page_table[4];//20263
   u16 u16Sensor_inittable_length_EX1;//20265
   u16 sensor_initial_table_EX1[256];//20777
   u8 u16Framerate_pccam_length_EX1;//20778
   u16 Framerate_pccam_table_EX1[48];//20874
   u8 u16Framerate_video_length_EX1;//20875
   u16 Framerate_video_table_EX1[48];//20971
   u8 u16Framerate_preview_length_EX1;//20972
   u16 Framerate_preview_table_EX1[48];//21068
   u8  u8Cap60HZ_tablelength;//21069
   u16 Cap_antiflicker60HZ[8];//21085
   u8  u8Cap50HZ_tablelength;//21086
   u16 Cap_antiflicker50HZ[8];//21102
   u8  u8CapZoom_page_enable;//21103
   u8  u8CapZoom_page_length;//21104
   u16 CapZoom_page_table[8];//21120
   u8  u8CapZoomPLL_length;//21121
   u16 CapZoomPLL_table[32];//21185
   u8 u8Manual_WB_length_EX1;//21186
   u16 Manual_AWBtable_EX1[48];//21282
   u16 u16Sensor_inittable_length_EX2;//21284
   u16 sensor_initial_table_EX2[256];//21796
   u8  u8AF_action_table_length;//21797
   u16 u16AF_action_table[16];//21829
   u16 u16AF_ready_register;//21831
   u16 u16AF_ready_mask_bit;//21833
   u16 u16AF_ready_delay; //21835
   u16 u16AF_ready_value;
   u8  Fast_framerate_enable;
   u8  u8Framerate_30_video_length;
   u16 Framerate_30_video_table[96];
   u8  u8Sensor_freq_video;
   u8  sensor_information[64];//22096
   u8  u8_SPI_sensor_enable;//22097
   u16 u16empty1;//22099(5653)+10h=5663
} SenTab_s;

#ifdef __GNUC__

#pragma pack()
#endif
#endif
//sensor table
#if defined(__MULTIPLE_SENSOR_TABLE_DETECTION__)
	DrvSr_ErrCode_e fn_Sensor_Table_Init(u8 *pu8SRTBL, SEN_SRC_e  eSource); // u32 fn_Sensor_Table_Init(u32 *pu32SRTBL)
	DrvSr_ErrCode_e fn_SensorTableSwitch(SEN_SRC_e eSource);
	DrvSr_ErrCode_e fn_CheckSenTab(void);
	u8* fn_Sensor_GetSenTbl(SEN_SRC_e eSource);
    void fn_Sensor_SetSenTbl(u8 *Sen_Tab, SEN_SRC_e eSource);
#endif
DrvSr_ErrCode_e fn_Sensor_Init(u8 UVC, SEN_INIT_PARA_t *pPara) ; // DrvSr_ErrCode_e fn_Sensor_Init(u8 UVC, u8 *pu8MdlCam_Para, u8 *pbSRTBLAddr); // DrvSr_ErrCode_e fn_Sensor_Init(u8 UVC, u8 *pu8MdlCam_Para); // void fn_Sensor_Init(u8 UVC);


//info
void fn_Sensor_Set_15FPS_VDR_Capability(u32 u32_15fps_VDR_Capability);
void fn_Sensor_Reset_15FPS_VDR_Capability(void);
u8 fn_Sensor_GetFramerate15VideoTable(void);
u8 fn_Sensor_GetVSyncPolarity(void);
u16 fn_Sensor_GetSensorWidth(void);
u16 fn_Sensor_GetSensorHeight(void);
u16 fn_Sensor_SetSensorWidth(u16 SensorWidth);
u16 fn_Sensor_SetSensorHeight(u16 SensorHeight);

u16 fn_Sensor_GetPreviewWidth(void);
u16 fn_Sensor_GetPreviewHeight(void);
u8 fn_Sensor_isHoldFrameUpdate(void);
u8 fn_Sensor_GetPreviewFrameDelay(void);
u16 fn_SensorReadLuma(void);
u8 fn_Sensor_CheckSensorID(u8 *Sen_Tab, SEN_SRC_e eSource);
u8 DrvSenSetFifoFullStatusGet(void);
void DrvSenSetFifoFullStatusSet(u8 nSta);
u8 fn_Sensor_ZoomCapability(u16 nWidth, u16 nHeight);
SenDataFormat_e fn_Sensor_CaptureSensorFormat(u16 nWidth, u16 nHeight);
s32 fn_Sensor_AA_Save(void);
s32 fn_Sensor_AA_Restore(void);


#if defined(__DEVICE_INFO__)
u16 DrvSenGetCamStrInfo(u8 id, char *pStr, u16 maxLen);
#endif

//set
void fn_Sensor_FullSet(u16 frame_width,u16 frame_height, SEN_ANTI_FLICKER_e eSenFlickerHz);
DrvSr_ErrCode_e fn_Sensor_SetXYFlip(u8 u8SensorXYFlip);
DrvSr_ErrCode_e fn_Sensor_SetFrameRate(SEN_ANTI_FLICKER_e eAntiFlicker, u8 u8EnvirCn, u8 u8TableSelect);

//power
void fn_Sensor_SetPowerDown( SEN_PWR_e eEnable,SEN_SRC_e eSource);

//clock
void fnSensorCLK_Enable(u8 bEnable);
//sensor interface
void fn_Sensor_SIFInit(void);
//irq
void fn_Sensor_EnableIrq(void);
void fn_Sensor_DisableIrq(void);
void fn_Sensor_FIFOFULLIRQ_CB_Config(void);
DrvSr_ErrCode_e fn_SensorWaitVsync(u16 nFrameCount);
//Set color, brightness, flicker, special effect...
DrvSr_ErrCode_e	fn_Sensor_SetEV(u8 u8EVLevel);
DrvSr_ErrCode_e   fn_Sensor_SetEnvirCn(SenSceneMode_e eEnvirCn);
DrvSr_ErrCode_e	fn_Sensor_SetAntiFlicker(SEN_ANTI_FLICKER_e eAntiFlicker);
DrvSr_ErrCode_e   fn_Sensor_SetAWBEnable(u8 u8AWBEnable);
DrvSr_ErrCode_e   fn_Sensor_SetAWBMode(SenWhiteBalanceMode_e eAWBMode);
DrvSr_ErrCode_e fn_Sensor_SetExposure(SenExposureMode_e eMode, u8 u8Option);
void fn_Sensor_BriSet_new(U16 u16Bri);
void fn_Sensor_ContrastSet_new(U16 u16Cont);
void fn_Sensor_special_effect(u8 mode);
u32 fn_Sensor_special_effect_bitmask(void);
u16 fn_Sensor_AutoFocus(void);
u16 fn_Sensor_Single_AF(void);
u16 fn_Sensor_AF_supported(void);
void fn_Sensor_set_autofocus_capture(u8 AF_capture);
u8  fn_SPI_sensor_get(void);
u8 fn_Zoom_factor_enable(void);
//ATV
void fn_ATV_SIFInit(DrvSrif_InitPara_t *SensorIF_InitPara);
void fn_ATV_IRQ_CB_Disable(u8 VSYNC_POLARITY);
void fn_ATV_IRQ_CB_Config(u8 VSYNC_POLARITY);
void fn_ATV_FIFOFULLIRQ_CB_Config(void);
//UVC
DrvSr_ErrCode_e	fn_Sensor_SetUVC(u8 u8UVC);
//CB
u16 fn_Sensor_RegExternalIrqCallback(void (*fn)(void));
u16 fn_Sensor_UnRegExternalIrqCallback(void);
void fn_Sensor_JpegCaptureQuality(u8 nJpegCaptureQuality);
u32 fn_Sensor_GetJpegRealSize(u8 *pCaptureJpegBuffer);

u8 fnSensorMCLK_SetHalfCLK(u8 isHalfCLK);

#endif //DRV_SENSOR_DRIVER_PUB_H__


