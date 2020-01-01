//------------------------------------------------------------------------------
//
//  File        : ldws_cfg.h
//  Description : Header file of LDWS configuration
//  Author      : SunnyChang
//  Revision    : 0.0
//
//------------------------------------------------------------------------------
#ifndef _LDWS_CFG_H_
#define _LDWS_CFG_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "ldws.h"
#include "mmpf_adas_ctl.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================
#ifndef LDWS_CALIBRATION_FILENAME
#define LDWS_CALIBRATION_FILENAME           "SF:1:\\LDWS_Calibration.bin"
#endif

#ifndef LDWS_CALIBRATION_UPDATE_FILENAME
#define LDWS_CALIBRATION_UPDATE_FILENAME    "SD:\\LDWS_Calibration_Update.bin"
#endif

#ifndef LDWS_CALIBRATION_UPDATE_FILENAME2
#define LDWS_CALIBRATION_UPDATE_FILENAME2   "SD:\\LDWS_Calibration_Update.bak"
#endif

#ifndef LDWS_CALIBRATION_BACKUP_FILENAME
#define LDWS_CALIBRATION_BACKUP_FILENAME    "SD:\\LDWS_Calibration_Backup.bin"
#endif

#ifndef LDWS_CALIBRATION_DEFAULT_FILENAME
#define LDWS_CALIBRATION_DEFAULT_FILENAME   "SF:1:\\LDWS_Calibration_Default.bin"
#endif

#ifndef FCWS_CALIBRATION_FILENAME		//temp
#define FCWS_CALIBRATION_FILENAME           "SF:1:\\FCWS_Calibration.bin"
#endif

#ifndef LDWS_SETUP_POS_OFFSET
#define LDWS_SETUP_POS_OFFSET               (0)
#endif

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
//#define BACKUP_LDWS_CALIBRATION_FILE

/* Width of source image */
#define LDWS_WIDTH              (432)//		// For 16:9 video resolution
/* Heigth of source image */
#define LDWS_HEIGHT             (240)//
/* The gap of every two frames to do LDWS */
#define LDWS_FRAME_GAP          (0)//(5)
/* Color format of source image */
#define LDWS_COLOR_Y            (1)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct {
    unsigned int width;     // Width of source image
    unsigned int height;    // Height of source image
} LDWS_RESOL;

typedef struct _user_ldws_tuning_params {
	unsigned short laneCalibrationImageWidth;
	unsigned short laneCalibrationImageHeight;
	unsigned short laneCalibrationUpPointY;
	unsigned short laneCalibrationDownPointY;
} user_ldws_tuning_params;

typedef struct  {
	unsigned short cardv_height_pos;
	unsigned short CalibrationStarY;
	unsigned short CalibrationEndY;
} fcws_tuning_params;

typedef enum _Adas_ldws_warning_mode{
  ADAS_WARNING_MODE_WAIT = 0,
  ADAS_WARNING_MODE_NO_WAIT
} Adas_ldws_warning_mode;
//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern unsigned char        gubLdwsFrameGap;
extern LDWS_RESOL           gstLdwsResol;
extern ldws_tuning_params   ldwsTuningParms;

void        LDWS_CalibrationParamReset(void);
void        LDWS_CalibrationParam_Convert(ldws_tuning_params menu_ldws_tuning_params);
MMP_ERR     LDWS_CalibrationParam_Save(void);
MMP_ERR     LDWS_CalibrationParam_Backup(void);
MMP_ERR     LDWS_CalibrationParam_Read(void);
MMP_ERR     LDWS_CalibrationParam_UserUpdate(void);
MMP_BOOL    LDWS_SettingChanged(void);
MMP_ERR 	LDWS_CalibrationParam_UserUpdate(void);
void LDWS_SetChanged(MMP_BOOL changed);
#endif // _LDWS_CFG_H_

