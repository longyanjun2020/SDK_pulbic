
#ifndef __MANAGER_ADAPTER_H__
#define __MANAGER_ADAPTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <ncc_types.h>
#include <nccpush_manager.h>
#include <nccwsp.h>

#define PUSH_ACCEPT_APPLICATION                 0x32
#define PUSH_BEARER_INDICATION                  0x33
#define PUSH_PUSH_FLAG                          0x34

#define PUSH_PUSH_FLAG_AUTHENTICATED            0x01
#define PUSH_PUSH_FLAG_TRUSTED                  0x02
#define PUSH_PUSH_FLAG_LAST                     0x04

#define PUSH_PDU_TYPE_PUSH_MESSAGE              0x06/**<Define Macro that indicate Pdu Type.*/
#define PUSH_NO_OTA_PARAMETER                   -21
#define PUSH_GET_ALL_HEADER_ERROR               -22 /**<Return value:Indicate that decode MSG header fields error.*/
#define PUSH_GET_OTA_ERROR                      -23 /**<Return value:Indicate that get OTA parameter error.*/

/**
  *This structure is used to indicate Po-Unit-Push primitive.This primitive is
  *used to send information from the server to the client in a unconfirmed manner on the connectionless
  */
typedef struct{
    /**
      *This structure is used to indicate S-Unit-Push primitive.
      */
    T_PUSH_S_UNIT *s_unit;
    /**
      *Authenticated indicates if the initiator URI is authenticated by the server.
      */
    int32_t Authenticated;
    /**
      *Trusted indicates if the push content is trusted by the server.
      */
    int32_t Trusted;
    /**
      *Last is a hint to the client that this is the last message to send according
      *to the server¡¯s best knowledge. The client MAY terminate use of the network bearer.
      */
    int32_t Last;
}T_PUSH_PO_UNIT;

/**
  *This structure is used to indicate OTA parameters.
  */
typedef struct{
    /**
      *
      */
    uint8_t *Accept_Application;
    /**
      *
      */
    uint8_t *Bearer_Indication; /**<Integer-value.*/
    /**
      *
      */
    uint8_t *Push_Flag; /**Short-integer.*/
}T_PUSH_OTA;

/**The FUNC is used to get the OTA parameter.
 * \param  *pHeader    The pointer of Header Field buffer.
 * \param  pduLen      Then length of Header Fiedl.
 * \param  **para      The pointer of T_PUSH_OTA structure.
 *
 * \return <ul>
 *             <li>If successful,then return#PUSH_SUCCESS.
 *             <li>If unsuccessful,then return
 *                 <ul>
 *                     <li>#PUSH_INPUT_PARAMETER_ERROR.
 *                     <li>#PUSH_GET_ALL_HEADER_ERROR.
 *                     <li>#PUSH_ALLOC_MEMORY_ERROR.
 *                 </ul>
 *         </ul>
 */
int32_t PUSH_GetOTAParameter(uint8_t *pHeader,int32_t pduLen,T_PUSH_OTA **OTA);

#ifdef __cplusplus
}
#endif

#endif
