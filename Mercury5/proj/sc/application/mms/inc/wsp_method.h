
#ifndef __WSP_METHOD_H__
#define __WSP_METHOD_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern  "C" {
#endif

extern  const struct T_WAP_EventArray gpWAP_Event[];

typedef struct WSP_AUTH_LIST
{
    int8_t *pRealm;
    int8_t *pUser;
    int8_t *pPass;
    struct WSP_AUTH_LIST *next;
}T_WSP_AUTH_LIST;

/**
 * Destroy the auth list.
 *
 *   \param  pauthlist   a authlist pointer.
 *   \return
 */
int32_t  fnMETHOD_destroyAuthList(T_WSP_AUTH_LIST *pauthlist);

/**
 * Call this functiont to make a GET PDU packet.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  p the message buff.
 *   \param  url the URL to check;
 *   \param  header the header;
 *   \param  headerlen the length of the header;
 *   \return  If encode URL error, return WAP_INVALIDURL;else return 0;
 */
 int32_t fnMETHOD_MakeGetPdu(void *hc,T_WAP_MSG_P *p,int8_t *url,int8_t *header[],int32_t headerlen);
/**
 * Call this function to make a POST PDU packet.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  p the message buffer.
 *   \param  url the URL to check;
 *   \param  header the header;
 *   \param  headerlen the length of the header;
 *   \param  DataContentType the data content type.
 *   \return If the url is invalid,then the funtion will return WAP_INVALIDURL;
 *           else return 0.
 */

 int32_t fnMETHOD_MakePostPdu(void *hc,T_WAP_MSG_P *p,int8_t *url,int8_t *header[],int32_t headerlen,int8_t * DataContentType);

/**
 * The client originate the Abort action,but the event is the
 * Abort,so the wsp must inform the wtp and return the
 * S_MethodAbort.ind to the client.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the MCB;
 *   \param  res the reason of abort.
 *   \return
 */

 void fnMETHOD_Abort_Requesting(void *hc,void *ctl,void * res);
/**
 * The handle of the event Abort at the method  state of Waiting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the message control block;
 *   \param  res the reason of abort.
 *   \return
 */
 void fnMETHOD_Abort_Waiting(void *hc,void *ctl,void * res);

/**
 * The handle of the event MethodInvoke.Req at the session state of Null.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  pSession the pointer to session index;
 *   \param  tid the TID;
 *   \param  url the URL;
 *   \param  header the header to request;
 *   \param  HeaderLen the length of the header;
 *   \param  METHOD the method type(either the Get or Post PDU);
 *   \param  Content the content;
 *   \param  Content_len-the length of the content;
 *   \param  ContentType the type of the content.
 *   \return The function return 0 when there is not any error.
 *                                otherwise #WAP_INVALIDURL
 *                                               #WAP_BIGGERTHANMOR
 */
 int32_t fnMETHOD_MethodInvokeReq_Null(void *hc,T_WAP_SIndex *psession,uint16_t tid,int8_t *url,int8_t *header[],int32_t headerlen,int8_t METHOD,int8_t *Content,int32_t Content_len,int8_t* ContentType);

/**
 * The handle of the event MethodAbort.Req at the method state of Waiting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the MCB;
 *   \param  msg the message.
 *   \return
 */
 void fnMETHOD_MethodAbortReq_Waiting(void *hc,void *ctl,void *msg);

/**
 * The handle of the event MethodResult.Res at the method state
 * of Completing.It gives the response information to the peer.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the message control block;
 *   \param  msg the message
 *   \return
 */
 void fnMETHOD_MethodResultRes_Completing(void *hc,void *ctl,void *msg);

/**
 * The client originate a s_methodabort.req,so that
 * wsp must inform the wtp and give birth to the
 * s_methodabort.ind to the client.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the message control block;
 *   \param  msg the message
 *   \return
 */
 void fnMETHOD_MethodAbortReq_Requesting(void *hc,void *ctl,void *msg);

/**
 * The wtp inform the wsp with the primitive of TR-Invoke.cnf,so that
 * the wsp must give birth to the S-MethodInvoke.cnf,but
 * the function missing it.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the message control block;
 *   \param  msg the message
 *   \return
 */
 void fnMETHOD_TRInvokeCnf_Requesting(void *hc,void *ctl,void * msg);

/**
 * The handle of the event TR_Abort.Ind at the method state of Requesting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the message control block;
 *   \param  msg the message.
 *   \return
 */
 void fnMETHOD_TRAbortInd_Requesting(void *hc,void *ctl,void *msg);

/**
 * The handle of the event TR-Result.Ind at the method state of Waiting.
 * The wtp originate the event of TR-Result.ind at the state of WAITING.
 * If there are the right tdata,the function will return will return the error
 * of WAP_FIND_NO_DATA) missing:condition of SDU size>MRU
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the message control block;
 *   \param  msg the message
 *   \return
 */
 void fnMETHOD_TRResultInd_Waiting(void *hc,void * ctl,void * msg);

/**
 * The handle of the event TR-Abort.Ind at the method   state of Waiting.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the message control block;
 *   \param  msg the message
 *   \return
 */
 void fnMETHOD_TRAbortInd_Waiting(void *hc,void *ctl,void *msg);

/**
 * The handle of the event TRAbort.Ind at the method  state of Completing.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  ctl the message control block.
 *   \param  msg the message.
 *   \return
 */
 void fnMETHOD_TRAbortInd_Completing(void *hc,void *ctl,void *msg);

/**
 * The receive function of the WSP layer when session type is WSP_CONNECTLESS.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  packet the received packet.
 *   \return
 */
 void fnMETHOD_UnitWspRecv(void *hc,T_WAP_MSG_P packet);

/**
 * The receive function for the PUSH when session type is WSP_CONNECTLESS.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  packet the buffer to write.
 *   \return
 */
 void fnMETHOD_UnitPushRecv(void *hc,T_WAP_MSG_P packet);

#ifdef __cplusplus
}
#endif

#endif /* __WSP_METHOD_H__ */

