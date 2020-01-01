/**
* @file lwIP.h
* @brief A brief file description.
* @details
*     A more elaborated file description.
* @author Wang Mengyin
* @date  2010Jul19 15:54:55
* @note
*               Copyright 2010 Wang Mengyin.ALL RIGHTS RESERVED.
*                            http://tigerwang202.blogbus.com
*    This software is provided under license and contains proprietary and
* confidential material which is the property of Company Name tech.
*/


#ifndef __LW_IP_H
#define __LW_IP_H

#ifdef __cplusplus
extern "C" { /* Make sure we have C-declarations in C++ programs */
#endif


/* Includes ------------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/

/* ********/



void      LwIP_Init(bool static_ip);


void      LwIP_DhcpStart(bool static_ip);
void      LwIP_DhcpStop(void);




#ifdef __cplusplus
}
#endif


#endif /* #ifndef __LW_IP_H */
/*-- File end --*/

