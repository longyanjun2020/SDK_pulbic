
#ifndef __IFLAYER_DLPAGE_H__
#define __IFLAYER_DLPAGE_H__

#include <ncc_types.h>

#define MAX_DOWNLOAD_MEDIA_SIZE (510*1024)
/**
* query to download web page
*   \return
*/
int32_t fnDB_DLCheckPage(void);

/**
* parse a html page by memory
*   \param  htmlBuf  memory pointer of html page
*/
void fnDB_ParseAHtmlPage(int8_t * htmlBuf);

#endif
