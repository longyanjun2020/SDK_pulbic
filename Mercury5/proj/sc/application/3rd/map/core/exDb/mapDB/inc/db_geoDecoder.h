/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      db_geoDecoder.h
 *
 * DESCRIPTION
 *      This file provides the local functions to handle class-shape index table,
 *      get the number of vertices and get the names of the geometry shapes.
 *
 * HISTORY
 *      2009.04.21       Mickey Chiang     Initial Version
 *      2009.04.23       Mickey Chiang     Replaced psGrid with psGridArch.
 *      2009.05.05       Mickey Chiang     Added the comments for "else" condition.
 *      2009.05.06       Mickey Chiang     Initialized the local variables.
 *      2009.06.15       Mickey Chiang     Modified the structure of the grid for
 *                                         the reduced DB.
 *      2009.07.14       Mickey Chiang     Added the name cache mechanism.
 *----------------------------------------------------------------------------- 
 */
#ifndef DB_GEODECODER_H
#define DB_GEODECODER_H
/*------------------------------------------------------------------------------
    Local Function
-------------------------------------------------------------------------------*/
/*
 *  Syntax:
 *      S32 _geoShpIdxGet(pGridArch_st psGridArch,U8 u8FilterClass);
 *
 *  Purpose:
 *      Get the class and shape index of the geometry grid. Every grid has a table with class and
 *      class count pairs. This function is used to collect the indexes of the matched classes
 *      the starting shape index for every class and store at sg_as32ClassIdx[] and sg_as32ClsOff[]
 *      respectively.
 *
 *  Parameters:
 *      psGridArch
 *          [in] The grid architecture.
 *      u8FilterClass
 *          [in] The filter of the geometry level.
 *
 *  Return Values:
 *      The number of matched classes.
 */
static S32 _geoShpIdxGet(pGridArch_st psGridArch,U8 u8FilterClass)
{
    S32 i=0;

    /* scan every class pair */
    for(i=0;i<psGridArch->u8ShpClassPairCount;i++)
    {
        if(u8FilterClass<=psGridArch->au8Class[i])    /* found the matched class */
        {
            S32 s32Count=0,s32LastIdx=psGridArch->u8ShpClassPairCount-1;

            for(;;i++)
            {    /* fill in the class index table and offset table after the matched class */
                sg_as32ClassIdx[s32Count]=i;
                sg_as32ClsOff[s32Count++]=MF_ONE_INT16_TO_INT32(psGridArch->au16ClassOffset[i]);
                if(i==s32LastIdx)    /* meet the last class */
                {
                    return s32Count;
                }
                /* else: continue, it doesn't reach the last class */
            }
        }
        /* else: continue, can't find the matched class */
    }
    return 0;
}

/*
 *  Syntax:
 *      S32 _geoVerCountGet(PU8 pu8RawData,PS32 ps32Idx,PMBOOL pbVertex2Bytes);
 *
 *  Purpose:
 *      Get the number of vertices of the geometry shape.
 *
 *  Parameters:
 *      pu8RawData
 *          [in] The raw data of one geometry shape.
 *      ps32Idx
 *          [out] The index to point to the following encoded data of the geometry shape.
 *      pbVertex2Bytes
 *          [out] Depict whether the geometry shape is formed in 2 bytes for every vertex.
 *
 *  Return Values:
 *      The number of vertices.
 */
static S32 _geoVerCountGet(PU8 pu8RawData,PS32 ps32Idx,PMBOOL pbVertex2Bytes)
{
    S32 s32VerCount=0;

    /* get vertex count */
    if(0==(pu8RawData[0]&0x01))    /* use 1 byte to depict (vertex count-2) */
    {
        s32VerCount=((S32)pu8RawData[1])+2;
        (*ps32Idx)=2;
    }
    else    /* use 2 bytes to depict (vertex count-2) */
    {
        s32VerCount=((((S32)pu8RawData[1])<<8)|((S32)pu8RawData[2]))+2;
        (*ps32Idx)=3;
    }
    (*pbVertex2Bytes)=(0x02==(pu8RawData[0]&0x02))?MBOOL_TRUE:MBOOL_FALSE;
    return s32VerCount;
}

#if defined(SUPPORT_RETURN_ONE_SCREENDATA)&&defined(SUPPORT_NAMECACHE)
/*
 *  Syntax:
 *      MVOID _geoNameGet(pOneShpAttri_st psShpAttri,PU8 pu8RawData,pGridArch_st psGridArch,PS32 ps32Idx,
 *                        PU32 pu32Name1ID,PU32 pu32Name2ID,PU32 pu32NameNumID);
 *
 *  Purpose:
 *      Get the names of the geometry shape.
 *
 *  Parameters:
 *      psShpAttri
 *          [out] The geometry shape data which provide the pointers to the names.
 *      pu8RawData
 *          [in] The raw data of one geometry shape.
 *      psGridArch
 *          [in] The grid architecture.
 *      ps32Idx
 *          [out] The index to point to the following encoded data of the geometry shape.
 *      pu32Name1ID
 *          [out] The ID of the name of the geometry shape.
 *      pu32Name2ID
 *          [out] no use for geometry shape.
 *      pu32NameNumID
 *          [out] no use for geometry shape.
 *
 *  Return Values:
 *      None.
 */
static MVOID _geoNameGet(pOneShpAttri_st psShpAttri,PU8 pu8RawData,pGridArch_st psGridArch,PS32 ps32Idx,
                         PU32 pu32Name1ID,PU32 pu32Name2ID,PU32 pu32NameNumID)
{
    /* try to get the Name1 */
    if(0x08==(pu8RawData[0]&0x08))
    {
        if(psGridArch->u8NameIDFlag)    /* use 2 bytes for Name ID */
        {
            (*pu32Name1ID) =(U32)(pu8RawData[(*ps32Idx)++])<<8;
            (*pu32Name1ID)|=(U32)(pu8RawData[(*ps32Idx)++]);
        }
        else    /* use 1 byte for Name ID */
        {
            (*pu32Name1ID)=(U32)(pu8RawData[(*ps32Idx)++]);
        }
        psShpAttri->pu16Name1=&(psGridArch->pu16NameTbl[*pu32Name1ID]);
    }
    else    /* no Name1 */
    {
        (*pu32Name1ID)       =RDGEO_INVALID_ID;
        psShpAttri->pu16Name1=NULL;
    }
    /* For geometry, Name2 and NameNum are both NULL */
    psShpAttri->pu16Name2  =NULL;
    psShpAttri->pu16NameNum=NULL;
    /* For geometry, no name 2 ID and name number ID */
    (*pu32Name2ID)  =RDGEO_INVALID_ID;
    (*pu32NameNumID)=RDGEO_INVALID_ID;
}
#else    /* !defined(SUPPORT_RETURN_ONE_SCREENDATA)||!defined(SUPPORT_NAMECACHE) */
/*
 *  Syntax:
 *      MVOID _geoNameGet(pOneShpAttri_st psShpAttri,PU8 pu8RawData,pGridArch_st psGridArch,PS32 ps32Idx);
 *
 *  Purpose:
 *      Get the names of the geometry shape.
 *
 *  Parameters:
 *      psShpAttri
 *          [out] The geometry shape data which provide the pointers to the names.
 *      pu8RawData
 *          [in] The raw data of one geometry shape.
 *      psGridArch
 *          [in] The grid architecture.
 *      ps32Idx
 *          [out] The index to point to the following encoded data of the geometry shape.
 *
 *  Return Values:
 *      None.
 */
static MVOID _geoNameGet(pOneShpAttri_st psShpAttri,PU8 pu8RawData,pGridArch_st psGridArch,PS32 ps32Idx)
{
    /* try to get the Name1 */
    if(0x08==(pu8RawData[0]&0x08))
    {
        U32 u32NameID=0;

        if(psGridArch->u8NameIDFlag)    /* use 2 bytes for Name ID */
        {
            u32NameID =(U32)(pu8RawData[(*ps32Idx)++])<<8;
            u32NameID|=(U32)(pu8RawData[(*ps32Idx)++]);
        }
        else    /* use 1 byte for Name ID */
        {
            u32NameID=(U32)(pu8RawData[(*ps32Idx)++]);
        }
        psShpAttri->pu16Name1=&(psGridArch->pu16NameTbl[u32NameID]);
    }
    else    /* no Name1 */
    {
        psShpAttri->pu16Name1=NULL;
    }
    /* For geometry, Name2 and NameNum are both NULL */
    psShpAttri->pu16Name2  =NULL;
    psShpAttri->pu16NameNum=NULL;
}
#endif    /* end of #if defined(SUPPORT_RETURN_ONE_SCREENDATA)&&defined(SUPPORT_NAMECACHE) */

/*
 *  Syntax:
 *      MBOOL _geoIsCoveredGrid(PU8 pu8RawData);
 *
 *  Purpose:
 *      Check whether this shape covers the whole grid. This kind of shape is only for
 *      the boundary polygon.
 *
 *  Parameters:
 *      pu8RawData
 *          [in] The raw data of one geometry shape.
 *
 *  Return Values:
 *      The boolean value depicts whether this shape covers the whole grid.
 */
static MBOOL _geoIsCoveredGrid(PU8 pu8RawData)
{
    if(0x04==(pu8RawData[0]&0x04))
    {
        return MBOOL_TRUE;
    }
    else
    {
        return MBOOL_FALSE;
    }
}
#endif    /* end of #ifndef DB_GEODECODER_H */
