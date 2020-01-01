/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file AamsAppInfoUtil.h
 * Appli
 cation Information Analysis JBI
 */
/**
 * @addtogroup Application_Information_Analysis_JBI
 * @{
 */

#ifndef ___AAMS_APPINFO_UTIL_H
#define ___AAMS_APPINFO_UTIL_H

#include "JkTypes.h"
#include "JkTypesAppInfoUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Creates the application information analysis functions environment.
 *  @param heapSize
 *         The size (in bytes) of the memory area used by the application
 *         information analysis functions.
 *  @param heapAddr
 *         A pointer to the memory area used by the application information
 *         analysis functions.
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function.<br>
 *         Designate #JK_NULL if no error code needs to be fetched.<br>
 *         One of the following values is put in this memory area. <br>
 *         - #JK_AMS_OK: succeeded<br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Either of the following cases<br>
 *           - #JK_NULL was designated in the heapAddr parameter<br>
 *           - A value of 0 or less was designated in the heapSize parameter
 *           .
 *         - #JK_AMS_OUT_OF_MEMORY_ERROR:
 *           Could not allocate the memory space needed by the management area
 *           of the Java application information analysis functions environment.
 *         .
 *  @return
 *         - Not #JK_INVALID_HANDLE: the application information analysis functions environment
 *           handle (succeeded)
 *         - #JK_INVALID_HANDLE: failed
 *         .
 *
 *  Call this function before using the application information analysis functions.
 *
 *  It is possible to create more than one handle identifying an application
 *  information analysis functions environment. It is not allowed, however, to
 *  use the same handle to call Java application information analysis functions
 *  from different tasks at the same time.
 *  This function obtains from the native system the memory area (heap) for use by the
 *  application information analysis functions and manages the heap internally.
 *  All operations thereafter with respect to the application descriptor file (JAD
 *  file) or JAR file make use of this heap.
 *
 *  While the returned handle is in use, be sure to
 *  hold the contents of the heap designated in the parameter.
 *  While the contents are held, do not write to the heap from the native system.
 *
 *  The required memory area size depends on the JAD file and JAR file size as well
 *  as the operation to be performed.
 *  The recommended amount of memory to be made available is at least enough
 *  to accomodate the maximum JAD file size and maximum manifest file size used
 *  in the native system plus about 8 KB.
 *  Note that if the JAD file and manifest file have more than the usual number
 *  of attributes, or if the JAD file contains a large number of files, more
 *  memory than usual will be required, in which case the amount estimated as
 *  above may not be sufficient.
 *
 *  After ending use of the application information analysis functions, call #AamsEnvFinalize().
 * @see AamsEnvFinalize() @see AamsJadOpen() @see AamsJarOpen()
 */
JKAmsEnvHandle AamsEnvInitialize(JKSint32 heapSize, void *heapAddr,
                                 JKSint32 * errorCode);

/**
 *  Disposes of the application information analysis functions environment.
 *  @param hEnv
 *         The handle of the application information analysis functions environment.
 *         Designate the handle returned by #AamsEnvInitialize().
 *  @return
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: #JK_INVALID_HANDLE was designated in
 *           the hEnv parameter (failed)
 *         .
 *
 *  Upon completion of this function, the heap that was used by the environment is
 *  freed, becoming available for other uses.
 * @see AamsEnvInitialize()
 */
JKSint32 AamsEnvFinalize(JKAmsEnvHandle hEnv);

/**
 *  Creates a handle for accessing the application descriptor file (JAD file).
 *  @param hEnv
 *         The application information analysis functions environment handle obtained
 *          by #AamsEnvInitialize()
 *  @param jadSize
 *         The size (in bytes) of the JAD file.
 *  @param jadAddr
 *         A pointer to the buffer holding the JAD file.<br>
 *         If #JK_NULL is designated, the JAD file will be read by the callback
 *         function designated in the parameter jadRead.
 *  @param jadRead
 *         A pointer to the stream function (callback function) for reading the JAD
 *         file. <br>
 *         If #JK_NULL is designated, the JAD file in the buffer designated
 *         in the parameter jadAddr is referenced.
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function.<br>
 *         Designate #JK_NULL if no error code needs to be fetched.<br>
 *         One of the following values is put in this memory area.
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Any of the following cases<br>
 *           - #JK_INVALID_HANDLE was designated in the hEnv parameter<br>
 *           - A value of 0 or less was designated in the jadSize parameter<br>
 *           - #JK_NULL was designated in the jadAddr and jadRead parameters
 *           .
 *         - #JK_AMS_OUT_OF_MEMORY_ERROR: Could not allocate the memory space needed
 *            for JAD file analysis<br>
 *         - #JK_AMS_ILLEGAL_FORMAT_ERROR: The JAD file format is illegal
 *         .
 *  @return
 *         - Not #JK_INVALID_HANDLE: The JAD file handle (succeeded) <br>
 *         - #JK_INVALID_HANDLE: failed
 *         .
 *
 *  Call this function before accessing the JAD file to get or verify its data. <br>
 *  When the handle obtained by this function is no longer needed, call
 *  #AamsDescriptorClose().
 *
 *  A value must be set in either jadAddr or jadRead.
 *  If both are designated, the value designated in jadAddr is used.<br>
 *  Use UTF-8 as the JAD file character encoding.
 *
 *  During the time the JAD file handle returned by this function is in use for
 *  subsequent processing, be sure to retain the contents of the buffer or
 *  read stream containing the JAD file.
 *
 *  The notation in the JAD file must be in a format conforming to the MIDP
 *  specification.<br>
 *  If a format that cannot be processed as an application descriptor is detected,
 *  this function fails.<br>
 *  If a MIDlet attribute is designated more than once, the last attribute value designation
 *  is valid.
 *
 *  <small>
 *  <b>Notes:</b><br>
 *  Some possible ways of storing the JAD file include the following. <br>
 *  - Stored in a contiguous area in flash ROM or other storage built into the device <br>
 *  - Stored in a non-contiguous area in flash ROM or other storage built into the
 *    device (stored in the file system or equivalent) <br>
 *  - Stored in a contiguous area of RAM in the device <br>
 *  - Stored in a non-contiguous area of RAM in the device (stored in the file system
 *    or equivalent)
 *  .
 *  Choose either of the following methods of designating the JAD file so as to allow
 *  the file to be accessed in any of the above cases. <br>
 *  - Designate the address of the memory area storing the JAD file in the jadAddr
 *    parameter, and designate #JK_NULL in jadRead. <br>
 *  - Designate the stream function for reading the JAD file in the jadRead parameter, and
 *    designate #JK_NULL in jadAddr.
 *  .
 *  </small>
 * @see AamsDescriptorClose()
 */
JKAmsDescHandle AamsJadOpen(JKAmsEnvHandle hEnv, JKSint32 jadSize,
                            const void *jadAddr,
                            JKAmsAppInfoStreamReader jadRead,
                            JKSint32 * errorCode);

/**
 *  Creates a handle for accessing the manifest file in the JAR file.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hJar
 *         The JAR file handle obtaind by #AamsJarOpen().<br>
 *         Be sure to keep this handle until operations on the manifest file have
 *         finished and #AamsDescriptorClose() is called.
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function.<br>
 *         Designate #JK_NULL if no error code needs to be fetched.<br>
 *         One of the following values is put in this memory area. <br>
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: #JK_INVALID_HANDLE was designated
 *           in the hEnv or hJar parameter <br>
 *         - #JK_AMS_IO_ERROR: There is no manifest file in the JAR file<br>
 *         - #JK_AMS_OUT_OF_MEMORY_ERROR: Could not allocate the memory space
 *           needed for manifest file analysis<br>
 *         - #JK_AMS_ILLEGAL_FORMAT_ERROR: The manifest file format is illegal
 *         .
 *  @return
 *         - Not #JK_INVALID_HANDLE: The manifest file handle (succeeded) <br>
 *         - #JK_INVALID_HANDLE: failed
 *         .
 *
 *  Call this function before accessing the manifest file in the JAR file to get or
 *  verify its data. <br>
 *  When the handle obtained by this function is no longer needed, call
 *  #AamsDescriptorClose().
 *
 *  If there is no manifest file in the JAR file, this function fails.
 *
 *  The notation in the manifest file must be in a format conforming to the MIDP
 *  specification.<br>
 *  If a format that cannot be processed as a manifest file is detected, this function
 *  fails.<br>
 *  If a MIDlet attribute is designated more than once, the last attribute value designation
 *  is valid.
 * @see AamsDescriptorClose()
 */
JKAmsDescHandle AamsManifestOpen(JKAmsEnvHandle hEnv, JKAmsJarHandle hJar,
                                 JKSint32 * errorCode);


/**
 *  Disposes of the handle of a JAD file, manifest file or merged data from the two.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hDesc
 *         The handle of the JAD file, manifest file or merged data.
 *         Designate the handle obtained by #AamsJadOpen(), #AamsManifestOpen(), or
 *         #AamsMIDletMergeDescriptors().
 *  @return
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Either of the following cases (failed)<br>
 *           - #JK_INVALID_HANDLE was designated in the hEnv or hDesc parameter <br>
 *           - The handle designated in the hDesc parameter was not created by 
 *             AamsJadOpen(), AamsManifestOpen(), or AamsMIDletMergeDescriptors() <br>
 *           .
 *         .
 *
 *  Do not dispose of the JAD file and manifest file handles used for the merge
 *  until the merged data handle has been disposed of.
 * @see AamsJadOpen() @see AamsManifestOpen() @see AamsMIDletMergeDescriptors()
 */
JKSint32 AamsDescriptorClose(JKAmsEnvHandle hEnv, JKAmsDescHandle hDesc);

/**
 *  Creates a handle for accessing a JAR file.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param jarSize
 *         The size (in bytes) of the JAR file
 *  @param jarAddr
 *         A pointer to the buffer holding the JAR file.<br>
 *         If #JK_NULL is designated, the JAR file will be read by the callback function
 *         designated in the  parameter jarRead.
 *  @param jarRead
 *         A pointer to the stream function (callback function) for reading the JAR file. <br>
 *         If #JK_NULL is designated, the JAR file in the buffer designated in the
 *         parameter jarAddr is referenced.
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function.<br>
 *         Designate #JK_NULL if no error code needs to be fetched.<br>
 *         One of the following values is put in this memory area.<br>
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Either of the following cases<br>
 *           - #JK_INVALID_HANDLE was designated in the hEnv parameter <br>
 *           - #JK_NULL was designated in the jarAddr and jarRead parameters
 *           .
 *         - #JK_AMS_INVALID_JARSIZE_ERROR: A negative value was designated in
 *           the jarSize parameter<br>
 *         - #JK_AMS_OUT_OF_MEMORY_ERROR: Could not designate the memory area
 *           for opening the JAR file <br>
 *         - #JK_AMS_IO_ERROR: An error occurred while reading the JAR file<br>
 *         - #JK_AMS_ILLEGAL_FORMAT_ERROR: Illegal JAR file format
 *         .
 *  @return
 *         - Not #JK_INVALID_HANDLE: The JAR file handle (succeeded) <br>
 *         - #JK_INVALID_HANDLE: failed
 *
 *  Call this function before accessing the JAR file to get or verify its data. <br>
 *  When the handle obtained by this function is no longer needed, call
 *  #AamsJarClose().
 *
 *  A value must be set in either jarAddr or jarRead. <br>
 *  If both are designated, the value designated in jarAddr is used.<br>
 *  During the time the JAR file handle returned by this function is in use for
 *  subsequent processing, be sure to retain the contents of the buffer or
 *  read stream containing the JAR file.
 *
 *  <small>
 *  <b>Notes:</b><br>
 *  Some possible ways of storing the JAR file include the following.
 *  - Stored in a contiguous area in flash ROM or other storage built into the device
 *  - Stored in a non-contiguous area in flash ROM or other storage built into the
 *    device (stored in the file system or equivalent)
 *  - Stored in a contiguous area of RAM in the device
 *  - Stored in a non-contiguous area of RAM in the device (stored in the file system
 *    or equivalent)
 *  .
 *  Choose either of the following methods of designating the JAR file so as to allow
 *  the file to be accessed in any of the above cases.
 *  - Designate the address of the JAR memory area in the jarAddr parameter,
 *    and designate #JK_NULL in jarRead.
 *  - Designate the stream function for reading the JAR file in the jarRead parameter, and
 *    designate #JK_NULL in jarAddr.
 *  .
 *  </small>
 * @see AamsJarClose()
 */
JKAmsJarHandle AamsJarOpen(JKAmsEnvHandle hEnv, JKSint32 jarSize,
                           const void *jarAddr,
                           JKAmsAppInfoStreamReader jarRead,
                           JKSint32 * errorCode);

/**
 *  Disposes of a JAR file handle.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize().
 *  @param hJar
 *         The handle of the JAR file.
 *         Designate the handle obtained by #AamsJarOpen().
 *  @return
 *         - #JK_AMS_OK: succeeded
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: #JK_INVALID_HANDLE was designated
 *           in the hEnv or hJar parameter (failed)
 *         .
 *
 * Do not call this function while the manifest file in the JAR file is being accessed,
 * until #AamsDescriptorClose() is called.
 * @see AamsJarOpen() @see AamsManifestOpen() @see AamsDescriptorClose()
 */
JKSint32 AamsJarClose(JKAmsEnvHandle hEnv, JKAmsJarHandle hJar);

/**
 *  Verifies conformity of a JAD file to the MIDP specification.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hJad
 *         The handle of the JAD file.
 *         Designate the handle obtained by #AamsJadOpen().
 *  @return
 *         - #JK_AMS_OK: Conforms to MIDP specification<br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR:  Either of the following cases<br>
 *           - #JK_INVALID_HANDLE was designated in the hEnv or hJad parameter<br>
 *           - The handle designated in the hJad parameter was not created by AamsJadOpen()<br>
 *           .
 *         - #JK_AMS_NO_MIDLET_NAME_ERROR: No MIDlet-Name entry in the JAD file <br>
 *         - #JK_AMS_NO_MIDLET_VENDOR_ERROR: No MIDlet-Vendor entry in the JAD
 *           file <br>
 *         - #JK_AMS_NO_MIDLET_VERSION_ERROR: No MIDlet-Version entry in the
 *           JAD file <br>
 *         - #JK_AMS_NO_MIDLET_JAR_URL_ERROR: No MIDlet-Jar-URL entry in the
 *           JAD file <br>
 *         - #JK_AMS_NO_MIDLET_JAR_SIZE_ERROR: No MIDlet-Jar-Size entry in the
 *           JAD file <br>
 *         - #JK_AMS_ILLEGAL_FORMAT_ERROR: Format error in MIDlet-Version or
 *           MIDlet-<n> designation<br>
 *         - #JK_AMS_INVALID_VALUE_LENGTH_ERROR: Length of
 *           MIDlet-Install-Notify or MIDlet-Delete-Notify exceeds 256
 *           characters
 *         - #JK_AMS_CONFIGURATION_NOT_SUPPORTED_ERROR: A configuration not supported by
 *           JBlend is designated for the MicroEdition-Configuration attribute<br>
 *         - #JK_AMS_PROFILE_NOT_SUPPORTED_ERROR: A profile not supported by JBlend
 *           is designated for the MicroEdition-Profile attribute<br>
 *         - #JK_AMS_RUNTIME_EXECUTION_ENVIRONMENT_NOT_SUPPORTED_ERROR:
 *           A value not supported by JBlend is set for the 
 *           Runtime-Execution-Environment attribute.
 *         - #JK_AMS_ENVIRONMENT_CONFIGURATION_MISMATCH_ERROR:
 *           The value set for the Runtime-Execution-Environment attribute does 
 *           not match the value set for the MicroEdition-Configuration attribute.
 *         .
 *
 *  This function checks the JAD file designated by hJad for conformity to the MIDP
 *  specification. The following conditions are checked.<br>
 *  - That the following MIDlet attributes whose designation in the JAD file is mandatory are in fact designated.
 *    - MIDlet-Name
 *    - MIDlet-Vendor
 *    - MIDlet-Version
 *    - MIDlet-Jar-URL
 *    - MIDlet-Jar-Size
 *    .
 *  - That individual attributes are designated in the correct format.<br>
 *    Checked attributes:
 *    - MIDlet-Version
 *    - MIDlet-@<n@>
 *    .
 *  - That the MicroEdition-Configuration attribute indicates the configuration supported by JBlend.
 *  - That the MicroEdition-Profile attribute indicates the profile supported by JBlend.
 *  - That the attribute value length does not exceed 256 characters.<br>
 *    Checked attributes:
 *    - MIDlet-Install-Notify
 *    - MIDlet-Delete-Notify
 *    .
 *  - That the following conditions are met if the Runtime-Execution-Environment attribute is designated.
 *    - A value supported by JBlend is set.
 *    - The value matches that set for the MicroEdition-Configuration attribute.
 *    .
 *  .
 *
 *  If the MicroEdition-Profile attribute contains a string other than the
 *  profile supported by JBlend, #JK_AMS_PROFILE_NOT_SUPPORTED_ERROR is
 *  returned.
 *  See the explanation of AamsJBlendGetProperty() regarding profiles
 *  supported by JBlend.
 * @see AamsJadOpen()
 */
JKSint32 AamsJadVerify(JKAmsEnvHandle hEnv, JKAmsDescHandle hJad);

/**
 *  Verifies conformity of a manifest file to the MIDP specification.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hManifest
 *         The manifest file handle
 *         Designate the handle obtained by #AamsManifestOpen().
 *  @return
 *         - #JK_AMS_OK: Conforms to MIDP specification<br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Either of the following cases<br>
 *           - #JK_INVALID_HANDLE was designated in the hEnv or hManifest parameter<br>
 *           - The handle designated in hManifest parameter was not created by AamsManifestOpen()<br>
 *           .
 *         - #JK_AMS_NO_MIDLET_NAME_ERROR: No MIDlet-Name entry in the manifest
 *           file <br>
 *         - #JK_AMS_NO_MIDLET_VENDOR_ERROR: No MIDlet-Vendor entry in the
 *           manifest file <br>
 *         - #JK_AMS_NO_MIDLET_VERSION_ERROR: No MIDlet-Version entry in the
 *           manifest file <br>
 *         - #JK_AMS_ILLEGAL_FORMAT_ERROR: Format error in MIDlet-Version or
 *           MIDlet-@<n@> designation <br>
 *         - #JK_AMS_INVALID_VALUE_LENGTH_ERROR: Length of
 *           MIDlet-Install-Notify or MIDlet-Delete-Notify exceeds 256
 *           characters
 *         .
 *
 *  This function checks the  manifest file designated by hManifest for conformity to the
 *  MIDP specification. The following conditions are checked.<br>
 *  - That the following MIDlet attributes whose designation in the manifest file is mandatory are in fact designated.
 *    - MIDlet-Name
 *    - MIDlet-Vendor
 *    - MIDlet-Version
 *    .
 *  - That individual attributes are designated in the correct format.<br>
 *    Checked attributes:
 *    - MIDlet-Version
 *    - MIDlet-@<n@>
 *    .
 *  - That the attribute value length does not exceed 256 characters.<br>
 *    Checked attributes:
 *    - MIDlet-Install-Notify
 *    - MIDlet-Delete-Notify
 *    .
 *  .
 * @see AamsManifestOpen()
 */
JKSint32 AamsManifestVerify(JKAmsEnvHandle hEnv, JKAmsDescHandle hManifest);

/**
 *  Checks for consistency between the MIDlet attributes designated in a JAD file and
 *  a manifest file.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hJad
 *         The JAD file handle.
 *         Designate the handle obtained by #AamsJadOpen().
 *         If there is no JAD file, designate #JK_INVALID_HANDLE.
 *  @param hManifest
 *         The manifest file handle.
 *         Designate the handle obtained by #AamsManifestOpen().
 *  @param isTrusted
 *         Information indicating whether the application to be verified for consistency
 *         is a trusted MIDlet suite.
 *         Designate either of the following values.<br>
 *         - #JK_TRUE: A trusted MIDlet suite
 *         - #JK_FALSE: An untrusted MIDlet suite
 *         .
 *  @return
 *         - #JK_AMS_OK: The JAD file and manifest file entries are
 *            consistent<br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR:  Any of the following cases<br>
 *           - #JK_INVALID_HANDLE was designated in the hEnv or hManifest parameter <br>
 *           - The handle designated in the hManifest parameter was not created by AamsManifestOpen()<br>
 *           - For an untrusted MIDlet suite, the handle designated in the 
 *             hJad parameter is not #JK_INVALID_HANDLE, and it
 *             was not created by AamsJadOpen().<br>
 *           - #JK_INVALID_HANDLE was designated in the hJad parameter for a trusted MIDlet suite <br>
 *           - The handle designated in the hJad parameter was not created by AamsJadOpen() for a trusted MIDlet suite<br>
 *           .
 *         - #JK_AMS_NOT_IDENTICAL_VALUES_ERROR: Different attribute values are
 *           designated in the JAD file and manifest file of a trusted MIDlet
 *           suite <br>
 *         - #JK_AMS_MIDLET_NAME_NOT_IDENTICAL_ERROR: MIDlet-Name was assigned
 *           different values in the JAD file and manifest file of an untrusted
 *           MIDlet suite <br>
 *         - #JK_AMS_MIDLET_VENDOR_NOT_IDENTICAL_ERROR: MIDlet-Vendor was assigned
 *           different values in the JAD file and manifest file of an untrusted
 *           MIDlet suite<br>
 *         - #JK_AMS_MIDLET_VERSION_NOT_IDENTICAL_ERROR: MIDlet-Version was
 *           assigned different values in the JAD file and manifest file of an
 *           untrusted MIDlet suite<br>
 *         - #JK_AMS_NO_MICROEDITION_PROFILE_ERROR: MicroEdition-Profile entry
 *           is missing in both the JAD file and manifest file <br>
 *         - #JK_AMS_NO_MICROEDITION_CONFIGURATION_ERROR:
 *           MicroEdition-Configuration entry is missing in both the JAD file and
 *           manifest file <br>
 *         - #JK_AMS_NO_MIDLET_1_ERROR: MIDlet-1 entry is missing in both the JAD
 *           file and manifest file
 *         - #JK_AMS_CONFIGURATION_NOT_SUPPORTED_ERROR: A configuration not supported by
 *           JBlend is designated for MicroEdition-Configuration attribute<br>
 *         - #JK_AMS_PROFILE_NOT_SUPPORTED_ERROR: A profile not supported by JBlend
 *           is designated for MicroEdition-Profile attribute<br>
 *         - #JK_AMS_RUNTIME_EXECUTION_ENVIRONMENT_NOT_SUPPORTED_ERROR:
 *           A value not supported by JBlend is set for the Runtime-Execution-Environment attribute.
 *         - #JK_AMS_ENVIRONMENT_CONFIGURATION_MISMATCH_ERROR:
 *           The value set for the Runtime-Execution-Environment attribute does not match the value set for the MicroEdition-Configuration attribute.
 *         .
 *
 *  Of the MIDlet attributes designated in the JAD file and manifest file designated by
 *  hJad and hManifest, this function checks for consistency of those that must match
 *  according to the MIDP specification.
 *
 *  The following conditions are checked.<br>
 *  <b>For an untrusted MIDlet</b><br>
 *  - That identical values are designated for the following attributes
 *    - MIDlet-Name
 *    - MIDlet-Vendor
 *    - MIDlet-Version
 *    .
 *  - That the following attributes are designated in either the JAD file or manifest file
 *    - MIDlet-1
 *    - MicroEdition-Configuration
 *    - MicroEdition-Profile
 *    .
 *  - That the MicroEdition-Configuration attribute indicates the configuration supported by JBlend.
 *  - That the MicroEdition-Profile attribute indicates the profile supported by JBlend.
 *  - That the following conditions are met if the Runtime-Execution-Environment attribute is designated.
 *    - A value supported by JBlend is set.
 *    - The value matches that set for the MicroEdition-Configuration attribute.
 *    .
 *  .
 *  <b>For a trusted MIDlet</b><br>
 *  In addition to the conditions checked for an untrusted MIDlet, the following condition is checked.<br>
 *  - That all attributes designated in both the JAD file and manifest file have the same values in both.
 *  .
 *
 *  This check must be performed even if there is no JAD file.
 *
 *  This function presupposes that the JAD file and manifest file designated in
 *  the hJad and hManifest parameters conform to the MIDP specification.<br>
 *  Use AamsJadVerify() and AamsManifestVerify() to verify this conformance.
 *
 *  If the MicroEdition-Profile attribute contains a string other than the
 *  profile supported by JBlend, #JK_AMS_PROFILE_NOT_SUPPORTED_ERROR is
 *  returned.
 *  See the explanation of AamsJBlendGetProperty() regarding profiles
 *  supported by JBlend.
 * @see AamsJadOpen() @see AamsManifestOpen()
 */
JKSint32 AamsMIDletVerify(JKAmsEnvHandle hEnv, JKAmsDescHandle hJad,
                          JKAmsDescHandle hManifest, JKBool isTrusted);

/**
 *  Merges MIDlet attributes from the JAD file and manifest file.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize().
 *  @param hJad
 *         The JAD file handle.
 *         Designate the handle obtained by #AamsJadOpen().
 *  @param hManifest
 *         The manifest file handle.
 *         Designate the handle obtained by #AamsManifestOpen().
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function.<br>
 *         Designate #JK_NULL if no error code needs to be fetched.<br>
 *         One of the following values is put in this memory area.<br>
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Either of the following cases<br>
 *           - #JK_INVALID_HANDLE was designated for one of the parameters hEnv, hJad, or hManifest <br>
 *           - The handle designated in the hJad or hManifest parameter was not created by #AamsJadOpen() or #AamsManifestOpen()<br>
 *           .
 *         - #JK_AMS_OUT_OF_MEMORY_ERROR: Could not allocate the memory space
 *           needed for storing the merge result
 *         .
 *  @return
 *         - Not #JK_INVALID_HANDLE: The handle of the merged data (succeeded) <br>
 *         - #JK_INVALID_HANDLE: failed
 *
 *  This function merges MIDlet attributes designated in a JAD file and a manifest file.
 *
 *  This function presupposes that the JAD file and manifest file designated in
 *  the hJad and hManifest parameters conform to the MIDP specification.<br>
 *  Use AamsJadVerify(), AamsManifestVerify(), and AamsMIDletVerify() to verify
 *  this conformance.
 *
 *  If MIDlet entries for the same keyword are described in both files, only
 *  the JAD file designation is valid and is merged into the result.
 *
 *  Even after this function merges MIDlet attributes, the memory areas of the JAD file and
 *  manifest file are not released in this function.<br>
 *  Do not dispose of the JAD file and manifest file handles used for the merge
 *  until the merged data handle has been disposed of.
 * @see AamsJadOpen() @see AamsManifestOpen()
 */
JKAmsDescHandle AamsMIDletMergeDescriptors(JKAmsEnvHandle hEnv,
                                           JKAmsDescHandle hJad,
                                           JKAmsDescHandle hManifest,
                                           JKSint32 * errorCode);

/**
 *  Gets the character string of a MIDlet attribute.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hDesc
 *         The MIDlet attribute data handle.<br>
 *         Designate the handle obtained by #AamsJadOpen(), #AamsManifestOpen(), or
 *         #AamsMIDletMergeDescriptors().
 *  @param keyId
 *         An identifier of the MIDlet attribute keyword<br>
 *         The following identifiers can be designated.<br>
 *         #JK_AMS_ATTR_ID_JAR_URL, #JK_AMS_ATTR_ID_JAR_SIZE, #JK_AMS_ATTR_ID_NAME,
 *         #JK_AMS_ATTR_ID_VERSION, #JK_AMS_ATTR_ID_VENDOR, #JK_AMS_ATTR_ID_PROFILE,
 *         #JK_AMS_ATTR_ID_CONFIGURATION, #JK_AMS_ATTR_ID_DESCRIPTION,
 *         #JK_AMS_ATTR_ID_ICON, #JK_AMS_ATTR_ID_INFO_URL, #JK_AMS_ATTR_ID_DATA_SIZE,
 *         #JK_AMS_ATTR_ID_PERMISSIONS, #JK_AMS_ATTR_ID_PERMISSIONS_OPT,
 *         #JK_AMS_ATTR_ID_INSTALL_NOTIFY, #JK_AMS_ATTR_ID_DELETE_NOTIFY,
 *         #JK_AMS_ATTR_ID_DELETE_CONFIRM, #JK_AMS_ATTR_ID_RSA_SHA1, 
 *         #JK_AMS_ATTR_ID_RUNTIME_EXECUTION_ENVIRONMENT
 *  @param valueLen
 *         A pointer to the memory area for receiving the string length of the MIDlet attribute in bytes.
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function.<br>
 *         Designate #JK_NULL if no error code needs to be fetched.<br>
 *         One of the following values is put in this memory area.<br>
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Either of the following cases<br>
 *           - #JK_INVALID_HANDLE was designated in the hEnv or hDesc parameter<br>
 *           - The handle designated in the hDesc parameter was not created by
 *             AamsJadOpen(), AamsManifestOpen(), or AamsMIDletMergeDescriptors()<br>
 *           .
 *         - #JK_AMS_NO_SUCH_ENTRY_ERROR: No such MIDlet attribute <br>
 *         - #JK_AMS_UNKNOWN_ID_ERROR: Unknown keyId
 *         .
 *  @return
 *         A pointer to the MIDlet attribute string. <br>
 *         The pointer is valid only while the handle designated in hDesc is
 *         valid.
 *
 *  This function gets the character string of the MIDlet attribute designated by its
 *  defined identifier.
 *  If no identifier is defined for a MIDlet, call #AamsDescriptorGetValueByKey() to get its
 *  character string.
 * @see AamsDescriptorGetValueByKey() @see AamsJadOpen() @see AamsManifestOpen() @see AamsMIDletMergeDescriptors()
 */
const JKUTF8Char *AamsDescriptorGetValue(JKAmsEnvHandle hEnv,
                                         JKAmsDescHandle hDesc,
                                         JKSint32 keyId,
                                         JKSint32 * valueLen,
                                         JKSint32 * errorCode);

/**
 *  Gets the character string of a MIDlet attribute by designating its keyword.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hDesc
 *         The MIDlet attribute data handle.<br>
 *         Designate the handle obtained by #AamsJadOpen(), #AamsManifestOpen(), or
 *         #AamsMIDletMergeDescriptors().
 *  @param key
 *         A pointer to the memory area holding the MIDlet attribute keyword
 *  @param keyLen
 *         The size (in bytes) of the MIDlet attribute keyword
 *  @param valueLen
 *         A pointer to the memory area for receiving the string length of the MIDlet attribute in bytes.
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function.<br>
 *         Designate #JK_NULL if no error code needs to be fetched.<br>
 *         One of the following values is put in this memory area.<br>
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Either of the following cases<br>
 *           - #JK_INVALID_HANDLE was designated in the hEnv or hDesc parameter<br>
 *           - The handle designated in the hDesc parameter was not created by
 *             AamsJadOpen(), AamsManifestOpen(), or AamsMIDletMergeDescriptors()<br>
 *           .
 *         - #JK_AMS_NO_SUCH_ENTRY_ERROR: No MIDlet entry
 *         .
 *  @return
 *         A pointer to the MIDlet attribute string. <br>
 *         The pointer is valid only while the handle designated in hDesc is
 *         valid.
 *
 *  The function gets the character string of a MIDlet attribute designated by its keyword.
 *  This function is for getting the character strings of MIDlet attributes that do not
 *  have keywords defined in JBlend (e.g., attributes defined independently in
 *  a Java application).
 *  Use #AamsDescriptorGetValue() to get the character strings of MIDlet attributes with
 *  keywords defined in JBlend.
 * @see AamsDescriptorGetValue() @see AamsJadOpen() @see AamsManifestOpen() @see AamsMIDletMergeDescriptors()
 */
const JKUTF8Char *AamsDescriptorGetValueByKey(JKAmsEnvHandle hEnv,
                                              JKAmsDescHandle hDesc,
                                              const JKUTF8Char * key,
                                              JKSint32 keyLen,
                                              JKSint32 * valueLen,
                                              JKSint32 * errorCode);


/**
 *  Gets the size of icon data designated by the MIDlet-Icon attribute.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hDesc
 *         The MIDlet attribute data handle.<br>
 *         Designate the handle obtained by #AamsJadOpen(), #AamsManifestOpen(), or
 *         #AamsMIDletMergeDescriptors().
 *  @param hJar
 *         The JAR file handle.
 *         Designate the handle obtained by #AamsJarOpen().
 *  @return
 *         - Value of 0 or more: The size (in bytes) of the icon data (succeeded)
 *         - One of the following: failed<br>
 *           - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Either of the following cases<br>
 *             - #JK_INVALID_HANDLE was designated for the parameters hEnv, hDesc, or hJar. <br>
 *             - The handle designated in the hDesc parameter was not created by
 *               AamsJadOpen(), AamsManifestOpen(), or AamsMIDletMergeDescriptors()<br>
 *             .
 *           - #JK_AMS_NO_SUCH_ENTRY_ERROR: MIDlet-Icon not designated <br>
 *           - #JK_AMS_IO_ERROR: Could not access icon data <br>
 *           - #JK_AMS_OUT_OF_MEMORY_ERROR: Out of memory
 *           .
 *         .
 * @see AamsMIDletGetIconData() @see AamsJadOpen() @see AamsManifestOpen() @see AamsMIDletMergeDescriptors() @see AamsJarOpen()
 */
JKSint32 AamsMIDletGetIconSize(JKAmsEnvHandle hEnv, JKAmsDescHandle hDesc,
                               JKAmsJarHandle hJar);

/**
 *  Gets the icon data designated by the MIDlet-Icon attribute.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hDesc
 *         The MIDlet attribute data handle.<br>
 *         Designate the handle obtained by #AamsJadOpen(), #AamsManifestOpen(), or
 *         #AamsMIDletMergeDescriptors().
 *  @param hJar
 *         The JAR file handle.
 *         Designate the handle obtained by #AamsJarOpen().
 *  @param buffer
 *         A pointer to the buffer for receiving the icon data
 *  @param bufferSize
 *         The size (in bytes) of the icon data buffer.
 *         The byte value obtained by #AamsMIDletGetIconSize() can be designated.
 *  @return
 *         - Value of 0 or more: The actual size (in bytes) of obtained icon data (succeeded)
 *         - One of the following: failed<br>
 *           - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Either of the following cases<br>
 *             - #JK_INVALID_HANDLE was designated for the parameters hEnv, hDesc, or hJar <br>
 *             - The handle designated in the hDesc parameter was not created by 
 *               AamsJadOpen(), AamsManifestOpen(), or AamsMIDletMergeDescriptors()(failed)<br>
 *             .
 *           - #JK_AMS_NO_SUCH_ENTRY_ERROR: MIDlet-Icon not designated <br>
 *           - #JK_AMS_IO_ERROR: Could not access icon data <br>
 *           - #JK_AMS_OUT_OF_MEMORY_ERROR: Out of memory
 *           .
 *         .
 *  Gets from the JAR file the icon data (in PNG format) having the file name
 *  designated in the MIDlet-Icon attribute.
 * @see AamsMIDletGetIconSize() @see AamsJadOpen() @see AamsManifestOpen() @see AamsMIDletMergeDescriptors() @see AamsJarOpen()
 */
JKSint32 AamsMIDletGetIconData(JKAmsEnvHandle hEnv, JKAmsDescHandle hDesc,
                               JKAmsJarHandle hJar, void *buffer,
                               JKSint32 bufferSize);

/**
 *  Gets the size of entry data archived in a JAR file.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hJar
 *         The handle of the JAR file.
 *         Designate the handle obtained by AamsJarOpen(). 
 *  @param path
 *         The path of entry data archived in a JAR file.
 *         Designate as in the examples below. 
 *           - file1.jpg
 *           - dir1/file2.png
 *           - dir1/dir2/file3.jpg
 *           - META-INF/MANIFEST.MF
 *           .
 *         Putting a slash "/" at the beginning of a path makes the path illegal, causing
 *         the function to fail.
 *  @param pathLen
 *         The length (in bytes) of the path designated in the <i>path</i> parameter.
 *  @return
 *         - Value of 0 or more: The size (in bytes) of the entry data (succeeded)
 *         - One of the following: failed<br>
 *           - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Illegal argument <br>
 *           - #JK_AMS_IO_ERROR: Could not access the entry data <br>
 *           - #JK_AMS_OUT_OF_MEMORY_ERROR: Out of memory
 *           .
 *         .
 *  <p>
 *  This function sets in the return value the size of the JAR file entry data 
 *  located on the path designated in the <i>path</i> parameter.
 *  
 *  In the native system, when getting entry data in a JAR file, allocate a memory
 *  space for storing the data based on the size obtained by this function, then 
 *  call AamsJarGetEntryData().
 *  
 *  This function is provided as an aid in implementing extended specifications outside of 
 *  MIDP or in creating an application original to the native system. 
 *  The use of this function is not necessary if the device manufacturer implements only the
 *  AMS specified in MIDP.
 * @see AamsJarGetEntryData()
 */
JKSint32 AamsJarGetEntrySize(JKAmsEnvHandle hEnv, JKAmsJarHandle hJar,
                             const JKUTF8Char * path, JKSint32 pathLen);

/**
 *  Gets the entry data archived in a JAR file.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hJar
 *         The handle of the JAR file.
 *         Designate the handle obtained by AamsJarOpen(). 
 *  @param path
 *         The path of entry data archived in a JAR file.
 *         Designate as in the examples below. 
 *           - file1.jpg
 *           - dir1/file2.png
 *           - dir1/dir2/file3.jpg
 *           - META-INF/MANIFEST.MF
 *           .
 *         Putting a slash "/" at the beginning of a path makes the path illegal, causing
 *         the function to fail.
 *  @param pathLen
 *         The length (in bytes) of the path designated in the <i>path</i> parameter.
 *  @param buffer
 *         A pointer to the buffer for receiving the entry data.
 *  @param bufferSize
 *         The length (in bytes) of the memory area indicated by the <i>buffer</i> parameter.
 *         Pass the length obtained by AamsJarGetEntrySize(). 
 *  @return
 *         - Value of 0 or more: The size (in bytes) of the entry data (succeeded)
 *         - One of the following: failed<br>
 *           - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Illegal argument <br>
 *           - #JK_AMS_IO_ERROR: Could not access the entry data <br>
 *           - #JK_AMS_OUT_OF_MEMORY_ERROR: Out of memory
 *           .
 *         .
 *  <p>
 *  This function puts in the memory space indicated by the <i>buffer</i> parameter the JAR file 
 *  entry data on the path designated by the <i>path</i> parameter. 
 *  Designate in buffer a pointer to a memory space allocated in advance by the device
 *  manufacturer based on the size obtained by #AamsJarGetEntrySize().
 *  
 *  This function is provided as an aid in implementing extended specifications outside of 
 *  MIDP or in creating an application original to the native system. 
 *  The use of this function is not necessary if the device manufacturer implements only the
 *  AMS specified in MIDP.
 * @see AamsJarGetEntrySize()
 */
JKSint32 AamsJarGetEntryData(JKAmsEnvHandle hEnv, JKAmsJarHandle hJar,
                             const JKUTF8Char * path, JKSint32 pathLen,
                             void *buffer, JKSint32 bufferSize);

/**
 *  Gets the version information designated in the MIDlet-Version attribute.
 *  @param hEnv
 *         The application information analysis functions environment handle obtained by
 *         #AamsEnvInitialize()
 *  @param hDesc
 *         The MIDlet attribute data handle.<br>
 *         Designate the handle obtained by #AamsJadOpen(), #AamsManifestOpen(), or
 *         #AamsMIDletMergeDescriptors().
 *  @param major
 *         A pointer to the buffer for receiving the numerical value of the major version
 *         number. #JK_NULL cannot be designated.
 *  @param minor
 *         A pointer to the buffer for receiving the numerical value of the minor version
 *         number. #JK_NULL cannot be designated.
 *  @param micro
 *         A pointer to the buffer for receiving the numerical value of the micro version
 *         number. #JK_NULL cannot be designated.
 *  @return
 *         - #JK_AMS_OK: succeeded
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Any of the following cases (failed)<br>
 *           - #JK_INVALID_HANDLE was designated in the hEnv or hDesc parameter<br>
 *           - #JK_NULL was designated for the parameters major, minor, or micro<br>
 *           - The handle designated in the hDesc parameter was not created by 
 *             AamsJadOpen(), AamsManifestOpen(), or AamsMIDletMergeDescriptors()<br>
 *           .
 *         .
 *
 * This function gets the major version, minor version, and micro version specified
 * in the following MIDlet-Version attribute format. (The string in [] can be omitted.)
 *
 * major.minor[.micro] <br>
 *
 * See the MIDP specification for details of version information given in the
 * MIDlet-Version attribute.
 * @see AamsJadOpen() @see AamsManifestOpen() @see AamsMIDletMergeDescriptors()
 */
JKSint32 AamsMIDletGetVersion(JKAmsEnvHandle hEnv, JKAmsDescHandle hDesc,
                              JKSint32 * major, JKSint32 * minor,
                              JKSint32 * micro);


/**
 *  Gets the integer value from a character string expressing a numerical value.
 *  @param str
 *         A pointer to the memory area holding the character string (encoded in UTF-8)
 *         expressing a numerical value
 *  @param strLen
 *         The size (in bytes) of the character string
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function.<br>
 *         Designate #JK_NULL if no error code needs to be fetched.<br>
 *         One of the following values is put in this memory area.<br>
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: #JK_NULL was designated in str, or
 *           a value of 0 or less was designated in strLen parameter<br>
 *         - #JK_AMS_ILLEGAL_FORMAT_ERROR: The string format is incorrect for a
 *           numerical value <br>
 *         - #JK_AMS_OVERFLOW_ERROR: A numerical overflow occurred
 *         .
 *  @return
 *         The resulting integer: succeeded
 *
 *  This function gets the integer value of a string expressing a
 *  numerical value. <br>
 *  The string must consist of numerical digits only, or of numerical
 *  digits only prefixed by a plus sign (+) or minus sign (-).
 *  The string cannot contain a blank character. <br>
 *  Attempting to convert a string that does not meet the above
 *  conditions will have uncertain results.
 */
JKSint32 AamsStringToInteger(const JKUTF8Char * str, JKSint32 strLen,
                             JKSint32 * errorCode);


/**
 *  Searches for a string and gets the position of its delimiter character.
 *  @param str
 *         A pointer to the memory location of the search string (encoded in UTF-8)
 *  @param fromIndex
 *         The search start position. The byte at this position is included in
 *         the search.
 *         Designate a byte offset value, with 0 assigned to the initial byte of
 *         the string designated in the str parameter.
 *  @param toIndex
 *         The search end position. The byte at this position is not included
 *         in the search.
 *         Designate a byte offset value, with 0 assigned to the initial byte of
 *         the string designated in the str parameter.
 *  @param delimiter
 *         A pointer to the memory location of the delimiter character (one character
 *         encoded in UTF-8).
 *  @param delimiterLen
 *         The size in bytes of the delimiter character.
 *  @return
 *         - 0 or above: the delimiter position, expressed as the byte offset
 *           value, with 0 assigned to the initial byte of the string designated
 *           in the str parameter (succeeded)
 *         - One of the following: failed<br>
 *           - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Any of the following cases<br>
 *             - #JK_NULL was designated in the str parameter <br>
 *             - A negative value was designated in fromIndex <br>
 *             - A negative value was designated in toIndex <br>
 *             - The value of fromIndex is larger than toIndex <br>
 *             - #JK_NULL was designated in the delimiter parameter<br>
 *             - A value of 0 or less was designated in the delimiter parameter
 *             .
 *           - #JK_AMS_CHAR_NOT_FOUND_ERROR: delimiter not found <br>
 *           .
 *         .
 *         The scope of the search is from the position designated in fromIndex
 *         up to the position designated in toIndex minus 1.
 */
JKSint32 AamsStringIndexOfChar(const JKUTF8Char * str,
                               JKSint32 fromIndex, JKSint32 toIndex,
                               const JKUTF8Char * delimiter,
                               JKSint32 delimiterLen);

/**
 *  Gets the position of a string, found by excluding the preceding and
 *  trailing blank and tab characters from the designated string.
 *  @param str
 *         A pointer to the memory location of the string (encoded in UTF-8)
 *  @param strLen
 *         The size in bytes of the string
 *  @param length
 *         A pointer to the memory space for receiving the byte size of the
 *         string not including blank and tab characters
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function.<br>
 *         Designate #JK_NULL if no error code needs to be fetched.<br>
 *         One of the following values is put in this memory area.<br>
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Any of the following cases (failed) <br>
 *           - #JK_NULL was designated in the str parameter<br>
 *           - A negative value was designated in the strLen parameter<br>
 *           - #JK_NULL was designated in the length parameter
 *           .
 *         .
 *  @return
 *         A pointer to the memory location of the string from which blank and tab
 *         characters were deleted: succeeded<br>
 *         The pointer indicates the initial character of the string
 *         stored in the memory location designated by the str parameter,
 *         ignoring blank and tab characters.<br>
 *
 *  This function searches for the designated character string, not including
 *  preceding or trailing blank (0x20) or tab (0x09) characters.
 */
const JKUTF8Char *AamsStringTrim(const JKUTF8Char * str, JKSint32 strLen,
                                 JKSint32 * length, JKSint32 * errorCode);


/**
 *  Searches for a comma-delimited token in the designated string.
 *  @param str
 *         A pointer to the memory location of the string (encoded in UTF-8)
 *  @param strLen
 *         The size in bytes of the string
 *  @param index
 *         The position of the token to be searched.
 *         Designate the position of the token, with 0 assigned to the initial token.
 *         For example, to get "param2" in "param1, param2, param3," designate 1.
 *  @param length
 *         A pointer to the memory location for receiving the size in bytes of
 *         the token obtained in the search.
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function.<br>
 *         Designate #JK_NULL if no error code needs to be fetched.<br>
 *         One of the following values is put in this memory area.<br>
 *         - #JK_AMS_OK: succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Any of the following cases<br>
 *           - #JK_NULL was designated in the str parameter <br>
 *           - A negative value was designated in strLen<br>
 *           - A negative value was designated in index<br>
 *           - #JK_NULL was designated in length
 *           .
 *         - #JK_AMS_CHAR_NOT_FOUND_ERROR:
 *           A token was not found in the position designated by the index parameter.
 *         .
 *  @return
 *         A pointer to the memory area holding the token found in the search.
 *         (succeeded)<br>
 *         The pointer indicates the initial character of the first token
 *         found in the string designated by the str parameter.
 *
 *  This function searches for a token of the designated position in the 
 *  comma (0x2c) delimited string.
 *  The token searched for by this function does not include preceding 
 *  or trailing space (0x20) or tab characters (0x09).
 *  Since the MIDlet attribute values as specified by MIDP are not enclosed
 *  in quotation marks, a quotation mark in a token is considered part of the
 *  value. 
 *
 *  The #AamsCSVGetCount() and #AamsCSVParse() functions do not retain the
 *  results from the previous time they were called.
 *  For this reason, using a combination of #AamsStringIndexOfChar() and
 *  #AamsStringTrim() for searches is generally faster than using
 *  AamsCSVParse().
 */
const JKUTF8Char *AamsCSVParse(const JKUTF8Char * str,
                               JKSint32 strLen,
                               JKSint32 index,
                               JKSint32 * length, JKSint32 * errorCode);

/**
 *  Gets the number of comma-delimited tokens in the designated string.
 *  @param str
 *         A pointer to the memory location of the string (encoded in UTF-8)
 *  @param strLen
 *         The size in bytes of the string
 *  @return
 *         - 0 or above: The number of tokens (succeeded)<br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: Either of the following cases
 *           (failed) <br>
 *           - #JK_NULL was designated in the str parameter<br>
 *           - A negative value was designated in the strLen parameter
 *           .
 *         .
 *
 * This function returns the count of phrases delimited by commas (0x2c) that
 * are included in the designated string.
 */
JKSint32 AamsCSVGetCount(const JKUTF8Char * str, JKSint32 strLen);




/**
 * @} end of group
 */
/**
 * @addtogroup JBlend_Property_JBI
 * @{
 */

/**
 *  An ID for getting the configuration supported by JBlend <br>
 *  Pass this ID as a parameter when calling #AamsJBlendGetProperty().
 */
#define JK_AMS_JBLEND_ID_SUPPORTED_CONFIGURATION        0

/**
 *  An ID for getting the profile supported by JBlend <br>
 *  Pass this ID as a parameter when calling #AamsJBlendGetProperty().
 */
#define JK_AMS_JBLEND_ID_SUPPORTED_PROFILE              1

/**
 *  An ID for getting the build configuration of JBlend <br>
 *  Pass this ID as a parameter when calling #AamsJBlendGetProperty().
 */
#define JK_AMS_JBLEND_ID_RUNTIME_BUILD_CONFIGURATION    2

/**
 *  An ID for getting the build date of JBlend <br>
 *  Pass this ID as a parameter when calling #AamsJBlendGetProperty().
 */
#define JK_AMS_JBLEND_ID_RUNTIME_BUILD_DATE             3

/**
 *  An ID for getting the build number of JBlend <br>
 *  Pass this ID as a parameter when calling #AamsJBlendGetProperty().
 */
#define JK_AMS_JBLEND_ID_RUNTIME_BUILD_NUMBER           4

/**
 *  An ID for getting the revision number of JBlend <br>
 *  Pass this ID as a parameter when calling #AamsJBlendGetProperty().
 */
#define JK_AMS_JBLEND_ID_RUNTIME_KERNEL_VERSION         5

/**
 *  Gets a string indicating a JBlend property.
 *  @param id
 *         An ID indicating the property to be acquired <br>
 *         The following IDs can be designated.<br>
 *         - #JK_AMS_JBLEND_ID_SUPPORTED_CONFIGURATION<br>
 *           In the case of the JBlend described in this manual,
 *           "CLDC-1.0" or "CLDC-1.1" is returned.<br>
 *           More than one configuration cannot be supported at the same time. <br>
 *         - #JK_AMS_JBLEND_ID_SUPPORTED_PROFILE<br>
 *           If more than one profile is supported, the return string lists
 *           each profile separated by a blank space. <br>
 *           In the case of the JBlend described in this manual, "MIDP-2.0
 *           MIDP-1.0" or  "MIDP-2.1 MIDP-2.0 MIDP-1.0" is returned.
 *         - #JK_AMS_JBLEND_ID_RUNTIME_BUILD_CONFIGURATION<br>
 *         - #JK_AMS_JBLEND_ID_RUNTIME_BUILD_DATE<br>
 *         - #JK_AMS_JBLEND_ID_RUNTIME_BUILD_NUMBER<br>
 *         - #JK_AMS_JBLEND_ID_RUNTIME_KERNEL_VERSION<br>
 *  @param length
 *         A pointer to the memory area for receiving the size in bytes of the
 *         string returned by this function
 *  @param errorCode
 *         A pointer to the memory area for receiving the error code that
 *         indicates the result of the function processing.<br>
 *         One of the following values is put in this memory area.<br>
 *         - #JK_AMS_OK: Succeeded <br>
 *         - #JK_AMS_ILLEGAL_ARGUMENT_ERROR: #JK_NULL was designated in the length parameter<br>
 *         - #JK_AMS_UNKNOWN_ID_ERROR: An illegal ID was designated
 *         .
 *  @return
 *         A pointer to the memory area holding the property string for the
 *         designated ID.<br>
 *         This pointer is valid only while the JBlend libraries are
 *         loaded.
 */
const JKUTF8Char *AamsJBlendGetProperty(JKSint32 id, JKSint32 * length,
                                        JKSint32 * errorCode);

#ifdef __cplusplus
}
#endif
#endif
/**
 * @} end of group
 */
