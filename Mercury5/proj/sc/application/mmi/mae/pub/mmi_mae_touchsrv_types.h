/**
* @file mmi_mae_touchsrv_types.h
* @version $Id: mmi_mae_touchsrv_types.h 1533 2009-08-05 08:41:01Z steve.lee $
*
* @brief This header file defines the data types of ITouchSrv
*/

#ifndef __MMI_MAE_TOUCHSRV_TYPES_H__
#define __MMI_MAE_TOUCHSRV_TYPES_H__
#include "mmi_mae_common_def.h"

/**
* Finger command id
*/
#define MAETSCMDMASK(v)	        (1<<(v))
#define MAE_TS_MAX_TOUCH        (2)

#define MAE_TS_1PNT_MAX_HOOK       (3)
//Plus multi-touch macro
#define TOUCHSRV_INVALID_UNIQUEID (0xff)
#define TOUCHSRV_UNHOOKALL (TOUCHSRV_INVALID_UNIQUEID-1)
#define TOUCHSRV_FOR_SINGLEUNHOOK (TOUCHSRV_INVALID_UNIQUEID-2)


enum MAETsCmdId_e_
{
    MAE_TS_CMD_ID_NONE = 0,
    MAE_TS_CMD_ID_UP = MAETSCMDMASK(0),
    MAE_TS_CMD_ID_DOWN = MAETSCMDMASK(1),
    MAE_TS_CMD_ID_LEFT = MAETSCMDMASK(2),
    MAE_TS_CMD_ID_RIGHT = MAETSCMDMASK(3),
    MAE_TS_CMD_ID_CLICK = MAETSCMDMASK(4),
    MAE_TS_CMD_ID_DBL_CLICK = MAETSCMDMASK(5),
    MAE_TS_CMD_ID_LONG_PRESS = MAETSCMDMASK(6),
    MAE_TS_CMD_ID_ALL = (s32)0xFFFFFFFF
};


/** 
* @brief    This is defined for Multi-touch use.        
*/

struct MultiTouchData_t_
{
    s32 PosX;
    s32 PosY;
    u8  nPointId;
};

/**
* Structure for calibration
*/
typedef struct 
{
	s32 x;
	s32 y;
}MAE_TS_Point_t;

struct MAE_TS_Calibration_t_
{
	MAE_TS_Point_t tExpLeftTopPoint;    ///< the expected left-top point on screen
	MAE_TS_Point_t tUsrLeftTopPoint;    ///< the real left-top point that user pointed.
	MAE_TS_Point_t tExpRightBtmPoint;   ///< the expected right-bottom point on screen
	MAE_TS_Point_t tUsrRightBtmPoint;   ///< the real right-bottom point that user pointed.
#ifdef __MULTI_TOUCH_SLIM__
    MAE_TS_Point_t tResistance;   ///< the expected right-bottom point on screen
#endif
};

struct MAE_TS_Rect_t_
{
	s32 x;
	s32 y;
	s32 w;
	s32 h;
};

typedef struct
{
    u8 nFingerNum;
    u8 nUpdateIdx;
    struct MultiTouchData_t_ tPoint[MAE_TS_MAX_TOUCH];
} MAE_TS_MultiTouchInfo_t;

typedef struct  
{
    MAE_EventId nEvtId;
    void*pRegData;
    MAE_TS_MultiTouchInfo_t tSendingDataMT;
}MAE_TS_MultiTouchMeta_t;


/**
* Define the enum for coordinate mode.
* Now support four direction.
*/
enum MAETouchCoorMode_e_
{
    MAE_TS_DISP_COOR_NORMAL = 0,
    MAE_TS_DISP_COOR_90CW,
    MAE_TS_DISP_COOR_180CW,
    MAE_TS_DISP_COOR_270CW,
    MAE_TS_DISP_COOR_END
};

/**
 * @brief The enumeration defines the touch screen type.
 */
opaque_enum(MAETscrType_e_)
{
    MAE_TS_R_TYPE,      /**< Resistance type of touch screen */
    MAE_TS_C_TYPE,      /**< Capacitance type of touch screen */
    MAE_TS_UNKNOWN_TYPE /**< Unknown type of touch screen */
};

#endif /*__MMI_MAE_TOUCHSRV_TYPESH__*/

