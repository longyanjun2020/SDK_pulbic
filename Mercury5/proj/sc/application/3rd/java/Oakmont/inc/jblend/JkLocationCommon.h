/*
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file 
 *   Common Header for Location JSI.
 */

#ifndef ___JKLOCATIONCOMMON_H___
#define ___JKLOCATIONCOMMON_H___

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * @addtogroup location_Common
 *
 * @{
 */

/**
 *   Error code: Normal termination
 */
#define JK_LOCATION_OK 0

/**
 *   Error code: Illegal parameter
 *
 *   JBlend throws <code>IllegalArgumentException</code> in case a JSI function returns
 *   this error code.
 */
#define JK_LOCATION_ERROR_ILLEGAL_ARGUMENT -1

/**
 *   Error code: I/O error
 *
 *   JBlend throws <code>IOException</code> in case a JSI function returns this error
 *   code.
 */
#define JK_LOCATION_ERROR_IO -2

/**
 *   Error code: Operation not supported
 *
 *   JBlend throws <code>LandmarkException</code> in case a JSI function returns this
 *   error code.
 */
#define JK_LOCATION_ERROR_NOT_SUPPORTED -3

/**
 *   Error code: Out of memory
 *
 *   JBlend throws <code>OutOfMemoryError</code> in case a JSI function returns this
 *   error code.
 */
#define JK_LOCATION_ERROR_NO_MEMORY -4

/**
 *   A data structure to store a string
 *
 *   This structure is used to pass a string to/from JBlend from/to
 *   the native system.
 */
typedef struct JKLocationString {
    /**
     *   The number of characters
     *
     *   The number of characters that this structure contains.
     *   Note that this is not the byte count.
     */
    JKSint32 len;

    /**
     *   The string
     *
     *   The entity of the string. It is encoded in UNICODE and not terminated 
     *   by '\0'. In case this pointer equals #JK_NULL, this structure represents 
     *   a string that the corresponding Java <code>String</code> object is 
     *   <code>null</code>. At the same time, the <i>len</i> member equal zero.
     */
    JKWChar *str;
} JKLocationString;

/**
 *   A data structure to store coordinates
 *
 *   This structure is used to pass coordinates to/from JBlend
 *   from/to the native system.
 */
typedef struct JKLocationCoordinates {
    /**
     *   Validity flag
     * 
     *   A boolean that indicates the validity of this coordinates.
     */
    JKBool isValid;

    /**
     *   Latitude
     *
     *   The latitude measured on WGS84 datum in degrees. The valid
     *   range is [-90.0, 90.0]. Positive values indicate northern
     *   latitude and negative values southern latitude.
     */
    double latitude;

    /**
     *   Longitude
     *
     *   The longitude measured on WGS84 datum in degrees. The valid
     *   range is [-180.0, 180.0). Positive values indicate eastern
     *   longitude and negative values western longitude.
     */
    double longitude;

    /**
     *   Altitude
     *
     *   The altitude measured from the WGS84 ellipsoid in meters. It
     *   can be NaN (Not a Number) to indicate the altitude is
     *   unknown.
     */
    float altitude;

    /**
     *   Horizontal accuracy
     *
     *   The horizontal accuracy of this location information. The RMS
     *   (root mean square) of east accuracy (standard deviation of
     *   latitudinal error in meters) and north accuracy (longitudinal
     *   one). It can be NaN (Not a Number), if unknown.
     */
    float horizontalAccuracy;

    /**
     *   Vertical accuracy
     *
     *   The vertical accuracy of this location information. The
     *   standard deviation of vertical error orthogonal to ellipsoid
     *   surface in meters. It can be NaN (Not a Number), if unknown.
     */
    float verticalAccuracy;
} JKLocationCoordinates;

/**
 *   A data structure to store an address information
 *
 *   This structure is used to pass an address information to/from
 *   JBlend from/to the native system. Each member contains an item of
 *   the address representation for the terminal's locale.
 *   An example follows:
 * 
 * <table>
 *     <tr>
 *       <td>Structure Member</td>
 *       <td>American Example</td>
 *       <td>British Example</td>
 *     </tr>
 *   <tr>
 *     <td><i>extension</i></td>
 *     <td>Flat5</td>
 *     <td>The Oaks</td>
 *   </tr>
 *   <tr>
 *     <td><i>street</i></td>
 *     <td>10 Washington Street</td>
 *     <td>20 Greenford Court</td>
 *   </tr>
 *   <tr>
 *     <td><i>postal_code</i></td>
 *     <td>12345</td>
 *     <td>AB1 9YZ</td>
 *   </tr>
 *   <tr>
 *     <td><i>city</i></td>
 *     <td>Palo Alto</td>
 *     <td>Cambridge</td>
 *   </tr>
 *   <tr>
 *     <td><i>county</i></td>
 *     <td>Santa Clara County</td>
 *     <td>Cambridgeshire</td>
 *   </tr>
 *   <tr>
 *     <td><i>state</i></td>
 *     <td>California</td>
 *     <td>England</td>
 *   </tr>
 *   <tr>
 *     <td><i>country</i></td>
 *     <td>United States of America</td>
 *     <td>United Kingdom</td>
 *   </tr>
 *   <tr>
 *     <td><i>country_code</i></td>
 *     <td>US</td>
 *     <td>GB</td>
 *   </tr>
 * </table>
 * 
 *   In case the value of a member is unknown, set #JK_NULL and 0 for the 
 *   JKLocationString structure <i>str</i> member and the <i>len</i> member respectively.
 *
 */
typedef struct JKLocationAddressInfo {
    /**
     *   Validity flag
     * 
     *   A boolean that indicates the validity of this addressInfo.
     */
    JKBool isValid;

    /**
     *   Address extension
     */
    JKLocationString extension;

    /**
     *   Street name and number
     */
    JKLocationString street;

    /**
     *   Zip or postal code
     */
    JKLocationString postal_code;

    /**
     *   Town or city
     */
    JKLocationString city;

    /**
     *   County
     */
    JKLocationString county;

    /**
     *   State or province
     */
    JKLocationString state;

    /**
     *   Country
     */
    JKLocationString country;

    /**
     *   Country code (two-letter ISO 3166-1 code)
     */
    JKLocationString country_code;

    /**
     *   Municipal district
     */
    JKLocationString district;

    /**
     *  Building name
     */
    JKLocationString building_name;

    /**
     *   Building floor
     */
    JKLocationString building_floor;

    /**
     *   Building room
     */
    JKLocationString building_room;

    /**
     *   Building zone
     */
    JKLocationString building_zone;

    /**
     *   Street in a crossing 1
     */
    JKLocationString crossing1;

    /**
     *   Street in a crossing 2
     */
    JKLocationString crossing2;

    /**
     *   URL
     */
    JKLocationString url;

    /**
     *   Phone number
     */
    JKLocationString phone_number;
} JKLocationAddressInfo;

#ifdef __cplusplus
}
#endif

#endif /* !___JKLOCATIONCOMMON_H___ */

/** @} end of group */
