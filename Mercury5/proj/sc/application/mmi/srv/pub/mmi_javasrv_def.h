/**
 * @file mmi_javasrv_def.h
 *
 * JAVASRV structure definition
 *
 * @version $Id$
 */
#ifndef __MMI_JAVASRV_DEF_H__
#define __MMI_JAVASRV_DEF_H__

#include "mmi_if_java.h"
#include "mmi_req_java.h"

enum
{
    JAVASRV_MASK_AMS = 1 << 0
   ,JAVASRV_MASK_HTTP = 1 << 1
   ,JAVASRV_MASK_ALLMask = -1
} ;

typedef s32 JAVASRV_NOTIFY_MASK_e;

enum
{
   JAVASRV_STORAGE_NAND	= 0,
   JAVASRV_STORAGE_NOR,
   JAVASRV_STORAGE_MEMCARD,
   JAVASRV_STORAGE_MEMCARD2,
   JAVASRV_STORAGE_PREINSTALL,
   JAVASRV_STORAGE_NUM,
};
typedef u8 JAVASRV_STORAGE_e;

#endif /* __MMI_JAVASRV_DEF_H__ */
