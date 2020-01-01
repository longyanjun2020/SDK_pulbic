#include "java_head.h"

//#include "vm_msgt.ht"

#include "nemomp.h"
#include "nemomp_malloc.h" // 20090104: Added
#include "nemomp_storage.h" // 20090105: Added
#include "nemomp_jam_service.h"
#include "nemomp_jam.h"
#include "java_ams.h"

#include "ven_os.h"
#include "ven_dbg.h"
#include "ven_codec.h"
#include "java_ams_itf.h"
#include "nemomp_malloc.h"
#include "nemomp_files.h"

//#include "java_preinstall_data.h"


#define JAVA_AMS_DEBUG
#define AMS_MAP
//#define fakedata




extern int myMIDletId;
extern int mySuiteId;

extern char myjadPath[128];
extern char myjarPath[128];
extern bool ams_mode;
extern int nemomp_jam_storage_check_and_recovery(void); //20090216 added


extern u32 java_get_app_handle(void);
extern int Java_checkPreinstallFiles(void);

extern int nemomp_ams_installMidletSuite(u16 *jadPath, u16 *jarPath, int KeepRMS);
extern int java_ams_HTTP_download_impl(u16* u16Http,u16* u16FilePath);
extern void java_ams_HTTP_download_quit(void);

#ifdef __JAVA_JTWI__
extern void jPxy_SendStartCnf(int suiteID,int midletID, int cause);
extern bool nemomp_check_push_enable(void);
#else
extern void jPxy_SendStartCnf(void);
#endif


#ifdef AMS_MAP

#define AMS_MAP_FILE "ams.map"
#define AMS_MAP_SIZE 65

extern int ams_map[AMS_MAP_SIZE];
extern int jam_install_suite_id;
extern int jam_update_removed_suite_id;
extern int load_ams_map(void);
extern int remove_ams_map(int index);
extern int save_ams_map(void);
extern int ams_map_load;
extern void list_ams_map(void);
extern void update_ams_map(int index);
extern int get_ams_map_index_by_value(int value);
#endif



extern java_install_storage_e jam_install_target;

int nemomp_ams_initial_req(void);
int nemomp_ams_release_req(void);
int nemomp_ams_getSuiteCount_req(void);
int nemomp_ams_getSuiteInfo_req(int index,java_suite_struct *suite);
int nemomp_ams_removeSuite_req(int index);
int nemomp_ams_getPermission_req(int index,java_permission_setting *java_per_set); //20091119
int nemomp_ams_setPermission_req(int index, java_permission_setting *ps); //20091119
int nemomp_ams_getMidletCount_req(int suite_index,int *mids_count);
int nemomp_ams_getMidletInfo_req(int  suite_index,int midlet_index,java_midlet_struct *midlet);
int nemomp_ams_launchMidlet_req(int suite_index,int midlet_index, java_LanuchCause cause);
int nemomp_ams_installMidletSuite_req(u16 *jadPath, u16 *jarPath, int KeepRMS, java_install_storage_e storage, java_ams_installProgressCB cb);

