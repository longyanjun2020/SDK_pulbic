#ifndef __VEN__TEST_CAMERA_DEFINE_H__
#define __VEN__TEST_CAMERA_DEFINE_H__

/**
 *
 * @file    test_ven_cam.h
 * @brief   This file defines the camera interface definition.
 *
 * @author  Code.Lin
 * @version $Id: test_ven_time.h 27833 2009-04-08 12:12:22Z code.lin $
 *
 */
#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_cam.h"

enum
{
	CAM_OPEN_CAMERA,
	CAM_CLOSE_CAMERA,
	CAM_START_PREVIEW,
	CAM_STOP_PREVIEW,
	CAM_GET_IMAGE,
	CAM_CONVERT_IMAGE,
	CAM_LAUNCH_APP,
};

#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

#endif // __VEN__TEST_CAMERA_DEFINE_H__
