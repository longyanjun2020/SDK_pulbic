#ifndef __NEMOMP_MEDIA_CTRL_H__
#define __NEMOMP_MEDIA_CTRL_H__

typedef struct _MetaDataCtrl {
	nm_int32 length;
	nm_wchar metaValue[255];
} nm_metadata_ctrl;

////#ifdef MMAPI_MIDICTRL_SUPPORT
extern nm_bool nemomp_media_midi_device_open(int mma_type, int java_player);

extern int nemomp_media_midi_get_bank_list_size(int java_player, nm_bool custom);
extern int* nemomp_media_midi_get_bank_list(int java_player, nm_bool custom);

extern int nemomp_media_midi_get_channel_volume(int java_player, int channel);
extern void nemomp_media_midi_set_channel_volume(int java_player, int channel, int volume);

extern nm_char* nemomp_media_midi_get_key_name(int java_player, int bank, int prog, int key, int* len);

extern int nemomp_media_midi_get_program_size(int java_player, int channel);
extern int* nemomp_media_midi_get_program(int java_player, int channel);

extern void nemomp_media_midi_set_program(int java_player, int channel, int bank, int program);

extern int nemomp_media_midi_get_program_list_size(int java_player, int bank);
extern int* nemomp_media_midi_get_program_list(int java_player, int bank);

extern nm_char* nemomp_media_midi_get_program_name(int java_player, int bank, int program, int* len);

extern int nemomp_media_midi_long_event(int java_player, nm_char* data, int offset, int length);

extern void nemomp_media_midi_short_event(int java_player, int type, int data1, int data2);
////#endif

////#ifdef MMAPI_RECORD_SUPPORT
extern int nemomp_media_record_start(int java_player);

extern int nemomp_media_record_stop(int java_player);

extern int nemomp_media_record_commit(int java_player);

extern int nemomp_media_record_reset(int java_player);

extern void nemomp_media_record_set_location(int java_player, nm_wchar* filename, int namelen);

extern nm_wchar* nemomp_media_record_get_location(int java_player, int* namelen);

extern int nemomp_media_record_set_limit(int java_player, int size);

////#endif

#endif /* __NEMOMP_MEDIA_H__ */
