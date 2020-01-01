/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */
/** 
 * @file ajutil.h
 * AJSC Utility Header
 */
/*=========================================================================
 * KVM
 *=========================================================================
 * SYSTEM:    KVM
 * SUBSYSTEM: AJUTIL
 * FILE:      ajutil.h
 * OVERVIEW:  Utilities for common usage
 * VERSION:   2004/10/20
 *=======================================================================*/
#ifndef AJ_UTILITY_HEADER
#define AJ_UTILITY_HEADER

#ifdef __cplusplus
extern "C"{
#endif

#include <aj_type.h>

 
/**
 * @addtogroup Character_String_Utility_ACI
 *
 * @par Include file 
 * \#include ajutil.h
 * @{
 */


/**
 * The structure type for containing the URL information parsed by ajutil_parseURL().
 */
typedef struct _AJURLInfoR2
{
    /** 
     * A pointer to the string containing the URL. 
     */
    AJ_BYTE     *uri;
    /** 
     * The length in bytes of the string indicated by <i>url</i>. 
     */
    AJ_INT      uriLength;

    /** 
     * A pointer to the host name portion in the URL. 
     */
    AJ_BYTE     *hostname;
    /** 
     * The length in bytes of the host name indicated by <i>url</i>. 
     */
    AJ_INT      hostnameLength;

    /** 
     * The value of port number if exist. 
     * If a port number is not specified in the URL, 
     * 80 or 443 is set for "http" or "https" protocol respectively.
     * 0 is set for any other protocol.
     */
    AJ_INT      port;

    /** 
     * A pointer to the path portion following the host name in the URL. 
     */
    AJ_BYTE     *path;
    /** 
     * The length in bytes of the path indicated by <i>path</i>. 
     */
    AJ_INT      pathLength;

    /** 
     * This is reserved for future use. 
     */
    AJ_BYTE     *query;
    /** 
     * This is reserved for future use. 
     */
    AJ_INT      queryLength;
} AJURLInfoR2;

/**
 *        Converts a Unicode character string to a UTF-8 byte array.
 * @param in
 *        A pointer to the memory area containing the Unicode character string.
 * @param inChars
 *        The number of characters in the Unicode character string.
 * @param out
 *        A pointer to the memory area for receiving the UTF-8 byte array resulting from 
 *        conversion.
 * @param outBytes
 *        The number of bytes that can be output to the memory area designated in the 
 *        <i>out</i> parameter.
 *        The number of characters resulting from conversion of a Unicode character 
 *        string to a UTF-8 byte array can be obtained by calling ajutil_UniToUtf8Size().
 *        When priority is given to speed of execution, the value designated in <i>inChars</i> 
 *        times 3 bytes is an estimate on the safe side and can be used here.
 * @return
 *        The number of Unicode characters converted to a UTF-8 byte array is returned.
 *
 * If the return value is identical to that designated in the <i>inChars</i> parameter, 
 * this means the entire Unicode character string was converted.
 * If not all the Unicode character string could be processed due to lack of 
 * output space, -1 is returned.
 *
 * Even if the Unicode character string contains a termination character ('\\0'), 
 * the designated number of bytes are processed. '\\0' is output as is.
 * '\\0' is not added at the end of the UTF-8 byte array after conversion.
 */
AJ_S32 ajutil_UniToUtf8(const AJ_U16* in,  AJ_S32 inChars,
                              AJ_U8*  out, AJ_S32 outBytes );



/**
 *        Returns the number of bytes resulting from conversion of a Unicode character 
 *        string to a UTF-8 byte array.
 * @param in
 *        A pointer to the memory area containing the Unicode character string.
 * @param inChars
 *        The number of characters in the Unicode character string.
 *
 * @retval "A value of 0 or more"
 *         if the function succeeds.
 *         The number of bytes resulting from conversion of a Unicode character string to a UTF-8 byte array is returned.
 *         This byte count does not include '\\0' termination.
 * @retval -1
 *         if the function fails due to an illegal parameter.
 *         For example, when #AJ_NULL is passed in the <i>in</i> parameter or 
 *         a negative value is passed in the <i>inChars</i> parameter.
 */
AJ_S32 ajutil_UniToUtf8Size(const AJ_U16* in, AJ_S32 inChars);

/**
 *        Converts a UTF-8 byte array to a Unicode character string.
 * @param in
 *        A pointer to the memory area containing the UTF-8 byte array.
 * @param inBytes
 *        The number of bytes in the UTF-8 byte array.
 * @param out
 *        A pointer to the memory area for receiving the Unicode character string 
 *        resulting from conversion.
 * @param outChars
 *        The number of characters that can be output to the memory area designated by 
 *        the <i>out</i> parameter. 
 *        The number of characters resulting from conversion of a UTF-8 byte array to a 
 *        Unicode character string can be obtained by calling ajutil_Utf8ToUniSize().
 *        When priority is given to speed of execution, the value designated in <i>inBytes</i> 
 *        is an estimate on the safe side and can be used here.
 *
 * @retval "A value of 0 or more"
 *         if the function succeeds.
 *         The number of UTF-8 bytes converted to a Unicode character string is returned.
 *         If the return value is identical to that designated in the <i>inBytes</i> parameter, 
 *         this means the entire UTF-8 byte array was converted.
 * @retval -1
 *         if the function fails due to lack of output space.
 * @retval -2
 *         if the function fails due to an illegal parameter.
 *         For example, when #AJ_NULL is passed in either the <i>in</i> or <i>out</i> parameter.
 *   
 * Even if the UTF-8 byte array contains a termination character ('\\0'),  
 * the designated number of bytes are processed. '\\0' is output as is.
 * If the UTF-8 byte array contains UCS4 character codes of 0x10000 and above,
 * these characters are not converted but are replaced by the alternate character 
 * designated in the substitute parameter and counted in the characters that could 
 * not be converted.
 *
 * UTF-8 converted to an illegal byte length is considered an illegal code under 
 * RFC2279, but conversion proceeds in this function nonetheless.
 * Example:: U+0000 in UTF-8 is the 1 byte 0x00, but conversion processing takes 
 * place even it is encoded as 2 or 3 bytes (0xC0 0x80 or 0xE0 0x80 0x80).
 */
AJ_S32 ajutil_Utf8ToUni(const AJ_U8*  in,  AJ_S32 inBytes,
                              AJ_U16* out, AJ_S32 outChars );



/**
 *        Returns the number of characters resulting from conversion of a UTF-8 byte array 
 *        to a Unicode character string.
 * @param in
 *        A pointer to the memory area containing the UTF-8 byte array.
 * @param inBytes
 *        The number of bytes in the UTF-8 byte array.
 * @retval "A value of 0 or more"
 *         if the function succeeds.
 *         The number of characters resulting from conversion of a UTF-8 byte array to a Unicode character string is returned. 
 *         This character count does not include the '\\0' terminating the converted Unicode character string.
 * @retval -1
 *         if the function fails due to an illegal parameter.
 *         For example, when #AJ_NULL is passed in the <i>in</i> parameter or 
 *         a negative value is passed in the <i>inBytes</i> parameter.
 *   
 * If conversion is interrupted while processing a multi-byte character, that 
 * character is not included in the count.
 */
AJ_S32 ajutil_Utf8ToUniSize(const AJ_U8* in, AJ_S32 inBytes);

/**
 *        Finds the first occurrence of a character string in buffer.
 * @param src                
 *        A pointer to the buffer containing the original data.
 * @param key                
 *        The character string to search for.
 * @param srcSize            
 *         The size in bytes of the buffer indicated by <i>src</i>.
 * @retval "A non-NULL value"
 *         if the function succeeds. 
 *          A pointer to the first occurrence of the specified character string is returned.
 * @retval #AJ_NULL
 *         if the function fails.
 */
AJ_BYTE *ajutil_findStringInBuffer(const AJ_BYTE *src,
                                   const AJ_BYTE *key,
                                   const AJ_U32  srcSize);

/**
 *        Compares two strings case-insensitively with specified length.
 * @param str1            
 *        String 1. A NUL-terminated string.
 * @param str2            
 *        String 2. A NUL-terminated string.
 * @param maxLen          
 *        The maximum length to compare.
 * @retval  0 if the two strings are case-insensitively identical.
 * @retval  1 if str2 < str1
 * @retval -1 if str1 < str2
 */
AJ_S32 ajutil_stricmp(const AJ_U8 *str1, 
                      const AJ_U8 *str2, 
                      const AJ_S32 maxLen);

/**
 *        Compares two block of memory with specified length
 * @param str1            
 *        String 1. A NUL-terminated string.
 * @param strlen1         
 *        The length in bytes of the string indicated by <i>str1</i> excluding the trailing NUL.
 * @param str2            
 *        String 2. A NUL-terminated string.
 * @param strlen2         
 *        The length in bytes of the string indicated by <i>str1</i> excluding the trailing NUL.
 * @retval  0 if the two strings are identical.
 * @retval  1 if str2 < str1
 * @retval -1 if str1 < str2
 *
 * The comparison rule is same as ASCII string comparation strcmp().
 */
AJ_S32 ajutil_memicmp(const AJ_U8  *str1, 
                            AJ_S32  strlen1, 
                      const AJ_U8  *str2, 
                            AJ_S32  strlen2);

/**
 *        Parses a URL string
 * @param url             
 *        A pointer to the URL string to be parsed.
 * @param urlLength       
 *        The length in bytes of the string indicated by <i>url</i>.
 * @param urlInfo         
 *        A pointer to an #AJURLInfoR2 structure for receiving the parse result.
 * @retval  0 if the function succeeds.
 * @retval -1 if the function fails.
 **/
AJ_INT ajutil_parseURL(const AJ_BYTE *url, AJ_INT urlLength, AJURLInfoR2 *urlInfo);


/**
 *        Encodes a byte sequence using Base64 algorithm.
 * @param inbuf
 *        A pointer to the data to be encoded.
 * @param inbuf_len
 *        The length in bytes of the data indicated by <i>inbuf</i>.
 * @param outbuf
 *        A pointer to the buffer for receiving the encoded data.
 *        The buffer size must be greater than (4 * <i>inbuf_len</i> / 3 + 3) bytes.
 * @return
 *        The size of the encoded data written in the output buffer <i>outbuf</i>.
 */
AJ_S32 ajutil_b64_encode( AJ_U8* inbuf, AJ_S32 inbuf_len, AJ_U8* outbuf );

/**
 *        Decodes a Base64 encoded sequence.
 * @param inbuf
 *        A pointer to the data to be decoded.
 * @param inbuf_len   
 *        The length in bytes of the data indicated by <i>inbuf</i>.
 * @param outbuf
 *        A pointer to the buffer for receiving the decoded data.
 *        The buffer size must be greater than (3 * <i>inbuf_len</i> / 4) bytes.
 * @return
 *        The size of the decoded data written in the output buffer <i>outbuf</i>.
 */
AJ_S32 ajutil_b64_decode( AJ_U8* inbuf, AJ_S32 inbuf_len, AJ_U8* outbuf );

/** @} */

#ifdef __cplusplus
}
#endif 

#endif /* AJ_UTILITY_HEADER */
