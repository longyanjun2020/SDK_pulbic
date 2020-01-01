/**
* @file    mmi_mae_sensormgr_types.h
*
* Accelerometer (G-Sensor)
* ------------------------------
* An accelerometer is a device for measuring acceleration and gravity induced reaction forces.
* The 3-axis is defined as following. Z-axis was ignored for 2-axis model.
*
*            ^
*            | Y-axis                            .
*            |       /                   Z-axis /|\   /\        
*       .---------. /                            |   /   Y-axis
*       | .-----. |/                           .-|------.
*       | |     | |                           / .|----. /|
*       | |     | |                          / / |   / //
*       | |     | |                         / /  |  / //
* ----- | .-----. |-----> X-axis     ----- / .-----. //-----> X-axis
*       | == o == |                       / == o == //
*       |  1/2 3  |                      /  1 2 3  //
*       |  / 5 6  |                     /  4 5 6  //
*       | /7 8 9  |                    /  7 8 9  //
*       ./--------.                   ._________./
*       /    |                        .----/----.|
*      /     |                            /      |
*     V      |                           /       |
*   Z-axis
*           (1)                                  (2)
*
* The output value from g-sensor for the above two example are:
* (1) (x, y, z) = (0g, -1g, 0g)
* (2) (x, y, z) = (0g, 0g, -1g)
* which indicate direction of the gravity induced reaction forces.
* The unit for the output value is not g directly and you can use GSENSOR_VALUE_TO_G macro to convert the value
* to the g unit.
* To prevent the using of floating number, the output value for G-sensor is integer and located between
* GSENSOR_VALUE_MIN and GSENSOR_VALUE_MAX.
*
* If you need the value in G unit, you can use GSENSOR_VALUE_TO_G macro to convert it to G value and you
* may need to use a float or double type to handle this value.
* Here is the mapping between the output value and the g unit value:
*
* output value: GSENSOR_VALUE_MIN     <--> ... <--> GSENSOR_GVALUE_0G <-->  ... <--> GSENSOR_VALUE_MAX
*       g unit: GSENSOR_GVALUE_MIN(g) <--> ...  <-->      0g          <-->  ... <--> GSENSOR_GVALUE_MAX(g)
* and
* output value: GSENSOR_GVALUE_0G-GSENSOR_COUNTS_1G <--> GSENSOR_GVALUE_0G <--> GSENSOR_GVALUE_0G+GSENSOR_COUNTS_1G
*       g unit:                 -1g                 <-->        0g         <-->                  1g
*
* GSENSOR_COUNTS_1G is the count level for 1g, that is, ouput value exists GSENSOR_COUNTS_1G steps between 0g and 1g.
*
* Note: 1g = STANDARD_GRAVITY m/s^2
*
* If you are interested in the motion instead the real sensor value provided here, you can consider to
* use a implementaion of IMotionDetector. IMotionDetector provides a higher view for these g-sensor data.
*
*
* Implementations:
* CLSID_SENSORMGR, current implementation and device only support a 2-axis accelerometer sensor.
* References:
* degree	X(g)	value	Y(g)	value
* ------------------------------------------
*   90		1.000	33792	0.000	32768
*   85		0.996	33788	0.087	32856
*   80		0.985	33776	0.174	32946
*   70		0.940	33730	0.342	33118
*   60		0.866	33654	0.500	33280
*   45		0.707	33492	0.707	33492
*   30		0.500	33280	0.866	33654
*   20		0.342	33118	0.94	33730
*   10		0.174	32946	0.985	33776
*   05		0.087	32856	0.996	33788
*   00		0.000	32768	1.000	33792
*
* @author  mark.yang@mstarsemi.com
* @version $Id: mmi_mae_sensormgr.h 540 2009-03-31 11:04:04Z mark.yang $
*/
#ifndef __MMI_MAE_SENSORMGR_TYPES_H__
#define __MMI_MAE_SENSORMGR_TYPES_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_clstbl.h"
#include "mmi_mae_sensormgr_forward.h"

/**
 * Mapping of output value from ISensor Manager and the real g unit value:
 *  value: 30719 <--> 31743 <--> 32767 <--> 33791 <--> 34815 <--> 35839
 * g unit:  -2g <--> -1g  <-->  0g  <-->  1g  <-->  2g
 */
#define GSENSOR_GVALUE_0G		(32768)		/**< the value for 0g */
#define GSENSOR_GVALUE_DEGREE_00 (32768)
#define GSENSOR_GVALUE_DEGREE_05 (32856)
#define GSENSOR_GVALUE_DEGREE_10 (32946)
#define GSENSOR_GVALUE_DEGREE_20 (33118)
#define GSENSOR_GVALUE_DEGREE_30 (33280)
#define GSENSOR_GVALUE_DEGREE_45 (33492)
#define GSENSOR_GVALUE_DEGREE_60 (33654)
#define GSENSOR_GVALUE_DEGREE_70 (33730)
#define GSENSOR_GVALUE_DEGREE_80 (33776)
#define GSENSOR_GVALUE_DEGREE_85 (33788)
#define GSENSOR_GVALUE_DEGREE_90 (33792)
#define GSENSOR_COUNTS_1G		(1024)		/**< the counts for 1g */
#define GSENSOR_VALUE_TO_G(v)	(((v)-GSENSOR_GVALUE_0G)/GSENSOR_COUNTS_1G) /**< macro to convert the output value to g unit */

#define STANDARD_GRAVITY		(9.80665)		/**< Standard gravity (g) at the Earth's surface at sea level. */

/**
 * Events for client if client need to send event to itself in the call back function
 */
#define SENSORMGR_EVT_SensorNotify	(CLSID_SENSORMGR << 16 | 1)

#define SENSOR_NOTIFY_DELAY_DEFAULT SENSOR_NOTIFY_DELAY_NORMAL

/**
 * Sensor id
 */
opaque_enum(SENSOR_e_)
{
    SENSOR_ACCELEROMETER = 0,	/**< Accelerometer sensor(G-Sensor) */
    SENSOR_LIGHT,				/**< Ambient light sensor */
    SENSOR_COMPASS,				/**< Digital compass which indicate the direction of the device */
    SENSOR_ATMOSPHERIC,			/**< Atmospheric pressure sensor */
    SENSOR_TEMPERATURE			/**< Temperature sensor */
};

/**
 * The sensor notify delay level.
 */
opaque_enum(SENSOR_NOTIFY_DELAY_e_)
{
    SENSOR_NOTIFY_DELAY_FASTEST = 0,	/**< Get notify as soon as possible */
    SENSOR_NOTIFY_DELAY_GAME,		/**< Notify delay suitable for games */
    SENSOR_NOTIFY_DELAY_NORMAL,		/**< [DEFAULT] delay delay suitable for screen orientation changes */
    SENSOR_NOTIFY_DELAY_UI			/**< Notify delay suitable for the user interface */
};

struct GSensorInfo_t_
{
	u16 x;	/**< x-ax accelerometer sensor value */
	u16 y;	/**< y-ax accelerometer sensor value */
	u16 z;	/**< z-ax accelerometer sensor value */
};

struct GSensorDevInfo_t_
{
	u16 nAxisNum;
	u16 nSensitiveLevel;
};

#ifdef __PROXIMITY_SENSOR_MMI__
typedef struct
{
    u16 nIndicator;
    u16 dataL;                    /**< data--L thro */
    u16 dataH;                    /**< data--H thro */
    u16 op_flag;		/*1:intp on; 0:intp off*/
}PaiSensorInfo_t;
#endif

struct LightValue_t_
{
	s32 nLumen;
};

struct AtmosphericValue_t_
{
	s32 nPa;
};

struct TemperatureValue_t_
{
	s16 nSelsius;	/**< degree of C */
};

union SensorInfo_u_
{
	GSensorInfo_t tGSensor;
    #ifdef __PROXIMITY_SENSOR_MMI__
    PaiSensorInfo_t tPaiSensor;
    #endif
	LightValue_t tLight;
	AtmosphericValue_t tAtmospheric;
	TemperatureValue_t tTemperature;
};

union SensorDevInfo_u_
{
	GSensorDevInfo_t tGSensorDevInfo;
};

#endif //  __MMI_MAE_SENSORMGR_TYPES_H__
