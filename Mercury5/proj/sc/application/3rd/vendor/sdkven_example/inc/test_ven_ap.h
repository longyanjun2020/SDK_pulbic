#ifndef __VEN__TEST_AP_DEFINE_H__
#define __VEN__TEST_AP_DEFINE_H__

/**
 *
 * @file    test_ven_ap.h
 * @brief   This file defines the test cases for ap interface.
 *
 * @author  Alison.Chen
 * @version $Id: test_ven_ap.h 45468 2009-11-13 05:13:00Z Mobile_CM $
 *
 */

#include "ven_file.h"
#include "ven_msg.h"
#include "ven_cc.h"
#include "ven_phb.h"
#include "ven_editor.h"
#include "ven_wap.h"

enum{
    AP_CC,
    AP_SMS,
    AP_SMSEX,
    AP_FILE_BROWSER,
    AP_PHB_BROWSER,
    AP_PLAY_VIDEO,
    AP_EDIT_EX,
	AP_EDIT_DATE,
	AP_EDIT_TIME,
    AP_PHB_ADD_CONTACT,
    AP_PHB_WRITE_CONTACT,
    AP_PHB_MWP_SEARCH,
    AP_PHB_FIND_FIRST_CONTACT,
    AP_PHB_FIND_NEXT_CONTACT,
    AP_PHB_DELETE_CONTACT,
    AP_PHB_MODIFY_CONTACT,
    AP_PHB_GET_MEM_STATUS,
    AP_PHB_NUMBER_FUZZY_SEARCH,
    AP_MSG_EDITOR,
    AP_WAP_OPEN_BROWSER,
    AP_CC_GET_CALL_ID,
    AP_CC_GET_CALL_ID_AND_RELEASE_CALL,
    AP_FILE_SELECT_FOLDER,
};

typedef struct{
    u8 APType;
    u32 Data1;
    u32 Data2;
}ven_ap_cb_data_t;

#ifndef __SDK_API_WAP_MMS_ONLY__

/***********************************************************************************/
/*		Editor																																			 */
/***********************************************************************************/
void ms_ven_editor_test_case_for_alpha_ucs2_text(s32 nHandle);
void ms_ven_editor_test_case_for_digital_ucs2_text(s32 nHandle);
void ms_ven_editor_test_case_for_all_ucs2_text(s32 nHandle);
void ms_ven_editor_test_case_for_format_ucs2_text(s32 nHandle);
void ms_ven_editor_test_case_for_alpha_utf8_text(s32 nHandle);
void ms_ven_editor_test_case_for_all_utf8_text(s32 nHandle);
void ms_ven_editor_test_case_for_alpha_ucs2_pswd(s32 nHandle);
void ms_ven_editor_test_case_for_digital_ucs2_pswd(s32 nHandle);
void ms_ven_editor_test_case_for_dialing_ucs2_text(s32 nHandle);
void ms_ven_editor_test_case_for_rate_ucs2_text(s32 nHandle);
void ms_ven_editor_test_case_for_numeric_ucs2_text(s32 nHandle);

void ms_ven_editor_test_case_for_sync_alpha_ucs2_text(s32 nHandle, u8 *outStr);
void ms_ven_editor_test_case_for_sync_digital_ucs2_text(s32 nHandle, u8 *outStr);
void ms_ven_editor_test_case_for_sync_all_ucs2_text(s32 nHandle, u8 *outStr);
void ms_ven_editor_test_case_for_sync_format_ucs2_text(s32 nHandle, u8 *outStr);
void ms_ven_editor_test_case_for_sync_alpha_utf8_text(s32 nHandle, u8 *outStr);
void ms_ven_editor_test_case_for_sync_all_utf8_text(s32 nHandle, u8 *outStr);
void ms_ven_editor_test_case_for_sync_alpha_ucs2_pswd(s32 nHandle, u8 *outStr);
void ms_ven_editor_test_case_for_sync_digital_ucs2_pswd(s32 nHandle, u8 *outStr);
void ms_ven_editor_test_case_for_sync_dialing_ucs2_text(s32 nHandle, u8* outStr);
void ms_ven_editor_test_case_for_sync_rate_ucs2_text(s32 nHandle, u8* outStr);
void ms_ven_editor_test_case_for_sync_numeric_ucs2_text(s32 nHandle, u8* outStr);


void ms_ven_editor_test_case_for_alpha_asc_ucs2_text(s32 nHandle);
void ms_ven_editor_test_case_for_digital_asc_ucs2_text(s32 nHandle);
void ms_ven_editor_test_case_for_all_asc_ucs2_text(s32 nHandle);
void ms_ven_editor_test_case_for_format_asc_ucs2_text(s32 nHandle);

void ms_ven_editor_test_case_for_sync_alpha_asc_ucs2_text(s32 nHandle, u8* outStr);
void ms_ven_editor_test_case_for_sync_digital_asc_ucs2_text(s32 nHandle, u8* outStr);
void ms_ven_editor_test_case_for_sync_all_asc_ucs2_text(s32 nHandle, u8* outStr);
void ms_ven_editor_test_case_for_sync_format_asc_ucs2_text(s32 nHandle, u8* outStr);

void ms_ven_date_editor_test_case_20220101(s32 ven_handle);
void ms_ven_time_editor_test_case_203040(s32 nHandle);
/***********************************************************************************/
/*		phb browse																																	 */
/***********************************************************************************/
void ms_ven_phb_test_case_browse_phone_single_select(s32 nHandle);
void ms_ven_phb_test_case_browse_phone_multi_select(s32 nHandle);
void ms_ven_phb_test_case_browse_email_single_select(s32 nHandle);
void ms_ven_phb_test_case_browse_email_multi_select(s32 nHandle);

void ms_ven_phb_test_case_browse_phone_sync_single_select(s32 nHandle, u8 *outStr);
void ms_ven_phb_test_case_browse_phone_sync_multi_select(s32 nHandle, u8 *outStr);
void ms_ven_phb_test_case_browse_email_sync_single_select(s32 nHandle, u8 *outStr);
void ms_ven_phb_test_case_browse_email_sync_multi_select(s32 nHandle, u8 *outStr);

ven_phb_ret_t ms_ven_phb_test_case_add_contact_sync(s32 nHandle, u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_add_contact_async(s32 nHandle, u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_write_contact_sync(s32 nHandle, u8 *outStr, ven_phb_phonebook_type_t phbBookType);
ven_phb_ret_t ms_ven_phb_test_case_write_contact_async(s32 nHandle, u8 *outStr, ven_phb_phonebook_type_t phbBookType);
ven_phb_ret_t ms_ven_phb_test_case_find_contact_sync(s32 nHandle,ven_phb_phonebook_type_t phbkTpye,u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_find_contact_async(s32 nHandle,ven_phb_phonebook_type_t phbkTpye,u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_delete_contact_sync(s32 nHandle, u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_delete_contact_async(s32 nHandle, u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_modify_contact_sync(s32 nHandle, u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_modify_contact_async(s32 nHandle, u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_get_mem_status_sync(s32 nHandle, ven_phb_phonebook_type_t tPhbTpye, u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_get_mem_status_async(s32 nHandle, ven_phb_phonebook_type_t tPhbTpye, u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_number_fuzzy_search_sync(s32 nHandle, ven_phb_phonebook_type_t tPhbTpye, u8 *outStr);
ven_phb_ret_t ms_ven_phb_test_case_number_fuzzy_search_async(s32 nHandle, ven_phb_phonebook_type_t tPhbTpye, u8 *outStr);
#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

/***********************************************************************************/
/*		file browse																																	 */
/***********************************************************************************/
void ms_ven_file_test_case_browse_image_single_select(s32 nHandle);
void ms_ven_file_test_case_browse_image_multi_select(s32 nHandle);
void ms_ven_file_test_case_browse_audio_single_select(s32 nHandle);
void ms_ven_file_test_case_browse_audio_multi_select(s32 nHandle);
void ms_ven_file_test_case_browse_video_single_select(s32 nHandle);
void ms_ven_file_test_case_browse_video_multi_select(s32 nHandle);
void ms_ven_file_test_case_browse_all_single_select(s32 nHandle);
void ms_ven_file_test_case_browse_all_multi_select(s32 nHandle);
void ms_ven_file_test_case_select_folder_async(s32 nHandle);

void ms_ven_file_test_case_browse_image_sync_single_select(s32 nHandle, u8 *outStr);
void ms_ven_file_test_case_browse_image_sync_multi_select(s32 nHandle, u8 *outStr);
void ms_ven_file_test_case_browse_audio_sync_single_select(s32 nHandle, u8 *outStr);
void ms_ven_file_test_case_browse_audio_sync_multi_select(s32 nHandle, u8 *outStr);
void ms_ven_file_test_case_browse_video_sync_single_select(s32 nHandle, u8 *outStr);
void ms_ven_file_test_case_browse_video_sync_multi_select(s32 nHandle, u8 *outStr);
void ms_ven_file_test_case_browse_all_sync_single_select(s32 nHandle, u8 *outStr);
void ms_ven_file_test_case_browse_all_sync_multi_select(s32 nHandle, u8 *outStr);
void ms_ven_file_test_case_select_folder_sync(s32 nHandle, u8 *outStr);

void ms_ven_file_test_case_browse_ex_single_select(s32 nHandle);
void ms_ven_file_test_case_browse_ex_multi_select(s32 nHandle);

#ifndef __SDK_API_WAP_MMS_ONLY__

/***********************************************************************************/
/*		msg	  																																			 */
/***********************************************************************************/
void ms_ven_msg_test_case_send_sms_7bit(s32 nHandle);
void ms_ven_msg_test_case_send_sms_8bit(s32 nHandle);
void ms_ven_msg_test_case_send_sms_ucs2(s32 nHandle);
void ms_ven_msg_test_case_send_sms_unspecific(s32 nHandle);
void ms_ven_msg_test_case_count_sms_page(u8 *outStr);
void ms_ven_msg_test_case_open_editor_sync(s32 nHandle, bool bSms);
void ms_ven_msg_test_case_open_editor(s32 nHandle, bool bSms);

/***********************************************************************************/
/*		call control																																 */
/***********************************************************************************/
void ms_ven_cc_test_case(s32 nHandle);
#ifdef __SDK_API_01_SMS_MMS_CC__
void ms_ven_cc_test_case_get_call_id(s32 nHandle);
void ms_ven_cc_test_release_call(s32 nHandle);
#endif

#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

/***********************************************************************************/
/*		video       																																 */
/***********************************************************************************/


/***********************************************************************************/
/*		wap       																																 */
/***********************************************************************************/
ven_wap_ret_t ms_ven_wap_test_case_open_browser(s32 nHandle, bool bSync);
ven_wap_ret_t ms_ven_wap_test_case_download_browser(s32 nHandle, bool bSync);
ven_wap_ret_t ms_ven_wap_test_case_open_browser_ex(s32 nHandle,ven_wap_download_storage_t eStorage, u8 SimID, bool bSync);
ven_wap_ret_t ms_ven_wap_test_case_get_useragent(s32 nHandle);

#endif // __VEN__TEST_AP_DEFINE_H__
