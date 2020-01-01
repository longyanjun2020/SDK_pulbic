/*
 * iq_paraprint.h
 *
 *  Created on: 2016/4/28
 *      Author: Elsa-cf.Lin
 */

#ifndef __iq_paraprint__
#define __iq_paraprint__

#include <isp_types.h>

typedef enum{
  IQ_PRI_ALL = 0,
  IQ_PRI_NOHAL,   //not subbport in HalIQ
  IQ_PRI_NOIQ,    //not support in MSTAR/SUB IQ
}IQ_PRINT_NOVAL;

typedef enum{
  IQ_SFT_NA = 0,
  IQ_SFT_L,
  IQ_SFT_R,
}IQ_SHIFT;

int IQ_Print_IPInfo(iq_handle_t *handle, IQ2_BLK_List *BlockTbl, char** IPname, char** IPen, MS_U8 ip_ind);
int IQ_Print_IQOPMODE(MS_U8 ip_ind, MS_U8 mod);
int IQ_Para_Print_ALL(iq_handle_t *handle, MS_U8 blk_id, MS_U8 isoind, MS_U8 Lev);
int IQ_Print_APILEV_ALL(iq_handle_t *handle, MS_U8 isoind);
int IQ_Para_Print_API20(IQAPI20_t *handle, MS_U8 api_id, MS_U8 tblscl, MS_U8 isoind);
void PrintWDR_table_log(iq_handle_t *handle);



#endif /* __iq_paraprint__ */
