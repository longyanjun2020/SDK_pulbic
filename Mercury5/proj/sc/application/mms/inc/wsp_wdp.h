
#ifndef __WSP_WDP_H__
#define __WSP_WDP_H__

#include <wsp_pub.h>
#include <wsp_conf.h>

#ifdef __cplusplus
extern  "C" {
#endif

#define WAP_SOCKET unsigned long

typedef struct T_WDP_Addr2Sap {
    T_WAP_AddrTuple Addr;       /**< Address Tuple */
    uint32_t Sap;               /**< Socket description */
    struct T_WDP_Addr2Sap *next; /**< Next element */
}T_WDP_Addr2Sap;

/**
 *  Find a address tuple from the address tuple list.
 *   \param  hc  a wsp instance handle.
 *   \param  addr   the address tuple to find.
 *   \return If find ,return a pointer to the found address tuple,else return 0.
 */
 int32_t fnWDP_FindSap(void *hc,T_WAP_AddrTuple *addr);

/**
 *  Call this function to create a address tuple and add it
 *   to address tuple list.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  addr   the address tuple to add.
 *   \return return a pointer to the created address tuple.
 */
 struct T_WDP_Addr2Sap *fnWDP_CreateMap(void *hc,T_WAP_AddrTuple *addr);

/**
 *  Call this function to  delete a address tuple from the list and free it.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  T_WAP_AddrTuple *addr   the address tuple to free.
 *   \return
 */
 void fnWDP_DestoryMap(void *hc,T_WAP_AddrTuple *addr);

/**
 *  Call this function to do some initilization of WDP.
 *
 *   \param  hc  a wsp instance handle.
 *   \return
 */
 void fnWDP_init(void *hc);

/**
 *  Call this function to clean WDP.
 *
 * \param    hc  a wsp instance handle.
 *   \return
 */
 void fnWDP_Clean(void *hc);

/**
 *  Function to send data in the WDP layer of WAP stack.
 *
 *   \param  hc  a wsp instance handle.
 *   \param  buf the data buffer of the send data;
 *   \param  addr the address tuple of communication;
 *   \param  len the length of the data buffer.
 *   \return
 */
 void fnWDP_Send(void *hc,uint8_t *buf,T_WAP_AddrTuple *addr,int32_t len);

/**
 *  Function to receive data in the WDP layer of WAP stack.
 *  After get data from lower layer ,it will call the function of
 *  upper layer(such as fnWTP_Rcv,fnMETHOD_UnitWspRecv,
 *  nMETHOD_UnitPushRecv) to do further process.
 *
 * \param    hc  a wsp instance handle.
 *   \return
 */
 void fnWDP_Recv(void *hc);


#ifdef __cplusplus
}
#endif

#endif /*__WSP_WDP_H__*/

