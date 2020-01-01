#ifndef __MS_SOCKET_IND_ITF_H__
#define __MS_SOCKET_IND_ITF_H__

#include "ms_socket_cmn.h"
#include "ms_socket_msg_def.h"

void Mserv_socket_bearer_status_change_req(MservSocketBearer_e eBearer, Mserv_bearer_info_u *puBearerInfo, bool bConnect);

#endif/* __MS_SOCKET_IND_ITF_H__ */
