#ifndef _MDL_VT_COMMON_H_
#define _MDL_VT_COMMON_H_

#include "vm_msgof.hc"

//#define VT_TEST 0

#define VT_LAUNCH_AVP 1
#define VT_LAUNCH_VDR 1
#define VT_LAUNCH_PREVIEW 1
#define VT_RESPONSE_TO_COMMANDER 1
#define VT_USE_HW_M4VD 0

#define VT_NO_USERDATA 0

#define VT_PIC_WIDTH  176
#define VT_PIC_HEIGHT 144
#define VT_PIC_BUF_SIZE (VT_PIC_WIDTH*VT_PIC_HEIGHT*2)

#define VT_DUMMY_PREVIEW_WIDTH 4
#define VT_DUMMY_PREVIEW_HEIGHT 4

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum {
#include "mdl_vt_common_message_define__.hi"
} mdl_vt_msg_et;

#include "mdl_vt_internal.h"
#include "mdl_vt_state.h"

#define VT_SLEEP(ms) MsSleep(RTK_MS_TO_TICK(ms))
#define VTM_GET_LOWBYTE(a)   (u32)(((u64)a)&0xFFFFFFFF)
#define VTM_GET_HIGHBYTE(a)  (u32)(((u64)(a)>>32)&0xFFFFFFFF)

typedef enum {
    VT_RANDOM_TEST_ALL = 1,
    VT_RANDOM_TEST_SCREEN,
    VT_RANDOM_TEST_RESERVED,
} random_test_et;

typedef struct {
   unsigned char loopback_mode;
   unsigned char log_file;
   random_test_et random;
} vt_test_param_t;

typedef enum {
    VT_ROTATION_0 = 0,
    VT_ROTATION_90,
    VT_ROTATION_180,
    VT_ROTATION_270,
    VT_ROTATION_360,
} vt_rotation_et;

typedef struct {
    vt_state_t cur_state;
    vt_test_param_t test;
    unsigned char test_started;
    void *PreviewSetting;
    vt_rotation_et local_win_rotation;
    vt_rotation_et remote_win_rotation;
    unsigned char *DispBuf[2];
    unsigned char *AudTxDmaBuf;
    unsigned char *RemotePicBuf;
    unsigned char *LocalPicBuf;
    unsigned char *PreviewDummyBuf;
    long long rec_time; /* sec */
} vt_t;

int mdl_vt_printf(int level, const char *pFmt, ...);
long long mdl_vt_get_current_time(void);
void mdl_vt_reset_timer(void);
int mdl_vt_init_logging(void);
int mdl_vt_finalize_logging(void);


#endif
