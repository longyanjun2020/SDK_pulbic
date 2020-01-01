/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      db_rdgeoDecoder.h
 *
 * DESCRIPTION
 *      This file provides the interfaces to decode the road/geometry grids.
 *
 * HISTORY
 *      2009.04.21       Mickey Chiang     Initial Version
 *      2009.04.23       Mickey Chiang     Replaced psGrid with psGridArch.
 *      2009.05.13       Mickey Chiang     Added dbRdGeoDecoderGetScreenParams() to
 *                                         get the number of shapes, vertices and names.
 *      2009.06.15       Mickey Chiang     Modified the structure of the grid for
 *                                         the reduced DB.
 *      2009.06.23       Mickey Chiang     Add error code for retrieving APIs.
 *      2009.09.17       Mickey Chiang     Added SUPPORT_DRAWING_TW to determine whether
 *                                         support the function with twice drawing.
 *-----------------------------------------------------------------------------
 */
#ifndef DB_RDGEODECODER_H
#define DB_RDGEODECODER_H

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
/* the assistant decoder type */
typedef enum AssDecoder_e
{
    E_ASSDECODER_RD=0,         /* the assistant decoder to road shapes without handling            */
    E_ASSDECODER_GEO,          /* the assistant decoder to geometry shapes without handling        */
    E_ASSDECODER_RD_ONCE,      /* the assistant decoder for road shapes with one-time handling     */
    E_ASSDECODER_GEO_ONCE,     /* the assistant decoder for geometry shapes with one-time handling */
#ifdef SUPPORT_DRAWING_TW
    E_ASSDECODER_RD_TWICE,     /* the assistant decoder for road shapes with twice handling        */
#endif    /* end of #ifdef SUPPORT_DRAWING_TW */
    E_ASSDECODER_UNKNOWN       /* unknow assistant decoder type                                    */
} AssDecoder_et,*pAssDecoder_et;

#define DB_RDGEO_NUMOF_DECODER E_ASSDECODER_UNKNOWN    /* the number of assistant decoder types */

/*
 *  Syntax:
 *      S32 (*ShpIdxGet_pfn)(pGridArch_st psGridArch,U8 u8FilterClass);
 *
 *  Purpose:
 *      Get the class and shape index of the road/geometry grid.
 *
 *  Parameters:
 *      psGridArch
 *          [in] The grid architecture.
 *      u8FilterClass
 *          [in] The filter of the road/geometry level.
 *
 *  Return Values:
 *      The number of matched classes.
 */
typedef S32 (*ShpIdxGet_pfn)(pGridArch_st,U8);

/*
 *  Syntax:
 *      S32 (*VerCountGet_pfn)(PU8 pu8RawData,PS32 ps32Idx,PMBOOL pbVertex2Bytes);
 *
 *  Purpose:
 *      Get the number of vertices of the road/geometry shape.
 *
 *  Parameters:
 *      pu8RawData
 *          [in] The raw data of one road/geometry shape.
 *      ps32Idx
 *          [out] The index to point to the following encoded data of the road/geometry shape.
 *      pbVertex2Bytes
 *          [out] Depict whether the road/geometry shape is formed in 2 bytes for every vertex.
 *
 *  Return Values:
 *      The number of vertices.
 */
typedef S32 (*VerCountGet_pfn)(PU8,PS32,PMBOOL);

#if defined(SUPPORT_RETURN_ONE_SCREENDATA)&&defined(SUPPORT_NAMECACHE)
/*
 *  Syntax:
 *      MVOID (*NameGet_pfn)(pOneShpAttri_st psShpAttri,PU8 pu8RawData,pGridArch_st psGridArch,
 *                           PS32 ps32Idx,PU32 pu32Name1ID,PU32 pu32Name2ID,PU32 pu32NameNumID);
 *
 *  Purpose:
 *      Get the names of the road/geometry shape.
 *
 *  Parameters:
 *      psShpAttri
 *          [out] The road/geometry shape data which provide the pointers to the names.
 *      pu8RawData
 *          [in] The raw data of one road/geometry shape.
 *      psGridArch
 *          [in] The grid architecture.
 *      ps32Idx
 *          [out] The index to point to the following encoded data of the road/geometry shape.
 *      pu32Name1ID
 *          [out] The ID of the name 1 of the road/geometry shape.
 *      pu32Name2ID
 *          [out] The ID of the name 2 of the road/geometry shape.
 *      pu32NameNumID
 *          [out] The ID of the name number of the road/geometry shape.
 *
 *  Return Values:
 *      None.
 */
typedef MVOID (*NameGet_pfn)(pOneShpAttri_st,PU8,pGridArch_st,PS32,PU32,PU32,PU32);
#else    /* !defined(SUPPORT_RETURN_ONE_SCREENDATA)||!defined(SUPPORT_NAMECACHE) */
/*
 *  Syntax:
 *      MVOID (*NameGet_pfn)(pOneShpAttri_st psShpAttri,PU8 pu8RawData,pGridArch_st psGridArch,PS32 ps32Idx);
 *
 *  Purpose:
 *      Get the names of the road/geometry shape.
 *
 *  Parameters:
 *      psShpAttri
 *          [out] The road/geometry shape data which provide the pointers to the names.
 *      pu8RawData
 *          [in] The raw data of one road/geometry shape.
 *      psGridArch
 *          [in] The grid architecture.
 *      ps32Idx
 *          [out] The index to point to the following encoded data of the road/geometry shape.
 *
 *  Return Values:
 *      None.
 */
typedef MVOID (*NameGet_pfn)(pOneShpAttri_st,PU8,pGridArch_st,PS32);
#endif    /* end of #if defined(SUPPORT_RETURN_ONE_SCREENDATA)&&defined(SUPPORT_NAMECACHE) */

/*
 *  Syntax:
 *      MBOOL (*IsCoveredGrid_pfn)(PU8 pu8RawData);
 *
 *  Purpose:
 *      Check whether this shape covers the whole grid. This kind of shape is only for
 *      the boundary polygon, so it's impossible to exist at road DB.
 *
 *  Parameters:
 *      pu8RawData
 *          [in] The raw data of one road/geometry shape.
 *
 *  Return Values:
 *      The boolean value depicts whether this shape covers the whole grid.
 */
typedef MBOOL (*IsCoveredGrid_pfn)(PU8);

/*
 *  Syntax:
 *      S32 (*MapViewShpDecode_pfn)(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
 *                                  S32 s32ScaleUnit,U8 u8FilterClass,U8 u8TWFilterClass,pGrid_st psGrid,
 *                                  pGridArch_st psGridArch,ShpIdxGet_pfn pfnShpIdxGet,
 *                                  VerCountGet_pfn pfnVerCountGet,NameGet_pfn pfnNameGet,
 *                                  IsCoveredGrid_pfn pfnIsCoveredGrid,PMVOID pvClientData,
 *                                  PMVOID pvHandler,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Decode the shape data and then handle the decoded data.
 *
 *  Parameters:
 *      bReferBoundary
 *          [in] Depict whether to refer to the input bounding box.
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32ScaleUnit
 *          [in] The scale unit.
 *      u8FilterClass
 *          [in] The filter of the road/geometry level.
 *      u8TWFilterClass
 *          [in] The filter of the road/geometry level for twice handling.
 *      psGrid
 *          [in] The grid data.
 *      psGridArch
 *          [in] The grid architecture.
 *      pfnShpIdxGet
 *          [in] The callback function to get the class and shape index of the road/geometry grid.
 *      pfnVerCountGet
 *          [in] The callback function to get the number of vertices of the road/geometry shape.
 *      pfnNameGet
 *          [in] The callback function to get the names of the road/geometry shape.
 *      pfnIsCoveredGrid
 *          [in] The callback function to check whether the shape covers the whole grid.
 *      pvClientData
 *          [in] The caller's client data.
 *      pvHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values:
 *      The number of decoded shapes.
 */
typedef S32 (*MapViewShpDecode_pfn)(MBOOL,S32,S32,S32,S32,S32,U8,U8,pGrid_st,pGridArch_st,ShpIdxGet_pfn,
                                    VerCountGet_pfn,NameGet_pfn,IsCoveredGrid_pfn,PMVOID,PMVOID,
                                    pDBErrCode_et);

/*
 *  Syntax:
 *      S32 (*MapViewBPGShpDecode_pfn)(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
 *                                     U8 u8FilterClass,pCoveredGrid_st psCoveredGrid,
 *                                     PMVOID pvClientData,PMVOID pvHandler,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Decode the boundary polygon shape data and then handle the decoded data.
 *
 *  Parameters:
 *      bReferBoundary
 *          [in] Depict whether to refer to the input bounding box.
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      u8FilterClass
 *          [in] The filter of the road/geometry level.
 *      psCoveredGrid
 *          [in] The boundary data which covers the whole grid.
 *      pvClientData
 *          [in] The caller's client data.
 *      pvHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values:
 *      The number of decoded shapes.
 */
typedef S32 (*MapViewBPGShpDecode_pfn)(MBOOL,S32,S32,S32,S32,U8,pCoveredGrid_st,PMVOID,PMVOID,pDBErrCode_et);

/* data structure to assist the grid decoding */
typedef struct GridAssDecoder_s
{
    ShpIdxGet_pfn           pfnShpIdxGet;         /* the function pointer to get the matched class index and corresponding vertex index */
    VerCountGet_pfn         pfnVerCountGet;       /* the function pointer to get the vertex count                                       */
    NameGet_pfn             pfnNameGet;           /* the function pointer to get name(s)                                                */
    IsCoveredGrid_pfn       pfnIsCoveredGrid;     /* the function pointer to check whether the shape covers the whole grid.             */
    MapViewShpDecode_pfn    pfnMVShpDecode;       /* the function pointer to decode the shape data                                      */
    MapViewBPGShpDecode_pfn pfnMVBPGShpDecode;    /* the function pointer to decode the boundary polygon shape data                     */
} GridAssDecoder_st,*pGridAssDecoder_st;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef SUPPORT_INPUT_MEMSPACE
/*
 *  Syntax:
 *      MBOOL dbRdGeoDecoderInitialize(PMVOID pvMemAddr,S32 s32MaxSize,PS32 ps32Idx);
 *
 *  Purpose:
 *      Initialize the decoder to assign the space to store the decoded data.
 *
 *  Parameters:
 *      pvMemAddr
 *          [in] The address of the given memory space.
 *      s32MaxSize
 *          [in] The size of the given memory space.
 *      ps32Idx
 *          [out] The starting index of the memory space for the next module.
 *
 *  Return Values
 *      MBOOL_TRUE:  success.
 *      MBOOL_FALSE: fail.
 */
MBOOL dbRdGeoDecoderInitialize(PMVOID pvMemAddr,S32 s32MaxSize,PS32 ps32Idx);

#else    /* !defined(SUPPORT_INPUT_MEMSPACE) */
/*
 *  Syntax:
 *      MVOID dbRdGeoDecoderInitialize(MVOID);
 *
 *  Purpose:
 *      Initialize the decoder to assign the space to store the decoded data. The whole memory
 *      space is declared in static mode.
 *
 *  Parameters:
 *      None.
 *
 *  Return Values
 *      None.
 */
MVOID dbRdGeoDecoderInitialize(MVOID);

#endif    /* end of #ifdef SUPPORT_INPUT_MEMSPACE */

#if defined(SUPPORT_DRAWING_TW)||defined(SUPPORT_RETURN_ONE_SCREENDATA)
/*
 *  Syntax:
 *      pGridShp_st dbRdGeoDataDecoderPoolGet(MVOID);
 *
 *  Purpose:
 *      Get the shape pool which will be used to store the decoded data if necessary.
 *
 *  Parameters:
 *      None.
 *
 *  Return Values
 *      The shape pool.
 */
pGridShp_st dbRdGeoDataDecoderPoolGet(MVOID);
#endif    /* end of #if defined(SUPPORT_DRAWING_TW)||defined(SUPPORT_RETURN_ONE_SCREENDATA) */

/*
 *  Syntax:
 *      pGridAssDecoder_st dbRdGeoDecoderGet(AssDecoder_et eType);
 *
 *  Purpose:
 *      Get the assistant decoder functions according to the given assistant decoder type.
 *
 *  Parameters:
 *      eType
 *          [in] The assistant decoder type.
 *               E_ASSDECODER_RD=0     : the assistant decoder to road shapes without handling.
 *               E_ASSDECODER_GEO      : the assistant decoder to geometry shapes without handling.
 *               E_ASSDECODER_RD_ONCE  : the assistant decoder for road shapes with one-time handling.
 *               E_ASSDECODER_GEO_ONCE : the assistant decoder for geometry shapes with one-time handling.
 *               E_ASSDECODER_RD_TWICE : the assistant decoder for road shapes with twice handling.
 *               E_ASSDECODER_GEO_TWICE: the assistant decoder for geometry shapes with twice handling.
 *
 *  Return Values
 *      The assistant decoder function set.
 */
pGridAssDecoder_st dbRdGeoDecoderGet(AssDecoder_et eType);

/*
 *  Syntax:
 *      S32 dbRdGeoDataDecoder(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
 *                             S32 s32ScaleUnit,U8 u8FilterClass,U8 u8TWFilterClass,pGrid_st psGrid,
 *                             pGridArch_st psGridArch,ShpIdxGet_pfn pfnShpIdxGet,
 *                             VerCountGet_pfn pfnVerCountGet,NameGet_pfn pfnNameGet,
 *                             IsCoveredGrid_pfn pfnIsCoveredGrid,PMVOID pvClientData,
 *                             PMVOID pvHandler,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Decode the shape data and then store the decoded data at the shape pool.
 *
 *  Parameters:
 *      bReferBoundary
 *          [in] Depict whether to refer to the input bounding box.
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32ScaleUnit
 *          [in] The scale unit.
 *      u8FilterClass
 *          [in] The filter of the road/geometry level.
 *      u8TWFilterClass
 *          [in] The filter of the road/geometry level for twice handling.
 *               This parameter is not referred inside this function body.
 *      psGrid
 *          [in] The grid data.
 *      psGridArch
 *          [in] The grid architecture.
 *      pfnShpIdxGet
 *          [in] The callback function to get the class and shape index of the road/geometry grid.
 *      pfnVerCountGet
 *          [in] The callback function to get the number of vertices of the road/geometry shape.
 *      pfnNameGet
 *          [in] The callback function to get the names of the road/geometry shape.
 *      pfnIsCoveredGrid
 *          [in] The callback function to check whether the shape covers the whole grid.
 *      pvClientData
 *          [in] The caller's client data.
 *               This parameter is not referred inside this function body.
 *      pvHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *               This parameter is not referred inside this function body.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values:
 *      The number of decoded shapes.
 */
S32 dbRdGeoDataDecoder(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,S32 s32ScaleUnit,
                       U8 u8FilterClass,U8 u8TWFilterClass,pGrid_st psGrid,pGridArch_st psGridArch,
                       ShpIdxGet_pfn pfnShpIdxGet,VerCountGet_pfn pfnVerCountGet,NameGet_pfn pfnNameGet,
                       IsCoveredGrid_pfn pfnIsCoveredGrid,PMVOID pvClientData,PMVOID pvHandler,
                       pDBErrCode_et peErrCode);

/*
 *  Syntax:
 *      S32 dbRdGeoDataDecoderHandler(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
 *                                    S32 s32ScaleUnit,U8 u8FilterClass,U8 u8TWFilterClass,pGrid_st psGrid,
 *                                    pGridArch_st psGridArch,ShpIdxGet_pfn pfnShpIdxGet,
 *                                    VerCountGet_pfn pfnVerCountGet,NameGet_pfn pfnNameGet,
 *                                    IsCoveredGrid_pfn pfnIsCoveredGrid,PMVOID pvClientData,
 *                                    PMVOID pvHandler,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Decode the shape data and then handle the decoded data via the given callback function.
 *
 *  Parameters:
 *      bReferBoundary
 *          [in] Depict whether to refer to the input bounding box.
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32ScaleUnit
 *          [in] The scale unit.
 *      u8FilterClass
 *          [in] The filter of the road/geometry level.
 *      u8TWFilterClass
 *          [in] The filter of the road/geometry level for twice handling.
 *               This parameter is not referred inside this function body.
 *      psGrid
 *          [in] The grid data.
 *      psGridArch
 *          [in] The grid architecture.
 *      pfnShpIdxGet
 *          [in] The callback function to get the class and shape index of the road/geometry grid.
 *      pfnVerCountGet
 *          [in] The callback function to get the number of vertices of the road/geometry shape.
 *      pfnNameGet
 *          [in] The callback function to get the names of the road/geometry shape.
 *      pfnIsCoveredGrid
 *          [in] The callback function to check whether the shape covers the whole grid.
 *      pvClientData
 *          [in] The caller's client data.
 *      pvHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values:
 *      The number of decoded shapes.
 */
S32 dbRdGeoDataDecoderHandler(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
                              S32 s32ScaleUnit,U8 u8FilterClass,U8 u8TWFilterClass,pGrid_st psGrid,
                              pGridArch_st psGridArch,ShpIdxGet_pfn pfnShpIdxGet,
                              VerCountGet_pfn pfnVerCountGet,NameGet_pfn pfnNameGet,
                              IsCoveredGrid_pfn pfnIsCoveredGrid,PMVOID pvClientData,PMVOID pvHandler,
                              pDBErrCode_et peErrCode);

#ifdef SUPPORT_DRAWING_TW
/*
 *  Syntax:
 *      S32 dbRdGeoDataDecoderTWHandler(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
 *                                      S32 s32ScaleUnit,U8 u8FilterClass,U8 u8TWFilterClass,
 *                                      pGrid_st psGrid,pGridArch_st psGridArch,ShpIdxGet_pfn pfnShpIdxGet,
 *                                      VerCountGet_pfn pfnVerCountGet,NameGet_pfn pfnNameGet,
 *                                      IsCoveredGrid_pfn pfnIsCoveredGrid,PMVOID pvClientData,
 *                                      PMVOID pvHandler,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Decode the shape data and then handle the decoded data via the given callback function twice.
 *
 *  Parameters:
 *      bReferBoundary
 *          [in] Depict whether to refer to the input bounding box.
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      s32ScaleUnit
 *          [in] The scale unit.
 *      u8FilterClass
 *          [in] The filter of the road/geometry level.
 *      u8TWFilterClass
 *          [in] The filter of the road/geometry level for twice handling.
 *      psGrid
 *          [in] The grid data.
 *      psGridArch
 *          [in] The grid architecture.
 *      pfnShpIdxGet
 *          [in] The callback function to get the class and shape index of the road/geometry grid.
 *      pfnVerCountGet
 *          [in] The callback function to get the number of vertices of the road/geometry shape.
 *      pfnNameGet
 *          [in] The callback function to get the names of the road/geometry shape.
 *      pfnIsCoveredGrid
 *          [in] The callback function to check whether the shape covers the whole grid.
 *      pvClientData
 *          [in] The caller's client data.
 *      pvHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values:
 *      The number of decoded shapes.
 */
S32 dbRdGeoDataDecoderTWHandler(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
                                S32 s32ScaleUnit,U8 u8FilterClass,U8 u8TWFilterClass,pGrid_st psGrid,
                                pGridArch_st psGridArch,ShpIdxGet_pfn pfnShpIdxGet,
                                VerCountGet_pfn pfnVerCountGet,NameGet_pfn pfnNameGet,
                                IsCoveredGrid_pfn pfnIsCoveredGrid,PMVOID pvClientData,PMVOID pvHandler,
                                pDBErrCode_et peErrCode);
#endif    /* end of #ifdef SUPPORT_DRAWING_TW */

/*
 *  Syntax:
 *      S32 dbBoundaryPGDecoder(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
 *                              U8 u8FilterClass,pCoveredGrid_st psCoveredGrid,
 *                              PMVOID pvClientData,PMVOID pvHandler,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Decode the boundary polygon shape data and then store the decoded data at the shape pool.
 *
 *  Parameters:
 *      bReferBoundary
 *          [in] Depict whether to refer to the input bounding box.
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      u8FilterClass
 *          [in] The filter of the road/geometry level.
 *      psCoveredGrid
 *          [in] The boundary data which covers the whole grid.
 *      pvClientData
 *          [in] The caller's client data.
 *               This parameter is not referred inside this function body.
 *      pvHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *               This parameter is not referred inside this function body.
 *      peErrCode
 *          [out] The error code.
 *
 *  Return Values:
 *      The number of decoded shapes.
 */
S32 dbBoundaryPGDecoder(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
                        U8 u8FilterClass,pCoveredGrid_st psCoveredGrid,
                        PMVOID pvClientData,PMVOID pvHandler,pDBErrCode_et peErrCode);

/*
 *  Syntax:
 *      S32 dbBoundaryPGDecoderHandler(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
 *                                     U8 u8FilterClass,pCoveredGrid_st psCoveredGrid,
 *                                     PMVOID pvClientData,PMVOID pvHandler,pDBErrCode_et peErrCode);
 *
 *  Purpose:
 *      Decode the boundary polygon shape data and then handle the decoded data via the given
 *      callback function.
 *
 *  Parameters:
 *      bReferBoundary
 *          [in] Depict whether to refer to the input bounding box.
 *      s32LX
 *          [in] The given left x coordinate of the bounding box.
 *      s32BY
 *          [in] The given bottom y coordinate of the bounding box.
 *      s32RX
 *          [in] The given right x coordinate of the bounding box.
 *      s32TY
 *          [in] The given top y coordinate of the bounding box.
 *      u8FilterClass
 *          [in] The filter of the road/geometry level.
 *      psCoveredGrid
 *          [in] The boundary data which covers the whole grid.
 *      pvClientData
 *          [in] The caller's client data.
 *      pvHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *
 *  Return Values:
 *      The number of decoded shapes.
 */
S32 dbBoundaryPGDecoderHandler(MBOOL bReferBoundary,S32 s32LX,S32 s32BY,S32 s32RX,S32 s32TY,
                               U8 u8FilterClass,pCoveredGrid_st psCoveredGrid,
                               PMVOID pvClientData,PMVOID pvHandler,pDBErrCode_et peErrCode);

#ifdef SUPPORT_DRAWING_TW
/*
 *  Syntax:
 *      MVOID dbRdGeoDecoder2Run(pGridShp_st psGridShp,PMVOID pvClientData,PMVOID pvHandler);
 *
 *  Purpose:
 *      Do the 2nd run handling for the stored shape data.
 *
 *  Parameters:
 *      psGridShp
 *          [in] The shape pool.
 *      pvClientData
 *          [in] The caller's client data.
 *      pvHandler
 *          [in] The callback function to handle the matched mapview shape data.
 *
 *  Return Values:
 *      None.
 */
MVOID dbRdGeoDecoder2Run(pGridShp_st psGridShp,PMVOID pvClientData,PMVOID pvHandler);
#endif    /* end of #ifdef SUPPORT_DRAWING_TW */

#if defined(FOR_UNIT_TEST)&&defined(SUPPORT_RETURN_ONE_SCREENDATA)
/*
 *  Syntax:
 *      MVOID dbRdGeoDecoderGetScreenParams(PS32 ps32NumOfShps,PS32 ps32NumOfVers,PS32 ps32NumOfNames);
 *
 *  Purpose:
 *      Get the screen parameters, such as number of shapes, vertices and names.
 *
 *  Parameters:
 *      ps32NumOfShps
 *          [out] The number of shapes.
 *      ps32NumOfVers
 *          [out] The number of vertices.
 *      ps32NumOfNames
 *          [out] The number of names.
 *
 *  Return Values:
 *      None.
 */
MVOID dbRdGeoDecoderGetScreenParams(PS32 ps32NumOfShps,PS32 ps32NumOfVers,PS32 ps32NumOfNames);
#endif    /* end of #if defined(FOR_UNIT_TEST)&&defined(SUPPORT_RETURN_ONE_SCREENDATA) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* end of #ifndef DB_RDGEODECODER_H */
