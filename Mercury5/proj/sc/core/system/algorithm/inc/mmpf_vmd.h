//==============================================================================
//
//  File        : mmpf_vmd.h
//  Description : INCLUDE File for the Video Motion Detection Function
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_VMD_H_
#define _MMPF_VMD_H_

#include "includes_fw.h"
#include "mi_md.h"

#if (CPU_ID == CPU_A)
#include "mmpf_fdtc.h"
#endif
#if (CPU_ID == CPU_B)
#include "mmpf_score.h"
#endif
#if (MDTC_ON_SCORE)
#include "mmp_multicore_inc.h"
#endif

/** @addtogroup MMPF_VMD
@{
*/
#if ((DSC_R_EN)||(VIDEO_R_EN))&&(SUPPORT_MDTC)

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#if (MDTC_ON_SCORE)
#define VMD_SEND_CMD_TO         (50) ///< 50ms as sending command timeout
#define VMD_BUFINFO_CMD_TO      (100) ///< timeout for MD_get_buffer_info()
#define VMD_INIT_CMD_TO         (200) ///< timeout for MD_init()
#define VMD_SET_WIN_CMD_TO      (100) ///< timeout for MD_set_detect_window()
#define VMD_SET_PARAM_CMD_TO    (100) ///< timeout for MD_set_window_params_in()
#define VMD_SET_TIME_CMD_TO     (100) ///< timeout for MD_set_time_ms()
#define VMD_RUN_CMD_TO          (200) ///< timeout for MD_run()
#define VMD_GET_RESULT_CMD_TO   (100) ///< timeout for MD_get_window_params_out()
#endif

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

#if (CPU_ID == CPU_A)
typedef enum _MMPF_VMD_STATE {
    MMPF_VMD_IDLE_STATE = 0,        ///< VMD is in idle state
    MMPF_VMD_ACTIVE_STATE,          ///< VMD is initialized & enabled
    MMPF_VMD_WAIT_FRAME_STATE,      ///< VMD is waiting for Luma frame
    MMPF_VMD_FRAME_READY_STATE,     ///< Luma frame is ready
    MMPF_VMD_OPERATING_STATE        ///< VMD is under processing
} MMPF_VMD_STATE;
#endif

#if (MDTC_ON_SCORE)
/*
 * Request commands
 */
typedef enum _MMPF_VMD_CMD {
    MMPF_VMD_CMD_GET_BUF_INFO = 0,
    MMPF_VMD_CMD_INIT,
    MMPF_VMD_CMD_RUN,
    MMPF_VMD_CMD_SET_WIN,
    MMPF_VMD_CMD_SET_WIN_PARAM_IN,
    MMPF_VMD_CMD_GET_WIN_PARAM_OUT,
    MMPF_VMD_CMD_SET_TIME
} MMPF_VMD_CMD;
#endif

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

#if (CPU_ID == CPU_A)
typedef struct _MMPF_VMD_ATTRIBUTE {
    MMP_ULONG   ulWorkBuf;          ///< the addr of working buffer
    MMP_ULONG   ulWorkBufSize;      ///< the size of working buffer
	MMP_USHORT  usInputW;           ///< the width of input frame to do motion detection
	MMP_USHORT  usInputH;           ///< the height of input frame to do motion detection
    MMP_ULONG   ulInputLumaAddr;    ///< the buf addr to store the luma data
    MMP_ULONG   ulInputLumaSize;    ///< the size of luma data
    MMP_UBYTE   ubFrameGap;         ///< the gap (frame count) of the two frames for calculation
    MMP_ULONG   ulGapTimeMs;        ///< the gap time in unit of ms
} MMPF_VMD_ATTRIBUTE;
#endif

#if (MDTC_ON_SCORE)
/*
 * Request Parameters according to the specified command
 */
typedef struct _MMPF_VMD_REQ {
    /* Inheritance from class DUALCORE_REQ_OBJ */
    DUALCORE_REQ_OBJ    req;

    /* NOTE:
     * The total size of the following elements should under 28 bytes.
     * Please refer to MAX_REQ_PARAM_SIZE for more information.
     */
    MMP_ULONG           cmd;    // @refer MMPF_VMD_CMD
    union {
        /* refer MD_get_buffer_info() */
        struct {
            MMP_USHORT  width;
            MMP_USHORT  height;
            MMP_UBYTE   color;
            MMP_UBYTE   w_div;
            MMP_UBYTE   h_div;
        } buf_info;

        /* refer MD_init() */
        struct {
            MMP_UBYTE   *workbuf;
            MMP_ULONG   workbuf_len;
            MMP_USHORT  width;
            MMP_USHORT  height;
            MMP_UBYTE   color;
        } init;

        /* refer MD_run() */
        struct {
            MMP_UBYTE   *frame;
            MMP_ULONG   frame_size;
        } run;

        /* refer MD_set_detect_window() */
        struct {
            MMP_USHORT  lt_x;
            MMP_USHORT  lt_y;
            MMP_USHORT  rb_x;
            MMP_USHORT  rb_y;
            MMP_UBYTE   w_div;
            MMP_UBYTE   h_div;
        } set_win;

        /* refer MD_set_window_params_in() */
        struct {
            MMP_UBYTE   w_num;
            MMP_UBYTE   h_num;
            MD_params_in_t param;
        } set_win_param_in;

        /* refer MD_get_window_params_out() */
        struct {
            MMP_UBYTE   w_num;
            MMP_UBYTE   h_num;
        } get_win_param_out;

        /* refer MD_set_time_ms() */
        struct {
            MMP_ULONG   diff_ms;
        } set_time;
    } param;
} MMPF_VMD_REQ;

/*
 * Response results according for the specified command
 */
typedef struct _MMPF_VMD_RESP {
    /* Inheritance from class DUALCORE_RESP_OBJ */
    DUALCORE_RESP_OBJ   resp;

    /* NOTE:
     * The total size of the following elements should under 28 bytes.
     * Please refer to MAX_RESP_PARAM_SIZE for more information.
     */
    MMP_ULONG           err_code;

    union {
        /* refer MD_get_buffer_info() */
        struct {
            MMP_ULONG   buf_size;
        } buf_info;

        /* refer MD_get_window_params_out() */
        struct {
            MD_params_out_t param;
        } get_win_param_out;
    } result;
} MMPF_VMD_RESP;

#endif //(MDTC_ON_SCORE)

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

typedef void MMPF_VMD_Callback(void);

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

#if (CPU_ID == CPU_A)
MMP_ERR     MMPF_VMD_ProcessCmd(void);
MMP_BOOL    MMPF_VMD_IsEnable(void);
MMP_UBYTE   MMPF_VMD_GetFrameGapConfig(void);
void        MMPF_VMD_UpdateInputLumaAddr(MMP_ULONG ulSrcLumaAddr);
MMP_ERR     MMPF_VMD_Operate(void);
MMPF_VMD_STATE MMPF_VMD_GetState(void);
#endif

#if (CPU_ID == CPU_B)
void        MMPF_VMD_ProcRequest(DUALCORE_REQ *req, DUALCORE_RESP *resp);
#endif

#endif // ((DSC_R_EN)||(VIDEO_R_EN))&&(SUPPORT_MDTC)
#endif // _MMPF_VMD_H_
/// @}
