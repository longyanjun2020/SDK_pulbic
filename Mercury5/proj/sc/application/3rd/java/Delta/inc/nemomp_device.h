#ifndef __NEMOMP_DEVICE_H__
#define __NEMOMP_DEVICE_H__

typedef enum
{
    NM_ALERT_INFO = 1,
    NM_ALERT_WARNING,
    NM_ALERT_ERROR,
    NM_ALERT_ALARM,
    NM_ALERT_CONFIRMATION
} nm_alert_type_enum;

extern nm_bool nemomp_play_alert_sound(nm_int32 alertType);
extern nm_bool nemomp_start_vibrate(int duration);
extern nm_bool nemomp_stop_vibrate(void);
extern nm_bool nemomp_set_backlight(nm_bool mode);
extern int nemomp_run_phone_call(char *number);
extern int nemomp_run_wap_browser(char *url);
extern int nemomp_get_audio_volume_level(void);
extern void nemomp_set_audio_volume_level(int level);

// 20090218: Added
extern nm_char* nemomp_get_mime_type(nm_char* url);

#endif /* __NEMOMP_DEVICE_H__ */
