#ifndef __DALVIK_AMS_H_
#define __DALVIK_AMS_H_

#include "java_ams.h"
#define JAVA_PREINSTALL_SUITE_COUNT 9

extern int jam_install_suite_id;

extern java_install_storage_e jam_install_target;

extern int java_ams_initial_req(void);
extern int nemomp_ams_initial_req(void);
extern int nemomp_ams_release_req();
extern int nemomp_ams_getSuiteCount_req();
extern int nemomp_ams_getSuiteInfo_req(int index,java_suite_struct * suite);
extern int nemomp_ams_getMidletCount_req(int suite_index, int *mids_count);
extern int nemomp_ams_getMidletInfo_req(int  suite_index,int midlet_index,java_midlet_struct *midlet);
extern int nemomp_ams_removeSuite_req(int index);
extern int nemomp_ams_launchMidlet_req(int suite_index,int midlet_index, java_LanuchCause cause);
extern int nemomp_ams_installMidletSuite_req(u16 *jadPath, u16 *jarPath, int KeepRMS, java_install_storage_e storage, java_ams_installProgressCB cb);
extern int java_ams_set_show_progress_rsp( u32 *selectkey );

#endif
