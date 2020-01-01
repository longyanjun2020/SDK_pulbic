/* ut_playlist_if.h */
#ifndef __UT_PLAYLIST_IF_H__
#define __UT_PLAYLIST_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getPlaylist_IF_UT(void);
int   noPlaylist_IF_UT(void);
void  releasePlaylist_IF_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_PLAYLIST_IF_H__ */
