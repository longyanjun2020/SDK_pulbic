#ifndef __NEMOMP_EVENT_H__
#define __NEMOMP_EVENT_H__

#define SUPPORT_KET_REPEATED_EVENT	1 // 20091210: Added

typedef enum
{
    NM_KEY_0 = 0,
    NM_KEY_1,
    NM_KEY_2,
    NM_KEY_3,
    NM_KEY_4,
    NM_KEY_5,
    NM_KEY_6,
    NM_KEY_7,
    NM_KEY_8,
    NM_KEY_9,
    NM_KEY_LSK,
    NM_KEY_RSK,
    NM_KEY_CSK,
    NM_KEY_UP_ARROW,
    NM_KEY_DOWN_ARROW,
    NM_KEY_LEFT_ARROW,
    NM_KEY_RIGHT_ARROW,
    NM_KEY_SEND,
    NM_KEY_END,
    NM_KEY_CLEAR,
    NM_KEY_STAR,
    NM_KEY_POUND,
    NM_KEY_VOL_UP,
    NM_KEY_VOL_DOWN,
    NM_KEY_CAMERA,
    NM_KEY_ENTER,
    NM_KEY_CODE_TOTAL
} nm_key_code_enum;

// 20091210: Changed
typedef enum {
    NM_EVENT_KEY_PRESSED=1,
    NM_EVENT_KEY_RELEASED=2,
    NM_EVENT_KEY_REPEATED=3,
    NM_EVENT_KEY_TYPE_TOTAL
} nm_key_event_enum;

typedef enum
{
    NM_EVENT_PEN_DOWN,
    NM_EVENT_PEN_UP,
    NM_EVENT_PEN_MOVE,
    NM_EVENT_PEN_TYPE_TOTAL
} nm_pen_event_enum;

typedef struct {
    nm_int32 type;
    nm_int32 code;
} nm_key_event;

typedef enum
{
    NM_MEDIA_EVENT_END_OF_MEDIA,
    NM_MEDIA_EVENT_STOPPED_AT_TIME,
} nm_media_event_type_enum;

// 20081119: Added
typedef enum
{
    NM_NOT_PAUSED_TYPE,
    NM_PAUSE_ONLY_TYPE,
    NM_PAUSE_NOTIFY_TYPE,
    NM_PAUSE_TYPE_TOTAL
} nm_pause_type_enum;

extern nm_pause_type_enum current_pause_type;
extern nm_bool pauseJavaTask;

extern nm_bool nemomp_event_check_stop(void);
extern nm_bool nemomp_peek_message(int* pMsg, int* pArg1, int* pArg2);
extern void nemomp_event_media_post(nm_media_event_type_enum evt_type, nm_int32 player_id, nm_int64 player_time);

extern void nemomp_event_get_properties(nm_int32 *hasPointerEvents, nm_int32 *hasPointerMotionEvents, nm_int32 *hasKeyRepeatEvents);
extern void nemomp_event_external_check(void);

extern void nemomp_event_init_vm(void);
extern void nemomp_event_pause_vm(nm_pause_type_enum pause_type);
extern void nemomp_event_resume_vm(void);
extern void nemomp_event_stop_vm(void);

#endif /* __NEMOMP_EVENT_H__ */
