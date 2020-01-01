
/**
 * @file
 * NCC mms protocol config
 *
 * Config Macros of the NCC mms protocol module
 */

#ifndef __PROT_CONFIG_H__
#define __PROT_CONFIG_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* system setting config  */
#define MMS_VERSION10                                        0x90
#define MMS_VERSION11                                        0x91
#define MMS_VERSION12                                        0x92
#define MMS_SENDCONF_RECEIVEBUF_SIZE                         1024
#define MMS_NOTIFYRESP_IND_SIZE                              100
#define MMS_ACKNOWLEDGE_IND_SIZE                             100
#define MMS_FORWARD_REQ_SIZE                                 1024
#define MMS_BODY_ADDED_LENGTH                                700
//#define MMS_EACH_ELEMENT_HEADER_LEN                          70
#define MMS_EACH_ELEMENT_HEADER_LEN                          300
#define MMS_BOXSTORE_REQ_SIZE                                512
#define MMS_BOXVIEW_REQ_SIZE                                 1024
#define MMS_BOXUPLOAD_REQ_SIZE                               512
#define MMS_BOXUPDELETE_REQ_SIZE                             512

/* config whether MMS support multiple receiverS, recommended 20 totals */
#define MMS_SUPPORT_MULTIPLE_RCVER

#ifdef __cplusplus
}
#endif

#endif /* __PROT_CONFIG_H__ */
