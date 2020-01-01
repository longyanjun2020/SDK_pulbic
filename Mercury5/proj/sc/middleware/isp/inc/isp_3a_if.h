#ifndef ISP_3A_IF_H
#define ISP_3A_IF_H

#include <drv_ms_isp_general.h>
#include <drv_ms_rwcfg.h>
#include <isp_reg_shadow.h>

typedef void* IqCfgHandle; //debug buffer handle
typedef void* AwbHandle;
typedef void* AeHandle;

/******************* IQ_DEBUG_Mode ********************/
typedef enum
{
    DEBUG_ENABLE_IQ,     /**< Stop IQ update */
    DEBUG_LEVEL,         /**< enable show log of iq.debug.blkid */
    DEBUG_BLKID,         /**< show log for each IP */
    DEBUG_PARALEV,       /**< parameter level: SUB(0)/DBG(1)/HAL(2) */
    DEBUG_INDSHOW,       /**< show GainCheck result */
    DEBUG_TBLSCAL,       /**< set table scale for debug show (def: 16, only work for 8, 4, 2, 1)*/
    DEBUG_SETPROPEN,     /**< replace function by setprop (works by follow mark with $$) */
    DEBUG_ISOFIX,        /**< ($$)fix iso to present index */
    DEBUG_ISOIND,        /**< ($$)assign isoind under fix iso mode */
    DEBUG_IQ_TRIGGER,   /**< ($$)Force Trigger IQ by mod and blkid */
    DEBUG_IQ_TRIGMOD,   /**< ($$)Force Trigger IQ by mod and blkid */
    DEBUG_AUTOIQ,       /**< on/off autoiq (def:on) */
    DEBUG_SKIPCFGVC,    /**< skip cfg major version check */

    DEBUG_APISHOW,       /**< show debug message of API */
    DEBUG_APIRESET,      /**< reset all API setting of OFF */

    DEBUG_SKIPML,

    //---[WDR_GBL, WDR_LOC]
    DEBUG_FEATURE_LEVEL,
    DEBUG_DEFOG_ENABLE,
    DEBUG_DEFOG_MODE,
    DEBUG_DEFOG_AUTO_LEVEL,
    DEBUG_DEFOG_MANUAL_LEVEL,
    DEBUG_DRC_ENABLE,
    DEBUG_DRC_WHITE_LEVEL,
    DEBUG_DRC_BLACK_LEVEL,
    DEBUG_DRC_ASYMMETRY,
    DEBUG_DRC_BRIGNT_ENHANCE,
    DEBUG_DRC_EMODE,
    DEBUG_DRC_MANUAL_LEVEL,
    DEBUG_DRC_AUTO_LEVEL,
    DEBUG_LOCWDR_TblShow,
    DEBUG_LOCWDR_TblSmooth,


    //---[RGBIR]
    DEBUG_IRIDX_THRD_0,
    DEBUG_IRIDX_THRD_1,
    DEBUG_IRIDX_THRD_2,
    DEBUG_IRIDX_THRD_3,
    DEBUG_IRIDX_THRD_4,

    //---[MEMALLOC]
    DEBUG_NLM_MEMALLOC_EN,
    DEBUG_HIST_MEMALLOC_EN,

    DBG_PROP_MAX,
} DBG_PROP;

typedef struct
{
    //---[Enable IQ]
    MS_U16 IQ_DEBUG_ENABLE_IQ;     /**< Stop IQ update */
    MS_U16 IQ_DEBUG_LEVEL;         /**< enable show log of iq.debug.blkid */
    MS_U16 IQ_DEBUG_BLKID;         /**< show log for each IP */
    MS_U16 IQ_DEBUG_PARALEV;       /**< parameter level: SUB(0)/DBG(1)/HAL(2) */
    MS_U16 IQ_DEBUG_INDSHOW;       /**< show GainCheck result */
    MS_U16 IQ_DEBUG_TBLSCAL;       /**< set table scale for debug show (def: 16, only work for 8, 4, 2, 1)*/
    MS_U16 IQ_DEBUG_SETPROPEN;     /**< replace function by setprop (works by follow mark with $$) */
    MS_U16 IQ_DEBUG_ISOFIX;        /**< ($$)fix iso to present index */
    MS_U16 IQ_DEBUG_ISOIND;        /**< ($$)assign isoind under fix iso mode */
    MS_U16 IQ_DEBUG_IQ_TRIGGER;   /**< ($$)Force Trigger IQ by mod and blkid */
    MS_U16 IQ_DEBUG_IQ_TRIGMOD;   /**< ($$)Force Trigger IQ by mod and blkid */
    MS_U16 IQ_DEBUG_AUTOIQ;       /**< on/off autoiq (def:on) */
    MS_U16 IQ_DEBUG_SKIPCFGVC;    /**< skip cfg major version check */
    //---[API]
    MS_U16  IQ_DEBUG_APISHOW;      /**< show debug message of API */
    MS_U16  IQ_DEBUG_APIRESET;     /**< reset all API setting of OFF */
    //---[MLoad]
    MS_U16  IQ_DEBUG_SKIPML;
    //---[WDR_GBL, WDR_LOC]
    MS_U16  IQ_DEBUG_FEATURE_LEVEL;
    MS_U16  IQ_DEBUG_DEFOG_ENABLE;
    MS_U16 IQ_DEBUG_DEFOG_MODE;
    MS_U16 IQ_DEBUG_DEFOG_AUTO_LEVEL;
    MS_U16 IQ_DEBUG_DEFOG_MANUAL_LEVEL;
    MS_U16  IQ_DEBUG_DRC_ENABLE;
    MS_U16 IQ_DEBUG_DRC_WHITE_LEVEL;
    MS_U16 IQ_DEBUG_DRC_BLACK_LEVEL;
    MS_U16 IQ_DEBUG_DRC_ASYMMETRY;
    MS_U16 IQ_DEBUG_DRC_BRIGNT_ENHANCE;
    MS_U16 IQ_DEBUG_DRC_EMODE;
    MS_U16 IQ_DEBUG_DRC_MANUAL_LEVEL;
    MS_U16 IQ_DEBUG_DRC_AUTO_LEVEL;
    MS_U16  IQ_DEBUG_LOCWDR_TblShow;
    MS_U16  IQ_DEBUG_LOCWDR_TblSmooth;
    //---[RGBIR]
    MS_U16 IQ_DEBUG_IRIDX_THRD_0;
    MS_U16 IQ_DEBUG_IRIDX_THRD_1;
    MS_U16 IQ_DEBUG_IRIDX_THRD_2;
    MS_U16 IQ_DEBUG_IRIDX_THRD_3;
    MS_U16 IQ_DEBUG_IRIDX_THRD_4;
    //---[Memalloc]
    MS_U16  IQ_DEBUG_NLM_MEMALLOC_EN;
    MS_U16  IQ_DEBUG_HIST_MEMALLOC_EN;

} IQDEBUG_t;

typedef struct
{
    //---[Enable AE]
    MS_S32 AE_DEBUG_ENABLE_AE;          /**< Enable/Disable AE */
    MS_S32 AE_DEBUG_LEVEL;              /**< 0: disable, 1: Exposure 2: Algo parameters 4: Algo statistics 32: API debug */

} AEDEBUG_t;

typedef struct
{
    //---[Enable AWB]
    MS_S32 AWB_DEBUG_AWB_ENABLE;        /**< Enable/Disable AWB */
    MS_S32 AWB_DEBUG_MWB_ENABLE;        /**< Enable/Disable MWB */
    MS_S32 AWB_DEBUG_MWB_RGAIN;         /**< MWB Rgain */
    MS_S32 AWB_DEBUG_MWB_BGAIN;         /**< MWB Bgain */
    MS_S32 AWB_DEBUG_LEVEL;             /**< AWB Debug Mode: 1:show simple algo paramaters 2:always show detail algo parameters 3:show detail algo parameters 7:User Paramters*/

} AWBDEBUG_t;

/******************* AE *********************/
#define isp_3A_ROW          128   /**< number of 3A statistic blocks in a row */
#define isp_3A_COL          90    /**< number of 3A statistic blocks in a column */
#define isp_3A_HIST_BIN0    40    /**< histogram type0 resolution*/
#define isp_3A_HIST_BINX    128   /**< histogram type1 resolution*/
#define isp_DLC_HISTOGRAM_REPORT_NUM    8 /**< histogram type1 resolution(DRC)*/


typedef struct
{
    MS_U8  r;
    MS_U8  g;
    MS_U8  b;
    MS_U8  y;
} __attribute__((packed, aligned(1))) ISPAESample_t;

typedef struct
{
    MS_U16 u2HistY[isp_3A_HIST_BINX];
} __attribute__((packed, aligned(1))) ISPHistX_t;

typedef struct
{
    MS_U32 Size;                   /**< struct size*/
    char sensor_id[32];             /**< sensor module id*/
    MS_U32 shutter;                /**< shutter Shutter in us*/
    MS_U32 shutter_step;           /**< shutter Shutter step us*/
    MS_U32 shutter_min;            /**< shutter Shutter min us*/
    MS_U32 shutter_max;            /**< shutter Shutter max us*/
    MS_U32 sensor_gain;            /**< sensor_gain Sensor gain, 1X = 1024*/
    MS_U32 sensor_gain_min;        /**< sensor_gain_min Minimum Sensor gain, 1X = 1024*/
    MS_U32 sensor_gain_max;        /**< sensor_gain_max Maximum Sensor gain, 1X = 1024*/
    MS_U32 isp_gain;               /**< isp_gain Isp digital gain , 1X = 1024 */
    MS_U32 isp_gain_max;           /**< isp_gain Maximum Isp digital gain , 1X = 1024 */
    MS_U32 FNx10;                  /**< F number * 10*/
    MS_U32 fps;                    /**< initial frame per second*/
}ISPAEInitParam_t,AeInitParam_t;

/*! @brief ISP report to AE, hardware statistic */
typedef struct
{
    MS_U32 Size;            /**< struct size*/
    ISPHistX_t *hist1;      /**< HW statistic histogram 1*/
    ISPHistX_t *hist2;      /**< HW statistic histogram 2*/
    MS_U32 AvgBlkX;         /**< HW statistics average block number*/
    MS_U32 AvgBlkY;         /**< HW statistics average block number*/
    ISPAESample_t *avgs;    /**< HW statistics average block data*/
    MS_U32 FNx10;           /**< Current Aperture in FNx10*/
    MS_U32 Shutter;         /**< Current shutter in ns*/
    MS_U32 SensorGain;      /**< Current Sensor gain, 1X = 1024 */
    MS_U32 IspGain;         /**< Current ISP gain, 1X = 1024*/
    MS_U32 ShutterHDR;      /**< Shutter in ns */
    MS_U32 SensorGainHDR;   /**< Sensor gain, 1X = 1024 */
    MS_U32 IspGainHDR;      /**< ISP gain, 1X = 1024 */
    MS_U32 PreCurYx10;
    MS_U32 PreAvgYx10;
    AEDEBUG_t *tAEDebug;    /**< AE debug -> unit test*/
} __attribute__((packed, aligned(1))) ISPAEInfo_t, AeInput_t;

/*! @brief ISP ae algorithm result*/
typedef struct
{
    MS_U32 Size;            /**< struct size*/
    MS_U32 Change;          /**< if true, apply this result to hw register*/
    MS_U32 FNx10;           /**< Aperture in FNx10*/
    MS_U32 Shutter;         /**< Shutter in ns */
    MS_U32 SensorGain;      /**< Sensor gain, 1X = 1024 */
    MS_U32 IspGain;         /**< ISP gain, 1X = 1024 */
    MS_U32 ShutterHDR;      /**< Shutter in ns */
    MS_U32 SensorGainHDR;   /**< Sensor gain, 1X = 1024 */
    MS_U32 IspGainHDR;      /**< ISP gain, 1X = 1024 */
    MS_S32 i4BVx16384;      /**< Bv * 16384 in APEX system, EV = Av + Tv = Sv + Bv */
    MS_U32 CurYx10;         /**< frame brightness with weighting*/
    MS_U32 AvgYx10;         /**< frame brightness */
    MS_U32 SceneTargetx10;  /**< Current AE target for CurY */
    MS_BOOL IsStable;
    MS_BOOL IsReachBoundary;
    MS_U8  HistMaxY;        /**< HistMaxY*/
	MS_U32 AeHdr_Num_BV[17];
}__attribute__((packed, aligned(1))) ISPAEResult_t, AeOutput_t;

/*! @brief AE library initialization
    @param[in] CfgHandle IQ data handle
    @retval SUCCESS or FAIL if error occurs.
*/
AeHandle AeInit(AeInitParam_t pInitParam,ISP_DBGBUF_HANDLE CfgHandle,AeInput_t *input_param, AeOutput_t *output_param);

/*! @brief Release resources that allocated at AeInit
    @param[in] IQ data handle
    @retval SUCCESS or FAIL if error occurs.
*/
MS_S32 AeRelease(AeHandle Handle);

/*! @brief AE algorithm entry
    @param[in] handle AE Algorithm private data
    @param[in] pInput AE algorithm input.
@param[in] pDbgBuf Debug buffer handle.
    @param[out] pOutput AE algorithm result.
    @retval SUCCESS or FAIL if error occurs.
*/
MS_S32 DoAe(AeHandle Handle,const AeInput_t *pInput,AeOutput_t *pOutput);


/******************* AWB ********************/
/*! @brief AWB gain*/

//typedef struct
//{
//    MS_U16 nRgain;     /** R  channel */
//    MS_U16 nGrgain;    /** Gr channel */
//    MS_U16 nGbgain;    /** Gb channel */
//    MS_U16 nBgain;     /** B  channel */
//} IspAwbGain_t;

/*! @brief Input parameters of function DoAWB()*/
typedef struct
{
    MS_U32          nSize;          /**< Size of DoAwbInput_t */
    MS_U32          nFrameCount;    /**< Frame counts */
    MS_S32          nBV;            /**< Bright value from DoAE() result */
	MS_S32			CurYx10;
    IspCropWin_t    tCrop;          /**< AWB statistic windows parameter */
    IspAwbWin_t     tBlock;         /**< AWB statistic block parameter */
    IspAwbStatis_t  *pAwbStatis;    /**< AWB statistic data */
    AWBDEBUG_t      *tAWBDebug;     /**< AWB debug -> unit test*/
}AwbInput_t;

/*! @brief Output of function DoAWB()*/
typedef struct
{
    MS_U32          nSize;                  /** Size of DoAwbOutput_t */
    IspCropWin_t    tCrop;                  /**< New AWB statistic windows settings for next frame */
    IspAwbWin_t     tBlock;                 /**< New AWB statistic block settings for next frame */
    IspAwbGain_t    tGain;                  /**< AWB gain */
    MS_U16          nColorTmp;              /**< Color temperature */
    MS_BOOL         nMultiLS_CaliCCMUpdate; /**< Color calibration CCM update flag for multi-lightsource*/
    MS_U16          nMultiLS_CaliCCM[9];    /**< Color calibration CCM for multi-lightsource*/
}AwbOutput_t;


/*! @brief AWB algorithm entry
    @param[in] handle AWB Algorithm private data
    @param[in] AWB HW statistics
    @param[out] pOutput AWB algorithm result.
    @retval SUCCESS or FAIL if error occurs.
*/
MS_S32 DoAwb(AwbHandle Handle, const AwbInput_t *pInput, AwbOutput_t *pOutput);

/*! @brief AWB library initialization
    @param[in] CfgHandle IQ data handle
    @retval SUCCESS or FAIL if error occurs.
*/
AwbHandle AwbInit(ISP_DBGBUF_HANDLE CfgHandle, AwbInput_t *input_param, AwbOutput_t *output_param);

/*! @brief Release resources that allocated at AwbInit
    @param[in] IQ data handle
    @retval SUCCESS or FAIL if error occurs.
*/
MS_S32 AwbRelease(AwbHandle Handle);


/******************* IQ ********************/
/*! @brief Calculate IQ for current condition then output the ISP setting to shadow register buffer
    @param[in] pHandle IQ handle
    @param[out] pRegShd register shadow buffer
    @retval SUCCESS or FAIL if error occurs.
*/
/*! @brief Input of function DoIQ()*/

typedef struct
{
    MS_U32 nHistY[isp_DLC_HISTOGRAM_REPORT_NUM];       ///<  reg_total_1f-ff_00
    MS_U32 nPixelWeight;                               ///<  reg_main_total_pixel_weight
    MS_U32 nPixelCount;                                ///<  reg_main_total_pixel_count
    MS_U8 nMinPixel;                                   ///<  reg_main_min_pixel
    MS_U8 nMaxPixel;                                   ///<  reg_main_max_pixel
    MS_U8 nBaseidx;                                    ///<  reg_vip_stat_baseidx
} __attribute__((packed, aligned(1))) IQDRCHistX_t;

typedef struct
{
    MS_U32 nSize;               /** Size of IqInput_t **/
    MS_S32 nBV;                 /**< Bright value from DoAE() result */
    MS_U32 nTotalGain;          /** TotalGain = ISP gain + Sensor gain **/
    MS_S32 nChipTemp;           /** Chip temperature **/
    MS_S32 nSensorTemp;         /** Sensor temperature **/
    MS_U32 nColorTemp;          /** Color temperature **/
    MS_U32 nAwbRx1024;          /** Awb R gain 1024 base **/
    MS_U32 nAwbGx1024;          /** Awb G gain 1024 base **/
    MS_U32 nAwbBx1024;          /** Awb B gain 1024 base **/
    MS_U32 nWdrRatiox1024;      /** Wdr ratio 1024 base **/
    MS_U32 nIrindex;            /** RGBIR index **/
    MS_U32 nCropSizeW;          /** Image width after crop **/
    MS_U32 nCropSizeH;          /** Image height after crop **/
    MS_U32 nAvgBlkX;            /**< HW statistics average block number*/
    MS_U32 nAvgBlkY;            /**< HW statistics average block number*/
    MS_U32 nHistMaxY;           /**< HW histogram Max Y*/
    MS_U16 nHist[256*2];        /**< histogram */
    ISPAESample_t *tAvgs;       /**< HW statistics average block data*/
    IQDEBUG_t     *tIQDebug;    /**< IQ debug -> unit test*/
    IQDRCHistX_t  *tDRCHist;    /**< histogram type1 resolution(DRC)*/
    ISP_HDR_STATS *pHdrStats;   /**< HDR statistic */
    MS_BOOL        nMultiLS_CaliCCMUpdate;  /**< Color calibration CCM update flag for multi-lightsource*/
    MS_U16         nMultiLS_CaliCCM[9];     /**< Color calibration CCM for multi-lightsource*/
	MS_U32 AeHdr_Num_BV[17];
}IqInput_t;


/*! @brief IQ algorithm entry
    @param[in] handle IQ Algorithm private data
    @param[in] IQ HW statistics
    @param[out] pOutput IQ algorithm result.
    @retval SUCCESS or FAIL if error occurs.
*/
MS_S32 DoIq(IqCfgHandle pHandle);//, IqInput_t *pInput, IspRegShd_t *pRegShd);
MS_S32 DoIqPerFrame(IqCfgHandle pHandle); //for IP which has to update per frame ex WDR_LOC


/*! @brief IQ library initialization
    @param[in] CfgHandle IQ data handle
    @retval SUCCESS or FAIL if error occurs.
*/
IqCfgHandle IqInit(IqInput_t *pInput, IspRegShd_t *pRegShd, ISP_DBGBUF_HANDLE pDbgBuf);

/*! @brief IQ resources that allocated at IQInit
    @param[in] IQ data handle
    @retval SUCCESS or FAIL if error occurs.
*/
MS_S32 IqRelease(IqCfgHandle Handle);

#endif
