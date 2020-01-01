/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */
/**
 *  @file ajms_ota.h
 *  OTA ACI
 */

#ifndef AJMS_OTA_HEADER
#define AJMS_OTA_HEADER

#ifdef __cplusplus
extern "C"{
#endif

/** @addtogroup Application_Installation_and_Uninstallation
 *  @{
 */

/*
 *  Interfaces listed in the group are used for application installation,
 *  including these functionalities:
 *       - Verify a MIDlet suite's JAD/JAR data.
 *       - Install a MIDlet suite by JAD/JAR data.
 *       - Install a MIDlet suite by JAD/JAR native file path.
 *       - Delete an installed midlet suite.
 *       .
 */

/*-----------------------------------------------------------------------------
 * Marcos, Constants, Types, and Structures
 *----------------------------------------------------------------------------*/
/**
 * @addtogroup MIDlet_Suite_Verification_ACI MIDlet Suite Verification ACI
 * An interface for performing JAD/JAR checking for MIDlet suite installation.
 * This interface is implemented in AJSC.
 *
 * @par Include file
 * \#include ajms_ota.h
 * @{
 */

/**
 * @name Application Check Type
 * @{
 * Macros for indicating check type to ajms_ota_check().
 */
/**
 * Indicates that the type of the data passed to ajms_ota_check() is JAD file.
 */
#define AJMS_CHECK_TYPE_JAD (1)
/**
 * Indicates that the type of the data passed to ajms_ota_check() is JAR file.
 */
#define AJMS_CHECK_TYPE_JAR (2)

/**
 * Indicates that the type of the data passed to ajms_ota_check() is JAD file,
 * and the JAD file will be installed to external storage (other than /java folder)
 */
#define AJMS_CHECK_TYPE_JAD_EX (3)
/**
 * Indicates that the type of the data passed to ajms_ota_check() is JAR file.
 * and the Jar file will be installed to external storage (other than /java folder)
 */
#define AJMS_CHECK_TYPE_JAR_EX (4)
/** @} */

/**
 * @name MIDlet Upgrade Check Result
 * @{
 */
/**
 * The AJSC Java application repository has no MIDlet suite with the same vendor name and MIDlet suite name.
 */
#define AJMS_UPDATE_MIDLET_SUITE_NOT_EXIST   (1)
/**
 * Upgrade is not allowed because the new application is an untrusted MIDlet suite,
 * which cannot take over an existing trusted MIDlet suite.
 */
#define AJMS_UPDATE_SECURITY_VIOLATTION      (2)
/**
 * Upgrade is allowed.\ The new MIDlet suite has a newer version.
 */
#define AJMS_UPDATE_NEWER_VERSION            (3)
/**
 * Upgrade is not necessary because the new MIDlet suite has the same version.
 */
#define AJMS_UPDATE_SAME_VERSION             (4)
/**
 * Upgrade is not allowed because the new MIDlet suite has an older version.
 */
#define AJMS_UPDTAE_OLDER_VERSION            (5)
/** @} */
/** @} */

/**
 * @addtogroup MIDlet_Suite_Installation_ACI MIDlet Suite Installation ACI
 * An interface for performing MIDlet suite installation.
 * This interface is implemented in AJSC.
 *
 * @par Include file
 * \#include ajms_ota.h
 * @{
 */

/**
 * @name MIDlet Installation Option
 * @{
 */
/**
 * Indicates that no installation option is requested.
 */
#define AJMS_INSTALL_DEFAULT                 (0x00)
/**
 * Installation option: Keep original RMS files during MIDlet updating.
 */
#define AJMS_INSTALL_KEEP_RMS                (0x01)
/**
 * Installation option: Perform JAR precheck during installation.
 */
#define AJMS_INSTALL_PRECHECK                (0x02)
/**
 * This flag is reserved for future use.
 <!--
 * Installation option: Make a copy of JAR file.\ This is for use with ajms_ota_installEx() only.
 -->
 */
#define AJMS_INSTALL_COPY_JAR                (0x10)
/**
 * This flag is reserved for future use.
 <!--
 * Installation option: Make a copy of JAD file.\ This is for use with ajms_ota_installEx() only.
 -->
 */
#define AJMS_INSTALL_COPY_JAD                (0x20)
/**
 * Installation option: Force the installed application to be under Manufacturer domain without performing any integrity checking.
 */
#define AJMS_INSTALL_AS_MANUFACTURER         (0x100)
/**
 * Installation option: Force the installed application to be under Operator domain without performing any integrity checking.
 */
#define AJMS_INSTALL_AS_OPERATOR             (0x200)
/**
 * Installation option: Force the installed application to be under Third Party domain without performing any integrity checking.
 */
#define AJMS_INSTALL_AS_THIRD_PARTY          (0x400)
/**
 * Installation option: Force the installed application to be under unspecified (Untrusted) domain without performing any integrity checking.
 */
#define AJMS_INSTALL_AS_UNSPECIFIED          (0x800)

/** @} */
/** @} */

/**
 * @addtogroup OTA_Status_Code OTA Status Code
 * A list of the status codes used for an OTA installation/deletion status report.
 *
 * @par Include file
 * \#include ajms_ota.h
 * @{
 */

/**
 * @name OTA Status Code
 * @{
 */

/**
 * OTA status code: Success.
 */
#define AJMS_ERR_OTA_OK                         (900)
/**
 * OTA status code: Insufficient memory (Insufficient storage space in the file system).
 **/
#define AJMS_ERR_OTA_NO_ENOUGH_SPACE            (901)
/**
 * OTA status code: User canceled.
 */
#define AJMS_ERR_OTA_USER_CANCEL                (902)
/**
 * OTA status code: Loss of service.
 */
#define AJMS_ERR_OTA_LOSS_OF_SERVICE            (903)
/**
 * OTA status code: JAR size mismatch
 */
#define AJMS_ERR_OTA_JAR_SIZE_MISMATCH          (904)
/**
 * OTA status code: Attribute mismatch
 */
#define AJMS_ERR_OTA_ATTRIBUTE_MISMATCH         (905)
/**
 * OTA status code: Invalid descriptor
 */
#define AJMS_ERR_OTA_INVALID_JAD                (906)
/**
 * OTA status code: Invalid JAR
 */
#define AJMS_ERR_OTA_INVALID_JAR                (907)
/**
 * OTA status code: Incompatible configuration or profile
 */
#define AJMS_ERR_OTA_CLDC_MIDP_VERSION          (908)
/**
 * OTA status code: Application authentication failure
 */
#define AJMS_ERR_OTA_AUTHENTICATION_FAILURE     (909)
/**
 * OTA status code: Application authorization failure
 */
#define AJMS_ERR_OTA_AUTHORIZATION_FAILURE      (910)
/**
 * OTA status code: Push registration failure
 */
#define AJMS_ERR_OTA_PUSH_REGISTRATION_FALIURE  (911)
/**
 * OTA status code: Deletion notification
 */
#define AJMS_ERR_OTA_DELETION_NOTIFICATION      (912)
/**
 * OTA status code: Non-defined OTA error
 */
#define AJMS_ERR_OTA_NOT_DEFINE                 (999)
/** @} */
/** @} */

/**
 * @addtogroup MIDlet_Suite_Verification_ACI
 * @{
 */

/**
 * The data structure type for containing a JAD/JAR check result by ajms_ota_check().
 */
typedef struct _AJMS_CheckResult
{
    /**
     * The MIDlet-Name attribute string of the MIDlet suite.\ A UTF-8 encoded NUL-terminated string.
     */
    AJ_U8     name[AJMS_MAX_ENTRY_NAME_LENGTH + 1];
    /**
     * The MIDlet-Vendor attribute string of the MIDlet suite.\ A UTF-8 encoded NUL-terminated string.
     */
    AJ_U8     vendor[AJMS_MAX_ENTRY_NAME_LENGTH + 1];
    /**
     * The MIDlet-Jar-URL attribute string of the MIDlet suite.\ A UTF-8 encoded NUL-terminated string.
     * This member is not set when performing the #AJMS_CHECK_TYPE_JAR checking by ajms_ota_check().
     */
    AJ_U8     jarUrl[AJMS_MAX_ENTRY_URL_LENGTH + 1];
    /**
     * The MIDlet-Install-Notify attribute string of the MIDlet suite.\ A UTF-8 encoded NUL-terminated string.
     * This member is not set when performing the #AJMS_CHECK_TYPE_JAR checking by ajms_ota_check().
     */
    AJ_U8     installNotifyUrl[AJMS_MAX_ENTRY_URL_LENGTH + 1];
    /**
     * The OTA status code.
     * One of the following values is set:
     * - #AJMS_ERR_OTA_OK
     * - #AJMS_ERR_OTA_NO_ENOUGH_SPACE
     * - #AJMS_ERR_OTA_USER_CANCEL
     * - #AJMS_ERR_OTA_LOSS_OF_SERVICE
     * - #AJMS_ERR_OTA_INVALID_JAD
     * - #AJMS_ERR_OTA_INVALID_JAR
     * - #AJMS_ERR_OTA_CLDC_MIDP_VERSION
     * - #AJMS_ERR_OTA_AUTHENTICATION_FAILURE
     * - #AJMS_ERR_OTA_NOT_DEFINE
     */
    AJ_S32    otaCode;
    /**
     * A flag indicating whether or not the MIDlet-Push-1 attribute exists in JAD.
     */
    AJ_BOOL   hasPush;
    /**
     * The name field of the MIDlet-1 attribute of the the MIDlet suite.\ A UTF-8 encoded NUL-terminated string.
     * If the attribute string is longer than #AJMS_MAX_ENTRY_NAME_LENGTH, this function only takes
     * the first #AJMS_MAX_ENTRY_NAME_LENGTH bytes and appends a NUL-character.
     */
    AJ_U8     midlet[AJMS_MAX_ENTRY_NAME_LENGTH + 1];
    /**
     * The major version value of the MIDlet-Version attribute of the MIDlet suite.
     */
    AJ_S32  majorVersion;
    /**
     * The minor version value of the MIDlet-Version attribute of the MIDlet suite.
     */
    AJ_S32  minorVersion;
    /**
     * The micro version value of the MIDlet-Version attribute of the MIDlet suite.
     */
    AJ_S32  microVersion;
    /**
     * The size in bytes of the JAR content.
     */
    AJ_U32    jarSize;
    /**
     * The minimum storage space size (in bytes) necessary for the MIDlet suite.
     */
    AJ_U32    minimumInstallSize;
    /**
     * The candidate of the application identifier for the next installation.
     *
     * When the AMS uses the {@link #AJMS_APPLICATION_TYPE_3 Storage type 3} application installation,
     * i.e., installation of a device protected application using ajms_ota_installEx(),
     * in some cases it is convenient to determine the file name with the application identifier.
     * The AMS in advance can use the information of this member to determine a unique name for an application.
     */
    AJ_S32    candidateId;
    /**
     * A flag indicating whether the MIDlet suite can be upgraded.
     * One of the following values is set:
     * - #AJMS_UPDATE_MIDLET_SUITE_NOT_EXIST:<br>
     *   The AJSC Java application repository has no MIDlet suite with the same vendor name and MIDlet suite name.
     * - #AJMS_UPDATE_SECURITY_VIOLATTION:<br>
     *   Upgrade is not allowed because the new application is an untrusted MIDlet suite,
     *   which cannot take over an existing trusted MIDlet suite.
     * - #AJMS_UPDATE_NEWER_VERSION:<br>
     *   Upgrade is allowed. The new MIDlet suite has a newer version.
     * - #AJMS_UPDATE_SAME_VERSION:<br>
     *   Upgrade is not necessary because the new MIDlet suite has the same version.
     * - #AJMS_UPDTAE_OLDER_VERSION:<br>
     *   Upgrade is not allowed because the new MIDlet suite has an older version.
     */
    AJ_S32   update;
    /**
     * The identifier of the MIDlet suite with the same vendor name and MIDlet suite name.
     * This member is valid when <i>update</i> is other than #AJMS_UPDATE_MIDLET_SUITE_NOT_EXIST.
     */
    AJ_S32 oldId;
    /**
     * The major version value of the MIDlet-Version attribute of the existing MIDlet suite.
     */
    AJ_S32  oldMajorVersion;
    /**
     * The minor version value of the MIDlet-Version attribute of the existing MIDlet suite.
     */
    AJ_S32  oldMinorVersion;
    /**
     * The micro version value of the MIDlet-Version attribute of the existing MIDlet suite.
     */
    AJ_S32  oldMicroVersion;
    /**
     * The protection domain obtained by kjava_ext_verifyChainCert().
     * This member is valid only when JAD file is passed to ajms_ota_check().
     * One of the following values is set.
     * - #KJAVA_DOMAIN_MANUFACTURER
     * - #KJAVA_DOMAIN_OPERATOR
     * - #KJAVA_DOMAIN_THIRD_PARTY
     * - #KJAVA_DOMAIN_UNSPECIFIED
     */
    AJ_S32  domainId;
    /**
     * The identifier of the certificate chain with which authentication has succeeded with kjava_ext_verifyChainCert().
     * This member is valid only when JAD file is passed to ajms_ota_check().
     * This is the value of &lt;n&gt; of the MIDlet-Certificate-&lt;n&gt;-&lt;m&gt; attribute.
     *
     * When there exists no MIDlet-Certificate-&lt;n&gt;-&lt;m&gt; attribute, or when
     * JAR file is passed to ajms_ota_check(), a value of 0 is set.
     */
    AJ_S32  chainId;

} AJMS_CheckResult;

/** @} */

/**
 * @addtogroup MIDlet_Suite_Installation_ACI
 * @{
 */

/**
 * The data structure type for containing an installation result.
 */
typedef struct _AJMS_InstallResult
{
    /**
     * The MIDlet suite identifier.
     */
    AJ_S32    suiteId;
    /**
     * The protection domain identifier.
     * One of the following values is set:
     * - #AJMS_PCS_DOMAIN_UNSPECIFIED
     * - #AJMS_PCS_DOMAIN_MANUFACTURER
     * - #AJMS_PCS_DOMAIN_OPERATOR
     * - #AJMS_PCS_DOMAIN_THIRD_PARTY
     */
    AJ_S32    domainId;
    /**
     * The MIDlet-Install-Notify attribute string of the MIDlet suite.\ A UTF-8 encoded NUL-terminated string.
     */
    AJ_U8     installNotifyUrl[AJMS_MAX_ENTRY_URL_LENGTH + 1];
    /**
     * The OTA status code.
     * One of the following values is set:
     * - #AJMS_ERR_OTA_OK
     * - #AJMS_ERR_OTA_NO_ENOUGH_SPACE
     * - #AJMS_ERR_OTA_USER_CANCEL
     * - #AJMS_ERR_OTA_LOSS_OF_SERVICE
     * - #AJMS_ERR_OTA_JAR_SIZE_MISMATCH
     * - #AJMS_ERR_OTA_ATTRIBUTE_MISMATCH
     * - #AJMS_ERR_OTA_INVALID_JAD
     * - #AJMS_ERR_OTA_INVALID_JAR
     * - #AJMS_ERR_OTA_CLDC_MIDP_VERSION
     * - #AJMS_ERR_OTA_AUTHENTICATION_FAILURE
     * - #AJMS_ERR_OTA_AUTHORIZATION_FAILURE
     * - #AJMS_ERR_OTA_PUSH_REGISTRATION_FALIURE
     * - #AJMS_ERR_OTA_DELETION_NOTIFICATION
     * - #AJMS_ERR_OTA_NOT_DEFINE
     */
    AJ_S32    otaCode;

} AJMS_InstallResult;

/** @} */

/**
 * @addtogroup MIDlet_Suite_Verification_ACI
 * @{
 */

/**
 *        The function type of the result notification callback for ajms_ota_check().
 * @param total
 *        The total checking steps. When the value of this parameter is -1,
 *        it indicates that an error occurred during JAD/JAR checking.
 *        The error code is passed in the <i>step</i> parameter.
 * @param step
 *        The current step or an error result.
 *        - A value of 0 or more:<br>
 *          The current step.
 *        - #AJMS_ERR_USER_CANCEL:<br>
 *          The AMS previously has canceled the check procedure by returning 0 in this callback function.
 *        - #AJMS_ERR_INVALID_FORMAT:<br>
 *          JAD or JAR file format is illegal.
 *        - #AJMS_ERR_MEMORY_OVERFLOW:<br>
 *          Insufficient memory space.
 *        - #AJMS_ERR_NOT_SUPPORT:<br>
 *          No "MIDlet-1" attribute in the manifest file.
 *          This can occur only in the #AJMS_CHECK_TYPE_JAR checking.
 *        - #AJMS_ERR_INTERNAL:<br>
 *          The check processing failed for any other reason.
 *        .
 * @param result
 *        A pointer to the structure indicating the JAD/JAR checking result.
 *        This parameter is the pointer passed to ajms_ota_check() and the buffer
 *        this parameter points to will be filled with results.
 *        - When <i>total > 0 </i> and <i>total != step</i>,
 *          structure members are for tracing purpose only and correctness of them are not guaranteed.
 *        - When <i>total > 0 </i> and <i>total == step</i>,
 *          structure members are filled with the final results.
 *        - When <i>total == -1</i>,
 *          only the {@link AJMS_CheckResult#otaCode result->otaCode} member is valid.
 *        .
 * @retval 1 to continue check processing.
 * @retval 0 to cancel check processing.
 *
 * A callback function of this type should be passed to ajms_ota_check().
 * The callback function is to be implemented by the device manufacturer.
 *
 * The callback function is called several times in the KVE
 * thread context to indicate the progress of check processing.
 *
 * Once an error is reported by this function, the checking process is aborted
 * and the function is no longer called.
 *
 * When this function returns 0, AJSC immediately cancels the
 * check procedure and releases all the resources prepared for
 * the check. Finally, AJSC invokes the function with
 * <i>total</i> == -1 and <i>steps</i> == #AJMS_ERR_OTA_USER_CANCEL
 * for error notification.
 *
 * At the final step, the structure indicated by <i>result</i> contains the check result.
 *
 * If {@link AJMS_CheckResult#hasPush result->hasPush} == #AJ_TRUE, AMS should ask user whether to
 * allow the application to be installed with the push registry request.
 *
 * If <i>{@link AJMS_CheckResult#update result->update}</i> == #AJMS_UPDATE_NEWER_VERSION, AMS should ask user whether to
 * perform application upgrade.
 *
 * @see ajms_ota_check()
 */
typedef AJ_S32 (*AJMS_CheckCB)
               ( AJ_S32 total, AJ_S32 step, AJMS_CheckResult *result );

/** @} */

/**
 * @addtogroup MIDlet_Suite_Installation_ACI
 * @{
 */

/**
 *        The function type of the progress/result notification callback for ajms_ota_install().
 * @param total
 *        The total installation steps. When the value of this parameter is -1,
 *        it indicates that an error occurred during installation.
 *        The error code is passed in the <i>step</i> parameter.
 * @param step
 *        The current step or an error result.
 *        - A value of 0 or more:<br>
 *          The current step.
 *        - #AJMS_ERR_USER_CANCEL:<br>
 *          The AMS previously has canceled the installation procedure by returning 0 in this callback function.
 *        - #AJMS_ERR_INVALID_FORMAT:<br>
 *          JAD or JAR file format is illegal.
 *        - #AJMS_ERR_MEMORY_OVERFLOW:<br>
 *          Insufficient memory space.
 *        - #AJMS_ERR_NOT_SUPPORT:<br>
 *          The MIDlet suite to be installed requests support of Push feature
 *          but the feature is disabled in the current configuration of the AJSC library.
 *        - #AJMS_ERR_NOT_ALLOWED<br>
 *          Installation fails due to a security issue.
 *        - #AJMS_ERR_INTERNAL:<br>
 *          Installation processing failed for any other reason.
 *        .
 * @param result
 *        A pointer to the structure indicating the installation result.
 *        This parameter is the pointer passed to ajms_ota_install() and the buffer
 *        this parameter points to will be filled with results.
 *        - When <i>total > 0 </i> and <i>total != step</i>,
 *          structure members are for tracing purpose only and correctness of them are not guaranteed.
 *        - When <i>total > 0 </i> and <i>total == step</i>,
 *          structure members are filled with the final results.
 *        - When <i>total == -1</i>,
 *          only the {@link AJMS_CheckResult#otaCode result->otaCode} member is valid.
 * @retval 1 to continue installation.
 * @retval 0 to cancel installation.
 *
 * A callback function of this type should be passed to ajms_ota_install().
 * The callback function is to be implemented by the device manufacturer.
 *
 * The callback function is called several times in the KVE
 * thread context to indicate the progress of installation.
 *
 * Once an error is reported by this function, the installation process is aborted
 * and the function is no longer called.
 *
 * When this function returns 0, AJSC cancels the
 * installation procedure immediately and releases all resources prepared for the
 * installation. Finally, AJSC invokes the function with
 * <i>total</i> == -1 and <i>steps</i> == #AJMS_ERR_OTA_USER_CANCEL
 * for error notification.
 *
 * @see ajms_ota_install()
 */
typedef AJ_S32 (*AJMS_InstallCB)
               ( AJ_S32 total, AJ_S32 step, AJMS_InstallResult *result);

/** @} */

/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/

/**
 * @addtogroup MIDlet_Suite_Verification_ACI
 * @{
 */

/**
 *        Requests JAD/JAR checking.
 * @param dataSize
 *        The size of the JAD/JAR data indicated by <i>dataAddr</i>.
 * @param dataAddr
 *        A pointer to the buffer holding the JAD/JAR data.
 * @param dataRead
 *        The function address of a JAD/JAR reader callback function.
 * @param dataType
 *        A flag indicating whether the data is JAD or JAR.
 *        Pass either #AJMS_CHECK_TYPE_JAD or #AJMS_CHECK_TYPE_JAR.
 * @param jadUrl
 *        A pointer to the NUL terminated string representing the JAD URL.
 *        When checking a JAR, pass #AJ_NULL in this parameter.
 * @param result
 *        A pointer to the structure for receiving verification result.
 * @param callback
 *        The address of the progress/result notification callback function.
 *
 * @retval #AJMS_ERR_NONE
 *         if the check request has been sent to the KVE thread normally.
 * @retval #AJMS_ERR_INVALID_PARAMS
 *         if the function fails due to an invalid parameter.
 *
 * Check by this function must be performed prior to any kind of installation.
 * For JAD+JAR installation, AMS needs to check only JAD content before installation.
 * For JAR-only installation, AMS needs to check JAR content before installation.
 *
 * A non-NULL value must be set in either <i>dataAddr</i> or <i>dataRead</i>.
 * If both are designated, the value designated in <i>dataAddr</i> is used.
 *
 * The check processing is performed asynchronously in the KVE thread.
 * This function only sends a check request to the KVE thread by using kjava_sys_sendAction() and returns to the caller.
 *
 * The callback function <i>callback</i> is called several times in the KVE thread context to indicate the check progress and result.
 * See #AJMS_CheckCB for details.
 *
 * The pointer or address indicated by the following parameters must remain valid until
 * <i>callback</i> completes notification or this function returns #AJMS_ERR_INVALID_PARAMS.
 * - <i>dataAddr</i> or <i>dataRead</i>
 * - <i>result</i>
 * - <i>callback</i>
 * .
 *
 * @see AJMS_CheckCB
 */
AJ_S32 ajms_ota_check(
                             const AJ_S32                      dataSize,
                             const AJ_U8                      *dataAddr,
                             AJMS_Reader                       dataRead,
                             const AJ_S32                      dataType,
                             const AJ_U8                      *jadUrl,
                             AJMS_CheckResult                 *result,
                             AJMS_CheckCB                      callback);

/** @} */

/**
 * @addtogroup MIDlet_Suite_Installation_ACI
 * @{
 */

/**
 *        Installs a Java application by JAD and JAR data.
 * @param categoryId
 *        The category to bind the Java application to be installed.
 *        This is used only when the AJSC Java application repository supports the category feature.
 * @param jadSize
 *        The size in bytes of the JAD data.
 *        Pass 0 when installing by JAR file only.
 * @param jadAddr
 *        A pointer to the buffer holding the JAD file content.
 *        Pass #AJ_NULL when installing by JAR file only.
 * @param jadRead
 *        The function address of a JAD reader callback function.
 *        Pass #AJ_NULL when installing by JAR file only.
 * @param jadUrl
 *        A pointer to the NUL terminated string representing the JAD URL.
 *        Specify this parameter only when installing with JAD + JAR files and
 *        the AMS needs to retrieve the JAD URL via ajms_ab_getJadUrl() later
 *        for the purpose of analyzing whether or not an application is upgradeable.
 *        When installing by JAR file only, for example, pass #AJ_NULL.
 * @param jarSize
 *        The size in bytes of the JAR data.
 * @param jarAddr
 *        A pointer to the buffer holding the JAR file content.
 * @param jarRead
 *        The function address of a JAR reader callback function.
 * @param flag
 *        A bit-mapped flags indicating installation options.
 *        Three kinds of options listed below are available.
 *        If no option required, pass #AJMS_INSTALL_DEFAULT (=0x00).
 *        - #AJMS_INSTALL_KEEP_RMS<br>
 *          This flag requests to keep the old application RMS data after upgrading application.
 *          This is only meaningful when update is allowed.
 *          In other words, the caller MUST first use ajms_ota_check() to get the upgrade information.
 *          Note that the native system is responsible for determining whether to allow
 *          upgrading with the old RMS data.
 *        - #AJMS_INSTALL_PRECHECK<br>
 *          This flag requests Jar data precheck during installation.
 *          It can reduce the time for launching the application but may spend more time during installation.
 *          This flag is used only when the AJSC supports the precheck feature.
 *        - One of the following options. <br>
 *          - #AJMS_INSTALL_AS_MANUFACTURER<br>
 *            This flag forces application to be under Manufacturer domain.
 *          - #AJMS_INSTALL_AS_OPERATOR<br>
 *            This flag forces application to be under Operator domain.
 *          - #AJMS_INSTALL_AS_THIRD_PARTY<br>
 *            This flag forces application to be under Third Party domain.
 *          - #AJMS_INSTALL_AS_UNSPECIFIED<br>
 *            This flag forces application to be under Untrusted domain.
 *          .
 *          Use this option only when the protection domain is determined before installation.
 *          For example, when application integrity has already been checked by a WAP browser during downloading.
 * @param oldId
 *        Pass the value of <i>{@link AJMS_CheckResult#oldId result->oldId}</i> member set by ajms_ota_check().
 * @param callback
 *        The address of the progress/result notification callback function.
 * @param result
 *        A pointer to the structure for receiving installation result.
 *
 * @retval #AJMS_ERR_NONE
 *         if the installation request has been sent to the KVE thread normally.
 * @retval #AJMS_ERR_INVALID_PARAMS
 *         if the function fails due to an invalid parameter.
 *
 * Use this function to install a Java application into the AJSC Java application repository.
 *
 * This function does not perform JAD/JAR check.
 * It is device manufacturer's responsibility to verify JAD/manifest by invoking ajms_ota_check() before this function.
 *
 * The installation processing is performed asynchronously in the KVE thread.
 * This function only sends an installation request to the KVE thread by using kjava_sys_sendAction() and returns to the caller.
 *
 * The callback function <i>callback</i> is called several times in the KVE thread context to indicate the verification progress or result.
 * See #AJMS_InstallCB for details.
 *
 * A non-NULL value must be set in either <i>jarAddr</i> or <i>jarRead</i>.
 * If both are designated, the value designated in <i>jarAddr</i> is used.
 * The same rule is applied to <i>jadAddr</i> and <i>jadRead</i>, except that
 * both of them can be #AJ_NULL if JAD is not provided to the function.
 *
 * The pointer or address indicated by the following parameters must remain valid until
 * <i>callback</i> completes notification or this function returns #AJMS_ERR_INVALID_PARAMS.
 * - <i>jadAddr</i> or <i>jadReader</i>
 * - <i>jarAddr</i> or <i>jarReader</i>
 * - <i>result</i>
 * - <i>callback</i>
 * .
 *
 * The number of MIDlets in one MIDlet suite should be less than or equal to 255.
 * If the number of MIDlets is more than 255, MIDlets of which index is greater than 255 are ignored.
 */
AJ_S32 ajms_ota_install( const AJ_S32                      categoryId,
                         const AJ_S32                      jadSize,
                         const AJ_U8                      *jadAddr,
                         AJMS_Reader                       jadRead,
                         const AJ_U8                      *jadUrl,
                         const AJ_S32                      jarSize,
                         const AJ_U8                      *jarAddr,
                         AJMS_Reader                       jarRead,
                         const AJ_S32                      flag,
                         const AJ_S32                      oldId,
                         AJMS_InstallResult               *result,
                         AJMS_InstallCB                    callback);

#ifdef SUPPORT_OTA_INSTALLATION_WITH_JAD_JAR_LOCATION
AJ_S32 ajms_ota_install_to( const AJ_S32                      categoryId,
	                        int                               installtype,
                            const AJ_U8                      *jadinstallPath,
                            const AJ_U8                      *jarinstallPath,
                            const AJ_S32                      jadSize,
                            const AJ_U8                      *jadAddr,
                            AJMS_Reader                       jadRead,
                            const AJ_U8                      *jadUrl,
                            const AJ_S32                      jarSize,
                            const AJ_U8                      *jarAddr,
                            AJMS_Reader                       jarRead,
                            const AJ_S32                      flag,
                            const AJ_S32                      oldId,
                            AJMS_InstallResult               *result,
                            AJMS_InstallCB                    cb);
#endif
/**
 *        Installs a Java application by native file paths.
 * @param categoryId
 *        The category to bind the Java application to be installed.
 *        This is used only when the AJSC Java application repository supports the category feature.
 * @param jad
 *        A UTF-8 encoded NUL-terminated string containing the absolute path of the JAD file.
 *        The path must be a valid one to access the file via @ref kjava_dev_fs_io.
 *        If this is not satisfied, this function returns #AJMS_ERR_NOT_ALLOWED.
 * @param jadUrl
 *        A pointer to the NUL-terminated string representing the JAD URL.
 *        Specify this parameter only when installing with JAD + JAR files and
 *        the AMS needs to retrieve the JAD URL via ajms_ab_getJadUrl() later
 *        for the purpose of analyzing whether or not an application is upgradeable.
 *        When installing by JAR file only, for example, pass #AJ_NULL.
 * @param jar
 *        A UTF-8 encoded NUL-terminated string containing the absolute path of the JAR file.
 *        The same rule as described for <i>jad</i> applies to this parameter.
 * @param flag
 *        A bit-mapped flags indicating installation options.
 *        Three kinds of options listed below are available.
 *        If no option required, pass #AJMS_INSTALL_DEFAULT (=0x00).
 *        - #AJMS_INSTALL_KEEP_RMS<br>
 *          This flag requests to keep the old application RMS data after upgrading application.
 *          This is only meaningful when update is allowed.
 *          In other words, the caller MUST first use ajms_ota_check() to get the upgrade information.
 *          Note that the native system is responsible for determining whether to allow
 *          upgrading with the old RMS data.
 *        - #AJMS_INSTALL_PRECHECK<br>
 *          This flag requests Jar data precheck during installation.
 *          It can reduce the time for launching the application but may spend more time during installation.
 *          This flag is used only when the AJSC supports the precheck feature.
 *        - One of the following options. <br>
 *          - #AJMS_INSTALL_AS_MANUFACTURER<br>
 *            This flag forces application to be under Manufacturer domain.
 *          - #AJMS_INSTALL_AS_OPERATOR<br>
 *            This flag forces application to be under Operator domain.
 *          - #AJMS_INSTALL_AS_THIRD_PARTY<br>
 *            This flag forces application to be under Third Party domain.
 *          - #AJMS_INSTALL_AS_UNSPECIFIED<br>
 *            This flag forces application to be under Untrusted domain.
 *          .
 *          Use this option only when the protection domain is determined before installation.
 *          For example, when application integrity has already been checked by a WAP browser during downloading.
 * @param oldId
 *        Pass the value of <i>{@link AJMS_CheckResult#oldId result->oldId}</i> member set by ajms_ota_check().
 * @param result
 *        A pointer to the structure for receiving installation result.
 * @param callback
 *        The address of the progress/result notification callback function.
 *
 * @retval #AJMS_ERR_NONE
 *         if the installation request was sent to the KVE thread normally.
 * @retval #AJMS_ERR_INVALID_PARAMS
 *         if the function failed due to an invalid parameter.
 * @retval #AJMS_ERR_NOT_ALLOWED
 *         if the function failed because access to the directory of <i>jad</i> or <i>jar</i> was not allowed.
 *
 * The feature of this function is as same as the one of ajms_ota_install() except that
 * JAD and JAR file contents are passed via absolute file paths.
 *
 * You can install the JAD and JAR files into the AJSC Java application repository without
 * making copies of them. In this case you need to keep the files until uninstalling them by ajms_ota_delete().
 */
AJ_S32 ajms_ota_installEx( const AJ_S32        categoryId,
                           const AJ_U8*        jad,
                           const AJ_U8*        jadUrl,
                           const AJ_U8*        jar,
                           const AJ_S32        flag,
                           const AJ_S32        oldId,
                           AJMS_InstallResult *result,
                           AJMS_InstallCB      callback );

/** @} */

/**
 * @addtogroup MIDlet_Suite_Uninstallation_ACI MIDlet Suite Deletion ACI
 * An interface for performing MIDlet suite deletion.
 * This interface is implemented in AJSC.
 *
 * @par Include file
 * \#include ajms_cfg.h
 * @{
 */
/**
 *        Deletes an installed application in the AJSC Java application repository.
 * @param suiteId
 *        The identifier of the MIDlet suite to be deleted.
 *        See @ref Application_Repository for details of retrieving MIDlet suite identifier.
 *
 * @retval #AJMS_ERR_NONE
 *         The application has been deleted normally.
 * @retval #AJMS_ERR_ID_NOT_EXIST
 *         The <i>suiteId</i> parameter is invalid.
 * <p>
 * Use this function to delete an application from the AJSC Java application repository.
 *
 * Note that this function performs its processing synchronously.
 * Care must be taken so that this function is not called while an asynchronous processing
 * is accessing the AJSC Java application repository.
 * In short, during the period the KVE thread is performing an action accessing the repository,
 * e.g., OTA check, installation, or execution of an application, this function must not be called.
 *
 */
AJ_S32 ajms_ota_delete( const AJ_S32 suiteId );

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* AJMS_OTA_HEADER */
