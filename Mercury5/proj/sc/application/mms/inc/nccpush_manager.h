
/**
 * @file nccpush_manager.h
 * PUSH manager Service Layer
 *
 * Service API exposed by the manager module of PUSH.
 *
 * <!-- #interface list begin -->
 * \section nccpush_manager Interface
 * - NCCPush_manager_adapter()
 * - NCCPush_manager_otaPush()
 * - NCCPush_manager_registerApp()
 * - NCCPush_manager_quit()
 * - NCCPush_manager_freeMemory()
 * <!-- #interface list end -->
 */

#ifndef __NCCPUSH_MANAGER_H__
#define __NCCPUSH_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <nccwsp.h>
#include <ncc_types.h>

/**
 * @defgroup PUSH_MODULE Push manager
 * The module mainly define some macros,structure and APIs of push module.
 * @{
 */

/**
 * \name PUSH_RETURN_VALUE
 * Define Return Value of external FUNC in PUSH Manger MODULE.
 */
//@{
#define PUSH_REGISTER_APP_IS_NULL               1   /**<Return value:Indicate that the pointer of current register APP us NULL.*/
#define PUSH_SUCCESS                            0   /**<Return value:Indicate that Operation is successfully finished.*/
#define PUSH_INPUT_PARAMETER_ERROR              -1  /**<Return value:Indicate that input parameters of FUNC is ERROR.*/
#define PUSH_ALLOC_MEMORY_ERROR                 -2  /**<Return value:Indicate that alloc memory is failure.*/
#define PUSH_CURRENT_MSG_NOT_PUSH_MSG           -3  /**<Return value:Indicate that current message is not Push Message.*/
#define PUSH_GET_HEADER_LEN_ERROR               -4  /**<Return value:Indicate that the operation of getting headerlen field is unsuccess.*/
#define PUSH_OTAPUSH_ERROR                      -5  /**<Return value:Indicate that the Procession of OTA is error.*/
#define PUSH_GET_BODY_LEN_ERROR                 -6  /**<Return value:Indicate that the operation of getting the length of body is unsuccessful .*/
#define PUSH_REGISTER_PUSH_APP_ERROR            -7  /**<Return value:Indicate that the registration of PUSH APP is unsuccessful.*/
#define PUSH_APP_NOT_REGISTERED                 -8  /**<Return value:Indicate that current PUSH APP is not registered in PUSH MODULE.*/
//@}
/**
 * \name STRUCTURE_TYPE_MACROS
 * Define macros that used to indicate the type of struct.============
 */
//@{
#define PUSH_OTA_STRUCT                         0x02    /**<Indicate that Current struct is T_PUSH_OTA struct.*/
#define PUSH_APP_STRUCT                         0x03    /**<Indicate that Current struct is PUSH APP struct.*/
//@}

#define CONTENT_TYPE_TOKEN 0x91/**Content-Type field token.*/

/**
 * \name PUSH_STRUCTURE
 * Define some structure for push module.
 */
//@{

///S-Unit_Push primitive.
/**
 *This structure is used to indicate S-Unit-Push primitive.
 *This primitive is used to send unsolicited information from
 *the server to the client in a non-confirmed manner.
 */
typedef struct{
    /**
      *Client Address identifies the peer to which the push is to be sent.
      */
    uint8_t *C_Addr;
    /**
      *Server Address identifies the originator of the push.
      */
    uint8_t *S_Addr;
    /**
      *This attribute is used to note some header information about push message.
      */
    uint8_t *PUSHHead;
    /**
      *This field is used to indicate the length of MSG header Field.
      */
    int32_t Header_Len;
    /**
      *Push Body is the content in the push, which is semantically equivalent to an HTTP entity body.
      */
    uint8_t *PUSHBody;
    /**
      *This Field is used to indicate the length of MSG body Field.
      */
    int32_t Body_Len;
    /**
      *The service users MAY use Push Id to distinguish between pushes.
      */
    uint8_t PUSH_ID;
}T_PUSH_S_UNIT;

///push header node.
/**The structure is used to indicate that information of header.*/
typedef struct T_PUSH_HEADER_NODE{
    T_HEADER_FIELD *pHeader; /**<The pointer of header.*/
    struct T_PUSH_HEADER_NODE *next; /**<the pointer that pointing to the next header.*/
}T_PUSH_HEADER_NODE;

///push header list.
/**The structure is used to indicate the list of header.*/
typedef struct T_PUSH_HEADER_LIST{
    uint32_t total; /**<The number of header in the header list*/
    struct T_PUSH_HEADER_NODE *next;    /**<The pointer that pointing to the next header.*/
}T_PUSH_HEADER_LIST;

///registered FUNC pointer.
/**define a FUNC pointer that have been registered into PUSH MODULE*/
typedef void (*PFUNC)(T_PUSH_HEADER_LIST *Header,
                        uint8_t *Body,
                        int32_t len,
                        int32_t argc,
                        void *argv[]);

///basic information of push app.
/**define a structure that indicate basical information of PUSH APP.*/
typedef struct T_PUSH_APP_B_ATT
{
    uint32_t MIMEPort;          /**<used to indicate that port number of APP.*/
    int32_t  HeaderFLAG;        /**<used to indicate if need MSG Header.*/
    PFUNC pProcessFunc;         /**<used to indicate that pointer of Function.*/
    int32_t argc;
    void **argv;
}T_PUSH_APP_B_ATT;

///text information of push app.
/**The structure that indicate some Text informationof PUSH APP.*/
typedef struct T_PUSH_APP_TEXT_ATT
{
    int8_t *APPName;    /**<Indicate the name of PUSH APP.*/
    int8_t *MIMEType;   /**<Indicate the MIMETYPE of PUSH APP.*/
}T_PUSH_APP_TEXT_ATT;

///push app.
/**The structure used to indicate the information of push APP*/
typedef struct T_PUSH_APP{
    T_PUSH_APP_B_ATT bAtt;  /**<the basical information of the push APP.*/
    T_PUSH_APP_TEXT_ATT txtAtt; /**<the Text information of the push APP.*/
}T_PUSH_APP;

///push handle.
/**Define a handle for push Module.*/
typedef struct T_PUSH_APP_LIST *PUSH_HANDLE;
//@}

/**
 * \name PUSH_APIS
 * define some external interface of push module.
 */
//@{
#ifdef NCC_WITH_CONSMS
/**
 *The entrance of push Module.The ConSMS module can invoke this FUNC to process push message.
 *This FUNC used to generate S-Unit-Push primitive for OTA push.
 *
 * \param PushHandle The handle of Push Module.
 * \param *pduBuf The pointer of push message.
 * \param Buflen The length of push PDU.
 *
 * \return <ul>
 *            <li>If successful,then return#PUSH_SUCCESS.
 *            <li>If unsuccessful,then return
 *              <ul>
 *                 <li>#PUSH_INPUT_PARAMETER_ERROR.
 *                 <li>#PUSH_CURRENT_MSG_NOT_PUSH_MSG.
 *                 <li>#PUSH_GET_BODY_LEN_ERROR.
 *                 <li>#PUSH_GET_BODY_LEN_ERROR.
 *                 <li>#PUSH_ALLOC_MEMORY_ERROR.
 *                 <li>#PUSH_OTAPUSH_ERROR.
 *             </ul>
 *         </ul>
 */
int32_t NCCPush_manager_adapter(PUSH_HANDLE PushHandle,uint8_t * pduBuf, int32_t Buflen);
#endif

/**
 *Generate Po-Unit-Push primitives.This primitive is used to
 *send information from the server to the client in a unconfirmed manner on the connectionless
 * \param *SUnit The pointer of T_PUSH_S_UNIT structure that indicate S-Unit-Push primitives.
 *
 * \return <ul>
 *             <li>If successful,then return#PUSH_SUCCESS.
 *             <li>If unsuccessful,then return
 *             <ul>
 *                 <li>#PUSH_INPUT_PARAMETER_ERROR.
 *                 <li>#PUSH_GET_CONTENT_TYPE_ERROR.
 *                 <li>#PUSH_GET_ALL_HEADER_ERROR.
 *                 <li>#PUSH_APP_NOT_REGISTERED.
 *             </ul>
 *         </ul>
 */
int32_t NCCPush_manager_otaPush(PUSH_HANDLE PushHandle,T_PUSH_S_UNIT *SUnit);


/**
 *The Registered Interface.When systerm start,The FUNC Must be invoked to Init a push handle,
 *of course user also can dynamicly register a APP.
 * \param *PushHandle The pointer of PushHandle,The first invoking the parameter Must be NULL.
 * \param *App The pointer of Push APP.
 *
 * \return <ul>
 *            <li>If successful,then return#PUSH_SUCCESS or PUSH_REGISTER_APP_IS_NULL.
 *            <li>If unsuccessful,then return#PUSH_REGISTER_PUSH_APP_ERROR.
 *         </ul>
 * \sa NCCPush_manager_quit
 */
int32_t NCCPush_manager_registerApp(PUSH_HANDLE *PushHandle,T_PUSH_APP *App);

/**
 *Clear system resource.It Must be invoked to CRTL_free push handle when exit system.
 * \param *PushHandle The pointer of push handle.
 *
 * \return <ul>
 *             <li>return#PUSH_SUCCESS.
 *         </ul>
 */
int32_t NCCPush_manager_quit(PUSH_HANDLE *PushHandle);

/**
 *Free memory,when a struct will not be used.
 * \param type The type of struct that will be CRTL_freeed.
 * \param *pStruct The pointer of struct.
 *
 * \return void
 */
void NCCPush_manager_freeMemory(uint8_t type,void *pStruct);
//@}

/**@}*/

#ifdef __cplusplus
}
#endif

#endif
