/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      db_rdgeoGrid.h
 *
 * DESCRIPTION
 *      This file provides the interfaces to load the index table of the grid
 *      group and load/handle the grids.
 *
 * HISTORY
 *      2009.04.21       Mickey Chiang     Initial Version
 *      2009.04.23       Mickey Chiang     Added SUPPORT_COMBINED_DB.
 *      2009.05.06       Mickey Chiang     Used "S32" to replace "int".
 *      2009.06.15       Mickey Chiang     Modified the structure of the grid for
 *                                         the reduced DB.
 *      2009.06.23       Mickey Chiang     Added error code for retrieving APIs.
 *      2009.07.07       Mickey Chiang     Added error code for dbRdGeoGridGrpIdxLoad().
 *----------------------------------------------------------------------------- 
 */
#ifndef DB_RDGEOGRID_H
#define DB_RDGEOGRID_H

/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/
#define DB_RDGEO_MAX_SHPCLASSPAIR    62       /* the maximal number of the shape class pairs     */
#define DB_RDGEO_GRIDGRPIDX_FILESIZE 86412    /* 120 horizontal grids and 120 vertical grids     */
                                              /* 2 bytes for grid ID and 4 bytes for file offset */
                                              /* 12 bytes for the version words                  */
                                              /* So, 120x120x6+12=86400+12=86412 bytes           */

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
/* the data structure of the grid unit */
typedef struct GridUnit_s
{
    S32 s32PointUnit;         /* the scale unit for a vertex                         */
    S32 s32OriX;              /* the X coordinate of the original point              */
    S32 s32OriY;              /* the Y coordinate of the original point              */
    S32 s32MaxX;              /* the maximal X coordinate                            */
    S32 s32MaxY;              /* the maximal Y coordinate                            */
    S32 s32XUnitOfGrid;       /* the X-coordinate unit for a grid                    */
    S32 s32YUnitOfGrid;       /* the Y-coordinate unit for a grid                    */
    S32 s32NumOfXGrid;        /* the number of grids at X-coordinate in a grid group */
    S32 s32NumOfYGrid;        /* the number of grids at Y-coordinate in a grid group */
    S32 s32LastGridID;        /* the last grid ID in a grid group                    */
    S32 s32XUnitOfGridGrp;    /* the X-coordinate unit for a grid group              */
    S32 s32YUnitOfGridGrp;    /* the Y-coordinate unit for a grid group              */
    S32 s32NumOfXGridGrp;     /* the number of grid groups at X-coordinate           */
} GridUnit_st,*pGridUnit_st;

/* data structure of the grid group index table */
typedef struct GridGrpIdx_s
{
    MHANDLE hGridDBHandle;                               /* the handle of the grid DB                */
    S32     s32NumOfGrids;                               /* the number of grids                      */
    S32     s32FileSize;                                 /* the size of the grid group index file    */
    PU32    pu32FileOffset;                              /* the grid file offset table               */
    PU16    pu16ID;                                      /* the grid ID table                        */
    U8      au8RawData[DB_RDGEO_GRIDGRPIDX_FILESIZE];    /* the content of the grid group index file */
} GridGrpIdx_st,*pGridGrpIdx_st;

/* data structure of one grid architecture */
typedef struct GridArch_s
{
    U8        u8NameIDFlag;                                  /* the Name ID flag: 0->1 byte for Name ID, 1->2 bytes for Name ID */
    U8        u8ShpClassPairCount;                           /* the number of shape class pair                                  */
    U8        au8Class[DB_RDGEO_MAX_SHPCLASSPAIR];           /* the class types                                                 */
    U16       au16ClassCount[DB_RDGEO_MAX_SHPCLASSPAIR];     /* the number of shapes in every class                             */
    U16       au16ClassOffset[DB_RDGEO_MAX_SHPCLASSPAIR];    /* the offset of the starting shape in every class                 */
    PU8       pu8ShpRawData;                                 /* the pointer to the shape encoded raw data                       */
    PU16      pu16NameTbl;                                   /* the pointer to the name table                                   */
} GridArch_st,*pGridArch_st;

/* data structure of one grid data */
typedef struct Grid_s
{
    U32         u32GridID;                       /* the grid ID                                           */
    Vertex_st   sOriPt;                          /* the original point of this grid                       */
    Vertex_st   sMaxPt;                          /* the maximal point of this grid                        */
#ifdef SUPPORT_COMBINED_DB
    GridArch_st asGridArch[E_DBSESSION_BOTH];    /* the grid architectures for road and geometry sessions */
#else    /* !defined(SUPPORT_COMBINED_DB) */
    GridArch_st sGridArch;                       /* the grid architecture for road or geometry session    */
#endif    /* end of #ifdef SUPPORT_COMBINED_DB */
    PU8         pu8GridRawData;                  /* the pointer to the grid entity                        */
} Grid_st,*pGrid_st;

/* data structure of one grid data with only one full-covered shape for boundary polygon */
typedef struct CoveredGrid_s
{
#ifdef FOR_UNIT_TEST
    U32       u32GridID;    /* the grid ID        */
#endif    /* end of #ifdef FOR_UNIT_TEST */
    U32       u32Class;     /* the shape class    */
    Vertex_st sMinV;        /* the minimal corner */
    Vertex_st sMaxV;        /* the maximal corner */
} CoveredGrid_st,*pCoveredGrid_st;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 *  Syntax:
 *      MBOOL dbRdGeoGridGrpIdxLoad(PU16 pu16RootDIR,PU16 pu16LODInfoFile,U32 u32GridGrpID,
 *                                  pGridGrpIdx_st psGridGrpIdx,pDBErrCode_et peErrCode);
 * 
 *  Purpose:
 *      Load the index table of the grid group.
 *
 *  Parameters:
 *      pu16RootDIR
 *          [in] The root path of road/geometry DB.
 *      pu16LODInfoFile
 *          [in] The prefix of the road/geometry LOD information file.
 *      u32GridGrpID
 *          [in] The grid group ID.
 *      psGridGrpIdx
 *          [out] The space to store the one grid group index table.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      MBOOL_TRUE:  success.
 *      MBOOL_FALSE: fail.
 */
MBOOL dbRdGeoGridGrpIdxLoad(PU16 pu16RootDIR,PU16 pu16LODInfoFile,U32 u32GridGrpID,
                            pGridGrpIdx_st psGridGrpIdx,pDBErrCode_et peErrCode);

#ifdef SUPPORT_COMBINED_DB
/*
 *  Syntax:
 *      S32 dbRdGeoGridGrpLoad(MBOOL bMightMeetBound,S32 s32GGLX,S32 s32GGBY,S32 s32BoundLX,
 *                             S32 s32BoundBY,S32 s32BoundRX,S32 s32BoundTY,U32 u32Type,U32 u32GridGrpID,
 *                             U32 u32LBGridID,U32 u32RTGridID,pGridUnit_st psGridUnit,
 *                             pGridGrpIdx_st psGridGrpIdx,U8 u8RdFilter,U8 u8RdTWFilter,U8 u8GeFilter,
 *                             PMVOID pvRdDecoder,PMVOID pvRdClientData,PMVOID pvRdHandler,
 *                             PMVOID pvGeDecoder,PMVOID pvGeClientData,PMVOID pvGeHandler,
 *                             pDBErrCode_et peErrCode);
 * 
 *  Purpose:
 *      Load and handle the grids.
 *
 *  Parameters:
 *      bMightMeetBound
 *          [in] Depict whether the given grid group is closed to the bounding box.
 *      s32GGLX
 *          [in] The given left x coordinate of the bounding box for the grid group.
 *      s32GGBY
 *          [in] The given bottom y coordinate of the bounding box for the grid group.
 *      s32BoundLX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BoundBY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32BoundRX
 *          [in] The given right x coordinate of the bounding box.
 *      s32BoundTY
 *          [in] The given top y coordinate of the bounding box.
 *      u32Type
 *          [in] The DB session type.
 *               E_DBSESSION_GE  : for geometry session.
 *               E_DBSESSION_RD  : for road session.
 *               E_DBSESSION_BOTH: for both geometry and road sessions.
 *      u32GridGrpID
 *          [in] The grid group ID.
 *      u32LBGridID
 *          [in] The left-bottom corner grid ID in this grid group.
 *      u32RTGridID
 *          [in] The right-top corner grid ID in this grid group.
 *      psGridUnit
 *          [in] The grid unit data in this LOD.
 *      psGridGrpIdx
 *          [in] The grid group index table.
 *      u8RdFilter
 *          [in] The filter of the road level.
 *      u8RdTWFilter
 *          [in] The filter of the road level for twice handling.
 *      u8GeFilter
 *          [in] The filter of the geometry level.
 *      pvRdDecoder
 *          [in] The callback function to decode the grids for road data.
 *      pvRdClientData
 *          [in] The caller's client data for road data.
 *      pvRdHandler
 *          [in] The callback function to handle the matched mapview road shape data.
 *      pvGeDecoder
 *          [in] The callback function to decode the grids for geometry data.
 *      pvGeClientData
 *          [in] The caller's client data for geometry data.
 *      pvGeHandler
 *          [in] The callback function to handle the matched mapview geometry shape data.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      The number of the matched shapes.
 */
S32 dbRdGeoGridGrpLoad(MBOOL bMightMeetBound,S32 s32GGLX,S32 s32GGBY,
                       S32 s32BoundLX,S32 s32BoundBY,S32 s32BoundRX,S32 s32BoundTY,U32 u32Type,
                       U32 u32GridGrpID,U32 u32LBGridID,U32 u32RTGridID,
                       pGridUnit_st psGridUnit,pGridGrpIdx_st psGridGrpIdx,
                       U8 u8RdFilter,U8 u8RdTWFilter,U8 u8GeFilter,
                       PMVOID pvRdDecoder,PMVOID pvRdClientData,PMVOID pvRdHandler,
                       PMVOID pvGeDecoder,PMVOID pvGeClientData,PMVOID pvGeHandler,
                       pDBErrCode_et peErrCode);
#else    /* !defined(SUPPORT_COMBINED_DB) */
/*
 *  Syntax:
 *      S32 dbRdGeoGridGrpLoad(MBOOL bMightMeetBound,S32 s32GGLX,S32 s32GGBY,S32 s32BoundLX,
 *                             S32 s32BoundBY,S32 s32BoundRX,S32 s32BoundTY,U32 u32GridGrpID,
 *                             U32 u32LBGridID,U32 u32RTGridID,pGridUnit_st psGridUnit,
 *                             pGridGrpIdx_st psGridGrpIdx,U8 u8Filter,U8 u8TWFilter,PMVOID pvDecoder,
 *                             PMVOID pvClientData,PMVOID pvHandler,pDBErrCode_et peErrCode);
 * 
 *  Purpose:
 *      Load and handle the grids.
 *
 *  Parameters:
 *      bMightMeetBound
 *          [in] Depict whether the given grid group is closed to the bounding box.
 *      s32GGLX
 *          [in] The given left x coordinate of the bounding box for the grid group.
 *      s32GGBY
 *          [in] The given bottom y coordinate of the bounding box for the grid group.
 *      s32BoundLX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BoundBY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32BoundRX
 *          [in] The given right x coordinate of the bounding box.
 *      s32BoundTY
 *          [in] The given top y coordinate of the bounding box.
 *      u32GridGrpID
 *          [in] The grid group ID.
 *      u32LBGridID
 *          [in] The left-bottom corner grid ID in this grid group.
 *      u32RTGridID
 *          [in] The right-top corner grid ID in this grid group.
 *      psGridUnit
 *          [in] The grid unit data in this LOD.
 *      psGridGrpIdx
 *          [in] The grid group index table.
 *      u8Filter
 *          [in] The filter of the road/geometry level.
 *      u8TWFilter
 *          [in] The filter of the road/geometry level for twice handling.
 *      pvDecoder
 *          [in] The callback function to decode the grids.
 *      pvClientData
 *          [in] The caller's client data.
 *      pvHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values
 *      The number of the matched shapes.
 */
S32 dbRdGeoGridGrpLoad(MBOOL bMightMeetBound,S32 s32GGLX,S32 s32GGBY,
                       S32 s32BoundLX,S32 s32BoundBY,S32 s32BoundRX,S32 s32BoundTY,
                       U32 u32GridGrpID,U32 u32LBGridID,U32 u32RTGridID,
                       pGridUnit_st psGridUnit,pGridGrpIdx_st psGridGrpIdx,U8 u8Filter,U8 u8TWFilter,
                       PMVOID pvDecoder,PMVOID pvClientData,PMVOID pvHandler,pDBErrCode_et peErrCode);
#endif    /* end of #ifdef SUPPORT_COMBINED_DB */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* end of #ifndef DB_RDGEOGRID_H */
