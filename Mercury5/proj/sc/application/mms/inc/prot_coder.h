
/**
 * @file
 * NCC mms protocol coder
 *
 * Encode/Decode helper routines of the NCC mms protocol module
 */

#ifndef __PROT_CODER_H__
#define __PROT_CODER_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CONTENT_TYPE_MAX_LENGTH                              50
#define MMS_MAX_RECEIVER_LENGTH                              60

#ifdef MMS_SUPPORT_JSR205
#define APPLICATION_ID_STRING   "Application-Id"
#define REPLY_TO_APPLICATION_ID "Reply-To-Application-Id"
#endif

typedef struct T_Content_Type_Union {
    int8_t *pContentType;
    int8_t *Name;
    int8_t HasCharSet;          /* 0--none charset value ;1--has charset value */
    uint8_t Boundary[3];        /* fullfill for align */
    int32_t CharSet;
#ifdef MMS_SUPPORT_JSR205
    uint8_t *ApplicationId;/*Because it doesn't do memory copy, so don't need to free the pointer.*/
    uint8_t *ReplyToApplicationId;/*Because it doesn't do memory copy, so don't need to free the pointer.*/
    uint8_t *StartContentId;/*Because it doesn't do memory copy, so don't need to free the pointer.*/
#endif
    /* more other function can be added below */
} T_Content_Type_Union;

/**
 * Encode string into pdu
 * \param pDest pdu's temp pointer
 * \param pSource the string's pointer
 * \return <ul>
 *		<li> None
 *	   </ul>
 */
void EncodeString(uint8_t ** pDest, int8_t * pSource);

/**
 * Get string from  pdu string
 * \param pSource pdu string's pointer
 * \param pStrlen the string length pointer
 * \return <ul>
 *		<li> the string get from the pdu's pointer
 *	   </ul>
 */
int8_t *DecodeString(uint8_t ** pSource, uint16_t * pStrlen);

/**
 * Encode string into pdu
 * \param pDest the pdu's temp pointer
 * \param pSource the string's pointer
 * \return <ul>
 *		<li> None
 *	   </ul>
 */
void EncodeTextString(uint8_t ** pDest, int8_t * pSource);

/**
 * Get string from  pdu string
 * \param pSource the pdu string's pointer
 * \param pStrlen the string length pointer
 * \return <ul>
 *		<li> the string get from the pdu's pointer
 *	   </ul>
 */
int8_t *DecodeTextString(uint8_t ** pSource, uint16_t * pStrlen);

/**
 * Encode string into pdu
 * \param pDest the pdu's temp pointer
 * \param pSource the string's pointer
 * \return <ul>
 *		<li> None
 *	   </ul>
 */
void EncodeEncodedString(uint8_t ** pDest, int8_t * pSource);

/**
 * Get string from  pdu string
 * \param pSource the pdu string's pointer
 * \param pStrlen the string length pointer
 * \return <ul>
 *		<li> the string get from the pdu's pointer
 *	   </ul>
 */
int8_t *DecodeEncodedString(uint8_t ** pSource, uint16_t * pStrlen);

/**
 * Encode address string into pdu
 * \param pDest the pdu's temp pointer
 * \param pSource the string's pointer
 * \return <ul>
 *		<li> 0			if it's mail number
 *		<li> 1			if it's phone number
 *	   </ul>
 */
uint8_t EncodeAddressString(uint8_t ** pDest, int8_t * pSource);

/**
 * Decode address
 * \param pSource the pdu string's pointer
 * \param pStrlen the string length pointer
 * \return <ul>
 *		<li> the string get from the pdu's pointer
 *	   </ul>
 */
int8_t *DecodeAddressString(uint8_t ** pSource, uint16_t * pStrlen);

/**
 * Decode octets to uint value
 * \param pSource the pdu string's pointer
 * \return <ul>
 *		<li> type value value
 *	   </ul>
 */
int32_t OctetsToLongInt(uint8_t * pSource);

/**
 * Get the length value of the Length field
 * \param pOctets the Octets's pointer
 * \return <ul>
 *		<li> None
 *	   </ul>
 */
uint32_t GetLengthValue(uint8_t ** pOctets);

uint32_t OctetsToUintvar(uint8_t ** pOctets);

/**
 * Convert the uint value to octets
 * \param chvalue the pointer of the pdu
 * \param value the uint's value
 * \return <ul>
 *		<li> the number of octets
 *	   </ul>
 */
int8_t CompactUintvar(uint8_t * chvalue, int32_t value);

/**
 * Decode octets to uint value
 * \param pSource the content type value's pointer
 * \param pLength the length of content type's value
 * \return <ul>
 *		<li> NULL		if failed
 *		<li> the struct of  T_Content_Type_Union's pointer if success
 *	   </ul>
 */
T_Content_Type_Union *GetContentType(uint8_t ** pSource, int32_t * pLength);

/**
 * According to the content type assigned number to get the string of the content type
 * \param ContentType the content type 's assigned number value
 * \return <ul>
 *		<li> the content type's string value
 *	   </ul>
 */
uint8_t EncodeContentType(int8_t * ContentType);

/**
 * Compact the value-length  value to pdu
 * \param pPdu the pointer of the pdu
 * \param value the uint's value
 * \return <ul>
 *		<li> the number of octets
 *	   </ul>
 */
int8_t EncodeValueLength(uint8_t * pPdu, int32_t Value);

/**
 * Encode integer into pdu
 * \param pSource the pdu's address pointer
 * \param the integer value
 * \return <ul>
 *		<li> None
 *	   </ul>
 */
void EncodeIntegerValue(uint8_t ** pSource, int32_t Value);

/**
 * Decode integer value
 * \param pSource the pdu's address pointer
 * \param pStrlen the length of  the integer value
 * \return <ul>
 *		<li> the value of the  int32_t type
 *	   </ul>
 */
int32_t DecodeIntegerValue(uint8_t ** pSource, uint16_t * pStrlen);

/**
 * Get the length of the long integer value
 * \param value the long intege's  value
 * \return <ul>
 *		<li> the length of the encode number
 *	   </ul>
 */
int8_t GetLongIntLength(int32_t Value);

/**
 * Encode long int value to octets
 * \param value the long intege's  value
 * \param pDest the pdu pointer
 * \return <ul>
 *		<li> None
 *	   </ul>
 */
void LongInt2Octets(uint8_t ** pDest, int32_t Value);

/**
 * Encode muliple receiver to the head field
 * \param pDest the pdu buffer pinter's pointer
 * \param pSource the receive field's string pointer
 * \param fieldType the receiver's type,to,cc or bcc
 * \return <ul>
 *		<li> None
 *	   </ul>
 */
void EncodeMultiRcver(uint8_t ** pDest, int8_t * pSource, uint8_t fieldType);

/**
 * Parse one receiver's address from the string
 * \param String the receive field's string pointer's pointer
 * \param pReceiver the receive's address's store buffer
 * \return <ul>
 *		<li> TRUE			if success
 *		<li> FALSE			if failed
 *	   </ul>
 */
int32_t GetOneReceiverValue(int8_t ** pString, int8_t * pReceiver);

/**
 * Parse the content type which include parameters
 * \param pSource the content type value's pointer
 * \param Len the length of content type's value
 * \return <ul>
 *		<li> the struct of  T_Content_Type_Union's pointer
 *	   </ul>
 */
T_Content_Type_Union *ParseContentTypeWithParam(uint8_t * pSource,
                                                int32_t * Len);

/**
 * According to the content type assigned number to get the string of the content type
 * \param ContentType the content type 's assigned number value
 * \return <ul>
 *		<li> the content type's string value
 *	   </ul>
 */
int8_t *DecodeWellKnownContentType(uint8_t ContentType);

/**
 *Encode element into pdu.
 * \param *pElement An T_MMS_Media_Element pointer to specify that the list of element.
 * \param **pOutBuf An uint8_t pointer to specify the pdu which will be returned.
 *
 * \return <ul>
 *             <li>Success,return#COMPOSER_SUCCESS.
 *             <li>Otherwise,return#COMPOSER_INPUT_PARAM_ERROR
 *         </ul>
 */
int32_t CompactMMSElementIntoPdu(T_MMS_Media_Element *pElement, uint8_t **pOutBuf);

#ifdef __cplusplus
}
#endif

#endif /* __PROT_CODER_H__ */
