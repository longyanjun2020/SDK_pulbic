
#ifndef _MENU_STATE_CAMERA_MENU_H_
#define _MENU_STATE_CAMERA_MENU_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_gui.h"

/*===========================================================================
 * Enum define 
 *===========================================================================*/ 

typedef enum {
    ITEMID_STILL_IMAGE_SIZE=1,
#if (MENU_STILL_SIZE_30M_EN)    
    ITEMID_IMAGE_SIZE_30M,
#endif
#if (MENU_STILL_SIZE_14M_EN)    
    ITEMID_IMAGE_SIZE_14M,
#endif
#if (MENU_STILL_SIZE_12M_EN)    
    ITEMID_IMAGE_SIZE_12M,
#endif
#if (MENU_STILL_SIZE_8M_EN)    
    ITEMID_IMAGE_SIZE_8M,
#endif
#if (MENU_STILL_SIZE_5M_EN)        
    ITEMID_IMAGE_SIZE_5M,
#endif
#if (MENU_STILL_SIZE_3M_EN)    
    ITEMID_IMAGE_SIZE_3M,
#endif
#if (MENU_STILL_SIZE_2M_WIDE_EN)    
    ITEMID_IMAGE_SIZE_2M,
#endif
#if (MENU_STILL_SIZE_1d2M_EN)    
    ITEMID_IMAGE_SIZE_1_2M,
#endif    
#if (MENU_STILL_SIZE_VGA_EN)
    ITEMID_IMAGE_SIZE_VGA,
#endif
    
    ITEMID_STILL_QUALITY,
#if (MENU_STILL_QUALITY_SUPER_FINE_EN)
    ITEMID_SQUALITY_SUPERFINE,
#endif
#if (MENU_STILL_QUALITY_FINE_EN)    
    ITEMID_SQUALITY_FINE,
#endif  
  
    ITEMID_STILL_STABLEILIZATION,
#if (MENU_STILL_STABILIZE_ON_EN)    
    ITEMID_STILL_STABLE_ON,
#endif
#if (MENU_STILL_STABILIZE_OFF_EN)    
    ITEMID_STILL_STABLE_OFF,
#endif
   
    ITEMID_FLASH,
#if (MENU_STILL_FLASH_AUTO_EN)    
    ITEMID_FLASH_AUTO,
#endif
#if (MENU_STILL_FLASH_SLOW_SYNC_EN)    
    ITEMID_FLASH_SLOW_SYNC,
#endif
#if (MENU_STILL_FLASH_ON_EN)    
    ITEMID_FLASH_ON,
#endif
#if (MENU_STILL_FLASH_OFF_EN)    
    ITEMID_FLASH_OFF,
#endif  
  
    ITEMID_FLASH_LEVEL,
#if (MENU_STILL_FLASH_LEVEL_HIGH_EN)    
    ITEMID_FLASH_LEVEL_HIGH,
#endif
#if (MENU_STILL_FLASH_LEVEL_NORMAL_EN)    
    ITEMID_FLASH_LEVEL_NORMAL,
#endif
#if (MENU_STILL_FLASH_LEVEL_LOW_EN)    
    ITEMID_FLASH_LEVEL_LOW,
#endif    

    ITEMID_REDEYE_REDUCTION,
#if (MENU_STILL_REDEYE_REDUCE_ON_EN)    
    ITEMID_REDEYE_REDUC_ON,
#endif
#if (MENU_STILL_REDEYE_REDUCE_OFF_EN)    
    ITEMID_REDEYE_REDUC_OFF,
#endif  
  
    ITEMID_SELFTIMER,
#if (MENU_STILL_SELF_TIMER_OFF_EN)    
    ITEMID_SELFTIMER_OFF,
#endif
#if (MENU_STILL_SELF_TIMER_2S_EN)    
    ITEMID_SELFTIMER_2S,
#endif
#if (MENU_STILL_SELF_TIMER_10S_EN)    
    ITEMID_SELFTIMER_10S,
#endif    

    ITEMID_BURST_CAPTURE,
#if (MENU_STILL_BURST_SHOT_OFF_EN)    
    ITEMID_BURST_OFF,
#endif
#if (MENU_STILL_BURST_SHOT_LO_EN)    
    ITEMID_BURST_SHOT_LO,
#endif
#if (MENU_STILL_BURST_SHOT_MID_EN)    
    ITEMID_BURST_SHOT_MID,
#endif
#if (MENU_STILL_BURST_SHOT_HI_EN)    
    ITEMID_BURST_SHOT_HI,
#endif

    ITEMID_VMD_SHOT_NUM,
#if (MENU_STILL_VMD_SHOT_NUM_1P_EN)    
    ITEMID_VMD_SHOT_NUM_1P,
#endif
#if (MENU_STILL_VMD_SHOT_NUM_2P_EN)    
    ITEMID_VMD_SHOT_NUM_2P,
#endif
#if (MENU_STILL_VMD_SHOT_NUM_3P_EN)    
    ITEMID_VMD_SHOT_NUM_3P,
#endif
#if (MENU_STILL_VMD_SHOT_NUM_5P_EN)    
    ITEMID_VMD_SHOT_NUM_5P,
#endif

    ITEMID_TIME_LAPSE,
#if (MENU_STILL_TIMELAPSE_TIME1_EN)    
    ITEMID_TIME_LAPSE_TIME1,
#endif
#if (MENU_STILL_TIMELAPSE_TIME2_EN)    
    ITEMID_TIME_LAPSE_TIME2,
#endif
#if (MENU_STILL_TIMELAPSE_TIME3_EN)    
    ITEMID_TIME_LAPSE_TIME3,
#endif
#if (MENU_STILL_TIMELAPSE_TIME4_EN)    
    ITEMID_TIME_LAPSE_TIME4,
#endif
#if (MENU_STILL_TIMELAPSE_TIME5_EN)    
    ITEMID_TIME_LAPSE_TIME5,
#endif
#if (MENU_STILL_TIMELAPSE_TIME6_EN)    
    ITEMID_TIME_LAPSE_TIME6,
#endif
#if (MENU_STILL_TIMELAPSE_TIME7_EN)    
    ITEMID_TIME_LAPSE_TIME7,
#endif

    ITEMID_STILL_END    
} CAMERAITEMID;

/*===========================================================================
 * Function prototype 
 *===========================================================================*/ 

//void MenuStateCameraMode( UINT32 ulEvent, UINT32 ulPosition );

void STATE_CAMERA_MENU_EVENT_TV_DETECT(UINT32 ulEvent);
void STATE_CAMERA_MENU_EVENT_TV_REMOVED(UINT32 ulEvent);
void STATE_CAMERA_MENU_EVENT_HDMI_DETECT(UINT32 ulEvent);
void STATE_CAMERA_MENU_EVENT_HDMI_REMOVED(UINT32 ulEvent);

#endif //_MENU_STATE_CAMERA_MENU_H_


