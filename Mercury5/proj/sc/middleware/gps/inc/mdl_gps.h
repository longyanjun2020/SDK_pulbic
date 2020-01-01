#ifndef __MDL_GPS_H__
#define __MDL_GPS_H__

typedef enum
{
    MDL_GPS_STATE_CLOSE  = 0x00,
    MDL_GPS_STATE_OPEN  = 0x01,
    MDL_GPS_STATE_RUNNING = 0x02,
    MDL_GPS_STATE_NUM
} MdlGpsState_e;

typedef enum
{
    MDL_GPS_ERROR_SUCCESS = 0,
    MDL_GPS_ERROR_FAIL,
    MDL_GPS_ERROR_NUM
} MdlErrCode_e;

/*
typedef enum
{
    MDL_GPS_OPEN_GPS = 0,                     //Open GPS
    MDL_GPS_CLOSE_GPS,                        //Close GPS
    MDL_GPS_START_GPS,                        //Start GPS
    MDL_GPS_STOP_GPS
} MdlGpsCmd_e;
*/
extern void MdlGpsTaskInit (void);

extern void MdlGpsTaskParser (void *pMessage);

#endif // __MDL_GPS_H__

