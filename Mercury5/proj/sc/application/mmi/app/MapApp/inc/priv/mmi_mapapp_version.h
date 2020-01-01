#ifndef __MMI_MAPAPP_VERSION_H__
#define __MMI_MAPAPP_VERSION_H__

#define MAPAPP_VERCHK_FILE_PATH L"/CARD/Maps/MapApp.version"
#ifdef __DUAL_CARD__
#define MAPAPP_VERCHK_FILE_PATH_CARD2 L"/SD_2/Maps/MapApp.version"
#endif

#ifdef CHECK_MAPAPP_VERSION

#define     MAPAPP_VERCHK_SOFTWARE_VER      L"107"
#define     MAPAPP_VERCHK_PRODUCT_NUM       L"pppppppp"
#define     MAPAPP_VERCHK_MAP_VENDOR        L"0"
#define     MAPAPP_VERCHK_MAP_DB_FUNC       L"1"
#define     MAPAPP_VERCHK_POI_DB_FUNC       L"0"

#endif  // for CHECK_MAPAPP_VERSION

/**************************************************************************
MAPAPP_VERCHK_MAP_VENDOR : 0 = General, 1 = EMG.
MAPAPP_VERCHK_MAP_DB_FUNC: 0 = Mapview, 1 = Boundary Polygon, 2 = Routing.
MAPAPP_VERCHK_POI_DB_FUNC: 0 = Mapview.
**************************************************************************/

#endif  // for __MMI_MAPAPP_VERSION_H__
