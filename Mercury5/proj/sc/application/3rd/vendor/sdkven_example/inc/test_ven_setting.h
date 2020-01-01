#ifndef __TEST_VEN_SETTING__
#define __TEST_VEN_SETTING__
/**
 *
 * @file    Test_ven_setting.h
 * @brief   This file defines the test case of ven_setting SDK API
 *
 * @author  Jorena.Ku
 * @version $Id: 
 *
 */

#include "ven_setting.h"


/**
 *  ven_setting_getProfileFileURL_syncTest
 *  @brief  Test the ven_setting_getProfileFileURL API with the sync request.
 *          Before running this test case, user should set the profile file as not predefine file or theme file.
 *
 *  @param  type the file type. Wallpaper or specific ringtone
 *  @retval None
 */
void ven_setting_getProfileFileURL_syncTest(ven_setting_file_type_t type);

/**
 *  ven_setting_getProfileFileURL_asyncTest
 *  @brief  Test the ven_setting_getProfileFileURL API with the async request.
 *          Before running this test case, user should set the profile file as not predefine file or theme file.
 *
 *  @param  type the file type. Wallpaper or specific ringtone
 *  @retval None
 */
void ven_setting_getProfileFileURL_asyncTest(ven_setting_file_type_t type);

/**
 *  ven_setting_getProfileFileDisplayName_syncTest
 *  @brief  Test the ven_setting_getProfileFileDisplayName API with the sync request.
 *          Before running this test case, user should set the profile file as not predefine file or theme file.
 *
 *  @param  type the file type. Wallpaper or specific ringtone
 *  @retval None
 */
void ven_setting_getProfileFileDisplayName_syncTest(ven_setting_file_type_t type);

/**
 *  ven_setting_getProfileFileDisplayName_asyncTest
 *  @brief  Test the ven_setting_getProfileFileDisplayName API with the async request.
 *          Before running this test case, user should set the profile file as not predefine file or theme file.
 *
 *  @param  type the file type. Wallpaper or specific ringtone
 *  @retval None
 */
void ven_setting_getProfileFileDisplayName_asyncTest(ven_setting_file_type_t type);

/**
 *  ven_setting_setWallpaperFileURL_syncTest
 *  @brief  Test the ven_setting_setProfileFileURL API with the sync request and VEN_SETTING_FILE_WALLPAPER file type.
 *          Before running this test case, user should copy a test.bmp bitmap file in /CARD/ folder
 *          and insert the SD card.
 *
 *  @param  type the file type. Wallpaper or specific ringtone
 *  @retval None
 */
void ven_setting_setWallpaperFileURL_syncTest(void);

/**
 *  ven_setting_setWallpaperFileURL_asyncTest
 *  @brief  Test the ven_setting_setProfileFileURL API with the async request and VEN_SETTING_FILE_WALLPAPER file type.
 *          Before running this test case, user should copy a test.bmp bitmap file in /CARD/ folder
 *          and insert the SD card.
 *
 *  @param  type the file type. Wallpaper or specific ringtone
 *  @retval None
 */
void ven_setting_setWallpaperFileURL_asyncTest(void);
void ven_setting_getProfileVibration_syncTest(void);
void ven_setting_getProfileVibration_asyncTest(void);
void ven_setting_getProfileVolume_syncTest(ven_setting_profile_volume_type_t type);
void ven_setting_getProfileVolume_asyncTest(ven_setting_profile_volume_type_t type);
void ven_setting_getNetworkProfile_syncTest(ven_setting_network_profile_type_t type, ven_common_sim_id_t SimID);
void ven_setting_getNetworkProfile_asyncTest(ven_setting_network_profile_type_t type, ven_common_sim_id_t SimID);
void ven_setting_setNetworkProfile_syncTest(ven_setting_network_profile_type_t type, ven_common_sim_id_t SimID);
void ven_setting_setNetworkProfile_asyncTest(ven_setting_network_profile_type_t type, ven_common_sim_id_t SimID);
void ven_setting_getSelectSIM_syncTest(ven_setting_sim_function_type_t type);
void ven_setting_getSelectSIM_asyncTest(ven_setting_sim_function_type_t type);

#endif
