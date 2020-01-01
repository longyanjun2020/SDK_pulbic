#ifndef __NEMOMP_MEDIA_VIDEO_H__
#define __NEMOMP_MEDIA_VIDEO_H__

#include "nemomp_media_ctrl.h"

extern nm_bool nemomp_media_video_create(int mma_type, int java_player,nm_char* data, nm_wchar* filename, int len, int x, int y, int w, int h);
extern void nemomp_media_video_close(int mma_type, int java_player);
extern nm_bool nemomp_media_video_play(int mma_type, int java_player);
extern nm_bool nemomp_media_video_resume(int mma_type, int java_player);
extern nm_bool nemomp_media_video_pause(int mma_type, int java_player);
extern nm_bool nemomp_media_video_stop(int mma_type, int java_player);
extern int nemomp_media_video_set_displaysize(int mma_type, int java_player,int x,int y, int w, int h);
extern int nemomp_media_video_get_duration(int mma_type, int java_player);
extern int nemomp_media_video_set_media_time(int mma_type, int java_player, int now);
extern int nemomp_media_video_get_media_time(int mma_type, int java_player);
extern int nemomp_media_video_set_volume(int mma_type, int java_player, int volumne);
extern char* nemomp_media_video_getsnapshot(int mma_type, int java_player,  nm_char* imgType, int count, int *len);
extern nm_bool nemomp_media_video_getframe(int mma_type, int java_player, nm_char* imgType, int count, int *len);

extern nm_bool nemomp_media_video_get_info(int mma_type, int java_player,nm_char* data, nm_wchar* filename, int len, nm_metadata_ctrl* meta);

/*
extern int nemomp_media_video_captureStartVideo(int java_player);
extern int nemomp_media_video_captureStopVideo(int java_player);
extern int nemomp_media_video_captureEndVideo(int java_player);
extern int nemomp_media_video_capturePauseVideo(int java_player);
extern nm_bool nemomp_media_video_callback(nm_bool setCalbak);
*/
#endif /* __NEMOMP_MEDIA_VIDEO_H__ */

