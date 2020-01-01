
#ifndef __FMS_BUF_H__
#define __FMS_BUF_H__

#ifdef __M18_MCP_SUPPORT__
extern s32 fms_BufInit(u32 addr, u32 size);
extern s32 fms_BufWrite(u32 dst, u32 data_size, const void *data);
extern s32 fms_BufFlush(void);
extern s32 fms_BufIntersect(u32 *addr, u32 *size);
extern s32 fms_BufGetChecksum(u32 addr, u32 size, u32 *checksum);
extern void fms_BufVerifyAfterFlush(u32);
extern s32 fms_BufAddrInBuf(u32);

#endif // __M18_MCP_SUPPORT__

#endif // __FMS_BUF_H__

