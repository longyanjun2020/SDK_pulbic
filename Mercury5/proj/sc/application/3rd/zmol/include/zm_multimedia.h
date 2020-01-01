#ifndef _zm_multimedia_h_
#define _zm_multimedia_h_

#include "zm_typedef.h"

typedef enum
{
	zm_audio_file=1,
	zm_audio_midi,
	zm_audio_arm,
	zm_audio_wav,
	zm_audio_pcm
}zm_audio_type;

typedef zm_void (*zm_mdi_callback)(zm_int32 result); 

/*
 * 开始震动
 */
zm_extern zm_void zm_start_shake(zm_int ms);

/*
 * 结束震动
 */
zm_extern zm_void zm_stop_shake(void);

/*
 * 开始播放声音
 */
zm_extern zm_bool zm_sound_play(zm_audio_type type, zm_uint8* ptr, zm_int len, zm_bool loop,zm_mdi_callback callback);

/*
 * 停止播放声音
 */
zm_extern zm_bool zm_sound_stop(zm_void);

/**
 * 设置音量大小。
 * @param volume 音量。
 */
zm_extern zm_void zm_set_volume(zm_int8 volume);

/**
 * 设置来电铃声。
 * @param filepath	铃声文件的完整路径。
 * @return			返回0表示设置成功，否则为错误。
 */
zm_extern zm_bool zm_set_ringtone(const zm_int8* filepath);

/**
 * 设置背景墙纸
 * @param filepath	图片文件的完整路径。
 * @return			返回0表示设置成功，否则为错误。
 */
zm_extern zm_bool zm_set_wallpaper(const zm_int8* filepath);

/**
 * 设置是否按键发出声音,进入游戏需要关闭按键声音
 */
zm_extern zm_void zm_kbd_enable_tone(zm_bool b);

/**
 * 设置按键的重复频率是否为高频率
 */
zm_extern zm_void zm_kbd_enable_high_frequency(zm_bool b);

/**
 * 录音接口,开始录音
 */
zm_extern zm_void zm_aud_start_record(zm_int8* filename,zm_mdi_callback callback);
/**
 * 停止录音
 */
zm_extern zm_int32 zm_aud_stop_record(zm_void);

/**----------------------------------------------------------------------
 * MP3播放接口
 *----------------------------------------------------------------------*/
/**
参数:
audio 指定文件名或数据Buffer 首地址
format 音频格式
size 音频数据长度,为0 则audio 传入的为文件名
返回:
int
	0 成功
	!0 失败,并标志失败信息
*/
zm_int zm_media_playsound(zm_int8*audio, zm_int format, zm_int size,zm_mdi_callback callback);

/**
说明: 停止正在播放的音频
参数:
void
返回:
int
	0 成功
	!0 失败,并标志失败信息
*/
zm_int zm_media_stopsound(zm_void);    

/**
说明: 暂停播放音频
参数:
void
返回:
int
	0 成功
	!0 失败,并标志失败信息
 */                  
zm_int zm_media_pausesound(zm_void);    

/**
说明: 恢复播放音频
参数:
void
返回:
int
	0 成功
	!0 失败,并标志失败信息
 */                  
zm_int zm_media_resumesound(zm_void);

/**
说明: 获得音频文件播放总时间
参数:
file_name 指定文件名
返回:
int
	>= 0 成功,返回总时间ms
	< 0 失败
 */
zm_int zm_media_getsoundduration(zm_int8 *file_name); 

/**
说明: 获得音频播放进度(此功能仅限于文件播放)
参数:
void
返回:
int
	>= 0 成功,返回当前进度时间ms
	< 0 失败
 */
zm_int zm_media_getsoundprogress(zm_void);    

/**
说明: 设置当前视频播放的进度
参数:
progress 需要设置的进度值ms
返回:
int
	0 成功
	!0 失败,并标志失败信息
 */
zm_int zm_media_setsoundprogress(zm_int progress);                      

#endif//_zm_multimedia_h_
