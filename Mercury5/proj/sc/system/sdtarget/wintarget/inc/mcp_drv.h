
#ifndef __MCP_DRV_H__
#define __MCP_DRV_H__

#define M18_PAGE_SIZE   (1024)
#define M18_PAGE_MASK   (M18_PAGE_SIZE - 1)

#ifdef __M18_MCP_SUPPORT__
extern u32 mcp_IsM18(void);
#else
#define mcp_IsM18()     (0)
#endif

#endif

