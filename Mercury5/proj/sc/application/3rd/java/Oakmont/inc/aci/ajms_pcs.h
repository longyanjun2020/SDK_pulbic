#ifndef _AJMS_PCS_HEADER
#define _AJMS_PCS_HEADER

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @file ajms_pcs.h
 * Permission Control ACI
 */

#include <aj_type.h>


/*
 *
 *  Interfaces listed in the group are used for manage protection domain, 
 *  including these functionalities:
 *
 *  - List all permissions in one protection domain.
 *  - List all permission groups in one protection domain.
 *  - List all relations between the permission groups in one protection domain.
 *  - List all restrictions between the permission groups in one protection domain.
 *  - Change locale string table.
 *  .
 *
 */

/***********************************************************
 * Constant Variable
 ***********************************************************/

/** 
 * @addtogroup Permission_Status_Code 
 * Constants for defining permission settings.
 *
 * @anchor anchor_permission_setting
 * @par "Permission Setting"
 * A permission setting consists of the following three fields:
 * - Permission scope <br>takes one of the following values:
 *   - 0 (The permission is public)
 *   - #AJMS_PCS_ISPRIVATE 
 * - Permission level <br>takes one of the following values:
 *   - #AJMS_PCS_STATE_ALLOWED
 *   - #AJMS_PCS_STATE_USER
 *   - #AJMS_PCS_STATE_NOT_EXIST.
 * - User interaction mode <br>takes one of the following values when the permission level is #AJMS_PCS_STATE_USER:
 *   - #AJMS_PCS_MODE_BLANKET
 *   - #AJMS_PCS_MODE_SESSION
 *   - #AJMS_PCS_MODE_ONESHOT
 *   - #AJMS_PCS_MODE_NO
 * .
 *
 *
 * @par Include file 
 * \#include ajms_pcs.h
 */

/** 
 * @addtogroup Permission_Status_Code
 * @{
 */
 
/**
 * Permission scope: Private.
 *
 * If the permission group is made public, a Java application 
 * can find out all the permission in that group using the 
 * <code>javax.microedition.midlet.MIDlet</code> class <code>checkPermission</code> 
 * method. The private permission group setting cannot be changed by user.
 */
#define AJMS_PCS_ISPRIVATE         (0x1000)

/**
 * Permission level: Allowed.
 *
 * The Java application is allowed to use the feature without confirming with the user.
 * The allowed permission setting cannot be changed by the user.
 */
#define AJMS_PCS_STATE_ALLOWED     (0x100)

/**
 * Permission level: User. 
 *
 * Indicates that the user must be asked whether the Java application is allowed to use a feature.
 * The permission setting can be changed by the user.
 */
#define AJMS_PCS_STATE_USER        (0x200)

/**
 * Permission level: Not exist. 
 *
 * Indicates that the permission for use of the feature does not exist in the protection 
 * domain to which the Java application belongs. 
 * This setting value occurs only when a fatal error occurs.
 */
#define AJMS_PCS_STATE_NOT_EXIST   (0x400)

/**
 * User interaction mode: Blanket mode.
 * 
 * Indicates that if the user allows use of a feature, 
 * the permission is valid while the Java application is running, 
 * and the permission applies thereafter.
 */
#define AJMS_PCS_MODE_BLANKET      (0x1)

/**
 * User interaction mode: Session mode.
 *
 * Indicates that if the user allows use of a feature, the permission is valid
 * during the current Java application session.
 */
#define AJMS_PCS_MODE_SESSION      (0x2)

/**
 * User interaction mode: Oneshot mode.
 * 
 * Indicates that if the user allows use of a feature, the permission is valid only this time.
 */
#define AJMS_PCS_MODE_ONESHOT      (0x4)

/**
 * User interaction mode: No mode.
 * 
 * Indicates that use of the feature is not permitted.
 */
#define AJMS_PCS_MODE_NO           (0x8)

/**
 * User interaction mode: Blanket mode with user grant authority.
 * 
 * The special blanket mode that indicates that user has already granted authority.
 * This mode is only used by ajms_mss_getGroupMode() and ajms_mss_setGroupMode().
 */
#define AJMS_PCS_MODE_BLANKET_GRANTED (0x11)

/** @} */

/** 
 * @addtogroup Protection_Domain_Identifier 
 *
 * @par Include file 
 * \#include ajms_pcs.h
 * @{
 */

/*
 * Same as the PKCS#11 spec. 
 * Java MIDP security domain: 
 * 0 = unspecified (default value), 
 * 1 = manufacturer, 
 * 2 = operator, 
 * 3 = third party
 */
/** 
 * Unspecified (Untrusted) domain.
 */
#define AJMS_PCS_DOMAIN_UNSPECIFIED  (0)
/** 
 * Manufacturer domain.
 */
#define AJMS_PCS_DOMAIN_MANUFACTURER (1)
/** 
 * Operator domain.
 */
#define AJMS_PCS_DOMAIN_OPERATOR     (2)
/** 
 * Third Party domain.
 */
#define AJMS_PCS_DOMAIN_THIRD_PARTY  (3)

/** @} */

/** 
 * @addtogroup Restriction_ACI Permission Restriction ACI
 *
 * @par Include file 
 * \#include ajms_pcs.h
 * @{
 */

/**
 * Permission conflict level: No conflict.
 */
#define AJMS_PCS_CONFLICT_NORMAL     (0)

/**
 * Permission conflict level: Alert message required.
 */
#define AJMS_PCS_CONFLICT_ALERT      (1)

/**
 * Permission conflict level: Mutual exclusion processing required.
 */
#define AJMS_PCS_CONFLICT_EXCLUSIVE  (2)

/** @} */

/***********************************************************
 * Structures
 ***********************************************************/
 
/** 
 * @addtogroup Permission_ACI Permission ACI
 *
 * @par Include file 
 * \#include ajms_pcs.h
 * @{
 */
 
/** 
 * The structure type for containing permission information.
 */
typedef struct _AJMS_Permission
{
    /** 
     * A pointer to the UTF-8 encoded NUL terminated string representing the permission name.
     */
    AJ_U8* name;
    /** 
     * The index of the function group to which this permission belongs. 
     * A value between 0 and the return value of ajms_pcs_getGroupCount() minus 1 is set.
     */
    AJ_S32 group;
} AJMS_Permission;

/** @} */

/** 
 * @addtogroup Function_Group_ACI 
 * @{
 */

/** 
 * The structure type for containing information of a function group.
 * The structure members reflect the GROUPS fields specified in 
 * the PIK function group configuration file described for the function group.
 * See @ref page_pik_permission_group_config_format at @ref PIK_GROUPS for details.
 */
typedef struct _AJMS_DomainGroup
{
    /** 
     * The default permission setting for the function group. 
     * See @ref anchor_permission_setting "Permission Setting" for details of the format of this value.
     */
    AJ_S32  defaultMode;
    /** 
     * The possible permission settings for the function group. 
     * See @ref anchor_permission_setting "Permission Setting" for details of the format of this value.
     * Note that, if the permission level is #AJMS_PCS_STATE_USER, the user interaction mode field can be 
     * a bitwise-OR of the following possible modes.
     *   - #AJMS_PCS_MODE_BLANKET
     *   - #AJMS_PCS_MODE_SESSION
     *   - #AJMS_PCS_MODE_ONESHOT
     *   - #AJMS_PCS_MODE_NO
     *   .
     * 
     */
    AJ_S32  interactiveModes;
    /** 
     * The title for use with the permission confirmation dialog.
     * A pointer to the UTF-8 encoded NUL terminated string containing the title of the 
     * dialog that queries the user of the permission setting.
     */
    AJ_U8*  title;
    /**
     * The message for use with the permission confirmation dialog displayed by JVM.
     * A pointer to the UTF-8 encoded NUL terminated string containing the message of the 
     * dialog displayed by the JVM when it queries the user of the permission setting.
     */
    AJ_U8*  message;
    /** 
     * The message for use with the permission confirmation dialog displayed by AMS.
     * A pointer to the UTF-8 encoded NUL terminated string containing the message of the 
     * dialog displayed by the AMS when it queries the user of the permission setting.
     */
    AJ_U8*  ams;
} AJMS_DomainGroup;

/** @} */

/** 
 * @addtogroup Relation_ACI
 *
 * @par Include file 
 * \#include ajms_pcs.h
 * @{
 */

/** 
 * The structure type for containing information of a relation between two function groups.
 * The structure members reflect the RELATIONS fields specified in 
 * the PIK function group configuration file described for the function group.
 * See @ref page_pik_permission_group_config_format at @ref PIK_RELATIONS for details.
 */
typedef struct _AJMS_DomainRelation
{
    /** 
     * The first function group index. 
     * A value between 0 and the return value of ajms_pcs_getGroupCount() minus 1 is set.
     */
    AJ_S32 group0;
    /** 
     * The first function group permission setting.
     * See @ref anchor_permission_setting "Permission Setting" for details of the format of this value.
     */
    AJ_S32 state0;
    /** 
     * The second function group index. 
     * A value between 0 and the return value of ajms_pcs_getGroupCount() minus 1 is set.
     */
    AJ_S32 group1;
    /** 
     * The permission setting that should be set for the second function group.
     * See @ref anchor_permission_setting "Permission Setting" for details of the format of this value.
     */
    AJ_S32 state1;
} AJMS_DomainRelation;

/** @} */

/** 
 * @addtogroup Restriction_ACI
 * @{
 */

/** 
 * The structure type for containing information of a restriction between two function groups.
 * The structure members reflect the RESTRICTIONS fields specified in 
 * the PIK function group configuration file described for the function group.
 * See @ref page_pik_permission_group_config_format at @ref PIK_RESTRICTION for details.
 */
typedef struct _AJMS_DomainRestriction
{
    /** 
     * The first function group index. 
     * A value between 0 and the return value of ajms_pcs_getGroupCount() minus 1 is set.
     */
    AJ_S32 group0;
    /** 
     * The first function group permission setting. 
     * See @ref anchor_permission_setting "Permission Setting" for details of the format of this value.
     */
    AJ_S32 state0;
    /** 
     * The second function group index. 
     * A value between 0 and the return value of ajms_pcs_getGroupCount() minus 1 is set.
     */
    AJ_S32 group1;
    /** 
     * The second function group permission setting. 
     * See @ref anchor_permission_setting "Permission Setting" for details of the format of this value.
     */
    AJ_S32 state1;
    /** 
     * The conflict level. 
     * #AJMS_PCS_CONFLICT_ALERT or #AJMS_PCS_CONFLICT_EXCLUSIVE is set in this member.
     */
    AJ_S32 conflict;
    /** 
     * The new function group permission setting that should be set for either <i>group0</i> or <i>group1</i>. 
     * This is valid only when the <i>conflict</i> member is #AJMS_PCS_CONFLICT_EXCLUSIVE.
     * See @ref anchor_permission_setting "Permission Setting" for details of the format of this value.
     */
    AJ_S32 state2;
    /** 
     * The title of the permission conflict dialog.
     * A pointer to the UTF-8 encoded NUL terminated string containing the title of the 
     * permission dialog displayed by the JVM when it queries the user of the permission setting.
     */
    AJ_U8* title;
    /** 
     * The message of the permission conflict dialog.
     * A pointer to the UTF-8 encoded NUL terminated string containing the message of the 
     * permission dialog displayed by the JVM when it queries the user of the permission setting.
     */
    AJ_U8* message;
    /** 
     * The first choice for the mutual exclusive permission conflict dialog.
     * A pointer to the UTF-8 encoded NUL terminated string containing the string displayed on the first item of the mutual exclusive choice box.
     */
    AJ_U8* choice0;
    /** 
     * The second choice for the mutual exclusive permission conflict dialog.
     * A pointer to the UTF-8 encoded NUL terminated string containing the string displayed on the second item of the mutual exclusive choice box.
     */
    AJ_U8* choice1;
} AJMS_DomainRestriction;

/** @} */
#ifdef SUPPORT_PCS_FOR_ROMIZED_APP
typedef void (*PermissionQueryCallBack)(const char *);
typedef void (*PermissionResultCallBack)(int);
void ajms_pcs_set_permission_callback(PermissionQueryCallBack querycallback, 
                                      PermissionResultCallBack resultcallback);
#endif
/***********************************************************
 * APIs
 ***********************************************************/

/** 
 * @addtogroup Permission_Control_System_Initialization_ACI
 *
 * @par Include file 
 * \#include ajms_pcs.h
 * @{
 */

/**
 * @internal
 * Initializes the protection domain control system. 
 * @retval #AJMS_ERR_NONE
 *         If the function succeeds.
 * @retval #AJMS_ERR_FILE_NOT_EXIST
 *         if the protection domain file is missing.
 *
 * In most cases, initialization is performed in ajms_init(). 
 * AMS does not need to initialize with this function again. 
 * Inside this function, the AJSC tries to load the ROMized PIK data. 
 * Details about PIK, please refer to @ref page_pik.
 */
AJ_S32 ajms_pcs_init( void );

/**
 * @internal
 *        Finalizes the protection domain control system.
 * @return
 *        #AJMS_ERR_NONE (The function always succeeds.)
 *
 * In most cases, the finalization is done by ajms_fini(). 
 * AMS does not need to finalize with this function again. 
 */
AJ_S32 ajms_pcs_fini( void );
 
/**
 *        Sets the locale string table.
 * @param tableId
 *        The identifier of the string table defined in the PIK configuration file.
 *        See @ref page_pik_config_format at @ref section_pik_cfg_string_table for details.
 *
 * @retval #AJMS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if the function fails due to an invalid identifier.
 *         If this value is returned, check @ref section_pik_cfg_string_table for setting up the locale string table.
 *
 * The string table should be defined in the PIK configuration file. 
 * For example, if the PIK configuration file contains <code>"StringTable-2: input/cn.res"</code>, 
 * the AMS can use that string table by passing 2 in the <i>tableId</i> parameter.
 */
AJ_S32 ajms_pcs_setStringTable( AJ_S32 tableId );

/** @} */

/** 
 * @addtogroup Permission_ACI
 * @{
 */

/**
 *        Get the number of permissions in a protection domain.
 * @param domainId
 *        The domain identifier. One of the following values should be passed here.
 *        - #AJMS_PCS_DOMAIN_UNSPECIFIED 
 *        - #AJMS_PCS_DOMAIN_MANUFACTURER 
 *        - #AJMS_PCS_DOMAIN_OPERATOR
 *        - #AJMS_PCS_DOMAIN_THIRD_PARTY
 *        .
 * @retval "A value of 0 or greater" representing the number of permissions in the protection domain.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if the function fails due to an invalid domain identifier.
 */
AJ_S32 ajms_pcs_getPermissionCount( AJ_S32 domainId );

/**
 *        Gets information of a permission in a protection domain.
 * @param domainId
 *        The domain identifier. One of the following values should be passed here.
 *        - #AJMS_PCS_DOMAIN_UNSPECIFIED 
 *        - #AJMS_PCS_DOMAIN_MANUFACTURER 
 *        - #AJMS_PCS_DOMAIN_OPERATOR
 *        - #AJMS_PCS_DOMAIN_THIRD_PARTY
 *        .
 * @param permId
 *        The permission index. 
 *        The value must be between 0 and the return value of ajms_pcs_getPermissionCount() minus 1.
 * @param info
 *        A pointer to an #AJMS_Permission structure for receiving the permission information.
 *
 * @retval #AJMS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if <i>domainId</i> or <i>permId</i> is invalid.
 * @retval #AJMS_ERR_INVALID_PARAMS
 *         if <i>info</i> is NULL.
 */ 
AJ_S32 ajms_pcs_getPermission( AJ_S32 domainId, 
                               AJ_S32 permId,
                               AJMS_Permission* info );

/** @} */

/** 
 * @addtogroup Function_Group_ACI
 * @{
 */

/**
 *        Gets the number of function groups in a protection domain.
 * @param domainId
 *        The domain identifier. One of the following values should be passed here.
 *        - #AJMS_PCS_DOMAIN_UNSPECIFIED 
 *        - #AJMS_PCS_DOMAIN_MANUFACTURER 
 *        - #AJMS_PCS_DOMAIN_OPERATOR
 *        - #AJMS_PCS_DOMAIN_THIRD_PARTY
 *        .
 *
 * @retval "A value of 0 or greater" representing the number of function groups in the protection domain.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if the function fails due to an invalid domain identifier.
 */
AJ_S32 ajms_pcs_getGroupCount( AJ_S32 domainId );

/**
 *        Gets the information of a function group in a protection domain.
 * @param domainId
 *        The domain identifier. One of the following values should be passed here.
 *        - #AJMS_PCS_DOMAIN_UNSPECIFIED 
 *        - #AJMS_PCS_DOMAIN_MANUFACTURER 
 *        - #AJMS_PCS_DOMAIN_OPERATOR
 *        - #AJMS_PCS_DOMAIN_THIRD_PARTY
 *        .
 * @param groupId
 *        The function group index. 
 *        The value should be between 0 and the return value of ajms_pcs_getGroupCount() minus 1.
 * @param info
 *        A pointer to an #AJMS_DomainGroup structure for receiving the function group information.
 *        The pointer type members in the structure remain valid until the next time an ACI function is called.
 *
 * @retval #AJMS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if <i>domainId</i> or <i>groupId</i> is invalid.
 * @retval #AJMS_ERR_INVALID_PARAMS
 *         if <i>info</i> is NULL.
 */
AJ_S32 ajms_pcs_getGroup( AJ_S32 domainId, 
                          AJ_S32 groupId, 
                          AJMS_DomainGroup* info );

/** @} */

/** 
 * @addtogroup Relation_ACI
 * @{
 */

/**
 *        Gets the number of relations for a protection domain.
 * @param domainId
 *        The domain identifier. One of the following values should be passed here.
 *        - #AJMS_PCS_DOMAIN_UNSPECIFIED 
 *        - #AJMS_PCS_DOMAIN_MANUFACTURER 
 *        - #AJMS_PCS_DOMAIN_OPERATOR
 *        - #AJMS_PCS_DOMAIN_THIRD_PARTY
 *        .
 *
 * @retval "A value of 0 or greater" representing the number of relations in the protection domain.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if the function fails due to an invalid domain identifier.
 */
AJ_S32 ajms_pcs_getRelationCount( AJ_S32 domainId );

/**
 *        Gets the information of a relation in a protection domain.
 * @param domainId
 *        The domain identifier. One of the following values should be passed here.
 *        - #AJMS_PCS_DOMAIN_UNSPECIFIED 
 *        - #AJMS_PCS_DOMAIN_MANUFACTURER 
 *        - #AJMS_PCS_DOMAIN_OPERATOR
 *        - #AJMS_PCS_DOMAIN_THIRD_PARTY
 *        .
 * @param relationId
 *        The relation index. 
 *        The value should be between 0 and the return value of ajms_pcs_getRelationCount() minus 1.
 * @param info
 *        A pointer to an #AJMS_DomainRelation structure for receiving the relation information.
 *
 * @retval #AJMS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if the function fails due to an invalid domain identifier.
 * @retval #AJMS_ERR_INVALID_PARAMS
 *         if <i>info</i> is NULL.
 */
AJ_S32 ajms_pcs_getRelation( AJ_S32 domainId,
                             AJ_S32 relationId,
                             AJMS_DomainRelation* info );

/** @} */

/** 
 * @addtogroup Restriction_ACI
 * @{
 */

/**
 *        Gets the number of restrictions for a protection domain.
 * @param domainId
 *        The domain identifier. One of the following values should be passed here.
 *        - #AJMS_PCS_DOMAIN_UNSPECIFIED 
 *        - #AJMS_PCS_DOMAIN_MANUFACTURER 
 *        - #AJMS_PCS_DOMAIN_OPERATOR
 *        - #AJMS_PCS_DOMAIN_THIRD_PARTY
 *        .
 *
 * @retval "A value of 0 or greater" representing the number of restrictions in the protection domain.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if the function fails due to an invalid domain identifier.
 */
AJ_S32 ajms_pcs_getRestrictionCount( AJ_S32 domainId );
                      
/**
 *        Gets the information of a restriction in a protection domain.
 * @param domainId
 *        The domain identifier. One of the following values should be passed here.
 *        - #AJMS_PCS_DOMAIN_UNSPECIFIED 
 *        - #AJMS_PCS_DOMAIN_MANUFACTURER 
 *        - #AJMS_PCS_DOMAIN_OPERATOR
 *        - #AJMS_PCS_DOMAIN_THIRD_PARTY
 *        .
 * @param restricId
 *        The restriction index. 
 *        The value should be between 0 and the return value of ajms_pcs_getRestrictionCount() minus 1.
 * @param info
 *        A pointer to an #AJMS_DomainRestriction structure for receiving the restriction information.
 *        The pointer type members in the structure remain valid until the next time an ACI function is called.
 *
 * @retval #AJMS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         if the function fails due to an invalid domain identifier.
 * @retval #AJMS_ERR_INVALID_PARAMS
 *         if <i>info</i> is NULL.
 */
AJ_S32 ajms_pcs_getRestriction( AJ_S32 domainId, 
                                AJ_S32 restricId, 
                                AJMS_DomainRestriction* info );
                                
/** @} */

#ifdef __cplusplus
}
#endif

#endif
