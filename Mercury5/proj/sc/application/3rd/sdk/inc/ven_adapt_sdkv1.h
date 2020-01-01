/**
 *
 * @file    ven_adapt_sdkv1.h
 * @brief   Adaption layer for old SDK v1
 *
 * @author  Sata.Yeh
 * @version $Id:  $
 *
 */
#ifndef __VEN_ADAPT_SDKV1_H__
#define __VEN_ADAPT_SDKV1_H__

#include "ven_sdk.h"
#include "ven_file.h"
#include "drv_vm_rtc.h"
#include "ms_stmsg.hi"

#ifdef __SDK_MMI_V1_ADAPTION__
/**
 *  s8 ven_dbg_trace(u32 level, char *strFormat, ...);
 *
 * \brief   Sends a debugging trace string to the VC++ debugging session (in WIN32),
 * \brief   or to TMT tool (in target environment)
 * \param   level         [in] Diagnose element and level of the trace
 * \param   strFormat     [in] format of the trace (printf like): %s is not accepted
 * \return  always 0
 */
extern s8 ven_dbg_trace(u32 level, char *strFormat, ...);

/**
 *  mem_malloc
 *  @brief  allocate memory space in SDK v1
 *  @param  Size      [in] Memory size
 *  @retval  memory address if success
 *           NULL else
 */
extern void * mem_malloc(s32 Size);

/**
 *  mem_free
 *  @brief  free memory space interface in SDK v1
 *  @param  pData      [in] memory address to free
 *  @retval  void
 */
extern void mem_free(void *pData);

/* Implementation of network profile function in SDK v1 */
#define MSERV_PROFILE_MAX_LEN_PRFNAME    15     /* max len(profile name) in UCS2 */
#define MSERV_PROFILE_MAX_LEN_SERVERURL 127     /* max len(server URL) in ASCII */
#define MSERV_PROFILE_MAX_LEN_GPRSAPN    31     /* max len(GPRS APN) in ASCII */
#define MSERV_PROFILE_MAX_LEN_USERNAME   31     /* max len(username) in ASCII */
#define MSERV_PROFILE_MAX_LEN_PASSWORD   31     /* max len(password) in ASCII */
#define MSERV_PROFILE_PROTOCOL_WAP       0x0
#define MSERV_PROFILE_PROTOCOL_HTTP      0x1


typedef struct
{
    u8 pPrfName[(MSERV_PROFILE_MAX_LEN_PRFNAME + 1) * 2];   /* profile name (in UCS2) */
    u8 pServerUrl[MSERV_PROFILE_MAX_LEN_SERVERURL + 1];
    u16 nProxyPort;
    u16 tProtocol;    /* type of WAP protocol: WAP/HTTP */
    u16 _align0;
    u8 nProxyIp[4]; /* xxx.xxx.xxx.xxx */
    u8 pGprsApn[MSERV_PROFILE_MAX_LEN_GPRSAPN + 1];
    u8 pUsername[MSERV_PROFILE_MAX_LEN_USERNAME + 1];
    u8 pPassword[MSERV_PROFILE_MAX_LEN_PASSWORD + 1];
    u8 nDnsIp[4]; /* xxx.xxx.xxx.xxx */
} iMserv_Profile_t;

void Mserv_ReadProfile(iMserv_3rd_Application_Type_t type, iMserv_Profile_t *profile);

/* 0:  UTC-11,  Midway islands, Samoa   */
/* 1:  UTC-10,  Hawaii                  */
/* 2:  UTC-9,   Alaska                  */
/* 3:  UTC-8,   Pacific USA, Tijuana    */
/* 4:  UTC-7,   Mountains USA           */
/* 5:  UTC-6,   Central USA, Mexico     */
/* 6:  UTC-5,   East USA, Bogota        */
/* 7:  UTC-4,   Caracas, La Paz         */
/* 8:  UTC-3.5, Newfoundland            */
/* 9:  UTC-3,   Brasilia                */
/* 10: UTC-2,   Atlantic                */
/* 11: UTC-1,   The Azores              */
/* 12: UTC+0,   London (GMT)            */
/* 13: UTC+1,   West Europa, Warsaw     */
/* 14: UTC+2,   East Europa, Cairo      */
/* 15: UTC+3,   Moscow, Nairobi         */
/* 16: UTC+3.5, Teheran                 */
/* 17: UTC+4,   Abu Dhabi, Volgograd    */
/* 18: UTC+4.5, Kaboul                  */
/* 19: UTC+5,   Islamabad, Karachi      */
/* 20: UTC+5.5, Bombay, New Dehli       */
/* 21: UTC+6,   Dhaka                   */
/* 22: UTC+7,   Bangkok                 */
/* 23: UTC+8,   Beijing, Hong-Kong      */
/* 24: UTC+9,   Tokyo                   */
/* 25: UTC+9.5, Darwin                  */
/* 26: UTC+10,  Sydney                  */
/* 27: UTC+11,  Solomon islands         */
/* 28: UTC+12,  Fiji islands            */

/**
 *  tim_GetSecondFrom1970_01_01
 *  @brief  Convert given date/time to seconds count from 1970/1/1,00:00:00 in SDK v1
 *  @param  Time       [in]Pointer to the input date/time
 *  @retval 0 if failed
 *          number of seconds from 1970/1/1,00:00:00
 */
u32 tim_GetSecondFrom1970_01_01(vm_rtcTimeFormat_t *Time);

/**
 *  tim_GetTimeZone
 *  @brief  Get current timezone index in SDK v1
 *  @param
 *  @retval timezone index
 */
u32 tim_GetTimeZone(void);

/**
 *  tim_GetUTCTime
 *  @brief  Get current UTC time in SDK v1
 *  @param  Time        [out]Pointer to the output UTC time
 *  @retval
 */
void tim_GetUTCTime(vm_rtcTimeFormat_t *Time);

/**
 *  tim_ConvertToLocalTime
 *  @brief  Convert UTC time to local time in SDK v1
 *  @param  pUTCTime        [in]Pointer to the input UTC time
            pLocalTime      [out]Pointer to the output local time
            TimeZone        [in]Timezone index in SDK v1
 *  @retval
 */
void tim_ConvertToLocalTime(vm_rtcTimeFormat_t *pUTCTime, vm_rtcTimeFormat_t *pLocalTime, u32 TimeZone);

#include "winsocket.h"
/* SDK V1 socket interfaces are defined & preserved in <winsocket.h> */

//SOCKET NET_socket (int af, int type, int protocol);
//int NET_recv_cb (SOCKET s, void* cbfunc, int flags);
//int NET_recvfrom_cb (SOCKET s, void* cbfunc, int flags);
//int NET_connect_cb (SOCKET s, const struct sockaddr  *name, int namelen, void* cbfunc);
//int NET_gethostbyname_cb (const char  *name, void* cbfunc);
//int NET_send_cb (SOCKET s, const char  *buf, int len, void* cbfunc, int flags);
//int NET_sendto_cb (SOCKET s, const char  *buf, int len, void* cbfunc, int flags, const struct sockaddr *to, int tolen);
//int NET_closesocket_cb (SOCKET s, void* cbfunc);
//u_long  NET_htonl (u_long hostlong);
//u_short NET_htons (u_short hostshort);
//u_long  NET_ntohl (u_long netlong);
//u_short NET_ntohs (u_short netshort);
//int NET_GetLastError(void);

#endif /* __SDK_MMI_V1_ADAPTION__ */

#endif /* __VEN_ADAPT_SDKV1_H__ */
