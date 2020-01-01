/*
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file 
 *   Orientation JSI.
 */

#ifndef ___JKLOCATIONORIENTATION_H___
#define ___JKLOCATIONORIENTATION_H___

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkLocationCommon.h"

/**
 * @addtogroup location_Orientation
 *
 * @{
 */

/**
 *   A data structure to store an orientation
 *
 *   This structure is used to pass an orientation from the native
 *   system to JBlend.
 */
typedef struct JKLocationOrientation {
    /**
     *   Flag indicating whether this orientation is relative to the magnetic 
     *   field of the Earth or relative to true north and gravity.
     *
     *   A boolean which indicates whether or not this orientation is relative to the 
     *   magnetic field. #JK_TRUE, if azimuth and pitch is relative
     *   to the magnetic field of the Earth. #JK_FALSE, otherwise.
     */
    JKBool isMagnetic;

    /**
     *   Compass azimuth
     *
     *   The compass azimuth of the terminal in degrees. The valid
     *   range is [0.0, 360.0). The value must be set in accordance with
     *   the <i>isMagnetic</i> member.
     */
    float azimuth;

    /**
     *   Pitch
     * 
     *   The tilt of the terminal in degrees as an angle in the
     *   vertical plane orthogonal to the ground. The valid range is
     *   [-90.0, 90.0]. A negative value means that the top of the
     *   terminal screen is pointing towards the ground.
     *   This value can be NaN (Not a Number), if unknown.
     */
    float pitch;

    /**
     *   Roll
     * 
     *   The rotation of the terminal in degrees around its own
     *   longitudinal axis. The valid range is [-180.0, 180.0). A
     *   negative value means that the terminal is orientated
     *   anti-clockwise from its default orientation, looking from
     *   direction of the bottom of the screen.
     *   This value can be NaN (Not a Number), if unknown.
     */
    float roll;
} JKLocationOrientation;

/**
 *   Gets the current orientation
 * 
 * @param orientation
 *       A pointer to the structure for putting the acquired orientation.
 * @return
 *       Return #JK_LOCATION_OK if the operation succeeds.
 *       If it fails, return one of the following values.
 *       <ul>
 *         <li> #JK_LOCATION_ERROR_IO<br>
 *              Failed due to general IO error.
 *         <li> #JK_LOCATION_ERROR_NOT_SUPPORTED<br>
 *              The native system does not support orientation acquisition.
 *       </ul>
 * <p>
 *   Store the terminal's current orientation in given structure. At
 *   least azimuth must be valid. If even azimuth can not be obtained,
 *   fail this function with #JK_LOCATION_ERROR_IO. Pitch and roll can
 *   be NaN (Not a Number), if not available.
 */
JKSint32 JkLocationGetOrientation(JKLocationOrientation *orientation);

#ifdef __cplusplus
}
#endif

#endif /* !___JKLOCATIONORIENTATION_H___ */

/** @} end of group */
