#ifndef __MMI_COMMON_CAM_TYPE_H__
#define __MMI_COMMON_CAM_TYPE_H__

/*
 * data type definition of CamApp that is required by other libraries
 * */

typedef enum
{
	CAM_PICTURE_MODE = 0,
	CAM_VIDEO_MODE,
	CAM_EM_MODE,
	CAM_EM_MODE_AUTO_CLOSE
} CamMode_e;

#endif // __MMI_COMMON_CAM_TYPE_H__
