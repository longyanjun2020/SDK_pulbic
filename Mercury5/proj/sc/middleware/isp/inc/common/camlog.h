/*
 * camlog.h
 *
 *  Created on: Nov 16, 2015
 *      Author: edward00.yang
 */
#ifndef __camlog__
#define __camlog__

//#include "cutils/properties.h"
//#include "cutils/log.h"
//#include <drv_ms_isp_hal.h>

void init_isp_log();
void uninit_isp_log();
int property_get_int(char *name,int def);
int property_set_int(char *name,int val);

//[Daniel]
//void init_global_info(isp_hal_handle_t  *pIspHalHandle);
void update_global_info();
void uninit_global_info();
u64 get_global_fcount();
void print_kmsg(const char* txt);	//print timestamp and message into kernel dmesg buffer

extern FILE *g_log_fd; /**< Global log output file.*/
extern int g_log_level;

/** @brief output log*/
#define PRINT_LOG(...) do{\
        if(g_log_fd)\
        {\
            fprintf(g_log_fd, __VA_ARGS__);\
            fflush(g_log_fd);\
        }else\
            fprintf(stdout, __VA_ARGS__); }while(0)

#define USING_ALOG  (0) // logcat
#if !USING_ALOG
#ifndef LOGE
#define LOGE(...) PRINT_LOG(__VA_ARGS__)
#endif

#ifndef LOGD
#define LOGD(...) PRINT_LOG(__VA_ARGS__)
#endif

#ifndef LOGV
#define LOGV(...) PRINT_LOG(__VA_ARGS__)
#endif

#ifndef MSG
#define MSG(...) PRINT_LOG(__VA_ARGS__)
#endif

#else
#undef LOGE
#define LOGE ALOGE
#undef LOGD
#define LOGD ALOGD
#undef LOGV
#define LOGV ALOGV

#undef MSG
#define MSG(...) PRINT_LOG(__VA_ARGS__)

#endif // WIN32


//isp properties

#define IQ_DEBUG_OBA "iq.debug.oba" /**< property description */
#define IQ_DEBUG_R0 "iq.debug.r0"   /**< property description */
#define IQ_DEBUG_R1 "iq.debug.r0"   /**< property description */
#define IQ_DEBUG_R2 "iq.debug.r0"   /**< property description */
#define IQ_DEBUG_R3 "iq.debug.r0"   /**< property description */
#define IQ_DEBUG_R4 "iq.debug.r0"   /**< property description */
#define IQ_DEBUG_R5 "iq.debug.r0"   /**< property description */
#define IQ_DEBUG_R6 "iq.debug.r0"   /**< property description */
#define IQ_DEBUG_R7 "iq.debug.r0"   /**< property description */
#define IQ_DEBUG_R8 "iq.debug.r0"   /**< property description */

#define AE_DEBUG_ENABLE_AE          "ae.debug.ae_enable"        /**< Enable/Disable AE */
#define AE_DEBUG_LEVEL              "ae.debug.level"            /**< 0: disable, 1: Exposure 2: Algo parameters 4: Algo statistics 32: API debug */
#define AE_DEBUG_SIMPLEY            "ae.debug.simpley"          /**< Replace weighted Y with average Y */
#define AE_DEBUG_BL_ENABLE          "ae.debug.bl.enable"        /**< Enable Back-Light compensation*/
#define AE_DEBUG_COE_ENABLE         "ae.debug.coe.enable"       /**< Enable Center Over-Exposure suppression*/
#define AE_DEBUG_SWITCH_TEST        "ae.debug.switch_test"      /**< Change only one of exposure value to test effective cycle */
#define AE_DEBUG_FIX_TARGET         "ae.debug.fix_target"       /**< Use CFG target, not changed by scene */
#define AE_DEBUG_MANUAL_SCENE       "ae.debug.scene"            /**< Set scene */
#define AE_DEBUG_MANUAL_HISTTYPE    "ae.debug.hist"             /**< Set histogram type */
#define AE_DEBUG_SWITCH_TEST_USEC   "ae.debug.switch_test_usec"
#define AE_DEBUG_SWITCH_TEST_AGAIN  "ae.debug.switch_test_again"
#define AE_DEBUG_SWITCH_TEST_DGAIN  "ae.debug.switch_test_dgain"
#define AE_DEBUG_FORCE_AUTO_STR     "ae.debug.force_auto_str"
#define AE_DEBUG_FORCE_AUTO_SNTY    "ae.debug.force_auto_snty"
#define AE_DEBUG_IR_IDX_ENABLE      "ae.debug.IRIdx.enable"     // 0: set IR index to zero.
#define AE_DEBUG_IR_INFO_SHOW       "ae.debug.IRInfo.show"      // IR related log..
#define AE_DEBUG_IR_TOP_LIMIT       "ae.debug.IRTop.limit"      //modified the IRTop limit
#define AE_DEBUG_IR_RGB_TOP_LIMIT   "ae.debug.IR_RGBTop.limit"  //modified the IRTop limit

#define AWB_DEBUG_AWB_ENABLE        "awb.debug.awb_enable"      /**< Enable/Disable AWB */
#define AWB_DEBUG_LEVEL             "awb.debug.level"           /**< AWB Debug Mode: 1:show simple algo paramaters 2:always show detail algo parameters 3:show detail algo parameters 7:User Paramters*/
#define AWB_DEBUG_MWB_ENABLE        "awb.debug.mwb_enable"      /**< Enable/Disable Manual WB, must disable AWB first */
#define AWB_DEBUG_MWB_RGAIN         "awb.debug.mwb_rgain"       /**< Setting Manual WB Rgain, default:1024 */
#define AWB_DEBUG_MWB_BGAIN         "awb.debug.mwb_bgain"       /**< Setting Manual WB Bgain, default:1024 */
#define AWB_DEBUG_PREFER_ENABLE     "awb.debug.prefer.enable"   /**< Enable/Disable AWB prefer gain */
#define AWB_DEBUG_PREFER_RGSTHR     "awb.debug.prefer.rgstrh"   /**< Prefer RG ratio, default:128, no change */
#define AWB_DEBUG_PREFER_BGSTHR     "awb.debug.prefer.bgstrh"   /**< Prefer BG ratio, default:128, no change */
#define AWB_DEBUG_TEST_API          "awb.debug.test.api"        /**< Internal test only, for testing AWB api */
#define AWB_DEBUG_INTERVAL_COUNT    "awb.debug.interval_count"

#define IQ_DEBUG_FEATURE_LEVEL      "iq.debug.feature_lv"
#define IQ_DEBUG_DEFOG_ENABLE       "iq.debug.defog_enable"
#define IQ_DEBUG_DEFOG_MODE         "iq.debug.defog_mode"
#define IQ_DEBUG_DEFOG_AUTO_LEVEL   "iq.debug.defog_auto_level"
#define IQ_DEBUG_DEFOG_MANUAL_LEVEL "iq.debug.defog_manual_level"
#define IQ_DEBUG_DRC_ENABLE         "iq.debug.drc_bEnable"
#define IQ_DEBUG_DRC_WHITE_LEVEL    "iq.debug.drc_u32WhiteLevel"
#define IQ_DEBUG_DRC_BLACK_LEVEL    "iq.debug.drc_u32BlackLevel"
#define IQ_DEBUG_DRC_ASYMMETRY      "iq.debug.drc_u32Asymmetry"
#define IQ_DEBUG_DRC_BRIGNT_ENHANCE "iq.debug.drc_u32BrigntEnhance"
#define IQ_DEBUG_DRC_EMODE          "iq.debug.drc_eMode"
#define IQ_DEBUG_DRC_MANUAL_LEVEL   "iq.debug.drc_u32ManualLevel"
#define IQ_DEBUG_DRC_AUTO_LEVEL     "iq.debug.drc_u32AutoLevel"
#define IQ_DEBUG_LOCWDR_TblShow     "iq.debug.LocalWDR_TblShow"
#define IQ_DEBUG_LOCWDR_TblSmooth   "iq.debug.LocalWDR_TblSmooth"
#define IQ_DEBUG_IRIDX_THRD_0       "iq.debug.IRIdx.thrd0"
#define IQ_DEBUG_IRIDX_THRD_1       "iq.debug.IRIdx.thrd1"
#define IQ_DEBUG_IRIDX_THRD_2       "iq.debug.IRIdx.thrd2"
#define IQ_DEBUG_IRIDX_THRD_3       "iq.debug.IRIdx.thrd3"
#define IQ_DEBUG_IRIDX_THRD_4       "iq.debug.IRIdx.thrd4"

#define IQ_DEBUG_NLM_MEMALLOC_EN    "iq.debug.nlm.memalloc_enable"
#define IQ_DEBUG_HIST_MEMALLOC_EN   "iq.debug.hist.memalloc_enable"

#define IQ_DEBUG_LEVEL              "iq.debug.level"            /**< enable show log of iq.debug.blkid */
#define IQ_DEBUG_BLKID              "iq.debug.blkid"            /**< show log for each IP */
#define IQ_DEBUG_PARALEV            "iq.debug.paralev"          /**< parameter level: SUB(0)/DBG(1)/HAL(2) */
#define IQ_DEBUG_INDSHOW            "iq.debug.indshow"          /**< show GainCheck result */
#define IQ_DEBUG_APIRESET           "iq.debug.apireset"         /**< reset all API setting of OFF */
#define IQ_DEBUG_APISHOW            "iq.debug.apishow"          /**< show debug message of API */
#define IQ_DEBUG_TBLSCAL            "iq.debug.tblscal"          /**< set table scale for debug show (def: 16, only work for 8, 4, 2, 1)*/
#define IQ_DEBUG_ENABLE_IQ          "iq.debug.iq_enable"        /**< Stop IQ update */
#define IQ_DEBUG_SETPROPEN          "iq.debug.setpropen"        /**< replace function by setprop (works by follow mark with $$) */
#define IQ_DEBUG_ISOFIX             "iq.debug.isofix"           /**< ($$)fix iso to present index */
#define IQ_DEBUG_ISOIND             "iq.debug.isoind"           /**< ($$)assign isoind under fix iso mode */
#define IQ_DEBUG_IQ_TRIGGER         "iq.debug.iq_trigger"       /**< ($$)Force Trigger IQ by mod and blkid */
#define IQ_DEBUG_IQ_TRIGMOD         "iq.debug.iq_trigmod"       /**< ($$)Force Trigger IQ by mod and blkid */
#define IQ_DEBUG_AUTOIQ             "iq.debug.autoiq"           /**< on/off autoiq (def:on) */
#define IQ_DEBUG_SKIPCFGVC          "iq.debug.skipcfgvc"        /**< skip cfg major version check */
#define IQ_DEBUG_SKIPML             "iq.debug.skipml"

#define ISP_DBG_ISP_CLK             "isp.dbg.isp.clk"           /**< Force ISP clock at 123/86/72/54 Mhz*/
#define ISP_DBG_OUTPUT_DEST         "isp.dbg.output.dest"       /**< Select isp debug message output destination. 0:Console , 1:Text file at /tmp/tmp/isp_log.log*/
#define ISP_RAW_GRAB_COUNT          "isp.raw.grab.count"        /**< Trigger raw dump N frames*/
#define ISP_DBG_AE_EN               "isp.dbg.ae.en"             /**< Force ISP AE enable*/
#define ISP_DBG_AWB_EN              "isp.dbg.awb.en"            /**< Force ISP AWB enable*/
#define ISP_DBG_IQ_EN               "isp.dbg.iq.en"             /**< Force ISP IQ enable*/
#define ISP_DBG_ALGO_EN             "isp.dbg.algo.en"           /**< Force ISP algo enable*/
#define ISP_DBG_SHUTTER             "isp.dbg.shutter"           /**< Force set shutter*/
#define ISP_DBG_FPS                 "isp.dbg.fps"               /**< Force set fps*/

#define ALGOMGR_DBG_FIXGAIN         "algomgr.debug.fixgain"

#define CALI_DEBUG_SDC_DUMP_RESULT          "cali.debug.sdc_dump_result"
#define CALI_DEBUG_SDC_DUMP_RAW_DATA        "cali.debug.sdc_dump_raw_data"
#define CALI_DEBUG_SDC_CALCULATE_TIME       "cali.debug.sdc_dump_cal_time"
#define CALI_DEBUG_SDC_DISP_MESSAGE         "cali.debug.sdc_disp_message"
#define CALI_DEBUG_SDC_DISP_HIST_STATIS     "cali.debug.sdc_disp_hist_statis"
#endif /* __camlog__ */
