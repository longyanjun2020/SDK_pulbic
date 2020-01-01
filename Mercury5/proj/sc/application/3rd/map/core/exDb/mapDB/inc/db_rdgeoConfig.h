/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      db_rdgeoConfig.h
 *
 * DESCRIPTION
 *      This file provides the definition of the module constant values.
 *
 * HISTORY
 *      2009.04.21       Mickey Chiang     Initial Version
 *      2009.04.23       Mickey Chiang     Added SUPPORT_COMBINED_DB.
 *      2009.07.07       Mickey Chiang     Added the function ID definition.
 *----------------------------------------------------------------------------- 
 */
#ifndef DB_RDGEOCONFIG_H
#define DB_RDGEOCONFIG_H

/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/
#define DB_RDGEO_NUMOFLOD           7                        /* the number of LODs                                                        */
#define DB_RDGEO_MAX_FILENAME_SIZE  256                      /* the maximal size of the file name                                         */
#define DB_RDGEO_VERSION_SIZE       12                       /* the number of version word                                                */
#define DB_RDGEO_GRID_IDX_SIZE      6                        /* the size of one grid index (2 bytes for grid ID, 4 bytes for file offset) */

#ifdef SUPPORT_COMBINED_DB
#define DB_RDGEO_LODINFORM_FILE     UCS2_TEXT("MSRG_LOD")    /* the prefix of the combined DB LOD information file                        */
#else    /* !defined(SUPPORT_COMBINED_DB) */
#define DB_RDGEO_RDLODINFORM_FILE   UCS2_TEXT("MSRD_LOD")    /* the prefix of the road LOD information file                               */
#define DB_RDGEO_GEOLODINFORM_FILE  UCS2_TEXT("MSGE_LOD")    /* the prefix of the geometry LOD information file                           */
#endif    /* end of #ifdef SUPPORT_COMBINED_DB */

#define DB_RDGEO_SUFFIX_DAT         UCS2_TEXT("dat")         /* the suffix string for the LOD information file                            */
#define DB_RDGEO_SUFFIX_IDX         UCS2_TEXT("idx")         /* the suffix string for the grid group index file                           */
#define DB_RDGEO_SUFFIX_BIN         UCS2_TEXT("bin")         /* the suffix string for the grid group DB file                              */

/* One complete grid ID:                              */
/* bit31       (1  bit ): type (0: road; 1: geometry) */
/*                        Don't care for combined DB  */
/* bit30~bit28 (3  bits): LOD                         */
/* bit27~bit16 (12 bits): grid group ID               */
/* bit15~bit0  (16 bits): local grid ID               */
#define DB_RDGEO_LOD_SHIFTBIT       12            /* at the 16-bit grid group ID, the bit14~bit12 are for LOD              */
#define DB_RDGEO_TYPE_SHIFTBIT      15            /* at the 16-bit grid group ID, bit15 is the type (0: road, 1: geometry) */
#define DB_RDGEO_GRIDGRPID_SHIFTBIT 16            /* at the 32-bit grid ID, the leading 16 bits are for grid group ID      */
#define DB_RDGEO_GRIDGRPID_MASK     0x000007FF    /* at the 16-bit grid group ID, the mask to retrieve grid group ID       */
#define DB_RDGEO_GRIDID_MASK        0x0000FFFF    /* at the 32-bit grid ID, the mask to retrieve the local grid ID         */
#define DB_RDGEO_LOD_MASK           0x00000007    /* at the 4-bit LOD, the bit2~bit0 are for LOD                           */

#ifndef SUPPORT_COMBINED_DB
/* the DB type for the grid group ID */
#define DB_RDGEO_DBTYPE_GGRD 0x00000000    /* the bit15 is 0 for road     */
#define DB_RDGEO_DBTYPE_GGGE 0x00008000    /* the bit15 is 1 for geometry */
#endif    /* end of #ifndef SUPPORT_COMBINED_DB */

/* The function ID definition at byte 2 of the version field */
#define DB_RDGEO_FNID '1'    /* '0': map view                                   */
                             /* '1': map view with boundary polygon             */
                             /* '2': map view with boundary polygon and routing */
#define DB_RDGEO_FID  2      /* the location of the function ID */

#endif    /* end of #ifndef DB_RDGEOCONFIG_H */
