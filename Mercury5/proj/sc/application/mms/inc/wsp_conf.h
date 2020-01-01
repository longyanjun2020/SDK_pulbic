
#ifndef __WSP_CONF_H__
#define __WSP_CONF_H__

/********************WSP Configuration*************************/
#define WSP_CONNECT_SUPPORT         /**< Connection Session support.no use */

#define MAX_SESSION     1
#define WSP_CSDU        8000    /**< Default Maximum Client SDU */
#define WSP_SSDU        8000    /**< Default Maximum Server SDU */
#define WSP_MAX_SDU     (512*1024)/**< Default Maximum possible SDU size. WSP specification and
                                    its implemetation have the limitation on the SDU size.  Adding
                                    Check on this value to avoid potiential compatibility of GW side.
                                    e.g. CMCC GW will drop the request if our WSP_CSDU and WSP_SSDU set to 1M.
                                    Until now no wap gateway we have tested can really support downloading
                                    media which larger than 400K even they indicate they can when we do
                                    capability negotiation. 512K is also the Maximum value which we found
                                    in the real mobile phones*/

#ifdef  NCC_BROWSER1_2
#define WSP_MSGSIZE     1500   /**< Maximum WDP packet size */
#else
#define WSP_MSGSIZE     10240   /**< Maximum WDP packet size */
#endif

#define WSP_OPTIONS     0x00    /**< Protocol Options */
#define WSP_MOM         3       /**< Maximum Outstanding Method Requests.should not modified */
#define WSP_MOP         1       /**< Maximum Outstanding Push Requests */

/*optimize the headers we don't use.disable this option will
save about 30% http header decoding time*/
#ifndef NCC_BROWSER1_2
#define WSP_FULL_HEADER_DECODING
#endif

/********************WTP Configuration*************************/
#define WTP_EACH_SEGPDU_SIZE    1300 /**< Define the length of data in each segment invoke in a group.wap_wtp.header's
                                    length doesn't included. (WTP_EACH_SEGPDU_SIZE+additional headers length)<WSP_MSGSIZE. */

#define WTP_RetransTimeOut      16 /**< Retransmit interval,in ms.It should be modified according to the target system which the user using */

#define WTP_MAXRCR              3   /**< Maxium retransmit number */
#define MAX_GROUP_NUMBER        8   /**< Max supported receiving group number */
#define MAX_GROUP_NUMBER_RECV   25   /**< Max supported receiving group number */
#define MAX_ERRDES_SIZE     12  /**< Maxium error description buffer size */
#define  MAX_CAPS_BUF_SIZE          5

/** Define MACRO WAP_WTP_TPI_OPTION to enable support more TPI function. If network is not very good
or cpu is overload,this option should not be enable*/
#define WAP_WTP_TPI_OPTION
#ifdef	WAP_WTP_TPI_OPTION
/* Define WAP_WTP_TPI_OPTION_TOTLA_MESSAGE_SIZE to enable negotiate the total message size. */
#define WAP_WTP_TPI_OPTION_MAX_GROUPS /**< Enable WTP TPI OPTION GROUP */
#endif
#define WAP_WTP_TPI_OPTION_MAX_GROUPS_SIZE (MAX_GROUP_NUMBER*WTP_EACH_SEGPDU_SIZE+8)


/********************WTLS Configuration*************************/
#ifdef WTLS_SUPPORT/**< this should not be enable becase multiple instance is not supported by WTLS module */

    #define WTLS_RECEIVE                wtls_receive
    #define WTLS_SEND                   wtls_send
    #define WTLS_OPEN_RETRANSMIT(cout)  -1
    #define WTLS_IS_OPEN                wtls_is_open
    #define WTLS_CLOSE                  wtls_close
    #define WTLS_CLEAR                  wtls_clear
    #define WTLS_INIT                   wtls_init
    #define WTLS_OPEN                   wtls_open
    #define WTLS_PROCESS_RETRANSMIT     process_wtls_retran
#else
    #define WTLS_RECEIVE(buf)
    #define WTLS_SEND(ack,addr,len)
    #define WTLS_OPEN_RETRANSMIT(cout) -1
    #define WTLS_IS_OPEN() 1
    #define WTLS_CLOSE()
    #define WTLS_CLEAR()
    #define WTLS_INIT()
    #define WTLS_OPEN(addr) 1
    #define WTLS_PROCESS_RETRANSMIT()
#endif

/* Enable this option when you use wtls in the system which use big endian */

#ifdef CLIENT_TEST
    #define TEST_RSA_ANON
#endif

/********************OS Configuration*************************/

/********************Network Configuration*************************/
#define USE_WIN_NET

#ifdef USE_WIN_NET
    #define USE_WINDOW_SOCKET
    #define _WINSOCKAPI_
#endif

/*NOTE:all following options should not be enable becase multiple instance is not supported*/

/********************Debug Configuration*************************/
/**< Must enable this option if you use wap API in blocked way. default value is able */

#define DEBUG
#define WAP_DEBUG_EXCEPTION

//#define DEBUG_WAP_SIM_DATA_SAVE
//#define DEBUG_WAP_SIM_DATA_SAVE_EXT

/**< Work as a gsm mobile phone.now our requset can be accept by many wap server such as sohu.
but we can't access to provider's inter network for lackless of proper router for us.
this option should not used in user realese version because of something may be illegle*/

#define WAP_NACK_PSN        5   /* Create a nack which first psn is WAP_NACK_PSN.*/
#define WAP_NACK_INC        1   /* Number of pdu need to retransmit*/

#ifdef DEBUG_WAP_DATA_SIM
#define SIM_DATA_SIZE       15  /* Maximum pdu number which we can simulated*/

#define SIM_SERVER_ABORT    /*USER ABORT*/
#endif

#endif /* __WSP_CONF_H__ */

