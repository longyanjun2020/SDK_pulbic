#ifndef __DRIVING_SAFETY_H__
#define __DRIVING_SAFETY_H__

/*===========================================================================
 * Include file
 *===========================================================================*/

#include "AHC_Config_SDK.h"
#include "mmp_lib.h"
#include "ldws.h"
#include "mmpf_adas_ctl.h"
#include "ldws_cfg.h"
#include "ahc_menu.h"
#include "adas.h"

/*===========================================================================
 * Global variable
 *===========================================================================*/


/*===========================================================================
 * Macro define
 *===========================================================================*/

#define FATIGUEALERT_HR 3600

/*===========================================================================
 * Enum define
 *===========================================================================*/


/*===========================================================================
 * Structure define
 *===========================================================================*/


/*===========================================================================
 * Extern varible
 *===========================================================================*/


/*===========================================================================
 * Function prototype
 *===========================================================================*/

/* Remind Headlight */
#if (DRIVING_SAFETY_REMIND_HEADLIGHT)
#if (ENABLE_SHOWING_EXPOSURE_VALUE)
MMP_ULONG   Driving_Safety_GetAvgLux(void);
#endif
MMP_BOOL    Driving_Safety_IsRemindHeadlightNotify(void);
void 		Driving_Safety_IsRemindHeadlightProcDoneNotify(MMP_BOOL bEnable);
void        Driving_Safety_RemindHeadlightEnable(MMP_BOOL bEnable);
MMP_BOOL    Driving_Safety_Calculate_RemindHeadlight(MMP_BYTE Oprt, MMP_ULONG *GetAvgLux);
MMP_BOOL    Driving_Safety_RemindHeadlightCheck(void);
#endif

/* Eco Drive */
#if (defined(DRIVING_SAFETY_ECODRIVE) && DRIVING_SAFETY_ECODRIVE == 1)
MMP_BOOL    Driving_Safety_EcoDrive(void);
MMP_LONG    Driving_Safety_CheckEcoDriveLevel(void);
#endif

/* LDWS */
#if (ENABLE_ADAS_LDWS)
#if 1 // integrated and modified from Dvr_CarDV_MIO, TBD
void LDWS_Callback(const void * pADAS_Param, ADAS_CALL_BK_TYPE type);
#else
void LDWS_Callback(const ldws_params_t*);
#endif
MMP_BOOL LDWS_IsStart(void);
void LDWS_GetResult(ldws_params_t*);
void LDWS_Lock(void);
void LDWS_Unlock(void);
#endif

#endif // #ifndef __DRIVING_SAFETY_H__
