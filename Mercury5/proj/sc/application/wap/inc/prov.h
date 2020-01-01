
#ifndef __PROV_H__
#define __PROV_H__

/*#include <string.h>
#include <stdlib.h>
#ifdef JACANA_MEM_TEST
#include <jacana_memory.h>
#endif*/
#ifndef UAPP_PUSH_PROV
//#error "PROV had been disabled"
#endif /* UAPP_PUSH_PROV */

#include <ncc_types.h>
#include <nccprov.h>

#ifdef __cplusplus
extern "C" {
#endif

/** macro define of provsion mime type */
#define PROV_DOC_TYPE_XML       0       /**< provision document format is XML */
#define PROV_DOC_TYPE_WBXML     1       /**< provision document format is WBXML */
#define PROV_DOC_TYPE_SI        3       /**< provision si message document format */
#define PROV_DOC_TYPE_TXT       2       /**< provision txt message document format */

#define PROV_PATH           "system"  /**< the path to save provision infomations */
#define PROV_FILE_NAME_LEN      128      /**< the length of file in provision */

#ifdef JACANA_MEM_TEST
#define PROV_Free(size)     jacanaLogFree(size, __FILE__)
#define PROV_Malloc(size)   jacanaLogMalloc(size, __FILE__)
#else /* JACANA_MEM_TEST */
#define PROV_Free(size)     CRTL_free(size)
#define PROV_Malloc(size)   CRTL_malloc(size)
#endif

//#define PROVMIN(a,b)    (a<b?a:b)

#ifdef _PROV_DEBUG_TRACE_
void mytrace(int iTraceType, char * szTraceName, void * traceValue, int iTraceLine, char * fileName);
#define PROV_TRACE(iTraceType, szTraceName, traceValue) mytrace(iTraceType, szTraceName, traceValue, __FILE__, __LINE__)
#else /**< _PROV_DEBUG_ */
#define PROV_TRACE(iTraceType, szTraceName, traceValue)
#endif

/**
    Parameter Length accroding to OMA_WAP_ProvCont_v1_1
*/
#define PROV_LENGTH_AACCEPT 16 /**< the length(byte) of AACCEPT */
#define PROV_LENGTH_AAUTHTYPE 32 /**< the length(byte of AAUTHTYPE) */
#define PROV_LENGTH_AAUTHNAME 80 /**< the length(byte) of AAUTHNAME */
#define PROV_LENGTH_AAUTHSECRET 40 /**< the length(byte) of AAUTHSECRET */
#define PROV_LENGTH_ADDR 64 /**< the length(byte) of ADDR */
#define PROV_LENGTH_APPID 16 /**< the length(byte) of APPID */
#define PROV_LENGTH_APROTOCOL 16 /**< the length(byte) of APROTOCOL */
#define PROV_LENGTH_AUTHNAME 16 /**< the length(byte) of AUTHNAME */
#define PROV_LENGTH_AUTHSECRET 16 /**< the length(byte) of AUTHSECRET */
#define PROV_LENGTH_BASAUTH_ID 16 /**< the length(byte) of BASAUTH-ID */
#define PROV_LENGTH_BASAUTH_PW 16 /**< the length(byte) of BASAUTH-PW */
#define PROV_LENGTH_CLIENT_ID 32 /**< the length(byte) of CLIENT-ID */
#define PROV_LENGTH_DNLINKSPEED 6 /**< the length(byte) of DNLINKSPEED */
#define PROV_LENGTH_DNS_ADDR 45 /**< the length(byte) of DNS-ADDR */
#define PROV_LENGTH_DOMAIN 64 /**< the length(byte) of DOMAIN */
#define PROV_LENGTH_LINGER 4 /**< the length(byte) of LINGER */
#define PROV_LENGTH_LINKSPEED 6 /**< the length(byte) of LINKSPEED */
#define PROV_LENGTH_NAME 48 /**< the length(byte) of NAME */
#define PROV_LENGTH_NAP_ADDRESS 64 /**< the length(byte) of NAP-ADDRESS */
#define PROV_LENGTH_NAPID 16 /**< the length(byte) of NAPID */
#define PROV_LENGTH_PHYSICAL_PROXY_ID 16 /**< the length(byte) of PHYSICAL-PROXY-ID */
#define PROV_LENGTH_PROVIDER_ID 32 /**< the length(byte) of PROVIDER-ID in characteristic APPLICATION */
#define PROV_LENGTH_PROVURL 64 /**< the length(byte) of PROVURL */
#define PROV_LENGTH_PROXY_ID 45 /**< the length(byte) of PROXY-ID */
#define PROV_LENGTH_PROXY_PROVIDER_ID 45 /**< the length(byte) of PROXY-PROVIDER-ID */
#define PROV_LENGTH_PROXY_PW 16 /**< the length(byte) of PROXY-PW */
#define PROV_LENGTH_PXADDR  45 /**< the length(byte) of PXADDR */
#define PROV_LENGTH_PXADDR_FQDN 64/**< the length(byte) of PXADDR-FQDN */
#define PROV_LENGTH_PXAUTH_ID 16 /**< the length(byte) of PXAUTH-ID */
#define PROV_LENGTH_PXAUTH_PW 16 /**< the length(byte) of PXAUTH-PW */
#define PROV_LENGTH_REREG_THRESHOLD 2 /**< the length(byte) of REREG-THRESHOLD */
#define PROV_LENGTH_RULE 16 /**< the length(byte) of RULE */
#define PROV_LENGTH_STARTPAGE 64 /**< the length(byte) of STARTPAGE */
#define PROV_LENGTH_URI 64 /**< the length(byte) of URI */
#define PROV_LENGTH_VALIDUNTIL 8 /**< the length(byte) of VALIDUNTIL */

/**
    MAX number of "1 or more entries" parameters
*/
#define MAX_DOMAIN          4 /**< max number of DOMAIN("1 to 4 entries") */
#define MAX_SERVICE         5 /**< max number of SERVICE */
#define MAX_BEARER          5 /**< max number of BEARER */

#define MAX_TO_NAPID        5 /**< max number of TO-NAPID */
#define MAX_PORT            5 /**< max number of PORT */
#define MAX_DNS_ADDR        5 /**< max number of DNS-ADDR */
#define MAX_PXAUTHINFO      5 /**< max number of PXAUTHINFO */
#define MAX_PHYSICAL_PROXY  5 /**< max number of PHYSICAL-PROXY */
#define MAX_NAPAUTHINFO     5 /**< max number of NAPAUTHINFO */
#define MAX_VALIDITY        5 /**< max number of VALIDITY */
#define MAX_PROXY_ID        5 /**< max number of PROXY-ID */
#define MAX_ADDR            5 /**< max number of ADDR */
#define MAX_APPADDR         5 /**< max number of APPADDR */
#define MAX_APPAUTH         5 /**< max number of APPAUTH */
#define MAX_RESOURCE        5 /**< max number of RESOURCE */
#define MAX_APPID           5 /**< max number of APPID */
#define MAX_PORTNBR         5 /**< max number of PORTNBR */
#define MAX_RULE            5 /**< max number of RULE */

/**
    Others
*/
#define PROV_WSP_VERSION_LENGTH 8 /**< the length(byte) of WSP-VERSION */
#define PROV_COUNTRY_LENGTH     8 /**< the length(byte) of COUNTRY */
#define PROV_NETWORK_LENGTH     8 /**< the length(byte) of NETWORK */
#define PROV_NETWORK_NUMBER     8 /**< the length(byte) of NETWORK NUMBER */
#define PROV_PERSERVED_LENGTH   20 /**< the length(byte) of PERSERVED */
#define PROV_VERSION_LENGTH 3 /**< the length(byte) of VERSION */
#define PROV_CA_LENGTH      4 /**< the length(byte) of context-allow */

#define PROV_UNKNOWN 0 /**< parmeter undefined in provision */
/**
    Range of value :
    PPGAUTH_TYPE
*/
/**< The PPGAUTH-TYPE parameter links the PROXY-ID and PROXY-PW to an authentication method. */
#define PROV_PPGAUTHTYPE_HTTPBASIC  0 /**< Basic authentication done according to [RFC2617] */
#define PROV_PPGAUTHTYPE_HTTPDIGEST 1 /**< Digest authentication done according to [RFC2617] */

/**
    Range of value :
    PXAUTH_TYPE
*/
/**< The PXAUTH-TYPE indicates the proxy authentication method */
#define PROV_PXAUTHTYPE_HTTPBASIC   1 /**< Basic authentication done according to [RFC2617] */
#define PROV_PXAUTHTYPE_HTTPDIGEST  2 /**< Digest authentication done according to [RFC2617] */
#define PROV_PXAUTHTYPE_HTTPWTLSSS  3 /**< WTLS Shared Secret authentication */

/**
    Range of value :
    PXADDRTYPE       0~3
    NAP_ADDRESSTYPE 0~7
    LOCAL_ADDRTYPE 0~1
    DNS_ADDR        0~1
    ADDR(in APPADDR characteristics) 0~3
*/
#define PROV_ADDR_IPV4          1       /**< IPv4 address */
#define PROV_ADDR_IPV6          2       /**< IPv6 address */
#define PROV_ADDR_E164          3       /**< A phone number according E164 scheme */
#define PROV_ADDR_ALPHA         4       /**< Generic alphanumberic address, see [RFC2396] */
#define PROV_ADDR_APN           5       /**< A GPRS APN */
#define PROV_ADDR_SCODE         6       /**< A USSD service code */
#define PROV_ADDR_TETRA_ITSI        7       /**< A TETERA SDS address, see [WAPWDP] */
#define PROV_ADDR_MAN           8       /**< A mobitex MAN address, see [WAPWDP] */

/**
    Range of value :
    SERVICE

*/
#define PROV_MAX_PORT_VALUE 65535
#define PROV_SERVICE_CL_WSP             PROV_MAX_PORT_VALUE+1 /**< WAP connection-less session service */
#define PROV_SERVICE_CO_WSP             PROV_MAX_PORT_VALUE+2 /**< WAP session service */
#define PROV_SERVICE_CL_SEC_WSP         PROV_MAX_PORT_VALUE+3 /**< WAP secure connection-less session service */
#define PROV_SERVICE_CO_SEC_WSP         PROV_MAX_PORT_VALUE+4 /**< WAP secure session service */
#define PROV_SERVICE_CO_SEC_WTA         PROV_MAX_PORT_VALUE+5 /**< WAP WTA secure session service (over WSP) */
#define PROV_SERVICE_CL_SEC_WTA         PROV_MAX_PORT_VALUE+6 /**< WAP WTA secure connection-less session service (over WSP) */
#define PROV_SERVICE_OTA_HTTP_TO        PROV_MAX_PORT_VALUE+7 /**< OTA-HTTP service (push), TO-TCP [PushOTA] */
#define PROV_SERVICE_OTA_HTTP_TLS_TO    PROV_MAX_PORT_VALUE+8 /**< OTA-HTTP secure service (push), TO-TCP [PushOTA] */
#define PROV_SERVICE_OTA_HTTP_PO        PROV_MAX_PORT_VALUE+9 /**< OTA-HTTP service (push), PO-TCP [PushOTA] */
#define PROV_SERVICE_OTA_HTTP_TLS_PO    PROV_MAX_PORT_VALUE+10 /**< OTA-HTTP secure service (push), PO-TCP [PushOTA] */

/**
    Range of vlaue :
    BEARER
*/
/**< valid network type of bearer */
#define PROV_BEARER_GSM_USSD            1 /**< network type is GSM-USSD */
#define PROV_BEARER_GSM_SMS             2 /**< network type is GSM-SMS */
#define PROV_BEARER_ANSI_136_GUTS       3 /**< network type is ANSI-136-GUTS */
#define PROV_BEARER_IS_95_CDMA_SMS      4 /**< network type is IS-95-CDMA_SMS */
#define PROV_BEARER_IS_95_CDMA_CSD      5 /**< network type is IS-95-CDMA_CSD */
#define PROV_BEARER_IS_95_CDMA_PACKET   6 /**< network type is IS-95-CDMA_PACKET */
#define PROV_BEARER_ANSI_136_CSD        7 /**< network type is ANSI-136-CSD */
#define PROV_BEARER_ANSI_136_GPRS       8 /**< network type is ANSI-136-GPRS */
#define PROV_BEARER_GSM_CSD             9 /**< network type is GSM-CSD */
#define PROV_BEARER_GSM_GPRS            10 /**< network type is GSM-GPRS */
#define PROV_BEARER_AMPS_CDPD           11 /**< network type is AMPS-CDPD */
#define PROV_BEARER_PDC_CSD             12 /**< network type is PDC-CSD */
#define PROV_BEARER_PDC_PACKET          13 /**< network type is PDC-PACKET */
#define PROV_BEARER_IDEN_SMS            14 /**< network type is IDEN-SMS */
#define PROV_BEARER_IDEN_CSD            15 /**< network type is IDEN-CSD */
#define PROV_BEARER_IDEN_PACKET         16 /**< network type is IDEN-PACKET */
#define PROV_BEARER_FLEX_REFLEX         17 /**< network type is FLEX-REFLEX */
#define PROV_BEARER_PHS_SMS             18 /**< network type is PHS-SMS */
#define PROV_BEARER_PHS_CSD             19 /**< network type is PHS-CSD */
#define PROV_BEARER_TETRA_SDS           20 /**< network type is TETRA-SDS */
#define PROV_BEARER_TETRA_PACKET        21 /**< network type is TETRA-PACKET */
#define PROV_BEARER_ANSI_136_GHOST      22 /**< network type is ANSI-136-GHOST */
#define PROV_BEARER_MOBITEX_MPAK        23 /**< network type is MOBITEX-MPAK */
#define PROV_BEARER_CDMA2000_1X_SIMPLE_IP   24 /**< network type is CDMA2000-1X-SIMPLE-IP */
#define PROV_BEARER_CDMA2000_1X_MOBILE_IP   25 /**< network type is CDMA2000-1X-MOBILE-IP */
#define PROV_BEARER_UNKNOWN         26
/**
    Range of value :
    CALLTYPE
*/
/**< The CALLTYPE parameter is used to define call type or protocol surpported by some bearers */
#define PROV_CALLTYPE_ANALOG_MODEM      1 /**< calltype is ANALOG-MODEM */
#define PROV_CALLTYPE_V_120             2 /**< calltype is V-120 */
#define PROV_CALLTYPE_V_110             3 /**< calltype is V-110 */
#define PROV_CALLTYPE_X_31              4 /**< calltype is X-31 */
#define PROV_CALLTYPE_BIT_TRANSPRENT    5 /**< calltype is BIT-TRANSPRENT */
#define PROV_CALLTYPE_DIRECT_ASYNCHRONOUS_DATA_SERVICE  6 /**< calltype is DIRECT-ASYNCHRONOUS-DATA-SERVICE */

/**
    Range of value :
    AUTH_ENTITY
*/
/**< AUTH-ENTITY parameter defines entity to which NAPAUTHINFO credentials are valid. */
#define PROV_AUTHENTITY_AAA 1 /**< Authentication credentials are valid for the AAA. */
#define PROV_AUTHENTITY_HA  2 /**< Authentication credentials are valid for the HA. */

/**
    Range of value :
    AAUTHLEVEL
*/
/**< The AAUTHLEVEL parameter tells how the provided authentication credentials are to be applied. */
#define PROV_AAUTHLEVEL_APPSRV  1 /**< Authentication done by the application service */
#define PROV_AAUTHLEVEL_OBEX    2 /**< OBEX authentication */

/**
    Range of value :
    AAUTHTYPE
*/
/**< The AAUTHTYPE parameter indicates the authentication method used by the application. */
#define PROV_AAUTHTYPE_HTTP_BASIC   1 /**< Basic authentication done according to [RFC2617] */
#define PROV_AAUTHTYPE_HTTP_DIGEST  2 /**< Digest authentication done according to [RFC2617] */
#define PROV_AAUTHTYPE_BASIC        3 /**< The 'basic' authentication method recognised by the application */
#define PROV_AAUTHTYPE_DIGEST       4 /**< The 'digest' authentication method recognised by the application */

/**
    Range of value :
    NAPAUTHTYPE
*/
#define PROV_NAPAUTH_TYPE_PAP   1 /**< Password Authentication Protocol type */
#define PROV_NAPAUTH_TYPE_CHAP  2 /**< Challenge Handshake Authentication Protocol type */
#define PROV_NAPAUTH_TYPE_MD5   3 /**< The MD5 Message-Digest Algorithm authentication type */

#define PROV_TYPE_CHARACTER_PXLOGICAL  1 /**< Definition of a logical proxy */
#define PROV_TYPE_CHARACTER_NAPDEF   2 /**< Definition of a Network Access Point */
#define PROV_TYPE_CHARACTER_BOOTSTRAP    3 /**< Defines parameters relevant for bootstrapping */
#define PROV_TYPE_CHARACTER_CLIENTIDENTITY  4 /**< Defines the client-ID */
#define PROV_TYPE_CHARACTER_VENDORCONFIG    5 /**< Vendor specific configuration */
#define PROV_TYPE_CHARACTER_APPLICATION 6 /**< Definition of general application specific parameters */
#define PROV_TYPE_CHARACTER_ACCESS  7 /**< Definition of a set of access rules for the terminal */

#define MAX_CHARACTER_NUM 5 /**< define the max save number of same characters */

/*
    The Macro Defination:
    example :
        PROV_DTD_PXLOGICAL_PXPHYSICAL_PORT_PORTNBR       1171001
    descirption :
        PROV_DTD_PXLOGICAL_PXPHYSICAL_PORT_PORTNBR : The node of provisioning doc tree
        1171001 can divide into  1-17-10-01,
        1   the 1st level number, 1-7   represent 7 top characteristics
        17  the 2nd level number, 01-xx represent parm or characterics on 2nd level.
        10  the 3rd level number, 01-xx represent parm or characterics on 3rd level.
        01  the 4th level number, 01-02 represent parm on 4th level.
*/
#define PROV_DTD_PXLOGICAL                               1000000
#define PROV_DTD_PXLOGICAL_PROXY_ID                      1010000
#define PROV_DTD_PXLOGICAL_PROXY_PW                      1020000
#define PROV_DTD_PXLOGICAL_PPGAUTH_TYPE                  1030000
#define PROV_DTD_PXLOGICAL_PROXY_PROVIDER_ID             1040000
#define PROV_DTD_PXLOGICAL_NAME                          1050000
#define PROV_DTD_PXLOGICAL_DOMAIN                        1060000
#define PROV_DTD_PXLOGICAL_TRUST                         1070000
#define PROV_DTD_PXLOGICAL_MASTER                        1080000
#define PROV_DTD_PXLOGICAL_STARTPAGE                     1090000
#define PROV_DTD_PXLOGICAL_BASAUTH_ID                    1100000
#define PROV_DTD_PXLOGICAL_BASAUTH_PW                    1110000
#define PROV_DTD_PXLOGICAL_WSP_VERSION                   1120000
#define PROV_DTD_PXLOGICAL_PUSHENABLED                   1130000
#define PROV_DTD_PXLOGICAL_PULLENABLED                   1140000
#define PROV_DTD_PXLOGICAL_PXAUTHINFO                    1150000
#define PROV_DTD_PXLOGICAL_PXAUTHINFO_PXAUTH_TYPE        1150100
#define PROV_DTD_PXLOGICAL_PXAUTHINFO_PXAUTH_ID          1150200
#define PROV_DTD_PXLOGICAL_PXAUTHINFO_PXAUTH_PW          1150300
#define PROV_DTD_PXLOGICAL_PORT                          1160000
#define PROV_DTD_PXLOGICAL_PORT_PORTNBR                  1160100
#define PROV_DTD_PXLOGICAL_PORT_SERVICE                  1160200
#define PROV_DTD_PXLOGICAL_PXPHYSICAL                    1170000
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_PHYSICAL_PROXY_ID  1170100
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_DOMAIN             1170200
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_PXADDR             1170300
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_PXADDRTYPE         1170400
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_PXADDR_FQDN        1170500
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_WSP_VERSION        1170600
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_PUSHENABLED        1170700
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_PULLENABLED        1170800
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_TO_NAPID           1170900
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_PORT               1171000
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_PORT_PORTNBR       1171001
#define PROV_DTD_PXLOGICAL_PXPHYSICAL_PORT_SERVICE       1171002
#define PROV_DTD_NAPDEF                                  2000000
#define PROV_DTD_NAPDEF_NAPID                            2010000
#define PROV_DTD_NAPDEF_BEARER                           2020000
#define PROV_DTD_NAPDEF_NAME                             2030000
#define PROV_DTD_NAPDEF_INTERNET                         2040000
#define PROV_DTD_NAPDEF_NAP_ADDRESS                      2050000
#define PROV_DTD_NAPDEF_NAP_ADDRTYPE                     2060000
#define PROV_DTD_NAPDEF_DNS_ADDR                         2070000
#define PROV_DTD_NAPDEF_CALLTYPE                         2080000
#define PROV_DTD_NAPDEF_LOCAL_ADDR                       2090000
#define PROV_DTD_NAPDEF_LOCAL_ADDRTYPE                   2100000
#define PROV_DTD_NAPDEF_LINKSPEED                        2110000
#define PROV_DTD_NAPDEF_DNLINKSPEED                      2120000
#define PROV_DTD_NAPDEF_LINGER                           2130000
#define PROV_DTD_NAPDEF_DELIVERY_ERR_SDU                 2140000
#define PROV_DTD_NAPDEF_DELIVERY_ORDER                   2150000
#define PROV_DTD_NAPDEF_TRAFFIC_CLASS                    2160000
#define PROV_DTD_NAPDEF_MAX_SDU_SIZE                     2170000
#define PROV_DTD_NAPDEF_MAX_BITRATE_UPLINK               2180000
#define PROV_DTD_NAPDEF_MAX_BITRATE_DNLINK               2190000
#define PROV_DTD_NAPDEF_RESIDUAL_BER                     2200000
#define PROV_DTD_NAPDEF_SDU_ERROR_RATIO                  2210000
#define PROV_DTD_NAPDEF_TRAFFIC_HANDL_PRIO               2220000
#define PROV_DTD_NAPDEF_TRANSFER_DELAY                   2230000
#define PROV_DTD_NAPDEF_GUARANTEED_BITRATE_UPLINK        2240000
#define PROV_DTD_NAPDEF_GUARANTEED_BITRATE_DNLINK        2250000
#define PROV_DTD_NAPDEF_MAX_NUM_RETRY                    2260000
#define PROV_DTD_NAPDEF_FIRST_RETRY_TIMEOUT              2270000
#define PROV_DTD_NAPDEF_REREG_THRESHOLD                  2280000
#define PROV_DTD_NAPDEF_T_BIT                            2290000
#define PROV_DTD_NAPDEF_NAPAUTHINFO                      2300000
#define PROV_DTD_NAPDEF_NAPAUTHINFO_AUTHTYPE             2300100
#define PROV_DTD_NAPDEF_NAPAUTHINFO_AUTHNAME             2300200
#define PROV_DTD_NAPDEF_NAPAUTHINFO_AUTHSECRET           2300300
#define PROV_DTD_NAPDEF_NAPAUTHINFO_AUTH_ENTITY          2300400
#define PROV_DTD_NAPDEF_NAPAUTHINFO_SPI                  2300500
#define PROV_DTD_NAPDEF_VALIDITY                         2310000
#define PROV_DTD_NAPDEF_VALIDITY_COUNTRY                 2310100
#define PROV_DTD_NAPDEF_VALIDITY_NETWORK                 2310200
#define PROV_DTD_NAPDEF_VALIDITY_SID                     2310300
#define PROV_DTD_NAPDEF_VALIDITY_SOC                     2310400
#define PROV_DTD_NAPDEF_VALIDITY_VALIDUNTIL              2310500
#define PROV_DTD_BOOTSTRAP                               3000000
#define PROV_DTD_BOOTSTRAP_NAME                          3010000
#define PROV_DTD_BOOTSTRAP_NETWORK                       3020000
#define PROV_DTD_BOOTSTRAP_COUNTRY                       3030000
#define PROV_DTD_BOOTSTRAP_PROXY_ID                      3040000
#define PROV_DTD_BOOTSTRAP_PROVURL                       3050000
#define PROV_DTD_BOOTSTRAP_CONTEXT_ALLOW                 3060000
#define PROV_DTD_CLIENTIDENTITY                          4000000
#define PROV_DTD_CLIENTIDENTITY_CLIENT_ID                4010000
#define PROV_DTD_VENDORCONFIG                            5000000
#define PROV_DTD_VENDORCONFIG_NAME                       5010000
#define PROV_DTD_VENDORCONFIG_                           5020000
#define PROV_DTD_APPLICATION                             6000000
#define PROV_DTD_APPLICATION_APPID                       6010000
#define PROV_DTD_APPLICATION_PROVIDER_ID                 6020000
#define PROV_DTD_APPLICATION_NAME                        6030000
#define PROV_DTD_APPLICATION_AACCEPT                     6040000
#define PROV_DTD_APPLICATION_APROTOCOL                   6050000
#define PROV_DTD_APPLICATION_TO_PROXY                    6060000
#define PROV_DTD_APPLICATION_TO_NAPID                    6070000
#define PROV_DTD_APPLICATION_ADDR                        6080000
#define PROV_DTD_APPLICATION_APPADDR                     6090000
#define PROV_DTD_APPLICATION_APPADDR_ADDR                6090100
#define PROV_DTD_APPLICATION_APPADDR_ADDRTYPE            6090200
#define PROV_DTD_APPLICATION_APPADDR_PORT                6090300
#define PROV_DTD_APPLICATION_APPADDR_PORT_PORTNBR        6090301
#define PROV_DTD_APPLICATION_APPADDR_PORT_SERVICE        6090302
#define PROV_DTD_APPLICATION_APPAUTH                     6100000
#define PROV_DTD_APPLICATION_APPAUTH_AAUTHLEVEL          6100100
#define PROV_DTD_APPLICATION_APPAUTH_AAUTHTYPE           6100200
#define PROV_DTD_APPLICATION_APPAUTH_AAUTHNAME           6100300
#define PROV_DTD_APPLICATION_APPAUTH_AAUTHSECRET         6100400
#define PROV_DTD_APPLICATION_APPAUTH_AAUTHDATA           6100500
#define PROV_DTD_APPLICATION_RESOURCE                    6110000
#define PROV_DTD_APPLICATION_RESOURCE_URI                6110100
#define PROV_DTD_APPLICATION_RESOURCE_NAME               6110200
#define PROV_DTD_APPLICATION_RESOURCE_AACCEPT            6110300
#define PROV_DTD_APPLICATION_RESOURCE_AAUTHTYPE          6110400
#define PROV_DTD_APPLICATION_RESOURCE_AAUTHNAME          6110500
#define PROV_DTD_APPLICATION_RESOURCE_AAUTHSECRET        6110600
#define PROV_DTD_APPLICATION_RESOURCE_AAUTHDATA          6110700
#define PROV_DTD_APPLICATION_RESOURCE_STARTPAGE          6110800
#define PROV_DTD_ACCESS                                  7000000
#define PROV_DTD_ACCESS_RULE                             7010000
#define PROV_DTD_ACCESS_APPID                            7020000
#define PROV_DTD_ACCESS_PORTNBR                          7030000
#define PROV_DTD_ACCESS_DOMAIN                           7040000
#define PROV_DTD_ACCESS_TO_NAPID                         7050000
#define PROV_DTD_ACCESS_TO_PROXY                         7060000

/** macro define of root_characteristic type */
#define PROV_CHARACTER_NUM 7            /**< max number of provision characters */

#define PROV_CHARACTER_PXLOGICAL            0
#define PROV_CHARACTER_NAPDEF               1
#define PROV_CHARACTER_BOOTSTRAP            2
#define PROV_CHARACTER_CLIENTIDENTITY   3
#define PROV_CHARACTER_VENDORCONFIG     4
#define PROV_CHARACTER_APPLICATION      5
#define PROV_CHARACTER_ACCESS           6

#define PROV_SYSTEM_DIR ""
#define ID_STRING_LEN  200

#define MAX_ADD_CONTEXT 254 /**< max supported additional context */

#define SECTYPE_NOTUSED     -1
#define SECTYPE_NETWPIN     0
#define SECTYPE_USERPIN     1
#define SECTYPE_USERNETWPIN 2
#define SECTYPE_USERPINMAC  3
#define SECTYPE_MAXTYPE     3

/**
 * Parse the PROV object and save them
 * \param   idString        the point of string to search
 * \param   bufferLen       the buffer length
 * \param   XmlType         the document type of PROV object
 *
 * \return  <ul>
 *              <li>when successful, return the plus
 *              <li>when failed, return -1
 *          </ul>
 */
int32_t Prov_SaveIdStr(int8_t * idString);

/**
 * Register the PROV object and save them
 * \param   provUrl        the TPS url string
 * \param   cxtAllow       the string of context-Allow
 *
 * \return  <ul>
 *              <li>when successful, return the positive integer as save file prefix name
 *              <li>when failed, return FALSE
 *          </ul>
 */
int32_t Prov_regContext(int8_t * provUrl, int8_t * cxtAllow);

/**
 * Register the PROV object validity
 * \param   provUrl        the TPS url string
 *
 * \return  <ul>
 *              <li>when successful, return TRUE
 *              <li>when failed, return FALSE
 *          </ul>
 */
int32_t Prov_chkContext(int8_t * provUrl);

int32_t Prov_SearchId(int8_t * idString);
int32_t Prov_SaveCharacter(int8_t * filename, int8_t * buf, int32_t characterType);

int32_t Prov_GetCharacterNum(int8_t * filename, int32_t characterType, int32_t * characterNum);
int32_t Prov_GetCharacter(int8_t * filename, int8_t * buf, int32_t characterType);

int32_t prov_parse(int32_t seccode,int8_t *maccode,int8_t* buf,int32_t buflen,int8_t xmltype);

typedef int8_t parm; /**< Definition of parm */

/**
    PXLOGICAL->PROV_PORT
    PXLOGICAL->PXPHYSICAL->PROV_PORT
    APPLICATION->APPADDR->PORT
*/
typedef struct _PROV_PORT {
    int32_t PORTNBR; /**< save the configuration of PORTNBR*/
    int32_t SERVICE[MAX_SERVICE]; /**< save the configuration of SERVICE*/
} PROV_PORT; /**< save the configuration of PORT settings*/

/**
    PXLOGICAL->PXAUTHINFO
*/
typedef struct _PROV_PXLOGICAL_PXAUTHINFO {
    parm PXAUTH_TYPE; /**< save the configuration of PXAUTH-TYPE*/
    parm PXAUTH_ID[PROV_LENGTH_PXAUTH_ID + 1]; /**< save the configuration of PXAUTH-ID*/
    parm PXAUTH_PW[PROV_LENGTH_PXAUTH_PW + 1]; /**< save the configuration of PXAUTH-PW*/
} PROV_PXLOGICAL_PXAUTHINFO; /**< save the configuration of PXAUTHINFO of PXLOGICAL settings*/

/**
    PXLOGICAL->PXPHYSICAL
*/
typedef struct _PROV_PXLOGICAL_PXPHYSICAL {
    parm PHYSICAL_PROXY_ID[PROV_LENGTH_PHYSICAL_PROXY_ID + 1]; /**< save the configuration of PROXY-ID of PHYSICAL*/
    parm provDOMAIN[MAX_DOMAIN][PROV_LENGTH_DOMAIN + 1]; /**< save the configuration of DOMAIN*/
    parm PXADDR[PROV_LENGTH_ADDR + 1]; /**< save the configuration of PXADDR*/
    parm PXADDRTYPE; /**< save the configuration of PXADDRTYPE*/
    parm PXADDR_FQDN[PROV_LENGTH_PXADDR_FQDN + 1]; /**< save the configuration of PXADDR-FQDN*/
    parm WSP_VERSION[PROV_WSP_VERSION_LENGTH + 1]; /**< save the configuration of WSP-VERSION*/
    parm PUSHENABLED; /**< save the configuration of PUSHENABLED*/
    parm PULLENABLED; /**< save the configuration of PULLENABLED*/
    parm TO_NAPID[MAX_TO_NAPID][PROV_LENGTH_NAPID + 1]; /**< save the configuration of PROXY-ID*/
    PROV_PORT PXPHYSICAL_PORT[MAX_PORT]; /**< save the configuration of PORT of PXPHYSICAL*/
} PROV_PXLOGICAL_PXPHYSICAL; /**< save the configuration of PXPHYSICAL of PXLOGICAL settings*/

/**
    PXLOGICAL
*/
typedef struct _PROV_PXLOGICAL {
    parm PROXY_ID[PROV_LENGTH_PROXY_ID + 1]; /**< save the configuration of PROXY-ID*/
    parm PROXY_PW[PROV_LENGTH_PROXY_PW + 1]; /**< save the configuration of PROXY-PW*/
    parm PPGAUTH_TYPE; /**< save the configuration of PPGAUTH-TYPE*/
    parm PROXY_PROVIDER_ID[PROV_LENGTH_PROXY_PROVIDER_ID + 1]; /**< save the configuration of PROXY-PROVIDER-ID*/
    parm NAME[PROV_LENGTH_NAME + 1]; /**< save the configuration of NAME*/
    parm provDOMAIN[MAX_DOMAIN][PROV_LENGTH_DOMAIN + 1]; /**< save the configuration of DOMAIN*/
    parm TRUST; /**< save the configuration of TRUST*/
    parm MASTER; /**< save the configuration of MASTER*/
    parm STARTPAGE[PROV_LENGTH_STARTPAGE + 1]; /**< save the configuration of STARTPAGE*/
    parm BASAUTH_ID[PROV_LENGTH_BASAUTH_ID + 1]; /**< save the configuration of BASAUTH-ID*/
    parm BASAUTH_PW[PROV_LENGTH_BASAUTH_PW + 1]; /**< save the configuration of BASAUTH-PW*/
    parm WSP_VERSION[PROV_VERSION_LENGTH + 1]; /**< save the configuration of WSP-VERSION*/
    parm PUSHENABLED; /**< save the configuration of PUSHENABLED*/
    parm PULLENABLED; /**< save the configuration of PULLENABLED*/
    PROV_PXLOGICAL_PXAUTHINFO PXAUTHINFO[MAX_PXAUTHINFO]; /**< save the configuration of PXAUTHINFO*/
    PROV_PXLOGICAL_PXPHYSICAL PHYSICAL_PROXY[MAX_PHYSICAL_PROXY]; /**< save the configuration of PHYSICAL-PROXY*/
    PROV_PORT PORT[MAX_PORT]; /**< save the configuration of PORT*/
} PROV_PXLOGICAL; /**< save the configuration of PXLOGICAL settings*/

/**
    NAPDEF_>NAPAUTHINFO
*/
typedef struct _PROV_NAPAUTHINFO {
    parm AUTHTYPE; /**< save the configuration of AUTHTYPE*/
    parm AUTHNAME[PROV_LENGTH_AUTHNAME + 1]; /**< save the configuration of AUTHNAME*/
    parm AUTHSECRET[PROV_LENGTH_AUTHSECRET + 1]; /**< save the configuration of AUTHSECRET*/
    parm AUTH_ENTITY; /**< save the configuration of AUTH_ENTITY*/
    parm SPI; /**< save the configuration of SPI*/
} PROV_NAPAUTHINFO; /**< save the configuration of NAPAUTHINFO settings*/

/**
    NAPDEF_>VALIDITY
*/
typedef struct _PROV_VALIDITY {
    parm COUNTRY[PROV_COUNTRY_LENGTH + 1]; /**< save the configuration of COUNTRY*/
    int32_t NETWORK[PROV_NETWORK_NUMBER]; /**< save the configuration of NETWORK*/
    int32_t SID; /**< save the configuration of SID*/
    int32_t SOC; /**< save the configuration of SOC*/
    int32_t VALIDUNTIL; /**< save the configuration of VALIDUNTIL*/
} PROV_VALIDITY; /**< save the configuration of VALIDITY settings*/

/**
    NAPDEF
*/
typedef struct _PROV_NAPDEF {
    parm NAPID[PROV_LENGTH_NAPID + 1]; /**< save the configuration of NAPID*/
    parm BEARER[MAX_BEARER]; /**< save the configuration of BEARER*/
    parm NAME[PROV_LENGTH_NAME + 1]; /**< save the configuration of NAME*/
    parm INTERNET; /**< save the configuration of INTERNET*/
    parm NAP_ADDRESS[PROV_LENGTH_NAP_ADDRESS + 1]; /**< save the configuration of NAP-ADDRESS*/
    parm NAP_ADDRTYPE; /**< save the configuration of NAP_ADDRTYPE*/
    parm DNS_ADDR[MAX_DNS_ADDR][PROV_LENGTH_DNS_ADDR + 1]; /**< save the configuration of DNS_ADDR*/
    parm CALLTYPE; /**< save the configuration of CALLTYPE*/
    parm LOCAL_ADDR[PROV_LENGTH_ADDR + 1]; /**< save the configuration of LOCAL-ADDR*/
    parm LOCAL_ADDRTYPE; /**< save the configuration of LOCAL-ADDRTYPE */
    int32_t LINKSPEED;                          /**< 0_autobanding */
    int32_t DNLINKSPEED;                /**< 0_autobanding */
    int32_t LINGER;                             /**< A decimal number, seconds*/
    parm DELIVERY_ERR_SDU;              /**< A hexadecimal number, See [3GPP24008] Figure 10.5.138*/
    parm DELIVERY_ORDER;                /**< A hexadecimal number, See [3GPP24008]*/
    parm TRAFFIC_CLASS;                         /**< A hexadecimal number, See [3GPP23107]*/
    parm MAX_SDU_SIZE;                          /**< A hexadecimal number, See [3GPP24008]*/
    parm MAX_BITRATE_UPLINK;            /**< A hexadecimal number, See [3GPP24008]*/
    parm MAX_BITRATE_DNLINK;            /**< A hexadecimal number, See [3GPP24008]*/
    parm RESIDUAL_BER;                          /**< A hexadecimal number, See [3GPP24008]*/
    parm SDU_ERROR_RATIO;               /**< A hexadecimal number, See [3GPP24008]*/
    parm TRAFFIC_HANDL_PRIO;            /**< A hexadecimal number, See [3GPP24008]*/
    parm TRANSFER_DELAY;                /**< A hexadecimal number, See [3GPP24008]*/
    parm GUARANTEED_BITRATE_UPLINK;     /**< A hexadecimal number, See [3GPP24008]*/
    parm GUARANTEED_BITRATE_DNLINK;     /**< A hexadecimal number, See [3GPP24008]*/
    parm MAX_NUM_RETRY;                         /**< A hexadecimal number, value:1_3 See [IS683B]*/
    parm FIRST_RETRY_TIMEOUT;           /**< A hexadecimal number, value:1_7 See [IS683B]*/
    parm REREG_THRESHOLD;               /**< A hexadecimal number, value:1_63 See [IS683B]*/
    parm T_BIT;                                         /**< whether reverse tunneling is required, See [IS683B]*/
    PROV_NAPAUTHINFO NAPAUTHINFO[MAX_NAPAUTHINFO]; /**< save the configuration of NAPAUTHINFO*/
    PROV_VALIDITY VALIDITY[MAX_VALIDITY]; /**< save the configuration of VALIDITY*/
} PROV_NAPDEF; /**< save the configuration of NAPDEF settings*/

/**
    BOOTSTRAP
*/
typedef struct _PROV_BOOTSTRAP {
    parm NAME[PROV_LENGTH_NAME + 1]; /**< save the configuration of NAME*/
    int32_t NETWORK; /**< save the configuration of NETWORK*/
    parm COUNTRY[PROV_COUNTRY_LENGTH + 1]; /**< save the configuration of COUNTRY*/
    parm PROXY_ID[MAX_PROXY_ID][PROV_LENGTH_PROXY_ID + 1]; /**< save the configuration of PROXY_ID*/
    parm PROVURL[PROV_LENGTH_PROVURL + 1]; /**< save the configuration of PROVURL*/
    parm CONTEXT_ALLOW[PROV_CA_LENGTH+1]; /**< save the configuration of CONTEXT-ALLOW*/
} PROV_BOOTSTRAP; /**< save the configuration of BOOTSTRAP settings*/

/**
    CLIENTIDENTITY
*/
typedef struct _PROV_CLIENTIDENTITY {
    parm CLIENT_ID[PROV_LENGTH_CLIENT_ID + 1]; /**< save the configuration of CLIENT_ID*/
} PROV_CLIENTIDENTITY; /**< save the configuration of CLIENTIDENTITY settings*/

/**
    PROV_VENDORCONFIG
*/
typedef struct _PROV_VENDORCONFIG {
    parm NAME[PROV_LENGTH_NAME + 1]; /**< save the configuration of NAME*/
    parm PERSERVED1[PROV_PERSERVED_LENGTH + 1]; /**< save the configuration of PERSERVED1*/
    parm PERSERVED2[PROV_PERSERVED_LENGTH + 1]; /**< save the configuration of PERSERVED2*/
    parm PERSERVED3[PROV_PERSERVED_LENGTH + 1]; /**< save the configuration of PERSERVED3*/
} PROV_VENDORCONFIG; /**< save the configuration of VENDORCONFIG settings*/

/**
    APPLICATION_>APPADDR
*/
typedef struct _PROV_APPADDR {
    parm ADDR[PROV_LENGTH_ADDR + 1]; /**< save the configuration of ADDR*/
    parm ADDRTYPE; /**< save the configuration of ADDRTYPE*/
    PROV_PORT PORT[MAX_PORT]; /**< save the configuration of PORT*/
} PROV_APPADDR; /**< save the configuration of APPADDR settings*/

/**
    APPLICATION_>APPAUTH
*/
typedef struct _PROV_APPAUTH {
    parm AAUTHLEVEL; /**< save the configuration of AAUTHLEVEL*/
    parm AAUTHTYPE[PROV_LENGTH_AAUTHTYPE+1]; /**< save the configuration of AAUTHTYPE, HTTP-BASIC, HTTP-DIGEST, BASIC, DIGEST or user-defined*/
    parm AAUTHNAME[PROV_LENGTH_AAUTHNAME + 1]; /**< save the configuration of AAUTHNAME*/
    parm AAUTHSECRET[PROV_LENGTH_AAUTHSECRET + 1]; /**< save the configuration of AAUTHSECRET*/
    parm AAUTHDATA; /**< save the configuration of AAUTHDATA*/
} PROV_APPAUTH; /**< save the configuration of APPAUTH settings */

/**
    APPLICATION_>RESOURCE
*/
typedef struct _PROV_RESOURCE {
    parm URI[PROV_LENGTH_URI + 1]; /**< save the configuration of URI*/
    parm NAME[PROV_LENGTH_NAME + 1]; /**< save the configuration of NAME*/
    parm AACCEPT[PROV_LENGTH_AACCEPT + 1]; /**< save the configuration of AACCEPT*/
    parm AAUTHTYPE; /**< save the configuration of AAUTHTYPE*/
    parm AAUTHNAME[PROV_LENGTH_AAUTHNAME + 1]; /**< save the configuration of AAUTHNAME*/
    parm AAUTHSECRET[PROV_LENGTH_AAUTHSECRET + 1]; /**< save the configuration of AAUTHSECRET*/
    parm AAUTHDATA; /**< save the configuration of AAUTHDATA*/
    parm STARTPAGE[PROV_LENGTH_STARTPAGE + 1]; /**< save the configuration of STARTPAGE*/
} PROV_RESOURCE; /**< save the configuration of RESOURCE settings */

/**
    APPLICATION
*/
typedef struct _PROV_APPLICATION {
    parm APPID[PROV_LENGTH_APPID + 1]; /**< save the configuration of APPID*/
    parm PROVIDER_ID[PROV_LENGTH_PROVIDER_ID + 1]; /**< save the configuration of PROVIDER-ID*/
    parm NAME[PROV_LENGTH_NAME + 1]; /**< save the configuration of NAME*/
    parm AACCEPT[PROV_LENGTH_AACCEPT + 1]; /**< save the configuration of AACCEPT*/
    parm APROTOCOL[PROV_LENGTH_APROTOCOL + 1]; /**< save the configuration of APROTOCOL*/
    parm TO_PROXY[MAX_PROXY_ID][PROV_LENGTH_PROXY_ID + 1]; /**< save the configuration of TO-PROXY*/
    parm TO_NAPID[MAX_TO_NAPID][PROV_LENGTH_NAPID + 1]; /**< save the configuration of TO-NAPID*/
    parm ADDR[MAX_ADDR][PROV_LENGTH_ADDR + 1]; /**< save the configuration of ADDR*/
    PROV_APPADDR APPADDR[MAX_APPADDR]; /**< save the configuration of APPADDR*/
    PROV_APPAUTH APPAUTH[MAX_APPAUTH]; /**< save the configuration of APPAUTH*/
    PROV_RESOURCE RESOURCE[MAX_RESOURCE]; /**< save the configuration of RESOURCE*/
} PROV_APPLICATION; /**< save the configuration of APPLICATION settings*/

/**
    ACCESS
*/
typedef struct _PROV_ACCESS {
    parm RULE[MAX_RULE][PROV_LENGTH_RULE + 1]; /**< save the configuration of RULE*/
    parm APPID[MAX_APPID][PROV_LENGTH_APPID + 1]; /**< save the configuration of APPID*/
    int32_t PORTNBR[MAX_PORTNBR]; /**< save the configuration of PORTNBR*/
    parm provDOMAIN[MAX_DOMAIN][PROV_LENGTH_DOMAIN + 1]; /**< save the configuration of DOMAIN*/
    parm TO_NAPID[MAX_TO_NAPID][PROV_LENGTH_NAPID + 1]; /**< save the configuration of TO-NAPID*/
    parm TO_PROXY[MAX_PROXY_ID][PROV_LENGTH_PROXY_ID + 1]; /**< save the configuration of TO-PROXY*/
} PROV_ACCESS; /**< save the configuration of ACCESS settings*/

typedef struct _PROV_DOCUMENT {
    PROV_PXLOGICAL      *Proxy[MAX_CHARACTER_NUM]; /**< save the configuration of PXLOGICAL*/
    PROV_NAPDEF     *Nap[MAX_CHARACTER_NUM]; /**< save the configuration of NAPDEF*/
    PROV_BOOTSTRAP      *Bootstrap[MAX_CHARACTER_NUM]; /**< save the configuration of BOOTSTRAP*/
    PROV_CLIENTIDENTITY *ClientID[MAX_CHARACTER_NUM]; /**< save the configuration of CLIENTIDENTITY*/
    PROV_VENDORCONFIG   *Vendor[MAX_CHARACTER_NUM]; /**< save the configuration of VENDORCONFIG*/
    PROV_APPLICATION    *App[MAX_CHARACTER_NUM]; /**< save the configuration of APPLICATION*/
    PROV_ACCESS     *Access[MAX_CHARACTER_NUM]; /**< save the configuration of ACCESS*/
}Prov_Doc;  /**< save the configuration of settings*/


#ifdef _WINCE_INTEGRATE_
/**
    for entry of nerwork connection in wince
*/
typedef struct _PROV_PROXY_PARM {
    parm appNAME[PROV_LENGTH_NAME + 1]; /**< save the configuration of appNAME*/
    parm NAME[PROV_LENGTH_NAME + 1]; /**< save the configuration of proxy NAME*/
    parm PROXY_ID[PROV_LENGTH_PROXY_ID + 1]; /**< save the configuration of PROXY-ID*/
    parm PHYSICAL_PROXY_ID[PROV_LENGTH_PHYSICAL_PROXY_ID + 1]; /**< save the configuration of PROXY-ID of PHYSICAL*/
    parm TO_NAPID[PROV_LENGTH_NAPID + 1]; /**< save the configuration of NAP-ID*/
    parm T0_APPID[PROV_LENGTH_NAME + 1]; /**< save the associated app NAME*/
    parm TO_APPADDR[PROV_LENGTH_ADDR + 1]; /**< save the configuration of ADDR*/
    parm szProxy[PROV_LENGTH_ADDR + 1];
    int32_t iPort;
}Prov_Proxyparm;

typedef struct _PROV_NAP_PARM {
    parm appNAME[PROV_LENGTH_NAME + 1]; /**< save the configuration of appNAME*/
    parm NAME[PROV_LENGTH_NAME + 1]; /**< save the configuration of nap NAME*/
    parm NAPID[PROV_LENGTH_NAPID + 1]; /**< save the configuration of NAPID*/
    parm T0_APPID[PROV_LENGTH_NAME + 1]; /**< save the associated app NAME*/
    parm TO_APPADDR[PROV_LENGTH_ADDR + 1]; /**< save the configuration of ADDR*/
}Prov_NAPparm;

typedef struct _PROV_MMS_PARM {
    parm mmsc[PROV_LENGTH_PROXY_ID + 1]; /**< save the mmsc of MMS*/
    parm PXADDR[PROV_LENGTH_ADDR + 1]; /**< save the configuration of PXADDR*/
    parm TO_NAPID[PROV_LENGTH_NAPID + 1]; /**< save the configuration of NAPID*/
    parm TO_PROXYID[PROV_LENGTH_PROXY_ID + 1]; /**< save the configuration of PROXY-ID*/
}Prov_MMSparm;

typedef struct _PROV_BROWSER_PARM {
    parm TO_PROXY[PROV_LENGTH_PROXY_ID + 1]; /**< save the proxy of BROWSER */
    parm TO_NAPID[PROV_LENGTH_NAPID + 1]; /**< save the configuration of NAPID*/
    parm favoriteURI[PROV_LENGTH_URI + 1]; /**< save the configuration of URI*/
}Prov_BROWSERparm;

#endif

typedef struct _TestProvDoc{
    int SECCode;  /**< sec code value */
    char PINCode[MAXPINLEN+1]; /**< pin code value */
    char MACCode[MAXMACLEN+1]; /**< mac code value */
    char * buf; /**< input provision buffer */
    int bufLen; /**< input provision buffer length */
    char type;  /**< input provision buffer type */
}TestProvDoc;


#ifdef __cplusplus
}
#endif

#endif /* __PROV_H__ */
