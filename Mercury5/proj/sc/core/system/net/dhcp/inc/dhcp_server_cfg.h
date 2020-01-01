/*
Copyright (c) 2013 , Caesar Chang (Chiennan Chang)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.

*/

#ifndef __DHCP_SERVER_CFG_H__
#define __DHCP_SERVER_CFG_H__

#define MAKE_IP_ADDRESS(A1,A2,A3,A4)   ((A1) | ( (A2)<<8 ) | ( (A3)<<16 ) | ( (A4)<<24 ) )

/*******************************************************************************
 *
 *   DHCP SERVER CONFIG 
 *
*******************************************************************************/
#define  DHCP_IP_MAX_NUM                                    253         // (.1 ~ .254 )
#define  DHCP_IP_POOL_BEGIN_DEFAULT                         20      
#define  DHCP_IP_POOL_END_DEFAULT                           219
#define  DHCP_SERVER_PORT                                   67
#define  DHCP_CLIENT_PORT                                   68

/*******************************************************************************
 *
 *   START DATETIME
 *
*******************************************************************************/

#define DATETIME_BEGIN_YEAR                                 2010
#define DATETIME_BEGIN_MONTH                                1
#define DATETIME_BEGIN_DAY                                  1
#define DATETIME_SECONDS_PER_DAY                            (86400)


#define DHCPD_SERVER_ADDRESS                                MAKE_IP_ADDRESS(192,168, 11, 8 )
#define DHCPD_DNS1_ADDRESS                                  MAKE_IP_ADDRESS(8,8, 8, 8 )
#define DHCPD_DNS2_ADDRESS                                  MAKE_IP_ADDRESS(8,8, 4, 4 )
#define DHCPD_ROUTER_ADDRESS                                MAKE_IP_ADDRESS(192,168, 11, 8 )

#define DHCPD_LEASE_TIME_IN_SECOND                          (2*DATETIME_SECONDS_PER_DAY)
#define DHCPD_RENEW_TIME_IN_SECOND                          (DATETIME_SECONDS_PER_DAY)

/*******************************************************************************
 *
 *   START DATETIME
 *
*******************************************************************************/
#define USE_MEM_POOL                                0
#define DHCP_SERVER_POOL_SIZE                      (100*1024)

/*******************************************************************************
 *
 *   CONFIGURATION FILE PATH
 *
*******************************************************************************/
#define DHCPD_SERVER_CFG_PATH               "ddsvrcfg.bin"
#define DHCPD_IP_POOL_PATH                  "ddippool.bin"
#define DHCPD_PATH_LENGTH                   64


// If set to 1, it is not compatable with lwip.
#define DHCPD_USE_SOCKET_API                0


#define  USE_64BIT_DATEIME                  0


#if     USE_64BIT_DATEIME
#define DateTime __int64
#else  //USE_64BIT_DATEIME
#define DateTime int
#endif //USE_64BIT_DATEIME

#endif // __DHCP_SERVER_CFG_H__

