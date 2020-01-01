#ifndef _H263_SHARED_DATA_H_
#define _H263_SHARED_DATA_H_

#include "swvenc_deftypes.h"

// extern "C"
// {
extern uint8 * cur;
extern uint8 * pre;    // IMAGESIZEY * IMAGESIZEX Array
                       // First dimension is Y, second dimension is X
                       // for purpose of row major.
extern int IMAGESIZEX;
extern int IMAGESIZEY;
extern int TOTALPIXEL;
extern int Cx_IMAGESIZEX;
extern int Cx_IMAGESIZEY;
extern int BLOCKNUMX;
extern int BLOCKNUMY;
extern int TOTALBLOCK;

// global var to store the Motion Vector of every block.
extern point_t* MVArray;

extern int16 *gpDctInBuf;
extern int16 *gpDctOutBuf;

extern int16 *gpDctInBuf_new[6];
extern int16 *gpDctOutBuf_new[6];
// };


#endif
