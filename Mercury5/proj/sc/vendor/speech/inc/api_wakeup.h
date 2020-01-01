/**
 * Project  : AIWakeup.v1.0.7
 * FileName : api/api_wakeup.h
 *
 * COPYRIGHT (C) 2015-2016, AISpeech Ltd.. All rights reserved.
 */
#ifndef __AISPEECH__API_WAKEUP_H__
#define __AISPEECH__API_WAKEUP_H__
typedef enum wakeup_status {
    WAKEUP_STATUS_ERROR = -1,     // 閸炪倝鍟嬮崙铏瑰箛瀵倸鐖�
    WAKEUP_STATUS_WAIT,           // 缁涘绶熼崬銈夊晪
    WAKEUP_STATUS_WOKEN,          // 瀹告彃鏁滈柋锟�
    WAKEUP_STATUS_WOKEN_BOUNDARY, // 瑜版捇鍘ょ純鐣妔e_output_boundary=1閺冭绱濇潏鎾冲毉閸炪倝鍟嬬拠宥堢珶閻ｅ奔淇婇幁锟�
    WAKEUP_STATUS_RESTART
} wakeup_status_t;

typedef struct wakeup wakeup_t;

/**
 * 閸ョ偠鐨熼崙鑺ユ殶鐎规矮绠�
 *
 * @param user_data: 閻€劍鍩涙导鐘插弳閻ㄥ嫭鏆熼幑顔剧波閺嬪嫭瀵氶柦锟�
 * @param status: 閸炪倝鍟嬮悩鑸碉拷锟�
 * @param json: 鏉╂柨娲栭崬銈夊晪濡�虫健閻ㄥ嫪淇婇幁锟�
 * @param bytes: JSON娑撹尙娈戠�涙濡弫锟�
 */
typedef int (*wakeup_handler_t)(void *user_data, wakeup_status_t status, char *json, int bytes);
//typedef void (*_handler_print)( char* szFormat, ... );

#ifdef __cplusplus
extern "C" {
#endif

//#pragma import(__use_no_semihosting_swi)
/**
 * 閸掓稑缂撻崬銈夊晪濡�虫健閻ㄥ嫬鐤勬笟锟�
 *
 * @param fn: 閸炪倝鍟嬬挧鍕爱鐠侯垰绶為妴锟�
 * @param json: 娑擃亝锟窖冨鐎规艾鍩楅弮璁圭礉濮濄倖鏋冩禒鎯扮熅瀵板嫪璐熼崝鐘茬槕閸氬海娈戦張顒�婀撮柅姘辨暏閸炪倝鍟嬮惃鍕帳缂冾喕淇婇幁顖ょ礉閸愬懎顔愮拠锕侇潌[娑擃亝锟窖冨鐎规艾鍩楅柊宥囩枂閺嶇厧绱
 */
wakeup_t *wakeup_new(const char *bin_fn, const char *json);

/**
 * 濞撳懐鎮婇崬銈夊晪鐎圭偘绶ラ獮鍫曞櫞閺�鎯у敶鐎涳拷
 *
 * @param w: 閸炪倝鍟嬪Ο鈥虫健閻ㄥ埇nstance
 */
void wakeup_delete(wakeup_t *w);

/**
 * 闁插秶鐤嗛崬銈夊晪濡�虫健
 *
 * @param w: 閸炪倝鍟嬪Ο鈥虫健閻ㄥ埇ntance
 */
void wakeup_reset(wakeup_t *w);

/**
 * 閸氼垰濮╅崬銈夊晪濡拷閺岋拷
 *
 * @param w: 閸炪倝鍟嬪Ο鈥虫健閻ㄥ埇nstance
 * @param env: 閼奉亜鐣炬稊澶婂棘閺侊拷
 * @param bytes: 閼奉亜鐣炬稊澶婂棘閺佹壆娈戦梹鍨
 */
int wakeup_start(wakeup_t *w, char *env, int bytes);

/**
 * 閹绘劒绶甸棅鎶筋暥閺佺増宓佺紒娆忔暅闁辨帗膩閸ф绱濋崚銈嗘焽閸炪倝鍟嬮悩鑸碉拷锟�
 *
 * @param w: 閸炪倝鍟嬪Ο鈥虫健閻ㄥ埇nstance
 * @param data: 闂婃娊顣堕弫鐗堝祦
 * @param bytes: 閺佺増宓佺�涙濡弫锟�
 *
 * @return 閸炪倝鍟嬮悩鑸碉拷锟�
 */
wakeup_status_t wakeup_feed(wakeup_t *w, char *data, int bytes);

/**
 * 濞撳懐鎮婇崬銈夊晪濡�虫健閻ㄥ垻ache閸欏﹦濮搁幀锟�
 *
 * @param w: 閸炪倝鍟嬪Ο鈥虫健閻ㄥ埇nstance
 */
wakeup_status_t wakeup_end(wakeup_t *w);

/**
 * 濞夈劌鍞介悩鑸碉拷浣烘畱閸ョ偠鐨熼崙鑺ユ殶
 *
 * @param w: 閸炪倝鍟嬪Ο鈥虫健閻ㄥ埇nstance
 * @param user_data: 閻€劍鍩涢惃鍕殶閹诡喚绮ㄩ弸锟�
 * @param func: 濞夈劌鍞介惃鍕毐閺侊拷
 */
void wakeup_register_handler(wakeup_t *w, void *user_data, wakeup_handler_t func);

#ifdef __cplusplus
}
#endif

#endif //__AISPEECH__API_WAKEUP_H__
