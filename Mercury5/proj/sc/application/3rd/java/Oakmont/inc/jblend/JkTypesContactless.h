/*
 *   Copyright 2007 Aplix Corporation. All rights reserved.
 */
/**
 *  @file JkTypesContactless.h
 *  Contactless Communication Data Types and Constants
 */

#ifndef ___JKTYPESCONTACTLESS_H__
#define ___JKTYPESCONTACTLESS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 */

/**
 * @addtogroup Contactless_Common_Data_Types_and_Constants
 * @{
 */

/**
 *   Contactless connection handle type
 */
typedef JKHandle JKContactlessConnectionHandle;

/**
 * @name Contactless Target Type
 * @{
 */
/**
 * Target type: A tag containing NFC Forum formatted data. 
 * Corresponds to the <code>TargetType.NDEF_TAG</code> field.
 */
#define JK_CONTACTLESS_TARGET_NDEF_TAG                  (0x0001)
/**
 * Target type: General RFID tag.
 * Corresponds to the <code>TargetType.RFID_TAG</code> field.
 */
#define JK_CONTACTLESS_TARGET_RFID_TAG                  (0x0002)
/**
 * Target type: ISO14443-4 compliant smart card.
 * Corresponds to the <code>TargetType.ISO14443_TAG</code> field.
 */
#define JK_CONTACTLESS_TARGET_ISO14443_CARD             (0x0004)
/**
 * Target type: General visual tag.
 * Corresponds to the <code>TargetType.VISUAL_TAG</code> field.
 *
 * @par Note
 * Visual tag is not supported by JBlend yet as per December 2007.
 */
#define JK_CONTACTLESS_TARGET_VISUAL_TAG                (0x0008)

/** @} */
/**
 * @name NDEF Record Type
 * @{
 */

/**
 * NDEF record type: EMPTY
 */
#define JK_CONTACTLESS_NDEF_RECORD_EMPTY                (0)
/**
 * NDEF record type: NFC_FORUM_RTD
 */
#define JK_CONTACTLESS_NDEF_RECORD_NFC_FORUM_RTD        (1)
/**
 * NDEF record type: MIME
 */
#define JK_CONTACTLESS_NDEF_RECORD_MIME                 (2)
/**
 * NDEF record type: URI
 */
#define JK_CONTACTLESS_NDEF_RECORD_URI                  (3)
/**
 * NDEF record type: EXTERNAL_RTD
 */
#define JK_CONTACTLESS_NDEF_RECORD_EXTERNAL_RTD         (4)
/**
 * NDEF record type: UNKNOWN
 */
#define JK_CONTACTLESS_NDEF_RECORD_UNKNOWN              (5)

/** @} */
/**
 * @name Result Code
 * @{
 */

/**
 * Operation succeeded.
 */
#define JK_CONTACTLESS_OK                               (0)
/**
 * The requested target type or operation is not supported.
 */
#define JK_CONTACTLESS_ERROR_NOT_SUPPORTED              (-1)
/**
 * The number of listeners exeeded a maximum limit defined in the native system.
 */
#define JK_CONTACTLESS_ERROR_EXCEED_MAXIMUM_LISTENER    (-2)
/**
 * The requested hardware has been powered off and is not available now.
 */
#define JK_CONTACTLESS_ERROR_POWER_OFF                  (-3)
/**
 * The write operation is failed due to the tag is out of capacity.
 */
#define JK_CONTACTLESS_ERROR_OUT_OF_CAPACITY            (-4)
/**
 * The JVM is suspended and not able to receive event notifications.
 */
#define JK_CONTACTLESS_ERROR_VM_SUSPENDED               (-5)
/**
 * General error.
 */
#define JK_CONTACTLESS_ERROR_OTHER                      (-128)

/** @} */


/**
 * The structure type for storing the data returned from the native system.
 * This structure is used by the following event notifications:
 * - #JK_CONTACTLESS_EVENT_NDEF_RECORD_DETECTED
 * - #JK_CONTACTLESS_EVENT_NDEF_MESSAGE_READ
 * - #JK_CONTACTLESS_EVENT_ISO14443_DATA_EXCHANGE
 * - #JK_CONTACTLESS_EVENT_RFID_TRANSCEIVE
 */
typedef struct {
    /**
     * A pointer to the buffer storing the data.
     */
    JKUint8    *buffer;

    /**
     * The size in bytes of the data indicated by <i>buffer</i>.
     */
    JKSint32    length;
} JKT_Contactless_Data;


/**
 * The structure type for storing an NDEF record type.
 *
 * @see JkContactlessAddNDEFRecordListener(), JkContactlessRemoveNDEFRecordListener()
 */
typedef struct {
    /**
     * Record type format.
     * One of the following is set.
     * - #JK_CONTACTLESS_NDEF_RECORD_EMPTY
     * - #JK_CONTACTLESS_NDEF_RECORD_NFC_FORUM_RTD
     * - #JK_CONTACTLESS_NDEF_RECORD_MIME
     * - #JK_CONTACTLESS_NDEF_RECORD_URI
     * - #JK_CONTACTLESS_NDEF_RECORD_EXTERNAL_RTD
     * - #JK_CONTACTLESS_NDEF_RECORD_UNKNOWN
     * .
     */
    JKSint32    format;

    /**
     * A pointer to the ASCII-encoded and NUL-terminated string representing the record type name.
     * Record type names must follow the rules defined by the NFC Forum RTDs and the RFCs.
     *
     * Prefixes of the record type names set in this member must be removed.
     * See the specification of the <code>NDEFRecordType</code> class for details of this requirement.
     */
    JKUint8    *name;

    /**
     * The size in bytes of the name indicated by <i>name</i>.
     */
    JKSint32    nameLength;
} JKT_Contactless_NDEFRecordType;


/**
 * The structure type for containing proeprties of a contactless target.
 * The information stored in this structure is used as properties accessible via the 
 * <code>TargetProperties</code> interface.
 *
 * This structure is used by the #JK_CONTACTLESS_EVENT_TARGET_DETECTED event notifications.
 */
typedef struct {
    /**
     * The type of the target.
     * A bitwise-OR of the following values representing the target type is set.
     * - #JK_CONTACTLESS_TARGET_NDEF_TAG
     * - #JK_CONTACTLESS_TARGET_RFID_TAG or #JK_CONTACTLESS_TARGET_ISO14443_CARD <!-- or #JK_CONTACTLESS_TARGET_VISUAL_TAG -->
     * .
     */
    JKUint32    types;

    /**
     * A pointer to the hexadecimal representing the unique identifier (UID) for the target.
     * This information is used for the <code>TargetProperties\#getUid</code> method.
     */
    JKUint8    *uid;

    /**
     * The size in bytes of the uid indicated by <i>uid</i>.
     */
    JKSint32    uidLength;

    /**
     * A pointer to the UTF-8 encoded and NUL-terminated character string representing the 
     * mapping for the application to identify the actual tag type detected.
     * This member is used only when #JK_CONTACTLESS_TARGET_RFID_TAG is set in <i>types</i>.
     * For other target type, #JK_NULL should be set.
     *
     * This information is used for the <code>TargetProperties\#getMapping</code> method.
     * See JSR-257 for details.
     */
    JKUTF8Char *mapping;

	/**
	 * The number of properties.
	 */
    JKSint32    numProperty;

    /**
     * The address of an array of the pointers to property name strings.
     * Each array element stores a pointer to a UTF-8 encoded and NUL-terminated character string that represents 
     * the name of an available property of the target.
     * The value of a property is indicated in the array <i>propertyAttrs</i> at the same array index.
     *
     * The array is terminated with #JK_NULL.
     *
     * This information is used for the <code>TargetProperties\#getProperty</code> method.
     */
    JKUTF8Char **propertyKeys;

    /**
     * The address of an array of the pointers to property value strings.
     * Each array element stores a pointer to a UTF-8 encoded and NUL-terminated character string that represents 
     * the value of an available property of the target.
     *
     * The array is terminated with #JK_NULL.
     *
     * This information is used for the <code>TargetProperties\#getProperty</code> method.
     */
    JKUTF8Char **propertyAttrs;

	/**
	 * The number of urls.
	 */
    JKSint32    numUrl;

    /**
     * The address of an array of the pointers to URL strings that can be used to access the targets indicated by the <i>types</i> member. 
     * The number of bits set in <i>types</i> must be equal to the number of the elements of this array.
     * When #JK_CONTACTLESS_TARGET_NDEF_TAG is set in <i>types</i>, the 1st element of the array must be 
     * the URL to access the NDEF target followed by an element containing the URL to acdess the physical level target.
     */
    JKUTF8Char **urls;
} JKT_Contactless_TargetProperties;


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* not ___JKTYPESCONTACTLESS_H___ */

