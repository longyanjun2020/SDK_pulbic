/****************************************************************************/
/*  File    : winsock_config.h                                              */
/*--------------------------------------------------------------------------*/
/*  Scope   : Constants,Structure, Macro and Prototypes definition          */
/*            of MIC XML parser                                             */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*
 * --------------------------------------------------------------------------
 *  Date     | Author | Revision       | Description
 * ----------+--------+----------------+-------------------------------------
 */

#ifndef _WINSOCK_API_CONFIGURATION_H_
#define _WINSOCK_API_CONFIGURATION_H_

#define NET_hostname "MStarHost"

#define LITTLE_ENDIAN


#if defined(BIG_ENDIAN)

    #define htons_m(A) (A)
    #define htonl_m(A) (A)
    #define ntohs_m(A) (A)
    #define ntohl_m(A) (A)

#elif defined(LITTLE_ENDIAN)

    #define htons_m(A) ((((A) & 0xff00) >> 8) | \
                    (((A) & 0x00ff) << 8))

    #define htonl_m(A) ((((A) & 0xff000000) >> 24) | \
                    (((A) & 0x00ff0000) >> 8 ) | \
                    (((A) & 0x0000ff00) << 8 ) | \
                    (((A) & 0x000000ff) << 24))

    #define ntohs_m htons_m
    #define ntohl_m htonl_m

#else

    #error "One of BIG_ENDIAN or LITTLE_ENDIAN must be #define'd."

#endif

//==============================================================
// Network definition
//==============================================================
typedef enum
{
    BEARER_ANY_UDP,                  
    BEARER_GSM_SMS,                  
    BEARER_GSM_CSD,                  
    BEARER_GSM_GPRS,                 
    BEARER_BT,                       
    BEARER_ANY,                      
}Network_Bearer_Type_t;


#endif  /* _WINSOCK_API_CONFIGURATION_H_ */
