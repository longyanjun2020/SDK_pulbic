/**
* @file mmi_srv_profile.h
* @brief   Profile Service provide APIs for the profile control purpose. 
*          For Example, to get/set profile settings for some profile ID, to restore profile settings, etc.
*  
*/
#ifndef __MMI_SRV_PROFILE_H__
#define __MMI_SRV_PROFILE_H__


#include "mmi_srv_client_commondefine.h"
#include "mmi_profilesrv.h"


/* callback function type */

/** SRV_PROFILE Event and Callback Function description
* @brief  The interface of Service Client is used to set the indicator-callback to CB module
*
* PROFILESRV_EVT_PROFILE_CHANGE
* PROFILESRV_EVT_PROFILE_INIDICATOR
* PROFILESRV_EVT_INACTIVE_PROFILE_SETTING_CHANGE
*/

/** SrvProfileProfileChangeCB
* @brief         The callback function to confirm the profile change(for current profile). (triggered by PROFILESRV_EVT_PROFILE_CHANGE)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eProfileID         The class ID of the launched AP.
*/
typedef void (* SrvProfileProfileChangeCB)(void *pThis, ProfileID_e eProfileID);

/** SrvProfileInactiveProfileSettingChangeCB
* @brief         The callback function to confirm the profile change(for inactive profile). (triggered by PROFILESRV_EVT_INACTIVE_PROFILE_SETTING_CHANGE)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eProfileID         The class ID of the launched AP.
*/
typedef void (* SrvProfileInactiveProfileSettingChangeCB)(void *pThis, ProfileID_e eProfileID);

/** SrvProfileProfileIndicatorChangeCB
* @brief         The callback function to confirm the profile-indicator change. (triggered by PROFILESRV_EVT_PROFILE_INIDICATOR)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eProfileInd        The class ID of the launched AP.
*/
typedef void (* SrvProfileProfileIndicatorChangeCB)(void *pThis, ProfileIndicator_e eProfileInd);

/* APIs */

/** SrvProfileSetProfileChangeCB
* @brief  Register/deregister a callback function to listen to the profile changed
*
* @param[in]    pfnCallBack             SrvProfileProfileChangeCB, a callback function pointer
*/
void SrvProfileSetProfileChangeCB(SrvProfileProfileChangeCB pfnCallBack);

/** SrvProfileSetProfileIndicatorChangeCB
* @brief  Register/deregister a callback function to listen the profile indicator changed
*
* @param[in]    pfnCallBack             SrvProfileProfileIndicatorChangeCB, a callback function pointer
*/
void SrvProfileSetProfileIndicatorChangeCB(SrvProfileProfileIndicatorChangeCB   pfnCallBack);

/** SrvProfileSetInactiveProfileIndicatorChangeCB
* @brief  Register/deregister a callback function to listen to the setting changed for an inactive profile 
*
* @param[in]    pfnCallBack             SrvProfileInactiveProfileSettingChangeCB, a callback function pointer
*/
void SrvProfileSetInactiveProfileIndicatorChangeCB(SrvProfileInactiveProfileSettingChangeCB pfnCallBack);

/** SrvProfileActivateProfile
* @brief    Activate a profile according to the proposed profile ID.
*
* @param[in]    eProfileID              Indicate the profile ID which sould be activated: PROFILESRV_ID_FIRST
                                                                                          PROFILESRV_ID_NONE
                                                                                          PROFILESRV_ID_GENERAL
                                                                                          PROFILESRV_ID_MEETING
                                                                                          PROFILESRV_ID_OUTDOOR
                                                                                          PROFILESRV_ID_SILENT
                                                                                          PROFILESRV_ID_PERSONAL
                                                                                          PROFILESRV_ID_HEADSET
                                                                                          PROFILESRV_ID_BLUETOOTH
                                                                                          PROFILESRV_ID_LAST
*
* @retval   profile service return value: IPROFILESRV_RET_SUCCESS               ///< operation completed successfully
                                          IPROFILESRV_RET_BAD_PARAM             ///< invalid input parameters
                                          IPROFILESRV_RET_FAILED                ///< WHAT? every code here is failed
                                          IPROFILESRV_RET_OUT_OF_MEMORY         ///< memory is not enough to complete the operation
                                          IPROFILESRV_RET_NOT_SUPPORTED         ///< the request is not supported
                                          IPROFILESRV_RET_NOT_READY             
                                          IPROFILESRV_RET_NOT_FOUND             ///< the specified item is not found
                                          IPROFILESRV_RET_BUSY
                                          IPROFILESRV_RET_FS_FULL
                                          IPROFILESRV_RET_ILLEGAL_OPERATION     ///< the operation is not allowed;
                                          IPROFILESRV_RET_DENY_CHANGE_HEADSET_PROFILE
                                          IPROFILESRV_RET_HEADSET_IN_DENY_CHANGE_PROFILES
                                          IPROFILESRV_RET_DENY_CHANGE_BLUETOOTH_PROFILE
                                          IPROFILESRV_RET_BLUETOOTH_IN_DENY_CHANGE_PROFILES
                                          IPROFILESRV_RET_UNKNOWN_ERROR

*/
IPROFILESRV_Ret SrvProfileActivateProfile(ProfileID_e eProfileID);

/** SrvProfileRestoreProfile
* @brief    Restore the profile settings to its default value.
*
* @param[in]    eProfileID              Indicate the profile ID which sould be restored to default.
*
* @retval   MAE_RET_SUCCESS             If successful.
* @return   MAE_RET_FAILED              If an error happen.
* @retval   MAE_RET_NOT_READY           If ProfileSrv is already terminated.
* @retval   MAE_RET_BAD_PARAM           If wrong parameters. 
* @return   MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvProfileRestoreProfile(ProfileID_e eProfileID);

/** SrvProfileGetCurrentProfileSettings
* @brief    Get the profile settings that currently used.
*
* @param[out]   pstProfileSettings      Place holder to get current profile settings
*
* @retval   MAE_RET_SUCCESS             If successful.
* @return   MAE_RET_FAILED              If an error happen.
* @retval   MAE_RET_NOT_READY           If ProfileSrv is already terminated.
* @retval   MAE_RET_BAD_PARAM           If wrong parameters. 
* @return   MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvProfileGetCurrentProfileSettings(ProfileSettings_t *pstProfileSettings);

/** SrvProfileSetCurrentProfileSettings
* @brief    Set the profile settings that currently used.
*
* @param[in]    pstProfileSettings      The proposed profile settings
*
* @retval   MAE_RET_SUCCESS             If successful.
* @return   MAE_RET_FAILED              If an error happen.
* @retval   MAE_RET_NOT_READY           If ProfileSrv is already terminated.
* @retval   MAE_RET_BAD_PARAM           If wrong parameters. 
* @return   MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvProfileSetCurrentProfileSettings(ProfileSettings_t *pstProfileSettings);

/** SrvProfileGetProfileSettings
* @brief    Get the profile settings accorting to the proposed profile ID and the flag about getting default value or not.
*
* @param[in]    eProfileID              Indicate the profile ID 
* @param[out]   pstProfileSettings      Place holder to get profile settings
* @param[in]    bGetDefaultVaule        TRUE for getting the default settings and FALSE for current settings
*
* @retval   MAE_RET_SUCCESS             If successful.
* @return   MAE_RET_FAILED              If an error happen.
* @retval   MAE_RET_NOT_READY           If ProfileSrv is already terminated.
* @retval   MAE_RET_BAD_PARAM           If wrong parameters. 
* @return   MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvProfileGetProfileSettings(ProfileID_e eProfileID, ProfileSettings_t *pstProfileSettings, boolean bGetDefaultVaule);

/** SrvProfileSetProfileSettings
* @brief    Set the profile settings accorting to the proposed profile ID.
*
* @param[in]    eProfileID              Indicate the profile ID
* @param[in]    pstProfileSettings      The proposed profile settings
*
* @retval   MAE_RET_SUCCESS             If successful.
* @return   MAE_RET_FAILED              If an error happen.
* @retval   MAE_RET_NOT_READY           If ProfileSrv is already terminated.
* @retval   MAE_RET_BAD_PARAM           If wrong parameters. 
* @return   MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvProfileSetProfileSettings(ProfileID_e eProfileID, ProfileSettings_t *pstProfileSettings);

/** SrvProfileGetCurrentProfileID
* @brief    Get the profile ID that currently used.
*
* @param[out]   peProfileID             Place holder to get current profile ID
*
* @retval   MAE_RET_SUCCESS             If successful.
* @return   MAE_RET_FAILED              If an error happen.
* @retval   MAE_RET_NOT_READY           If ProfileSrv is already terminated.
* @retval   MAE_RET_BAD_PARAM           If wrong parameters. 
* @return   MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvProfileGetCurrentProfileID(ProfileID_e *peProfileID);

/** SrvProfileReloadCurrentProfile
* @brief    Reload the profile settings that currently used.
            Used when master reset.
*
* @retval   MAE_RET_SUCCESS             If successful.
* @return   MAE_RET_FAILED              If an error happen.
* @retval   MAE_RET_NOT_READY           If ProfileSrv is already terminated.
* @retval   MAE_RET_BAD_PARAM           If wrong parameters. 
* @return   MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvProfileReloadCurrentProfile(void);

/** SrvProfileGetCurrentPorfileVolumeInfo
* @brief  Get the volume information of the current profile.
*
* @param[out]   pMaxVol                 Place holder to get max volume.
* @param[out]   pCurVol                 Place holder to get current volume: VOLUME_LEVEL_MIN
                                                                            VOLUME_LEVEL_OFF
                                                                            VOLUME_LEVEL_1
                                                                            VOLUME_LEVEL_2
                                                                            VOLUME_LEVEL_3
                                                                            VOLUME_LEVEL_4
                                                                            VOLUME_LEVEL_5
                                                                            VOLUME_LEVEL_6
                                                                            VOLUME_LEVEL_7
                                                                            VOLUME_LEVEL_8
                                                                            VOLUME_LEVEL_MAX
*
* @retval   MAE_RET_SUCCESS             If successful.
* @return   MAE_RET_FAILED              If an error happen.
* @retval   MAE_RET_NOT_READY           If ProfileSrv is already terminated.
* @retval   MAE_RET_BAD_PARAM           If wrong parameters. 
* @return   MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvProfileGetCurrentProfileVolumeInfo(SetRingToneVolume_e *pMaxVol, SetRingToneVolume_e *pCurVol);

/** SrvProfileGetCurrentPorfileIndicator
* @brief  Get the indicator of the current profile .
*
* @param[out]   pProfileIndicator       Place holder to get profile indicator: PROFILESRV_IND_FIRST 
                                                                               PROFILESRV_IND_GENERAL
                                                                               PROFILESRV_IND_MEETING
                                                                               PROFILESRV_IND_OUTDOOR
                                                                               PROFILESRV_IND_SILENT
                                                                               PROFILESRV_IND_PERSONAL
                                                                               PROFILESRV_IND_HEADSET
                                                                               PROFILESRV_IND_BLUETOOTH
                                                                               PROFILESRV_IND_SILENT_HEADSET
                                                                               PROFILESRV_IND_LAST
*
* @retval   MAE_RET_SUCCESS             If successful.
* @return   MAE_RET_FAILED              If an error happen.
* @retval   MAE_RET_NOT_READY           If ProfileSrv is already terminated.
* @retval   MAE_RET_BAD_PARAM           If wrong parameters. 
* @return   MAE_RET_OUT_OF_MEMORY       If can not allocate memory from OS.
*/
MAE_Ret SrvProfileGetCurrentProfileIndicator(ProfileIndicator_e *pProfileIndicator);

/** SrvProfileGetPreviousPorfileID
* @brief  Get the previous profile ID.
*
* @param[out]   peProfileID             Place holder to get previous profile ID.
* 
* @retval   MAE_RET_SUCCESS             If successful.
*/
MAE_Ret SrvProfileGetPreviousProfileID(ProfileID_e *peProfileID);

/** SrvProfileNotifyInactivateSilentModeByHotKey
* @brief  The interface is used to notify that the next SrvProfileActivateProfile is called to inactivate silent mode by hot key(#)
*
* @retval   MAE_RET_SUCCESS          If successful.
* @retval   MAE_RET_NOT_READY        If ProfileSrv is already terminated.
*/
MAE_Ret SrvProfileNotifyInactivateSilentModeByHotKey(void);

#endif /* __MMI_SRV_PROFILE_H__ */
