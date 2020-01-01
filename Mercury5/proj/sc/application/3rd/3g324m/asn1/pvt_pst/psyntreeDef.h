/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/


/*
  psyntreeDef

  Database definitions of the syntax trees

  */

#ifndef _PSYNTREE_DEF_H
#define _PSYNTREE_DEF_H

#include "rvtypes.h"
#include "psyntree.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined(RV_DEBUG)
#define RV_PST_DEBUG
#endif


/************************************************************************
 * fmt2Elem
 * Node ID element. Connects between a string field in the ASN to its
 * data.
 * nameOffset   - The offset inside the names buffer
 * dataOffset   - The offset inside the data buffer
 ************************************************************************/
typedef struct
{
    RvUint16    nameOffset;
    RvInt16     dataOffset;
} fmt2Elem;


/************************************************************************
 * fmt2Struct
 * ASN.1 information structure
 * This struct holds all the pointers to an ASN.1 compiled file.
 * dictionary       - Strings dictionary. Contains all the strings inside
 *                    the specific ASN.1 description
 * data             - The actual data, holding the ASN.1 types and
 *                    information about them
 * table            - The link between the dictionary and the data
 * dictionarySize   - The size of the dictionary
 * dataSize         - The size of the data
 * tableSize        - The size of the linkage table
 * dataEnd          - Pointer to the boundary of the data array. Used for
 *                    fast sanity checks
 ************************************************************************/
typedef struct
{
    char*     dictionary;
    RvUint32* data;
    fmt2Elem* table;
    int       dictionarySize;
    int       dataSize;
    RvSize_t  tableSize;
    RvUint32* dataEnd;
} fmt2Struct;


/************************************************************************
 * synStruct
 * Syntax Tree definition structure.
 * Hold the information to identify the structure of ASN.1 messages.
 * syntaxName   - Name of the syntax used - this one is for debugging...
 * syntax       - Syntax definition to use
 * rootNodeId   - Node ID of the root
 * rootNameId   - Name ID of the root
 ************************************************************************/
typedef struct
{
    fmt2Struct* syntax;

    RvPstNodeId rootNodeId;
    RvInt32     rootNameId;

#if defined(RV_PST_DEBUG)
    RvChar      syntaxName[128];
#endif
} synStruct;



/* each entry contains the number of ones in
 the binary representation of its index */
extern unsigned char ones[];




/************************************************************************
 *
 *                          TYPES/FIELDS syntax
 *
 ************************************************************************/


/* Flag values for stNodeExt */
typedef enum
{
    synFlagFromAbsent    = 0x1,
    synFlagToAbsent      = 0x2
} synFlagsEnum;



/***********************************************************************
 * stNodeExt
 * Syntax node definition
 *
 * 4 byte - control
 * 4 byte - control (ext)
 * ... (optional)
 *
 * (NOTE: it is assumed that all ID's are 16 bits long!)
 *
 *  ------------------------------------------------------------------------------------------
 * |tag   | type |is  |  tag  | ofId  |fromId | from  |  to   |flags|  num of    | num of Opt |
 * |Class |      |Exte|present|present|present|present|present|     |   childs   | bef ext    |
 *  ------+------+----+-------+-------+-------+-------+-------+-----+------------+------------
 * |  3   |  5   | 1  |   1   |   1   |   1   |   1   |   1   |  2  |      8     |     8      |
 *  ------------------------------------------------------------------------------------------
 *  ------------------------------------------------------------------------------------------
 * | num of      |                                                                            |
 * |  bef ext    |                                                                            |
 *  -------------+----------------------------------------------------------------------------
 * |     8       |                                                                            |
 *  ------------------------------------------------------------------------------------------
 *
 * control  format (bits are numbered LSB first)
 * 1-3   - tagClass
 * 4-8   - type
 * 9-9   - isExtension
 * 10-10 - tag present
 * 11-11 - ofId present
 * 12-12 - fromId present
 * 13-13 - from present
 * 14-14 - to present
 * 15-16 - flags
 * 17-24 - num of childs
 * 25-32 - num of optionals before ext
 *
 * control (ext) format (optional - exists only when isExtension==1)
 * 1-24 - empty
 * 25-32 - num of childs before ext
 *
 * for each present field another long is allocated so if tag is present, ofId is not present
 * and fromId is present then fromId will be in ((long *)(ptr))[3] since [0]&[1] is the control
 * and [2] is the tag.
 ***********************************************************************/
typedef RvUint32 stNodeExt;

/* ACCESS macros */
#define m_tagClass(p)           (((*(p))&7))
#define m_type(p)               (((*(p))>>3)&0x1f)
#define m_isExtension(p)        (((*(p))>>8)&1)
#define m_flags(p)              (synFlagsEnum)(((*(p))>>14)&3)
#define m_numOfChilds(p)        (((*(p))>>16)&0xff)
#define m_tag(p)                ( (((*(p))>>9)&1) ? (int)(*((p)+ones[(((*(p))>>9)&1)])) : (int)-1)
#define m_ofId(p)               ( (((*(p))>>10)&1) ? (int)(*((p)+ones[(((*(p))>>9)&3)])) : (int)-1)
#define m_fromId(p)             ( (((*(p))>>11)&1) ? (int)(*((p)+ones[(((*(p))>>9)&7)])) : (int)-1)
#define m_from(p)               ( (((*(p))>>12)&1) ? *((p)+ones[(((*(p))>>9)&15)]) : 0)
#define m_to(p)                 ( (((*(p))>>13)&1) ? *((p)+ones[(((*(p))>>9)&31)]) : 0)
#define m_numOptBeforeExt(p)    (((*(p))>>24)&0xff)
#define m_childsBeforeExt(p)    (((*((p)+1))&0xff))



/***********************************************************************
 * stChildExt
 * Field node definition (stored inside SEQUENCEs and CHOICEs)
 *
 * 4 byte - control & defaultId
 * 4 byte - fieldId & structId
 * 4 byte (optional) - enumeration value
 *
 * (NOTE: it is assumed that all ID's are 16 bits long!)
 *
 *  -----------------------------------------------------------
 * | is | is | is | is    | enum  |           | defaultId      |
 * |Defa|Opti|Exte|Special|present|           |                |
 *  -----------------------------------------------------------
 * | 1  | 1  | 1  | 3     | 1     |     9     | 16             |
 *  -----------------------------------------------------------
 *
 *  -------------------------------
 * |    fieldId     |   structId   |
 * |                |              |
 *  -------------------------------
 * |       16       |      16      |
 *  -------------------------------
 *
 * control format (bits are numbered LSB first)
 * 1-1   - isDefault
 * 2-2   - isOptional
 * 3-3   - isExtended
 * 4-6   - isSpecial
 * 7-7   - enuerationValue present
 * 17-32 - defaultId
 *
 * the second long format is
 * 2 byte - fieldId
 * 2 byte - structId
 *
 *  The length character before the new structure will have the
 * original length in the low 16 bits and the new in the high.
 ***********************************************************************/
typedef RvUint32 stChildExt;

/* ACCESS macros */
#define m_defaultId(p)          (((*(p))&0xffff0000)>>16)
#define m_fieldId(p)            (((*((p)+1)&0x0000ffff)))
#define m_structId(p)           (((*((p)+1))&0xffff0000)>>16)
#define m_isDefault(p)          (((*(p))&1))
#define m_isOptional(p)         (((*(p))>>1)&1)
#define m_isExtended(p)         (((*(p))>>2)&1)
#define m_isSpecial(p)          (((*(p))>>3)&7)
#define m_enumerationValue(p)   ( (((*(p))>>6)&1) ? (int)(*((p)+2)) : (int)-1)


/***********************************************************************
 * Association table
 * The values of an association table contains the amount of values
 * inside it, followed by the values themselves
 *
 * 4 byte   - Number of items in the table
 ***********************************************************************/
typedef RvUint32 stAssociationTable;

#define m_ATNumObjects(p)   (*(p))
#define m_ATTable(p)        ((p)+1)
#define m_ATObjectSize(p)   (sizeof(stAssociationTableValue) * 2)

/***********************************************************************
 * Association table field value
 * The values of an association table sit right after a 32bit value of the
 * number of values in the table.
 * Each such value is an encoding option for the object
 *
 * 4 byte   - Syntax Object Id of the given type to encode/decode
 * 4 byte   - Syntax value associated with the given type
 *            The data in this position is of type stValueTree
 ***********************************************************************/
typedef RvUint32 stAssociationTableValue;

#define m_ATValueObject(p)  (*(p))
#define m_ATValueValue(p)   (*((p)+1))


/***********************************************************************
 * Default values - trees
 * Default values in the ASN.1 are stored in 8 bytes:
 *
 * first long (bits are numbered LSB first)
 * 1-30  - type reference
 * 31-32 - node type (integer, string, subtree)
 *
 * the second long format is
 * 4 byte - value
 ***********************************************************************/
typedef RvUint32 stValueTree;

/* ACCESS macros */
#define m_valueTreeTypeReference(p) (((*(p))&0x3fffffff))
#define m_valueTreeIsString(p)      (((*(p))>>30))
#define m_valueTreeValue(p)         (((*((p)+1))))


/***********************************************************************
 * Default values - nodes
 * Default values in the ASN.1 are stored in 8 bytes:
 *
 * first long (bits are numbered LSB first)
 * 1-30  - field's name
 * 31-32 - node type (integer, string, subtree)
 *
 * the second long format is
 * 4 byte - value
 ***********************************************************************/
typedef RvUint32 stValueNode;

/* ACCESS macros */
#define m_valueNodeFieldName(p)         (((*(p))&0x3fffffff))
#define m_valueNodeIsString(p)          (((*(p))>>30))
#define m_valueNodeValue(p)             (((*((p)+1))))


/* Definitions of errors in the pst */
#define RV_PST_ERROR_UNKNOWN (RvPstNodeId)RV_ERROR_UNKNOWN
#define RV_PST_ERROR_UNDEFINED_TYPE (RvPstNodeId)-1905



#ifdef __cplusplus
}
#endif

#endif  /* _PSYNTREE_DEF_H */



