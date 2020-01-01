/*
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file 
 *   Coordinates JSI.
 */

#ifndef ___JKLOCATIONCOORDINATES_H___
#define ___JKLOCATIONCOORDINATES_H___

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkLocationCommon.h"

/**
 * @addtogroup location_Coordinates
 *
 * @{
 */

/**
 *   Calculates the azimuth between two points
 * 
 * @param from
 *       The origin for azimuth calculation.
 * @param to
 *       The destination for azimuth calculation.
 * @return
 *       Return the azimuth from the origin given in <i>from</i> 
 *       to the destination given in <i>to</i>, in degrees. The valid
 *       range is [0.0, 360.0).
 *
 *   This function is called to calculate the azimuth between two
 *   points. The result shall be the angle relative to true north from
 *   the origin given in <i>from</i> and to the destination given in
 *   <i>to</i>. Calculation should be performed as accurate as
 *   possible on the WGS84 datum. Allowed error is 1.0 degree.
 *
 *   For the following special cases which are defined in JSR-179, the calculations 
 *   are handled by JBlend and therefore this function is not called.
 *   <ul>
 *     <li><i>from</i> is the North pole and <i>to</i> is other than the North pole: 180.0
 *     <li><i>from</i> is the South pole and <i>to</i> is other than the South pole: 0.0
 *     <li><i>from</i> and <i>to</i> is the same: 0.0
 *   </ul>
 *
 *   For the valid range of the members of the structure passed by <i>from</i> 
 *   and <i>to</i>, see description of the #JKLocationCoordinates structure
 */
float JkLocationGetAzimuth(const JKLocationCoordinates *from, const JKLocationCoordinates *to);

/**
 *   Calculates the distance between two points
 * 
 * @param from
 *       The origin for distance calculation.
 * @param to
 *       The destination for distance calculation.
 * @return
 *       Return the calculated distance between two points in meters.
 *
 *   This function is called to calculate the distance between two
 *   points. Calculation should be performed as accurate as possible
 *   on the WGS84 datum. Hight can be neglected. 
 *   When the target device conforms to Location API v1.0, the maximum permissible error is 0.35%; 
 *   for Location API v1.0.1, the maximum permissible error is 0.36%.
 *
 *   For the valid range of the members of the structure passed by <i>from</i> 
 *   and <i>to</i>, see description of the #JKLocationCoordinates structure
 */
float JkLocationGetDistance(const JKLocationCoordinates *from, const JKLocationCoordinates *to);

#ifdef __cplusplus
}
#endif

#endif /* !___JKLOCATIONCOORDINATES_H___ */

/** @} end of group */
