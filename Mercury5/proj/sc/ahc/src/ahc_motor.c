//==============================================================================
//
//  File        : AHC_Motor.c
//  Description : AHC Motor control function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================
#if 0 //Andy Liu TBD    
/*===========================================================================
 * Include files
 *===========================================================================*/ 

//#include "ahc_general.h"
#include "ahc_sensor.h"
#include "ahc_common.h"
#include "ahc_motor.h"
#include "ait_config.h"
#include "Isp_if.h"
#include "ahc_os.h"
#include "MotorCtrlTask.h"
#include "Mmp_media_def.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define ZOOM_IDX_OFFSET    24
#define FOCUS_IDX_OFFSET   60

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

AHC_SENSOR_OPT_ZOOM_INDEX  CurrStepIdx = 0;
AHC_SENSOR_OPT_ZOOM_INDEX  LastStepIdx = 0;

UINT16 ZoomStepMappingLut[OPT_ZOOM_MAX] = 
     {0, 152, 281, 375, 454, 517, 576, 670, 742, 807, 864, 900 };

UINT16 FocusStepMappingLut[OPT_ZOOM_MAX] = 
#if 1  // Focus in 2M 
     {5, 153, 270, 357, 425, 473, 507, 531, 510, 443, 330, 224 };
#endif
#if 0 // Focus in Infinite.
     {0, 146, 260, 343, 407, 450, 478, 491, 455, 370, 235, 112 };
#endif

/*===========================================================================
 * Extern varible
 *===========================================================================*/ 

extern AHC_OS_FLAGID  MotorCtrlFlag;

/*===========================================================================
 * Main body
 *===========================================================================*/ 

UINT8 AHC_SearchMappingTableIdx(INT16 bySteps)
{
    UINT8 i = 0;

    for(i=0; i < OPT_ZOOM_MAX - 1; i++)
    {
        if(  bySteps >= (ZoomStepMappingLut[i]+ZOOM_IDX_OFFSET)  &&
			 bySteps < (ZoomStepMappingLut[i+1]+ZOOM_IDX_OFFSET) )
            break;
	}
    return i;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetOpticalZoomStatus
//  Description :
//------------------------------------------------------------------------------
/**  For MT9P001
 @brief This API get Optical Zoom Status

 This function get status of Optocal Zoom-In / Zoom-Out. Currently, the zoom can 
 only based on center of scene.
 
 Parameters:
 @param[out] *pwStatus Get Zoom status result.
 
 @retval AHC_TRUE Success.
*/

AHC_BOOL AHC_GetOptocalZoomStatus( UINT8 *pwStatus )
{
    UINT8   ZoomStatus = 0;
    UINT32  CurSysMode;

    AHC_GetSystemStatus(&CurSysMode);
    
    CurSysMode >>= 16;
    
    if ( (CurSysMode != AHC_MODE_CAPTURE_PREVIEW) && 
         (CurSysMode != AHC_MODE_RECORD_PREVIEW ) && 
         (CurSysMode != AHC_MODE_VIDEO_RECORD   )  ) {
        return AHC_FALSE;
    }

    ZoomStatus = FuncMotorCtrl_ZoomReady();

    if ( MT_STATE_IDLE == ZoomStatus )
    {
        *pwStatus = OPT_ZOOM_IDLE;
    }
    else
    {
        *pwStatus = OPT_ZOOM_BUSY;
    }
    
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetOptocalZoom
//  Description :
//------------------------------------------------------------------------------
/**  For MT9P001
 @brief This API set Optical Zoom-In / Zoom-Out

 This function set Optocal Zoom-In / Zoom-Out. Currently, the zoom can  
 only based on center of scene.
 
 Parameters:
 
 @param[in] byDirection     Zoom-In or Zoom Out
 
 @retval AHC_TRUE Success.
*/

AHC_BOOL AHC_SetOptocalZoom(AHC_ZOOM_DIRECTION byDirection)
{
    UINT32  CurSysMode;

    AHC_GetSystemStatus(&CurSysMode);
    
    CurSysMode >>= 16;
    
    if ( (CurSysMode != AHC_MODE_CAPTURE_PREVIEW) && 
         (CurSysMode != AHC_MODE_RECORD_PREVIEW ) && 
         (CurSysMode != AHC_MODE_VIDEO_RECORD   ) ) {
        return AHC_FALSE;
    }

    // If the home position is not found, return false.
    if( !FuncMotorCtrl_ZoomHomeFound() )
    {
        return AHC_FALSE;
    }

    FuncMotorCtrl_ZoomStart(byDirection);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetOptocalZoomPos
//  Description :
//------------------------------------------------------------------------------
/**  For MT9P001
 @brief This API set Optical Zoom Position

 This function set Optocal Zoom accurate position. Currently, the zoom can 
 only based on center of scene.
 
 Parameters:
 
 @param[in] usPosIndex     Zoom position Index (0 ~ 125)
 
 @retval AHC_TRUE Success.
*/

AHC_BOOL AHC_SetOptocalZoomPos(UINT16 usPosIndex)
{
    UINT32  CurSysMode;

    AHC_GetSystemStatus(&CurSysMode);
    
    CurSysMode >>= 16;
    
    if ( (CurSysMode != AHC_MODE_CAPTURE_PREVIEW) && 
         (CurSysMode != AHC_MODE_RECORD_PREVIEW ) && 
         (CurSysMode != AHC_MODE_VIDEO_RECORD   )  ) {
        return AHC_FALSE;
    }

    // If the home position is not found, return false.
    if( !FuncMotorCtrl_ZoomHomeFound() )
    {
        return AHC_FALSE;
    }

    FuncMotorCtrl_ZoomSetPosition( usPosIndex );

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetOptocalZoomStop
//  Description :
//------------------------------------------------------------------------------
/**  For MT9P001
 @brief This API set Optical Zoom-In / Zoom-Out

 This function set Optocal Zoom-In / Zoom-Out. Currently, the zoom can 
only based on center of scene.
 
 Parameters:
 
 @param[in] 
 
 @retval AHC_TRUE Success.
*/

AHC_BOOL AHC_SetOptocalZoomStop(void)
{
    UINT32  CurSysMode;

    AHC_GetSystemStatus(&CurSysMode);
    
    CurSysMode >>= 16;
    
    if ( (CurSysMode != AHC_MODE_CAPTURE_PREVIEW) && 
         (CurSysMode != AHC_MODE_RECORD_PREVIEW ) && 
         (CurSysMode != AHC_MODE_VIDEO_RECORD   ) ) {
        return AHC_FALSE;
    }

    FuncMotorCtrl_ZoomStop();

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetOptocalZoomPos
//  Description :
//------------------------------------------------------------------------------
/**  For MT9P001
 @brief This API return Optical Zoom Position

 This function return the Optocal Zoom Postion. 
 
 Parameters:
 
 @param[out] usPosIndex     Current Zoom position Index (0 ~ 125)
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetOptocalZoomPos(UINT16 *usPosIndex)
{
    UINT32  CurSysMode;
    
    AHC_GetSystemStatus(&CurSysMode);
    
    CurSysMode >>= 16;
    
    if ( (CurSysMode != AHC_MODE_CAPTURE_PREVIEW) && 
         (CurSysMode != AHC_MODE_RECORD_PREVIEW ) && 
         (CurSysMode != AHC_MODE_VIDEO_RECORD   )  ) 
    {
        return AHC_FALSE;
    }

    *usPosIndex = FuncMotorCtrl_ZoomCurrentIndex();

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetAutoFocus
//  Description :
//------------------------------------------------------------------------------
/**  For MT9P001
 @brief This API set Focus Range

 This function set Focus Position.
 
 Parameters: Focus postion
 
 @param[in] Focus Step
 
 @retval AHC_TRUE Success.
*/

AHC_BOOL AHC_SetFocusPos()
{
    UINT32  CurSysMode;
    //UINT8   preOp, tarOp;

    AHC_GetSystemStatus(&CurSysMode);
    
    CurSysMode >>= 16;
    
    if ( (CurSysMode != AHC_MODE_CAPTURE_PREVIEW) && 
         (CurSysMode != AHC_MODE_RECORD_PREVIEW ) && 
         (CurSysMode != AHC_MODE_VIDEO_RECORD   ) ) {
        return AHC_FALSE;
    }
    
    #if 0 //Rogers:***
	preOp = ISP_IF_AF_GetSillAFOperation();

	if( preOp ==  ISP_AF_OPERATION_NOREQ )
	{
		tarOp = ISP_AF_OPERATION_START;
	}
	else
	{
		tarOp = ISP_AF_OPERATION_CANCEL;
	}

	ISP_IF_AF_SetSillAFOperation(tarOp);
    #endif
    
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetFocusPos
//  Description :
//------------------------------------------------------------------------------
/**  For MT9P001
 @brief This API Get Focus Range

 This function Get Focus Position.
 
 Parameters: Focus postion
 
 @param[in] Focus Step
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetFocusPos(UINT8 *bySteps)
{
    UINT32  CurSysMode;

    AHC_GetSystemStatus(&CurSysMode);
    
    CurSysMode >>= 16;
    
    if ( (CurSysMode != AHC_MODE_CAPTURE_PREVIEW) && 
         (CurSysMode != AHC_MODE_RECORD_PREVIEW ) && 
         (CurSysMode != AHC_MODE_VIDEO_RECORD   ) ) {
        return AHC_FALSE;
    }

    *bySteps = FocusStepMappingLut[CurrStepIdx] + FOCUS_IDX_OFFSET;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_MotorParking
//  Description :
//------------------------------------------------------------------------------
/** 
 @brief This API parks the zoom and focus motors around their home positions.

 This API parks the zoom and focus motors around their home positions.
 
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_MotorParking(UINT uiArg)
{
    
#if(  BIND_MOTOR_DUMMY == 0 )
    if( !MotorCtrl_ZoomParking() )
    {
        printc("Zoom parking is failed!\n");
        return AHC_FALSE;
    }

    if( !MotorCtrl_FocusParking() )
    {
        printc("Focus parking is failed!\n");
        return AHC_FALSE;
    }
#else
	//NOP
#endif
    return AHC_TRUE;
}
#else
typedef int dummy_ahc_motor;
#endif
