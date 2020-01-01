#ifndef H263HEADER_H
#define H263HEADER_H

int h263_getshvhdr(M4V_HANDLE *hp);
err_type h263_getgobhdr(M4V_HANDLE *hp);
uchar *h263ParseStartCodes(M4V_HANDLE *hp, uchar *buf, int len);

#endif
