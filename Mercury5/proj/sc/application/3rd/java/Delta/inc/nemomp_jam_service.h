#ifndef __NEMOMP_JAM_SERVICE_H__
#define __NEMOMP_JAM_SERVICE_H__

#include "nemomp_installer.h"
#include "nemomp.h"

extern int nemomp_jam_install_suite(nm_wchar* p_jad_path, nm_wchar* p_jar_path, nm_wchar* download_url);
extern nm_bool nemomp_jam_remove_suite(nm_int32 suiteID);
extern void nemomp_jam_update_suite(nm_int32 suiteID);
extern nm_int32 nemomp_jam_launch_midlet(nm_int32 suiteID, nm_int32 midletID,  nm_int32 vmHeapSize); //20091103 changed,  20081125: Changed
#ifdef __JAVA_JTWI__
extern nm_int32 nemomp_jam_launch_midlet_by_name(nm_char* storageName, nm_int32 midletID); // 20090226: Added
#endif

extern void nemomp_jam_tck_java_entry(int mode); // 20081201: Added

#endif /* __NEMOMP_JAM_SERVICE_H__ */
