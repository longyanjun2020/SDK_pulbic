#ifndef H263_BLOCK_H
#define H263_BLOCK_H

err_type h263IntraBlock(M4V_HANDLE *hp, short * block, int block_num, int coded);
err_type h263InterBlock(M4V_HANDLE *hp, short * block, int block_num, int coded);

#endif // H263_BLOCK_H
