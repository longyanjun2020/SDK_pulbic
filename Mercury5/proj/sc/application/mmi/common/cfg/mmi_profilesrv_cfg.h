
#ifndef __MMI_PROFILESRV_CFG__H__
#define __MMI_PROFILESRV_CFG__H__

#ifndef MID_INCOMING_PATH
#define MID_INCOMING_PATH L""
#endif
#ifndef MID_MESSAGE_PATH
#define MID_MESSAGE_PATH L""
#endif
#ifndef MID_CALENDAR_PATH
#define MID_CALENDAR_PATH L""
#endif
#ifndef MID_ALARM_PATH
#define MID_ALARM_PATH L""
#endif

#ifdef __DUAL_PROFILE_MMI__
//profile
#define CONFIG_AMR_PROFILE_GENERAL CONFIG_DEFINE(CFGIT_PROFILE_GENERAL, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_OFF/*eVibrateType*/, \
VOLUME_LEVEL_6/*eVolume*/, \
SET_ON/*ePowerOnTone*/, \
SET_ON/*ePowerOffTone*/, \
RING_TYPE_RINGING/*eRingingType*/, \
MESSAGE_TONE_ON/*eMessageTone*/, \
CALENDAR_TONE_ON/*eCalendarTone*/, \
ALARM_TONE_ON/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_INCOMING_PATH}/*stSIM2VoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_MESSAGE_PATH}/*stSIM2MessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_SILENT CONFIG_DEFINE(CFGIT_PROFILE_SILENT, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_OFF/*eVolume*/, \
FALSE/*eAutoAnswer*/, \
SET_OFF/*ePowerOffTone*/, \
RING_TYPE_SILENT/*eRingingType*/, \
MESSAGE_TONE_OFF/*eMessageTone*/, \
CALENDAR_TONE_OFF/*eCalendarTone*/, \
ALARM_TONE_OFF/*eAlarmTone*/, \
SET_OFF/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_INCOMING_PATH}/*stSIM2VoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_MESSAGE_PATH}/*stSIM2MessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_MEETING CONFIG_DEFINE(CFGIT_PROFILE_MEETING, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_2/*eVolume*/, \
SET_OFF/*ePowerOnTone*/, \
SET_OFF/*ePowerOffTone*/, \
RING_TYPE_BEEP/*eRingingType*/, \
MESSAGE_TONE_BEEP/*eMessageTone*/, \
CALENDAR_TONE_BEEP/*eCalendarTone*/, \
ALARM_TONE_BEEP/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_INCOMING_PATH}/*stSIM2VoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_MESSAGE_PATH}/*stSIM2MessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_OUTDOOR CONFIG_DEFINE(CFGIT_PROFILE_OUTDOOR, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_8/*eVolume*/, \
SET_ON/*ePowerOnTone*/, \
SET_ON/*ePowerOffTone*/, \
RING_TYPE_RINGING/*eRingingType*/, \
MESSAGE_TONE_ON/*eMessageTone*/, \
CALENDAR_TONE_ON/*eCalendarTone*/, \
ALARM_TONE_ON/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_INCOMING_PATH}/*stSIM2VoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_MESSAGE_PATH}/*stSIM2MessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_PERSONAL CONFIG_DEFINE(CFGIT_PROFILE_PERSONAL, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_6/*eVolume*/, \
SET_ON/*ePowerOnTone*/, \
SET_ON/*ePowerOffTone*/, \
RING_TYPE_RINGING/*eRingingType*/, \
MESSAGE_TONE_ON/*eMessageTone*/, \
CALENDAR_TONE_ON/*eCalendarTone*/, \
ALARM_TONE_ON/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_INCOMING_PATH}/*stSIM2VoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_MESSAGE_PATH}/*stSIM2MessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_HEADSET CONFIG_DEFINE(CFGIT_PROFILE_HEADSET, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_6/*eVolume*/, \
SET_ON/*ePowerOnTone*/, \
SET_ON/*ePowerOffTone*/, \
RING_TYPE_RINGING/*eRingingType*/, \
MESSAGE_TONE_ON/*eMessageTone*/, \
CALENDAR_TONE_ON/*eCalendarTone*/, \
ALARM_TONE_ON/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_INCOMING_PATH}/*stSIM2VoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_MESSAGE_PATH}/*stSIM2MessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_BLUETOOTH CONFIG_DEFINE(CFGIT_PROFILE_BLUETOOTH, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_6/*eVolume*/, \
SET_ON/*ePowerOnTone*/, \
SET_ON/*ePowerOffTone*/, \
RING_TYPE_RINGING/*eRingingType*/, \
MESSAGE_TONE_ON/*eMessageTone*/, \
CALENDAR_TONE_ON/*eCalendarTone*/, \
ALARM_TONE_ON/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_INCOMING_PATH}/*stSIM2VoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_MESSAGE_PATH}/*stSIM2MessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#ifdef __POWER_SAVING_PROFILE_MMI__
#define CONFIG_AMR_PROFILE_POWER_SAVING CONFIG_DEFINE(CFGIT_PROFILE_POWER_SAVING, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_OFF/*eVibrateType*/, \
VOLUME_LEVEL_4/*eVolume*/, \
SET_OFF/*ePowerOnTone*/, \
SET_OFF/*ePowerOffTone*/, \
RING_TYPE_RING_ONCE/*eRingingType*/, \
MESSAGE_TONE_BEEP/*eMessageTone*/, \
CALENDAR_TONE_BEEP/*eCalendarTone*/, \
ALARM_TONE_BEEP/*eAlarmTone*/, \
SET_OFF/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_INCOMING_PATH}/*stSIM2VoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_MESSAGE_PATH}/*stSIM2MessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#else
#define CONFIG_AMR_PROFILE_POWER_SAVING
#endif

#else//non __DUAL_PROFILE_MMI__

//profile
#define CONFIG_AMR_PROFILE_GENERAL CONFIG_DEFINE(CFGIT_PROFILE_GENERAL, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_OFF/*eVibrateType*/, \
VOLUME_LEVEL_6/*eVolume*/, \
SET_ON/*ePowerOnTone*/, \
SET_ON/*ePowerOffTone*/, \
RING_TYPE_RINGING/*eRingingType*/, \
MESSAGE_TONE_ON/*eMessageTone*/, \
CALENDAR_TONE_ON/*eCalendarTone*/, \
ALARM_TONE_ON/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_SILENT CONFIG_DEFINE(CFGIT_PROFILE_SILENT, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_OFF/*eVolume*/, \
SET_OFF/*ePowerOnTone*/, \
SET_OFF/*ePowerOffTone*/, \
RING_TYPE_SILENT/*eRingingType*/, \
MESSAGE_TONE_OFF/*eMessageTone*/, \
CALENDAR_TONE_OFF/*eCalendarTone*/, \
ALARM_TONE_OFF/*eAlarmTone*/, \
SET_OFF/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_MEETING CONFIG_DEFINE(CFGIT_PROFILE_MEETING, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_2/*eVolume*/, \
SET_OFF/*ePowerOnTone*/, \
SET_OFF/*ePowerOffTone*/, \
RING_TYPE_BEEP/*eRingingType*/, \
MESSAGE_TONE_BEEP/*eMessageTone*/, \
CALENDAR_TONE_BEEP/*eCalendarTone*/, \
ALARM_TONE_BEEP/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_OUTDOOR CONFIG_DEFINE(CFGIT_PROFILE_OUTDOOR, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_8/*eVolume*/, \
SET_ON/*ePowerOnTone*/, \
SET_ON/*ePowerOffTone*/, \
RING_TYPE_RINGING/*eRingingType*/, \
MESSAGE_TONE_ON/*eMessageTone*/, \
CALENDAR_TONE_ON/*eCalendarTone*/, \
ALARM_TONE_ON/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_PERSONAL CONFIG_DEFINE(CFGIT_PROFILE_PERSONAL, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_6/*eVolume*/, \
SET_ON/*ePowerOnTone*/, \
SET_ON/*ePowerOffTone*/, \
RING_TYPE_RINGING/*eRingingType*/, \
MESSAGE_TONE_ON/*eMessageTone*/, \
CALENDAR_TONE_ON/*eCalendarTone*/, \
ALARM_TONE_ON/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_HEADSET CONFIG_DEFINE(CFGIT_PROFILE_HEADSET, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_6/*eVolume*/, \
SET_ON/*ePowerOnTone*/, \
SET_ON/*ePowerOffTone*/, \
RING_TYPE_RINGING/*eRingingType*/, \
MESSAGE_TONE_ON/*eMessageTone*/, \
CALENDAR_TONE_ON/*eCalendarTone*/, \
ALARM_TONE_ON/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#define CONFIG_AMR_PROFILE_BLUETOOTH CONFIG_DEFINE(CFGIT_PROFILE_BLUETOOTH, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_ON/*eVibrateType*/, \
VOLUME_LEVEL_6/*eVolume*/, \
SET_ON/*ePowerOnTone*/, \
SET_ON/*ePowerOffTone*/, \
RING_TYPE_RINGING/*eRingingType*/, \
MESSAGE_TONE_ON/*eMessageTone*/, \
CALENDAR_TONE_ON/*eCalendarTone*/, \
ALARM_TONE_ON/*eAlarmTone*/, \
SET_ON/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#ifdef __POWER_SAVING_PROFILE_MMI__
#define CONFIG_AMR_PROFILE_POWER_SAVING CONFIG_DEFINE(CFGIT_PROFILE_POWER_SAVING, ProfileSettings_t, 1, {VIBRATE_TYPE_VIBRATE_OFF/*eVibrateType*/, \
VOLUME_LEVEL_4/*eVolume*/, \
SET_OFF/*ePowerOnTone*/, \
SET_OFF/*ePowerOffTone*/, \
RING_TYPE_RING_ONCE/*eRingingType*/, \
MESSAGE_TONE_BEEP/*eMessageTone*/, \
CALENDAR_TONE_BEEP/*eCalendarTone*/, \
ALARM_TONE_BEEP/*eAlarmTone*/, \
SET_OFF/*eMissEventReminder*/, \
KEYPAD_TONE_OFF/*eKeypadTone*/, \
SLIDE_TONE_OFF/*eSlideTone*/, \
FALSE/*eAutoAnswer*/, \
{MID_INCOMING_PATH}/*stVoiceCallRingToneURL*/, \
{MID_MESSAGE_PATH}/*stMessageRingToneURL*/, \
{MID_CALENDAR_PATH}/*stCalendarRingToneURL*/, \
{MID_ALARM_PATH}/*stAlarmRingToneURL*/,\
{MID_POWER_ON_PATH}/*stPowerOnToneURL*/,\
{MID_POWER_OFF_PATH}/*stPowerOffToneURL*/})
#else
#define CONFIG_AMR_PROFILE_POWER_SAVING
#endif
#endif

#define CONFIG_AMR_PROFILE_CURRENT_PROFILE_ID CONFIG_DEFINE(CFGIT_PROFILE_CURRENT_PROFILE_ID, ProfileID_e, 1, PROFILESRV_ID_GENERAL)
#define CONFIG_AMR_PROFILE_PREVIOUS_PROFILE_ID CONFIG_DEFINE(CFGIT_PROFILE_PREVIOUS_PROFILE_ID, ProfileID_e, 1, PROFILESRV_ID_GENERAL)
#define CONFIG_AMR_PROFILE_PREVIOUS_NORMAL_PROFILE_ID CONFIG_DEFINE(CFGIT_PROFILE_PREVIOUS_NORMAL_PROFILE_ID, ProfileID_e, 1, PROFILESRV_ID_GENERAL)
#ifdef __EXTRA_BLUETOOTH_HEADSET_PROFILE_MMI__
#define CONFIG_AMR_PROFILE_MAP_BTHEADSET_TO_HEADSET CONFIG_DEFINE(CFGIT_PROFILE_MAP_BTHEADSET_TO_HEADSET, boolean, 1, FALSE)
#else
#define CONFIG_AMR_PROFILE_MAP_BTHEADSET_TO_HEADSET CONFIG_DEFINE(CFGIT_PROFILE_MAP_BTHEADSET_TO_HEADSET, boolean, 1, TRUE)
#endif

//profile end

#define PROFILESRV_AMR_ALL_CONFIG \
                          CONFIG_AMR_PROFILE_GENERAL \
                          CONFIG_AMR_PROFILE_SILENT \
                          CONFIG_AMR_PROFILE_MEETING \
                          CONFIG_AMR_PROFILE_OUTDOOR \
                          CONFIG_AMR_PROFILE_PERSONAL \
                          CONFIG_AMR_PROFILE_HEADSET \
                          CONFIG_AMR_PROFILE_BLUETOOTH \
                          CONFIG_AMR_PROFILE_POWER_SAVING \
                          CONFIG_AMR_PROFILE_CURRENT_PROFILE_ID \
                          CONFIG_AMR_PROFILE_PREVIOUS_PROFILE_ID \
                          CONFIG_AMR_PROFILE_PREVIOUS_NORMAL_PROFILE_ID \
                          CONFIG_AMR_PROFILE_MAP_BTHEADSET_TO_HEADSET
#endif //__MMI_PROFILESRV_CFG__H__


