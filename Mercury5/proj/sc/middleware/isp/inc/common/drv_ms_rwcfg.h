#ifndef __RWCFG_H__
#define __RWCFG_H__

//#include "dbg_info.h"
#include "dbg_id.h"
#include "api_id.h"
#include <isp_types.h>

//============================================================================
// struct, flag, marcos
//============================================================================

#define SPEEDUP_PARSING_FILE (1)
#define SPEEDUP_LOADCFG 1

typedef void* ISP_DBGBUF_HANDLE;

typedef enum {
    eDBG_ITEM_TYPE_U8,
    eDBG_ITEM_TYPE_U16,
    eDBG_ITEM_TYPE_S16,
    eDBG_ITEM_TYPE_U32,
    eDBG_ITEM_TYPE_S32,
    eDBG_ITEM_TYPE_DOUBLE,
    eDBG_ITEM_TYPE_STRING,
    eDBG_ITEM_TYPE_U8_ARRAY,
    eDBG_ITEM_TYPE_U16_ARRAY,
    eDBG_ITEM_TYPE_S16_ARRAY,
    eDBG_ITEM_TYPE_U32_ARRAY,
    eDBG_ITEM_TYPE_S32_ARRAY,
    eDBG_ITEM_TYPE_DOUBLE_ARRAY,
    eDBG_ITEM_TYPE_U8_MATRIX,
    eDBG_ITEM_TYPE_S16_MATRIX,
    eDBG_ITEM_TYPE_U16_MATRIX,
    eDBG_ITEM_TYPE_U32_MATRIX,
    eDBG_ITEM_TYPE_S32_MATRIX,
    eDBG_ITEM_TYPE_DOUBLE_MATRIX,
    eDBG_ITEM_TYPE_MAX,
    eDBG_ITEM_TYPE_HEX = 0x20000000,
    eDBG_ITEM_TYPE_TMPVALUE = 0x40000000,
    eDBG_ITEM_TYPE_COMMAND = 0x80000000
} DBG_ITEM_TYPE;

typedef struct {
    char  pName[128];
    int         u4Tag;
    unsigned int/*DBG_ITEM_TYPE*/   eType;//for VS2015
    unsigned long   uNum; // # of units
    unsigned long   uSize;// units size
    union {
        unsigned char    bValue;
        unsigned char    uValue;
        unsigned short     u2Value;
        unsigned long     u4Value;
        double  d4Value;
    } Value;
    signed long   i4Min;
    signed long   i4Max;
    unsigned long   uBufferOffset;
    unsigned long  uItemSize;
} __attribute__((packed, aligned(1))) DBG_ITEM;

typedef struct {
    unsigned char parsed;
    unsigned char searched;
} DBG_ITEM_PARSEINFO;

typedef struct {
    unsigned long   u4Tag;
    union {
        unsigned char   bValue;
        unsigned char      uValue;
        unsigned short    u2Value;
        unsigned long     u4Value;
        double  d4Value;
    } Value;
} DBG_DATABUFFER_ITEM;


typedef struct __iq_cfg_info {
    int col;
    int row;
    int type;
    int offset;
} iq_cfg_info;

typedef struct
{
    DBG_ITEM              *pDbgItems;
    u8                    *pDbgBuf;
    u32                   u4DbgBufSize;
}dbgbuf_handle_t;

dbgbuf_handle_t strCameraInfo;

#define DBG_ITEM_ATT(name,type,num,size,def, max, min)    \
  { \
  .pName = #name, \
  .u4Tag = name, \
  .eType = type, \
  .uNum = num, \
  .uSize = size, \
  .Value.d4Value = def, \
  .i4Min = max, \
  .i4Max = min \
  }

int cfg_setcfgbyenum(ISP_DBGBUF_HANDLE hnd,DBG_TAG dbg_item_tag, void *buf);
int cfg_getcfgbyenum(ISP_DBGBUF_HANDLE hnd,DBG_TAG dbg_item_tag, void *buf);
int cfg_getcfg_info_byenum(ISP_DBGBUF_HANDLE hnd,DBG_TAG dbg_item_tag, void *buf, iq_cfg_info *info);
int getBufferData(void*buf, int x, int y, int num, DBG_ITEM_TYPE type);
int cfg_InitBinInfo(ISP_DBGBUF_HANDLE hnd,void* buffer);
int Cfg_GetDbgBufSize(ISP_DBGBUF_HANDLE hnd);
int cfg_ReleaseDBGInfo(ISP_DBGBUF_HANDLE hnd);

unsigned long cameraInitDebugBufferInfo(DBG_ITEM **pDbgItems, unsigned long* max_size);

#endif /*__UTIL_CFG_H__*/
