#ifndef __JAP_AMS_DEFINE_H__
#define __JAP_AMS_DEFINE_H__
/**
*
* @file    jap_ams.h
* @brief   This file .
*
* @author  Kris.Wang
* @version $Id: jap_ams.h 28349 2009-04-15 02:10:31Z code.lin $
*
*/


/* Mstar header - begin */
#include "jap_head.h"
#include "java_ams.h"
/* Mstar header - end */

#define AMS_RST_SUCCESS             JAVA_RET_OK
#define AMS_RST_ERROR               JAVA_RET_FAIL

// For SLDLM
#define AMS_SLDLM_LOADED                 (1)
#define AMS_SLDLM_ERROR                  (2)

// this is group id 
#define AMS_PERMISSION_GROUPID_NETWORK      0
#define AMS_PERMISSION_GROUPID_MESSAGE      1
#define AMS_PERMISSION_GROUPID_AUTOSTART    3
#define AMS_PERMISSION_GROUPID_LOCALCONN    4
#define AMS_PERMISSION_GROUPID_MULTIMEDIA   5
#define AMS_PERMISSION_GROUPID_READDATA     6
#define AMS_PERMISSION_GROUPID_WRITEDATA    7

enum
{
    JAP_INSTALL_TO_NAND = 0,
    JAP_INSTALL_TO_NOR,
    JAP_INSTALL_TO_MEMCARD,
    JAP_INSTALL_TO_MEMCARD2,
    JAP_INSTALL_TO_PREINSTALL
};
typedef u8 jap_installToStorage;

typedef struct _JAPAMS_Midlet
{
    u16 midlet_name[64 + 1];
    java_icon_struct *icon_data;
} JAPAMS_Midlet;

typedef struct _JAPAMS_Suite
{
    s32    id;
    u8  Category;
    u16 suiteName[64 + 1];
    u16 vendor[64 + 1];
    u16 version[16];
    u16 *jad_url;
    u16 *jar_url; 
    u16 *suite_description;
    u32 size;
    u8  numOfMidlet;
    java_icon_struct suite_icon; 
    JAPAMS_Midlet *midletList;
}
JAPAMS_Suite;

typedef struct
{
    u16  nInitTextlen;
    u16* pInitText;
    u16* pTitleText;
    u16* pInputModeText;
} JAPAMS_EditorData;

typedef enum
{
    JAP_AMS_UPDATE_NONE = 0,
    JAP_AMS_UPDATE_FULL,
    JAP_AMS_UPDATE_INSTALL,
    JAP_AMS_UPDATE_DELETE,

    JAP_TOTAL_AMS_UPDATE_LEVEL

} jap_AMSUpdateLevelE;

enum
{
    JAPAMS_INIT_NONE = 0,
    JAPAMS_INIT_ONCE,
    JAPAMS_INIT_REINIT,
};

/**
 *  jap_ams_release
 *
 *  @brief  Allocate resource for AMS running
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_initial(void);

/**
 *  jap_ams_release
 *
 *  @brief  Release resource that is allocated for AMS running
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_release(void);

/**
 *  jap_ams_create_AMSList
 *
 *  @brief  Ask VM to create the catched AMS list
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_create_AMSList(u8 updateLevel);

/**
 *  jap_ams_CheckMidletSuite
 *
 *  @brief  check a java jad/jar file 
 *
 *  @param  jadPath     [in] the jad file path
 *  @param  jarPath     [in] the jar file path
 *  @param  cb          [in] callback function for status update
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_CheckMidletSuite(u16 *jadPath, u16 *jarPath, u8 nStorage, java_ams_InstallCheckCB cb);

/**
 *  jap_ams_InstallMidletSuite
 *
 *  @brief  install a java app 
 *
 *  @param  jadPath     [in] the jad file path
 *  @param  jarPath     [in] the jar file path
 *  @param  KeepRMS     [in] if keep the previous RMS data
 *  @param  oldId       [in] check result need to be passed to Aplix VM
 *  @param  storage     [in] destination storage(NAND, SD,..) install to
 *  @param  cb          [in] callback function for status update
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_InstallMidletSuite(u16 *jadPath, u16 *jarPath, int KeepRMS, s32 oldId, jap_installToStorage storage, java_ams_installProgressCB cb);

/**
 *  jap_ams_getSuiteCount
 *
 *  @brief  Get numbers of installed suites
 *
 *  @retval > 0 if success, the return value is the suite count
 *          AMS_RST_ERROR if failed
 */
int jap_ams_getSuiteCount(void);

/**
 *  jap_ams_getSuiteInfo
 *
 *  @brief  Get detail info for an installed java suite
 *
 *  @param  index           [in] The index for the suite that you want to launch
 *  @param  ret             [out] The info structure for putting suite info
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_getSuiteInfo(int index, java_suite_struct *ret);

/**
 *  jap_ams_getMidletCount
 *
 *  @brief  Get numbers of midlet that included in a specified suite
 *
 *  @param  suite_index     [in] The index for the suite that you want to launch
 *
 *  @retval > 0 if success, the return value is the midlet count
 *          AMS_RST_ERROR if failed
 */
int jap_ams_getMidletCount(int suite_index);

/**
 *  jap_ams_getMidletInfo
 *
 *  @brief  Get detail info for an installed java midlet.
 *
 *  @param  suite_index     [in] The index for the suite that you want to launch
 *  @param  midlet_index    [in] The index for the midlet that belong to the suite
 *  @param  ret             [out] The info structure for putting midlet info
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_getMidletInfo(int  suite_index,int midlet_index, java_midlet_struct *ret);

/**
 *  jap_ams_removeSuite
 *
 *  @brief  Remove an installed java midlet.
 *
 *  @param  index     [in] The index for the suite that you want to launch
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_removeSuite(int index);

/**
 *  jap_ams_launchMidlet
 *
 *  @brief  Launch an installed java midlet.
 *
 *  @param  suite_index     [in] The index for the suite that you want to launch
 *  @param  midlet_index    [in] The index for the midlet that belong to the suite
 *  @param  cause           [in] The launch cause, user select, or push behavior
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_launchMidlet(int suite_index,int midlet_index, java_LanuchCause cause);

/**
 *  jap_ams_registerEimeHandler
 *
 *  @brief  Register for native input method
 *
 *  @retval 
 *          
 */
int jap_ams_registerEimeHandler(void);

/**
 *  jap_ams_getpermission
 *
 *  @brief  get current permission setting for the midlet
 *
 *  @param  suite_index       [in]  The index for the suite that you want to launch
 *  @param  currectSetting    [out] current permission setting for the midlet
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_getpermission(int suite_index, java_permission_setting * currectSetting);

/**
 *  jap_ams_setpermission
 *
 *  @brief  set permission setting for the midlet
 *
 *  @param  suite_index       [in]  The index for the suite that you want to launch
 *  @param  currectSetting    [out] user set permission setting for the midlet
 *
 *  @retval AMS_RST_SUCCESS if success
 *          AMS_RST_ERROR if failed
 */
int jap_ams_setpermission(int suite_index, java_permission_setting * updateSetting);

/**
 *  jap_ams_cancelinstallSuite
 *
 *  @brief  Cancel the ongoing install process
 *
 *  @retval 
 *          
 */
void jap_ams_cancelinstallSuite(void);

/**
 *  jap_ams_querySuiteIndex_by_ID
 *
 *  @brief  query suite index in the MMI AMS table with VM specified ID
 *
 *  @param  suiteId     [in] A pointer to an AJMS_EimeLaunch structure containing the information for launching the external input method procedure
 *
 *  @retval 
 *          
 */
int jap_ams_querySuiteIndex_by_ID(int suiteId);

/**
 *  jap_memcard_status_notify
 *
 *  @brief  Notify currect memory card's status 
 *
 *  @param  bPlugIn     [in] plug in or not
 *
 *  @retval 
 *          
 */
void jap_memcard_status_notify(bool bPlugIn);

/**
 *  jap_queryNotifyData
 *
 *  @brief  Get Current install/delete notify URL and code 
 *
 *  @param  statusCode     [out] install/delete notify Code
 *  @param  url            [out] install/delete notify url
 *
 *  @retval 1 if there is install/delete notify data 
 *          0 if not
 *          
 */
int jap_queryNotifyData(s32 *statusCode, u8** url);

/**
 *  jap_cleanNotifyData
 *
 *  @brief  Clean cache for install/delete notify 
 *
 *  @param  runCB     [in] if run install CB
 *
 *  @retval 
 *          
 */
void jap_cleanNotifyData(bool runCB);

/**
 *  jap_check_if_installing
 *
 *  @brief  check if install process is ongoing 
 *
 *  @retval TRUE if install process is ongoing 
 *          FALSE if not
 *          
 */
bool jap_check_if_installing(void);

int jap_ven_launchMidlet(void);

void jap_reset_launchMidlet(void);

#ifdef __ENABLE_SLDLM_JAVA_OAKMONT__
int jap_SLDLM_VMInit(void);
int jap_SLDLM_VMFini(void);
#endif

#endif /* __JAP_AMS_DEFINE_H__ */

