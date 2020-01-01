/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2009 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      db_rdDecoder.h
 *
 * DESCRIPTION
 *      This file provides the local functions to handle class-shape index table,
 *      get the number of vertices and get the names of the road.
 *
 * HISTORY
 *      2009.04.21       Mickey Chiang     Initial Version
 *      2009.04.23       Mickey Chiang     Replaced psGrid with psGridArch.
 *      2009.04.28       Mickey Chiang     Fixed the bug which can't display some
 *                                         pedestrian roads.
 *      2009.05.05       Mickey Chiang     Added the comments for "else" condition.
 *      2009.05.06       Mickey Chiang     Initialized the local variables.
 *      2009.06.15       Mickey Chiang     Modified the structure of the grid for
 *                                         the reduced DB.
 *      2009.07.14       Mickey Chiang     Added the name cache mechanism.
 *----------------------------------------------------------------------------- 
 */
#ifndef DB_RDDECODER_H
#define DB_RDDECODER_H
/*------------------------------------------------------------------------------
    Local Function
-------------------------------------------------------------------------------*/
/*
 *  Syntax:
 *      S32 _rdShpIdxGet(pGridArch_st psGridArch,U8 u8FilterClass);
 *
 *  Purpose:
 *      Get the class and shape index of the road grid. Every grid has a table with class and
 *      class count pairs. This function is used to collect the indexes of the matched classes
 *      the starting shape index for every class and store at sg_as32ClassIdx[] and sg_as32ClsOff[]
 *      respectively. It's necessary to handle the these two arrays because the flyover (
 *      E_L_RD_FLYOVER or E_L_RD_FFLYOVER) is set at the different levels from the view and 
 *      data handling.For the view, flyover is regarded as the 4th level (starting from 0), and
 *      for the data handling, it's regarded as the 11st level (starting from 0).
 *
 *  Parameters:
 *      psGridArch
 *          [in] The grid architecture.
 *      u8FilterClass
 *          [in] The filter of the road level.
 *
 *  Return Values:
 *      The number of matched classes.
 */
static S32 _rdShpIdxGet(pGridArch_st psGridArch,U8 u8FilterClass)
{
    S32 i=0,s32Count=0;

    if(E_L_RD_FWALK==u8FilterClass)    /* contain all of classes */
    {
        for(i=0;i<psGridArch->u8ShpClassPairCount;i++)
        {    /* fill in the class index table and offset table */
            sg_as32ClassIdx[s32Count]=i;
            sg_as32ClsOff[s32Count++]=MF_ONE_INT16_TO_INT32(psGridArch->au16ClassOffset[i]);
        }
    }
    else if(u8FilterClass>=E_L_RD_FPHIGHWAY)    /* the filter class range won't contain E_L_RD_FLYOVER or E_L_RD_FFLYOVER */
    {
        for(i=0;i<psGridArch->u8ShpClassPairCount;i++)
        {
            if(u8FilterClass<=psGridArch->au8Class[i])    /* found the matched class */
            {
                S32 s32LastIdx=psGridArch->u8ShpClassPairCount-1;

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
    }
    else    /* the filter class range contains E_L_RD_FLYOVER or E_L_RD_FFLYOVER */
    {
        for(i=0;i<psGridArch->u8ShpClassPairCount;i++)
        {
            if((u8FilterClass!=E_L_RD_FLYOVER)&&(u8FilterClass!=E_L_RD_FFLYOVER))    /* skip flyover classes */
            {
                if(u8FilterClass<=psGridArch->au8Class[i])
                {    /* fill in the class index table and offset table after the matched class */
                    sg_as32ClassIdx[s32Count]=i;
                    sg_as32ClsOff[s32Count++]=MF_ONE_INT16_TO_INT32(psGridArch->au16ClassOffset[i]);
                }
                /* else: continue, the class doesn't meet the filtered one */
            }
            /* else: the road is flyover, so skip this road */
        }
    }
    return s32Count;
}

/*
 *  Syntax:
 *      S32 _rdVerCountGet(PU8 pu8RawData,PS32 ps32Idx,PMBOOL pbVertex2Bytes);
 *
 *  Purpose:
 *      Get the number of vertices of the road shape.
 *
 *  Parameters:
 *      pu8RawData
 *          [in] The raw data of one road.
 *      ps32Idx
 *          [out] The index to point to the following encoded data of the road shape.
 *      pbVertex2Bytes
 *          [out] Depict whether the road shape is formed in 2 bytes for every vertex.
 *
 *  Return Values:
 *      The number of vertices.
 */
static S32 _rdVerCountGet(PU8 pu8RawData,PS32 ps32Idx,PMBOOL pbVertex2Bytes)
{
    S32 s32VerCount=0;

    /* get vertex count */
    if(0==(pu8RawData[0]&0x01))    /* use 7 bits to depict (vertex count-2) */
    {
        s32VerCount=(S32)(pu8RawData[1]&0x7F)+2;
        (*ps32Idx)=2;
    }
    else    /* use 15 bits to depict (vertex count-2) */
    {
        s32VerCount=((((S32)(pu8RawData[1]&0x7F))<<8)|((S32)(pu8RawData[2])))+2;
        (*ps32Idx)=3;
    }
    (*pbVertex2Bytes)=(0x80==(pu8RawData[1]&0x80))?MBOOL_TRUE:MBOOL_FALSE;
    return s32VerCount;
}

#if defined(SUPPORT_RETURN_ONE_SCREENDATA)&&defined(SUPPORT_NAMECACHE)
/*
 *  Syntax:
 *      MVOID _rdNameGet(pOneShpAttri_st psShpAttri,PU8 pu8RawData,pGridArch_st psGridArch,PS32 ps32Idx,
 *                       PU32 pu32Name1ID,PU32 pu32Name2ID,PU32 pu32NameNumID);
 *
 *  Purpose:
 *      Get the names of the road.
 *
 *  Parameters:
 *      psShpAttri
 *          [out] The road shape data which provide the pointers to the names.
 *      pu8RawData
 *          [in] The raw data of one road.
 *      psGridArch
 *          [in] The grid architecture.
 *      ps32Idx
 *          [out] The index to point to the following encoded data of the road shape.
 *      pu32Name1ID
 *          [out] The ID of the name 1 of the road shape.
 *      pu32Name2ID
 *          [out] The ID of the name 2 of the road shape.
 *      pu32NameNumID
 *          [out] The ID of the name number of the road shape.
 *
 *  Return Values:
 *      None.
 */
static MVOID _rdNameGet(pOneShpAttri_st psShpAttri,PU8 pu8RawData,pGridArch_st psGridArch,PS32 ps32Idx,
                        PU32 pu32Name1ID,PU32 pu32Name2ID,PU32 pu32NameNumID)
{
    if(psGridArch->u8NameIDFlag)    /* use 2 bytes for Name ID */
    {    /* try to get Name1 */
        if(0x08==(pu8RawData[0]&0x08))
        {
            (*pu32Name1ID) =(U32)(pu8RawData[(*ps32Idx)++])<<8;
            (*pu32Name1ID)|=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16Name1=&(psGridArch->pu16NameTbl[*pu32Name1ID]);
        }
        else    /* no Name1 */
        {
            (*pu32Name1ID)=RDGEO_INVALID_ID;
            psShpAttri->pu16Name1=NULL;
        }
        /* try to get Name2 */
        if(0x04==(pu8RawData[0]&0x04))
        {
            (*pu32Name2ID) =(U32)(pu8RawData[(*ps32Idx)++])<<8;
            (*pu32Name2ID)|=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16Name2=&(psGridArch->pu16NameTbl[*pu32Name2ID]);
        }
        else    /* no Name2 */
        {
            (*pu32Name2ID)=RDGEO_INVALID_ID;
            psShpAttri->pu16Name2=NULL;
        }
        /* try to get NameNum */
        if(0x02==(pu8RawData[0]&0x02))
        {
            (*pu32NameNumID) =(U32)(pu8RawData[(*ps32Idx)++])<<8;
            (*pu32NameNumID)|=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16NameNum=&(psGridArch->pu16NameTbl[*pu32NameNumID]);
        }
        else    /* no NameNum */
        {
            (*pu32NameNumID)=RDGEO_INVALID_ID;
            psShpAttri->pu16NameNum=NULL;
        }
    }
    else    /* use 1 byte for Name ID */
    {    /* try to get the Name1 */
        if(0x08==(pu8RawData[0]&0x08))
        {
            (*pu32Name1ID)=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16Name1=&(psGridArch->pu16NameTbl[*pu32Name1ID]);
        }
        else    /* no Name1 */
        {
            (*pu32Name1ID)=RDGEO_INVALID_ID;
            psShpAttri->pu16Name1=NULL;
        }
        /* try to get the Name2 */
        if(0x04==(pu8RawData[0]&0x04))
        {
            (*pu32Name2ID)=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16Name2=&(psGridArch->pu16NameTbl[*pu32Name2ID]);
        }
        else    /* no Name2 */
        {
            (*pu32Name2ID)=RDGEO_INVALID_ID;
            psShpAttri->pu16Name2=NULL;
        }
        /* try to get the NameNum */
        if(0x02==(pu8RawData[0]&0x02))
        {
            (*pu32NameNumID)=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16NameNum=&(psGridArch->pu16NameTbl[*pu32NameNumID]);
        }
        else    /* no NameNum */
        {
            (*pu32NameNumID)=RDGEO_INVALID_ID;
            psShpAttri->pu16NameNum=NULL;
        }
    }
}
#else    /* !defined(SUPPORT_RETURN_ONE_SCREENDATA)||!defined(SUPPORT_NAMECACHE) */
/*
 *  Syntax:
 *      MVOID _rdNameGet(pOneShpAttri_st psShpAttri,PU8 pu8RawData,pGridArch_st psGridArch,PS32 ps32Idx);
 *
 *  Purpose:
 *      Get the names of the road.
 *
 *  Parameters:
 *      psShpAttri
 *          [out] The road shape data which provide the pointers to the names.
 *      pu8RawData
 *          [in] The raw data of one road.
 *      psGridArch
 *          [in] The grid architecture.
 *      ps32Idx
 *          [out] The index to point to the following encoded data of the road shape.
 *
 *  Return Values:
 *      None.
 */
static MVOID _rdNameGet(pOneShpAttri_st psShpAttri,PU8 pu8RawData,pGridArch_st psGridArch,PS32 ps32Idx)
{
    U32 u32NameID=0;

    if(psGridArch->u8NameIDFlag)    /* use 2 bytes for Name ID */
    {
        /* try to get Name1 */
        if(0x08==(pu8RawData[0]&0x08))
        {
            u32NameID =(U32)(pu8RawData[(*ps32Idx)++])<<8;
            u32NameID|=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16Name1=&(psGridArch->pu16NameTbl[u32NameID]);
        }
        else    /* no Name1 */
        {
            psShpAttri->pu16Name1=NULL;
        }
        /* try to get Name2 */
        if(0x04==(pu8RawData[0]&0x04))
        {
            u32NameID =(U32)(pu8RawData[(*ps32Idx)++])<<8;
            u32NameID|=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16Name2=&(psGridArch->pu16NameTbl[u32NameID]);
        }
        else    /* no Name2 */
        {
            psShpAttri->pu16Name2=NULL;
        }
        /* try to get NameNum */
        if(0x02==(pu8RawData[0]&0x02))
        {
            u32NameID =(U32)(pu8RawData[(*ps32Idx)++])<<8;
            u32NameID|=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16NameNum=&(psGridArch->pu16NameTbl[u32NameID]);
        }
        else    /* no NameNum */
        {
            psShpAttri->pu16NameNum=NULL;
        }
    }
    else    /* use 1 byte for Name ID */
    {
        /* try to get Name1 */
        if(0x08==(pu8RawData[0]&0x08))
        {
            u32NameID=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16Name1=&(psGridArch->pu16NameTbl[u32NameID]);
        }
        else    /* no Name1 */
        {
            psShpAttri->pu16Name1=NULL;
        }
        /* try to get Name2 */
        if(0x04==(pu8RawData[0]&0x04))
        {
            u32NameID=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16Name2=&(psGridArch->pu16NameTbl[u32NameID]);
        }
        else    /* no Name2 */
        {
            psShpAttri->pu16Name2=NULL;
        }
        /* try to get NameNum */
        if(0x02==(pu8RawData[0]&0x02))
        {
            u32NameID=(U32)(pu8RawData[(*ps32Idx)++]);
            psShpAttri->pu16NameNum=&(psGridArch->pu16NameTbl[u32NameID]);
        }
        else    /* no NameNum */
        {
            psShpAttri->pu16NameNum=NULL;
        }
    }
}
#endif    /* end of #if defined(SUPPORT_RETURN_ONE_SCREENDATA)&&defined(SUPPORT_NAMECACHE) */

/*
 *  Syntax:
 *      MBOOL _rdIsCoveredGrid(PU8 pu8RawData);
 *
 *  Purpose:
 *      Check whether this shape covers the whole grid. This kind of shape is only for
 *      the boundary polygon, so it's impossible to exist at road DB.
 *
 *  Parameters:
 *      pu8RawData
 *          [in] The raw data of one road data.
 *
 *  Return Values:
 *      Must be MBOOL_FALSE because this kind of shape won't appear on road DB.
 */
static MBOOL _rdIsCoveredGrid(PU8 pu8RawData)
{
    return MBOOL_FALSE;
}
#endif    /* end of #ifndef DB_RDDECODER_H */
