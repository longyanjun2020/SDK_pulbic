#ifndef __NEMOMP_MMI_H__
#define __NEMOMP_MMI_H__

#include "java_head.h"
#include "nemomp.h"
#include "nemomp_jam_service.h"
#include "nemomp_jam.h"
#include "java_ams.h"
#include "nemomp.h"

#include "ven_os.h"
#include "ven_dbg.h"
#include "ven_codec.h"
#include "java_ams_itf.h"


//-----------SJH ADDed
#ifndef PLATFORM_MALLOC

extern long javaspace_first[];
extern long javaspace_second[];
#endif /* !PLATFORM_MALLOC */

extern void init_javaspace(void);
extern void release_javaspace(void);

extern void show_suites_list_sjh(void);
extern void print_one_suite_sjh(int suiteIndex, nm_suite_detail  *mids_info_ptr);
extern void print_one_midlet_sjh(int midletIndex, nm_midlet_info *mid_ptr);
//-----------SJH ADDed




typedef enum NM_IME_TYPE_ENUM
{
    NM_IME_TYPE_NUMERIC,
    NM_IME_TYPE_PHONE_NUMBER,
    NM_IME_TYPE_ALPHANUMERIC_LOWERCASE,
    NM_IME_TYPE_NUMERIC_PASSWORD,
    NM_IME_TYPE_ALPHANUMERIC_PASSWORD,
    NM_IME_TYPE_DECIMAL_NUMERIC
} nm_ime_type_enum;

// 20081229: Added; 20081231: Changed
typedef enum
{
    NM_ERROR_START = 6000,
	NM_ERROR_OUT_OF_MEMORY = NM_ERROR_START,
	NM_ERROR_CLASS_NOT_FOUND = 6001,
	NM_ERROR_CLASS_NOT_FOUND_BEFORE_LAUNCH = 6002,
	NM_ERROR_UNDEFINED_FAILURE = 6999,
} nm_vm_error_code_enum;

extern void nemomp_mmi_run_editor(nm_uint16 *text_buf, nm_int32 text_buf_length, nm_ime_type_enum input_type);

extern void nemomp_mmi_editor_callback(nm_bool result, int text_len);

extern nm_wchar *nemomp_jam_get_customize_string_by_id(nm_int32 jamMsgID);

extern void nemomp_mmi_transfer_suite_icon_data(nm_uint8* icon, nm_int32 icon_len,
						   nm_int32 width, nm_int32 height);

extern nm_char* nemomp_jam_get_install_dir(nm_int32 requestSize); // 20081210: Changed

extern nm_int32 nemomp_jam_request_http_and_save_to_file(nm_int32 total_jar_size, nm_wchar* url, nm_wchar* file_name,
						nm_wchar* midlet_name, nm_int32 name_len);
extern void nemomp_jam_respond_download_status(nm_int32 error_code, nm_int32 downloadSize);
extern nm_int32 nemomp_jam_request_http_post(nm_wchar *url, nm_char *post_message, nm_int32 *server_response_code);


extern nm_bool nemomp_jam_install_user_confirm(nm_wchar *confirmMsg);
extern nm_bool nemomp_jam_install_get_rms_confirm(void);
extern nm_bool nemomp_jam_delete_confirm(nm_wchar *suiteInfoMsg);
extern void nemomp_jam_update_confirm(nm_bool success, nm_int32 jamMsgID);
extern void nemomp_jam_install_confirm(nm_bool success, nm_int32 jamMsgID);
extern nm_bool nemomp_jam_get_permission_confirm(nm_int32 jamMsgID);

extern void nemomp_jam_internal_error_confirm(nm_int32 error_code);
extern void nemomp_jam_install_set_progress(nm_uint32 value);
extern int nemomp_ams_installMidletSuite(u16 *jadPath, u16 *jarPath, int KeepRMS); //SJH 20081125


extern nm_int32 nemomp_jam_check_event(void); // 20081117 Added

extern void nemomp_error_alert_user(nm_int32 jamMsgID, nm_bool needStopVM); // 20081229: Added; 20081231: Changed

extern jPxy_SendInstallCnf(u16* jadPath, u16* jarPath, int KeepRMS);
extern int java_jam_request_http_post(u16 *u16Http, char *post_message, int *server_response_code);

#endif /* __NEMOMP_TIME_H__ */
