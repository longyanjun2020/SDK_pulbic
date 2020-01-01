/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */
/** 
 * @file ajms_ab.h
 * Application Browse ACI
 */

#ifndef AJMS_AB_HEADER
#define AJMS_AB_HEADER

#ifdef __cplusplus
extern "C"{
#endif

#include "aj_type.h"
#include "ajms_common.h"

/** @addtogroup Application_Repository 
 *  @{ 
 */

/*  
 *  Interfaces listed in the group are used for application browsing, 
 *  including these functionalities:
 *      - list/manage categories.
 *      - list/manage MIDlet suites in a specified category.
 *      - list MIDlets in a specified MIDlet suite.
 *      - list MIDlet suites' JAD and manifest content.
 *      - Parse one JAD and manifest content to get certain property.
 *      - Retrieve MIDlet suite identifier by name and vendor.
 *      - Retrieve MIDlet and MIDlet suite icon data.
 *      .
 *
 */
/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/

/** 
 * @addtogroup MIDlet_Suite_Raw_Data_ACI MIDlet Suite Raw Data ACI
 * An interface for retrieving raw data of a MIDlet suite.
 * This interface is implemented in AJSC. 
 *
 * @par Include file 
 * \#include ajms_ab.h
 * @{
 */
/** 
 * Application descriptor type: JAD
 */
#define AJMS_DESC_TYPE_JAD        (1)
/** 
 * Application descriptor type: JAR manifest 
 */
#define AJMS_DESC_TYPE_MANIFEST   (2)
/** @} */

/** 
 * @addtogroup Application_Category_ACI Application Category ACI
 * An interface for manipulating the application category data of the AJSC application repository.
 * This interface is implemented in AJSC. 
 *
 * @par Include file 
 * \#include ajms_ab.h
 * @{
 */
 
/** 
 * The identifier of the default unfiled category.
 * The name of this category is "unfiled."
 * This predetermined category cannot be renamed nor deleted.
 */
#define AJMS_DEFAULT_CATEGORY_ID_UNFILED          (0)
/** 
 * The identifier of the default pre-installed category.
 * The name of this category is "preinstall."
 * This predetermined category cannot be renamed nor deleted.
 */
#define AJMS_DEFAULT_CATEGORY_ID_PREINSTALLED     (1)


/**
 * The structure type for containing information of a category.
 */
typedef struct _AJMS_Category
{
    /** 
     * The identifier of the category. 
     */
    AJ_S32  id;
    /** 
     * The category name.\ A UTF-8 encoded NUL-terminated string.
     */
    AJ_U8   name[AJMS_MAX_ENTRY_NAME_LENGTH+1];
    /** 
     * A flag indicating whether or not the category is default (immutable).
     */
    AJ_BOOL isDefault;
}
AJMS_Category;

/** @} */

/** 
 * @addtogroup MIDlet_Suite_Browse_ACI MIDlet Suite Browse ACI
 * An interface for listing the applications in a category of the AJSC Java application repository.
 * This interface is implemented in AJSC. 
 *
 * @par Include file 
 * \#include ajms_ab.h
 * @{
 */

/** 
 * Sort type: By name of MIDlet suite.
 */
#define AJMS_SORT_BY_NAME                (1)
/** 
 * Sort type: By vendor name of MIDlet suite.
 */
#define AJMS_SORT_BY_VENDOR_NAME         (2)
/** 
 * Sort type: By name of category.
 */
#define AJMS_SORT_BY_CATEGORY            (3)
/** 
 * Sort type: By application storage type.
 */
#define AJMS_SORT_BY_TYPE                (4)
/** 
 * Sort type: By size of MIDlet-suite.
 */
#define AJMS_SORT_BY_SIZE                (6)
/** 
 * Sort type: By installation time of MIDlet-suite. 
 */
#define AJMS_SORT_BY_INSTALL_TIME        (7)

/**
 * The identifier representing the MIDlet suite icon for use with ajms_ab_getIcon().
 */
#define AJMS_SUITE_ICON_ID               (0xFF)

/** 
 * Application storage type 1.\ Preinstalled applications. 
 * This indicates the type of the applications installed by Preinstall ToolKit.
 */
#define AJMS_APPLICATION_TYPE_1          (0x01)

/** 
 * Application storage type 2.\ Applications protected by AJSC.
 * This indicates the type of the applications installed via ajms_ota_install().
 */
#define AJMS_APPLICATION_TYPE_2          (0x02)

/** 
 * Application storage type 3.\ Applications protected by device.
 * This indicates the type of the applications installed via ajms_ota_installEx().
 */
#define AJMS_APPLICATION_TYPE_3          (0x03)

#ifdef SUPPORT_FORBIDDEN_DELETE_APPLICATION_TYPE_4
/** \brief Application Type 4 for forbidden deleting */
#define AJMS_APPLICATION_TYPE_4          (0x04)
#endif
/**
 * The structure type for containing information of a MIDlet suite.
 */ 
typedef struct _AJMS_Suite
{
    /** 
     * The identifier of the MIDlet suite.
     */
    AJ_S32  id;
    /** 
     * The MIDlet suite alias name.\ The string must be UTF-8 encoded NUL-terminated.
     * The alias name can be modified via ajms_ab_setSuiteName() by AMS for any purpose.
     */
    AJ_U8   aliasName[AJMS_MAX_ENTRY_NAME_LENGTH + 1];
    /** 
     * The MIDlet suite name.\ The string must be UTF-8 encoded NUL-terminated.
     * The value of MIDlet-Name attribute is set in this member.
     */
    AJ_U8   suiteName[AJMS_MAX_ENTRY_NAME_LENGTH + 1];
    /** 
     * The MIDlet suite vendor name.\ The string must be UTF-8 encoded NUL-terminated.
     * The value of MIDlet-Vendor attribute is set in this member.
     */
    AJ_U8   vendor[AJMS_MAX_ENTRY_NAME_LENGTH + 1];
    /** 
     * The major version value.
     * The value of MIDlet-Version major field is set in this member.
     */
    AJ_S32  majorVersion;
    /** 
     * The minor version value.
     * The value of MIDlet-Version minor field is set in this member.
     */
    AJ_S32  minorVersion;
    /** 
     * The micro version value.
     * The value of MIDlet-Version micro field is set in this member.
     */
    AJ_S32  microVersion;
    /** 
     * The identifier of the protection domain to which the MIDlet suite belongs.
     * One of the following values is set in this member.
     * - #AJMS_PCS_DOMAIN_UNSPECIFIED
     * - #AJMS_PCS_DOMAIN_MANUFACTURER
     * - #AJMS_PCS_DOMAIN_OPERATOR
     * - #AJMS_PCS_DOMAIN_THIRD_PARTY
     */
    AJ_S32  domainId;
    /** 
     * The identifier of the category to which the MIDlet suite belongs.
     */
    AJ_U8  categoryId;
    /** 
     * The MIDlet suite storage type.
     * One of the following values is set in this member.
     * - #AJMS_APPLICATION_TYPE_1
     * - #AJMS_APPLICATION_TYPE_2
     * - #AJMS_APPLICATION_TYPE_3
     */
    AJ_S32 type;
    /** 
     * The total size in bytes of the MIDlet suite. 
     */
    AJ_U32  size;
    /** 
     * The number of MIDlets in the MIDlet suite.
     */
    AJ_U8  numOfMidlet;
    /**
     * The relative order of the MIDlet suite installation time.
     */
    AJ_S16  order;
}
AJMS_Suite;
/** @} */

/** 
 * @addtogroup MIDlet_Browse_ACI MIDlet Browse ACI
 * An interface for listing MIDlets in a MIDlet suite installed in the AJSC Java application repository.
 * This interface is implemented in AJSC. 
 *
 * @par Include file 
 * \#include ajms_ab.h
 * @{
 */

/** 
 * The data structure type for containing attributes of a MIDlet.
 */
typedef struct _AJMS_Midlet
{
    /** 
     * The name field of the MIDlet-&lt;n&gt; attribute.
     */
    AJ_U8 name[AJMS_MAX_ENTRY_NAME_LENGTH + 1];
    /** 
     * The icon field of the MIDlet-&lt;n&gt; attribute.
     */
    AJ_U8 icon[AJMS_MAX_ENTRY_NAME_LENGTH + 1];
    /** 
     * The class field of the MIDlet-&lt;n&gt; attribute.
     */
    AJ_U8 mainClass[AJMS_MAX_ENTRY_CLASS_LENGTH + 1]; 
}
AJMS_Midlet;

/** @} */

/*-----------------------------------------------------------------------------
 * Global Function Prototype
 *----------------------------------------------------------------------------*/

/** 
 * @addtogroup Application_Category_ACI
 * @{
 */

/**
 *        Gets the number of the categories stored in the AJSC Java application repository.
 * @return
 *        The number of the categories.
 *
 * Call this function to get the number of the categories stored in the AJSC Java application repository. 
 * 
 * If AJSC supports application category, at least the following two categories exist:
 *  - "unfiled" category (#AJMS_DEFAULT_CATEGORY_ID_UNFILED)
 *  - "preinstall" category (#AJMS_DEFAULT_CATEGORY_ID_PREINSTALLED)
 *  .
 *
 * If AJSC does not support application category, there is always one and only one dummy category named "none."
 * In this case the return value is always 1.
 */
AJ_S32 ajms_ab_getCategoryListCount( void );

/**
 *        Gets the categories stored in the AJSC Java application repository.
 * @param categoryArray
 *        A pointer to an #AJMS_Category array to receive categories stored in the AJSC Java application repository.
 *        The number of array elements must be equal to or greater than the return value of ajms_ab_getCategoryListCount().
 * @return 
 *        The number of categories this function has put in the array <i>categoryArray</i>.
 *
 * If AJSC does not support category, a dummy category named "none" is passed.
 */
AJ_S32 ajms_ab_getCategoryList( AJMS_Category *categoryArray );

/**
 *        Gets the identifier of a category by category name.
 * @param name
 *        A pointer to the UTF-8 encoded NUL-terminated  string representing the category name.
 *
 * @retval "A value of 0 or greater" indicating the category identifier.
 * @retval #AJMS_ERR_ID_NOT_EXIST    if the category designated by <i>name</i> does not exist.
 */
AJ_S32 ajms_ab_getCategoryId( const AJ_U8* name );

/**
 *        Adds a category to the AJSC Java application repository.
 * @param name
 *        A pointer to the UTF-8 encoded NUL-terminated  string representing the category name.
 *
 * @retval "A value of 0 or greater"     indicating the identifier of the added category.
 * @retval #AJMS_ERR_ENTRY_ALREADY_EXIST if a category with the specified name already exists.
 * @retval #AJMS_ERR_FILE_FULL           if the total number of categories already has reached the maximum of 20.
 * @retval #AJMS_ERR_NOT_SUPPORT         if AJSC does not support category.
 */
AJ_S32 ajms_ab_addCategory( const AJ_U8* name );

/**
 *         Renames an existing category in the AJSC Java application repository.
 * @param  categoryId
 *         The identifier of the category to be renamed.
 * @param  name
 *         A pointer to the UTF-8 encoded NUL-terminated  string representing the new category name.
 *
 * @retval #AJMS_ERR_NONE                if the function succeeds.
 * @retval #AJMS_ERR_ENTRY_ALREADY_EXIST if a category with the specified new <i>name</i> already exists.
 * @retval #AJMS_ERR_ID_NOT_EXIST        if the category indicated by <i>categoryId</i> does not exist.
 * @retval #AJMS_ERR_NOT_SUPPORT         if AJSC does not support category.
 * @retval #AJMS_ERR_INVALID_PARAMS      if the name of the category indicated by <i>categoryId</i> is not changeable.
 */
AJ_S32 ajms_ab_renameCategory( const AJ_S32 categoryId, 
                               const AJ_U8* name );

/**
 *         Deletes an existing category in the AJSC Java application repository.
 * @param  categoryId
 *         The identifier of the category to be deleted.
 *
 * @retval #AJMS_ERR_NONE           if the function succeeds.
 * @retval #AJMS_ERR_INVALID_PARAMS if <i>categoryId</i> is not valid.
 * @retval #AJMS_ERR_ID_NOT_EXIST   if the category indicated by <i>categoryId</i> does not exist.
 * @retval #AJMS_ERR_NOT_SUPPORT    if AJSC does not support category.
 * <p>
 * When a category is deleted, all the applications that have been in the deleted category 
 * are bound to the #AJMS_DEFAULT_CATEGORY_ID_UNFILED category.
 */
AJ_S32 ajms_ab_deleteCategory( const AJ_S32 categoryId );

/** @} */

/** 
 * @addtogroup MIDlet_Suite_Browse_ACI
 * @{
 */

/**
 *        Gets the number of MIDlet suites stored in the AJSC Java application repository.
 * @param categoryId
 *        The category identifier. 
 *        A value of -1 can be designated in this parameter to get the number of all the
 *        applications rather than the applications in a specific category.
 *        If AJSC does not support category, this parameter is ignored 
 *        and the number of all the applications in the repository is returned.
 *        See @ref Application_Category_ACI for details of retrieving category identifier.
 * 
 * @retval "A value of 0 or greater" indicating the number of MIDlet suites.
 * @retval #AJMS_ERR_ID_NOT_EXIST    if the category indicated by <i>categoryId</i> does not exist.
 */
AJ_S32 ajms_ab_getSutieListCount( const AJ_S32 categoryId );

/**
 *        Gets the information of the applications stored in the AJSC Java application repository.
 * @param categoryId
 *        The identifier of the category of which application information is to be obtained.
 *        A value of -1 can be designated in this parameter to get the information of all 
 *        applications rather than applications in a specific category.
 *        If AJSC does not support category, this parameter is ignored.
 *        See @ref Application_Category_ACI for details of retrieving category identifier.
 * @param suiteList
 *        A pointer to the #AJMS_Suite array to receive application information.
 *        The number of array elements must be equal to or greater than the return value of ajms_ab_getSutieListCount().
 * @param sortBy
 *        The sort type.
 *        Specify one of the following values:
 *        - 0 (Sorting not required)
 *        - #AJMS_SORT_BY_NAME
 *        - #AJMS_SORT_BY_TYPE
 *        - #AJMS_SORT_BY_VENDOR_NAME
 *        - #AJMS_SORT_BY_CATEGORY
 *        - #AJMS_SORT_BY_SIZE
 *        - #AJMS_SORT_BY_INSTALL_TIME
 *
 * @retval "A value of 0 or greater" representing the number of MIDlet suites this function has put in the <i>suiteList</i> array.
 * @retval #AJMS_ERR_ID_NOT_EXIST    if the category indicated by <i>categoryId</i> does not exist.
 */
AJ_S32 ajms_ab_getSuiteList( const AJ_S32           categoryId, 
                                   AJMS_Suite*      suiteList, 
                             const AJ_S32           sortBy );

/**
 *        Sets the alias name of a MIDlet suite.
 * @param suiteId
 *        The identifier of the MIDlet suite of which alias name is to be set.
 * @param aliasName
 *        A pointer to the UTF-8 encoded NUL-terminated  string representing the new alias name.
 *
 * @retval #AJMS_ERR_NONE         if the function succeeds.
 * @retval #AJMS_ERR_ID_NOT_EXIST if the MIDlet suite specified by <i>suiteID</i> does not exist.
 */
AJ_S32 ajms_ab_setSuiteName( const AJ_S32  suiteId, const AJ_U8* aliasName );

/** @} */

/** 
 * @addtogroup MIDlet_Browse_ACI
 * @{
 */

/**
 *        Gets the number of the MIDlets of an installed MIDlet suite.
 * @param suiteId
 *        The identifier of the MIDlet suite.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 *
 * @retval "A positive value"     indicating the number of MIDlets.
 * @retval #AJMS_ERR_IO_ERROR     if an I/O error occurs.
 * @retval #AJMS_ERR_ID_NOT_EXIST if the MIDlet suite specified by <i>suiteID</i> does not exist.
 */
AJ_S32 ajms_ab_getMidletListCount( const AJ_S32 suiteId );

/**
 *        Gets information of all the MIDlets in a MIDlet suite.
 * @param suiteId
 *        The identifier of the MIDlet suite of which information is to be obtained. 
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param midletArray
 *        A pointer to an #AJMS_Midlet structure array for receiving information of all the MIDlets in the MIDlet suite 
 *        indicated by <i>suiteId</i>.
 *        The number of array elements must be equal to or greater than the return value of ajms_ab_getMidletListCount().
 *
 * @retval #AJMS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_ERR_IO_ERROR
 *         if an I/O error occurs.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if the MIDlet suite specified by <i>suiteID</i> does not exist.
 */
AJ_S32 ajms_ab_getMidletList( const AJ_S32        suiteId, 
                                    AJMS_Midlet*  midletArray );

/** @} */

/** 
 * @addtogroup MIDlet_Suite_Browse_ACI
 * @{
 */

/**
 *        Gets the identifier of the specified application with given MIDlet suite name and MIDlet vendor name.
 * @param suiteName
 *        A pointer to the UTF-8 encoded NUL-terminated string indicating the MIDlet suite name.
 * @param vendorName
 *        A pointer to the UTF-8 encoded NUL-terminated string indicating the MIDlet vendor name.
 *
 * @retval "A positive value" indicating the identifier of the found MIDlet suite.
 * @retval #AJMS_ERR_INVALID_PARAMS if the function fails due to an invalid parameter. 
 * @retval #AJMS_ERR_ID_NOT_EXIST if the function fails because a MIDlet suite specified by the parameters does not exist. 
 *
 * Use this function to get the identifier of the specified application. 
 * According to the MIDP 2.0 spec, the vendor name plus MIDlet suite name should be unique for each different MIDlet suite.
 */
AJ_S32 ajms_ab_getSuiteIdByNameVendor( const AJ_U8* suiteName, 
                                       const AJ_U8* vendorName );

/** @} */

/** 
 * @addtogroup Application_Category_ACI
 * @{
 */

/** 
 *         Binds a MIDlet suite with a category.
 * @param  suiteId
 *         The identifier of the MIDlet suite.
 *         See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param  categoryId
 *         The identifier of the category with which the MIDlet suite is to be bound.
 * @retval #AJMS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if the MIDlet suite specified by <i>suiteID</i> does not exist.
 * @retval #AJMS_ERR_NOT_SUPPORT
 *         if AJSC does not support category.
 * @retval #AJMS_ERR_NOT_ALLOWED
 *         if the specified MIDlet suite is not allowed to change its category.
 *
 * Note that the applications that belong to the #AJMS_DEFAULT_CATEGORY_ID_PREINSTALLED 
 * category cannot be bound with another category.
 * In those cases this function returns #AJMS_ERR_NOT_ALLOWED. 
 */
AJ_S32 ajms_ab_bindSuiteToCategory( const AJ_S32 suiteId, 
                                    const AJ_S32 categoryId );

/** @} */

/** 
 * @addtogroup MIDlet_Suite_Raw_Data_ACI
 * @{
 */

/** 
 *        Gets icon data by application ID.
 * @param suiteId
 *        The identifier of the MIDlet suite.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param iconId
 *        The value indicating the application of which icon is to be obtained.
 *        To get the icon for MIDlet-1 to MIDlet-n, pass 0 to n-1. 
 *        To get the icon for the MIDlet suite, pass #AJMS_SUITE_ICON_ID.
 * @param buffer
 *        A pointer to the buffer for receiving the icon data. 
 *        This parameter can be #AJ_NULL. 
 *        In this case the data is not passed to the caller but the size of the icon data is returned.
 * @param buflen
 *        The length in bytes of the buffer indicated by <i>buffer</i>.
 *
 * @retval "A positive value"     indicating the size of the icon data.
 * @retval "A value of 0"         if the icon does not exist.
 * @retval #AJMS_ERR_ID_NOT_EXIST if <i>suiteId</i> is invalid.
 * @retval #AJMS_ERR_IO_ERROR     if an I/O error occurs when opening or reading the icon data.
 */
AJ_S32 ajms_ab_getIcon( const  AJ_S32 suiteId,
                        const  AJ_S32 iconId,
                               AJ_U8* buffer,
                        const  AJ_S32 buflen );

/** 
 *        Gets complete JAD content of an installed MIDlet suite.
 * @param suiteId
 *        The identifier of the MIDlet suite.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param buffer
 *        A pointer to the buffer for receiving the JAD content. 
 *        This parameter can be #AJ_NULL. 
 *        In this case the data is not passed to the caller but the size of the JAD data is returned.
 * @param buflen
 *        The length in bytes of the buffer indicated by <i>buffer</i>.
 *
 * @retval "A positive value"     indicating the size of the JAD data.
 * @retval "A value of 0"         if the JAD file does not exist.
 * @retval #AJMS_ERR_ID_NOT_EXIST if <i>suiteId</i> is invalid.
 * @retval #AJMS_ERR_IO_ERROR     if an I/O error occurs when opening or reading JAD.
 */
AJ_S32 ajms_ab_getJadFileContent( const AJ_S32 suiteId, 
                                        AJ_U8* buffer, 
                                  const AJ_S32 buflen );

/** 
 *        Gets complete MANIFEST.MF content in the JAR file of an installed MIDlet suite.
 * @param suiteId
 *        The identifier of the MIDlet suite.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param buffer
 *        A pointer to the buffer for receiving the MANIFEST.MF content. 
 *        This parameter can be #AJ_NULL. 
 *        In this case the data is not passed to the caller but the size of the MANIFEST.MF data is returned.
 * @param buflen
 *        The length in bytes of the buffer indicated by <i>buffer</i>.
 *
 * @retval "A positive value"       indicating the size of the MANIFEST.MF data.
 * @retval #AJMS_ERR_ID_NOT_EXIST   if <i>suiteId</i> is invalid.
 * @retval #AJMS_ERR_IO_ERROR       if an I/O error occurs when opening or reading MANIFEST.MF.
 */
AJ_S32 ajms_ab_getManifestFileContent( const AJ_S32 suiteId, 
                                       AJ_U8* buffer, 
                                       const AJ_S32 buflen );

/** 
 *        Parses a complete JAD/MANIFEST.MF to get a MIDlet attribute value.
 * @param desc
 *        A pointer to the buffer holding JAD/MANIFEST.MF content.
 * @param descLen
 *        The length in bytes of the data indicated by <i>desc</i>.
 * @param descType
 *        A value indicating whether to get a JAD descriptor or a MANIFEST.MF descriptor.
 *        Pass either of the following:
 *        - #AJMS_DESC_TYPE_JAD
 *        - #AJMS_DESC_TYPE_MANIFEST
 * @param key
 *        A pointer to the UTF-8 encoded NUL-terminated  string representing the MIDlet attribute name.
 * @param propertyBuf
 *        A pointer to the buffer for receiving the attribute value as a UTF-8 encoded NUL-terminated  string.
 *        This parameter can be #AJ_NULL. 
 *        In this case the value is not passed but the necessary buffer size is returned.
 * @param propertyBuflen
 *        The length in bytes of the buffer indicated by <i>propertyBuf</i>.
 * @return 
 *        - A positive value.
 *          - When <i>propertyBuf</i> is not #AJ_NULL,
 *            the number of characters in the attribute value string stored in <i>propertyBuf</i> is returned.
 *          - When <i>propertyBuf</i> is #AJ_NULL,
 *            the necessary buffer size in bytes for the attribute value is returned.
 *        - #AJMS_ERR_APPKEY_NOT_FOUND<br>
 *          if the attribute designated by <i>key</i> is not found.
 *        - #AJMS_ERR_OUT_OF_RANGE<br>
 *          if the size of the <i>propertyBuf</i> is not enough.
 *
 * It is caller's responsibility to make sure the JAD/MANIFEST.MF fulfills the specification of MIDP2.0 and J2SE. 
 * Passing invalid JAD/MANIFEST.MF to this function leads to an unpredictable result. 
 */
AJ_S32 ajms_ab_getAppDescProperty( const AJ_U8*  desc,
                                   const AJ_S32  descLen,
                                   const AJ_S32  descType,
                                   const AJ_U8*  key,
                                         AJ_U8*  propertyBuf,
                                   const AJ_S32  propertyBuflen );


/**
 *        Gets the URL of the JAD of an installed MIDlet suite.
 * @param suiteId
 *        The identifier of the MIDlet suite.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param errorCode
 *        A pointer to the buffer for receiving the result code of function processing.
 *        One of the following values is put in this buffer.
 *        - #AJMS_ERR_NONE:<br>
 *          The function succeeded.
 *        - #AJMS_ERR_ID_NOT_EXIST:<br> 
 *          The function failed because an illegal identifier was designated.
 *        .
 * @return 
 *        - A pointer to the UTF-8 encoded NUL-terminated  string indicating the JAD URL.
 *          This pointer remains valid until the next call to an ACI function.
 *        - #AJ_NULL<br>
 *          if the function fails.
 *
 * A JAD URL is given during MIDlet suite installation time. 
 * The URL is used by AMS to get the upgrade information for a MIDlet suite. 
 */
const AJ_U8* ajms_ab_getJadUrl( const AJ_S32 suiteId, AJ_S32 *errorCode);

/**
 *        Gets the file path of the JAD of an installed MIDlet suite.
 * @param suiteId
 *        The identifier of the MIDlet suite.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param errorCode
 *        A pointer to the buffer for receiving the result code of function processing.
 *        One of the following values is put in this buffer.
 *        - #AJMS_ERR_NONE:<br>
 *          The function succeeded.
 *        - #AJMS_ERR_ID_NOT_EXIST:<br> 
 *          The function failed because an illegal identifier was designated.
 *        - #AJMS_ERR_FILE_NOT_EXIST:<br>
 *          The function failed because the JAD is in a ROMized virtual directory or the authenticated root is not available.
 *        .
 * @return 
 *        - A pointer to the UTF-8 encoded NUL-terminated  string indicating the JAD file path.
 *          This pointer remains valid until the next call to an ACI function.
 *        - #AJ_NULL<br>
 *          if the function fails.
 */
const AJ_U8* ajms_ab_getJadPath( const AJ_S32 suiteId, AJ_S32 *errorCode );

/**
 *        Gets the file path of the JAR of an installed MIDlet suite.
 * @param suiteId
 *        The identifier of the MIDlet suite.
 *        See @ref MIDlet_Suite_Browse_ACI for details of retrieving MIDlet suite identifier.
 * @param errorCode
 *        A pointer to the buffer for receiving the result code of function processing.
 *        One of the following values is put in this buffer.
 *        - #AJMS_ERR_NONE:<br>
 *          The function succeeded.
 *        - #AJMS_ERR_ID_NOT_EXIST:<br> 
 *          The function failed because an illegal identifier was designated.
 *        - #AJMS_ERR_FILE_NOT_EXIST:<br>
 *          The function failed because the JAR is in a ROMized virtual directory or the authenticated root is not available.
 *        .
 * @return 
 *        - A pointer to the UTF-8 encoded NUL-terminated  string indicating the JAR file path.
 *          This pointer remains valid until the next call to an ACI function.
 *        - #AJ_NULL<br>
 *          if the function fails.
 */
const AJ_U8* ajms_ab_getJarPath( const AJ_S32 suiteId, AJ_S32 *errorCode );

/** @} */ 
/** @} */ 

#ifdef __cplusplus
}
#endif 

#endif /* AJMS_AB_HEADER */
