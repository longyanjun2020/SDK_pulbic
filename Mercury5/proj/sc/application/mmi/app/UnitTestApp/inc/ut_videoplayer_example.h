/* ut_videoplayer_example.h */
#ifndef __UT_VIDEOPLAYER_EXAMPLE_H__
#define __UT_VIDEOPLAYER_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetVideoPlayer_Example(void);
s32  NumVideoPlayer_Example(void);
void  ReleaseVideoPlayer_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_VIDEOPLAYER_EXAMPLE_H__ */
