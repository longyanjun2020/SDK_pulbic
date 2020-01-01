/**
 * Copyright 2005 Aplix Corporation. All rights reserved.
 *
 * $Id: JkSatsaCommon.h,v 1.18 2007/11/30 09:42:42 yamagami Exp $
 */

/**
 * @file JkSatsaCommon.h
 *   SATSA Data Types and Constants
 *   
 */
/**
 * @addtogroup SATSA_Data_Types
 * @{
 */

#ifndef ___JK_SATSA_COMMON_H
#define ___JK_SATSA_COMMON_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *   Encryption algorithm: RSA
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_CIPHER_ALGORITHM_RSA               (1)

/**
 *   Encryption algorithm: DES (Data Encryption Standard) 
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_CIPHER_ALGORITHM_DES               (2)

/**
 *   Encryption algorithm: DES-EDE
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_CIPHER_ALGORITHM_DESEDE            (3)

/**
 *   Encryption algorithm: AES (Advanced Encryption Standard) 
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_CIPHER_ALGORITHM_AES               (4)

/**
 *   Encryption algorithm: RC4 (Rivest's Cipher 4) 
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_CIPHER_ALGORITHM_RC4               (5)

/**
 *   Block cipher mode: Disabled
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>blockMode</i> parameter.
 */
#define JK_SATSA_CIPHER_BLOCK_NO                    (1)

/**
 *   Block cipher mode: ECB (Electronic Code Book Mode) 
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>blockMode</i> parameter.
 */
#define JK_SATSA_CIPHER_BLOCK_ECB                   (2)

/**
 *   Block cipher mode: CBC (Cipher Block Chaining Mode) 
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>blockMode</i> parameter.
 */
#define JK_SATSA_CIPHER_BLOCK_CBC                   (3)

/**
 *   Block cipher mode: CFB (Cipher Feedback Chaining Mode) 
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>blockMode</i> parameter.
 */
#define JK_SATSA_CIPHER_BLOCK_CFB                   (4)

/**
 *   Block cipher mode: OFB (Output Feedback Chaining Mode) 
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>blockMode</i> parameter.
 */
#define JK_SATSA_CIPHER_BLOCK_OFB                   (5)

/**
 *   Padding: None
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>padding</i> parameter.
 */
#define JK_SATSA_CIPHER_PADDING_NO                  (1)

/**
 *   Padding: PKCS1
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>padding</i> parameter.
 */
#define JK_SATSA_CIPHER_PADDING_PKCS1               (2)

/**
 *   Padding: PKCS5
 *
 *   This is a constant passed to JkSatsaCreateCipher() in the 
 *   <i>padding</i> parameter.
 */
#define JK_SATSA_CIPHER_PADDING_PKCS5               (3)

/**
 *   Encrypt or decrypt: Encrypt
 *
 *   This is a constant passed to JkSatsaInitCipher() in the 
 *   <i>opmode</i> parameter.
 */
#define JK_SATSA_CIPHER_ENCRYPT                     (1)

/**
 *   Encrypt or decrypt: Decrypt
 *
 *   This is a constant passed to JkSatsaInitCipher() in the 
 *   <i>opmode</i> parameter.
 */
#define JK_SATSA_CIPHER_DECRYPT                     (2)

/**
 *   Message digest algorithm: SHA-1
 *
 *   This is a constant passed to JkSatsaCreateDigest() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_DIGEST_SHA1                        (1)

/**
 *   Message digest algorithm: MD2
 *
 *   This is a constant passed to JkSatsaCreateDigest() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_DIGEST_MD2                        (2)

/**
 *   Message digest algorithm: MD5
 *
 *   This is a constant passed to JkSatsaCreateDigest() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_DIGEST_MD5                        (3)

/**
 *   Digital signature algorithm: SHA-1withRSA
 *
 *   This is a constant passed to JkSatsaCreateSignature() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_SIGNATURE_SHA1RSA                  (1)

/**
 *   Digital signature algorithm: MD2withRSA
 *
 *   This is a constant passed to JkSatsaCreateSignature() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_SIGNATURE_MD2RSA                   (2)

/**
 *   Digital signature algorithm: MD5withRSA
 *
 *   This is a constant passed to JkSatsaCreateSignature() in the 
 *   <i>algorithm</i> parameter.
 */
#define JK_SATSA_SIGNATURE_MD5RSA                   (3)

/**
 *   The operation will be processed asynchronously. 
 *
 *   This constant is used as a return value by the following JSI functions. 
 *   <ul>
 *     <li>JkSatsaGetATR() 
 *     <li>JkSatsaOpenSEConnection() 
 *     <li>JkSatsaConnectionClose() 
 *     <li>JkSatsaSendCommandData() 
 *     <li>JkSatsaReceiveResponseData() 
 *     <li>JkSatsaGetACFileSize() 
 *     <li>JkSatsaGetACFileData() 
 *     <li>JkSatsaUpdateCipher() 
 *     <li>JkSatsaFinalCipher() 
 *     <li>JkSatsaUpdateDigest() 
 *     <li>JkSatsaFinalDigest()
 *     <li>JkSatsaUpdateSignatureVerify() 
 *     <li>JkSatsaFinalSignatureVerify() 
 *   </ul>
 */
#define JK_SATSA_ASYNC              (1)

/**
 *   Processing was completed normally. 
 *
 *   This constant is used as a return value by the
 *   @ref APDU_Connection_JSI and @ref Crypto_JSI functions.
 */
#define JK_SATSA_SUCCESS            (0)

/**
 *   Error code: An undefined error occurred. 
 *
 *   This constant is used as a return value by the
 *   @ref APDU_Connection_JSI and @ref Crypto_JSI functions.
 */
#define JK_SATSA_ERROR_GENERAL      (-1)

/**
 *   Error code: An out of memory error occurred. 
 *
 *   This constant is used as a return value by the
 *   @ref APDU_Connection_JSI and @ref Crypto_JSI functions.
 */
#define JK_SATSA_ERROR_MEMORY       (-2)


/**
 *   Error code: An error occurred due to a resource constraint. 
 *
 *   This constant is used as a return value by the
 *   @ref APDU_Connection_JSI and @ref Crypto_JSI functions.
 */
#define JK_SATSA_ERROR_RESOURCE     (-3)

/**
 *   Error code: An invalid encryption algorithm was designated. 
 *
 *   This constant is used as a return value by the following JSI functions. 
 *   <ul>
 *     <li>JkSatsaCreateCipher()
 *     <li>JkSatsaCreateDigest()
 *     <li>JkSatsaCreateSignature()
 *   </ul>
 */
#define JK_SATSA_ERROR_ALGORITHM    (-4)

/**
 *   Error code: An invalid block cipher mode was designated.
 *
 *   This constant is used as an error code by JkSatsaCreateCipher().
 */
#define JK_SATSA_ERROR_BLOCKMODE    (-5)

/**
 *   Error code: Invalid padding was designated. 
 *
 *   This constant is used as an error code by JkSatsaCreateCipher().
 */
#define JK_SATSA_ERROR_PADDING      (-6)

/**
 *   Error code: An invalid cryptographic key was designated.
 *
 *   This constant is used as a return value by the following JSI functions. 
 *   <ul>
 *     <li>JkSatsaInitSignatureVerify()
 *     <li>JkSatsaInitCipher()
 *   </ul>
 */
#define JK_SATSA_ERROR_KEY          (-7)

/**
 *   Error code: An invalid initialization vector was designated.
 *
 *   This constant is used as an error code by JkSatsaInitCipher().
 */
#define JK_SATSA_ERROR_IV           (-8)

/**
 *   Error code: Not enough memory to put the result. 
 *
 *   This constant is used as a return value by the following JSI functions. 
 *   <ul>
 *     <li>JkSatsaUpdateCipher()
 *     <li>JkSatsaFinalCipher()
 *     <li>JkSatsaGetIVCipher()
 *     <li>JkSatsaFinalDigest()
 *   </ul>
 */
#define JK_SATSA_ERROR_SHORTBUFFER  (-9)

/**
 *   Error code: In block cipher, the designated block size does not match the data.
 *
 *   This constant is used as an error code by JkSatsaFinalCipher().
 */
#define JK_SATSA_ERROR_BLOCKSIZE    (-10)

/**
 *   Error code: In decrypt mode, the designated padding does not match the data.
 *
 *   This constant is used as an error code by JkSatsaFinalCipher().
 */
#define JK_SATSA_ERROR_BADPADDING   (-11)

/**
 *   Error code: Message authenticity could not be verified. 
 *
 *   This constant is used as an error code by JkSatsaFinalSignatureVerify().
 */
#define JK_SATSA_ERROR_VERIFY       (-12)

/**
 *   Error code: An I/O error occurred.
 *
 *   This constant is used as an error code by @ref APDU_Connection_JSI functions.
 */
#define JK_SATSA_ERROR_CONNECTION   (-13)


/* SATSA protocol specific */
/**
 *   PIN entry dialog mode: VERIFY
 *
 *   This is a constant passed to JkSatsaPinEntryDialog() in the 
 *   <i>action</i> parameter.
 */
#define PIN_CMD_VERIFY                  (0)


/**
 *   PIN entry dialog mode: CHANGE
 *
 *   This is a constant passed to JkSatsaPinEntryDialog() in the 
 *   <i>action</i> parameter.
 */
#define PIN_CMD_CHANGE                  (1)


/**
 *   PIN entry dialog mode: DISABLE
 *
 *   This is a constant passed to JkSatsaPinEntryDialog() in the 
 *   <i>action</i> parameter.
 */
#define PIN_CMD_DISABLE                 (2)

/**
 *   PIN entry dialog mode: ENABLE
 *
 *   This is a constant passed to JkSatsaPinEntryDialog() in the 
 *   <i>action</i> parameter.
 */
#define PIN_CMD_ENABLE                  (3)

/**
 *   PIN entry dialog mode: UNBLOCK
 *
 *   This is a constant passed to JkSatsaPinEntryDialog() in the 
 *   <i>action</i> parameter.
 */
#define PIN_CMD_UNBLOCK                 (4)

/**
 *   PIN entry dialog mode: NEW_PIN
 *
 *   This is a constant passed to JkSatsaPinEntryDialog() in the 
 *   <i>action</i> parameter.
 */
#define PIN_CMD_NEW_PIN                 (5)

/**
 *   A SIM card is not mounted. 
 *
 *   This constant is used as an error code by JkSatsaGetSIMStatus().
 */
#define JK_SATSA_NOT_SAT_CONNECTION     (0) 

/**
 *   A GSM SIM card is mounted.
 *
 *   This constant is used as an error code by JkSatsaGetSIMStatus().
 */
#define JK_SATSA_IS_GSM_SIM             (1)

/**
 *   A UMTS SIM card is mounted.
 *
 *   This constant is used as an error code by JkSatsaGetSIMStatus().
 */
#define JK_SATSA_IS_UMTS_SIM            (2)

/*
 *     According to ISO7816-3, section 6.1 Max ATR length = 
 *     Initial character TS + max of 32 chars == 33bytes
 *     This value is checked on the Java side. 
 */
#define JK_SATSA_MAX_ATR_LEN            (33)

/**
 *   The handle type for identifying a cipher
 */
typedef JKHandle JKSatsaCipherHandle;

/**
 *   The handle type for identifying a message digest
 */
typedef JKHandle JKSatsaDigestHandle;

/**
 *   The handle type for identifying a digital signature algorithm 
 */
typedef JKHandle JKSatsaSignatureHandle;

/**
 *   The handle type for identifying a security element 
 */
typedef JKHandle JKSatsaConnectionHandle;

/**
 *   The handle type for identifying an entry dialog.
 */
typedef JKHandle JKSatsaDialogHandle;

/**
 *   The structure type for representing a common data type
 */
typedef struct JKT_Satsa_Data {
   /**
    *   A pointer to a memory area for holding data 
    *
    *   In some cases NULL is set in this member. 
    */
    JKUint8  *data;
   /**
    *   The offset
    */
    JKSint32 offset;
   /**
    *   The size (in bytes) of the data starting at <i>offset</i>.
    */
    JKSint32 len;
} JKT_Satsa_Data;

/**
 *   The structure type for holding common key data
 */
typedef struct JKT_Satsa_Symmetric {
   /**
    *   Common key
    */
    JKT_Satsa_Data key;
   /**
    *   Initialization vector
    */
    JKT_Satsa_Data iv;
} JKT_Satsa_Symmetric;

/**
 *   The structure type for holding public key data
 */
typedef struct JKT_Satsa_Asymmetric {
   /**
    *   Public exponent
    */
    JKT_Satsa_Data exp;
   /**
    *   Modulus
    */
    JKT_Satsa_Data mod;
} JKT_Satsa_Asymmetric;

/**
 *   The structure type for holding cryptographic key data
 *
 *   This structure is used with JkSatsaInitCipher().
 */
typedef struct JKT_Satsa_Cipher_Item {
   /**
    *   A pointer to a structure holding a cryptographic key data.
    */
    union {
       /**
        *   Common key data
        */
        JKT_Satsa_Symmetric  secretData;
       /**
        *   Public key data
        */
        JKT_Satsa_Asymmetric publicData;
    } type;
} JKT_Satsa_Cipher_Item;

/**
 *   The structure type for holding PIN attributes
 *
 *   This structure is used with JkSatsaPinEntryDialog().
 */
typedef struct {
    /**
     *   A pointer to a label. 
     */
    JKUint16* label;
    /**
     *   The length (number of characters) of the string indicated by 
     *   <i>label</i>.
     */
   JKSint32 labelLen;

    /**
     *   The maximum PIN number length (number of characters).
     */
    JKSint32 maxLength;
    /**
     *   Whether a PIN number contains only numeric digits. 
     *   If it contains only numeric digits, #JK_TRUE is designated.
     */
    JKBool isNumeric; 
    /**
     *   A pointer to a memory space for putting a string representing 
     *   a PIN number or label.
     *
     *   JBlend allocates a memory space of 255 bytes.
     *   In some cases, however, the memory is not allocated depending on the 
     *   PIN entry dialog operation mode.
     *   For details of the modes, see JkSatsaPinEntryDialog().
     */
    JKSint8* uiTextBuffer; 
} JKT_Satsa_TextField_Attrib;


/**
 *   Entry status of PIN entry dialog: Canceled 
 *
 *   This constant is used to notify JBlend of the PIN entry dialog entry status when
 *   requested by JkSatsaPinEntryDialog().
 */
#define JK_SATSA_DIALOG_USER_CANCEL 0x80

/**
 *   Entry status of PIN entry dialog: OK
 *
 *   This constant is used to notify JBlend of the PIN entry dialog entry status when
 *   requested by JkSatsaPinEntryDialog().
 */
#define JK_SATSA_DIALOG_USER_OK JK_SATSA_SUCCESS

/**
 *   Recommended SE access control is not supported.
 *
 *   This constant is used as a return value by the following JSI functions. 
 *   <ul>
 *     <li>JkSatsaGetACFileSize()
 *     <li>JkSatsaGetACFileData()
 *   </ul>
 */
#define JK_SATSA_ACF_NOT_SUPPORTED (-(0x81))


#ifdef __cplusplus
}
#endif

#endif /* ___JK_SATSA_COMMON_H */

/**
 * @} end of group
 */
