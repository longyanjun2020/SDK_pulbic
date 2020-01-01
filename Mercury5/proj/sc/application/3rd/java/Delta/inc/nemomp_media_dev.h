#ifndef __NEMOMP_CAMERA_H__
#define __NEMOMP_CAMERA_H__

extern nm_bool nemomp_media_camera_create(int mma_type, int java_player,int x, int y, int w, int h);
extern nm_bool nemomp_media_camera_play(int mma_type, int java_player);
extern nm_bool nemomp_media_camera_pause(int mma_type, int java_player);
extern nm_bool nemomp_media_camera_stop(int mma_type, int java_player);
extern void nemomp_media_camera_close(int mma_type, int java_player);
extern int nemomp_media_camera_get_duration(int mma_type, int java_player);
extern int nemomp_media_camera_set_media_time(int mma_type, int java_player, int now);
extern int nemomp_media_camera_get_media_time(int mma_type, int java_player);
extern int nemomp_media_camera_set_volume(int mma_type, int java_player, int volumne);
extern nm_bool nemomp_media_camera_resume(int mma_type, int java_player);
extern char* nemomp_media_camera_getsnapshot(int mma_type, int java_player,  nm_char* imgType, int count, int *len);
extern nm_bool nemomp_media_camera_getframe(int mma_type, int java_player, nm_char* imgType, int count, int *len);
extern int nemomp_media_camera_set_displaysize(int mma_type, int java_player,int x,int y, int w, int h);
extern int nemomp_media_camera_captureStartVideo(int cameraPlayer);
extern int nemomp_media_camera_captureStopVideo(int cameraPlayer);
extern int nemomp_media_camera_captureEndVideo(int cameraPlayer);
extern int nemomp_media_camera_capturePauseVideo(int cameraPlayer);
extern nm_bool nemomp_media_camera_callback(nm_bool setCalbak);

extern nm_bool nemomp_media_micphone_create(int mma_type, int java_player);
extern nm_bool nemomp_media_micphone_play(int mma_type, int java_player);
extern nm_bool nemomp_media_micphone_resume(int mma_type, int java_player);
extern nm_bool nemomp_media_micphone_pause(int mma_type, int java_player);
extern nm_bool nemomp_media_micphone_stop(int mma_type, int java_player);
extern void nemomp_media_micphone_close(int mma_type, int java_player);

#endif /* __NEMOMP_CAMERA_H__ */

