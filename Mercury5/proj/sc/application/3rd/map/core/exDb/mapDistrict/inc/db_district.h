#ifndef DB_DISTRICT_H
#define DB_DISTRICT_H

//#define DISTRICT_DB_ROOT UCS2_TEXT("/CARD/Maps/Database")
//#define DISTRICT_EX_DB_ROOT UCS2_TEXT("/CARD/Maps/Database/iddb")

//#define DISTRICT_DB_FILE UCS2_TEXT("district.db")
#define DISTRICT_NAME_DB_FILE UCS2_TEXT("district_name.db")
#define DB_DISTRICT_MAX_FILENAME_SIZE 512

#define INVALID_DISTRICT_ID 0xFFFF

#define DISTRICT_MIN_X  7344000
#define DISTRICT_MAX_X 13510000
#define DISTRICT_MIN_Y  1815000
#define DISTRICT_MAX_Y  5357000
#define DISTRICT_GRID_WT 1000
#define DISTRICT_GRID_HT 1000
#define DISTRICT_Y_GRID_CNT (S32)(((DISTRICT_MAX_Y)-(DISTRICT_MIN_Y))/DISTRICT_GRID_HT)

#define DISTRICT_ID_WIDTH 2

#define DISTRICT_INVALIAD_ID (0xFFFF)

#define DISTRICT_PROVINCE_NAME_IDX 4000

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

MBOOL dbGetDistrictName(S32 s32LX, S32 s32BY, S32 s32RX, S32 s32TY, PU16 pvCtName, U16 u16NameCtSize, PU16 pvPvName, U16 u16PvNameSize, PU16 pMapDBPath, PU16 pMapExDBPath);
    

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* end of #ifndef DB_DISTRICT_H */
