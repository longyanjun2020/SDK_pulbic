/****************************************************************************/
/*  File    : winsock_db.h                                                  */
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

#ifndef _WINSOCK_API_STATIC_DB_H_
#define _WINSOCK_API_STATIC_DB_H_

typedef struct __Socket_Service_DB
{
    char     *s_name;           /* official service name */
    short   s_port;                 /* port # */
    char     *s_proto;          /* protocol to use */
    char     *s_aliases;  /* alias list */
} Socket_Service_DB;

typedef struct __Socket_Protocol_DB
{
    char     *p_name;           /* official protocol name */
    short   p_proto;                /* protocol # */
    char     *p_aliases;  /* alias list */
} Socket_Protocol_DB;

typedef struct __Socket_Hosts_DB
{
    char     *h_name;           /* official name of host */
    short   h_addrtype;         /* host address type */
    char     *h_aliases;        /* alias list */
    char     *h_address;           /* list of addresses */
    short   h_length;           /* length of address */
} Socket_Hosts_DB;

#endif  /* _WINSOCK_API_STATIC_DB_H_ */
