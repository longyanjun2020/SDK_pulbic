#ifndef _IQSERVER_API_ID_H
#define _IQSERVER_API_ID_H

#define ID_API_COMMON_BASE              0x0000
#define ID_API_COMMON_END               0x0FFF

#define ID_API_ISP_BASE		            0x1000
#define ID_API_ISP_END		            0x1FFF

#define ID_API_CALIBRATION_20_BASE		0x2000
#define ID_API_CALIBRATION_20_END		0x22FF

#define ID_API_MAINTOOL_BASE            0x2300
#define ID_API_MAINTOOL_END             0x25FF

#define ID_API_PLUGIN_BASE              0x2600
#define ID_API_PLUGIN_END               0x28FF


//================================================================
//  ID Defined : Common  API
//================================================================
#define ID_API_COMMON_I2C_ACCESS                ( ID_API_COMMON_BASE + 32 ) //SET_API_ID_MI_ISP_WriteI2C
#define ID_API_COMMON_QuerySensorInfo           ( ID_API_COMMON_BASE + 33 ) //GET_API_ID_MI_ISP_QuerySensorInfo
#define ID_API_COMMON_OBCCALIB                  ( ID_API_COMMON_BASE + 35 )
#define ID_API_COMMON_FileID                    ( ID_API_COMMON_BASE + 100 )

//================================================================
//  ID Defined : ISP  API
//================================================================
//#define ID_API_ISP_ExposureAttr                 ( ID_API_ISP_BASE +  1 ) //1.  4097
//#define ID_API_ISP_ExposureStgyProp             ( ID_API_ISP_BASE +  2 ) //2.  4098
#define ID_API_ISP_QueryExposureInfo            ( ID_API_ISP_BASE +  3 ) //3.  4099
#define ID_API_ISP_WhiteBalanceAttr             ( ID_API_ISP_BASE +  4 ) //4.  4100
#define ID_API_ISP_WhiteBalanceAttrEX           ( ID_API_ISP_BASE +  5 ) //5.  4101
#define ID_API_ISP_QueryWBInfo                  ( ID_API_ISP_BASE +  6 ) //6.  4102
#define ID_API_ISP_BlackLevel                   ( ID_API_ISP_BASE +  7 ) //7.  4103
#define ID_API_ISP_DP                           ( ID_API_ISP_BASE +  8 ) //8.  4104
#define ID_API_ISP_Crosstalk                    ( ID_API_ISP_BASE +  9 ) //9.  4105
#define ID_API_ISP_AntiFalseColor               ( ID_API_ISP_BASE + 10 ) //10. 4106
#define ID_API_ISP_AntiFalseColor_EX            ( ID_API_ISP_BASE + 11 ) //11. 4107
#define ID_API_ISP_RGBIR                        ( ID_API_ISP_BASE + 12 ) //12. 4108
#define ID_API_ISP_CCM                          ( ID_API_ISP_BASE + 13 ) //13. 4109
#define ID_API_ISP_Saturation                   ( ID_API_ISP_BASE + 14 ) //14. 4110
#define ID_API_ISP_ColorToGray                  ( ID_API_ISP_BASE + 15 ) //15. 4111
#define ID_API_ISP_CSA                          ( ID_API_ISP_BASE + 16 ) //16. 4112
#define ID_API_ISP_HSV                          ( ID_API_ISP_BASE + 17 ) //17. 4113
#define ID_API_ISP_Gamma                        ( ID_API_ISP_BASE + 18 ) //18. 4114
#define ID_API_ISP_YUVGammaLut                  ( ID_API_ISP_BASE + 19 ) //19. 4115
#define ID_API_ISP_Contrast                     ( ID_API_ISP_BASE + 20 ) //20. 4116
#define ID_API_ISP_Brightness                   ( ID_API_ISP_BASE + 21 ) //21. 4117
#define ID_API_ISP_Lightness                    ( ID_API_ISP_BASE + 22 ) //22. 4118
#define ID_API_ISP_Sharpness                    ( ID_API_ISP_BASE + 23 ) //23. 4119
#define ID_API_ISP_Sharpness_EX                 ( ID_API_ISP_BASE + 24 ) //24. 4120
#define ID_API_ISP_NR2DBayer                    ( ID_API_ISP_BASE + 25 ) //25. 4121
#define ID_API_ISP_NRDeSpike                    ( ID_API_ISP_BASE + 26 ) //26. 4122
#define ID_API_ISP_NRLuma                       ( ID_API_ISP_BASE + 27 ) //27. 4123
#define ID_API_ISP_NR3D                         ( ID_API_ISP_BASE + 28 ) //28. 4124
#define ID_API_ISP_Defog                        ( ID_API_ISP_BASE + 29 ) //29. 4125
#define ID_API_ISP_DRC                          ( ID_API_ISP_BASE + 30 ) //30. 4126
#define ID_API_ISP_WDR                          ( ID_API_ISP_BASE + 31 ) //31. 4127
#define ID_API_ISP_LSC                          ( ID_API_ISP_BASE + 32 ) //32. 4128
#define ID_API_ISP_Exposure                     ( ID_API_ISP_BASE + 33 ) //33. 4129
#define ID_API_ISP_IQMode                       ( ID_API_ISP_BASE + 34 ) //34. 4130
#define ID_API_VENC_RcParamEx                   ( ID_API_ISP_BASE + 35 ) //35. 4131
#define ID_API_VI_SensorFrameRate               ( ID_API_ISP_BASE + 36 ) //36. 4132
#define ID_API_VENC_Resolution                  ( ID_API_ISP_BASE + 37 ) //37. 4133
#define ID_API_ISP_FPN                          ( ID_API_ISP_BASE + 38 ) //38. 4134
#define ID_API_ISP_GetIQVersionInfo             ( ID_API_ISP_BASE + 39 ) //39. 4135
#define ID_API_ISP_AFWindow                     ( ID_API_ISP_BASE + 40 ) //40. 4136
#define ID_API_ISP_AFFilter                     ( ID_API_ISP_BASE + 41 ) //41. 4137
#define ID_API_ISP_QueryAFInfo                  ( ID_API_ISP_BASE + 42 ) //42. 4138
#define ID_API_ISP_BDNR                         ( ID_API_ISP_BASE + 43 ) //43. 4139
#define ID_API_ISP_HDR16to12                    ( ID_API_ISP_BASE + 44 ) //44. 4140
#define ID_API_ISP_ColorTransform               ( ID_API_ISP_BASE + 45 ) //45. 4141
#define ID_API_ISP_CCM_EX                       ( ID_API_ISP_BASE + 46 ) //46. 4142
#define ID_API_ISP_HSV_EX                       ( ID_API_ISP_BASE + 47 ) //47. 4143
#define ID_API_ISP_RGBIRExposureAttr            ( ID_API_ISP_BASE + 48 ) //48. 4144
#define ID_API_ISP_WhiteBalanceMultiLSAttr      ( ID_API_ISP_BASE + 49 ) //49. 4145
#define ID_API_ISP_AE_EVComp                    ( ID_API_ISP_BASE + 50 ) //50. 4146
#define ID_API_ISP_AE_ExpMode                   ( ID_API_ISP_BASE + 51 ) //51. 4147
#define ID_API_ISP_AE_ManualExpo                ( ID_API_ISP_BASE + 52 ) //52. 4148
#define ID_API_ISP_AE_AEState                   ( ID_API_ISP_BASE + 53 ) //53. 4149
#define ID_API_ISP_AE_AETarget                  ( ID_API_ISP_BASE + 54 ) //54. 4150
#define ID_API_ISP_AE_AEConverge                ( ID_API_ISP_BASE + 55 ) //55. 4151
#define ID_API_ISP_AE_ExposureLimit             ( ID_API_ISP_BASE + 56 ) //56. 4152
#define ID_API_ISP_AE_PlainExpTbl               ( ID_API_ISP_BASE + 57 ) //57. 4153
#define ID_API_ISP_AE_AEWinWgt                  ( ID_API_ISP_BASE + 58 ) //58. 4154
#define ID_API_ISP_AE_Flicker                   ( ID_API_ISP_BASE + 59 ) //59. 4155
#define ID_API_ISP_AE_AEStrategy                ( ID_API_ISP_BASE + 60 ) //60. 4156
#define ID_API_ISP_WDR_GBL                      ( ID_API_ISP_BASE + 61 ) //61. 4157
#define ID_API_ISP_BlackLevel_P1	            ( ID_API_ISP_BASE + 62 ) //62. 4158
#define ID_API_ISP_AE_PlainShortExpTbl          ( ID_API_ISP_BASE + 63 ) //63. 4159
#define ID_API_ISP_HDR                          ( ID_API_ISP_BASE + 64 ) //64. 4160
#define ID_API_ISP_AE_HDR	                    ( ID_API_ISP_BASE + 65 ) //64. 4161

//================================================================
//  ID Defined : Calibration 2.0 API
//================================================================
#define ID_API_CALIBRATION_20_CaliBVAV              ( ID_API_CALIBRATION_20_BASE + 1 ) //SET_API_ID_CALIBRATION_CaliBVAV = 61,
#define ID_API_CALIBRATION_20_Apply                 ( ID_API_CALIBRATION_20_BASE + 2 ) //SET_API_ID_CALIBRATION_ApplyBVAV = 62,
#define ID_API_CALIBRATION_20_CaliData              ( ID_API_CALIBRATION_20_BASE + 3 ) //SET_API_ID_CALIBRATION_SetCaliData = 63,
#define ID_API_CALIBRATION_20_CaliPath              ( ID_API_CALIBRATION_20_BASE + 4 ) //SET_API_ID_CALIBRATION_SetCaliPath = 64,
#define ID_API_CALIBRATION_20_CaliDBPath            ( ID_API_CALIBRATION_20_BASE + 5 ) //SET_API_ID_CALIBRATION_SetCaliDBPath
#define ID_API_CALIBRATION_20_CaliInfo              ( ID_API_CALIBRATION_20_BASE + 6 ) //GET_API_ID_CALIBRATION_GetCaliInfo

#define ID_API_CALIBRATION_20_CaliAWB               ( ID_API_CALIBRATION_20_BASE + 7 )
#define ID_API_CALIBRATION_20_CaliOB                ( ID_API_CALIBRATION_20_BASE + 8 )
#define ID_API_CALIBRATION_20_CaliMinGain           ( ID_API_CALIBRATION_20_BASE + 9 )
#define ID_API_CALIBRATION_20_CaliShutterLinearity  ( ID_API_CALIBRATION_20_BASE + 10)
#define ID_API_CALIBRATION_20_CaliGainLinearity     ( ID_API_CALIBRATION_20_BASE + 11)
#define ID_API_CALIBRATION_20_CaliDPC               ( ID_API_CALIBRATION_20_BASE + 12)
#define ID_API_CALIBRATION_20_CaliALSC              ( ID_API_CALIBRATION_20_BASE + 13)
#define ID_API_CALIBRATION_20_CaliFPN               ( ID_API_CALIBRATION_20_BASE + 14)

//================================================================
//  ID Defined : MainTool  API
//================================================================
#define ID_API_MAINTOOL_QuerySensorInfo         ( ID_API_MAINTOOL_BASE + 1 ) //GET_API_ID_MI_ISP_QuerySensorInfo
#define ID_API_MAINTOOL_GetIQInd                ( ID_API_MAINTOOL_BASE + 2 ) //GET_API_ID_MI_ISP_QuerySensorInfo
#define ID_API_MAINTOOL_ByPass                  ( ID_API_MAINTOOL_BASE + 3 )

//================================================================
//  ID Defined : Plugin  API
//================================================================
#define ID_API_PLUGIN_I2C_ACCESS                ( ID_API_PLUGIN_BASE + 1 ) //SET_API_ID_MI_ISP_WriteI2C
#define ID_API_PLUGIN_OBCCALIB                  ( ID_API_PLUGIN_BASE + 2 ) //GET_API_ID_MI_ISP_GetOBCCALIB
#define ID_API_PLUGIN_WBCT                      ( ID_API_PLUGIN_BASE + 3 )
#define ID_API_PLUGIN_AWBCTStats                ( ID_API_PLUGIN_BASE + 4 )
#define ID_API_PLUGIN_AWBHWStats                ( ID_API_PLUGIN_BASE + 5 )

#endif
