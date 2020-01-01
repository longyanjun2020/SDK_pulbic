////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file mmi_emapp_driverinfo.h
*
* @version $Id: mmi_em_driverinfo.h 27933 2009-04-09 11:49:07Z lena.lin $
*/
#ifndef __MMI_EMAPP_DRIVERINFO_H__
#define __MMI_EMAPP_DRIVERINFO_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_emapp_priv.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define EM_AUTO_SWITCH_TIME (500)           //0.5sec
#define EM_MP3_SWITCH_TIME (1000)           //1sec.
#define EM_KEYPAD_CHECK_TIMER (5000)        //5sec.
#define EM_USB_CHECK_TIMER (10000)          //10sec.
#define EM_HEADSET_CHECK_TIMER (10000)      //10sec.
#define EM_SWITCH_HEADSET_AUDIO_PATH_TIMER (500)
#ifdef __G_SENSOR_MMI__
#define EM_TEST_GSENSOR_TIMEOUT (1500)
#define EM_GSENSOR_TEST_COUNTS (20)
#endif
#ifdef __APP_MMI_FM_RADIO__
#define EM_QUERY_FMR_CHANNEL_TIMER (1000)
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    MMI_EM_BT_POW_LEVEL_CHECK_BT_ONOFF= 0,
    MMI_EM_BT_POW_LEVEL
} EmAppBtPowLevelState_e;

typedef enum
{
    MMI_EM_BT_RSSI_CHECK_BT_ONOFF = 0,
    MMI_EM_BT_RSSI
} EmAppBtRssiState_e;

typedef enum
{
    MMI_EM_BT_AUTO_TEST_CHECK_BT_ONOFF = 0,
    MMI_EM_BT_AUTO_TEST
} EmAppBtAutoTestState_e;

typedef enum
{
    MMI_EM_GSENSOR_LEFT = 0x01,
    MMI_EM_GSENSOR_RIGHT = 0x02,
    MMI_EM_GSENSOR_TOP = 0x04,
    MMI_EM_GSENSOR_DOWN = 0x08
}MMI_EM_GSENSOR_DIRECTION_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/
//Request function
u32 em_request_audio_test               (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_backlight_test           (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_keypad_test              (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
//u32 em_request_contrast_test          (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_keypadlight_test         (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_lcd_test                 (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_dsc_test                 (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_rtc_test                 (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mp3_test                 (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_vibration_test           (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_sd_test                  (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#ifdef __DUAL_CARD__
u32 em_request_sd2_test                 (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif
u32 em_request_sd_performace_test       (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_sd_rela_config_radio_m   (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_sd_rela_config_sync      (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_sd_test_performance      (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_register_write           (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_register_read            (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_battery_test             (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_adc_test                 (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_headset_test             (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_io_status                (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_handwriting_speed        (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);

#ifdef __EM_USB_TEST_AVAILABLE__
u32 em_request_usb_status               (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif

#ifdef __BLUETOOTH_MMI__
u32 em_request_bt_host_version          (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_bt_status                (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_bt_address               (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_bt_pow_level             (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_bt_rssi                  (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_bt_conti                 (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_gsm_onoff(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_bt_auto_test             (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_bt_pow_level  (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_bt_rssi       (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_bt_conti      (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_bt_auto_test  (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32 em_exit_bt_test                     (EmAppData_t *pThis, u32 param1);
#endif//#ifdef __BLUETOOTH_MMI__

#ifdef __G_SENSOR_MMI__
u32 em_request_gsensor_test             (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif

#ifdef __APP_MMI_FM_RADIO__
u32 em_request_fmr_rf_test              (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_fmr_auto_list            (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_fmr_auto_list_ex         (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_fmr_set_area             (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_fmr_radio_menu           (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_fmr_set_radio_menu       (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_fmr_set_carrier          (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_fmr_area_values          (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_fmr_rf_performance(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif

#ifdef __GPS_MMI__
u32 em_request_gps_get_data_test        (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_gps_extfunc_test         (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_gps_io_test(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_exit_gps_get_data_test(EmAppData_t *pThis, u32 param1);

EmAppResRet_e em_response_gps_get_data_test(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_gps_extfunc_test (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_gps_io_test      (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

#endif


//Response function
EmAppResRet_e em_response_audio_test       (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_mp3_test         (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_backlight_test   (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
//EmAppResRet_e em_response_keypad_test    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_keypadlight_test (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_lcd_test         (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_register_write   (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_register_read    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

#ifdef __BLUETOOTH_MMI__
EmAppResRet_e em_response_bt_status        (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
#endif//#ifdef __BLUETOOTH_MMI__

#ifdef __G_SENSOR_MMI__
EmAppResRet_e em_response_gsensor_test     (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
#endif

EmAppResRet_e em_response_headset_test     (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_sd_test          (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
#ifdef __DUAL_CARD__
EmAppResRet_e em_response_sd2_test          (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
#endif

#ifdef __EM_USB_TEST_AVAILABLE__
EmAppResRet_e em_response_usb_test         (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
#endif

#ifdef __APP_MMI_FM_RADIO__
EmAppResRet_e em_response_fmr_rf_test      (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_fmr_auto_list    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_fmr_auto_list_ex (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_fmr_set_carrier  (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_fmr_set_radio_menu(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_fmr_rf_performance(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
#endif

//Exit function
u32 em_exit_audio_test                     (EmAppData_t *pThis, u32);
u32 em_exit_keypadlight_test               (EmAppData_t *pThis, u32);
u32 em_exit_backlight_test                 (EmAppData_t *pThis, u32);
u32 em_exit_lcd_test                       (EmAppData_t *pThis, u32);
u32 em_exit_mp3_test                       (EmAppData_t *pThis, u32);
u32 em_exit_vibration_test                 (EmAppData_t *pThis, u32);
u32 em_exit_handwriting_speed              (EmAppData_t *pThis, u32);
#ifdef __BLUETOOTH_MMI__
u32 em_exit_bt_status                      (EmAppData_t *pThis, u32);
#endif//#ifdef __BLUETOOTH_MMI__
u32 em_exit_headset_test                   (EmAppData_t *pThis, u32);
u32 em_exit_sd_test                        (EmAppData_t *pThis, u32);

#ifdef __EM_USB_TEST_AVAILABLE__
u32 em_exit_usb_test                       (EmAppData_t *pThis, u32);
#endif

#ifdef __G_SENSOR_MMI__
u32 em_exit_gsensor_test                   (EmAppData_t *pThis, u32 param1);
#endif

#ifdef __APP_MMI_FM_RADIO__
u32 em_exit_fmr_rf_test                    (EmAppData_t *pThis, u32 param1);
u32 em_exit_fmr_auto_list                  (EmAppData_t *pThis, u32 param1);
u32 em_exit_fmr_auto_list_ex               (EmAppData_t *pThis, u32 param1);
u32 em_exit_fmr_rf_performance             (EmAppData_t *pThis, u32 param1);
#endif

void EM_Driver_AutoSwitchTimerCB(void *pData);
static void EM_Driver_Interrupt_Callback(void *pUserData, u32 nCusData, MediaSrvInterruptStatus_e eStatus);

#ifdef __EM_KEYPAD_TEST_FUN__
void EM_Driver_CheckKeypadPressedCB(void* pApplet);
#endif//__EM_KEYPAD_TEST_FUN__
void EM_Driver_CheckTimeOutCB(void *pData);
#endif//__MMI_EMAPP_DRIVERINFO_H__

u32 em_request_mmp_status                           (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mmp_enable_force                     (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mmp_disable_force                    (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mmp_bist_test                        (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mmp_cmdtimeout_test		            (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);

u32 em_request_backlight_off_test                   (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_result_test                      (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_onoff_test                       (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_spi_nor_driving_test				(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_spi_nor_clock_test				(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_stress_test				        (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_bench_memcpy_test					(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_bench_nor_bits_test					(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_bench_nor_read_test					(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_bench_nor_write_test					(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_bench_riu_test					(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_mcp_bench_mmp_test					(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);


u32 em_backlight_restore                            (EmAppData_t *pThis, u32 param1);
EmAppResRet_e em_response_backlight_off_test        (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_keypad_light_off_test     (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

u32 em_request_keypad_light_off_test                (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#ifdef __FLASHLIGHT_MMI__
u32 em_request_flashlight_on_test(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_flashlight_on_test(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32  em_flashlight_restore(EmAppData_t *pThis, u32 param1);
#endif

#ifdef __TTS__
u32 em_request_tts_play_test(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_tts_play_test(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32  em_tts_restore(EmAppData_t *pThis, u32 param1);
#endif

#ifdef __FILLLIGHT_MMI__
u32 em_request_filllight_on_test(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_filllight_on_test(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32  em_filllight_restore(EmAppData_t *pThis, u32 param1);
#endif
u32 em_request_hot_key_exception(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_pitch_stretch(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
#ifdef __TOUCH_SCREEN_FWUPDATE_MMI__
u32 em_request_ts_fwupdate(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_response_ts_fwupdate(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32 em_exit_ts_fwupdate(EmAppData_t *pThis, u32 param1);
void UpdateTSFirmwareCb(void *pUserData, u32 nTsRet, u16 nFirmwareId);
#endif

u32 em_request_lcd_write_reg(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_lcd_write_reg(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

u32 em_request_lcd_read_reg(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_lcd_read_reg(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

#ifdef __WLAN_MMI__
u32 em_request_wifi_off(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_on(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_reset(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_gsm_off_wifi_on(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_gsm_on_wifi_on(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_aquariud_sw_version(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_get_ip(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_dest_mac(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_tx_rate_radio_menu(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_rate(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_channel(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_packet_length(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_packet_number(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_pga(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_send_tx(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_stop_tx(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_rx_rate(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_rx_len(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_rx_chan(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_rx_filter_mac(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_set_rx(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_get_rx(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_reg_bank(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_reg_offset(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_reg_write_value(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_write_reg_command(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_read_reg_command(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_rf_reg(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_write_rf_reg_command(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_read_rf_reg_command(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
ABL_WiFiErrCode_e em_request_wifi_read_all_rf_reg(EmAppData_t *pThis);
u32 em_request_wifi_aqua_mem_addr(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_aqua_mem_radio_menu(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_aqua_mem_len(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_write_aqua_mem_command(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_read_aqua_mem_command(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_set_tx_sinetone(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_stop_sinetone(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_production(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_throughput(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_wifi_throughput_set_ip(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif

#ifdef __WLAN_MMI__
EmAppResRet_e em_response_wifi_off(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_on(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_reset(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_gsm_off_wifi_on(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_gsm_on_wifi_on(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_aquariud_sw_version(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_get_ip(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_dest_mac(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_channel(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_packet_length(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_packet_number(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_pga(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_send_tx(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_stop_tx(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_rx_rate(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_rx_len(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_rx_chan(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_rx_filter_mac(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_set_rx(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_get_rx(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_reg_bank(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_reg_offset(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_reg_write_value(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_write_reg_command(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_read_reg_command(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_rf_reg(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_write_rf_reg_command(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_read_rf_reg_command(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_aqua_mem_addr(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_write_aqua_mem_command(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_read_aqua_mem_command(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_set_tx_sinetone(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_stop_sinetone(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_production(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_throughput(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_wifi_throughput_set_ip(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

#endif

#ifdef __WLAN_MMI__
u32 em_exit_wifi_off(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_on(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_reset(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_gsm_off_wifi_on(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_gsm_on_wifi_on(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_aquariud_sw_version(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_get_ip(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_dest_mac(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_channel(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_packet_length(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_packet_number(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_pga(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_send_tx(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_stop_tx(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_rx_rate(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_rx_len(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_rx_chan(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_rx_filter_mac(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_set_rx(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_get_rx(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_reg_bank(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_reg_offset(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_reg_write_value(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_write_reg_command(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_read_reg_command(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_rf_reg(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_write_rf_reg_command(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_read_rf_reg_command(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_aqua_mem_addr(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_write_aqua_mem_command(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_read_aqua_mem_command(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_set_tx_sinetone(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_stop_sinetone(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_production(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_throughput(EmAppData_t *pThis, u32 param1);
u32 em_exit_wifi_throughput_set_ip(EmAppData_t *pThis, u32 param1);

#endif
