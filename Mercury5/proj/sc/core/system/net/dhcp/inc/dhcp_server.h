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

#ifndef __DHCP_SERVER_H__
#define __DHCP_SERVER_H__
#include <stdarg.h>
//#include "sockets.h"
#include "cc.h"

#include "dhcp_server_cfg.h"
//#include "dhcp_server_port.h"

//----------------------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------------------

// 1. ip address string to int

//----------------------------------------------------------------------------------------
//Port
//----------------------------------------------------------------------------------------

// Get config 
//  1. server address
//  2. ip address range
//  3. server port
//  4. client port

// Get SystemDateTime
// calculate time span


/** DHCP PACKET LENGTH **/
#define BOOTP_ABSOLUTE_MIN_LEN  236
#define DHCP_VEND_SIZE          64
#define DHCP_MAX_MTU            1024
//#define DHCP_MAGIC_COOKIE       0x63538263UL

/*******************************************************************************
 *
 *   DHCP HARDWARE ADDRESS TYPE
 *
*******************************************************************************/
#define HW_ADDR_TYPE_ETHER                                  (1) 
#define HW_ADDR_TYPE_IEEE802                                (6) 
#define HW_ADDR_TYPE_FDDI                                   (8) 
//----------------------------------------------------------------
#define  BOOT_REQUEST                                       (1)
#define  BOOT_REPLY                                         (2)


/*******************************************************************************
 *
 *   DHCP Message Codes
 *
*******************************************************************************/
/*
#define  DHCP_DISCOVER                                      (1)
#define  DHCP_OFFER                                         (2)
#define  DHCP_REQUEST                                       (3)
#define  DHCP_DECLINE                                       (4)
#define  DHCP_ACK                                           (5)
#define  DHCP_NAK                                           (6)
#define  DHCP_RELEASE                                       (7)
#define  DHCP_INFORM                                        (8)
#define  DHCP_FORCERENEW                                    (9)
*/
/*******************************************************************************
 *
 *   DHCP OPTION CODES
 *
*******************************************************************************/
#define     DHO_PAD                                         (0)
#define     DHO_SUBNET_MASK                                 (1) 
#define     DHO_TIME_OFFSET                                 (2) 
#define     DHO_ROUTERS                                     (3) 
#define     DHO_TIME_SERVERS                                (4) 
#define     DHO_NAME_SERVERS                                (5) 
#define     DHO_DOMAIN_NAME_SERVERS                         (6) 
#define     DHO_LOG_SERVERS                                 (7) 
#define     DHO_COOKIE_SERVERS                              (8) 
#define     DHO_LPR_SERVERS                                 (9) 
#define     DHO_IMPRESS_SERVERS                             (10) 
#define     DHO_RESOURCE_LOCATION_SERVERS                   (11) 
#define     DHO_HOST_NAME                                   (12) 
#define     DHO_BOOT_SIZE                                   (13) 
#define     DHO_MERIT_DUMP                                  (14) 
#define     DHO_DOMAIN_NAME                                 (15) 
#define     DHO_SWAP_SERVER                                 (16) 
#define     DHO_ROOT_PATH                                   (17) 
#define     DHO_EXTENSIONS_PATH                             (18) 
#define     DHO_IP_FORWARDING                               (19) 
#define     DHO_NON_LOCAL_SOURCE_ROUTING                    (20) 
#define     DHO_POLICY_FILTER                               (21) 
#define     DHO_MAX_DGRAM_REASSEMBLY                        (22) 
#define     DHO_DEFAULT_IP_TTL                              (23) 
#define     DHO_PATH_MTU_AGING_TIMEOUT                      (24) 
#define     DHO_PATH_MTU_PLATEAU_TABLE                      (25) 
#define     DHO_INTERFACE_MTU                               (26) 
#define     DHO_ALL_SUBNETS_LOCAL                           (27) 
#define     DHO_BROADCAST_ADDRESS                           (28) 
#define     DHO_PERFORM_MASK_DISCOVERY                      (29) 
#define     DHO_MASK_SUPPLIER                               (30) 
#define     DHO_ROUTER_DISCOVERY                            (31) 
#define     DHO_ROUTER_SOLICITATION_ADDRESS                 (32) 
#define     DHO_STATIC_ROUTES                               (33) 
#define     DHO_TRAILER_ENCAPSULATION                       (34) 
#define     DHO_ARP_CACHE_TIMEOUT                           (35) 
#define     DHO_IEEE802_3_ENCAPSULATION                     (36) 
#define     DHO_DEFAULT_TCP_TTL                             (37) 
#define     DHO_TCP_KEEPALIVE_INTERVAL                      (38) 
#define     DHO_TCP_KEEPALIVE_GARBAGE                       (39) 
#define     DHO_NIS_DOMAIN                                  (40) 
#define     DHO_NIS_SERVERS                                 (41) 
#define     DHO_NTP_SERVERS                                 (42) 
#define     DHO_VENDOR_ENCAPSULATED_OPTIONS                 (43) 
#define     DHO_NETBIOS_NAME_SERVERS                        (44) 
#define     DHO_NETBIOS_DD_SERVER                           (45)
#define     DHO_NETBIOS_NODE_TYPE                           (46) 
#define     DHO_NETBIOS_SCOPE                               (47) 
#define     DHO_FONT_SERVERS                                (48) 
#define     DHO_X_DISPLAY_MANAGER                           (49) 
#define     DHO_DHCP_REQUESTED_ADDRESS                      (50) 
#define     DHO_DHCP_LEASE_TIME                             (51) 
#define     DHO_DHCP_OPTION_OVERLOAD                        (52) 
#define     DHO_DHCP_MESSAGE_TYPE                           (53) 
#define     DHO_DHCP_SERVER_IDENTIFIER                      (54) 
#define     DHO_DHCP_PARAMETER_REQUEST_LIST                 (55) 
#define     DHO_DHCP_MESSAGE                                (56) 
#define     DHO_DHCP_MAX_MESSAGE_SIZE                       (57) 
#define     DHO_DHCP_RENEWAL_TIME                           (58) 
#define     DHO_DHCP_REBINDING_TIME                         (59) 
#define     DHO_VENDOR_CLASS_IDENTIFIER                     (60) 
#define     DHO_DHCP_CLIENT_IDENTIFIER                      (61) 
#define     DHO_NWIP_DOMAIN_NAME                            (62) 
#define     DHO_NWIP_SUBOPTIONS                             (63) 
#define     DHO_NISV3_DOMAIN                                (64) 
#define     DHO_NISV3_SERVER                                (65) 
#define     DHO_TFTP_SERVER                                 (66) 
#define     DHO_BOOTFILE                                    (67) 
#define     DHO_MOBILE_IP_HOME_AGENT                        (68) 
#define     DHO_SMTP_SERVER                                 (69) 
#define     DHO_POP3_SERVER                                 (70) 
#define     DHO_NNTP_SERVER                                 (71) 
#define     DHO_WWW_SERVER                                  (72) 
#define     DHO_FINGER_SERVER                               (73) 
#define     DHO_IRC_SERVER                                  (74) 
#define     DHO_STREETTALK_SERVER                           (75) 
#define     DHO_STDA_SERVER                                 (76) 
#define     DHO_USER_CLASS                                  (77) 
#define     DHO_DIRECTORY_AGENT                             (78) 
#define     DHO_SERVICE_SCOPE                               (79) 
#define     DHO_RAPID_COMMIT                                (80) 
#define     DHO_FQDN                                        (81) 
#define     DHO_DHCP_AGENT_OPTIONS                          (82) 
#define     DHO_ISNS                                        (83) 
#define     DHO_NDS_SERVERS                                 (85) 
#define     DHO_NDS_TREE_NAME                               (86) 
#define     DHO_NDS_CONTEXT                                 (87) 
#define     DHO_BCMCS_CONTROLLER_DOMAIN_NAME_LIST           (88) 
#define     DHO_BCMCS_CONTROLLER_IPV4_ADDRESS               (89) 
#define     DHO_AUTHENTICATION                              (90) 
#define     DHO_CLIENT_LAST_TRANSACTION_TIME                (91) 
#define     DHO_ASSOCIATED_IP                               (92) 
#define     DHO_CLIENT_SYSTEM                               (93) 
#define     DHO_CLIENT_NDI                                  (94) 
#define     DHO_LDAP                                        (95) 
#define     DHO_UUID_GUID                                   (97) 
#define     DHO_USER_AUTHENTICATION_PROTOCOL                (98) 
#define     DHO_GEOCONF_CIVIC                               (99) 
#define     DHO_PCODE                                       (100) 
#define     DHO_TCODE                                       (101) 
#define     DHO_NETINFO_ADDRESS                             (112) 
#define     DHO_NETINFO_TAG                                 (113) 
#define     DHO_URL                                         (114) 
#define     DHO_AUTO_CONFIGURE                              (116) 
#define     DHO_NAME_SERVICE_SEARCH                         (117) 
#define     DHO_SUBNET_SELECTION                            (118) 
#define     DHO_DOMAIN_SEARCH                               (119) 
#define     DHO_SIP_SERVERS                                 (120) 
#define     DHO_CLASSLESS_STATIC_ROUTE                      (121) 
#define     DHO_CCC                                         (122) 
#define     DHO_GEOCONF                                     (123) 
#define     DHO_VI_VENDOR_CLASS                             (124) 
#define     DHO_VI_VENDOR_SPECIFIC_INFOMATION               (125) 
#define     DHO_ETHERBOOT_SIGNATURE                         (128) 
#define     DHO_CALL_SERVER_ADDRESS                         (129) 
#define     DHO_DISCRIMINATION_STRING                       (130) 
#define     DHO_REMOTE_STATISTICS_SERVER                    (131) 
#define     DHO_VLAN_ID                                     (132) 
#define     DHO_L2_PRIORITY                                 (133) 
#define     DHO_DSCP                                        (134) 
#define     DHO_HTTP_PROXY_FORPHONES                        (135) 
#define     DHO_OPTION_PANA_AGENT                           (136) 
#define     DHO_OPTION_PANA_V4_LOST                         (137) 
#define     DHO_OPTION_CAPWAP_AC_V4                         (138) 
#define     DHO_OPTION_IPV4_ADDRESS_MOS                     (139) 
#define     DHO_OPTION_IPV4_FQDN_MOS                        (140) 
#define     DHO_SIP_UA_CONFIGURATION_SERVICE_DOMAINS        (141) 
#define     DHO_ETHERBOOT                                   (150) 
#define     DHO_IP_TELEPHONE                                (176) 
#define     DHO_PACKETCABLE_DEPRECATED                      (177) 
#define     DHO_PXELINUX_MAGIC                              (208) 
#define     DHO_CONFIGURATION_FILE                          (209) 
#define     DHO_PATH_PREFIX                                 (210) 
#define     DHO_REBOOT_TIME                                 (211) 
#define     DHO_OPTION_6RD                                  (212) 
#define     DHO_OPTION_V4_ACCESS_DOMAIN                     (213) 
#define     DHO_SUBNET_ALLOCATION                           (220) 
#define     DHO_VIRTUAL_SUBNET                              (221) 
#define     DHO_CLASSLESS_STATIC_ROUTE_MS                   (249) 
#define     DHO_END                                         (255)


/*******************************************************************************
 *
 *   DATA STRUCTURES
 *
*******************************************************************************/
//Truman: Moved to .c file
/*
typedef struct tagSDHCP_RAW_MSG
{
    char            buffer[DHCP_MAX_MTU];
    int    			length;
    struct sockaddr address;
}SDHCP_RAW_MSG, *PSDHCP_RAW_MSG;
*/
typedef struct tagSDHCP_RAW_MSG *PSDHCP_RAW_MSG;

typedef struct tagSDHCPRAWOPTION
{
    char code;
    char length;
    char value[1];

} SDHCPRAWOPTION, *PSDHCPRAWOPTION;

typedef struct tagSDHCPOPTION
{
    struct tagSDHCPOPTION* next;
    char code;
    char length;
    char value[1];

} SDHCPOPTION, *PSDHCPOPTION;

typedef struct tagSDHCPMSG
{
    char    op;
    char    htype;
    char    hlen;
    char    hops;
    char    xid[4];
    char    secs[2];
    char    flags[2];
    char    ciaddr[4];
    char    yiaddr[4];
    char    siaddr[4];
    char    giaddr[4];
    char    chaddr[16];
    char    sname[64];
    char    file[128];
    PSDHCPOPTION options;
    char    *padding;

} SDHCPMSG, *PSDHCPMSG;


typedef struct tagSDHCPMSGBASE
{
    char    op;
    char    htype;
    char    hlen;
    char    hops;
    char    xid[4];
    char    secs[2];
    char    flags[2];
    char    ciaddr[4];
    char    yiaddr[4];
    char    siaddr[4];
    char    giaddr[4];
    char    chaddr[16];
    char    sname[64];
    char    file[128];

} SDHCPMSGBASE, *PSDHCPMSGBASE;



/*******************************************************************************
 *
 *   DHCP IP CONFIG
 *
*******************************************************************************/

#define DHCP_HW_ADDR_SIZE                       16

typedef union tagIP_ADDRESS
{
    unsigned long addr;
    unsigned char addr_byte[4];
} UIPADDR,*PUIPADDR;

typedef struct tagSSERVER_CONFIG
{
    // the dhcp server address
    UIPADDR dhcp_server_address;
    // the 1st dns server address
    UIPADDR dns1_address;
    // the 2nd dns server address
    UIPADDR dns2_address;
    // router address
    UIPADDR router_address;
    // lease time in seconds
    int lease_time; 
    // renewal time in seconds
    int renew_time;

    // the server port
    int server_port;
    int client_port;    

    int num_db_size;
    int ip_pool_start;
    int ip_pool_end;

    //    int ip_pool_next_free;

    //int rtc_exist;
    DateTime server_start_time;
}SSERVERCONFIG, *PSSERVERCONFIG;

typedef struct tagSIP_CONFIG
{
    DateTime   start_time;
    DateTime   due_time;
    char hw_address[DHCP_HW_ADDR_SIZE];
    UIPADDR ip_address;
    bool taken;			// set, when a client used the ip
}SIPCONFIG, *PSIPCONFIG;

struct SemLock;

typedef struct tagSDHCP_DB
{
    // Server data 
    SSERVERCONFIG server_config;
    SIPCONFIG Ip[DHCP_IP_MAX_NUM]; // ip_pool_start ~ ip_pool_start+DHCP_IP_MAX_NUM-1 ( 32 * 254 )

    // variable 
    bool            bStartServer;
    struct udp_pcb *pcb_dhcps;
    //MMPF_OS_SEMID   idSemLock;
    struct SemLock *sem_lock;
} SDHCPDB,*PSDHCPDB;

 
//-------------------------------------------------------
//  Log print
//-------------------------------------------------------
/*******************************************************************************
 *
 *   Log print
 *
*******************************************************************************/

//#define printc printf
#define vsprintc    vsprintf

#define DHCP_LOG_LEVEL_FATAL      0
#define DHCP_LOG_LEVEL_ERROR      1
#define DHCP_LOG_LEVEL_WARNING    2
#define DHCP_LOG_LEVEL_INFO       3
#define DHCP_LOG_LEVEL_DEBUG      5

#define DHCP_LOG_LEVEL  DHCP_LOG_LEVEL_ERROR
#define DHCP_LOG_ENABLE_FILENAME    0
#define DHCP_LOG_ENABLE_LINE_NUM    1

void DhcpLogPrint( int log_level, 
                #if DHCP_LOG_ENABLE_FILENAME
                   char* szFile, 
                #endif //DHCP_LOG_ENABLE_FILENAME
                #if     DHCP_LOG_ENABLE_LINE_NUM                             
                   int line,  
                #endif  //DHCP_LOG_ENABLE_LINE_NUM
                   char* szFmt, ... );


#if DHCP_LOG_ENABLE_FILENAME
    #if DHCP_LOG_ENABLE_LINE_NUM
        #define DHCPD_FATAL(...)    DhcpLogPrint( DHCP_LOG_LEVEL_FATAL  , __FILE__, __LINE__, __VA_ARGS__)
        #define DHCPD_ERROR(...)    DhcpLogPrint( DHCP_LOG_LEVEL_ERROR  , __FILE__, __LINE__, __VA_ARGS__)
        #define DHCPD_WARNING(...)  DhcpLogPrint( DHCP_LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
        #define DHCPD_INFO(...)     DhcpLogPrint( DHCP_LOG_LEVEL_INFO   , __FILE__, __LINE__, __VA_ARGS__)
        #define DHCPD_DEBUG(...)    DhcpLogPrint( DHCP_LOG_LEVEL_DEBUG  , __FILE__, __LINE__, __VA_ARGS__)
    #else //DHCP_LOG_ENABLE_LINE_NUM
        #define DHCPD_FATAL(...)    DhcpLogPrint( DHCP_LOG_LEVEL_FATAL  , __FILE__,           __VA_ARGS__)
        #define DHCPD_ERROR(...)    DhcpLogPrint( DHCP_LOG_LEVEL_ERROR  , __FILE__,           __VA_ARGS__)
        #define DHCPD_WARNING(...)  DhcpLogPrint( DHCP_LOG_LEVEL_WARNING, __FILE__,           __VA_ARGS__)
        #define DHCPD_INFO(...)     DhcpLogPrint( DHCP_LOG_LEVEL_INFO   , __FILE__,           __VA_ARGS__)
        #define DHCPD_DEBUG(...)    DhcpLogPrint( DHCP_LOG_LEVEL_DEBUG  , __FILE__,           __VA_ARGS__)
    #endif //DHCP_LOG_ENABLE_LINE_NUM
#else //DHCP_LOG_ENABLE_FILENAME
    #if DHCP_LOG_ENABLE_LINE_NUM
        #define DHCPD_FATAL(...)    DhcpLogPrint( DHCP_LOG_LEVEL_FATAL  ,           __LINE__, __VA_ARGS__)
        #define DHCPD_ERROR(...)    DhcpLogPrint( DHCP_LOG_LEVEL_ERROR  ,           __LINE__, __VA_ARGS__)
        #define DHCPD_WARNING(...)  DhcpLogPrint( DHCP_LOG_LEVEL_WARNING,           __LINE__, __VA_ARGS__)
        #define DHCPD_INFO(...)     DhcpLogPrint( DHCP_LOG_LEVEL_INFO   ,           __LINE__, __VA_ARGS__)
        #define DHCPD_DEBUG(...)    DhcpLogPrint( DHCP_LOG_LEVEL_DEBUG  ,           __LINE__, __VA_ARGS__)
    #else //DHCP_LOG_ENABLE_LINE_NUM                                                      
        #define DHCPD_FATAL(...)    DhcpLogPrint( DHCP_LOG_LEVEL_FATAL  ,                     __VA_ARGS__)
        #define DHCPD_ERROR(...)    DhcpLogPrint( DHCP_LOG_LEVEL_ERROR  ,                     __VA_ARGS__)
        #define DHCPD_WARNING(...)  DhcpLogPrint( DHCP_LOG_LEVEL_WARNING,                     __VA_ARGS__)
        #define DHCPD_INFO(...)     DhcpLogPrint( DHCP_LOG_LEVEL_INFO   ,                     __VA_ARGS__)
        #define DHCPD_DEBUG(...)    DhcpLogPrint( DHCP_LOG_LEVEL_DEBUG  ,                     __VA_ARGS__)
    #endif //DHCP_LOG_ENABLE_LINE_NUM

#endif //DHCP_LOG_ENABLE_FILENAME


/*******************************************************************************
 *
 *   Functions Prototypes
 *
*******************************************************************************/

PSDHCPMSG DhcpOnDiscovery( PSDHCPDB pDhcpDb, PSDHCPMSG pMsg );
PSDHCPMSG DhcpOnInform( PSDHCPDB pDhcpDb, PSDHCPMSG pMsg );
PSDHCPMSG DhcpOnRequest( PSDHCPDB pDhcpDb, PSDHCPMSG pMsg );
PSDHCPMSG DhcpOnRelease( PSDHCPDB pDhcpDb, PSDHCPMSG pMsg );
PSDHCPMSG DhcpOnDecline( PSDHCPDB pDhcpDb, PSDHCPMSG pMsg );

/* Truman@131009 Used BOOL before. That is in Firmware/driver/mempool/MemPool.h or Firmware/misc/MemPool.h
 * and in this file bool is also used.
 * Since this file is in Firmware/NET, so bool is used instead.
 */
bool DhcpServerStop(void);


DateTime SecondsNumberOffset( int year, int mon, int day, int hour, int min, int sec );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpDbGet
 *
 *   DESCRIPTION
 *
 *      Get the dhcp server database
 *
 *   ARGUMENTS
 *
 *
 *
 *   RETURN
 *   
 *      The pointer of the dhcp server database.
 *
*******************************************************************************/
PSDHCPDB DhcpDbGet(void);

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpDbInit
 *
 *   DESCRIPTION
 *
 *       Initialization of the dhcp server database config. Load the config from
 *      Storage.
 *
 *   ARGUMENTS
 *
  *      pDhcpDb  - The pointer of the dhcp server database config.
 *
 *   RETURN
 *   
 *      N/A
 *
*******************************************************************************/
bool DhcpDbInit( PSDHCPDB pDhcpDb );
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpDbCheckAndRemoveTimeoutIp
 *
 *   DESCRIPTION
 *
 *      Check IP address array and remove the item which is time out.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The database of the dhcp server.
 *      now      - The time now in seconds. 
 *
 *   RETURN
 *   
 *      TRUE  - Successful.
 *      FALSE - Failed.
 *
*******************************************************************************/
bool DhcpDbCheckAndRemoveTimeoutIp( PSDHCPDB pDhcpDb, unsigned long now );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpDbAllocIp
 *
 *   DESCRIPTION
 *
 *      Allocate a ip configuration for the specific client HW address.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The database of the dhcp server.
 *      hw_address  - The client hw address.
 *
 *   RETURN
 *   
 *      NON-NULL - The allocated ip configuration.
 *      NULL     - Failed.
 *
*******************************************************************************/
PSIPCONFIG DhcpDbAllocIp( PSDHCPDB pDhcpDb, char* hw_address);
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpDbRemoveIp
 *
 *   DESCRIPTION
 *
 *      Remove the ip configuration which assigned for the client hw address.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The database of the dhcp server.
 *      hw_address  - The client hw address.
 *
 *   RETURN
 *   
 *      N/A
 *
*******************************************************************************/
PSIPCONFIG DhcpDbRemoveIp(PSDHCPDB pDhcpDb, char* hw_address);

/*******************************************************************************
 *
 *   DHCP Server functions
 *
*******************************************************************************/

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpFreeMsg
 *
 *   DESCRIPTION
 *
 *      Free a DHCP message.
 *
 *   ARGUMENTS
 *
 *      pMsg  - The  DHCP message to free.
 *
 *
 *   RETURN
 *   
 *      TRUE  - Successful.
 *      FALSE - Failed.
 *
*******************************************************************************/
bool DhcpFreeMsg( PSDHCPMSG   pMsg );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpParseArg
 *
 *   DESCRIPTION
 *
 *      Parsing a raw message to a cooked message.
 *
 *   ARGUMENTS
 *
 *      buffer  - The buffer of the raw message.
 *      length  - The length of the buffer
 *
 *
 *   RETURN
 *   
 *      N/A
 *
*******************************************************************************/
PSDHCPMSG DhcpParseArg(char* buffer, int length );
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpMsgGetOption
 *
 *   DESCRIPTION
 *      Search the option with the specific code.
 *
 *   ARGUMENTS
 *
 *      pMsg - The DHCP Message.
 *      code - The key value of the code.
 *
 *   RETURN
 *      NON-NULL    - The pointer of the option.
 *      NULL - Not found.
 *
*******************************************************************************/
PSDHCPOPTION DhcpMsgGetOption(PSDHCPMSG pMsg, char code );
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpMsgAppendOption
 *
 *   DESCRIPTION
 *
 *      Append a option with assigned values on a option or a message .
 *
 *   ARGUMENTS
 *
 *      pMsg  - The DHCP message. If it's the 1st option of the message, set to non-NULL. 
 *              Otherwise set to NULL.
 *      pPrevOption - The previous option of the new option. If the new option is the 1st
 *                    option, then this value is set to NULL. Otherwise set to non-NULL. The
 *                     new option will append at the tail of this previous option.
 *
 *
 *   RETURN
 *   
 *      Non-NULL - The new option.
 *      NULL     - Failed.
 *
*******************************************************************************/
PSDHCPOPTION DhcpMsgAppendOption(PSDHCPMSG pMsg, PSDHCPOPTION pPrevOption, char code, char length, void* value );
PSDHCPOPTION DhcpMsgAppendOption8(PSDHCPMSG pMsg, PSDHCPOPTION pPrevOption, char code, unsigned char value );
PSDHCPOPTION DhcpMsgAppendOption16(PSDHCPMSG pMsg, PSDHCPOPTION pPrevOption, char code, unsigned short value );
PSDHCPOPTION DhcpMsgAppendOption32(PSDHCPMSG pMsg,PSDHCPOPTION pPrevOption, char code, unsigned long value );
PSDHCPOPTION DhcpMsgAppendOption64(PSDHCPMSG pMsg,PSDHCPOPTION pPrevOption, char code, unsigned long low, unsigned long hi );
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpPackMsg
 *
 *   DESCRIPTION
 *
 *      Pack a DCHP message to a raw message, which is ready to send to internet.
 *
 *   ARGUMENTS
 *
 *      pMsg  - The DHCP message.
 *      buffer- The buffer of the raw message.
 *      buff_length - The length of the buffer of the raw message.
 *
 *
 *   RETURN
 *   
 *      TRUE - Successful.
 *      FALSE - Failed.
 *
*******************************************************************************/
int DhcpPackMsg( PSDHCPMSG   pMsg, char* buffer, int buff_length );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpOnDiscovery
 *
 *   DESCRIPTION
 *
 *      The message handler of Discovery.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The DHCP database.
 *      pMsg     - The Discovery message.
 *
 *   RETURN
 *   
 *      Non-NULL - The response message.
 *      NULL     - Failed or no response.
 *
*******************************************************************************/
PSDHCPMSG DhcpOnDiscovery(PSDHCPDB pDhcpDb, PSDHCPMSG pMsg );
  
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpOnRequest
 *
 *   DESCRIPTION
 *
 *      The message handler of Request.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The DHCP database.
 *      pMsg     - The Request message.
 *
 *   RETURN
 *   
 *      Non-NULL - The response message.
 *      NULL     - Failed or no response.
 *
*******************************************************************************/
PSDHCPMSG DhcpOnRequest( PSDHCPDB pDhcpDb, PSDHCPMSG pMsg );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpOnInform
 *
 *   DESCRIPTION
 *
 *      The message handler of Inform.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The DHCP database.
 *      pMsg     - The Inform message.
 *
 *   RETURN
 *   
 *      Non-NULL - The response message.
 *      NULL     - Failed or no response.
 *
*******************************************************************************/
PSDHCPMSG DhcpOnInform( PSDHCPDB pDhcpDb, PSDHCPMSG pMsg );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpOnRelease
 *
 *   DESCRIPTION
 *
 *      The message handler of Release.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The DHCP database.
 *      pMsg     - The Release message.
 *
 *   RETURN
 *   
 *      NULL
 *
*******************************************************************************/
PSDHCPMSG DhcpOnRelease( PSDHCPDB pDhcpDb, PSDHCPMSG pMsg );
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpOnDecline
 *
 *   DESCRIPTION
 *
 *      The message handler of Decline.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The DHCP database.
 *      pMsg     - The Decline message.
 *
 *   RETURN
 *   
 *      NULL     
 *
*******************************************************************************/
PSDHCPMSG DhcpOnDecline( PSDHCPDB pDhcpDb, PSDHCPMSG pMsg );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpSendResponse
 *
 *   DESCRIPTION
 *
 *      Send the response message.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The DHCP database.
 *      pResponseMsg     - The response message.
 *
 *   RETURN
 *   
 *      N/A
 *
*******************************************************************************/
void DhcpSendResponse(PSDHCPDB pDhcpDb,  PSDHCPMSG pResponseMsg );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpDispatchMsg
 *
 *   DESCRIPTION
 *
 *      Dispatch the DHCP message to the specific handler.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The DHCP database.
 *      pMsg     - The received message.
 *
 *
 *   RETURN
 *   
 *      The response message.
 *
*******************************************************************************/
PSDHCPMSG DhcpDispatchMsg( PSDHCPDB pDhcpDb, PSDHCPMSG      pMsg );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpMsgHandler
 *
 *   DESCRIPTION
 *
 *      The primary DHCP message handler.
 *
 *   ARGUMENTS
 *
 *      pDhcpDb  - The DHCP database.
 *      pRawMsg  - The raw message.
 *
 *   RETURN
 *   
 *      0       - OK
 *      Other   - Error
 *
*******************************************************************************/
int DhcpMsgHandler( PSDHCPDB pDhcpDb, PSDHCP_RAW_MSG pRawMsg);
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpServerSetToDefault
 *
 *   DESCRIPTION
 *
 *      Reset the configuration of the dhcp server and save it to storage.
 *
 *   ARGUMENTS
 *
 *
 *   RETURN
 *   
 *      TRUE - OK
 *      FALSE - Failed.
 *
*******************************************************************************/
bool DhcpServerSetToDefault(void);

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpServerStop
 *
 *   DESCRIPTION
 *
 *      Stop DHCP server and save the setting.
 *
 *   ARGUMENTS
 *
 *
 *   RETURN
 *   
 *      TRUE - OK
 *      FALSE - Failed.
 *
*******************************************************************************/
bool DhcpServerStop(void);
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpServerStop
 *
 *   DESCRIPTION
 *
 *      Start DHCP server and save the setting.
 *
 *   ARGUMENTS
 *      N/A
 *
 *   RETURN
 *   
 *      TRUE - OK
 *      FALSE - Failed.
 *
*******************************************************************************/
bool DhcpServerStart(void);

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpLogPrint
 *
 *   DESCRIPTION
 *
 *      The implementation of the dbg print
 *
 *   ARGUMENTS
 *
 *
 *
 *   RETURN
 *   
 *      N/A
 *
*******************************************************************************/
void DhcpLogPrint( int log_level, 
                    #if DHCP_LOG_ENABLE_FILENAME
                                     char* szFile, 
                    #endif //DHCP_LOG_ENABLE_FILENAME
                    #if     DHCP_LOG_ENABLE_LINE_NUM                             
                                     int line,  
                    #endif                                   
                                     char* szFmt, ... );
                                     
                                     
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DhcpIsServerStart
 *
 *   DESCRIPTION
 *
 *      Is  DHCP server started.
 *
 *   ARGUMENTS
 *
 *
 *   RETURN
 *   
 *      TRUE  - Started
 *      FALSE - Stoped.
 *
*******************************************************************************/
bool DhcpIsServerStart(void);

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DayNumber
 *
 *   DESCRIPTION
 *
 *      DayNumber from 1-1-1
 *
 *   ARGUMENTS
 *
 *      date
 *
 *   RETURN
 *   
 *      The days from 1-1-1.
 *
*******************************************************************************/
int DayNumber( int year, int mon, int day );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      DayNumberOffset
 *
 *   DESCRIPTION
 *
 *      Get the days from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY
 *
 *   ARGUMENTS
 *
 *
 *   RETURN
 *   
 *      The days from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY
 *
*******************************************************************************/
int DayNumberOffset( int year, int mon, int day );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolLeakDetectStart
 *
 *   DESCRIPTION
 *
 *      Get the days from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY to Year-Month-Day
 *
 *   ARGUMENTS
 *
 *      days  - The days from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY.
 *      Output:
 *           year, month, day
 *   RETURN
 *      0 - Successful
 *      
 *
*******************************************************************************/
int DaysToDate( int days, int* year, int* month, int* day );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      SecondsNumberOffset
 *
 *   DESCRIPTION
 *
 *      Getthe seconds from DATETIME_BEGIN_YEAR-DATETIME_BEGIN_MONTH-DATETIME_BEGIN_DAY 00-00-00 
 *      to Year-Month-Day hour-min-sec.
 *
 *   ARGUMENTS
 *
 *      year-mon-day
 *      hour-min-sec
 *
 *   RETURN
 *   
 *      Seconds 
 *
*******************************************************************************/
DateTime SecondsNumberOffset( int year, int mon, int day, int hour, int min, int sec );


/*******************************************************************************
 *
 *   Serialization
 *
*******************************************************************************/
bool DhcpPort_ResetServerCfg( PSDHCPDB pDhcpDb );
bool DhcpPort_ResetIpPool( PSDHCPDB pDhcpDb );
bool DhcpPort_LoadCfg(char* buffer, unsigned int ulSize, char* szFilename );
bool DhcpPort_SaveCfg(char* buffer, unsigned int ulSize, char* szFilename );
bool DhcpPort_LoadDB(PSDHCPDB pDhcpDb);
bool DhcpPort_StoreDB(PSDHCPDB pDhcpDb);


/*******************************************************************************
 *
 *   Synchronization
 *
*******************************************************************************/

bool DhcpdPort_DB_LockInit(PSDHCPDB pDhcpDb);
int DhcpdPort_DB_LockRelease(PSDHCPDB pDhcpDb);
void DhcpdPort_DB_Lock(PSDHCPDB pDhcpDb);
void DhcpdPort_DB_Unlock(PSDHCPDB pDhcpDb);


#endif //__DHCP_SERVER_H__

