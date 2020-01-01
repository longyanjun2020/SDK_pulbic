
//#include "audiotypedef.h"

#ifndef _AUDIODRC_API_H_
#define _AUDIODRC_API_H_

typedef struct audiodrc_config_t
{
    short   att_idx, rel_idx;
    short   compr_x_db[4];
    short   compr_y_db[4];
    unsigned short   bEn;
}
audiodrc_config_t;

extern void* audiodrc_initialise    (void* audiodrc, int*   length);
extern int   audiodrc_configure     (void* audiodrc, void*  config);
extern int   audiodrc_process       (void* audiodrc, short* sample, unsigned int framsize);
extern int   audiodrc_terminate     (void* audiodrc);
short dBtoLinearGain(short dB);

#endif/*_AUDIODRC_API_H_*/
