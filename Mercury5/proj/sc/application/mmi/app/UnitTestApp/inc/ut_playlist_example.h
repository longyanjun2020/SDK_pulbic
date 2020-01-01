/* ut_playlist_example.h */
#ifndef __UT_PLAYLIST_EXAMPLE_H__
#define __UT_PLAYLIST_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetPlaylist_Example(void);
s32   NumPlaylist_Example(void);
void  ReleasePlaylist_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_PLAYLIST_EXAMPLE_H__ */
