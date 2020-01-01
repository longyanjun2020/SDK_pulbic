#if 0	//move to libcamera.h

/*! @file drv_cam_3a_if.h
      @brief This file contains Infinity ISP 3A interface for 3rd party algorithm
*/

/** @defgroup group1 ISP Customer 3A Interface
* @{
*/

/*
 * drv_cam_3a_if.h
 */

#ifndef DRV_CAM_3A_IF_H
#define DRV_CAM_3A_IF_H

#ifdef __cplusplus
extern "C"
{
#endif

/*! @brief API error code*/
enum CUS_3A_ERR_CODE
{
    CUS_3A_SUCCESS = 0,     /**< operation successful */
    CUS_3A_ERROR = -1,      /**< unspecified failure */
};

#define _3A_ROW    			(128)   /**< number of 3A statistic blocks in a row */
#define _3A_COL    			(90)    /**< number of 3A statistic blocks in a column */
#define _3A_HIST_BIN0    (40)    /**< histogram type0 resolution*/
#define _3A_HIST_BINX    (128)   /**< histogram type1 resolution*/

// AWB statistic , one sample
typedef struct
{
    u8  r;
    u8  g;
    u8  b;
}__attribute__((packed, aligned(1))) ISP_AWB_SAMPLE;

/*! @brief AWB HW statistics data*/
typedef struct
{
	ISP_AWB_SAMPLE data[_3A_ROW*_3A_COL];
}__attribute__((packed, aligned(1))) ISP_AWB_INFO;

/*! @brief AWB algorithm result*/
typedef struct isp_awb_result
{
    u32 Size;       /**< struct size*/
    bool Change;    /**< if true, apply this result to hw register*/
    u32 R_gain;     /**< AWB gain for R channel*/
    u32 G_gain;     /**< AWB gain for G channel*/
    u32 B_gain;     /**< AWB gain for B channel*/
    u32 ColorTmp;   /**< Return color temperature*/
}ISP_AWB_RESULT;

// AE statistics data
typedef struct
{
    u8  r;
    u8  g;
    u8  b;
    u8  y;
}__attribute__((packed, aligned(1))) ISP_AE_SAMPLE;

//Histogram
typedef struct {
      u16 r[_3A_HIST_BIN0];
      u16 g[_3A_HIST_BIN0];
      u16 b[_3A_HIST_BIN0];
}__attribute__((packed, aligned(1))) ISP_HIST0;

typedef struct {
    u16 u2HistY[_3A_HIST_BINX];
}__attribute__((packed, aligned(1))) ISP_HISTX;

/*! @brief ISP report to AE, hardware statistic */
typedef struct
{
    u32 Size;       /**< struct size*/
    ISP_HIST0  Hist0;   /**< HW statistic histogram 0*/
    ISP_HISTX  Hist1;   /**< HW statistic histogram 1*/
    ISP_HISTX  Hist2;   /**< HW statistic histogram 2*/
    ISP_AE_SAMPLE data[_3A_ROW*_3A_COL];
    u32 Shutter;                    /**< Current shutter in ns*/
    u32 SensorGain;                 /**< Current Sensor gain, 1X = 1024 */
    u32 IspGain;                    /**< Current ISP gain, 1X = 1024*/
}__attribute__((packed, aligned(1))) ISP_AE_INFO;

//AE algorithm result
/*! @brief ISP ae algorithm result*/
typedef struct
{
    u32 Size;       /**< struct size*/
    bool Change;    /**< if true, apply this result to hw register*/
    //u32 FNx10;           /**< F number * 10*/
    u32 Shutter;           /**< Shutter in ns */
    u32 SensorGain;        /**< Sensor gain, 1X = 1024 */
    u32 IspGain;           /**< ISP gain, 1X = 1024 */
    u32 u4BVx16384;        /**< Bv * 16384 in APEX system, EV = Av + Tv = Sv + Bv */
    u32 AvgY;              /**< frame brightness */
    //bool IsConverged;      /**< Report to ISP AE status is converged, Converged=1 otherwise=0. */
    //bool IsReachBoundary;  /**< AE report status reach boundary, Reach boundary=1 otherwise=0.*/
}__attribute__((packed, aligned(1))) ISP_AE_RESULT;


/*! @brief ISP initial status*/
typedef struct _isp_ae_init_param
{
    u32 Size;       /**< struct size*/
    char sensor_id[32];     /**< sensor module id*/
    u32 shutter;            /**< shutter Shutter in ns*/
    u32 shutter_step;       /**< shutter Shutter step ns*/
    u32 shutter_min;        /**< shutter Shutter min ns*/
    u32 shutter_max;        /**< shutter Shutter max ns*/
    u32 sensor_gain;        /**< sensor_gain Sensor gain, 1X = 1024*/
    u32 sensor_gain_max;    /**< sensor_gain_max Maximum Sensor gain, 1X = 1024*/
    u32 isp_gain;           /**< isp_gain Isp digital gain , 1X = 1024 */
    u32 isp_gain_max;       /**< isp_gain Maximum Isp digital gain , 1X = 1024 */
    u32 FNx10;              /**< F number * 10*/
    u32 fps;                /**< initial frame per second*/
}ISP_AE_INIT_PARAM;

typedef enum
{
    ISP_AE_FPS_SET, /**< ISP notify AE sensor FPS has changed*/
}ISP_AE_CTRL_CMD;

/**@brief ISP AE interface*/
typedef struct isp_ae_interface
{
    void *pdata; /**< Private data for AE algorithm.*/

    /** @brief AE algorithm init callback
    @param[in] pdata AE algorithm private data
    @param[in] init_state ISP initial status.
    @retval CUS_3A_SUCCESS or CUS_3A_ERROR if error occurs.
    @remark ISP call this function when AE algorithm initialize.
    */
    int (*init)(void* pdata,ISP_AE_INIT_PARAM *init_state);

    /** @brief AE algorithm close
    @param[in] pdata AE algorithm private data
    @remark ISP call this function when AE close.
    */
    void (*release)(void* pdata);

    /** @brief AE algorithm run
    @param[in] pdata AE algorithm private data
    @param[in] info ISP HW statistics
    @param[out] result AE algorithm return calculated result.
    @remark ISP call this function when AE close.
    */
    void (*run)(void* pdata,const ISP_AE_INFO *info,ISP_AE_RESULT *result);

    /** @brief AE algorithm control
    @param[in] pdata AE algorithm private data
    @param[in] cmd Control ID
    @param[in out] param Control parameter.
    @retval CUS_3A_SUCCESS or CUS_3A_ERROR if error occurs.
    @remark ISP call this function to change parameter
    */
    int (*ctrl)(void* pdata,ISP_AE_CTRL_CMD cmd,void* param);
}ISP_AE_INTERFACE;

/**@brief ISP user API to register 3rd party AE algorithm*/
int MS_ISP_AeLibRegInterface(ISP_AE_INTERFACE *ae);
//int MS_ISP_AeLibUnRegInterface();

typedef enum
{
    ISP_AWB_MODE_SET,
}ISP_AWB_CTRL_CMD;
/**@brief ISP AWB interface*/
typedef struct isp_awb_interface
{
    void *pdata; /**< Private data for AE algorithm.*/

    /** @brief AWB algorithm init callback
    @param[in] pdata Algorithm private data
    @retval CUS_3A_SUCCESS or CUS_3A_ERROR if error occurs.
    @remark ISP call this function when AE algorithm initialize.
    */
    int (*init)(void *pdata);

    /** @brief AWB algorithm close
    @param[in] pdata Algorithm private data
    @remark ISP call this function when AE close.
    */
    void (*release)(void *pdata);

    /** @brief AWB algorithm run
    @param[in] pdata Algorithm private data
    @param[in] info ISP HW statistics
    @param[out] result AWB algorithm return calculated result.
    @remark ISP call this function when AE close.
    */
    void (*run)(void *pdata,const ISP_AWB_INFO *awb_info,const ISP_AE_INFO *ae_info,ISP_AWB_RESULT *result);

    /** @brief AWB algorithm control
    @param[in] pdata Algorithm private data
    @param[in] cmd Control ID
    @param[in out] param Control parameter.
    @retval CUS_3A_SUCCESS or CUS_3A_ERROR if error occurs.
    @remark ISP call this function to change parameter
    */
    int (*ctrl)(void *pdata,ISP_AWB_CTRL_CMD cmd,void* param);
}ISP_AWB_INTERFACE;

/**@brief ISP user API to register 3rd party AWB algorithm*/
int MS_ISP_AwbLibRegInterface(ISP_AWB_INTERFACE *awb);

#ifdef __cplusplus
}//end of extern "C"
#endif

#endif
/** @} */ // end of ISP Customer 3A Interface

#endif
